/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _CORNERFINDER_H
#define _CORNERFINDER_H

/**
 * @file cornerFinder.h 
 *
 * algorithme finding corners points in a picture/image/frame using Shi and Tomasi Algorithme or Harris' one
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "imageAlgorithme.h"

/**
 * This Class define the algorithme to find Harris Corner Points
 * All parameters except _corners are the parameter set in opencv method
 * @version 1.0.0
 * @author Reynald Pereira
 */
class CornerFinder : public virtual ImageAlgorithme
{

private:
	double 		_qualityLevel;
	double 		_minimumDistance;
	int			_blockSize;
	bool		_harrisUsed;
	double		_weightCoefficientForHarrisAutocorrelation;
	int			_count;
	Corner* 	_corners; /** set of corners that the algorithm must fill in */

public:
	/**
	 * @brief Create a Class of this algorithm using the array of pictures, and the corners to fill in, plus the maximum number of corners. It fixes all parameters to a basic value. 
	 * @param array Array of pictures (the one set in imageAlgorithme.h using the enum imageEnum.h)
	 * @param corners Corners to be find
	 * @param count maximum number of corners we want to find
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	CornerFinder(cv::Mat* array, Corner* corners, int count);
    /**
     * @brief Basic destructor of the class.     
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~CornerFinder();
	/**
	 * @brief This setter will be used if the user wants to change the quality level from the basic value.
	 * @param value Value to set to the quality level
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setQualityLevel(double value);
	/**
	 * @brief This setter will be used if the user wants to change the minimum distance from the basic value.
	 * @param value Value to set to minimum distance
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setMinimumDistance(double value);
	/**
	 * @brief This setter will be used if the user wants to change to true the use the Harris coefficient of not.
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void useHarris();
	/**
	 * @brief This setter will be used if the user wants to change the array of Corners in use.
	 * @param value Value to set to corners
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setCorner(Corner* value);
	/**
	 * @brief This setter will be used if the user wants to change to false the use the Harris coefficient of not.
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void doNotUseHarris();

	/**
	 * @brief This function decide wether or not there's a mask in the algorithm, mask for the pictures
	 * @param mask Picture containing the values of the mask.
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void applyMask(cv::Mat* mask);
	/**
	 * @brief This setter will be used if the user wants to change the block size from the basic value.
	 * @param value Value to set to the block size
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setBlockSize(int value);
	/**
	 * @brief This getter send back the number of corners found
	 * @return return the number of corners found
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	int  getCornersCount();
	/**
	 * @brief This function perform the algorithme she is associated with
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	virtual void perform();
};
#endif
