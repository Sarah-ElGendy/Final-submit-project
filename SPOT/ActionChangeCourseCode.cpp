#include "ActionChangeCourseCode.h"
#include "Actions\ActionAddCourse.h"
#include "Registrar.h"

ActionChangeCourseCode::ActionChangeCourseCode(Registrar* p) :Action(p)
{
}

bool ActionChangeCourseCode::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("press on the course you want to change its code"); //it takes the action of the click..
	int x_point, y_point;  //variables to carry the XY points...
	if (actData.actType == DRAW_AREA) {  //get coord where user clicked...
		x_point = actData.x;
		y_point = actData.y; 
		sem semesters = pGUI->getYEARandSEM(x_point, y_point); //detect the semester and year
		StudyPlan* pS = pReg->getStudyPlay();   //this function returns a pointer on study plan...
		
		pS->DetectCourse(x_point, y_point, semesters.year, semesters.s); //detect course position
		pS->DeleteCourse(x_point, y_point, semesters.year, semesters.s);//delete the selected course
		//from here add course
		pGUI->PrintMsg("Enter the new course Code(e.g. CIE202)");
		Course_Code code = pGUI->GetSrting();
		CourseInfo* cinfo;   //pointer to title,code,prereq,...
		cinfo = pReg->getcourseinfo(code);   //check if course is found in course catalog
		
		graphicsInfo gInfo{ x_point, y_point }; //draw course in the selected area of the older course
		string Title = "Test101";
		int crd = cinfo->Credits;
		Course* pC = new Course(code, Title, crd);
		pC->setGfxInfo(gInfo);
		StudyPlan* pointerS = pReg->getStudyPlay();
		pS->AddCourse(pC, semesters.year, semesters.s);
	}
	return true;
}

ActionChangeCourseCode::~ActionChangeCourseCode()
{
}
