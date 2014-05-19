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
 * @file cornerPrecizer.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "cornerPrecizer.h"

CornerPrecizer::CornerPrecizer(CvArr** array, Corner** corners, int count)
{
	_imageArray = array;
	_corners = corners;
	_count = count;
	_windowSize = cvSize(10,10);
	_zeroZone = cvSize(-1,-1);
	_criteria = cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
}

CornerPrecizer::~CornerPrecizer() 
{
	_imageArray = NULL;
	_corners	= NULL;
	delete _imageArray;
	delete _corners;
}

void CornerPrecizer::setCriteria(int type, int max_iter, double epsilon)
{
	_criteria = cvTermCriteria(type,max_iter,epsilon);
}

void CornerPrecizer::setWindowSize(CvSize value)
{
	_windowSize = value;
}

void CornerPrecizer::setZeroZone(CvSize value)
{
	_zeroZone = value;
}
void CornerPrecizer::perform()
{
	cvFindCornerSubPix(
		_imageArray[GR_INPUT_IMAGE],
		*_corners,
		&_count,
		_windowSize,
		_zeroZone,
		_criteria);
}