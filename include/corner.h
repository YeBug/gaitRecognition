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

/**
 * @brief This type define what a corner point is, used in Harris Corner
 * @version 1.0.0
 * @author Reynald Pereira
 */
typedef std::vector<cv::Point2f> Corner;

/**
 * @brief This type define what a keypoint point is, used is SIFT and SURF
 * @version 1.0.0
 * @author Reynald Pereira
 */
typedef std::vector<cv::KeyPoint> KeyPoint;

#endif
