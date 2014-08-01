/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Friday May 16 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _IMAGEALGORITHME_H
#define _IMAGEALGORITHME_H

/**
 * @file imageAlgorithme.h 
 *
 * algoithme precize corners points found in a picture/image/frame
 */

#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <opencv2/highgui/highgui.hpp>
#include "imageEnum.h"
#include "corner.h"

/**
 * This Class define the superclass of image algorithm that will be used in all the software or in further implementation
 * @version 1.0.0
 * @author Reynald Pereira
 */
class ImageAlgorithme   
{

protected:
	cv::Mat*		_imageArray; /** array containing all images used in the whole software */

public:
	/**
	 * @brief Constructor only used in inherited class. It fixes all parameters to a basic value. 
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	ImageAlgorithme();
	/**
	 * @brief Constructor only used in inherited class. It fixes all parameters to a basic value. 
	 * @param array Array of pictures (the one set in imageAlgorithme.h using the enum imageEnum.h)
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	ImageAlgorithme(cv::Mat* array);
    /**
     * @brief Basic destructor of the class.  Nerver to be used    
     * @version 1.0.0
     * @author Reynald Pereira
     */
	~ImageAlgorithme();
	/**
	 * @brief This function performe the algorithme she is associated with
	 * @version 1.0.0
	 * @author Reynald Pereira
	 */
	virtual void perform() = 0;
};

#endif
