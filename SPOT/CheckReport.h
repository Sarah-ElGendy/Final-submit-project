#pragma once
#include "Registrar.h"
class CheckReport : public Action
{
public:
	CheckReport(Registrar*);
	bool Execute();
	virtual ~CheckReport();
};

