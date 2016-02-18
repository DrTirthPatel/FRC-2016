/*
 * RobotStrap.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: Tirth Patel & Pranav Kandarpa
 */

#include "WPILib.h"
#include "RobotStrap2015.h"
#include "constants2015.h"

/**
 *  Constructor
 */
RobotStrap::RobotStrap() :
	// Initialize all the member objects in the same order
	// declared within the body.
	myRobot(LEFT_MOTOR_PORT, RIGHT_MOTOR_PORT),
	stickLeft(JOYSTICK_PORT_LEFT),
	stickRight(JOYSTICK_PORT_RIGHT)
{
	myRobot.SetExpiration(0.1);
}

/**
 * Prints robot status to the console
 */
void RobotStrap::printStatus( void )
{
	// Get an instance of the driver station to use its API
	DriverStation* ds = DriverStation::GetInstance();

	// Get important variable data
	float voltage = ds -> GetBatteryVoltage();

	// Print the data
	printf("=======STATUS=======\n");
	printf("Battery Voltage: %f\n", voltage);
}

/**
 * Runs during test mode
 */
void RobotStrap::Test( void )
{
	//do nothing
}

/**
 * Drive left & right motors for 2 seconds then stop
 */
void RobotStrap::Autonomous( void )
{
	myRobot.SetSafetyEnabled(false);
	myRobot.Drive(-0.5, 0.0); // drive forwards half speed
	Wait(2.0); // for 2 seconds
	myRobot.Drive(0.0, 0.0); // stop robot
}

/**
 * Runs the motors with arcade steering.
 */
void RobotStrap::OperatorControl( void )
{
	// Set the safety
	myRobot.SetSafetyEnabled(true);

	// Establish end-effectors
	Jaguar* lift = new Jaguar(LIFT_MOTOR_PORT);
	Compressor* c = new Compressor(SPIKE_RELAY_PORT, PRESSURE_SWITCH_PORT);

	// Establish limit switches
	DigitalInput *fwdlim = new DigitalInput(FWD_LIM_PORT);
	DigitalInput *bwdlim = new DigitalInput(BWD_LIM_PORT);

	// Start the compressor
	c -> Start();

	// Infinite loop
	while (IsOperatorControl())
	{
		// Print status if the button is pressed
		if(stickRight.GetRawButton(11))
			this -> printStatus();

		// Move the arm based on buttons
		bool launchValue = stickRight.GetRawButton(1);
		bool rewindValue = stickRight.GetRawButton(2);

		// Determine the speed to throw the arm at
		float speed = (stickRight.GetThrottle() - (-1)) / 2;

		if(launchValue /* && !(fwdlim -> Get()) */)
			// make arm launch forwards
			arm -> Set(1 * speed);
		else if(rewindValue /* && !(bwdlim -> Get()) */)
			// make the arm launch backwards
			arm -> Set(-1 * speed);
		else
			arm -> Set(0);

		myRobot.TankDrive(stickLeft, stickRight); // drive with tank style
		Wait(0.005); // wait for a motor update time
	}
}

START_ROBOT_CLASS(RobotStrap);



