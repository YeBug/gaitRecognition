/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Friday May 16 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _OPTICALFLOWCALCULATER_H
#define _OPTICALFLOWCALCULATER_H

/**
 * @file opticalFlowCalculater.h 
 *
 * algoithme precize corners points found in a picture/image/frame
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "imageEnum.h"

class OpticalFlowCalculater : public virtual ImageAlgorithme
{

private:
	CvSize	_windowSize;

public:
	OpticalFlowCalculater(CvArr* array);
	~OpticalFlowCalculater();
	void setWindowSize(CvSize value);
	virtual void perform();
};

#endif