#include "Registrar.h"
#include "Actions/ActionAddCourse.h"
#include "ImportStudyPlan.h"
#include "Registrar.h"
#include <fstream>
#include<sstream>
#include<string>
#include <vector>
#include "Rules.h"
#include "StudyPlan\StudyPlan.h"
#include "StudyPlan\AcademicYear.h"
#include "ActionDeleteCourse.h"
#include "ActionAddNotes.h"
#include "ActionChangeCourseCode.h" 
#include <iostream>
#include "ActionReorderCourses.h"
#include "DisplayCourseInfo.h"
#include "ActionCalculateGPA.h"
#include "ActionSelectCourseStatus.h"
#include "ActionDisplayStudentLevel.h"
#include "CheckReport.h"
#include <list>
using namespace std;
Registrar::Registrar()
{
	pGUI = new GUI;	//create interface object
	pSPlan = new StudyPlan;	//create a study plan.
	load(); //calling course catalog
	ImportRequirements();  //calling imort req
}

//returns a pointer to GUI
GUI* Registrar::getGUI() const
{
	return pGUI;
}

//returns the study plan
StudyPlan* Registrar::getStudyPlay() const
{
	return pSPlan;
}
//ActionSelectCourseStatus* Registrar::getp() {
//	return p;
//}

Action* Registrar::CreateRequiredAction() 
{	
	ActionData actData = pGUI->GetUserAction("Pick and action...");
	Action* RequiredAction = nullptr;

	switch (actData.actType)
	{
	case ADD_CRS:	//add_course action
		RequiredAction = new ActionAddCourse(this);
		break;
	case LOAD:   //load study plan
		RequiredAction = new ImportStudyPlan(this);
		break;
	case DELETE_COURSE:
		RequiredAction = new ActionDeleteCourse(this);
		break;
	case NOTES:
		RequiredAction = new ActionAddNotes(this);
		break;
	case CHANGE_COURSE_CODE:
		RequiredAction = new ActionChangeCourseCode(this);
		break;
	case REORDER_COURSES:
		RequiredAction = new ActionReorderCourses(this);
		break;
	case DISPLAY_COURSE_INFO:
		RequiredAction = new DisplayCourseInfo(this);
		break;
	case CALCULATE_GPA:
		RequiredAction = new ActionCalculateGPA(this);
		break;
	case SELECT_COURSE_STATUS:
		RequiredAction = new ActionSelectCourseStatus(this);
		break;
	case REPORT:
		RequiredAction = new CheckReport(this);
		break;
	case Display_Student_Level:
		RequiredAction = new ActionDisplayStudentLevel(this);
		break;
	//TODO: Add case for each action
	
	/*case EXIT:
		break;
		*/
	}
	return RequiredAction;
}

//Executes the action, Releases its memory, and return true if done, false if cancelled
bool Registrar::ExecuteAction(Action* pAct)
{
	bool done = pAct->Execute();
	delete pAct;	//free memory of that action object (either action is exec or cancelled)
	return done;
}

void Registrar::Run()
{
	while (true)
	{
		//update interface here as CMU Lib doesn't refresh itself
		//when window is minimized then restored
		UpdateInterface();

		Action* pAct = CreateRequiredAction();
		if (pAct)	//if user doesn't cancel
		{
			if (ExecuteAction(pAct))	//if action is not cancelled
				UpdateInterface();
		}
	}
}


void Registrar::UpdateInterface()
{
	pGUI->UpdateInterface();	//update interface items
	pSPlan->DrawMe(pGUI);		//make study plan draw itself
}

