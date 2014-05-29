/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Monday May 19 2014
 *
 * @todo create the class 
 * @bug check if simple Corner pointer is enough
 */

/**
 * @file lukasKanade.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "lukasKanade.h"

LukasKanade::LukasKanade(cv::Mat* array) : OpticalFlowCalculater(array)
{
	_imageArray = array;
	_windowSize = cvSize(10,10);
}

LukasKanade::~LukasKanade() 
{
	_imageArray = NULL;
	delete _imageArray;
}

void LukasKanade::perform()
{
	cvCalcOpticalFlowLK(
		&_imageArray[GR_INPUT_IMAGE],
		&_imageArray[GR_OUTPUT_IMAGE],
		_windowSize,
		&_imageArray[GR_VELX_IMAGE],
		&_imageArray[GR_VELY_IMAGE]);
}
