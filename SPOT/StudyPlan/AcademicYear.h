#pragma once
#include <list>

#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"

//Represent one year in the student's study plan
class AcademicYear:public Drawable
{
	int TotalCredits=0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits=0, TotalMajorCredits=0,
		TotalTrackCredits=0, TotalConcentrationCredits=0,
		TotalMinorCredits=0;

	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	list<Course*> YearCourses[SEM_CNT];
	list<Course*> ::iterator ITERATOR;
	list <Course*>::iterator iter;
	list <Course*>::iterator it;
public:
	AcademicYear();
	virtual ~AcademicYear();
	bool actiondeletecourse(int x_point, int y_point,SEMESTER SEMs); //detect the course position and delete course
	Course* DetectPositionOfCourse(int x_point, int y_point, SEMESTER sem); //detect course position
	/*bool CheckMinorInSP(vector <Course_Code>MinorCourses);*/ //loop on YearCourses list to check if the minor courses are found
	//bool CheckDoneCORE(Course_Code code);
	bool AddCourse(Course*, SEMESTER );
	Course* CheckCreditsMaxMin(int x, int y, SEMESTER sem);
	Course_Code* CheckCoreq(Course_Code code, SEMESTER sem);  //check if the added course have its coreq or not
	void virtual DrawMe(GUI*) const;
};

