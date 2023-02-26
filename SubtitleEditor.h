#ifndef SUBTITLEEDITOR_H
#define SUBTITLEEDITOR_H

#include "Title.h"
#include "MyStack.h"
class SubtitleEditor {
public:
	SubtitleEditor();
	~SubtitleEditor();

	int loadSubtitles(string subtitles);
	string saveSubtitles();

	void addToSelection(int start, int end);
	void deselect();

	void shiftForward(int ms);
	void shiftBackward(int ms);
	void insertSubtitle(int start, int length, string text);
	void deleteSubtitles();
	void merge(string subtitles);

	void boldText(int start, int end);
	void italicText(int start, int end);
	void underlineText(int start, int end);
	void removeStyle();

	void fixLongLines(int max);
	void fixLongTime(int max);
	void undo();

private:

	typedef struct node {
		Title* titlePointer;
		MyStack* top;
		struct node* next;
	}Node;

	Node* head;
	bool listSelected;

	bool isOverlapped(string text, int start, int end);
	bool NeedsToBeFixed(string text, int max);
	string readWords(string text, int number, int& counter);
	string loadString();
};

#endif
