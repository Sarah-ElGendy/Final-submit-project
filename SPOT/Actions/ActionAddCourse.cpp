#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include "../GUI/GUI.h"
#include <iostream>
#include <fstream>
enum ChangeColor {
	ChangeColordefault,
	ChangeColorModerate,
	ChangeColorCritical
};
ActionAddCourse::ActionAddCourse(Registrar* p) :Action(p)
{
}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
	Course_Code code = pGUI->GetSrting();

	CourseInfo* cinfo;   //pointer to title,code,prereq,...
	cinfo = pReg->getcourseinfo(code);   //check if course is found in course catalog

	if (cinfo == NULL) {
		pGUI->PrintMsg("course is not found..press enter to contiue");
		Course_Code code = pGUI->GetSrting();
	}
	else {
		ActionData actData = pGUI->GetUserAction("Select a year to add coures to: ");

		int x, y;
		if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
		{
			//get coord where user clicked
			x = actData.x;
			y = actData.y;



			graphicsInfo gInfo{ x, y };


			string Title = "Test101";
			int crd = cinfo->Credits;
			//int crd = 0;
			Course* pC = new Course(code, Title, crd);
			pC->setGfxInfo(gInfo);


			//sem syearsem; // struct include the year and the semesters
			StudyPlan* pS = pReg->getStudyPlay();
			int yearof_course = pS->setYearSem(x);
			SEMESTER SEM = pS->Sem(x);

			Course* poC = pReg->getStudyPlay()->CheckMaxMini(x, y, yearof_course, SEM);
			//Course* poPreq = pReg->getStudyPlay()->CheckPreq(x, y, yearof_course, SEM);
			ChangeColor CB;
			if (poC != nullptr) {
				ActionData actData = pGUI->GetUserAction("error..moderate ");
				CB = ChangeColorModerate;
			}
			Course_Code* poPreq = pReg->CheckDone(code);
			if (poPreq != nullptr) {
				ActionData actData = pGUI->GetUserAction("error..preq ");
				//CB = ChangeColorCritical;
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "Critical issue, you should check the prerequisites of this course " + code + "\n";
			}
			Course_Code* poCoreq = pReg->checkcore(code, SEM, yearof_course);
			if (poCoreq != nullptr) {
				ActionData actData = pGUI->GetUserAction("error..Coreq..Critical Issue");
				//CB = ChangeColorCritical;
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "Critical issue, you should check the Corequisites of this course " + code + "\n";
			}
			else {
				CB = ChangeColordefault;
			}
			
			pS->AddCourse(pC, yearof_course, SEM);
		}
		//TODO:


		return true;

	}



}


ActionAddCourse::~ActionAddCourse()
{
}
