#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Progress.H>

#include "ClassSelectorGUI.h"
#include "AuthTokenGUI.h"

using namespace std;

class MainWindow {

	//generate teams 'static' callback function
	//this function calls the real TeamsButtonClick callback function.
	static void static_TeamsButtonClick(Fl_Widget* w, void * data) {
		((MainWindow*)data)->TeamsButtonClick(w);
	}

	static void static_ProgressTeamsButtonClick(Fl_Widget* w, void * data) {
			((MainWindow*)data)->ProgressTeamsButtonClick(w);
		}
	static void static_DoneButtonClick(Fl_Widget* w, void * data) {
		((MainWindow*)data)->DoneButtonClick(w);
	}

	static void static_StartButtonClick(Fl_Widget* w, void * data) {
		((MainWindow*)data)->StartButtonClick(w);
	}

	// callback functions
	void TeamsButtonClick(Fl_Widget* w);
	void ProgressTeamsButtonClick(Fl_Widget* w);
	void DoneButtonClick(Fl_Widget* w);
	void StartButtonClick(Fl_Widget* w);

    public:
		int num_projects;
		int num_students;
		bool nextWindowFlag;

		//progress bar window
		int barCount;
		Fl_Window *progressWindow;
		Fl_Progress *progressBar;
		Fl_Box *progressBox;
		Fl_Button *TeamsButton;
		Fl_Button *doneButton;

		//main window
		Fl_Window *windowMain;
		//ClassSelectorGUI *nextWindow;
		Fl_Window* nextWindow;
		Fl_Box *boxHeader;
		Fl_Button *buttonStart;
		Fl_Button *buttonOpenProject;
		Fl_Button *generateTeams;
		Fl_Int_Input* inputprojects;
		Fl_Int_Input* inputstudents;

        MainWindow();
        ~MainWindow();

};

#endif /*SRC_MAIN_MAINWINDOW_H_*/
