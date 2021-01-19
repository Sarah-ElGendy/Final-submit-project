#pragma once
#include "GUI\GUI.h"
#include "Actions\Action.h"
#include "Rules.h"
#include "StudyPlan/StudyPlan.h"
//The maestro class for the application
class Registrar
{
	GUI *pGUI;	//pointer to GUI 
	Rules RegRules;	//Registration rules
	StudyPlan *pSPlan;
	/*ActionSelectCourseStatus* p;*/
	CourseInfo* POINTERtoCourseData;
public:
	Registrar();
	GUI* getGUI() const;
	Action* CreateRequiredAction();
	bool ExecuteAction(Action*);
	void UpdateInterface();
	StudyPlan* getStudyPlay() const;
	void ImportRequirements(); //inport course Requirements (Rules)
	void Run();
	bool load();   //import course catalog
	CourseInfo* getcourseinfo(Course_Code code);      //check if the course is in the course catalog or not
	int SelectCourseStatus( int cred);
	bool FillDoneCoursesFun(Course_Code code);   //fill list of done courses
	bool FillMinorCourses(Course_Code code);  //fill list of minor courses
	Course_Code* CheckDone(Course_Code code);  //check if the added course have its preq done or not 
	Course_Code* checkcore(Course_Code code, SEMESTER sem, int year); 
	~Registrar();
};

