#ifndef TITLE_H
#define TITLE_H

#include "Time.h"

class Title {
public:
	Title(int start, int length, string text);
	Title(string str, int& pos);
	~Title();
	void selectTitle();
	void deselectTitle();
	bool getSelection();

	void changeTitleTime(int ms);
	void setTitleSerial(int serial);
	void setText(string text);
	void setEndingTime(int ms);

	int getSerial();
	string getText();
	string getTitleTimes();
	bool getError();

	int getTitleBeginningTime();
	int getTitleEndingTime();
	int getTitleTimeLength();
	

private:
	int title_serial;
	Time* time_begin;
	Time* time_end;
	string title_text;

	bool title_selected;
	bool title_error;

	int readSerial(string str, int& pos);
	string readTime(string str, int& pos);
	string readText(string str, int& pos);
};
#endif