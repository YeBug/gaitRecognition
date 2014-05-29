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
 * @file opticalFlowCalculater.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include "opticalFlowCalculater.h"

OpticalFlowCalculater::OpticalFlowCalculater(cv::Mat* array) : ImageAlgorithme(array)
{
}

OpticalFlowCalculater::~OpticalFlowCalculater() 
{
}

void OpticalFlowCalculater::setWindowSize(cv::Size value)
{
	_windowSize = value;
}

void OpticalFlowCalculater::perform() 
{
}