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
#include <opencv2/highgui/highgui.hpp>
#include "imageAlgorithme.h"
#include "imageEnum.h"

class OpticalFlowCalculater : public virtual ImageAlgorithme
{

protected:
	cv::Size	_windowSize;

public:
	OpticalFlowCalculater(cv::Mat* array);
	~OpticalFlowCalculater();
	void setWindowSize(cv::Size value);
	virtual void perform();
};

#endif
