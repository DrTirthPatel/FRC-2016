/*
 * CommandBase.h
 *
 *
 *  Created on: Feb 16, 2016
 *      Author: Tirth Patel & Pranav Kandarpa
 */

#ifndef SRC_COMMANDBASE_H_
#define SRC_COMMANDBASE_H_

#include <string>
#include "Commands/Command.h"
#include "Subsystems/ExampleSubsystem.h"
#include "OI.h"
#include "WPILib.h"

/**
 * The base for all commands. ALl atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	    CommandBase(char const *name);
	    CommandBase();
	    static void init();
	    // Create a single static instance of all of your subsystems
	    static ExampleSubsystem *examplesubsystem;
	    static OI *oi;
};

#endif /* SRC_COMMANDBASE_H_ */
