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
	size = 2*_width*_height;
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

	for(int i=0;i<2*_height*_width;i++)
	{
		_field[i] = 0;
	}

	for(int i=0;i<_inCorners->size();i++)
	{
		expandField(5,i);
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

void LIC::expandField(int times, int interation)
{
	double x1,x2,y1,y2;

	int index;

	double c1 = (*_inCorners)[interation].x;
	double c2 = (*_outCorners)[interation].x;
	double c3 = (*_inCorners)[interation].y;
	double c4 = (*_outCorners)[interation].y;



	for(int i=0;i<times;i++)
	{
		x1 = c1 - c2;
		y1 = c3  - c4;

		x2 = x1*x1;
		y2 = y1*y1;

		index = (int)(c1*_width+c3);

		if (index > 2*_width*_height-2)
		{
			index = 2*_width*_height-2;
		}
		if ( index < 0 )
		{
			break;
		}

		_field[index] = sqrt(x2+y2);
		_field[index+1] = sqrt(x2+y2);

		c1 += x1;
		c2 += y1;
		c3 += x1;
		c4 += y1;
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

void LIC::perform()
{	 
	int fieldId;
	int advectionDir;
	int advectionNb;
	int maxAdvection = _filterKernelLenght *3;
	float fieldX;
	float fieldY;
	float clip0X;
	float clip0Y;
	float clip1X;
	float clip1Y;
	float sampleX;
	float sampleY;
	float tmpLength;
	float segmentLength;
	float currentLength;
	float previousLength;
	float weightAcc;
	float textureValue;
	float sampleWeight;
	float compositeAccum[2];
	float weightAccum[2];
	float* weightTable;
	float lengthToId = (_filterSize-1)/_filterKernelLenght;
	unsigned char img[2*_height*_width];

	for(int i=0;i<_height*_width;i++)
	{
		img[i] = 0;
	}

    for(int	i=0;i<_height;i++)
	for(int	j=0;j<_width;j++)
	{
		for(advectionDir=0;advectionDir<2;advectionDir++)
		{
			compositeAccum[0] = compositeAccum[1] = weightAccum[0] = weightAccum[1] = 0.0f;

			advectionNb = 0;
			currentLength =0;
			clip0X = j+0.5;
			clip0Y = i+0.5;


			if ( advectionDir == 0)
			{
				weightTable = _0LevelFilter;
			}
			else
			{
				weightTable = _1LevelFilter;
			}

			while( currentLength < _filterKernelLenght && advectionNb < maxAdvection)
			{
				fieldId = ((int)clip0Y*_width+(int)clip0X) << 1;
				if (fieldId > 2*_width*_height-2)
				{
					fieldId = 2*_width*_height-2;
				}	
				fieldX = _field[fieldId];
				fieldY = _field[fieldId+1];

				if (fieldX==0 && fieldY == 0)
				{
					compositeAccum[advectionDir] = (advectionNb==0)?0:compositeAccum[advectionDir];
					weightAccum[advectionDir] = (advectionNb==0)?1:weightAccum[advectionDir];
					break;
				}

				if ( advectionDir == 0)
				{
					fieldX = -fieldX;
					fieldY = -fieldY;
				}

				segmentLength = _lineClipMax;
				segmentLength = (fieldX < -_vecMin) ? ( int(     clip0X         ) - clip0X ) / fieldX : segmentLength;
				segmentLength = (fieldX >  _vecMin) ? ( int( int(clip0X) + 1.5f ) - clip0X ) / fieldX : segmentLength;
				segmentLength = (fieldY < -_vecMin) ?	(((  tmpLength = ( int(clip0Y)- clip0Y ) / fieldY  )  <  segmentLength) ? tmpLength : segmentLength): segmentLength;
				segmentLength = (fieldY >  _vecMin) ?(((tmpLength = ( int( int(clip0Y) + 1.5f ) - clip0Y ) / fieldY)<segmentLength) ? tmpLength : segmentLength): segmentLength;

				previousLength = currentLength;
				currentLength += segmentLength;
				segmentLength += 0.0004;

				segmentLength = (currentLength>_filterKernelLenght)?(_filterKernelLenght-previousLength):segmentLength;
				currentLength = _filterKernelLenght;

				clip1X = clip0X + fieldX*segmentLength;
				clip1Y = clip0Y + fieldY*segmentLength;

				sampleX = (clip0X+clip1X)/2.0;
				sampleY = (clip0Y+clip1Y)/2.0;

				textureValue = _noise[(int)sampleY*_width+(int)sampleX];

				weightAcc = weightTable[(int)(currentLength*lengthToId)];
				sampleWeight = weightAcc - weightAccum[advectionDir];
				weightAccum[advectionDir] = weightAcc;
				compositeAccum[advectionDir] += textureValue*sampleWeight;

				advectionNb++;
				clip0X = clip1X;
				clip0Y = clip1Y;			


				if( clip0X < 0 || clip0X >= _width || clip0Y < 0 || clip0Y >= _height)
				{
					break;
				}
			}
		}

		textureValue = (compositeAccum[0]+compositeAccum[1])/(weightAccum[0]+weightAccum[1]);
		textureValue = (textureValue < 0)?0:textureValue;
		textureValue = (textureValue>255)?255:textureValue;

		img[i*_width+j] = (unsigned char)textureValue;
		// rajouter _imageArray
	}
		toPPM(img);
}

void LIC::toPPM(unsigned char*  image)
{	
	FILE*	o_file;
	if(   ( o_file = fopen("./dest.ppm", "w") )  ==  NULL   )  
	{  
		printf("Can't open output file\n");  
		return;  
	}

	fprintf(o_file, "P6\n%d %d\n255\n", _width, _height);

	for(int  j = 0;  j < _height;  j ++) 
	{
		for(int  i = 0;  i < _width;  i ++)
		{
			unsigned  char	unchar = image[j * _width + i];
  			fprintf(o_file, "%c%c%c", unchar, unchar, unchar);
		}
	}
	
	fclose (o_file);	o_file = NULL;
}

