/*
 * ExampleCommand.h
 *
 *  Created on: Feb 16, 2016
 *      Author: Tirth Patel & Pranav Kandarpa
 */

#ifndef SRC_EXAMPLECOMMAND_H_
#define SRC_EXAMPLECOMMAND_H_

#include "../CommandBase.h"
#include "WPILib.h"

class ExampleCommand: public CommandBase
{
public:
	ExampleCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif /* SRC_EXAMPLECOMMAND_H_ */
