/*
 *SteamPunkGUI1.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the main window of the GUI/application.
 *
 * Created on:   Feb 19, 2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 * List of functions:
 *    - TODO
 *
 */

#include "SteamPunkGUI1.h"
#include "DataEntryGUI.h"
#include "GUIStyles.h"
#include "ResultWindow.h"
//#include "CanvasUtility.h"
#include "main.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <thread>
#include <stdio.h>
#include <FL/names.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <FL/Fl.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include <curl/curl.h>


using namespace std;
int SteamPunkGUI1::num_projects = 0;
int SteamPunkGUI1::num_students = 0;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}




Fl_PNG_Image *LoadingPngsSP[22];

Fl_PNG_Image *TrainPngs[7];
Fl_PNG_Image *PreTrainPngs[8];
Fl_PNG_Image *EndTrainPngs[9];

Fl_PNG_Image *Gears1Pngs[10];
Fl_PNG_Image *Gears2Pngs[10];


void GearsAnimate(Fl_Window *w, Fl_Box *b, Fl_Box *b2) {


	int i = 0;
		while (w->shown()==true) {
			Fl::check();
			b->image(Gears1Pngs[i]);
			b2->image(Gears2Pngs[i]);
			w->redraw();
			usleep(100000);
			i++;
			if (i == 10) {
				i = 0;
			}
		}            //end while loop



}

