#pragma once
#include "Registrar.h"
class ActionAddNotes : public Action
{
public:
	ActionAddNotes(Registrar*);
	bool Execute();
	virtual ~ActionAddNotes();
};

