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
 * @file cornerFinder.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "cornerFinder.h"

CornerFinder::CornerFinder(CvArr** array, Corner** corners, int count)
{
	_imageArray = array;
	_corners = corners;
	_count = count;
	_qualityLevel = 0.01;
	_minimumDistance = 5.0;
	_blockSize = 3;
	_harrisUsed	= false;
	_weightCoefficientForHarrisAutocorrelation = 0.4;
}

CornerFinder::~CornerFinder() 
{
	_imageArray = NULL;
	_corners	= NULL;
	delete _imageArray;
	delete _corners;
}

void CornerFinder::setQualityLevel(double value)
{
	_qualityLevel = value;
}

void CornerFinder::setMinimumDistance(double value)
{
	_minimumDistance = value;
}

void CornerFinder::useHarris()
{
	_harrisUsed = true;
}

void CornerFinder::doNotUseHarris()
{
	_harrisUsed = false;
}

void CornerFinder::applyMask(CvArr* mask)
{
	_imageArray[GR_MASK_TRACK_IMAGE] = mask;
}

int CornerFinder::getCornersCount()
{
	return _count;
}

void CornerFinder::perform()
{
	cvGoodFeaturesToTrack(
		_imageArray[GR_INPUT_IMAGE],
		_imageArray[GR_EIGEN_VALUE_IMAGE],
		_imageArray[GR_TEMP_IMAGE],
		*_corners,
		&_count,
		_qualityLevel,
		_minimumDistance,
		_imageArray[GR_MASK_TRACK_IMAGE],
		_blockSize,
		(int)_harrisUsed,
		_weightCoefficientForHarrisAutocorrelation);
}