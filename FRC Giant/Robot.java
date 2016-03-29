// Pack this nonsense
package org.usfirst.frc.team5142.robot;

// Import the nonsense
import edu.wpi.first.wpilibj.DriverStation;
//import edu.wpi.first.wpilibj.DriverStationLCD;
//import edu.wpi.first.wpilibj.DriverStationLCD.Line;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SampleRobot;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.Victor;

/**
 * This is a demo program showing the use of the RobotDrive class, specifically it 
 * contains the code necessary to operate a robot with tank drive.
 *
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SampleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */

public class Robot extends SampleRobot {
	private static RobotDrive drivetrain;
	private static Joystick leftStick;
	private static Joystick rightStick;
	private static Talon arm1;
	private static Talon arm2;
	private static Talon arm3;
	private static Victor leftFront;
	private static Victor leftRear;
	private static Victor rightFront;
	private static Victor rightRear;
	private static Victor rightSide3;
	
    Victor leftSide1, leftSide2, rightSide1, rightSide2;	
    Joystick leftStick1;  // set to ID 1 in DriverStation
    Joystick rightStick1; // set to ID 2 in DriverStation
    
  /* Set up all the constant values */
    
    // Drive system motor ports
    private final int FRONT_LEFT_MOTOR_PORT = 2;
    private final int FRONT_RIGHT_MOTOR_PORT = 0;
    private final int REAR_LEFT_MOTOR_PORT = 3;
    private final int REAR_RIGHT_MOTOR_PORT = 1;
    
    private final int LEFT_JOYSTICK_PORT = 1;
    private final int RIGHT_JOYSTICK_PORT = 2;
    
    // Arm motor ports
    private final int ARM1_MOTOR_PORT = 0;
    private final int ARM2_MOTOR_PORT = 7;
    private final int ARM3_MOTOR_PORT = 5;
    private final int ARM4_MOTOR_PORT = 6;
	private double voltage;
    
    public Robot() {
    	
    	drivetrain = new RobotDrive (FRONT_LEFT_MOTOR_PORT, REAR_LEFT_MOTOR_PORT, FRONT_RIGHT_MOTOR_PORT, REAR_RIGHT_MOTOR_PORT);
        leftStick = new Joystick(0);
        rightStick = new Joystick(1);
        leftSide1 = new Victor(2);
        leftSide2 = new Victor(3);
        rightSide1 = new Victor(0);
        rightSide2 = new Victor(1);
        setRightSide3(new Victor(6));
        arm1 = new Talon(0);
        arm2 = new Talon(7);
        setArm3(new Talon(5));
    }

    public void autonomous() {
    	drivetrain.setSafetyEnabled(false);
    	drivetrain.drive(-1, 0.0); // drive 50% forward with 0% turn
    	Timer.delay(2); // wait for a bit
    	drivetrain.drive(0.0, 0.0); // drive 0% forward, 0% turn (stop)
    }
    
    /**
     * Runs the motors with tank steering.
     */
    
    public void operatorControl() {
        while (isOperatorControl() && isEnabled()) {
        	double leftSpeed = leftStick.getRawAxis(1);
        	double rightSpeed = rightStick.getRawAxis(1);
        	leftSide1.set(leftSpeed);
        	leftSide2.set(leftSpeed);
        	rightSide2.set(rightSpeed);
        	rightSide2.set(rightSpeed);
        	
        	  // set up the controls for throwing the arms
            boolean fire = leftStick.getRawButton(1);
            boolean reload = leftStick.getRawButton(4);
            
            if(fire)
            {
                // open the latch
                
                arm1.set(1);
                arm2.set(1);
            }
            if(reload)
            {
                arm1.set(-1);
                arm2.set(-1);
            }
            else
            {
                arm1.set(0);
                arm2.set(0);
            }
            
            // arcade drive
        	drivetrain.tankDrive(rightStick, leftStick);
        	
            Timer.delay(0.005);		// wait for a motor update time
        }
    }

public void printStaus() {
    // Get an instance of the driver station to use its API
	DriverStation ds = DriverStation.getInstance();
     
    // Get driver station LCD
    //DriverStationLCD dslcd = DriverStationLCD.getInstance();
    
	setVoltage(ds.getBatteryVoltage());

    // Print the voltage
   // dslcd.println(DriverStationLCD.Line.kUser6, 1, "Battery Voltage: " + String.valueOf(voltage));
    //dslcd.updateLCD();
}

/* Print a message to the user message center */
//public void printStuff(String msg, Line type)
{
    //DriverStationLCD dslcd = DriverStationLCD.getInstance();
    //dslcd.println(type, 1, msg);
    //dslcd.updateLCD();
}

/* Test function */
public void test()
{
	
}

public int getARM2_MOTOR_PORT() {
	return ARM2_MOTOR_PORT;
}

public int getARM1_MOTOR_PORT() {
	return ARM1_MOTOR_PORT;
}

public int getARM3_MOTOR_PORT() {
	return ARM3_MOTOR_PORT;
}

public int getARM4_MOTOR_PORT() {
	return ARM4_MOTOR_PORT;
}

public double getVoltage() {
	return voltage;
}

public void setVoltage(double voltage) {
	this.voltage = voltage;
}

public int getLEFT_JOYSTICK_PORT() {
	return LEFT_JOYSTICK_PORT;
}

public int getRIGHT_JOYSTICK_PORT() {
	return RIGHT_JOYSTICK_PORT;
}

public static Talon getArm3() {
	return arm3;
}

public static void setArm3(Talon arm3) {
	Robot.arm3 = arm3;
}

public static Victor getLeftFront() {
	return leftFront;
}

public static void setLeftFront(Victor leftFront) {
	Robot.leftFront = leftFront;
}

public static Victor getLeftRear() {
	return leftRear;
}

public static void setLeftRear(Victor leftRear) {
	Robot.leftRear = leftRear;
}

public static Victor getRightFront() {
	return rightFront;
}

public static void setRightFront(Victor rightFront) {
	Robot.rightFront = rightFront;
}

public static Victor getRightRear() {
	return rightRear;
}

public static void setRightRear(Victor rightRear) {
	Robot.rightRear = rightRear;
}

public static Victor getRightSide3() {
	return rightSide3;
}

public static void setRightSide3(Victor rightSide3) {
	Robot.rightSide3 = rightSide3;
}
}
