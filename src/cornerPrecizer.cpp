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
#include "cornerPrecizer.h"

CornerPrecizer::CornerPrecizer(cv::Mat* array, Corner* corners) : ImageAlgorithme(array)
{
	_corners = corners;
	_windowSize = cv::Size(10,10);
	_zeroZone = cv::Size(-1,-1);
	_criteria = *(new cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
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
	_criteria = *(new cv::TermCriteria(type,max_iter,epsilon));
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
	cornerSubPix(
		_imageArray[GR_INPUT_IMAGE],
		*_corners,
		_windowSize,
		_zeroZone,
		_criteria);
}
