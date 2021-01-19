#pragma once
#include "Actions\Action.h"
class DisplayCourseInfo : public Action
{
public:
	DisplayCourseInfo(Registrar*);
	bool virtual Execute();
	virtual ~DisplayCourseInfo();
};

