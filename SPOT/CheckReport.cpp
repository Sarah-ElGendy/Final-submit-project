#include "CheckReport.h"
#include "Actions\Action.h"
#include "Registrar.h"
#include <string>
#include <fstream>
using namespace std;
CheckReport::CheckReport(Registrar* p) :Action(p)
{
}
bool CheckReport::Execute() {
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Error Report:  ");
	ifstream myfile;
	myfile.open("report.txt", ios::in);
	if (myfile.is_open()) {
		string str;
		while (getline(myfile, str)) {
			pGUI->PrintMsg("" + str);
			Course_Code code = pGUI->GetSrting();
		}
	}
	return true;
}
CheckReport::~CheckReport() {

}