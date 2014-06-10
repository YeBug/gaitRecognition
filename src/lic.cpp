#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "lic.h"
#include <malloc.h>

LIC::LIC(cv::Mat* array,Corner* in, Corner* out) : ImageAlgorithme(array)
{
	_inCorners = in;
	_outCorners = out;
	_filterSize = 2048;
	_1LevelFilter = new float[_filterSize];
	_0LevelFilter = new float[_filterSize];
	_filterKernelLenght = 10.00000f;
	_vecMin = 0.050000f;
	_lineClipMax = 100000.0f;
}

LIC::~LIC()
{
	_inCorners = NULL;
	_outCorners = NULL;
	delete _field;
	delete _noise;
	delete _inCorners;
	delete _outCorners;
	delete _1LevelFilter;
	delete _0LevelFilter;
}

void LIC::allocSize()
{
	int size;
	_width = _imageArray[GR_OUTPUT_IMAGE].size().width;
	_height = _imageArray[GR_OUTPUT_IMAGE].size().height;
	std::cout<<_width<<"/"<<_height<<std::endl;
	size = _width*_height;
	_noise = new char[size];
	delete _field;
	_field = new float[size];
	genField();
	genFilter();
	genNoiseInput();
}

void LIC::genField()
{	
	int index;
	float vcMag;
	float scale;

	for(int i=0;i<_height*_width;i++)
	{
		_field[i] = 0;
	}

	for(int i=0;i<_inCorners->size();i++)
	{
		double xTmp = (*_inCorners)[i].x - (*_outCorners)[i].x;
		double yTmp = (*_inCorners)[i].y  - (*_outCorners)[i].y;

		xTmp *= xTmp;
		yTmp *= yTmp;

		_field[(int)((*_inCorners)[i].y*_width+(*_inCorners)[i].x)] = sqrt(xTmp+yTmp);
	}
    for(int	i=0;i<_height;i++)
	for(int	j=0;j<_width;j++)
    {	
		index = (i*_width+j)<<1;
       	vcMag = float(sqrt(double(_field[index]*_field[index]+_field[index+1]*_field[index+1])));
		scale = (vcMag==0.0f)?0.0f:1.0f/vcMag;
		_field[index] *= scale;
        _field[index+1] *= scale;
    }
}


///		make white noise as the LIC input texture     ///
void LIC::genNoiseInput()
{		
    for(int	i=0;i<_height;i++)
	for(int	j=0;j<_width;j++)
    {	
		int r = rand();
		r = ((r & 0xff)+((r&0xff00)>>8))&0xff;
        _noise[i*_width+j] =(char)(unsigned char)r;
    }
}

void LIC::genFilter()
{  		
	for(int i=0;i<_filterSize;i++)
	{
		_0LevelFilter[i] = i;
		_1LevelFilter[i] = i;
	}
}

void LIC::refillDatas(Corner* in, Corner* out)
{
	_inCorners = in;
	_outCorners = out;
	genField();
}

