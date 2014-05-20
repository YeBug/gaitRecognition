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
 * @file pyrLukasKanade.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "pyrLukasKanade.h"

PyrLukasKanade::PyrLukasKanade(CvArr*, Corner** corners, int count) : OpticalFlowCalculater(array)
{
	_imageArray = array;
	_corners = corners;
	_windowSize = cvSize(10,10);
	_count = count;
	_level = 5;
	_status = new char[_count];
	_trackError = new float[_count];
	_outCorners = new Corner[_count];
	_criteria = cvTermCriteria(CV_TERCRIT_ITER | CV_TERMCRIT_EPS,20,0.30);
	_flags = 0;
}

PyrLukasKanade::~PyrLukasKanade() 
{
	_imageArray = NULL;
	_corners	= NULL;
	delete _imageArray;
	delete _corners;
	delete _outCorners;
	delete _status;
	delete _trackError;
}

void PyrLukasKanade::setCriteria(int type, int max_iter, double epsilon)
{
	_criteria = cvTermCriteria(type,max_iter,epsilon);
}

void PyrLukasKanade::setFlags(int value)
{
	_flags = value;
}

void PyrLukasKanade::setLevel(int value)
{
	_level = value;
}

char* PyrLukasKanade::getStatus()
{
	return _status;
}

float* PyrLukasKanade::getTrackError()
{
	return _trackError;
}

Corner* PyrLukasKanade::getOurCorners()
{
	return _outCorners;
}

void PyrLukasKanade::perform()
{
	cvCalcOpticalFlowPyrLK(
		&_imageArray[GR_INPUT_IMAGE],
		&_imageArray[GR_OUTPUT_IMAGE],
		&_imageArray[GR_PYRA_IMAGE],
		&_imageArray[GR_PYRB_IMAGE],
		_corners;
		_outCorners,
		_count,
		_windowSize,
		_level,
		_status,
		_trackError
		_criteria,
		_flags);
}