void SteamPunkGUI1::MainWindow2() {

	//ASU logos
	Fl_PNG_Image ASU_LOGO_BLACK1("./Images/asu_university_horiz_rgb_black_600.png");
	Fl_PNG_Image ASU_LOGO_BLACK2("./Images/asu_sunburst_rgb_black_150ppi_0.png");
	Fl_PNG_Image ASU_LOGO_WHITE2("./Images/asu_university_horiz_rgb_white_150.png");

	Fl_PNG_Image AboutLogo("./Images/About3.png");
	for (int i = 0; i < 10; i++) {
			string filename = "./Images/Steampunk/Gears1/" + to_string(i) + ".png";
			int length = filename.length();
			char png_char[length + 1];
			strcpy(png_char, filename.c_str());
			Gears1Pngs[i] = new Fl_PNG_Image(png_char);
		}

	for (int i = 0; i < 10; i++) {
			string filename = "./Images/Steampunk/Gears2/" + to_string(i) + ".png";
			int length = filename.length();
			char png_char[length + 1];
			strcpy(png_char, filename.c_str());
			Gears2Pngs[i] = new Fl_PNG_Image(png_char);
		}

	const int windowMainW = 750;
	const int windowMainH = 450;
	const char windowMainStr[] =
			"_______________________________________________\nCAPSTONE TEAM ASSIGNMENT SYSTEM";
	windowMain = new Fl_Window(windowMainW, windowMainH,
			"Capstone Team Assignment System");
	windowMain->color(DARK_TAUPE);

	{
		Fl_Tabs *tabs = new Fl_Tabs(10, 10, 730, 350);
		tabs->selection_color(DARK_BRASS);
		windowMain->resizable(tabs);
		{
			Fl_Group *homeTab = new Fl_Group(10, 40, 720, 300, "   Home   ");
			homeTab->labelsize(15);
			homeTab->labelfont(FL_TIMES_ITALIC);
			windowMain->box(FL_BORDER_BOX);
			{
				homeTab->color(ASU_BLACK);
				homeTab->selection_color(ASU_BLACK);
				homeTab->labelcolor(ASU_WHITE);


				Fl_Box *boxHeader2 = new Fl_Box(20, 50, 710, 250);
				Fl_PNG_Image *silver = new Fl_PNG_Image("./Images/Steampunk/Silver.png");
				boxHeader2->image(silver);
				boxHeader2->box(FL_NO_BOX);


				boxHeader = new Fl_Box(20, 50, 710, 250, windowMainStr);
				Fl_PNG_Image *start = new Fl_PNG_Image("./Images/Steampunk/start1.png");
				buttonStart = new Fl_Button(20, 305, 710, 50);


				gearBox1 = new Fl_Box(540, 45, 210, 210);
				gearBox1->box(FL_NO_BOX);

				gearBox2 = new Fl_Box(15, 40, 150, 150);
				gearBox2->box(FL_NO_BOX);


				boxHeader->box(FL_NO_BOX);
				boxHeader->color(ASU_MAROON);
				boxHeader->image(ASU_LOGO_BLACK1);


				boxHeader->labelfont(FL_TIMES_ITALIC);
				boxHeader->labelsize(24);
				boxHeader->labelcolor(ASU_WHITE);
				boxHeader->redraw();

				buttonStart->color(DARK_BRASS);
				//buttonStart->labelfont(FL_TIMES_ITALIC);
				//buttonStart->labelsize(20);
				buttonStart->image(start);
				buttonStart->labelcolor(ASU_BLACK);
				buttonStart->selection_color(DARK_GREY);
				buttonStart->callback(static_StartButtonClick, this);
			}

			homeTab->end();
			Fl_Group *aboutTab = new Fl_Group(40, 50, 750, 360, "   About   ");
			{

				aboutTab->color(DARK_BRASS);
				aboutTab->selection_color(ASU_BLACK);
				aboutTab->labelcolor(ASU_WHITE);
				aboutTab->labelsize(15);
				aboutTab->labelfont(FL_TIMES_ITALIC);
				//Fl_PNG_Image *brass1 = new Fl_PNG_Image("./Images/Steampunk/Brass1.png");
				//aboutTab->image(brass1);


				Fl_Box *aboutBox1;
				Fl_Box *aboutBox2;
				Fl_Box *TextBox1;
				Fl_Box *TextBox2;
				Fl_Text_Display *aboutTextDisplay;
				Fl_Text_Buffer *aboutBuffer;

				aboutBox1 = new Fl_Box(20, 55, 345, 295);
				aboutBox1->box(FL_FLAT_BOX);
				Fl_PNG_Image *aboutpng = new Fl_PNG_Image("./Images/Steampunk/about8.png");
				aboutBox1->image(aboutpng);
				//aboutBox1->color(ASU_WHITE);
				aboutBox1->labelcolor(ASU_WHITE);
				aboutBox1->labelsize(15);
				aboutBox1->labelfont(FL_TIMES_BOLD_ITALIC);
				//aboutBox1->image(AboutLogo);

				const char AboutStr[] =
						"\nThe Capstone Team Assignment System\n was developed "
								"by five senior software \n engineering students during the \n Fall 2019 and Spring 2020 semesters.\n "
								"\n SOFTWARE TEAM ";
				const char TeamStr[] =
						"\n Elizabeth Marquise\n Matthew Cilibraise\n Sean Rogers          \n"
								" Cristi Deleo           \n Myles Colina          \n";

				TextBox1 = new Fl_Box(20, 55, 345, 100, AboutStr);
				TextBox1->labelcolor(ASU_BLACK);
				TextBox1->labelsize(15);
				TextBox1->labelfont(FL_TIMES_BOLD_ITALIC);

				TextBox2 = new Fl_Box(20, 125, 345, 200, TeamStr);
				TextBox2->labelcolor(ASU_BLACK);
				TextBox2->labelsize(22);
				TextBox2->labelfont(FL_TIMES_BOLD);

				aboutBox2 = new Fl_Box(375, 55, 355, 30, "About The Software");
				aboutBox2->box(FL_FLAT_BOX);
				aboutBox2->color(DARK_TAUPE);
				aboutBox2->labelcolor(ASU_WHITE);
				aboutBox2->labelsize(15);
				aboutBox2->labelfont(FL_TIMES_BOLD_ITALIC);

				// Buffer
				aboutBuffer = new Fl_Text_Buffer();

				//Text Display
				aboutTextDisplay = new Fl_Text_Display(375, 85, 355, 265);
				aboutTextDisplay->buffer(aboutBuffer);
				aboutTextDisplay->textfont(FL_TIMES);
				aboutTextDisplay->textcolor(ASU_BLACK);
				aboutTextDisplay->textsize(15);
				aboutTextDisplay->selection_color(ASU_GOLD);
				aboutTextDisplay->color(CREAM);

				aboutBuffer->text("\nThis software application creates \n"
						"high-quality assignments of student teams\n"
						"to ASU Capstone projects.This automizes a\n"
						"previously manual task reducing the time\n"
						"to just minutes. The task of assigning\n"
						"teams to projects is of NP-hard complexity,\n"
						"with the ‘brute force’ method of finding\n "
						"all possible combinations to arrive at\n"
						"the most optimal solution taking more\n"
						"years than there are atoms in the\n"
						"universe!\n"
						"The team has devised a software solution\n "
						"that reduces this time to minutes, \n"
						"and provides excellent student teams\n "
						"to project matches.\n \n"
						"The algorithm that the team created takes\n"
						"into account the student's skills, among\n"
						"other factors, and matches them to \n"
						"projects based on the required skills.\n"
						"The algorithm focuses on the quality of the\n"
						"entire team, ensuring that students are\n"
						"assigned to teams that closely match their\n"
						"own skill level, and the skills required\n"
						"for the project.\n"

				);

			}
			aboutTab->end();
		}

		tabs->end();

	}

	/* for running / testing inputs */
	inputprojects = new Fl_Int_Input(150, 400, 200, 30, "#Projects: ");
	inputstudents = new Fl_Int_Input(500, 400, 200, 30, "#Students: ");

	inputprojects->labelcolor(ASU_WHITE);
	inputprojects->labelfont(FL_TIMES_ITALIC);

	inputstudents->labelcolor(ASU_WHITE);
	inputstudents->labelfont(FL_TIMES_ITALIC);

	/* end */

	windowMain->show();
	windowMain->end();


	XInitThreads();
	thread threads[1];

	threads[0] = thread(GearsAnimate, windowMain, gearBox1, gearBox2);

	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();}


	//tabs->show();
	Fl::run();



}

