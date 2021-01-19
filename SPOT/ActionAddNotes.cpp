#include "ActionAddNotes.h"
#include "Actions\Action.h"
#include "Registrar.h"
#include <string>
#include <fstream>

ActionAddNotes::ActionAddNotes(Registrar* p) :Action(p)
{
}

bool ActionAddNotes::Execute() {

	GUI* pGUI = pReg->getGUI();
	pGUI->PrintMsg("write note you want to add");
	string notes = pGUI->GetSrting();      //take note from the user
	ofstream AddedNote;
	AddedNote.open("notefile.txt", ios::app);
	if (!AddedNote)     //check if the file is opened or not (if it's found)
	{
		pGUI->PrintMsg("Error opening Note file..press enter to continue");
		Course_Code code = pGUI->GetSrting();
		return false;
	}
	else {
		AddedNote << notes << endl;     //add note in the file
		AddedNote.close();                //close the file
		pGUI->PrintMsg("the note saved sucssesfully..press enter to continue");
		Course_Code code = pGUI->GetSrting();
		return true;
	}
	
}
ActionAddNotes::~ActionAddNotes()
{
}