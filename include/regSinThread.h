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
 * This File provides a new class to define C Thread in a Java way, that means you can only make another one inherit and overload run()
 * This File also provides a sub-thread class called RegSinThread that calculate the regression of the tacked points into a sin/cos function.
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

/**
 * Please Note That this class is just a tutorial example remade by my own.
 * It Allows to use thread as simple as in Java.
 * @version 1.0.0
 * @author Reynald Pereira.
 */
class Thread
{
  private:
    pthread_t   cThread;    /** C-Thread */
    bool        isRunning;  /** Tell is run() is still going on */
    bool        isDetached; /** Tell is C-Thread is deteched and unaccessible */

  public:
    /**
     * @brief This Constructor is the default one, it makes a Thread, but not to use since it a class that we want to make inherit.
     * @version 1.0.0
     * @author Reynald Pereira
     */
    Thread();
    /**
     * @brief Basic destructor of the class.     
     * @version 1.0.0
     * @author Reynald Pereira
     */
    virtual ~Thread(); 
    /**
     * @brief This function allows you to start a thread just as if you were using basic C-Thread. In fact, it create the thread and give the private C-Function in argument whoch will start run().
     * @return return the int that pthread_create would have returned to test and know if there are errors.
     * @version 1.0.0
     * @author Reynald Pereira.
     */
    int start();
    /**
     * @brief This function allows to take the ouput as the thread when the threaded funcion, run() here, is ended and follow the next thing in the programm.
     * @return return the int that pthread_join would have returned to know what's going on with the threads.     
     * @version 1.0.0
     * @author Reynald Pereira.
     */
    int join();
    /**
     * @brief This function performs detech from C-Thread and allow to continue even if the thread is running.
     * @return return the int that pthread_detach would have returned to get the state
     * @version 1.0.0
     * @author Reynald Pereira
     */
    int detach();
    /**
     * @brief This Funtion is a way to get th C-Thread and use it with the basic funciton of C.
     * @return return the C-Thread
     * @versuin 1.0.0
     * @author Reynald Pereira
     */
    pthread_t self(); 
    /**
     * @brief This function is pure virtual, that means it has to be overloaded with inheritance.
     * @version 1.0.0
     * @author Reynald Pereira
     */
    virtual void* run() = 0;
};

/**
 * This class inherit from Thread and is used to perform the SinRegression to get the movement is a+b.sin(wt)+c.cos(wt)
 * Note that we're usng another boolean to get the running status, but since we do not want to make perturbations in the C-Thread functions with changing every status, it's better to have ots own running status.
 * Also note that we are using this thread as a Java Thread with an overload of run only.
 * @version 1.0.0
 * @author Reynald Pereira
 */
class RegSinThread : public Thread
{
private:
	UnitVector 	_coordinateValues; /** Value of the function we want to make a regression on */
	UnitVector	_timeValues;       /** Value of the absiccea, here we say it's time for practical reasons */
	GaitPrint*	_functionComputed; /** Function computed with a/b/c/w*/
    bool        _runned;           /** Boolean that give the state of the run thread */
public:
    /**
     * @brief This Constructor is the ony one to use with both absiccea and value of the function at the point
     * @param coordinateValues Value of the function at all points
     * @param timeValues all absicceas
     * @version 1.0.0
     * @author Reynald Pereira
     */
	RegSinThread(UnitVector coordinateValues,UnitVector timeValues);
    /**
     * @brief Common destructor or RegSinThread
     * @version 1.0.0
     * @author Reynald Pereira
     */
	virtual ~RegSinThread();   
    /**
     * @brief Overload of run - Implementation of Jean Jacquelin algorithme to do Sinusoïdale Regression
     * @overload
     * @version 1.0.0
     * @author Reynald Pereira
     */ 
	virtual void* run();
    /**
     * @brief Save the output of the algorithme made is run in an external gaitprint.
     * @return Return the function as a gait print that will later be used to display
     * @version 1.0.0
     * @author Reynald Pereira
     */
	GaitPrint* getFunction();
};

#endif
