/*
 * Robot.cpp
 *
 *
 *
 *  Created on: Feb 16, 2016
 *      Author: Tirth Patel & Pranav Kandarpa
 */
#include "WPILib.h"

void EnableCamera();

class Robot: public SampleRobot

{
	//Initialize all members

	RobotDrive giantRobot;
	Joystick stick_left;
	Joystick stick_right;
	Joystick gamepad;
	Talon arm_left;
	Talon arm_right;
	DigitalInput top_limit;
	DigitalInput bottom_limit;

	int *autoLoopCounter;

	Command *autonomousCommand;
	LiveWindow *lw;

public:
	Robot() :

		//Instantiate all items from above

		giantRobot(1,2,3,4),


		stick_left(0),
		stick_right(1),
		gamepad(2),

		arm_left(6),
		arm_right(5),

		top_limit(2),
		bottom_limit(3),

		autoLoopCounter(0)
{
		giantRobot.SetExpiration(0.1);

		EnableCamera();
}

	void printStatus()
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
		 * Drive left & right motors for 2 seconds then stop
		 */
	void Autonomous()
	{
		giantRobot.SetSafetyEnabled(false);
		while (IsAutonomous() && IsEnabled()) {
			giantRobot.Drive(-0.5, -0.5);   // drive forwards half speed
			Wait(2.0);                      // for 2 seconds
			giantRobot.Drive(0.0, 0.0);     // stop robot
		}
	}


	/**
		 * Runs the motors with tank steering and raises/lowers the box lift
		 */
	void OperatorControl()
	{
		giantRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			while(1==1){
				giantRobot.TankDrive(stick_left, stick_right); //tank drive using left and right joysticks

				//Reverse all motors (they will drive backwards without this part)

				giantRobot.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
				giantRobot.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
				giantRobot.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
				giantRobot.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);

				/*
				 * This loop controls the top limit switch.
				 * If pressed, the limit switch reverses the direction of the
				 * motors for 0.5 seconds to prevent the robot from falling
				 * due to excessive force.  It then stops the motors to allow
				 * the driver to regain control.
				 */

				if(top_limit.Get() == 0){
					arm_left.Set(0.1);
					arm_right.Set(0.1);
					Wait(0.5);
					arm_left.Set(0);
					arm_right.Set(0);
				}

				/*
				 * This loop controls the bottom limit switch.
				 * When pressed, the limit switch will stop the motors completely
				 * so that the winch does not reverse direction.
				 * The driver can regain control of the robot when ready.
				 */

				if(bottom_limit.Get() == 1){
					arm_left.Set(0);
					arm_right.Set(0);
					Wait(0.3);
					arm_left.Set(gamepad.GetRawAxis(5) / 2);
					arm_right.Set(gamepad.GetRawAxis(5) / 2);
				}

				/*
				 * The else statement here ensures that the driver
				 * can control the arm normally if neither limit switch
				 * is pressed.
				 * Motors will run at half speed.
				 */

				else{
					arm_left.Set(gamepad.GetRawAxis(5) / 2);
					arm_right.Set(gamepad.GetRawAxis(5) / 2);
				}

				/*
				 * Prints out the battery voltage when button 11
				 * is pressed on the right stick.
				 */

				if(stick_right.GetRawButton(11)){
					this->printStatus();
				}

			}

			Wait(0.005);				// wait for a motor update time

		}

	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}


	void EnableCamera(void)
	{
		if (CameraServer::GetInstance()->IsAutoCaptureStarted() == false)
		{
			CameraServer::GetInstance()->SetQuality(75);
			CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		}
	}

};

START_ROBOT_CLASS(Robot);

