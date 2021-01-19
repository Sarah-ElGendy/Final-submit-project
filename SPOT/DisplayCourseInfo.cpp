#include "DisplayCourseInfo.h"
#include "Registrar.h"
#include "Courses\Course.h"
#include<sstream>  
DisplayCourseInfo::DisplayCourseInfo(Registrar* p) :Action(p)
{
}
bool DisplayCourseInfo::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("press on course you want to display it's information");
	int x_point, y_point;
	if (actData.actType == DRAW_AREA) {
		//get coord where user clicked
		x_point = actData.x;
		y_point = actData.y;
		StudyPlan* pS = pReg->getStudyPlay();
		int yearof_course = pS->setYearSem(x_point);
		SEMESTER SEM = pS->Sem(x_point);
		Course* PointerOnFirstCourse = pS->DetectCourse(x_point, y_point, yearof_course, SEM);  //detect position of the course selected
		if (PointerOnFirstCourse != nullptr) {
			int creditsC = PointerOnFirstCourse->getCredits();
			stringstream ConvertToString;
			ConvertToString << creditsC;
			string NEWcredits;
			ConvertToString >> NEWcredits;
			Course_Code course = PointerOnFirstCourse->getCode();
			string title = PointerOnFirstCourse->getTitle();
			pGUI->PrintMsg("code: " + course + "  title: " + title + " Credits: " + NEWcredits+"  Press enter to continue...");
			Course_Code code = pGUI->GetSrting();
		}
		else {
			pGUI->PrintMsg("clicked on empty area.. press enter to continue");
			Course_Code code = pGUI->GetSrting();
		}
	}
	return true;
}
DisplayCourseInfo::~DisplayCourseInfo() {

}