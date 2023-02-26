#include "SubtitleEditor.h"

SubtitleEditor::SubtitleEditor()
{
	this->head = new Node();
	this->head->titlePointer = nullptr;
	this->head->top = new MyStack();
	this->head->next = nullptr;
	this->listSelected = false;
}

SubtitleEditor::~SubtitleEditor()
{
	//prvo brisem moj stek stanja pozivajuci njegov destruktor, a onda se krecem kroz listu i brisem jedan po jedan element liste
	delete this->head->top;

	Node* tmp = this->head;
	while (this->head != nullptr) {
		this->head = this->head->next;
		delete tmp->titlePointer;
		delete tmp;
		tmp = this->head;
	}
}

int SubtitleEditor::loadSubtitles(string subtitles)
{
	int pos = 0; 
	this->head->titlePointer = new Title(subtitles, pos);
	if (this->head->titlePointer->getError())
		return this->head->titlePointer->getSerial();

	while (subtitles[pos] != '\0') {
		Node* element = new Node();
		element->titlePointer = new Title(subtitles, pos);
		element->next = nullptr;
		// ako postoji greska u titlu, vrati njegov redni broj, ako nema, ubaci ga u listu
		if (element->titlePointer->getError())
			return element->titlePointer->getSerial();

		else 
		{	if (this->head->next == nullptr)
				this->head->next = element;
			else
			{
				Node* tail = this->head;
				while (tail->next) tail = tail->next;
				tail->next = element;
			}
		};
	}
	// procitaj celu listu, smesti u string, a onda dodaj u stek
	string str = loadString();
	this->head->top->addToStack(str);

	return -1;
}

string SubtitleEditor::saveSubtitles()
{
	return this->head->top->getLastState();
}

void SubtitleEditor::addToSelection(int start, int end)
{
	Node* last = this->head;
	while (last->next) last = last->next;

	//ispitaj pocetak i start selekcije
	start = start < 1 ? 1 : start;
	end = end > last->titlePointer->getSerial() ? last->titlePointer->getSerial() : end;

	Node* current = this->head;
	while (current->next) {
		if (current->titlePointer->getSerial() >= start && current->titlePointer->getSerial() <= end) 
			current->titlePointer->selectTitle();
		current = current->next;
	}

	string str = loadString();
	this->head->top->addToStack(str);

	this->listSelected = true;
}

void SubtitleEditor::deselect()
{
	Node* current = this->head;

	while (current->next) {
		current->titlePointer->deselectTitle();
		current = current->next;
	}

	string str = loadString();
	this->head->top->addToStack(str);

	this->listSelected = false;
}

