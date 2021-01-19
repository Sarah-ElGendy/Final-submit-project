#include "StudyPlan.h"



StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added
	for (int i = 0; i < 5; i++)
		plan.push_back(new AcademicYear);
}

//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 

	plan[year - 1]->AddCourse(pC, sem);
	
	return true;
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
		plan[i]->DrawMe(pGUI);
}
//delete course
bool StudyPlan::DeleteCourse(int x_point,int y_point, int years, SEMESTER SEMs) {
	//int* point = nullptr;
	//for (int i = 0; i <= 4; i++) {
		return plan[years-1]->actiondeletecourse(x_point, y_point, SEMs);  //plan is list of academic years,
		/*if (point != nullptr) {
			return true;
			break;
		}*/
	//}
	return true;
}

Course* StudyPlan::DetectCourse(int x_point, int y_point, int year, SEMESTER sem) {
	Course* pointPointer = nullptr;
	pointPointer = plan[year-1]->DetectPositionOfCourse(x_point, y_point, sem);
	if (pointPointer != nullptr) {
		return pointPointer;
	}
	else
	{
		return pointPointer;
	}
	
}
//check if the courses in the minor vector is found in the study plan or not (year courses)
//Course* StudyPlan::CheckMinorCourses(vector <Course_Code>MinorCourses) {
//	Course* pointerToMinor = nullptr;
//	for (int i = 0; i < 5; i++) {
//		pointerToMinor = plan[i]->CheckMinorInSP(MinorCourses);
//	}
//}

Course* StudyPlan::CheckMaxMini(int x, int y, int year, SEMESTER sem) {
	Course* pointerc= nullptr;
	pointerc = plan[year - 1]->CheckCreditsMaxMin(x, y, sem);

	return pointerc;
}
//bool StudyPlan::FillDoneCoursesFun(Course_Code code) {
//	MinorCourses.push_back(code);
//	return true;
//}
//fill vector of minor courses
bool StudyPlan::FillMinorCourses(Course_Code code) {
    MinorCourses.push_back(code);
	return true;
}

int StudyPlan::setYearSem(int x) {
	int year;
	if (x > 0 && x < 270) { //year
			year = 1;
			return year;
	}
	if (x>270 && x < 540) {
		year = 2;
		return year;
	}
	if (x > 540 && x < 810) {
		year = 3;
		return year;
	}
	if (x > 810 && x <1080 ) {
		year = 4;
		return year;
	}
	if (x > 1080 && x <1350) {
		year = 5;
		return year;
	}
}
SEMESTER StudyPlan::Sem(int x) {
	SEMESTER SS;
	if (x > 0 && x < 90) { //sem
		SS = FALL;
		return SS;
	}
	if (x > 90 && x < 180) {
		SS = SPRING;
		return SS;
	}
	if (x > 180 && x < 270) {
		SS = SUMMER;
		return SS;
	}
	if (x > 270 && x < 360) {
		SS = FALL;
		return SS;
	}
	if (x > 360 && x < 450) {
		SS = SPRING;
		return SS;
	}
	if (x > 450 && x < 540) {
		SS = SUMMER;
		return SS;
	}
	if (x > 540 && x < 630) {
		SS = FALL;
		return SS;
	}
	if (x > 630 && x < 720) {
		SS = SPRING;
		return SS;
	}
	if (x > 720 && x < 810) {
		SS = SUMMER;
		return SS;
	}
	if (x > 810 && x < 900) {
		SS = FALL;
		return SS;
	}
	if (x > 900 && x < 990) {
		SS = SPRING;
		return SS;
	}
	if (x > 990 && x < 1080) {
		SS = SUMMER;
		return SS;
	}
	if (x > 1080 && x <1170) {
		SS = FALL;
		return SS;
	}
	if (x > 1170 && x < 1260) {
		SS = SPRING;
		return SS;
	}
	if (x > 1260 && x < 1350) {
		SS = SUMMER;
		return SS;
	}

}
//check coreq
Course_Code* StudyPlan::coreqyear(Course_Code code, SEMESTER sem, int year) {
	Course_Code* pointerCOREQ = nullptr;
	pointerCOREQ = plan[year - 1]->CheckCoreq(code, sem);
	return pointerCOREQ;
}

StudyPlan::~StudyPlan()
{
}
