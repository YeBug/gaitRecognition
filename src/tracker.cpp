/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Tuesday May 20 2014
 *
 * @todo create the class 
 * @bug check if simple Corner pointer is enough
 */

/**
 * @file tacker.cpp 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include "tacker.h"

Tracker::Tracker()
{
	_imageArray = new CvArr[GR_IMAGE_NUMBER];
}

Tracker::~Tracker() 
{
	delete _imageArray;
	delete _corners;
	delete _algos;
}

void Tracker::run()
{

}

void Tracker::init()
{

}

void Tracker::stop()
{

}

GaitPrint Tracker::computeGaitPrint()
{

}