void SubtitleEditor::boldText(int start, int end)
{
	//ako nije selektovana lista, prodji kroz sve titlove, ako jeste, samo kroz selektovane titlove
	if (!listSelected) {
		Node* current = this->head;

		while (current != nullptr) {
			string text = current->titlePointer->getText();
			int posStart = start < 0 ? 0 : start;
			int posEnd = end >= text.length() ? text.length() : end; // ispitivanje pozicija pocetnih i krajnjih karaktera u svakom titlu

			if (!isOverlapped(text, posStart, posEnd)) { //ako nema preklapanja stilova, udji u if i podesi stilizaciju
				text.insert(posStart, "<b>");
				text.insert(posEnd + 3, "</b>");
				current->titlePointer->setText(text);
			}

			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
	else {
		Node* current = this->head;

		while (current != nullptr) {
			if (current->titlePointer->getSelection() == true) {
				string text = current->titlePointer->getText();

				int posStart = start < 0 ? 0 : start;
				int posEnd = end >= text.length() ? text.length() : end;// ispitivanje pozicija pocetnih i krajnjih karaktera u svakom titlu
				if (!isOverlapped(text, posStart, posEnd)) {//ako nema preklapanja stilova, udji u if i podesi stilizaciju
					text.insert(posStart, "<b>");
					text.insert(posEnd + 3, "</b>");
					current->titlePointer->setText(text);
				}
			}
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}

	return;
}

void SubtitleEditor::italicText(int start, int end)
{
	//ako nije selektovana lista, prodji kroz sve titlove, ako jeste, samo kroz selektovane titlove
	if (!listSelected) {
		Node* current = this->head;

		while (current != nullptr) {
			string text = current->titlePointer->getText();
			int posStart = start < 0 ? 0 : start;
			int posEnd = end >= text.length() ? text.length() : end;// ispitivanje pozicija pocetnih i krajnjih karaktera u svakom titlu

			if (!isOverlapped(text, posStart, posEnd)) {//ako nema preklapanja stilova, udji u if i podesi stilizaciju
				text.insert(posStart, "<i>");
				text.insert(posEnd + 3, "</i>");
				current->titlePointer->setText(text);
			}

			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
	else {
		Node* current = this->head;

		while (current != nullptr) {
			if (current->titlePointer->getSelection() == true) {
				string text = current->titlePointer->getText();

				int posStart = start < 0 ? 0 : start;
				int posEnd = end >= text.length() ? text.length() : end;// ispitivanje pozicija pocetnih i krajnjih karaktera u svakom titlu
				if (!isOverlapped(text, posStart, posEnd)) {//ako nema preklapanja stilova, udji u if i podesi stilizaciju
					text.insert(posStart, "<i>");
					text.insert(posEnd + 3, "</i>");
					current->titlePointer->setText(text);
				}
			}
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}

	return;
}

void SubtitleEditor::underlineText(int start, int end)
{
	//ako nije selektovana lista, prodji kroz sve titlove, ako jeste, samo kroz selektovane titlove
	if (!listSelected) {
		Node* current = this->head;

		while (current != nullptr) {
			string text = current->titlePointer->getText();
			int posStart = start < 0 ? 0 : start;
			int posEnd = end >= text.length() ? text.length() : end;// ispitivanje pozicija pocetnih i krajnjih karaktera u svakom titlu

			if (!isOverlapped(text, posStart, posEnd)) {//ako nema preklapanja stilova, udji u if i podesi stilizaciju
				text.insert(posStart, "<u>");
				text.insert(posEnd + 3, "</u>");
				current->titlePointer->setText(text);
			}

			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
	else {
		Node* current = this->head;

		while (current != nullptr) {
			if (current->titlePointer->getSelection() == true) {
				string text = current->titlePointer->getText();

				int posStart = start < 0 ? 0 : start;
				int posEnd = end >= text.length() ? text.length() : end;// ispitivanje pozicija pocetnih i krajnjih karaktera u svakom titlu
				if (!isOverlapped(text, posStart, posEnd)) {//ako nema preklapanja stilova, udji u if i podesi stilizaciju
					text.insert(posStart, "<u>");
					text.insert(posEnd + 3, "</u>");
					current->titlePointer->setText(text);
				}
			}
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);

	}

	return;
}

void SubtitleEditor::removeStyle()
{
	Node* current = this->head;

	while (current != nullptr) {
		if (current->titlePointer->getSelection() == true) { //ako je titl selektovan, potrazi stilizacije, inace nemoj
			string text = current->titlePointer->getText();
			while (1) { // sve dok pronalazis stilove, izbaci ih iz tekstova titla
				int pos = text.find('<');

				if (pos == string::npos)
					break;

				text.erase(pos, 3);

				pos = text.find('<');
				text.erase(pos, 4);
			}

			current->titlePointer->setText(text);
		}

		current = current->next;
	}
	string str = loadString();
	this->head->top->addToStack(str);

	return;
}

void SubtitleEditor::fixLongLines(int max)
{
	if (listSelected) {
		Node* current = this->head;
		while (current) {
			if (current->titlePointer->getSelection()) {
				string text = current->titlePointer->getText();
				if (NeedsToBeFixed(text, max)) { //ako ima barem jednu liniju koja mora da se popravi, prepravi
					int i = 0;
					while (i < text.length()) { //prvo brisem sve nove redove
						if (text[i] == '\n') text.erase(i, 1);
						i++;
					}

					int cntChar = 0;
					int cntBlanco = 0;
					for (int i = 0; i < text.length(); i++) { //ako naidjem na oznake stilizacije, preskacem ih i ne racunam kao nebele znakove
						if (text[i] == '<' && text[i + 2] == '>') {
							i += 3;
							continue;
						}
						if (text[i] == '<' && text[i + 3] == '>') {
							i += 4;
							continue;
						}
						if (text[i] != ' ') cntChar++; //brojim koliko ima nebelih karaktera
						else cntBlanco++;//brojim koliko ima blanko znakova

						if (cntChar == max) {//ako je broj nebelih karaktera jednak maksimumu, podesim checkpoint na onu poziciju do koje sam stigao, i onda idem unazad sve dok ne dodjem do ' ' i tu postavim '\n'
							int checkpoint = i;
							while (1) {
								if (text[checkpoint] == ' ') {
									text[checkpoint] = '\n';
									i = checkpoint;
									break;
								}
								checkpoint--;
							}
							
							cntChar = cntBlanco = 0;//broj blanko znakova u redu podesim na nulu
						}
					}
					current->titlePointer->setText(text);//postavljam izmenjeni tekst u element liste 
				}
			}
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
	else {
		Node* current = this->head;
		while (current) {
			
				string text = current->titlePointer->getText();
				if (NeedsToBeFixed(text, max)) {
					int i = 0;
					while (i < text.length()) {
						if (text[i] == '\n') text.erase(i, 1);
						i++;
					}

					int cntChar = 0;
					int cntBlanco = 0;
					for (int i = 0; i < text.length(); i++) {
						if (text[i] == '<' && text[i + 2] == '>') {
							i += 3;
							continue;
						}
						if (text[i] == '<' && text[i + 3] == '>') {
							i += 4;
							continue;
						}
						if (text[i] != ' ') cntChar++;
						else cntBlanco++;

						if (cntChar == max) {
							int checkpoint = i;
							while (1) {
								if (text[checkpoint] == ' ') {
									text[checkpoint] = '\n';
									i = checkpoint;
									break;
								}
								checkpoint--;
							}

							cntChar = cntBlanco = 0;
						}
					}
					current->titlePointer->setText(text);
				}
			
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
}

void SubtitleEditor::fixLongTime(int max)
{
	if (listSelected) {
		Node* current = this->head;
		while (current) {

			if (current->titlePointer->getSelection()) {
				if (current->titlePointer->getTitleTimeLength() >= max) {//ako je dati titl u listi selektovan i prebacuje duzinu vremena, obradi ga

					int n = current->titlePointer->getTitleTimeLength() / max; 
					while (n * max <= current->titlePointer->getTitleTimeLength()) n++;
					// izracunat broj novih titlova

					int length = current->titlePointer->getTitleTimeLength() / n; // duzina jednog novog titla 
					int beginTime = current->titlePointer->getTitleBeginningTime(); // pocetak u ms prvog titla
					
					string text = current->titlePointer->getText();

					while (1)//izbacivanje '\n' iz teksta i menjanje sa ' '
					{
						int pos = text.find('\n');

						if (pos == string::npos)
							break;

						text[pos] = ' ';
					}
					
					int i = 0;
					int words = 0; // izracunavanje ukupnog broja reci u titlu 
					while (text[i] != '\0') {
						if (text[i] == '<' && text[i + 2] == '>') i += 3;
						if (text[i] == '<' && text[i + 3 == '>']) i += 4;
						if (text[i] == ' ') words++;
						i++;
					}
					words++;

					int m = words / n; // broj reci po titlu
					if (m * n <= words) m++;

					i = 0;
					// azuriranje trenutnog titla (podesavanje novog krajnjeg vremena i nov tekst)
					string newText = readWords(text, m, i);
					current->titlePointer->setText(newText);
					current->titlePointer->setEndingTime(length);
					beginTime += length;
					//obrada
					for (int j = 0; j < n-1; j++) {
						string titleText = readWords(text, m, i);
						insertSubtitle(beginTime, length, titleText);
						Node* tmp = this->head;
						while (tmp) { //prelomljeni titl zadrzava selekciju, tmp-om trazim svaki novi titl
							if (tmp->titlePointer->getTitleBeginningTime() == beginTime) {
								tmp->titlePointer->selectTitle();
								break;
							}
							tmp = tmp->next;
						}
						beginTime += length;
					}
				}
			}

			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
	else {
		Node* current = this->head;
		while (current) {

			if (current->titlePointer->getTitleTimeLength() >= max) {

				int n = current->titlePointer->getTitleTimeLength() / max;
				while (n * max <= current->titlePointer->getTitleTimeLength()) n++;
				

				int length = current->titlePointer->getTitleTimeLength() / n;  
				int beginTime = current->titlePointer->getTitleBeginningTime(); 

				string text = current->titlePointer->getText();

				while (1)
				{
					int pos = text.find('\n');

					if (pos == string::npos)
						break;

					text[pos] = ' ';
				}

				int i = 0;
				int words = 0;  
				while (text[i] != '\0') {
					if (text[i] == '<' && text[i + 2] == '>') i += 3;
					if (text[i] == '<' && text[i + 3 == '>']) i += 4;
					if (text[i] == ' ') words++;
					i++;
				}
				words++;

				int m = words / n; 
				if (m * n <= words) m++;

				i = 0;
				
				string newText = readWords(text, m, i);
				current->titlePointer->setText(newText);
				current->titlePointer->setEndingTime(length);
				beginTime += length;
				
				for (int j = 0; j < n-1; j++) {
					string titleText = readWords(text, m, i);
					insertSubtitle(beginTime, length, titleText);
					beginTime += length;
				}
			}


		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
}

void SubtitleEditor::undo()
{
	this->head->top->removeTop();
}

void SubtitleEditor::shiftForward(int ms)
{
	Node* current = this->head;
	if (this->listSelected) {
		while (current) {
			if (current->titlePointer->getSelection() == true) {
				current->titlePointer->changeTitleTime(ms);
			}
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
	else {
		while (current) {
			current->titlePointer->changeTitleTime(ms);
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
}

void SubtitleEditor::shiftBackward(int ms)
{
	int nms = -ms;

	Node* current = this->head;
	if (this->listSelected) {
		while (current) {
			if (current->titlePointer->getSelection() == true) {
				current->titlePointer->changeTitleTime(nms);
			}
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}
	else {
		while (current) {
			current->titlePointer->changeTitleTime(nms);
			current = current->next;
		}
		string str = loadString();
		this->head->top->addToStack(str);
	}

}

void SubtitleEditor::insertSubtitle(int start, int length, string text)
{
	//kreiranje titla koji treba da se umetne
	Node* insertion = new Node();
	insertion->titlePointer = new Title(start, length, text);
	insertion->next = nullptr;

	Node* current = this->head;
	while (current) {
		//ako moze da se ubaci, isprevezuj pokazivace i azuriraj redne brojeve titlova
		if (current->titlePointer->getTitleEndingTime() <= start && current->next->titlePointer->getTitleBeginningTime() >= start + length) {
			insertion->next = current->next;
			current->next = insertion;
			
			//azuriranje rednih brojeva ostalih titlova iza umetnutog
			int nextSerialNumber = current->titlePointer->getSerial() + 1;

			Node* currentCopy = current->next;
			while (currentCopy) {
				currentCopy->titlePointer->setTitleSerial(nextSerialNumber);
				nextSerialNumber++;
				currentCopy = currentCopy->next;
			}
			break;
		}
		current = current->next;
	};

	string str = loadString();
	this->head->top->addToStack(str);
}

void SubtitleEditor::deleteSubtitles()
{
	if (this->head == nullptr)
		return;
	if (listSelected == false)
		return;

	int serial = this->head->titlePointer->getSerial();

	//izbacivanje titlova od pocetka pa sve dok postoji selekcija
	while (this->head && this->head->titlePointer->getSelection()) {
		Node* tmp = this->head;
		this->head = this->head->next;
		delete tmp->titlePointer;
		delete tmp;

	}

	if (this->head == nullptr)
		return;

	//namestanje novog head-a
	this->head->titlePointer->setTitleSerial(serial);

	Node* current = this->head;

	//izbacivanje svih ostalih selektovanih titlova
	while (current != nullptr && current->next != nullptr) {
		if (current->next->titlePointer->getSelection() == true) {
			Node* tmp = current->next;
			current->next = tmp->next;
			delete tmp->titlePointer;
			delete tmp;
		}
		else {
			current = current->next;
		}
	}

	//azuriranje rednih brojeva preostalih titlova
	current = this->head->next;
	serial++;

	while (current != nullptr) {
		current->titlePointer->setTitleSerial(serial);
		serial++;
		current = current->next;
	}
	
	this->listSelected = false; //ne postoji selekcija, jer su svi selektovani titlovi uklonjeni
	
	string str = loadString();
	this->head->top->addToStack(str);
	
	return;
}

void SubtitleEditor::merge(string subtitles)
{
	SubtitleEditor* headTwo = new SubtitleEditor();
	headTwo->loadSubtitles(subtitles);

	//pronalazenje poslednjeg titla u prvom head-u i nadovezivanje novog na kraj prvog 
	Node* last = this->head;
	while (last->next) last = last->next;
	last->next = headTwo->head;

	//azuriranje rednih brojeva titlova (nije receno da moraju i vremena da se azuriraju)
	int nextSerialNumber = last->titlePointer->getSerial() + 1;

	Node* currentCopy = last->next;
	while (currentCopy) {
		currentCopy->titlePointer->setTitleSerial(nextSerialNumber);
		nextSerialNumber++;
		currentCopy = currentCopy->next;
	}

	string str = loadString();
	this->head->top->addToStack(str);

	return;
}


bool SubtitleEditor::isOverlapped(string text, int start, int end)
{
	for (int i = start; i < end - 4; i++) {
		string pom1 = "" + text[i] + text[i + 1] + text[i + 2];
		string pom2 = "" + text[i] + text[i + 1] + text[i + 2] + text[i + 3];

		if (pom1 == "<b>" || pom2 == "</b>" || pom1 == "<i>" || pom2 == "</i>" || pom1 == "<u>" || pom2 == "</u>") {
			return true;
		}
	}

	return false;
}

bool SubtitleEditor::NeedsToBeFixed(string str, int max)
{
	str.append("\n");
	int i = 0;
	int cntChar = 0;
	while (i < str.length()) {
		if (str[i] == '<' && str[i + 2] == '>') {
			i += 3;
			continue;
		}
		if (str[i] == '<' && str[i + 3] == '>') {
			i += 4;
			continue;
		}
		if (str[i] == '\n') cntChar = 0;
		else if (str[i] != ' ') cntChar++;

		if (cntChar == max) return true;
		else i++;
	}

	if (cntChar == max) return true;
	else return false;
}

string SubtitleEditor::readWords(string text, int number, int& counter)
{
	string str = "";
	int wordsRead = 0;
	while (1) {
		if (text[counter] == ' ') wordsRead++;
		if (wordsRead == number || text[counter] == '\0') {
			str.push_back('\n');
			counter++;
			break;
		}
		str.push_back(text[counter]);
		counter++;
	}
	
	return str;
}

string SubtitleEditor::loadString()
{
	string str;
	Node* tmp = this->head;

	while (tmp != nullptr) {
		str.append(to_string(tmp->titlePointer->getSerial()));
		str.append("\n");
		str.append(tmp->titlePointer->getTitleTimes());
		str.append(tmp->titlePointer->getText());
		str.append("\n");
		str.append("\n");

		tmp = tmp->next;
	}
	return str;
}
