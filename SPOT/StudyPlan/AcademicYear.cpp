#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include "../Registrar.h"
#include "../Rules.h"
#include <vector>
#include <sstream> 
#include <list>
#include <fstream>
using namespace std;
AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	//TODO:
	//This function still needs many checks to be compelete
	YearCourses[sem].push_back(pC);
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}


void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	
	for (int sem = FALL; sem < SEM_CNT; sem++)
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{

			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
		}
}
//delete course
bool AcademicYear::actiondeletecourse(int x_point, int y_point, SEMESTER SEMs) {
	//int* point = nullptr;
		for (ITERATOR = YearCourses[SEMs].begin(); ITERATOR != YearCourses[SEMs].end(); ITERATOR++) {
			Course* cpointer = *ITERATOR;   //cpointer it contains courses details
			graphicsInfo position = cpointer->getGfxInfo();   //function that detect the position of the rectangle course
				if (x_point>position.x && x_point<position.x+90 && y_point > position.y && y_point <position.y+40) {
							TotalCredits = TotalCredits - cpointer->getCredits();
							YearCourses[SEMs].erase(ITERATOR);  
							//it will delete the selected course...
							return true;
						
				}
				
		}
		return false;
}
//detect course position
Course* AcademicYear::DetectPositionOfCourse(int x_point, int y_point, SEMESTER sem) {
	for (iter = YearCourses[sem].begin(); iter != YearCourses[sem].end(); iter++) {
		Course* coursepointer = *iter;
		graphicsInfo pos = coursepointer->getGfxInfo();   //function that detect the position of the rectangle course
		if (x_point > pos.x && x_point<pos.x + 90 && y_point > pos.y && y_point < pos.y + 40) {
			return coursepointer;
		}

	}
	return nullptr;
}
//loop on YearCourses list to check if the minor courses are found
//bool AcademicYear::CheckMinorInSP(vector <Course_Code>MinorCourses) {
//	for (int i = 0; i < 3; i++) {
//		for (iter = YearCourses[i].begin(); iter != YearCourses[i].end(); iter++) {
//			Course* pCM = *iter;
//			for (int j = 0; j < MinorCourses.size(); j++) {
//				if (MinorCourses[j] == YearCourses[i]) {
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}
//check done courses in the course catalog
//bool AcademicYear::CheckDoneCORE(Course_Code code) {
//	/*CourseInfo coursedata; Course_Code c;*/
//	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
//		if (RegRules.CourseCatalog[i].Code == code) {
//			for (int n = 0; n < RegRules.CourseCatalog[i].PreReqList.size(); n++) {
//				for (int j = 0; j < DoneCourses.size(); j++) {
//					if (DoneCourses[j] == RegRules.CourseCatalog[i].PreReqList[n]) {
//						return true;
//					}
//
//
//				}
//			}
//		}
//
//	}
//	return false;
//}
//check coreq by looping on study plan
Course_Code* AcademicYear::CheckCoreq(Course_Code code, SEMESTER sem) {
	for (it = YearCourses[sem].begin(); it != YearCourses[sem].end(); it++) {
		Course* coursepointer = *it;
		if (coursepointer->getCode() == code) {
			return &code;
		}
	}
	return nullptr;
}

//check credits of each semester
Course* AcademicYear::CheckCreditsMaxMin(int x, int y, SEMESTER sem) {
	//int static semestercredits = 0;
	for (it = YearCourses[sem].begin(); it != YearCourses[sem].end(); it++) {
		Course* po = *it;
		graphicsInfo positionOfCourse = po->getGfxInfo();  //get x, y of course rectangle
		if (x > 0 && x < 90) { //sem
			int static Semester1 = 0;
			Semester1 += po->getCredits();
			if (Semester1 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at FALL year one \n";
				return po;
			}
			else {

				return nullptr;
			}
		}
		else if (x > 90 && x < 180) {
			int static Semester2 = 0;
			Semester2 += po->getCredits();
			if (Semester2 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at SPRING year one \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 180 && x < 270) {
			int static Semester3 = 0;
			Semester3 += po->getCredits();
			if (Semester3 > 6) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Summer year one \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 270 && x < 360) {
			int static Semester4 = 0;
			Semester4 += po->getCredits();
			if (Semester4 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at FALL year two \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 360 && x < 450) {
			int static Semester5 = 0;
			Semester5 += po->getCredits();
			if (Semester5 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Spring year two \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 450 && x < 540) {
			int static Semester6 = 0;
			Semester6 += po->getCredits();
			if (Semester6 > 6) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Summer year two \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 540 && x < 630) {
			int static Semester7 = 0;
			Semester7 += po->getCredits();
			if (Semester7 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at FALL year three \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 630 && x < 720) {
			int static Semester8 = 0;
			Semester8 += po->getCredits();
			if (Semester8 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Spring year three \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 720 && x < 810) {
			int static Semester9 = 0;
			Semester9 += po->getCredits();
			if (Semester9 > 6) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Summer year three \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 810 && x < 900) {
			int static Semester10 = 0;
			Semester10 += po->getCredits();
			if (Semester10 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at FALL year four \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 900 && x < 990) {
			int static Semester11 = 0;
			Semester11 += po->getCredits();
			if (Semester11 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Spring year four \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 990 && x < 1080) {
			int static Semester12 = 0;
			Semester12 += po->getCredits();
			if (Semester12 > 6) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Summer year four \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 1080 && x < 1170) {
			int static Semester13 = 0;
			Semester13 += po->getCredits();
			if (Semester13 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at FALL year five \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 1170 && x < 1260) {
			int static Semester14 = 0;
			Semester14 += po->getCredits();
			if (Semester14 > 15) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Spring year five \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
		else if (x > 1260 && x < 1350) {
			int static Semester15 = 0;
			Semester15 += po->getCredits();
			if (Semester15 > 6) {
				ofstream myfile;
				myfile.open("report.txt", ios::app);
				myfile << "you need an overload petition at Summer year five \n";
				return po;
			}
			else {
				return nullptr;
			}
		}
	}
	
}
//check preq
//Course* AcademicYear::Check_Preq(Course_Code code) {
//	
//	for (int j = 0; j < 3; j++) {
//		for (iter = YearCourses[j].begin(); iter != YearCourses[j].end(); iter++) {
//			
//		}
//	}
//}
