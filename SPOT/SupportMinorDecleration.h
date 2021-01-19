#pragma once
#include "Registrar.h"
class SupportMinorDecleration : public Action
{
	SupportMinorDecleration(Registrar*);
	bool Execute();
	~SupportMinorDecleration();
};

