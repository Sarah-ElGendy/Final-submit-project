#include "Course.h"
#include "../GUI/GUI.h"

Course::Course(Course_Code r_code, string r_title, int crd) :code(r_code), Title(r_title)
{
	credits = crd;
}

Course::~Course()
{
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
}

void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}
//return type of course uni, ...
string Course::getType() const {
	return type;
}

void Course::setpositionofcourse(double x_point, double y_point) { //set position of the rectangle of the course
	x = x_point;
	y = y_point;
}
int* Course::getpositionofcourse() const { //get position of the rectangle of the course
	int point[4] = { x , x + 80, y, y + 40 };
	return point;
}