bool Registrar::load() //function to import course catalog
{
	fstream file;
	file.open("FILES\\course_catalog.txt", ios::in);
	//ifstream coursecatalog("course catalog.txt");
	// if (file.fail()) { cout << "open file operation is failed" << endl; }
	
	string tempcrd;
	string data;
	string tempcoreq;  // one course of corequisites
	string temppreq;   // one course of prerequisites
	string Coreq_part;
	string Prereq_part;
	if (file.fail()) {
		return false;
	}
	else
	{
		while (getline(file, data)) {   //to loop the data in lines of the txt file
			CourseInfo Info;
			stringstream ss(data);
			getline(ss, Info.Code, ',');
			getline(ss, Info.Title, ',');
			getline(ss, tempcrd, ',');
			Info.Credits = stoi(tempcrd); // function to store an integer as a string
			getline(ss, Coreq_part, ':');   //to reed corequisites part
			if (Coreq_part == "Coreq")
			{
				string courses;
				getline(ss, courses, ',');
				while (true) {
					auto end = courses.find("And");
					string coursecode = courses.substr(0, end - 1);
					//cout << coursecode << endl;
					Info.CoReqList.push_back(coursecode);
					courses = courses.substr(end + 4, courses.length());
					if (end == -1) {
						break;
					}
				}

			}
			getline(ss, Prereq_part, ':');   //to reed prequisites part
			if (Prereq_part == "Prereq")
			{
				string preq = ss.str();
				getline(ss, preq, ',');
				while (true) {
					auto end = preq.find("And");
					string coursecode = preq.substr(0, end - 1);
					//cout << coursecode << endl;
					Info.PreReqList.push_back(coursecode);
					preq = preq.substr(end + 4, preq.length());
					//cout << coursecode << "  here  " << preq << endl;
					if (end == -1) {
						break;
					}
				}

			}
			else {
				string preqc;
				if (getline(ss, preqc, ':'))
				{
					while (true) {
						auto end = preqc.find("And");
						string coursecode = preqc.substr(0, end - 1);
						Info.PreReqList.push_back(coursecode);
						preqc = preqc.substr(end + 4, preqc.length());
						if (end == -1) {
							break;
						}
					}
				}
			}
			RegRules.CourseCatalog.push_back(Info);  // to shift course info into course catalog vector
		}
		return true;
	}
}

/*CourseInfo* Registrar::getcourseinfo(Course_Code code) {

	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
		if (RegRules.CourseCatalog[i].Code == code) {
			return &RegRules.CourseCatalog[i];
		}

	}
	for (int j = 0; j < RegRules.CourseCatalog.size(); j++) {
		if (RegRules.CourseCatalog[j].Code != code) {
			return nullptr;
			
		}
	}
}*/

CourseInfo* Registrar::getcourseinfo(Course_Code code) {
	int c = 0, num;
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
		if (RegRules.CourseCatalog[i].Code == code) {
			c += 1;
			num = i;
			break;
		}
		if (RegRules.CourseCatalog[i].Code != code) {
			c += 0;
		}
	}
	if (c > 0) {
		return &RegRules.CourseCatalog[num];
	}
	else if (c == 0){
		return nullptr;
	}
}
int Registrar::SelectCourseStatus(int cred)
{
	int static LevelCred=0;
	LevelCred += cred;
	return LevelCred;
}
//check courses of the minor

//take done courses from select course status class

