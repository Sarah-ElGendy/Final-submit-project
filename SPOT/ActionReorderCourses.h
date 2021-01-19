#pragma once
#include "Actions\Action.h"
class ActionReorderCourses : public Action
{
public:
	ActionReorderCourses(Registrar*);
	bool Execute();
	virtual ~ActionReorderCourses();
};

