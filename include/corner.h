/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Monday May 19 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _CORNER_H
#define _CORNER_H

/**
 * @file corner.h 
 *
 * redifinition of cv type

 */

#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>

typedef std::vector<cv::Point2f> Corner;
typedef std::vector<cv::KeyPoint> KeyPoint;

#endif