///		flow imaging (visualization) through Line Integral Convolution     ///
void LIC::perform()
{	
	int		vec_id;						///ID in the VECtor buffer (for the input flow field)
	int		advDir;						///ADVection DIRection (0: positive;  1: negative)
	int		advcts;						///number of ADVeCTion stepS per direction (a step counter)
	int		ADVCTS = int(_filterKernelLenght * 3);	///MAXIMUM number of advection steps per direction to break dead loops	
	
	float	vctr_x;						///x-component  of the VeCToR at the forefront point
	float	vctr_y;						///y-component  of the VeCToR at the forefront point
	float	clp0_x;						///x-coordinate of CLiP point 0 (current)
	float	clp0_y;						///y-coordinate of CLiP point 0	(current)
	float	clp1_x;						///x-coordinate of CLiP point 1 (next   )
	float	clp1_y;						///y-coordinate of CLiP point 1 (next   )
	float	samp_x;						///x-coordinate of the SAMPle in the current pixel
	float	samp_y;						///y-coordinate of the SAMPle in the current pixel
	float	tmpLen;						///TeMPorary LENgth of a trial clipped-segment
	float	segLen;						///SEGment   LENgth
	float	curLen;						///CURrent   LENgth of the streamline
	float	prvLen;						///PReVious  LENgth of the streamline		
	float	W_ACUM;						///ACcuMulated Weight from the seed to the current streamline forefront
	float	texVal;						///TEXture VALue
	float	smpWgt;						///WeiGhT of the current SaMPle
	float	t_acum[2];					///two ACcUMulated composite Textures for the two directions, perspectively
	float	w_acum[2];					///two ACcUMulated Weighting values   for the two directions, perspectively
	float*	wgtLUT = NULL;				///WeiGhT Look Up Table pointing to the target filter LUT
	float	len2ID = (_filterSize - 1) / _filterKernelLenght;	///map a curve LENgth TO an ID in the LUT
	unsigned char*	imageToPPM = new unsigned char[_height*_width];

	///for each pixel in the 2D output LIC image///
	for(int  j = 0;	 j < _height;  j ++)
	for(int  i = 0;	 i < _width;  i ++)
	{	
		///init the composite texture accumulators and the weight accumulators///
		t_acum[0] = t_acum[1] = w_acum[0] = w_acum[1] = 0.0f;
	
		///for either advection direction///
    	for(advDir = 0;  advDir < 2;  advDir ++)
    	{	
			///init the step counter, curve-length measurer, and streamline seed///
			advcts = 0;
			curLen = 0.0f;
        	clp0_x = i + 0.5f;
			clp0_y = j + 0.5f;

			///access the target filter LUT///
			wgtLUT = (advDir == 0) ? _0LevelFilter : _1LevelFilter;

			///until the streamline is advected long enough or a tightly  spiralling center / focus is encountered///
        	while( curLen < _filterKernelLenght && advcts < ADVCTS ) 
         	{
				///access the vector at the sample///
				vec_id = ( int(clp0_y) * _width + int(clp0_x) ) << 1;
				vctr_x = _field[vec_id    ];
				vctr_y = _field[vec_id + 1];

				///in case of a critical point///
				if( vctr_x == 0.0f && vctr_y == 0.0f )
				{	
					t_acum[advDir] = (advcts == 0) ? 0.0f : t_acum[advDir];		   ///this line is indeed unnecessary
					w_acum[advDir] = (advcts == 0) ? 1.0f : w_acum[advDir];
					break;
				}
				
				///negate the vector for the backward-advection case///
				vctr_x = (advDir == 0) ? vctr_x : -vctr_x;
				vctr_y = (advDir == 0) ? vctr_y : -vctr_y;

				///clip the segment against the pixel boundaries --- find the shorter from the two clipped segments///
				///replace  all  if-statements  whenever  possible  as  they  might  affect the computational speed///
				segLen = _lineClipMax;
				segLen = (vctr_x < -_vecMin) ? ( int(     clp0_x         ) - clp0_x ) / vctr_x : segLen;
				segLen = (vctr_x >  _vecMin) ? ( int( int(clp0_x) + 1.5f ) - clp0_x ) / vctr_x : segLen;
				segLen = (vctr_y < -_vecMin) ?	
						 (      (    (  tmpLen = ( int(     clp0_y)          - clp0_y ) / vctr_y  )  <  segLen    ) ? tmpLen : segLen      ) 
						: segLen;
				segLen = (vctr_y >  _vecMin) ?
						 (      (    (  tmpLen = ( int( int(clp0_y) + 1.5f ) - clp0_y ) / vctr_y  )  <  segLen    ) ? tmpLen : segLen      ) 
						: segLen;
				
				///update the curve-length measurers///
				prvLen = curLen;
				curLen+= segLen;
				segLen+= 0.0004f;
		   
				///check if the filter has reached either end///
				segLen = (curLen > _filterKernelLenght) ? ( (curLen = _filterKernelLenght) - prvLen ) : segLen;

				///obtain the next clip point///
				clp1_x = clp0_x + vctr_x * segLen;
				clp1_y = clp0_y + vctr_y * segLen;

				///obtain the middle point of the segment as the texture-contributing sample///
				samp_x = (clp0_x + clp1_x) * 0.5f;
				samp_y = (clp0_y + clp1_y) * 0.5f;

				///obtain the texture value of the sample///
				texVal = _noise[ int(samp_y) * _width + int(samp_x) ];

				///update the accumulated weight and the accumulated composite texture (texture x weight)///
				W_ACUM = wgtLUT[ int(curLen * len2ID) ];
				smpWgt = W_ACUM - w_acum[advDir];			
				w_acum[advDir]  = W_ACUM;								
				t_acum[advDir] += texVal * smpWgt;
			
				///update the step counter and the "current" clip point///
				advcts ++;
				clp0_x = clp1_x;
				clp0_y = clp1_y;

				///check if the streamline has gone beyond the flow field///
				if( clp0_x < 0.0f || clp0_x >= _width || clp0_y < 0.0f || clp0_y >= _height)  break;
			}	
     	}

		///normalize the accumulated composite texture///
     	texVal = (t_acum[0] + t_acum[1]) / (w_acum[0] + w_acum[1]);

		///clamp the texture value against the displayable intensity range [0, 255]
		texVal = (texVal <   0.0f) ?   0.0f : texVal;
		texVal = (texVal > 255.0f) ? 255.0f : texVal; 
		imageToPPM[j * _width + i] = (unsigned char) texVal;// ouput frame
		_imageArray[GR_OUTPUT_IMAGE].at<cv::Vec3b>(j,i) = *(new cv::Vec3b(texVal,texVal,texVal));
		if ( texVal != 0)
		{
			std::cout<<"Val:"<<texVal<<std::endl;
		} 	
	}
	toPPM(imageToPPM);
	cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "TOTO", _imageArray[GR_OUTPUT_IMAGE] ); 
}

void LIC::toPPM(unsigned char*  pImage)
{	
		FILE*	o_file;
		if(   ( o_file = fopen("./dest.ppm", "w") )  ==  NULL   )  
		{  
			printf("Can't open output file\n");  
			return;  
		}

  		fprintf(o_file, "P6\n%d %d\n255\n", _width, _height);

  		for(int  j = 0;  j < _height;  j ++)
   		for(int  i = 0;  i < _width;  i ++)
		{
			unsigned  char	unchar = pImage[j * _width + i];
      		fprintf(o_file, "%c%c%c", unchar, unchar, unchar);
		}

  		fclose (o_file);	o_file = NULL;
}

