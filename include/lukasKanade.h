/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _LUKASKANADE_H
#define _LUKASKANADE_H

/**
 * @file lukasKanade.h 
 *
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>
#include "opticalFlowCalculater.h"

/**
 * This Class define the algorithme to find in a second picture the corners calculated is the first one
 * It uses opencv LukasKanade alogrithm
 * @version 1.0.0
 * @author Reynald Pereira
 */
class LukasKanade : public OpticalFlowCalculater
{

private:

public:
	/**
	 * @brief Create a Class of this algorithm. It fixes all parameters to a basic value. 
	 * @param array Array of pictures (the one set in imageAlgorithme.h using the enum imageEnum.h)
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	LukasKanade(cv::Mat* array);
    /**
     * @brief Basic destructor of the class.     
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~LukasKanade();
	/**
	 * @brief This function perform the algorithme she is associated with
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	virtual void perform();
};

#endif
