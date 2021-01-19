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
		if (PointerCourse != nullptr) {
			ActionData actData = pGUI->GetUserAction("select course statues: Done, in progress ,pending: ");
			string selection = pGUI->GetSrting();
			int CredC = PointerCourse->getCredits();
			if (selection == "Done" || selection == "done" || selection == "DONE") {
				int Funselection = pReg->SelectCourseStatus(CredC);
				Course_Code CODE = PointerCourse->getCode();
				pReg->FillDoneCoursesFun(CODE);
				pGUI->PrintMsg("The course has selected as done sucssesfully ..press enter to continue");
				Course_Code selectSucss = pGUI->GetSrting();
			}
			else if (selection == "pending" ) {
			
				pGUI->PrintMsg("The course has selected as pending sucssesfully ..press enter to continue");
				Course_Code selectSucss = pGUI->GetSrting();
				
			}
			else if (selection == "in progress") {
				
				pGUI->PrintMsg("The course has selected as in progress sucssesfully ..press enter to continue");
				Course_Code selectSucss = pGUI->GetSrting();
				
			}
			else {
				
				pGUI->PrintMsg("invalid input ..press enter to continue");
				Course_Code selectSucss = pGUI->GetSrting();
				
			}

			
			return true;
		}
		else {
			pGUI->PrintMsg("empty area ..press enter to continue");
			Course_Code selectSucss = pGUI->GetSrting();
			return false;
		}
		
	}
	
		
}

ActionSelectCourseStatus::~ActionSelectCourseStatus() {

}
