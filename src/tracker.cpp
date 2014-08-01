/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Tuesday May 20 2014
 *
 * @todo create the class 
 * @bug check if simple Corner pointer is enough
 */

/**
 * @file tacker.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "tracker.h"

Tracker::Tracker()
{
	int cornerCount = GR_CORNER_NUMBER;

	_imageArray = new cv::Mat[GR_IMAGE_NUMBER];
	_corners = new Corner[GR_CORNER_NUMBER];

	_imageArray[GR_MASK_TRACK_IMAGE] = cv::Mat();

	_cornerFinder = new CornerFinder(_imageArray,_corners,cornerCount);
	_cornerPrecizer = new CornerPrecizer(_imageArray,_corners);
	_lukasKanade =  new LukasKanade(_imageArray);
	_pyrLK = new PyrLukasKanade(_imageArray,_corners,cornerCount);
	_hornSchunck = new HornSchunck(_imageArray);

	_init = true;

}

Tracker::~Tracker() 
{
}

void Tracker::runAlgos()
{
 	int color,c0;
 	double acc =0;

 	if ( _init ) 
 	{	
		_corners->clear();
 		_cornerFinder->setCorner(_corners);
 		_cornerPrecizer->setCorner(_corners);
 		_pyrLK->setCorner(_corners);
 		_cornerFinder->perform();
 		_cornerSize = _corners->size();
 		addCorners();
 		c0 = (*_corners)[_cornerSize+50].x;
		_cornerPrecizer->perform();
		_init = false;
		_pyrLK->setCount(_corners->size());
	}
	_pyrLK->perform();
	_outCorners = _pyrLK->getOutCorners(); 		
}

int Tracker::getCornerSize()
{
	return _cornerSize;
}

void Tracker::setInputImage1(cv::Mat img)
{
	_imageArray[GR_INPUT_IMAGE] = cv::Mat(img);
}

void Tracker::setInputImage2(cv::Mat img)
{
	_imageArray[GR_INPUTB_IMAGE] = cv::Mat(img);
}

void Tracker::setHeatMapImage(cv::Mat img)
{
	_imageArray[GR_OUTPUT_IMAGE] = cv::Mat(img);
}

void Tracker::reInit()
{
	_init = true;
}

cv::Mat* Tracker::getOutputFrame()
{
	return new cv::Mat(_imageArray[GR_INPUT_IMAGE]);
}

cv::Mat* Tracker::getOverlayFrame()
{
	return new cv::Mat(_imageArray[GR_OUTPUT_IMAGE]);
}

Corner* Tracker::getCorners()
{
	return _corners;
}

Corner* Tracker::getOutCorners()
{
	return _outCorners;
}

void Tracker::reallocCorners()
{
    _corners = _outCorners;
}

void Tracker::addCorners()
{
	int gSize = GR_GRID_SIZE;
	int nbW, nbH;

   	while ( _imageArray[GR_INPUT_IMAGE].size().width % gSize != 0
   			&& _imageArray[GR_INPUT_IMAGE].size().height % gSize != 0)
   	{
   		gSize--;
   	}

	nbW = _imageArray[GR_INPUT_IMAGE].size().width / gSize;
	nbH = _imageArray[GR_INPUT_IMAGE].size().height / gSize;

	for (int i = 0;i < (gSize+1)*nbW ; i+=nbW)
	{
		for(int j = 0;j < (gSize+1)*nbH; j+=nbH)
		{
			_corners->push_back(*(new cv::Point2f(i,j)));
		}
	}
}

void Tracker::plotField(cv::Mat& image, cv::Point2f p1, cv::Point2f p2)
{
	if( _init) 
	{
		return;
	}

	cv::Mat img;

	int color;
	int xColor = (p1.x - p2.x)*10000/image.size().width ;
	int yColor = (p1.y - p2.y)*10000/image.size().height;

	image.copyTo(img);

	if ( xColor < 0 )
	{
		xColor = -xColor;
	}
	if ( yColor < 0 )
	{
		yColor = -yColor;
	}

	color = xColor+yColor;
	color /= 2; 
	
	cv::circle(img,p1,8,cv::Scalar(color,0,0,150),-1);
	cv::circle(img,p1,4,cv::Scalar(0,color,0,150),-1);
	cv::circle(img,p1,1,cv::Scalar(0,0,color,150),-1);

	cv::addWeighted(img,0.3,image,1-0.3,0,image);


}