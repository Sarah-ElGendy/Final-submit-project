#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include "Courses\Course.h"
#include "Actions\Action.h"
#include <iostream>

ActionDeleteCourse::ActionDeleteCourse(Registrar* p) : Action(p)
{
}
bool ActionDeleteCourse::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Press on the course you want to Delete");
	int x_point, y_point;
	if (actData.actType == DRAW_AREA) {   //get coord where user clicked
		x_point = actData.x;
		y_point = actData.y; 
		
		StudyPlan* pS = pReg->getStudyPlay();
		int yearof_course = pS->setYearSem(x_point);
		SEMESTER SEMs= pS->Sem(x_point);
		pS->DeleteCourse(x_point, y_point, yearof_course, SEMs);
	}
	return true;
}
ActionDeleteCourse::~ActionDeleteCourse()
{
}
