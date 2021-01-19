#include "GUI.h"
#include "../Courses/Course.h"
#include "../StudyPlan/AcademicYear.h"
#include <sstream>

GUI::GUI()
{ 
	pWind = new window(WindWidth, WindHeight,wx,wy);
	pWind->ChangeTitle(WindTitle);
	ClearDrawingArea();
	ClearStatusBar();
	CreateMenu();
}


//Clears the status bar
void GUI::ClearDrawingArea() const
{
	pWind->SetBrush(BkGrndColor);
	pWind->SetPen(BkGrndColor);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight -StatusBarHeight);

}

void GUI::ClearStatusBar() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight, WindWidth, WindHeight);
}

void GUI::CreateMenu() const
{
	pWind->SetBrush(StatusBarColor);
	pWind->SetPen(StatusBarColor);
	pWind->DrawRectangle(0, 0, WindWidth, MenuBarHeight);
	//You can draw the menu icons any way you want.

	//First prepare List of images paths for menu item
	string MenuItemImages[ITM_CNT];
	MenuItemImages[ITM_ADD] = "GUI\\Images\\Menu\\Menu_add_course.jpg";
	MenuItemImages[ITM_DELETE] = "GUI\\Images\\Menu\\Menu_Delete.jpg";
	MenuItemImages[ITM_LOAD_STUDY_PLAN] = "GUI\\Images\\Menu\\Menu_Load.jpg";
	MenuItemImages[ITM_CHANGE_COURSE_CODE] = "GUI\\Images\\Menu\\Menu_Change_Course_Code.jpg";
	MenuItemImages[ITM_REORDER_COURSES] = "GUI\\Images\\Menu\\Menu_Reorder.jpg";
	MenuItemImages[ITM_DISPLAY_COURSE_INFO] = "GUI\\Images\\Menu\\Menu_CourseINFO.jpg";
	MenuItemImages[ITM_ADD_NOTES] = "GUI\\Images\\Menu\\Menu_Notes.jpg";
	MenuItemImages[ITM_CALCULATE_GPA] = "GUI\\Images\\Menu\\Menu_GPA.jpg";
	MenuItemImages[ITM_SELECT_COURSE_STATUS] = "GUI\\Images\\Menu\\Menu_Select_course_status.jpg";
	MenuItemImages[ITM_Display_Student_Level] = "GUI\\Images\\Menu\\Menu_Display_Student_Level.jpg";
	MenuItemImages[ITM_REPORT] = "GUI\\Images\\Menu\\Menu_Report.jpg";
	MenuItemImages[ITM_EXIT] = "GUI\\Images\\Menu\\Menu_Exit.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu items one image at a time
	for (int i = 0; i<ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*MenuItemWidth, 0, MenuItemWidth, MenuBarHeight);
}

////////////////////////    Output functions    ///////////////////

//Prints a message on the status bar
void GUI::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->SetPen(MsgColor);
	pWind->DrawString(MsgX, WindHeight - MsgY, msg);
}

//////////////////////////////////////////////////////////////////////////
void GUI::UpdateInterface() const
{
	
	pWind->SetBuffering(true);
	//Redraw everything
	CreateMenu();
	ClearStatusBar();
	ClearDrawingArea();
	pWind->UpdateBuffer();
	pWind->SetBuffering(false);

}

