#include "WPILib.h"

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

		giantRobot(),

		stick_left(0),
		stick_right(1),
		gamepad(2),

		arm_left(11),
		arm_right(10),

		top_limit(),
		bottom_limit(),

		autoLoopCounter(0)
{
		giantRobot.SetExpiration(0.1);
}

	void printStatus()
	{
		// Get an instance of the driver station to use its API
		DriverStation* ds = DriverStation::GetInstance();

		// Get important variable data
		float voltage = ds -> GetBatteryVoltage();

		// Print the data (voltage)
		printf("=======STATUS=======/n");
		printf("Battery Voltage: %f/n", voltage);
	}


	/*
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


	/*
	 * Runs the motors with tank steering
	 */
	void OperatorControl()
	{
		giantRobot.SetSafetyEnabled(true); // Set the safety

		// Establish limit switches
		DigitalInput *toplim = new DigitalInput(TOP_LIMIT);
		DigitalInput *botlim = new DigitalInput(BOTTOM_LIMIT);

		// Infinite loop
		while (IsOperatorControl() && IsEnabled())
		{
			while(1==1){
				giantRobot.TankDrive(stick_left, stick_right); //tank drive using left and right joysticks

				//Reverse all motors (they will drive backwards without this part)

				giantRobot.SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
				giantRobot.SetInvertedMotor(RobotDrive::kRearRightMotor, true);
				giantRobot.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
				giantRobot.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);

				// Move the arm based on buttons
				bool launchValue = stick.GetRawButton(1);
				bool rewindValue = stick.GetRawButton(2);

				// Determine the speed to throw the arm at
				float speed = (stick.GetThrottle() - (-1)) / 2;

				if(launchValue /* && !(toplim -> Get()) */)
						// make arm launch forwards
						arm -> Set(1 * speed);

				else if (rewindValue /* && !(botlim -> Get()) */)
					// make the arm launch backwards
					arm -> Set(-1 * speed);

				else
					arm -> Set(0);

				/* Prints out the battery voltage when button 11
				 * is pressed on the right stick.
				 */

				if(stick_right.GetRawButton(11)){
					this->printStatus();
				}
			}

			Wait(0.005);
		}
	}

	/*
	 * Runs during test mode
	 */
	void Test()
	{
	}
	}
};

START_ROBOT_CLASS(Robot);
