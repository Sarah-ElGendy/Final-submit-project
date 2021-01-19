#include "SupportMinorDecleration.h"
#include "Registrar.h"
#include <iostream>
SupportMinorDecleration::SupportMinorDecleration(Registrar* p) :Action(p) {

}
bool SupportMinorDecleration::Execute() {
	GUI* pGUI = pReg->getGUI();
	for (int i = 0; i < 5; i++) {
		ActionData actData = pGUI->GetUserAction("Enter five courses you want to minor: Enter Course:  ");
		Course_Code  MinorCourseOne = pGUI->GetSrting();
		StudyPlan* PointerToStudyPlan = pReg->getStudyPlay();
		CourseInfo* CheckMinor = pReg->getcourseinfo(MinorCourseOne);
		if (CheckMinor != nullptr) {
			PointerToStudyPlan->FillMinorCourses(MinorCourseOne);    //function to push back the vector of courses
		}
	}
	return true;
}
SupportMinorDecleration::~SupportMinorDecleration() {
}
