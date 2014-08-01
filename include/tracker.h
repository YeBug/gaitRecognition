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
#include <cmath>

#define GR_IMAGE_NUMBER 16
#define GR_CORNER_NUMBER 500
#define GR_GRID_SIZE 14

/**
 * This Class is the main class, it provide a set of function simple to the user to manipulate the datas with the algorithm.
 * Its aim is to be rewrittable to make some easy changes of the algorithme in use and the order of the actions
 * @version 1.0.0
 * @author Reynald Pereira
 */
class Tracker
{

private:
	cv::Mat*		_imageArray;		/** array containing all images */
	Corner* 		_corners;			/** input corners, found with cornerd finder and precizer */
    Corner* 		_outCorners;		/** output coners, computed with optical flow algorithm */
    CornerFinder* 	_cornerFinder;		/** algorithm to find corners */
	CornerPrecizer*	_cornerPrecizer;	/** algorithm to precize corners */
	LukasKanade*	_lukasKanade;		/** optical flow algorithm based on corners */
	PyrLukasKanade*	_pyrLK;				/** optical flow algorithm based on corners */
	HornSchunck*	_hornSchunck;		/** optical flow algorithm based on corners */
	bool			_init;				/** tell if the tracker is in initialisation phase or not */
	int 			_cornerSize;		/** number of corners in use, without the ones added by hand in addCorner() */

public:
	/**
	 * @briefThis class is the main class used to mix all algorithme and make it clearer for the user. Can be rewrited anyway you want to change the algorithm.
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	Tracker();
    /**
     * @brief Basic destructor of the class.     
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~Tracker();
	/**
	 * @brief this is the main function used, it starts one step the whole calcul you want to thred or loop
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	void runAlgos();
	/**
	 * @brief This function is used to clear the datas as much a you need, since it's most video utilisation, you need to refresh the datas tou're based on not to have bigger and bigger errors.
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	void reInit();
	/**
	 * @brief Give the array of picture the image that will be used as heat map
	 * @param img Picture to give
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	void setHeatMapImage(cv::Mat img);
	/**
	 * @brief Give the array of picture the image that will be used as main input to all algoritm
	 * @param img Picture to give
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	void setInputImage1(cv::Mat img);
	/**
	 * @brief Give the array of picture the image that will be used as second input to calculte flow mostly
	 * @param img Picture to give
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	void setInputImage2(cv::Mat img);
	/**
	 * @brief This function add a certain number of corners that are used to display the heat map picture
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	void addCorners();	
	/**
	 * @brief Give the number of corners found and in used by the algoritme to be used in non optical algrorithm
     * @return return the number currently in used
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	int getCornerSize();
	/**
	 * @brief Give the frame calculated as output from certain algorithm
	 * @return return the output frame
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	cv::Mat* getOutputFrame();
	/**
	 * @brief Give the overlay/heat map that is computed inside the algoritme
     * @return return the overlay
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	cv::Mat* getOverlayFrame();
	/**
	 * @brief Give a vector containing all input corners
	 * @return return corners
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	Corner* getCorners();
	/**
	 * @brief Give a vector containing all the computed corners, via optical flow algorithm
	 * @return return outcornerrs
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	Corner* getOutCorners();
	/**
	 * @brief this function reinit both corners and outcorners set of points not to make errors occur with reminescence of previous step if looped
	 * @version 1.0.0
     * @author Reynald Pereira
	 */
	void 	reallocCorners();
	/**
	 * @brief This function plot the field of point 1 by 1 with the ones returned by getOurCorners, only use the points given to it
     * @param image image on which you draw
     * @param p1 input corner value of the point, where the poitn is gonna be drawn
     * @param p2 outcorner value of the point, used to compute the intesity of the color depending on the distance tracked between p1 and p2
     * @version 1.0.0
     * @author Reynald Pereira
	 */
	void 	plotField(cv::Mat& image, cv::Point2f p1, cv::Point2f p2);
};
#endif
