#include "ActionCalculateGPA.h"
#include "Registrar.h"
#include <iostream>
#include <sstream>
ActionCalculateGPA::ActionCalculateGPA(Registrar* p) :Action(p) {

}
bool ActionCalculateGPA::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Enter number of courses to calculate the GPA: ");
	string get_num_of_courses = pGUI->GetSrting();
	int num_of_courses;
	istringstream(get_num_of_courses) >> num_of_courses;
	double result = 0, TotalCreditsOfCourses = 0, TotalResult = 0;
	for (int num = 0; num < num_of_courses; num++) {
		ActionData actData = pGUI->GetUserAction("press on course you want to calculate it's GPA: ");
		int x_point, y_point;
		if (actData.actType == DRAW_AREA) {
			//get coord where user clicked
			x_point = actData.x;
			y_point = actData.y;
			StudyPlan* pS = pReg->getStudyPlay();
			int yearof_course = pS->setYearSem(x_point);
			SEMESTER SEM = pS->Sem(x_point);
			Course* PointerOnCourse = pS->DetectCourse(x_point, y_point, yearof_course, SEM);  //detect position of the course selected
			//calc GPA 
			if (PointerOnCourse != nullptr) {
				int creditsOFcourse = PointerOnCourse->getCredits();
				pGUI->PrintMsg("Enter Grade of the course: ");
				string grades = pGUI->GetSrting();
				
				if (grades == "A" || grades == "a") {
					result = 4* creditsOFcourse;
				}
				else if (grades == "A-" || grades == "a-") {
					result = 3.7 * creditsOFcourse;
				}
				else if (grades == "B+" || grades == "b+") {
					result = 3.3 * creditsOFcourse;
				}
				else if (grades == "B" || grades == "b") {
					result = 3 * creditsOFcourse;
				}
				else if (grades == "B-" || grades == "b-") {
					result = 2.7 * creditsOFcourse;
				}
				else if (grades == "C+" || grades == "c+") {
					result = 2.3 * creditsOFcourse;
				}
				else if (grades == "C" || grades == "c") {
					result = 2 * creditsOFcourse;
				}
				else if (grades == "C-" || grades == "c-") {
					result = 1.7 * creditsOFcourse;
				}
				else if (grades == "D+" || grades == "d+") {
					result = 1.3 * creditsOFcourse;
				}
				else if (grades == "D" || grades == "d") {
					result = 1 * creditsOFcourse;
				}
				else if (grades == "D-" || grades == "d-") {
					result = 0.7 * creditsOFcourse;
				}
				else if (grades == "F" || grades == "f") {
					result = 0 * creditsOFcourse;
				}
				else {
					pGUI->PrintMsg("invalid input..press enter to continue");
					Course_Code invalidMsg = pGUI->GetSrting();
				}
				TotalCreditsOfCourses += creditsOFcourse;
				TotalResult += result;
			}
			else {
				pGUI->PrintMsg("Empty area... press enter to continue");
				Course_Code enter = pGUI->GetSrting();

			}
			
			
		}
		
	
	}
	
	double GPA = TotalResult / TotalCreditsOfCourses;
	if (GPA >=0 && GPA <= 4) {
		string StringGPA = to_string(GPA);
		pGUI->PrintMsg("Total GPA is: " + StringGPA + "  press enter to continue");
		Course_Code enter = pGUI->GetSrting();
	}
	
	return true;
}
ActionCalculateGPA::~ActionCalculateGPA() {

}
