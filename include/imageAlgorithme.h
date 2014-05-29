/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Friday May 16 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _IMAGEALGORITHME_H
#define _IMAGEALGORITHME_H

/**
 * @file imageAlgorithme.h 
 *
 * algoithme precize corners points found in a picture/image/frame
 */

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include "imageEnum.h"
#include "corner.h"

class ImageAlgorithme   
{

protected:
	cv::Mat*		_imageArray;

public:
	ImageAlgorithme();
	ImageAlgorithme(cv::Mat* array);
	~ImageAlgorithme();
	virtual void perform() = 0;
};

#endif