////////////////////////    Drawing functions    ///////////////////
void GUI::DrawCourse(const Course* pCrs)
{
	if (pCrs->isSelected())
		pWind->SetPen(HiColor, 2);
	else
	pWind->SetPen(DrawColor, 2);
	pWind->SetBrush(FillColor);
	
	/*if (pCOURSE->getType() == "UniversityCoumpulsory" || pCOURSE->getType() == "UniversityElective") {
		pWind->SetPen(YELLOW, 2);
	}
	else if (pCOURSE->getType() == "MajorCoumpulsory" || pCOURSE->getType() == "MajorElective") {
		pWind->SetPen(BLUE, 2);
	}
	else if (pCOURSE->getType() == "TrackCoumpulsory" || pCOURSE->getType() == "TrackElective") {
		pWind->SetPen(PINK, 2);
	}*/
	graphicsInfo gInfo = pCrs->getGfxInfo();
	//conditions of drawing the courses
	if (gInfo.x > 0 && gInfo.x < 270) { //year
		if (gInfo.x > 0 && gInfo.x < 90) { //sem
			gInfo.x = 1;
		}
		if (gInfo.x > 90 && gInfo.x < 180) {
			gInfo.x = 91;
		}
		if (gInfo.x > 180 && gInfo.x < 270) {
			gInfo.x = 181;
		}
	}
	if (gInfo.x > 270 && gInfo.x < 540) {
		if (gInfo.x > 270 && gInfo.x < 360) {
			gInfo.x = 271;
		}
		if (gInfo.x > 360 && gInfo.x < 450) {
			gInfo.x = 361;
		}
		if (gInfo.x > 450 && gInfo.x < 540) {
			gInfo.x = 451;
		}
	}
	if (gInfo.x > 540 && gInfo.x < 810) {
		if (gInfo.x > 540 && gInfo.x < 630) {
			gInfo.x = 541;
		}
		if (gInfo.x > 630 && gInfo.x < 720) {
			gInfo.x = 631;
		}
		if (gInfo.x > 720 && gInfo.x < 810) {
			gInfo.x = 721;
		}
	}
	if (gInfo.x > 810 && gInfo.x < 1080) {
		if (gInfo.x > 810 && gInfo.x < 900) {
			gInfo.x = 811;
		}
		if (gInfo.x > 900 && gInfo.x < 990) {
			gInfo.x = 901;
		}
		if (gInfo.x > 990 && gInfo.x < 1080) {
			gInfo.x = 991;
		}
	}
	if (gInfo.x > 1080 && gInfo.x < 1350) {
		if (gInfo.x > 1080 && gInfo.x < 1170) {
			gInfo.x = 1081;
		}
		if (gInfo.x > 1170 && gInfo.x < 1260) {
			gInfo.x = 1171;
		}
		if (gInfo.x > 1260 && gInfo.x < 1350) {
			gInfo.x = 1261;
		}

	}
	//end here
	pWind->DrawRectangle(gInfo.x, gInfo.y, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT);
	pWind->DrawLine(gInfo.x, gInfo.y + CRS_HEIGHT / 2, gInfo.x + CRS_WIDTH, gInfo.y + CRS_HEIGHT / 2);
	
	//Write the course code and credit hours.
	int Code_x = gInfo.x + CRS_WIDTH * 0.15;
	int Code_y = gInfo.y + CRS_HEIGHT * 0.05;
	pWind->SetFont(CRS_HEIGHT * 0.4, BOLD , BY_NAME, "Gramound");
	pWind->SetPen(MsgColor);
	
	
	ostringstream crd;
	crd<< "crd:" << pCrs->getCredits();
	pWind->DrawString(Code_x, Code_y, pCrs->getCode());
	pWind->DrawString(Code_x, Code_y + CRS_HEIGHT/2, crd.str());
}

