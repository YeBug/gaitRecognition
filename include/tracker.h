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
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <vector.h>
#include "imageAlgorithme.h"
#include "imageEnum.h"
#include "cornerFinder.h"
#include "cornerPrecizer.h"
#include "lukasKanade.h"
#include "pyrLukasKanade.h"
#include "hornSchuck.h"
#include "gaitPrint.h"

#define GR_IMAGE_NUMBER 11 
 
class Tracker : 
{

private:
	CvArr*			_imageArray;
	Corner* 		_corners;
	std::vector< imageAlgorithme > _algos;

public:
	Tracker();
	~Tracker();
	void init();
	void run();
	void stop();
	GaitPrint computeGaitPrint();

#endif