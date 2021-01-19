#include "ActionReorderCourses.h"
#include "Actions\Action.h"
#include "ActionDeleteCourse.h"
#include "Registrar.h"
#include <string>

ActionReorderCourses::ActionReorderCourses(Registrar* p) :Action(p)
{
}

bool ActionReorderCourses::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Press on the course you want to re-order");
	int x_point, y_point,xpoint,ypoint;
	if (actData.actType == DRAW_AREA) {
		//get coord where user clicked
		x_point = actData.x;
		y_point = actData.y;
		StudyPlan* pS = pReg->getStudyPlay();
		int yearcourse = pS->setYearSem(x_point);
		SEMESTER sems = pS->Sem(x_point);
		Course* PointerOnCourse = pS->DetectCourse(x_point, y_point, yearcourse, sems);
		
		if (PointerOnCourse != nullptr) {
			ActionData actData2 = pGUI->GetUserAction("Press on area you want to move to");
			if (actData2.actType == DRAW_AREA) {
				//get coord where user clicked
				xpoint = actData2.x;
				ypoint = actData2.y;
				
				int yearof_course = pS->setYearSem(xpoint);
				SEMESTER SEM = pS->Sem(xpoint);
				Course_Code code = PointerOnCourse->getCode();
				int crd = PointerOnCourse->getCredits();
				string Title = PointerOnCourse->getTitle();
				//int crd = 0;
				pS->DeleteCourse(x_point, y_point, yearcourse, sems);
				graphicsInfo gInfo{ xpoint, xpoint };
				Course* pCOURSE = new Course(code, Title, crd);
				pCOURSE->setGfxInfo(gInfo);
				pS->AddCourse(pCOURSE, yearof_course, SEM);
			}
		}
		else {
			pGUI->PrintMsg("clicked on empty area.. press enter to continue");
			Course_Code code = pGUI->GetSrting();
		}
		
	}
	
	return true;
}
ActionReorderCourses::~ActionReorderCourses()
{
}