/*****************************************************************************
 * TeamsButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Generate Teams button is clicked, this callback function
 *	    takes the inputs from the int text input boxes, and passes them
 *	    to the main Team assignment function (main_run).
 *	    It creates a new window with a progress bar.
 *
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void SteamPunkGUI1::TeamsButtonClick(Fl_Widget *w) {

	/*for (int i = 0; i < 22; i++) {

		string filename = "./Images/Loading/" + to_string(i + 1) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		LoadingPngsSP[i] = new Fl_PNG_Image(png_char);

	}*/

	//read in pngs for Pre-Train
	for (int i = 0; i < 8; i++) {
		string filename = "./Images/Steampunk/PreTrain/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		PreTrainPngs[i] = new Fl_PNG_Image(png_char);
	}

	for (int i = 0; i < 7; i++) {
		string filename = "./Images/Steampunk/Train/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		TrainPngs[i] = new Fl_PNG_Image(png_char);
	}

	for (int i = 0; i < 9; i++) {
		string filename = "./Images/Steampunk/EndTrain/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());
		EndTrainPngs[i] = new Fl_PNG_Image(png_char);
	}

	//PROGRESS BAR WINDOW

	progressWindow = new Fl_Window(870, 700, "Team Assignment Progress");
	progressWindow->begin();

	/*Fl_Box *backBox = new Fl_Box(0, 550, 870, 150);
	backBox->box(FL_BORDER_BOX);
	backBox->color(DARK_TAUPE);*/

	Fl_Box *backBox1 = new Fl_Box(5, 5, 865, 500);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(DARK_BRASS);

	Fl_Box *backBox2= new Fl_Box(0, 0, 870, 510);
	backBox2->box(FL_NO_BOX);
	//backBox2->color(DARK_BRASS);
	Fl_PNG_Image *frame = new Fl_PNG_Image("./Images/Steampunk/trainframe1.png");
	backBox2->image(frame);
	/*
	Fl_Box *backBox1 = new Fl_Box(0, 0, 65, 550);
	backBox1->box(FL_FLAT_BOX);
	backBox1->color(DARK_TAUPE);

	Fl_Box *backBox2 = new Fl_Box(0, 0, 870, 20);
	backBox2->box(FL_FLAT_BOX);
	backBox2->color(DARK_TAUPE);

	Fl_Box *backBox3 = new Fl_Box(805, 0, 65, 550);
	backBox3->box(FL_FLAT_BOX);
	backBox3->color(DARK_TAUPE);*/

	TeamsButton = new Fl_Button(25, 560, 200, 50, "Generate Teams");
	doneButton = new Fl_Button(645, 560, 200, 50, "Done");
	progressBar = new Fl_Progress(20, 625, 830, 40);



	progressBar->minimum(0);               // set progress range to be 0.0 ~ 1.0
	progressBar->maximum(1);
	progressBar->color(SP_GREEN2);               // background color
	progressBar->selection_color(SP_GREEN1);     // progress bar color
	progressBar->labelcolor(FL_WHITE);            // percent text color
	progressBar->labelfont(FL_HELVETICA_BOLD);
	progressBar->labelsize(15);
	progressBar->box(FL_RFLAT_BOX);

	progressWindow->resizable(progressBar);

	//Fl_PNG_Image *baseImage = new Fl_PNG_Image("./Images/Loading/1.png");
	Fl_PNG_Image *baseImage = new Fl_PNG_Image("./Images/Steampunk/PreTrain/0.png");
	//Fl_PNG_Image* baseImage = new Fl_PNG_Image("./Images/cookies/0.png");

	imageBox = new Fl_Box(75, 75, 700, 380);
	imageBox->color(DARK_BRASS);
	imageBox->box(FL_FLAT_BOX);
	imageBox->image(baseImage);
	imageBox->redraw();

	progressBox = new Fl_Box(125, 510, 550, 40, "");

	doneButton->color(DARK_BRASS);
	doneButton->selection_color(DARK_GREY);
	doneButton->labelfont(FL_TIMES_ITALIC);
	doneButton->labelsize(15);
	doneButton->labelcolor(ASU_BLACK);

	TeamsButton->color(DARK_BRASS);
	TeamsButton->selection_color(DARK_GREY);
	TeamsButton->labelfont(FL_TIMES_ITALIC);
	TeamsButton->labelsize(15);
	TeamsButton->labelcolor(ASU_BLACK);

	progressWindow->color(DARK_TAUPE);
	progressWindow->box(FL_BORDER_BOX);

	doneButton->deactivate();

	progressWindow->end();
	progressWindow->show();

	progressBar->value(0);
	progressBar->label(0);

	TeamsButton->callback(static_ProgressTeamsButtonClick, this);
	doneButton->callback(static_DoneButtonClick, this);
	progressWindow->redraw();


	Fl::run();
}

void cookieLoadSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar) {

	int i = 0;
	while (progressBar->value() != 100) {

		string filename = "./Images/cookies/" + to_string(i) + ".png";
		int length = filename.length();
		char png_char[length + 1];
		strcpy(png_char, filename.c_str());

		Fl_PNG_Image *cookies = new Fl_PNG_Image(png_char);
		Fl::check();
		b->image(cookies);
		b->redraw();
		usleep(100000);
		i++;
		if (i == 10) {
			i = 0;
		}
	}            //end while loop

}

void animateSP(Fl_Window *w, Fl_Box *b, Fl_Progress *progressBar,
		Fl_PNG_Image *loadingPngs[23]) {


			b->image(PreTrainPngs[0]);
				b->redraw();
				usleep(50000);

	for (int i = 1; i < 8; i++) {
		Fl::check();
			b->image(PreTrainPngs[i]);
			b->redraw();
			usleep(50000);

	}


	int j = 0;
	while (progressBar->value() != 100) {
		Fl::check();
		b->image(TrainPngs[j]);
		b->redraw();
		usleep(50000);
		j++;
		if (j == 7) {
			j = 0;
		}
	}            //end while loop

	for (int i = 0; i < 9; i++) {
		Fl::check();
			b->image(EndTrainPngs[i]);
			b->redraw();
			usleep(50000);
	}


}