void GUI::DrawAcademicYear(const AcademicYear* pY) 
{
	graphicsInfo gInfo = pY->getGfxInfo();
	static int x;
	for (x = 0; x <= 1350; ++x)
	{
		pWind->SetPen(BLACK);
		//year
		pWind->DrawRectangle(0 + x, 100, 270 + x, 600, FRAME);
		//semesters
		pWind->DrawRectangle(0 + x, 150, 90 + x, 600, FRAME);
		pWind->DrawRectangle(0 + x, 150, 180 + x, 600, FRAME);
		pWind->DrawRectangle(0 + x, 150, 270 + x, 600, FRAME);
		pWind->DrawRectangle(0 + x, 200, 90 + x, 600, FRAME);
		pWind->DrawRectangle(0 + x, 200, 180 + x, 600, FRAME);
		pWind->DrawRectangle(0 + x, 200, 270 + x, 600, FRAME);
		x += 270;
	}
	pWind->SetPen(BLUE);
	pWind->SetFont(30, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(90, 110, "year 1");
	pWind->DrawString(360, 110, "year 2");
	pWind->DrawString(600, 110, "year 3");
	pWind->DrawString(890, 110, "year 4");
	pWind->DrawString(1145, 110, "year 5");
	pWind->SetPen(RED);
	pWind->SetFont(27,  ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(20, 160, "fall");
	pWind->DrawString(300, 160, "fall");
	pWind->DrawString(565, 160, "fall");
	pWind->DrawString(1100, 160, "fall");
	pWind->DrawString(825, 160, "fall");
	pWind->SetFont(20, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(1000, 160, "summer"); //year 4
	pWind->DrawString(730, 160, "summer"); //3
	pWind->DrawString(1270, 160, "summer"); //5
	pWind->DrawString(470, 160, "summer"); //2
	pWind->DrawString(185, 160, "summer"); //1
	pWind->SetFont(22, ITALICIZED, BY_NAME, "Arial");
	pWind->DrawString(100, 160, "spring");
	pWind->DrawString(380, 160, "spring");
	pWind->DrawString(650, 160, "spring");
	pWind->DrawString(1180, 160, "spring");
	pWind->DrawString(920, 160, "spring");

	//if (x < 1352 && x >= 2) {
	//	pWind->SetPen(BLACK);
	//	pWind->DrawRectangle(2 + x, 200, 272 + x, 600, FRAME); //year
	//	pWind->DrawRectangle(2 + x, 250, 92 + x, 600, FRAME); //semester
	//	pWind->DrawRectangle(92 + x, 250, 182 + x, 600, FRAME); //semester
	//	pWind->DrawRectangle(182 + x, 250, 272 + x, 600, FRAME); //semester
	//	x += 270;
	//}
	//else {
	//	x = 2;
	//}
	//
}


////////////////////////    Input functions    ///////////////////
//This function reads the position where the user clicks to determine the desired action
//If action is done by mouse, actData will be the filled by mouse position
ActionData GUI::GetUserAction(string msg) const
{
	keytype ktInput;
	clicktype ctInput;
	char cKeyData;

	
	// Flush out the input queues before beginning
	pWind->FlushMouseQueue();
	pWind->FlushKeyQueue();
	
	PrintMsg(msg);

	while (true)
	{
		int x, y;
		ctInput = pWind->GetMouseClick(x, y);	//Get the coordinates of the user click
		ktInput = pWind->GetKeyPress(cKeyData);

		if (ktInput == ESCAPE)	//if ESC is pressed,return CANCEL action
		{
			return ActionData{ CANCEL };
		}

		
		if (ctInput == LEFT_CLICK)	//mouse left click
		{
			//[1] If user clicks on the Menu bar
			if (y >= 0 && y < MenuBarHeight)
			{
				//Check whick Menu item was clicked
				//==> This assumes that menu items are lined up horizontally <==
				
				int ClickedItemOrder = (x / MenuItemWidth);
				//Divide x coord of the point clicked by the menu item width (int division)
				//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
				
				
				switch (ClickedItemOrder)
				{
				case ITM_ADD: return ActionData{ ADD_CRS };	//Add course
				case ITM_DELETE: return ActionData{ DELETE_COURSE }; //delete course
				case ITM_LOAD_STUDY_PLAN: return ActionData{ LOAD }; //study plan
				case ITM_ADD_NOTES: return ActionData{ NOTES }; //add notes
				case ITM_CHANGE_COURSE_CODE: return ActionData{ CHANGE_COURSE_CODE }; //change course code
				case ITM_REORDER_COURSES: return ActionData{ REORDER_COURSES }; //reorder courses
				case ITM_DISPLAY_COURSE_INFO: return ActionData{ DISPLAY_COURSE_INFO }; //display course info
				case ITM_CALCULATE_GPA: return ActionData{ CALCULATE_GPA }; //calc gpa
				case ITM_SELECT_COURSE_STATUS: return ActionData{ SELECT_COURSE_STATUS }; //calc gpa
				case ITM_Display_Student_Level: return ActionData{ Display_Student_Level }; //calc gpa
				case ITM_REPORT: return ActionData{ REPORT };
				case ITM_EXIT: return ActionData{ EXIT };		//Exit

				default: return ActionData{ MENU_BAR };	//A click on empty place in menu bar
				}
			}

			//[2] User clicks on the drawing area
			if (y >= MenuBarHeight && y < WindHeight - StatusBarHeight)
			{
				return ActionData{ DRAW_AREA,x,y };	//user want clicks inside drawing area
				int clickedyear = (x / YearWidth);
				int clicksem = (x / SemWidth);

			}

			//[3] User clicks on the status bar
			return ActionData{ STATUS_BAR };
		}
	}//end while

}
sem GUI::getYEARandSEM(int x, int y)
{  
	sem yearsANDsem;
	if (y >= 100 && y < 600)
	{
		int clickedyear = (x / YearWidth)+1;
		int clicksem = (x / SemWidth)+1;
		/*int ClickedItemOrder = (x / MenuItemWidth);*/
		//Divide x coord of the point clicked by the menu item width (int division)
		//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
		switch (clickedyear) {
		case 1: yearsANDsem.year = 1;
			break;
		case 2: yearsANDsem.year = 2;
			break;
		case 3: yearsANDsem.year = 3;
			break;
		case 4: yearsANDsem.year = 4;
			break;
		case 5: yearsANDsem.year = 5;
			break;
		}
		switch (clicksem) {
		case 1: yearsANDsem.s = FALL;
			break;
		case 2: yearsANDsem.s = SPRING;
			break;
		case 3: yearsANDsem.s = SUMMER;
			break;
		case 4: yearsANDsem.s = FALL;
			break;
		case 5: yearsANDsem.s = SPRING;
			break;
		case 6: yearsANDsem.s = SUMMER;
			break;
		case 7: yearsANDsem.s = FALL;
			break;
		case 8: yearsANDsem.s = SPRING;
			break;
		case 9: yearsANDsem.s = SUMMER;
			break;
		case 10: yearsANDsem.s = FALL;
			break;
		case 11: yearsANDsem.s = SPRING;
			break;
		case 12: yearsANDsem.s = SUMMER;
			break;
		case 13: yearsANDsem.s = FALL;
			break;
		case 14: yearsANDsem.s = SPRING;
			break;
		case 15: yearsANDsem.s = SUMMER;
			break;
		}

	}
	return yearsANDsem;
}



string GUI::GetSrting() const
{
	//Reads a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" is also supported
	//User should see what he is typing at the status bar

	

	string userInput;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);

		switch (Key)
		{
		case 27: //ESCAPE key is pressed
			PrintMsg("");
			return ""; //returns nothing as user has cancelled the input

		case 13:		//ENTER key is pressed
			return userInput;

		case 8:		//BackSpace is pressed
			if (userInput.size() > 0)
				userInput.resize(userInput.size() - 1);
			break;

		default:
			userInput += Key;
		};

		PrintMsg(userInput);
	}

}








GUI::~GUI()
{
	delete pWind;
}