void Registrar::ImportRequirements()
{
	fstream file;
	file.open("FILES\\NANENG-Requirements.txt", ios::in);

	string data;
	string temptotalcr;
	string tempUniComCr;
	string tempUniElecCr;

	// first requrement

	getline(file, temptotalcr);
	RegRules.totalcr = stoi(temptotalcr);

	// 2 requirement

	getline(file, data);

	stringstream sss(data);
	getline(sss, tempUniComCr, ',');
	RegRules.UniComCr = stoi(tempUniComCr);
	getline(sss, tempUniElecCr);
	RegRules.UniElecCr = stoi(tempUniElecCr);


	// 3 requirement

	string tempTrackCr;
	getline(file, tempTrackCr);
	RegRules.TrackComCr = stoi(tempTrackCr);

	// 4 requirement

	string tempMajorComCr;
	string tempMajorElecCr;



	getline(file, data);
	stringstream ssss(data);
	getline(ssss, tempMajorComCr, ',');
	RegRules.MajorComCr = stoi(tempMajorComCr);
	getline(ssss, tempMajorElecCr);
	RegRules.MajorEleCr = stoi(tempMajorElecCr);
	//cout << Rule.MajorComCr << endl;


// 5 requirement

	string tempNumOfCon;
	getline(file, tempNumOfCon);
	RegRules.NumOfCon = stoi(tempNumOfCon);


	string tempMajorConcen1ComCr;
	string tempMajorConcen1ElecCr;
	string tempMajorConcen2ComCr;
	string tempMajorConcen2ElecCr;
	string tempMajorConcen3ComCr;
	string tempMajorConcen3ElecCr;

	// 6 requirement
	getline(file, data);
	if (stoi(tempNumOfCon) != 0)
	{

		stringstream nn(data);
		getline(nn, tempMajorConcen1ComCr, ',');
		RegRules.MajorConcen1ComCr = stoi(tempMajorConcen1ComCr);
		getline(nn, tempMajorConcen1ElecCr, ',');
		RegRules.MajorConcen1ElecCr = stoi(tempMajorConcen1ElecCr);

		getline(nn, tempMajorConcen2ComCr, ',');
		RegRules.MajorConcen2ComCr = stoi(tempMajorConcen2ComCr);
		getline(nn, tempMajorConcen2ElecCr, ',');
		RegRules.MajorConcen2ElecCr = stoi(tempMajorConcen2ElecCr);

		getline(nn, tempMajorConcen3ComCr, ',');
		RegRules.MajorConcen3ComCr = stoi(tempMajorConcen3ComCr);
		getline(nn, tempMajorConcen3ElecCr, ',');
		RegRules.MajorConcen3ElecCr = stoi(tempMajorConcen3ElecCr);

	}




	// 7  and 8 requirement

	string UniversityCompulsory;
	string UniversityElective;

	getline(file, data);
	stringstream n(data);
	while (getline(n, UniversityCompulsory, ','))
	{

		RegRules.UnivCompulsory.push_back(UniversityCompulsory);

	}



	getline(file, data);
	stringstream q(data);
	while (getline(q, UniversityElective, ','))
	{


		RegRules.UnivElective.push_back(UniversityElective);

	}

	// 9 and Track Elective Courses if found 

	string TrackCompulsoryCourses;
	string TrackElectiveCourses;

	getline(file, data);
	stringstream qq(data);
	while (getline(qq, TrackCompulsoryCourses, ','))
	{

		RegRules.TrackCompulsory.push_back(TrackCompulsoryCourses);

	}

	getline(file, data);
	stringstream qqq(data);

	while (getline(qqq, TrackElectiveCourses, ','))
	{


		RegRules.TrackElective.push_back(TrackElectiveCourses);

	}

	// 10 and 11 requirement

	string MajorCompulsoryCourses;
	string MajorElectiveCourses;

	getline(file, data);
	stringstream r(data);

	while (getline(r, MajorCompulsoryCourses, ','))
	{


		RegRules.MajorCompulsory.push_back(MajorCompulsoryCourses);

	}

	getline(file, data);
	stringstream rr(data);

	while (getline(rr, MajorElectiveCourses, ','))
	{


		RegRules.MajorElective.push_back(MajorElectiveCourses);
	}

	// 12 and 13 requirement


	string MajorConcentrationCompulsoryCourses;
	string MajorConcentrationElectiveCourses;



	for (int j = 0; j < stoi(tempNumOfCon); j++)
	{
		getline(file, data);
		stringstream ff(data);
		while (getline(ff, MajorConcentrationCompulsoryCourses, ','))
		{


			RegRules.MajorConcentrationCompulsory.push_back(MajorConcentrationCompulsoryCourses);

		}
		getline(file, data);
		stringstream f(data);
		while (getline(f, MajorConcentrationElectiveCourses, ','))
		{


			RegRules.MajorConcentrationElective.push_back(MajorConcentrationElectiveCourses);

		}



	}



}
//fill vector of minor courses
bool Registrar::FillMinorCourses(Course_Code code) {
	RegRules.MinorCourses.push_back(code);
	return true;
}
//fill done courses
bool Registrar::FillDoneCoursesFun(Course_Code code) {
	RegRules.DoneCourses.push_back(code);
	return true;
}
//check if the added course have its preq done or not 
Course_Code* Registrar::CheckDone(Course_Code code) {
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
		if (RegRules.CourseCatalog[i].Code == code) {
			if (RegRules.CourseCatalog[i].PreReqList.size() == 0) {
				return nullptr;
			}
			for (int n = 0; n < RegRules.CourseCatalog[i].PreReqList.size(); n++) {
				if (RegRules.DoneCourses.size() == 0) {
					return &RegRules.CourseCatalog[i].PreReqList[n];
				}
				for (int j = 0; j < RegRules.DoneCourses.size(); j++) {
					if (RegRules.DoneCourses[j] == RegRules.CourseCatalog[i].PreReqList[n]) {
						return nullptr;
					}

				}

			}

		}

	}
	return nullptr;
}
//CHECK COREQ
Course_Code* Registrar::checkcore(Course_Code code, SEMESTER sem, int year) {
	for (int i = 0; i < RegRules.CourseCatalog.size(); i++) {
		if (RegRules.CourseCatalog[i].Code == code) {
			if (RegRules.CourseCatalog[i].CoReqList.size() == 0) {
				return &RegRules.CourseCatalog[i].Code;
			}
			for (int n = 0; n < RegRules.CourseCatalog[i].CoReqList.size(); n++) {
				Course_Code CODE = RegRules.CourseCatalog[i].CoReqList[n];
				return pSPlan->coreqyear(CODE, sem, year);

			}
		}
	}
	return nullptr;
}

Registrar::~Registrar()
{
	delete pGUI;
}
