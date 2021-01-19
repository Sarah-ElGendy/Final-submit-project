#include "Registrar.h"
#include "Rules.h"
#include <string>
#include <vector>
#include <fstream>
#include "Actions/ActionAddCourse.h"
#include <iostream>    
#include <sstream> 
#include "StudyPlan\AcademicYear.h"
#include"Actions\Action.h"
#include"ImportStudyPlan.h"
using namespace std;

ImportStudyPlan::ImportStudyPlan(Registrar* p) :Action(p)
{
}

bool ImportStudyPlan::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Write the name of the file you want to import the study plan from:");
	Course_Code code = pGUI->GetSrting();
	vector <string> gettheyear;
	vector <string> courses;
	vector <string> semesters;
	fstream file;
	file.open("FILES\\CIE-StudyPlan.txt", ios::in);
	if (file.fail())
		return false;
	else
	{
		//go insidse the file and import the years, semesters and courses
		char* u; //it's a char to read everything 
		char* context = nullptr;
		const int size = 300;
		char line[size];
		//for the gui
		int x, y;
		int a = 0, b = 0, y2 = 0, c = 0, H, j = 0;
		//inialize the variables to store the file
		SEMESTER semester;
		int sem;
		int year;
		while (file.getline(line, size))
		{
			int t = 1;
			int i = 0;
			u = strtok_s(line, ",", &context);
			H = 0;
			i++;
			int yy = 0;
			while (u != NULL)
			{
				if (t == 1)
				{
					//know which year i am in
					gettheyear.push_back(u);
					gettheyear.push_back(u);
					cout << endl << gettheyear[b] << endl;
					if (gettheyear[b] == "Year 1")
					{
						year = 1;
					}
					if (gettheyear[b] == "Year 2")
					{
						year = 2;
					}
					if (gettheyear[b] == "Year 3")
					{
						year = 3;
					}
					if (gettheyear[b] == "Year 4")
					{
						year = 4;
					}
					if (gettheyear[b] == "Year 5")
					{
						year = 5;
					}

					b++;

				}
				if (t == 2)
				{
					semesters.push_back(u);
					cout << semesters[c];
					if (semesters[c] == "Fall")
					{
						semester = FALL;
						sem = 0;


					}
					if (semesters[c] == "Spring")
					{
						semester = SPRING;
						sem = 1;


					}
					if (semesters[c] == "Summer")
					{
						semester = SUMMER;
						sem = 2;

					}
					c++;
				}
				//for gui

				int PLAN_SEMESTER_HEIGHT = 70;
				if (t > 2)
				{
					courses.push_back(u);
					switch (year) 
					{
					case 1:
						x = 2;
						break;
					case 2:
						x = 272;
						break;
					case 3:
						x = 542;
						break;
					case 4:
						x = 812;
						break;
					case 5:
						x = 1082; //initial point and end in (90*3)
						break;
					}
					x = x + 90 * sem;
					y = 200 + 40 * yy;
					graphicsInfo gInfo{ x, y };
					string Title = "Test101";
					int crd = 0;
					Course* pC = new Course(courses[j], Title, crd);
					pC->setGfxInfo(gInfo);
					pC->setpositionofcourse(x, y);
					StudyPlan* pS = pReg->getStudyPlay();
					pS->AddCourse(pC, year, semester);
					j++;
					yy++;

				}
				u = strtok_s(context, ",", &context);
				t++;
			}
		}

		return true;

	}
}
ImportStudyPlan::~ImportStudyPlan()
{

}