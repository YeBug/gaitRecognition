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
	_keypoints = new KeyPoint[GR_CORNER_NUMBER];

	_imageArray[GR_MASK_TRACK_IMAGE] = cv::Mat();

	_cornerFinder = new CornerFinder(_imageArray,_corners,cornerCount);
	_cornerPrecizer = new CornerPrecizer(_imageArray,_corners);
	_lukasKanade =  new LukasKanade(_imageArray);
	_pyrLK = new PyrLukasKanade(_imageArray,_corners,cornerCount);
	_hornSchunck = new HornSchunck(_imageArray);
	_lic = new LIC(_imageArray,_corners,_corners);
	_surf = new SURF(_imageArray,_keypoints);

	_init = true;

}

Tracker::~Tracker() 
{
}

void Tracker::runAlgos()
{
 	int color;
	cv::FlannBasedMatcher matcher;
	std::vector<cv::DMatch> matchingKp;

 	//_imageArray[GR_OUTPUT_IMAGE] = *(new cv::Mat(_imageArray[GR_INPUT_IMAGE].size(),CV_8UC4));

 	if ( _init ) 
 	{	
 		//_imageArray[GR_OUTPUT_IMAGE] = *(new cv::Mat(_imageArray[GR_INPUT_IMAGE].size(),CV_8UC4));
		_lic->allocSize();
		_corners->clear();
 		_cornerFinder->setCorner(_corners);
 		_cornerPrecizer->setCorner(_corners);
 		_pyrLK->setCorner(_corners);
 		_cornerFinder->perform();
		_cornerPrecizer->perform();
		_init = false;
		_pyrLK->setCount(_corners->size());
		_imageArray[GR_INPUT_IMAGE].copyTo(_imageArray[GR_SURF_IMAGE]);
		_surf->perform();
	}
	_prevKeypoints = _keypoints;
	_imageArray[GR_SURF_IMAGE].copyTo(_imageArray[GR_SURF_PREV_IMAGE]);
	_pyrLK->perform();
	_outCorners = _pyrLK->getOutCorners();
	_lic->refillDatas(_corners,_outCorners);
	//_lic->perform();
	_imageArray[GR_OUTPUT_IMAGE].copyTo(_imageArray[GR_SURF_IMAGE]);
	_surf->perform();

	matcher.match(_imageArray[GR_SURF_IMAGE],
					_imageArray[GR_SURF_PREV_IMAGE],
					matchingKp);
	cv::drawMatches(_imageArray[GR_INPUT_IMAGE],
					*_prevKeypoints,
					_imageArray[GR_OUTPUT_IMAGE],
					*_keypoints,
					matchingKp,
					_imageArray[GR_VELY_IMAGE]);

	for( size_t i = 0; i < _keypoints->size(); i++ )
	{
		//cv::circle( _imageArray[GR_INPUT_IMAGE], (*_keypoints)[i], 2, cv::Scalar(0,150,150), -1, 8, 0 );
	}
	


	cv::imwrite("dst.png",_imageArray[GR_VELY_IMAGE]);
	
	cv::namedWindow( "test", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "test", _imageArray[GR_VELY_IMAGE] );
   // cv::namedWindow( "HeatMap", cv::WINDOW_AUTOSIZE );// Create a window for display.
   // cv::imshow( "HeatMap", _imageArray[GR_OUTPUT_IMAGE] ); 
	
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

void Tracker::plotField(cv::Mat& image, cv::Point2f x, cv::Point2f y)
{
	if( _init) 
	{
		return;
	}

	cv::Point2f q,p;

	int color = ((x.x - y.x)*255/image.size().width + (x.y - y.y)*255/image.size().height)/2;
	double angle = atan2((double)x.y-y.y,(double)x.x-y.x);
	double hyp = sqrt((x.y - y.y)*(x.y - y.y)+(x.x - y.x)*(x.x - y.x));
	double pi = 3.1415957f;

	y.x = (int)(x.x-3*hyp*cos(angle));
	y.y = (int)(x.y-3*hyp*sin(angle));

	q.x = (int)(y.x+9*cos(angle + pi/4));
	q.y = (int)(y.y+9*sin(angle + pi/4));

	p.x = (int)(y.x+9*cos(angle - pi/4));
	p.y = (int)(y.y+9*sin(angle - pi/4));

	//std::cout<<"Color found : "<<color<<std::endl;
	if ( color < 0 ) 
	{
		color = -color;
	}
	if ( color> 1 && color< 65 ) 
	{
		color = 65;
	}
	if ( color > 0 && color < 85 )
	{
		cv::line( image,x,y,cv::Scalar(color,0,0,color),1,1,0);
		cv::line( image,q,y,cv::Scalar(color,0,0,color),1,1,0);
		cv::line( image,p,y,cv::Scalar(color,0,0,color),1,1,0);
	}
	else if ( color > 85 && color < 170 )
	{
		cv::line( image,x,y,cv::Scalar(0,color,color,color),1,1,0);
		cv::line( image,q,y,cv::Scalar(0,color,color,color),1,1,0);
		cv::line( image,p,y,cv::Scalar(0,color,color,color),1,1,0);
	
	}
	else  if ( color > 170 && color < 255 )
	{
		cv::line( image,x,y,cv::Scalar(0,0,color,color),1,1,0);
		cv::line( image,q,y,cv::Scalar(0,0,color,color),1,1,0);
		cv::line( image,p,y,cv::Scalar(0,0,color,color),1,1,0);
	
	}

}