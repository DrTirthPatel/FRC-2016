/*
 * ExampleSubsystem.h
 *
 *  Created on: Feb 16, 2016
 *      Author: Tirth Patel & Pranav Kandarpa
 */

#ifndef SRC_EXAMPLESUBSYSTEM_H_
#define SRC_EXAMPLESUBSYSTEM_H_

#include "Commands/Subsystem.h"
#include "WPILib.h"

class ExampleSubsystem: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	ExampleSubsystem();
	void InitDefaultCommand();
};

#endif /* SRC_EXAMPLESUBSYSTEM_H_ */
