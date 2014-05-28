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
 * @file hornSchunck.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "hornSchunck.h"

HornSchunck::HornSchunck(CvArr* array) : OpticalFlowCalculater(array)
{
	_imageArray = array;
	_windowSize = cvSize(10,10);
	_usePrevious = false;
	_lambda = 1;
	_criteria = cvTermCriteria(CV_TERCRIT_ITER | CV_TERMCRIT_EPS,20,0.30);
}

HornSchunck::~HornSchunck() 
{
	_imageArray = NULL;
	delete _imageArray;
}

void HornSchunck::setCriteria(int type, int max_iter, double epsilon)
{
	_criteria = cvTermCriteria(type,max_iter,epsilon);
}

void HornSchunck::usePrevious()
{
	_usePrevious = true;
}

void HornSchunck::doNotUsePrevious()
{
	_usePrevious = false;
}

void setLambda(double value)
{
	_lambda = value;
}

void HornSchunck::perform()
{
	cvCalcOpticalFlowHS(
		&_imageArray[GR_INPUT_IMAGE],
		&_imageArray[GR_OUTPUT_IMAGE],
		_usePrevious,
		&_imageArray[GR_VELX_IMAGE],
		&_imageArray[GR_VELY_IMAGE],
		_lambda
		_criteria);
	usePrevious();
}