/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _CORNERFINDER_H
#define _CORNERFINDER_H

/**
 * @file cornerFinder.h 
 *
 * algoithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "imageAlgorithme.h"
#include "imageEnum.h"

class CornerFinder : public virtual ImageAlgorithme
{

private:
	double 		_qualityLevel;
	double 		_minimumDistance;
	int			_blockSize;
	bool		_harrisUsed;
	double		_weightCoefficientForHarrisAutocorrelation;
	int			_count;
	Corner** 	_corners;

public:
	CornerFinder(CvArr** array, Corner** corners, int count);
	~CornerFinder();
	void setQualityLevel(double value);
	void setMinimumDistance(double value);
	void useHarris();
	void doNotUseHarris();
	void applyMask();
	void setBlockSize(int value);
	virtual void perform();
};

#endif