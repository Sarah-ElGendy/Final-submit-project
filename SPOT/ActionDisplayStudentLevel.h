#pragma once
#include "Registrar.h"
#include "ActionSelectCourseStatus.h"
class ActionDisplayStudentLevel : public Action
{
public:
	ActionDisplayStudentLevel(Registrar*);
	bool Execute();
	virtual ~ActionDisplayStudentLevel();
};

