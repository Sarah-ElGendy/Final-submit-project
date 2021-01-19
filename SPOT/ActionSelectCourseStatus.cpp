#include "ActionSelectCourseStatus.h"
#include "ActionDisplayStudentLevel.h"
#include "Registrar.h"
#include <iostream>
#include <list>
using namespace std;
ActionSelectCourseStatus::ActionSelectCourseStatus(Registrar* p) :Action(p) {
	
}

//int* ActionSelectCourseStatus::getLevelCred() {
//	return &LevelCred;
//}

bool ActionSelectCourseStatus::Execute() {
	GUI* pGUI = pReg->getGUI();
	int static LevelCred = 0;
	ActionData actData = pGUI->GetUserAction("press on the course you want to select its status: ");
	int x, y; 
	
	if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
	{
		//get coord where user clicked
		x = actData.x;
		y = actData.y;
		StudyPlan* pS = pReg->getStudyPlay();
		int yearof_course = pS->setYearSem(x);
		SEMESTER SEM = pS->Sem(x);
		Course* PointerCourse = pS->DetectCourse(x, y, yearof_course, SEM);  //detect position of the course selected
		

		ActionData actData = pGUI->GetUserAction("select course statues: Done, in progress ,pending: ");
		string selection =pGUI ->GetSrting();
		int CredC = PointerCourse->getCredits();
		if (selection == "Done" || selection == "done" || selection == "DONE") {
			int Funselection = pReg->SelectCourseStatus(CredC);
            Course_Code CODE = PointerCourse->getCode();
			pReg->FillDoneCoursesFun(CODE);
		}
		else {
			int Funselection = pReg->SelectCourseStatus(0);
		}
		
		pGUI->PrintMsg("The course has selected sucssesfully ..press enter to continue");
		Course_Code selectSucss = pGUI->GetSrting();
		
	}
	return true;
}

ActionSelectCourseStatus::~ActionSelectCourseStatus() {

}
