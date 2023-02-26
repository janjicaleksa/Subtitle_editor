#include "Time.h"

Time::Time(int start)
{
	this->hours = this->minutes = this->seconds = this->miliseconds = this->timeLength = 0;
	this->timeError = false;
	this->timeString = "";
	
	if (start < 0) {
		this->timeError = true;
		return;
	}

	this->miliseconds = start % 1000;
	this->seconds = ((start - this->miliseconds) / 1000) % 60;
	this->minutes = ((((start - this->miliseconds) / 1000) - this->seconds) / 60) % 60;
	this->hours = start / (60 * 60 * 1000);

	this->timeLength = setTimeLength();
	this->timeString = setTimeString();
}

Time::Time(string str)
{
	this->timeString = str;
	this->timeError = false;

	int pos = 0;
	int h = readNumber(str, pos, 2);
	int m = readNumber(str, pos, 2);
	int s = readNumber(str, pos, 2);
	int ms = readNumber(str, pos, 3);

	if (h == -1 || m == -1 || s == -1 || ms == -1) {
		this->timeError = true;
	}
	else {
		this->hours = h;
		this->minutes = m;
		this->seconds = s;
		this->miliseconds = ms;
	}

	this->timeLength = setTimeLength();
}

string Time::getTime()
{
	return this->timeString;
}

bool Time::getTimeError()
{
	if (this->hours > 99 || this->minutes > 59 || this->seconds > 59 || this->miliseconds > 999) this->timeError = true;
	return this->timeError;
}

int Time::getTimeLength()
{
	return this->timeLength;
}

void Time::changeTime(int ms)
{	
	int calcTime = this->timeLength + ms;
	if (calcTime < 0) {
		this->timeError = true;
		return;
	}
	this->miliseconds = (calcTime) % 1000;
	this->seconds = ((calcTime - this->miliseconds) / 1000) % 60;
	this->minutes = ((((calcTime - this->miliseconds) / 1000) - this->seconds) / 60) % 60;
	this->hours = calcTime / (60 * 60 * 1000);

	this->timeLength = setTimeLength();
	this->timeString = setTimeString();
}

void Time::setTime(int ms)
{
	if (ms < 0) {
		this->timeError = true;
		return;
	}
	this->miliseconds = (ms) % 1000;
	this->seconds = ((ms - this->miliseconds) / 1000) % 60;
	this->minutes = ((((ms - this->miliseconds) / 1000) - this->seconds) / 60) % 60;
	this->hours = ms / (60 * 60 * 1000);

	this->timeLength = setTimeLength();
	this->timeString = setTimeString();
}

int Time::setTimeLength()
{
	return this->miliseconds + this->seconds * 1000 + this ->minutes * 1000 * 60 + this->hours * 1000 * 60 * 60;
}

string Time::setTimeString()
{
	string str;
	if (this->hours < 10) {
		str.append("0");
	}
	str.append(to_string(this->hours));
	str.append(":");
	if (this->minutes < 10) {
		str.append("0");
	}
	str.append(to_string(this->minutes));
	str.append(":");
	if (this->seconds < 10) {
		str.append("0");
	}
	str.append(to_string(this->seconds));
	str.append(",");
	if (this->miliseconds < 100) {
		str.append("0");
		if (this->miliseconds < 10) {
			str.append("0");
		}
	}
	str.append(to_string(this->miliseconds));
	
	return str;
}

int Time::readNumber(string str, int& pos, int size)
{
	int num = 0;
	for (int i = 0; i < size; i++) {
		if (str[pos] < '0' || str[pos] > '9') {
			return -1;
			break;
		}
		num = num * 10 + (str[pos] - '0');
		pos++;
	}
	pos++;
	return num;
};

