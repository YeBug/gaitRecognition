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
	// exemple provided in openCV book

	int cornerCount = GR_CORNER_NUMBER;

	_imageArray = new cv::Mat[GR_IMAGE_NUMBER];
	_corners = new Corner[GR_CORNER_NUMBER];

	//_imageArray[GR_INPUT_IMAGE] = cv::imread("./data/image0.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	//_imageArray[GR_INPUTB_IMAGE] = cv::imread("./data/image1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
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
 	int r = 4;
 	if ( _init ) 
 	{
 		_cornerFinder->perform();
		_cornerPrecizer->perform();
		_init = false;
	}
	_pyrLK->perform();
	_outCorners = _pyrLK->getOutCorners();

	std::cout<<"** Number of corners detected: "<<_corners->size()<<std::endl;

  	for( size_t i = 0; i < _corners->size(); i++ )
    { 
    	//cv::circle( _imageArray[GR_INPUT_IMAGE], (*_corners)[i], r, cv::Scalar(128,128,128), -1, 8, 0 );
    	cv::line( _imageArray[GR_INPUT_IMAGE], (*_corners)[i],(*_outCorners)[i],cv::Scalar(128,128,128),1,1,0);
    }

	cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "Display window", _imageArray[GR_INPUT_IMAGE] ); 

    _corners = _outCorners;

	
}

void Tracker::setInputImage1(cv::Mat img)
{
	_imageArray[GR_INPUT_IMAGE] = cv::Mat(img);
}

void Tracker::setInputImage2(cv::Mat img)
{
	_imageArray[GR_INPUTB_IMAGE] = cv::Mat(img);
}

void Tracker::reInit()
{
	_init = true;
}