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
#include "pyrLukasKanade.h"

PyrLukasKanade::PyrLukasKanade(cv::Mat* array, Corner* corners, int count) : OpticalFlowCalculater(array)
{
	_imageArray = array;
	_corners = corners;
	_windowSize = cv::Size(31,31);
	_count = count;
	_level = 3;
	_criteria = *(new cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS,20,0.30));
	_flags = 0;
	_minEigThreshold = 0.001;
}

PyrLukasKanade::~PyrLukasKanade() 
{
	_imageArray = NULL;
	_corners	= NULL;
	delete _imageArray;
	delete _corners;
}

void PyrLukasKanade::setCriteria(int type, int max_iter, double epsilon)
{
	_criteria = *(new cv::TermCriteria(type,max_iter,epsilon));
}

void PyrLukasKanade::setFlags(int value)
{
	_flags = value;
}

void PyrLukasKanade::setLevel(int value)
{
	_level = value;
}

void PyrLukasKanade::setMinEigThreshold(double value)
{
	_minEigThreshold = value;
}

std::vector<float> PyrLukasKanade::getTrackError()
{
	return _trackError;
}

std::vector<uchar> PyrLukasKanade::getStatus()
{
	return _status;
}

Corner* PyrLukasKanade::getOutCorners()
{
	return new Corner(_outCorners);
}

void PyrLukasKanade::perform()
{
	calcOpticalFlowPyrLK(
		_imageArray[GR_INPUT_IMAGE],
		_imageArray[GR_INPUTB_IMAGE],
		*_corners,
		_outCorners,
		_status,
		_trackError,
		_windowSize,
		_level,
		_criteria,
		_flags,
		_minEigThreshold);
}
