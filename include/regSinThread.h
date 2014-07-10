/* -*- c-basic-offset: 4 -*-
 */

/**
 * @author Reynald Pereira <KS10928@kingston.ac.uk>
 * @version 0.0.1 - Thursday May 15 2014
 *
 * @todo create the class 
 * @bug nothing atm
 */

#ifndef _REGSINTHREAD_H
#define _REGSINTHREAD_H

/**
 * @file regSinThread.h 
 *
 * algorithme computing to find the optical flow, saved in vels img
 */

#include <iostream>
#include <pthread.h>
#include <vector>
#include <sstream>
#include <string>
#include "gaitPrint.h"
#include "matrix.h"
#include <cmath>

typedef std::vector<double> UnitVector;
 
class Thread
{
  private:
    pthread_t  m_tid;
    int        m_running;
    int        m_detached;

  public:
    Thread();
    virtual ~Thread(); 
    int start();
    int join();
    int detach();
    pthread_t self(); 
    virtual void* run() = 0;
};


class RegSinThread : public Thread
{

private:
	UnitVector 	_coordinateValues;
	UnitVector	_timeValues;
	GaitPrint*	_functionComputed;
    bool        _runned;
public:
	RegSinThread(UnitVector coordinateValues,UnitVector timeValues);
	virtual ~RegSinThread();    
	virtual void* run();
	GaitPrint* getFunction();
};

#endif
