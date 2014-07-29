/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Friday May 16 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _OPTICALFLOWCALCULATER_H
#define _OPTICALFLOWCALCULATER_H

/**
 * @file opticalFlowCalculater.h 
 *
 * algoithme precize corners points found in a picture/image/frame
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "imageAlgorithme.h"
#include "imageEnum.h"

/**
 * This Class define the supercllas of algorithme to find in a second picture the corners calculated is the first one
 * @version 1.0.0
 * @author Reynald Pereira
 */
class OpticalFlowCalculater : public virtual ImageAlgorithme
{

protected:
	cv::Size	_windowSize; /** opencv arg used in every inherited class */

public:
	/**
	 * @brief Constructor only used in inherited class. It fixes all parameters to a basic value. 
	 * @param array Array of pictures (the one set in imageAlgorithme.h using the enum imageEnum.h)
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	OpticalFlowCalculater(cv::Mat* array);
    /**
     * @brief Basic destructor of the class.  Nerver to be used    
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~OpticalFlowCalculater();
	/**
	 * @brief Only used in inherited class. This setter will be used if the user wants to change the window size from the basic value.
	 * @param value Value to set to window size
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	void setWindowSize(cv::Size value);
	/**
	 * @brief This function performe the algorithme she is associated with
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	virtual void perform();
};

#endif
