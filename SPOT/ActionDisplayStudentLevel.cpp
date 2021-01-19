#include "ActionDisplayStudentLevel.h"
#include "ActionSelectCourseStatus.h"
#include "Registrar.h"
#include <iostream>
ActionDisplayStudentLevel::ActionDisplayStudentLevel(Registrar* p) :Action(p){

}
bool ActionDisplayStudentLevel::Execute() {
	GUI* pGUI = pReg->getGUI();
	int CounterOfCredits = pReg->SelectCourseStatus(0);
	if (CounterOfCredits > 0 && CounterOfCredits <= 30) {
		ActionData actData = pGUI->GetUserAction("the student level is: Freshman ");
	}
	if (CounterOfCredits > 30 && CounterOfCredits <= 59) {
		ActionData actData = pGUI->GetUserAction("the student level is: Second year student ");
	}
	if (CounterOfCredits > 59 && CounterOfCredits <= 89) {
		ActionData actData = pGUI->GetUserAction("the student level is: Third year student ");
	}
	if (CounterOfCredits > 89 && CounterOfCredits <= 90) {
		ActionData actData = pGUI->GetUserAction("the student level is: Junior ");
	}
	if (CounterOfCredits > 90 && CounterOfCredits <= 162) {
		ActionData actData = pGUI->GetUserAction("the student level is: Senior ");
	}
	return true;
}
ActionDisplayStudentLevel::~ActionDisplayStudentLevel() {

}
