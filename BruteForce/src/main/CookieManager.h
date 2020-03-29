/*
 * CookieManager.h
 *
 * Description:
 *
 *  Created on: 
 *      Author: Team 35
 * 
 */

#ifndef COOKIEMANAGER_H_
#define COOKIEMANAGER_H_

#include <curl/curl.h>
#include <string>
#include <vector>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <libsoup/soup.h>
#include "Student.h"
#include "Project.h"
#include "ClassSection.h"
#include "Team.h"

using namespace std;

class CookieManager {
public:
	vector <Student> currentStudents;

	CookieManager();
	~CookieManager();
	int newHttpsSession(const char *hostURL);

	void getCourses(vector<SoupCookie> cookiedata);
	void getQuizzes(vector<SoupCookie> cookiedata, int course_id, string quizName, vector<Student> students);
	void getAssignment(vector<SoupCookie> cookiedata, int course_ID, int quiz_ID, vector<Student> students);
	void getQuizSubmissions(vector<SoupCookie> cookiedata,int course_ID, int quiz_ID, int assignment_ID, vector<Student> students);
	vector<Student> getStudents(vector<SoupCookie> cookiedata, int course_ID);

	static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
			void *userp);
	static void print_cookies(CURL *curl);
	int newHttpSession(const char *hostURL);
	int postGroupCategories(vector<SoupCookie> cookiedata, ClassSection course);
	void postStudentstoGroups(vector<SoupCookie> cookiedata, vector <Team> allTeams);
	void postGroups(vector<SoupCookie> cookiedata, vector <Team> allTeams );
	int MiniBrowser(int argc, char*[]);
};

#endif /* SRC_MAIN_COOKIEMANAGER_H_ */
