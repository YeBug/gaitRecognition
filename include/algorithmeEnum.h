/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _ALGORITHMEENUM_H
#define _ALGORITHMEENUM_H

/**
 * @file algorithmeEnum.h 
 *
 * all different algorithme that will be used
 */

#include <iostream>

enum AlgorithmeEnum 
{ 
	GR_CORNER_FINDER = 0, 
	GR_CORNER_PRECIZER, 
	GR_OPTICAL_FLOW_LK,
	GR_OPTICAL_FLOW_PYR_LK,
	GR_OPTICAL_FLOW_HS
};

#endif