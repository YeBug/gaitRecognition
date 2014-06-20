/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _IMAGEENUM_H
#define _IMAGEENUM_H

/**
 * @file imageEnum.h 
 *
 * all different images that will be used
 */

#include <iostream>

enum ImageEnum 
{ 
	GR_INPUT_IMAGE = 0, 
	GR_INPUTB_IMAGE,
	GR_OUTPUT_IMAGE, 
	GR_EIGEN_VALUE_IMAGE, 
	GR_TEMP_IMAGE, 
	GR_VELX_IMAGE, 
	GR_VELY_IMAGE, 
	GR_PYRA_IMAGE,
	GR_PYRB_IMAGE, 
	GR_DISPLAYED_IMAGE, 
	GR_MASK_TRACK_IMAGE,
	GR_MASK_OPTICAL_FLOW_IMAGE,
	GR_OVERLAY_LIC,
	GR_SURF_IMAGE,
	GR_SURF_PREV_IMAGE
};

#endif