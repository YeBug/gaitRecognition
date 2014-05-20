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
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "tacker.h"

Tracker::Tracker()
{
	// exemple provided on openCV book

	int cornerCount = GR_CORNER_NUMBER;

	_imageArray = new CvArr[GR_IMAGE_NUMBER];
	_corners = new Corner[GR_CORNER_NUMBER];

	_imageArray[GR_INPUT_IMAGE] = *(cvLoadImage("image0.jpg",CV_LOAD_IMAGE_GRAYSCALE));
	_imageArray[GR_INPUTB_IMAGE] = *(cvLoadImage("image1.jpg",CV_LOAD_IMAGE_GRAYSCALE));

	CvSize pyrSize = CvSize(_imageArray[GR_INPUT_IMAGE].width+8,_imageArray[GR_INPUTB_IMAGE].height/3);
	
	_imageArray[GR_PYRA_IMAGE] = *(cvCreateImage(pyrSize,IPL_DEPTH_32F,1));
	_imageArray[GR_PYRB_IMAGE] = *(cvCreateImage(pyrSize,IPL_DEPTH_32F,1));

	CvSize 	imageSize = cvGetSize(&_imageArray[GR_INPUT_IMAGE]);

	_imageArray[GR_EIGEN_VALUE_IMAGE] = *(cvCreateImage(imageSize,IPL_DEPTH_32F,1));
	_imageArray[GR_TEMP_IMAGE] = *(cvCreateImage(imageSize,IPL_DEPTH_32F,1));


	_algos.push_back(new CornerFinder(_imageArray,&_corners,cornerCount));
	_algos.push_back(new CornerPrecizer(_imageArray,&_corners,cornerCount));
	_algos.push_back(new LukasKanade(_imageArray));
	_algos.push_back(new PyrLukasKanade(_imageArray,&_corners,cornerCount));
	_algos.push_back(new HornSchunck(_imageArray));

}

Tracker::~Tracker() 
{
	delete _imageArray;
	delete _corners;
	delete _algos;
}

void Tracker::runAlgos()
{
	_algos[GR_CORNER_FINDER]->perform();
	_algos[GR_CORNER_PRECIZER]->perform();
	_algos[GR_OPTICAL_FLOW_PYR_LK]->perform();

	_outCorners = _algos[GR_OPTICAL_FLOW_PYR_LK]->getOutCorner();
}

GaitPrint Tracker::computeGaitPrint()
{

}
