/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Monday May 19 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _TRACKER_H
#define _TRACKER_H

/**
 * @file tracker.h 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include "algorithmeEnum.h"
#include "imageAlgorithme.h"
#include "imageEnum.h"
#include "cornerFinder.h"
#include "cornerPrecizer.h"
#include "lukasKanade.h"
#include "pyrLukasKanade.h"
#include "hornSchunck.h"
//#include "gaitPrint.h"

#define GR_IMAGE_NUMBER 12 
#define GR_CORNER_NUMBER 500

class Tracker
{

private:
	cv::Mat*		_imageArray;
	Corner* 		_corners;
    Corner* 		_outCorners;
    CornerFinder* 	_cornerFinder;
	CornerPrecizer*	_cornerPrecizer;
	LukasKanade*	_lukasKanade;
	PyrLukasKanade*	_pyrLK;
	HornSchunck*	_hornSchunck;
	bool			_init;

public:
	Tracker();
	~Tracker();
	void runAlgos();
	void reInit();
	void setHeatMapImage(cv::Mat img);
	void setInputImage1(cv::Mat img);
	void setInputImage2(cv::Mat img);
	cv::Mat* getOutputFrame();
	Corner* getCorners();
	Corner* getOutCorners();
	void 	reallocCorners();
//	GaitPrint computeGaitPrint();
};
#endif
