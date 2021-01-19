#pragma once
#include <string>
using namespace std;

#include "..\DEFs.h"
#include "CMUgraphicsLib\CMUgraphics.h"

class Course;
class AcademicYear;
//user interface class
class GUI
{

	enum MENU_ITEM //The items of the menu (you should add more items)
	{
		//Note: Items are ordered here as they appear in the menu
		//If you want to change the menu items order, just change the order here
		ITM_ADD,		//Add a new course
		ITM_DELETE,
		ITM_LOAD_STUDY_PLAN,
		ITM_ADD_NOTES,
		ITM_CALCULATE_GPA,
		ITM_SELECT_COURSE_STATUS,
		ITM_Display_Student_Level,
		ITM_REPORT,
		ITM_DISPLAY_COURSE_INFO,
		ITM_CHANGE_COURSE_CODE,
		ITM_REORDER_COURSES,
						//TODO: Add more items names here


		ITM_EXIT,		//Exit item

		ITM_CNT			//no. of menu items ==> This should be the last line in this enum

	};

	//Some constants for GUI
	static const int	WindWidth = 1400, WindHeight = 700,	//Window width and height
		wx = 15, wy = 15,		//Window starting coordinates
		StatusBarHeight = 60,	//Status Bar Height
		MenuBarHeight = 80,		//Menu Bar Height (distance from top of window to bottom line of menu bar)
		MenuItemWidth = 70,
		YearWidth = 1350,
		SemWidth = 90;		//Width of each item in the menu
	    


	color DrawColor = BLACK;		//Drawing color
	color FillColor = LIGHTCYAN;		//Filling color (for courses)
	color HiColor = RED;			//Highlighting color
	color ConnColor = GREEN;		//Connector color
	color MsgColor = BLUE;			//Messages color
	color BkGrndColor = LIGHTGRAY;	//Background color
	color StatusBarColor = DARKGRAY;//statusbar color
	string WindTitle = "Study-Plan Organizational Tool (SPOT)";
	//from here
	color FillColorUni = LIGHTPINK;
	color FillColorTrack = SNOW;
	color FillColorMajor = LIGHTCYAN;
	color FillColorConcentration = LIGHTGREEN;
	color FillColorMinor = LIGHTGREY;
	color FillColorExtra = LIGHTSALMON;
	color FillColorElective = LIGHTYELLOW;
	color FillColorModerateError = ORANGE;
	color FillColorCriticalError = RED;
	//till here
	window* pWind;
public:
	GUI();
	void CreateMenu() const;
	void ClearDrawingArea() const;
	void ClearStatusBar() const;	//Clears the status bar

	//output functions
	void PrintMsg(string msg) const;		//prints a message on status bar

	//Drawing functions
	Course* pCOURSE;
	void DrawCourse(const Course*);
	void DrawCourseColorOrange(const Course*);
	void DrawCourseColorRed(const Course*);
	void DrawAcademicYear(const AcademicYear*);
	void UpdateInterface() const;
	
	//input functions
	ActionData GUI::GetUserAction(string msg = "") const;
	sem getYEARandSEM(int x, int y);
	string GetSrting() const;


	
	

	~GUI();
};

