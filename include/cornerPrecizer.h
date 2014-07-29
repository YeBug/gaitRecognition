/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Friday May 16 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _CORNERPRECIZER_H
#define _CORNERPRECIZER_H

/**
 * @file cornerPrecizer.h 
 *
 * algoithme precize corners points found in a picture/image/frame
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "imageAlgorithme.h"

/**
 * This Class define the algorithme to precize Corner Points previouly found
 * All parameters except _corners are the parameter set in opencv method
 * @version 1.0.0
 * @author Reynald Pereira
 */
class CornerPrecizer : public virtual ImageAlgorithme
{

private:
	Corner* 			_corners; /** set of corners that the algorithm must precize */
	cv::Size			_windowSize;
	cv::Size			_zeroZone;
	cv::TermCriteria	_criteria;

public:
	/**
	 * @brief Create a Class of this algorithm. It fixes all parameters to a basic value. 
	 * @param array Array of pictures (the one set in imageAlgorithme.h using the enum imageEnum.h)
	 * @param corners Corners to be precize
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	CornerPrecizer(cv::Mat* array, Corner* corners);
    /**
     * @brief Basic destructor of the class.     
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~CornerPrecizer();
	/**
	 * @brief This setter will be used if the user wants to change the array of Corners in use.
	 * @param value Value to set to corners
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setCorner(Corner* value);
	/**
	 * @brief This function create a cvtermcriteria using the opencv class and set is in the class parameter.
	 * @param type type of opencv criteria, opencv argument
	 * @param max_iter opencv argument
	 * @param epsilon precision, opencv argument
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setCriteria(int type, int max_iter, double epsilon);
	/**
	 * @brief This setter will be used if the user wants to change the window size from the basic value.
	 * @param value Value to set to window size
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setWindowSize(CvSize value);
	/**
	 * @brief This setter will be used if the user wants to change the zero zone from the basic value.
	 * @param value Value to set to zero zone
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setZeroZone(CvSize value);
	/**
	 * @brief This function perform the algorithme she is associated with
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	virtual void perform();
};

#endif
