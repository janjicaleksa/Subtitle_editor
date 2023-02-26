#include "Title.h"

Title::Title(int start, int length, string text)
{
	this->title_serial = 0;
	this->title_selected = false;

	this->time_begin = new Time(start);
	this->time_end = new Time(start+length);

	this->title_text = text;

	this->title_error = (this->time_begin->getTimeLength() > this->time_end->getTimeLength());
}

Title::Title(string str, int& pos)
{
	this->title_serial = readSerial(str, pos);
	if (this->title_serial == -1) {
		this->title_error = true;
	}

	string beginTime = readTime(str, pos);
	this->time_begin = new Time(beginTime);
	pos += 5; // da proguta " --> "
	string endTime = readTime(str, pos);
	this->time_end = new Time(endTime);
	pos++;

	this->title_text = readText(str, pos);

	this->title_selected = false;
	this->title_error = this->title_error || (this->time_begin->getTimeLength() > this->time_end->getTimeLength());
}

Title::~Title()
{
	delete this->time_begin;
	delete this->time_end;
}

void Title::selectTitle()
{
	this->title_selected = true;
}

void Title::deselectTitle()
{
	this->title_selected = false;
}

void Title::changeTitleTime(int ms)
{
	this->time_begin->changeTime(ms);
	this->time_end->changeTime(ms);
}

void Title::setTitleSerial(int serial)
{
	this->title_serial = serial;
}

void Title::setText(string text)
{ 
	this->title_text = text;
}

void Title::setEndingTime(int ms)
{
	int endingTime = this->time_begin->getTimeLength() + ms;
	this->time_end->setTime(endingTime);
}

int Title::getSerial()
{
	return this->title_serial;
}

string Title::getText()
{
	int stringSize = this->title_text.length();
	if (this->title_text[stringSize - 1] == '\n') {
		string fixedText = "";
		for (int i = 0; i < (stringSize - 1); i++) fixedText += this->title_text[i];
		return fixedText;
	}
	else return this->title_text;
}

string Title::getTitleTimes()
{
	string str;

	str.append(this->time_begin->getTime());
	str.append(" --> ");
	str.append(this->time_end->getTime());
	str.append("\n");

	return str;
}

bool Title::getError()
{
	return this->title_error;
}

int Title::getTitleBeginningTime()
{
	return this->time_begin->getTimeLength();;
}

int Title::getTitleEndingTime()
{
	return this->time_end->getTimeLength();
}

int Title::getTitleTimeLength()
{
	return (this->getTitleEndingTime() - this->getTitleBeginningTime());
}

bool Title::getSelection()
{
	return this->title_selected;
}



int Title::readSerial(string str, int& pos)
{
	int num = 0;
	while (str[pos] != '\n') {
		if (str[pos] >= '0' && str[pos] <= '9') {
			num = num * 10 + (str[pos] - '0');
			pos++;
		}
		else {
			this->title_error = true;
			return -1;
		}
	}
	pos++;
	return num;
}

string Title::readTime(string str, int& pos)
{
	string time = "";
	for (int i = 0; i < 12; i++) {
		time += str[pos];
		pos++;
	}
	return time;
}

string Title::readText(string str, int& pos)
{
	string s;
	while (str[pos] != '\n' || str[pos + 1] != '\n')
	{
		s.push_back(str[pos]);
		pos++;
	}
	pos += 2;
	
	return s;
}