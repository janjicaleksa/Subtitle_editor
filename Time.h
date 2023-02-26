#ifndef TIME_H
#define TIME_H
#include <string>
using namespace std;

class Time {

public:

	Time(int start);
	Time(string str);
	string getTime();
	bool getTimeError();
	int getTimeLength();
	void changeTime(int ms);
	void setTime(int ms);

private:
	int hours, minutes, seconds, miliseconds;
	bool timeError;
	int timeLength;
	string timeString;

	int readNumber(string str, int& pos, int size);
	int setTimeLength();
	string setTimeString();

};
#endif