#pragma once
#include "Registrar.h"
class ActionSelectCourseStatus : public Action
{
	
public:
	ActionSelectCourseStatus(Registrar*);
	bool Execute();
	virtual ~ActionSelectCourseStatus();
};