void teamAssignmentSP(int num_students, int num_projects,
		Fl_Progress *progressBar) {

	main m;
	m.main_run(num_projects, num_students, progressBar);
}

/*****************************************************************************
 * ProgressTeamsButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Generate Teams button is clicked, this callback function
 *	    takes the inputs from the int text input boxes, and passes them
 *	    to the main Team assignment function (main_run).
 *	    The progress bar then gets updated with the progress, and updates
 *	    the message.
 *
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void SteamPunkGUI1::ProgressTeamsButtonClick(Fl_Widget *w) {

	TeamsButton->deactivate();
	progressBox->label("Team Assignment System Running...");
	progressBox->labelfont(FL_HELVETICA);
	progressBox->labelsize(20);
	progressBox->labelcolor(ASU_BLACK);
	imageBox->redraw();

	XInitThreads();
	thread threads[1];

	threads[0] = thread(animateSP, progressWindow, imageBox, progressBar,
			LoadingPngsSP);

	//if you want to load cookies.
	//threads[0] = thread (cookieLoad, progressWindow, imageBox, progressBar);

	//call to main.cpp function main_run, to run the team assignment system.
	main m;
	m.main_run(num_projects, num_students, progressBar);

	//join threads
	for (int i = 0; i < 1; i++) {
		threads[i].join();
	}

	Fl_PNG_Image *doneImage = new Fl_PNG_Image("./Images/Steampunk/EndTrain/8.png");
	imageBox->image(doneImage);
	imageBox->redraw();

	doneButton->activate();
	progressBox->label("Team Assignment Complete! Click 'Done' to continue.");
	progressBox->labelsize(18);
	progressBox->labelfont(FL_HELVETICA);

}

/*****************************************************************************
 * DoneButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Done button is clicked, the results window is opened.
 *
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void SteamPunkGUI1::DoneButtonClick(Fl_Widget *w) {

	progressWindow->hide();
	ResultWindow windowResult;
	windowResult.buffer->loadfile("results.txt", 1000000);
	windowResult.addText();
}

/*****************************************************************************
 * StartButtonClick
 *
 * Author(s): Team#35
 *
 * Description:
 *		When the Start button is clicked, this callback function
 *	   Opens the next GUI window.
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void SteamPunkGUI1::StartButtonClick(Fl_Widget *w) {


	//open the firefox browser for ASU canvas login page.
	//system("firefox https://canvas.asu.edu/login");

	num_projects = atol(inputprojects->value());
	num_students = atol(inputstudents->value());
	windowMain->hide();

	//CanvasUtility Canvas;
	 //Canvas.getCourses();
	 //Canvas.getQuizzes();

	//call to next GUI window.
	DataEntryGUI dataGUI(windowMain);

}

int SteamPunkGUI1::handle(int event) {

	fprintf(stderr, "EVENT: %s(%d)\n", fl_eventnames[event], event);
	switch (event) {
	case FL_PUSH:
		cout << "FL_PUSH" << endl;
		Fl_PNG_Image TeamLogo2("./Images/button2.png");
		generateTeams->image(TeamLogo2);
		//windowMain.redraw();

		return 1;
	}
	return 0;
}

void SteamPunkGUI1::callTeams(Fl_Widget *w) {

	TeamsButtonClick(windowMain);

}



SteamPunkGUI1::SteamPunkGUI1() {
	// TODO Auto-generated constructor stub

}

SteamPunkGUI1::~SteamPunkGUI1() {
	// TODO Auto-generated destructor stub
}

