/*
 * RobotStrap.h
 *
 *  Created on: Feb 16, 2016
 *      Author: Tirth Patel & Pranav Kandarpa
 */

#ifndef SRC_ROBOTSTRAP_H_
#define SRC_ROBOTSTRAP_H_

#include <stdio.h>

/**
 * This is the base class
 */
class RobotStrap : public SimpleRobot
{
	private:

	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick

	public:

		/* Constructor */
		RobotStrap();
		~RobotStrap();

		/* Mode member functions */
		void Test( void );
		void Autonomous( void );
		void OperatorControl( void );

		/* Helper member functions */
		void printStatus( void );

};

#endif /* SRC_ROBOTSTRAP_H_ */
