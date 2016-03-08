#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

class Meeting { //represents a certain meeting of a class at a certain location for one hour on a certain day
	string location; //phyiscal location (building and room number)
	int period; //Number between 1 and 14 with 12, 13 and 14 representing periods E1, E2, and E3 respectively
	char day; //Day of the week. M = Monday, T = Tuesday, W = Wednesday. R = Thursday, F = Friday
	Meeting* next; //Pointer to the next meeting of the class
	public:
		Meeting() {next=NULL;};
		void setLocation(string newLoc) {location=newLoc;};
		string getLocation() {return location;};
		void setPeriod(int newPeriod) {period=newPeriod;};
		int getPeriod() {return period;};
		void setDay(char newDay) {day=newDay;};
		char getDay() {return day;};
		void setNext(Meeting* newNext) {next=newNext;};
		Meeting* getNext() {return next;};
		void print();
};

class MeetingList { //linked list of Meeting to represent all times when a class meets
	Meeting* firstMeeting; //Pointer to the first meeting of a course.
	public:
		MeetingList() {firstMeeting=NULL;};
		Meeting* getFirst() {return firstMeeting;};
		void setFirst(Meeting* newFirst) {firstMeeting=newFirst;};
		void add(Meeting* newLast);
		void print();
};

class Section { //represents a certain section of a course inclding all of the times it meets.
	string code;
	string name;
	string num;
	MeetingList alltimes;
	int credits;
	string professor;
	Section* next;
	Section* prev;
	public:
		Section() {next=NULL;prev=NULL;};
		string getCode() {return code;};
		void setCode(string newCode) {code=newCode;};
		string getName() {return name;};
		void setName(string newName) {name=newName;};
		string getNum() {return num;};
		void setNum(string newNum) {num=newNum;};
		int getCredits() {return credits;};
		void setCredits(int newCredits) {credits=newCredits;};
		string getProfessor() {return professor;};
		void setProfessor(string newProf) {professor=newProf;};
		void print();
		void addMeeting(char newDay,int newPeriod,string newLoc);
		Section* getNext() {return next;};
		Section* getPrev() {return prev;};
		void setNext(Section* newNext) {next=newNext;};
		void setPrev(Section* newPrev) {prev=newPrev;};
		bool doesConflict(Section* anotherSection);
		MeetingList getMeetings() {return alltimes;};
		void setMeetings(MeetingList newMeetings) {alltimes=newMeetings;};
};

/* Doubly linked list of Sections that can either be of the same course or not.
For example, a schedule with one section of each course (output of method to create schedule)
is an instance of a SectionList. All the sections of a particlar course is another instance
of a SectionList. */
class SectionList {
	Section* firstSection;
	string code;
	string name;
	public:
		SectionList() {firstSection=NULL;};
		Section* getHead() {return firstSection;};
		Section* getLast();
		void setHead(Section* newHead) {firstSection=newHead;};
		string getCode() {return code;};
		void setCode(string newCode) {code=newCode;};
		string getName() {return name;};
		void setName(string newName) {name=newName;};
		void addSection(Section* newSection);
		int getTotalCredits();
		int getSize();
		void print();
};

class Course { //Contains a SectionList with many Sections of the same Course.
	SectionList allSections;
	string code;
	string name;
	Course* nextCourse;
	Course* prevCourse;
	public:
		Course() {nextCourse=NULL;prevCourse=NULL;};
		string getCode() {return code;};
		void setCode(string newCode) {code=newCode;};
		string getName() {return name;};
		void setName(string newName) {name=newName;};
		Course* getNext() {return nextCourse;};
		Course* getPrev() {return prevCourse;};
		void setNext(Course* newNext) {nextCourse=newNext;};
		void setPrev(Course* newPrev) {prevCourse=newPrev;};
		SectionList getSections() {return allSections;};
		void addSection(Section* newSection) {allSections.addSection(newSection);};
		void print();
};

class CourseList { //Doubly linked list of Courses. This object is passed to the method to create a scedule.
	Course* firstCourse;
	public:
		CourseList() {firstCourse=NULL;};
		void setFirstCourse(Course* newFirst) {firstCourse=newFirst;};
		Course* getFirstCourse() {return firstCourse;};
		void addCourse(Course* newCourse);
		int getSize();
		void print();
};


void Meeting::print() {
	cout<<day<<" "<<period<<" "<<location<<endl;
}

void MeetingList::add(Meeting* newLast) { //Adds a meeting to a MeetingList.
	Meeting* temp=firstMeeting;
	if (temp==NULL) {
		setFirst(newLast);
	}
	else {
		while (temp->getNext()!=NULL) {
			temp=temp->getNext();
		}
		temp->setNext(newLast);
	}
}

void MeetingList::print() { //Prints the meetings of a particular section.
	Meeting* temp=firstMeeting;
	if (temp==NULL) {
		cout<<"NO MEETINGS AT ALL"<<endl;
	}
	else {
		while (temp!=NULL) {
			temp->print();
			temp=temp->getNext();
		}
	}
}

void Section::addMeeting(char newDay,int newPeriod,string newLoc) {//Constructs a Section by adding a Meeting.
	Meeting* temp=new Meeting();
	temp->setDay(newDay);
	temp->setPeriod(newPeriod);
	temp->setLocation(newLoc);
	alltimes.add(temp);
}

void Section::print() {  //Prints the information for each section.
	cout<<code<<": "<<name<<endl;
	cout<<"Section "<<num<<":"<<endl;
	cout<<credits<<" credits"<<endl;
	cout<<"Professor: "<<professor<<endl;
	alltimes.print();
}

bool Section::doesConflict(Section* anotherSection) {//Determines if any of the meeting times of two sections coincide.
	MeetingList primar=alltimes;
	MeetingList second=anotherSection->alltimes;
	Meeting* temp1=primar.getFirst();
	Meeting* temp2=second.getFirst();
	while (temp1!=NULL) {
		if (temp1->getPeriod()==temp2->getPeriod()&&temp1->getDay()==temp2->getDay()) {
			return true;
		}
		temp2=temp2->getNext();
		if (temp2==NULL) {
			temp1=temp1->getNext();
			temp2=second.getFirst();
		}
	}
	return false;
}

Section* SectionList::getLast() {	//Finds the last section in a SectionList
	Section* temp=firstSection;
	if (temp==NULL) {		//Case if there are no Sections in the SectionList.
		return NULL;
	}

	while (temp->getNext()!=NULL) {	//Otherwise traverses until it finds the last Section.
		temp=temp->getNext();
	}
	return temp;
}

void SectionList::addSection(Section* newSection) {//Adds a section to a SectionList
	Section* temp=firstSection;
	if (temp==NULL) { 		           //Case when the SectionList is currently empty.
		setHead(newSection);
	}
	else if (temp->getNext()==NULL) {	  //Case when there is a single Section in the SectionList.
		temp->setNext(newSection);
		newSection->setPrev(temp);
	}
	else {					  //Otherwise traverses and appends to the end of the list.
		while (temp->getNext()!=NULL) {
			temp=temp->getNext();
		}
		temp->setNext(newSection);
		newSection->setPrev(temp);
	}
}

int SectionList::getTotalCredits() {//Calculates the total number of credits in a SectionList
	Section* temp=firstSection;
	if (temp==NULL) {
		return 0;
	}
	int total=0;
	while (temp!=NULL) {
		total+=temp->getCredits();
		temp=temp->getNext();
	}
	return total;
}

int SectionList::getSize() { // Traverses the SectionList and counts how many sections it contains
	Section* temp=firstSection;
	if (temp==NULL) {
		return 0;
	}
	int length=0;
	while (temp!=NULL) {
		length+=1;
		temp=temp->getNext();
	}
	return length;
}

void SectionList::print() {//Traverses all the sections in the section list and prints their details.
	Section* temp=firstSection;
	if (temp==NULL) {
		cout<<"No sections available for "<<code<<": "<<name<<endl;
	}
	else {
		cout<<"Printing all sections for "<<code<<": "<<name<<endl;
		while (temp!=NULL) {
			temp->print();
			temp=temp->getNext();
		}
	}
}

void Course::print() {//Prints the code and name of each course and then prints each of the sections of the course
	cout<<code<<": "<<name<<endl;
	allSections.print();
}

void CourseList::addCourse(Course* newCourse) { //Adds a course to the CourseList
	Course* temp=firstCourse;
	if (temp==NULL) {
		setFirstCourse(newCourse);
	}
	else {
		while (temp->getNext()!=NULL) {
			temp=temp->getNext();
		}
		temp->setNext(newCourse);
	}
}

int CourseList::getSize() {//Calculates the number of courses in the CourseList.
	Course* temp=firstCourse;
	if (temp==NULL) {
		return 0;
	}
	int length=0;
	while (temp!=NULL) {
		length+=1;
		temp=temp->getNext();
	}
	return length;
}

void CourseList::print() {//Prints all the courses in the CourseList.
	Course* temp=firstCourse;
	if (temp==NULL) {
		cout<<"NO COURSES"<<endl;
	}
	else {
		while (temp!=NULL) {
			temp->print();
			temp=temp->getNext();
		}
	}
}

/* Finds all the department pages where each of the prefixes can be found.
Some prefixes can be found on more than one department page and each department page may contain  multiple prefixes.
ASN, BCN, FES, HIN, ICM, INP, KOR, REA, SCA, SCT, VTW, VTT not allowed...no valid departments*/
string findDepts(string course) {
	string prefix=course.substr(0,3); //The prefix is the first three letters of the course code.
	if(prefix== "ABE") {
		return "agribioe.htm chemical.htm";
	}
	else if(prefix== "ABT") {
		return "langarab.htm";
	}
	else if(prefix== "ACG") {
	    return "accounts.htm";
	}
	else if(prefix== "ADV") {
	    return "advertis.htm masscomm.htm";
	}
	else if(prefix== "AEB") {
	    return "agriture.htm agriopma.htm foodreso.htm mechaero.htm";
	}
	else if(prefix== "AEC") {
	    return "agriedco.htm";
	}
	else if(prefix== "AEE") {
	    return "agriture.htm foodreso.htm";
	}
	else if(prefix== "AFA") {
	    return "afrstudi.htm";
	}
	else if(prefix== "AFH") {
	    return "afrstudi.htm historys.htm";
	}
	else if(prefix== "AFR") {
	    return "miliafor.htm";
	}
	else if(prefix== "AFS") {
	    return "afrstudi.htm anthropo.htm";
	}
	else if(prefix== "AGG") {
	    return "agriedco.htm agronomy.htm";
	}
	else if(prefix== "AGR") {
	    return "agronomy.htm";
	}
	else if(prefix== "AHM") {
	    return "afrstudi.htm langaaaa.htm ";
	}
	else if(prefix== "AKA") {
	    return "afrstudi.htm langakan.htm langaaaa.htm";
	}
	else if(prefix== "ALS") {
	    return "agriedco.htm agriopma.htm agriture.htm agronomy.htm animalsc.htm entomolo.htm envrhort.htm foodreso.htm horticul.htm plantpat.htm soilwatr.htm";
	}
	else if(prefix== "AMH") {
	    return "afrstudi.htm historys.htm langaaaa.htm";
	}
	else if(prefix== "AML") {
	    return "englishs.htm";
	}
	else if(prefix== "ANG") {
	    return "anthropo.htm";
	}
	else if(prefix== "ANS") {
	    return "animalsc.htm";
	}
	else if(prefix== "ANT") {
	    return "anthropo.htm religion.htm";
	}
	else if(prefix== "AOM") {
	    return "agribioe.htm agriopma.htm";
	}
	else if(prefix== "APK") {
	    return "applyphys.htm healthed.htm tourismr.htm";
	}
	else if(prefix== "ARA") {
	    return "afrstudi.htm langarab.htm";
	}
	else if(prefix== "ARC") {
	    return "architec.htm desconpl.htm";
	}
	else if(prefix== "ARE") {
	    return "arthisto.htm educattl.htm";
	}
	else if(prefix== "ARH") {
	    return "arthisto.htm interdis.htm";
	}
	else if(prefix== "ART") {
	    return "arthisto.htm finearts.htm";
	}
	else if(prefix== "ASH") {
	    return "historys.htm";
	}
	else if(prefix== "ASL") {
	    return "speechlh.htm";
	}
	/*
	else if(prefix== "ASN") {
	    return "";
	}
	*/
	else if(prefix== "AST") {
	    return "astronom.htm bibozozo.htm physicss.htm";
	}
	else if(prefix== "ATE") {
	    return "animalsc.htm";
	}
	else if(prefix== "ATR") {
	    return "applyphys.htm";
	}
	else if(prefix== "BCC") {
		    return "mediaaaa.htm";
	}
	else if(prefix== "BCH") {
	    return "agriture.htm bibozobo.htm envrhort.htm medibioc.htm";
	}/*
	else if(prefix== "BCN") {
	    return "";
	}
	*/
	else if(prefix== "BME") {
	    return "biomedeg.htm chemical.htm electric.htm material.htm mediradi.htm";
	}
	else if(prefix== "BMS") {
	    return "mediaaaa.htm";
	}
	else if(prefix== "BOT") {
	    return "bibozobo.htm bibozozo.htm geoscien.htm";
	}
	else if(prefix== "BSC") {
	    return "bibozobi.htm bibozozo.htm healthpr.htm microbio.htm";
	}
	else if(prefix== "BUL") {
	    return "manageme.htm";
	}
	else if(prefix== "CAP") {
	    return "computer.htm";
	}
	else if(prefix== "CAS") {
	    return "speechlh.htm";
	}
	else if(prefix== "CAT") {
	    return "spaporpo.htm spaporsp.htm";
	}
	else if(prefix== "CBH") {
	    return "psycholo.htm";
	}
	else if(prefix== "CCE") {
	    return "civcseng.htm";
	}
	else if(prefix== "CCJ") {
	    return "soccrimi.htm";
	}
	else if(prefix== "CDA") {
	    return "computer.htm";
	}
	else if(prefix== "CEG") {
	    return "civcseng.htm";
	}
	else if(prefix== "CEN") {
	    return "computer.htm";
	}
	else if(prefix== "CES") {
	    return "civcseng.htm";
	}
	else if(prefix== "CGN") {
	    return "civcseng.htm";
	}
	else if(prefix== "CGS") {
	    return "computer.htm industri.htm";
	}
	else if(prefix== "CHI") {
	    return "langchin.htm";
	}
	else if(prefix== "CHM") {
	    return "chemical.htm chemistr.htm";
	}
	else if(prefix== "CHT") {
	    return "langaaaa.htm langchin.htm";
	}
	else if(prefix== "CHW") {
	    return "langchin.htm";
	}
	else if(prefix== "CIS") {
	    return "computer.htm";
	}
	else if(prefix== "CJC") {
	    return "soccrimi.htm";
	}
	else if(prefix== "CJE") {
	    return "soccrimi.htm";
	}
	else if(prefix== "CJJ") {
	    return "soccrimi.htm";
	}
	else if(prefix== "CJL") {
	    return "soccrimi.htm";
	}
	else if(prefix== "CLA") {
	    return "classicc.htm";
	}
	else if(prefix== "CLP") {
	    return "clinicap.htm psycholo.htm";
	}
	else if(prefix== "CLT") {
	    return "classicc.htm religion.htm";
	}
	else if(prefix== "CNT") {
	    return "computer.htm";
	}
	else if(prefix== "COM") {
	    return "writtenc.htm speechlh.htm masscomm.htm";
	}
	else if(prefix== "COP") {
	    return "computer.htm industri.htm";
	}
	else if(prefix== "COT") {
	    return "computer.htm chemical.htm";
	}
	else if(prefix== "CPO") {
	    return "politica.htm";
	}
	else if(prefix== "CRW") {
	    return "englishs.htm";
	}
	else if(prefix== "CTS") {
	    return "computer.htm";
	}
	else if(prefix== "CWR") {
	    return "agribioe.htm civcseng.htm ";
	}
	else if(prefix== "CZE") {
	    return "langczec.htm";
	}
	else if(prefix== "CZT") {
	    return "langczec.htm";
	}
	else if(prefix== "DAA") {
	    return "tourismr.htm theadanc.htm";
	}
	else if(prefix== "DAE") {
	    return "theadanc.htm";
	}
	else if(prefix== "DAN") {
	    return "theadanc.htm";
	}
	else if(prefix== "DCP") {
	    return "desconpl.htm urbanreg.htm";
	}
	else if(prefix== "DEN") {
	    return "denodiag.htm";
	}
	else if(prefix== "DEP") {
	    return "clinicap.htm psycholo.htm";
	}
	else if(prefix== "DIE") {
	    return "foodscie.htm";
	}
	else if(prefix== "DIG") {
	    return "arthisto.htm digworld.htm finearts.htm musicapp.htm";
	}
	else if(prefix== "DUT") {
	    return "langdutc.htm";
	}
	else if(prefix== "EAB") {
	    return "psycholo.htm";
	}
	else if(prefix== "EAP") {
	    return "linguist.htm";
	}
	else if(prefix== "EAS") {
	    return "mechaero.htm";
	}
	else if(prefix== "EBD") {
	    return "educasep.htm";
	}
	else if(prefix== "ECH") {
	    return "chemical.htm material.htm";
	}
	else if(prefix== "ECO") {
	    return "economic.htm";
	}
	else if(prefix== "ECP") {
	    return "economic.htm";
	}
	else if(prefix== "ECS") {
	    return "economic.htm";
	}
	else if(prefix== "EDA") {
	    return "educahdo.htm";
	}
	else if(prefix== "EDE") {
	    return "educattl.htm";
	}
	else if(prefix== "EDF") {
	    return "educasep.htm educattl.htm";
	}
	else if(prefix== "EDG") {
	    return "educattl.htm";
	}
	else if(prefix== "EDH") {
	    return "educahdo.htm";
	}
	else if(prefix== "EDM") {
	    return "educattl.htm";
	}
	else if(prefix== "EDP") {
	    return "educahdo.htm";
	}
	else if(prefix== "EDS") {
	    return "educahdo.htm";
	}
	else if(prefix== "EEC") {
	    return "educasep.htm";
	}
	else if(prefix== "EEE") {
	    return "electric.htm engingen.htm";
	}
	else if(prefix== "EEL") {
	    return "electric.htm";
	}
	else if(prefix== "EES") {
	    return "environm.htm";
	}
	else if(prefix== "EEX") {
	    return "educasep.htm";
	}
	else if(prefix== "EGI") {
	    return "educasep.htm";
	}
	else if(prefix== "EGM") {
	    return "civcseng.htm mechaero.htm";
	}
	else if(prefix== "EGN") {
	    return "biomedeg.htm computer.htm";
	}
	else if(prefix== "EGS") {
	    return "engingen.htm";
	}
	else if(prefix== "EIN") {
	    return "industri.htm";
	}
	else if(prefix== "EMA") {
	    return "material.htm";
	}
	else if(prefix== "EME") {
	    return "educattl.htm";
	}
	else if(prefix== "EML") {
	    return "nuclearr.htm";
	}
	else if(prefix== "EMS") {
	    return "medigene.htm";
	}
	else if(prefix== "ENC") {
	    return "writtenc.htm englishs.htm writprog.htm";
	}
	else if(prefix== "ENG") {
	    return "englishs.htm environm.htm writprog.htm";
	}
	else if(prefix== "ENL") {
	    return "englishs.htm";
	}
	else if(prefix== "ENT") {
	    return "finances.htm";
	}
	else if(prefix== "ENU") {
	    return "biomedeg.htm mediradi.htm microbio.htm nuclearr.htm";
	}
	else if(prefix== "ENV") {
	    return "civcseng.htm nuclearr.htm";
	}
	else if(prefix== "ENY") {
	    return "entomolo.htm";
	}
	else if(prefix== "EOC") {
	    return "civcseng.htm";
	}
	else if(prefix== "EPH") {
	    return "educasep.htm";
	}
	else if(prefix== "ESC") {
	    return "geoscien.htm";
	}
	else if(prefix== "ESE") {
	    return "educattl.htm";
	}
	else if(prefix== "ESI") {
	    return "engingen.htm industri.htm";
	}
	else if(prefix== "EUH") {
	    return "historys.htm";
	}
	else if(prefix== "EUS") {
	    return "european.htm";
	}
	else if(prefix== "EVR") {
	    return "envrhort.htm natresou.htm";
	}
	else if(prefix== "EVS") {
	    return "natresou.htm";
	}
	else if(prefix== "EXP") {
	    return "psycholo.htm";
	}
	else if(prefix== "FAS") {
	    return "fishsfrc.htm forresco.htm";
	}
	/*
	else if(prefix== "FES") {
	    return "";
	}
	*/
	else if(prefix== "FIL") {
	    return "journali.htm masscomm.htm";
	}
	else if(prefix== "FIN") {
	    return "finances.htm";
	}
	else if(prefix== "FLE") {
	    return "educattl.htm langaaaa.htm";
	}
	else if(prefix== "FNR") {
	    return "forresco.htm wildlife.htm";
	}
	else if(prefix== "FOL") {
	    return "spaporsp.htm langaaaa.htm langfren.htm";
	}
	else if(prefix== "FOR") {
	    return "forresco.htm";
	}
	else if(prefix== "FOS") {
	    return "foodscie.htm";
	}
	else if(prefix== "FOT") {
	    return "latiname.htm";
	}
	else if(prefix== "FOW") {
	    return "spaporpo.htm spaporsp.htm langfren.htm langhait.htm langital.htm";
	}
	else if(prefix== "FRC") {
	    return "horticul.htm";
	}
	else if(prefix== "FRE") {
	    return "langfren.htm";
	}
	else if(prefix== "FRT") {
	    return "langfren.htm";
	}
	else if(prefix== "FRW") {
	    return "langfren.htm";
	}
	else if(prefix== "FYC") {
	    return "agriture.htm famscien.htm";
	}
	else if(prefix== "GEA") {
	    return "geograph.htm";
	}
	else if(prefix== "GEB") {
	    return "business.htm finances.htm";
	}
	else if(prefix== "GEO") {
	    return "geoscien.htm geograph.htm";
	}
	else if(prefix== "GER") {
	    return "langaaaa.htm langdutc.htm langgerm.htm";
	}
	else if(prefix== "GET") {
	    return "langgerm.htm";
	}
	else if(prefix== "GEW") {
	    return "langgerm.htm";
	}
	else if(prefix== "GEY") {
	    return "psycholo.htm healthed.htm rehbsci2.htm mediaaaa.htm";
	}
	else if(prefix== "GIS") {
	    return "geograph.htm";
	}
	else if(prefix== "GLY") {
	    return "bibozozo.htm geoscien.htm geograph.htm";
	}
	else if(prefix== "GMS") {
	    return "biostati.htm veterina.htm epidemio.htm";
	}
	else if(prefix== "GMT") {
	    return "classicc.htm";
	}
	else if(prefix== "GRA") {
	    return "arthisto.htm";
	}
	else if(prefix== "GRE") {
	    return "classicg.htm";
	}
	else if(prefix== "GRK") {
	    return "classicg.htm";
	}
	else if(prefix== "GRW") {
	    return "classicg.htm";
	}
	else if(prefix== "HAI") {
	    return "langhait.htm";
	}
	else if(prefix== "HAT") {
	    return "langhait.htm";
	}
	else if(prefix== "HBR") {
	    return "langhebr.htm";
	}
	else if(prefix== "HBT") {
	    return "langhebr.htm";
	}
	else if(prefix== "HFT") {
	    return "tourismr.htm";
	}
	/*
	else if(prefix== "HIN") {
	    return "";
	}
	*/
	else if(prefix== "HIS") {
	    return "civcseng.htm historys.htm";
	}
	else if(prefix== "HLP") {
	    return "applyphys.htm healthed.htm tourismr.htm";
	}
	else if(prefix== "HMW") {
	    return "langhebr.htm";
	}
	else if(prefix== "HNG") {
	    return "european.htm";
	}
	else if(prefix== "HOS") {
	    return "agriture.htm envrhort.htm horticul.htm";
	}
	else if(prefix== "HPS") {
	    return "historys.htm philosop.htm";
	}
	else if(prefix== "HSA") {
	    return "economic.htm healthpr.htm healthsa.htm";
	}
	else if(prefix== "HSC") {
	    return "educattl.htm healthed.htm healthpr.htm mediphas.htm tourismr.htm";
	}
	else if(prefix== "HUM") {
	    return "afrstudi.htm arthisto.htm finearts.htm innovati.htm interdis.htm langaaaa.htm musicapp.htm";
	}
	else if(prefix== "HUN") {
	    return "foodscie.htm";
	}
	/*
	else if(prefix== "ICM") {
	    return "";
	}
	*/
	else if(prefix== "IDC") {
	    return "arthisto.htm finearts.htm";
	}
	else if(prefix== "IDH") {
	    return "chemistr.htm speechlh.htm historys.htm physicss.htm soccrimi.htm";
	}
	else if(prefix== "IDS") {
	    return "firstyrf.htm interdis.htm langaaaa.htm";
	}
	else if(prefix== "IND") {
	    return "interior.htm";
	}
	/*
	else if(prefix== "INP") {
	    return "";
	}
	*/
	else if(prefix== "INR") {
	    return "politica.htm";
	}
	else if(prefix== "INS") {
	    return "interdis.htm";
	}
	else if(prefix== "IPM") {
	    return "agronomy.htm plantpat.htm";
	}
	else if(prefix== "ISC") {
	    return "bibozobi.htm chemistr.htm interdisc.htm";
	}
	else if(prefix== "ISM") {
	    return "informat.htm";
	}
	else if(prefix== "ISS") {
	    return "interdis.htm";
	}
	else if(prefix== "ITA") {
	    return "langital.htm";
	}
	else if(prefix== "ITT") {
	    return "langital.htm";
	}
	else if(prefix== "ITW") {
	    return "langital.htm";
	}
	else if (prefix=="IUF") {
	    return "interdis.htm";
	}
	else if(prefix== "JOU") {
	    return "journali.htm masscomm.htm";
	}
	else if(prefix== "JPN") {
	    return "langjapa.htm";
	}
	else if(prefix== "JPT") {
	    return "langjapa.htm";
	}
	else if(prefix== "JPW") {
	    return "langaaaa.htm langjapa.htm";
	}
	else if(prefix== "JST") {
	    return "jewishst.htm";
	}
	/*
	else if(prefix== "KOR") {
	    return "";
	}
	*/
	else if(prefix== "LAA") {
	    return "landscap.htm";
	}
	else if(prefix== "LAE") {
	    return "educattl.htm englishs.htm";
	}
	else if(prefix== "LAH") {
	    return "historys.htm";
	}
	else if(prefix== "LAS") {
	    return "latiname.htm";
	}
	else if(prefix== "LAT") {
	    return "classicl.htm";
	}
	else if(prefix== "LAW") {
	    return "environm.htm lawschoo.htm";
	}
	else if(prefix== "LDE") {
	    return "envrhort.htm";
	}
	else if(prefix== "LEI") {
	    return "tourismr.htm";
	}
	else if(prefix== "LGL") {
	    return "afrstudi.htm langaaaa.htm";
	}
	else if(prefix== "LIN") {
	    return "speechlh.htm educasep.htm englishs.htm linguist.htm";
	}
	else if(prefix== "LIS") {
	    return "writtenc.htm";
	}
	else if(prefix== "LIT") {
	    return "englishs.htm jewishst.htm religion.htm";
	}
	else if(prefix== "LNW") {
	    return "classicl.htm";
	}
	else if(prefix== "MAA") {
	    return "mathemat.htm";
	}
	else if(prefix== "MAC") {
	    return "mathemat.htm";
	}
	else if(prefix== "MAD") {
	    return "mathemat.htm";
	}
	else if(prefix== "MAE") {
	    return "educattl.htm mathemat.htm";
	}
	else if(prefix== "MAN") {
	    return "finances.htm manageme.htm";
	}
	else if(prefix== "MAP") {
	    return "mathemat.htm";
	}
	else if(prefix== "MAR") {
	    return "marketin.htm";
	}
	else if(prefix== "MAS") {
	    return "mathemat.htm";
	}
	else if(prefix== "MAT") {
	    return "mathemat.htm";
	}
	else if(prefix== "MCB") {
	    return "microbio.htm phardyna.htm";
	}
	else if(prefix== "MDE") {
	    return "medipath.htm";
	}
	else if(prefix== "MDT") {
	    return "mediaaaa.htm";
	}
	else if(prefix== "MDU") {
	    return "medigene.htm medipsyc.htm medipath.htm";
	}
	else if(prefix== "MED") {
	    return "mediaaaa.htm";
	}
	else if(prefix== "MEL") {
	    return "epidemio.htm mediaaaa.htm";
	}
	else if(prefix== "MEM") {
	    return "historys.htm medievals.htm langgerm.htm";
	}
	else if(prefix== "MET") {
	    return "geograph.htm physicss.htm";
	}
	else if(prefix== "MGF") {
	    return "mathemat.htm";
	}
	else if(prefix== "MHF") {
	    return "mathemat.htm";
	}
	else if(prefix== "MHS") {
	    return "healthed.htm educahdo.htm rehbsci2.htm";
	}
	else if(prefix== "MMC") {
	    return "journali.htm masscomm.htm";
	}
	else if(prefix== "MSL") {
	    return "miliarmy.htm";
	}
	else if(prefix== "MTG") {
	    return "mathemat.htm";
	}
	else if(prefix== "MUC") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUE") {
	    return "educattl.htm musicapp.htm";
	}
	else if(prefix== "MUG") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUH") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUL") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUN") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUO") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUR") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUS") {
	    return "musicapp.htm";
	}
	else if(prefix== "MUT") {
	    return "musicapp.htm";
	}
	else if(prefix== "MVB") {
	    return "musicapp.htm";
	}
	else if(prefix== "MVK") {
	    return "musicapp.htm";
	}
	else if(prefix== "MVO") {
	    return "musicapp.htm";
	}
	else if(prefix== "MVP") {
	    return "musicapp.htm";
	}
	else if(prefix== "MVS") {
	    return "musicapp.htm";
	}
	else if(prefix== "MVV") {
	    return "musicapp.htm theadanc.htm";
	}
	else if(prefix== "MVW") {
	    return "musicapp.htm";
	}
	else if(prefix== "NEM") {
	    return "entomolo.htm";
	}
	else if(prefix== "NGR") {
	    return "nursings.htm";
	}
	else if(prefix== "NSC") {
	    return "milinavy.htm";
	}
	else if(prefix== "NUR") {
	    return "nursings.htm";
	}
	else if(prefix== "OCE") {
	    return "civcseng.htm geoscien.htm";
	}
	else if(prefix== "OCP") {
	    return "civcseng.htm";
	}
	else if(prefix== "ORH") {
	    return "envrhort.htm";
	}
	else if(prefix== "ORI") {
	    return "theadanc.htm";
	}
	else if(prefix== "OTH") {
	    return "healthpr.htm occupati.htm";
	}
	else if(prefix== "PAD") {
	    return "politica.htm";
	}
	else if(prefix== "PAS") {
	    return "mediphas.htm";
	}
	else if(prefix== "PCB") {
	    return "agronomy.htm bibozobi.htm bibozobo.htm bibozozo.htm forresco.htm geoscien.htm horticul.htm microbio.htm natresou.htm";
	}
	else if(prefix== "PCO") {
	    return "psycholo.htm";
	}
	else if(prefix== "PCY") {
	    return "arthisto.htm";
	}
	else if(prefix== "PEL") {
	    return "tourismr.htm";
	}
	else if(prefix== "PEM") {
	    return "tourismr.htm";
	}
	else if(prefix== "PEN") {
	    return "fishsfrc.htm tourismr.htm";
	}
	else if(prefix== "PEO") {
	    return "tourismr.htm";
	}
	else if(prefix== "PEQ") {
	    return "applyphys.htm healthed.htm tourismr.htm";
	}
	else if(prefix== "PET") {
	    return "applyphys.htm educattl.htm healthed.htm tourismr.htm";
	}
	else if(prefix== "PGY") {
	    return "arthisto.htm journali.htm";
	}
	else if(prefix== "PHA") {
	    return "mediphar.htm phardyna.htm";
	}
	else if(prefix== "PHC") {
	    return "biostati.htm clinicap.htm epidemio.htm healthed.htm healthpr.htm healthsa.htm publeat.htm";
	}
	else if(prefix== "PHH") {
	    return "philosop.htm";
	}
	else if(prefix== "PHI") {
	    return "philosop.htm religion.htm";
	}
	else if(prefix== "PHM") {
	    return "philosop.htm";
	}
	else if(prefix== "PHP") {
	    return "philosop.htm";
	}
	else if(prefix== "PHT") {
	    return "physical.htm";
	}
	else if(prefix== "PHY") {
	    return "physicss.htm";
	}
	else if(prefix== "PHZ") {
	    return "physicss.htm";
	}
	else if(prefix== "PKG") {
	    return "packagsc.htm";
	}
	else if(prefix== "PLP") {
	    return "bibozobo.htm plantpat.htm";
	}
	else if(prefix== "PLS") {
	    return "agriture.htm agronomy.htm envrhort.htm plantpat.htm";
	}
	else if(prefix== "PLT") {
	    return "langpoli.htm";
	}
	else if(prefix== "PLW") {
	    return "langpoli.htm";
	}
	else if(prefix== "PMA") {
	    return "entomolo.htm plantpat.htm";
	}
	else if(prefix== "POL") {
	    return "langpoli.htm";
	}
	else if(prefix== "POR") {
	    return "spaporpo.htm";
	}
	else if(prefix== "POS") {
	    return "latiname.htm politica.htm religion.htm";
	}
	else if(prefix== "POT") {
	    return "politica.htm";
	}
	else if(prefix== "POW") {
	    return "spaporpo.htm";
	}
	else if(prefix== "PPE") {
	    return "psycholo.htm";
	}
	else if(prefix== "PRT") {
	    return "spaporpo.htm";
	}
	else if(prefix== "PSB") {
	    return "psycholo.htm";
	}
	else if(prefix== "PSY") {
	    return "clinicap.htm psycholo.htm";
	}
	else if(prefix== "PUP") {
	    return "politica.htm";
	}
	else if(prefix== "PUR") {
	    return "masscomm.htm publicre.htm";
	}
	else if(prefix== "QMB") {
	    return "informat.htm";
	}
	else if(prefix== "RCS") {
	    return "healthpr.htm rehbsci2.htm";
	}
	/*
	else if(prefix== "REA") {
	    return "";
	}
	*/
	else if(prefix== "RED") {
	    return "educasep.htm educattl.htm englishs.htm writprog.htm";
	}
	else if(prefix== "REE") {
	    return "finances.htm";
	}
	else if(prefix== "REL") {
	    return "jewishst.htm philosop.htm religion.htm";
	}
	else if(prefix== "RLG") {
	    return "religion.htm";
	}
	else if(prefix== "RMI") {
	    return "finances.htm";
	}
	else if(prefix== "RSD") {
	    return "healthpr.htm occupati.htm rehbsci2.htm";
	}
	else if(prefix== "RTV") {
	    return "journali.htm masscomm.htm telecomm.htm";
	}
	else if(prefix== "RUS") {
	    return "langruss.htm";
	}
	else if(prefix== "RUT") {
	    return "langruss.htm";
	}
	else if(prefix== "RUW") {
	    return "langruss.htm";
	}
	/*
	else if(prefix== "SCA") {
	    return "";
	}
	*/
	else if(prefix== "SCE") {
	    return "educattl.htm";
	}
	/*
	else if(prefix== "SCT") {
	    return "";
	}
	*/
	else if(prefix== "SDS") {
	    return "healthed.htm educahdo.htm rehbsci2.htm";
	}
	else if(prefix== "SLS") {
	    return "educattl.htm firstyrf.htm interdis.htm";
	}
	else if(prefix== "SMT") {
	    return "educattl.htm";
	}
	else if(prefix== "SOP") {
	    return "psycholo.htm";
	}
	else if(prefix== "SPA") {
	    return "speechlh.htm rehbsci2.htm";
	}
	else if(prefix== "SPC") {
	    return "englishs.htm writtenc.htm";
	}
	else if(prefix== "SPM") {
	    return "applyphys.htm tourismr.htm";
	}
	else if(prefix== "SPN") {
	    return "spaporsp.htm";
	}
	else if(prefix== "SPS") {
	    return "educasep.htm";
	}
	else if(prefix== "SPT") {
	    return "spaporsp.htm";
	}
	else if(prefix== "SPW") {
	    return "spaporsp.htm";
	}
	else if(prefix== "SRK") {
	    return "religion.htm";
	}
	else if(prefix== "SSA") {
	    return "afrstudi.htm langyoru.htm";
	}
	else if(prefix== "SSE") {
	    return "educattl.htm";
	}
	else if(prefix== "SST") {
	    return "afrstudi.htm langaaaa.htm";
	}
	else if(prefix== "SSW") {
	    return "langswah.htm";
	}
	else if(prefix== "STA") {
	    return "statisti.htm agriture.htm publeat.htm epidemio.htm healthop.htm";
	}
	else if(prefix== "SUR") {
	    return "geomatic.htm";
	}
	else if(prefix== "SWA") {
	    return "afrstudi.htm langswah.htm";
	}
	else if(prefix== "SWS") {
	    return "soilwatr.htm";
	}
	else if(prefix== "SWW") {
	    return "langswah.htm";
	}
	else if(prefix== "SYA") {
	    return "agriture.htm socsocio.htm";
	}
	else if(prefix== "SYD") {
	    return "socsocio.htm";
	}
	else if(prefix== "SYG") {
	    return "agriture.htm socsocio.htm";
	}
	else if(prefix== "SYO") {
	    return "religion.htm socsocio.htm";
	}
	else if(prefix== "SYP") {
	    return "socsocio.htm";
	}
	else if(prefix== "TAX") {
	    return "accounts.htm";
	}
	else if(prefix== "THE") {
	    return "theadanc.htm";
	}
	else if(prefix== "TPA") {
	    return "theadanc.htm";
	}
	else if(prefix== "TPP") {
	    return "theadanc.htm";
	}
	else if(prefix== "TSL") {
	    return "educattl.htm linguist.htm";
	}
	else if(prefix== "TTE") {
	    return "civcseng.htm";
	}
	else if(prefix== "TUR") {
	    return "european.htm";
	}
	else if(prefix== "URP") {
	    return "urbanreg.htm";
	}
	else if(prefix== "VEC") {
	    return "horticul.htm";
	}
	else if(prefix== "VEM") {
	    return "veterina.htm";
	}
	else if(prefix== "VIC") {
	    return "masscomm.htm";
	}
	else if(prefix== "VME") {
	    return "animalsc.htm mediaaaa.htm publeat.htm veterina.htm";
	}
	/*
	else if(prefix== "VTN") {
	    return "";
	}
	*/
	/*
	else if(prefix== "VTT") {
	    return "";
	}
	*/
	else if(prefix== "WIS") {
	    return "forresco.htm wildlife.htm";
	}
	else if(prefix== "WOH") {
	    return "historys.htm";
	}
	else if(prefix== "WOL") {
	    return "afrstudi.htm langaaaa.htm";
	}
	else if(prefix== "WST") {
	    return "womenstu.htm";
	}
	else if(prefix== "XHO") {
	    return "afrstudi.htm langaaaa.htm";
	}
	else if(prefix== "YOR") {
	    return "afrstudi.htm langyoru.htm";
	}
	else if(prefix== "YOT") {
	    return "langyoru.htm";
	}
	else if(prefix== "YRW") {
	    return "langyoru.htm";
	}
	else if(prefix== "ZOO") {
	    return "bibozozo.htm microbio.htm";
	}
	else {
		return "";
	}
}

CourseList findCourses() {
	cout<<"How many courses would you like to have? ";
	int numOfCourses; //The number of courses the person wishes to look up.
	cin>>numOfCourses;
	string courseCode;//The course codes of the courses the user wishes to look up.
	string depts; //The departments in which that course code could possibly be found.
	CourseList allCourses;
	for (int i=0;i<numOfCourses;i++) { //Loop for each of the courses entered.
		cout<<"Enter course code (in form AAAXXXX where A is capital letter and X is number): ";
		cin>>courseCode; //Allow the user to type in that many course codes separated by the enter button.
		Course* tempCourse=new Course(); 
		tempCourse->setCode(courseCode);
		depts=findDepts(courseCode); //Finds the departments where that course code could potetially be found.
		int totalLength=depts.size(); //Length of string concatenation of potential departments.
		if (totalLength==0) { //If the course code cannot be found in any department.
			allCourses.addCourse(tempCourse);
			continue;
		}
		int index=0;
		bool found=false; //Determines if the course has been found.
		string fileName;
		while (index!=depts.size()&&found==false)  { //used to split up depts to determine HTML file names to open and parse
			fileName="";
			for (int i=index;i<depts.size();i++) {
				if (i==depts.size()-1) { //to succesfully get the last filename from string depts
					fileName+=depts.at(i);
					break;
				}
				else if (depts.at(i)==' ') { //adds characters until space is reached
					index=i+1;
					break;
				}
				fileName+=depts.at(i); //constructs fileName by adding characters
			}
			ifstream theFile; //reads the html file
			theFile.open(fileName.c_str()); //opens the file
			if (theFile.is_open()) { //makes sure the file exists and is open.
				string line; //the current line of text being read
				while (!theFile.eof()) { //read each line until the end of the document.
					if (line.find(courseCode)==-1) { //if the course code is not found.
						getline(theFile,line); //then move to the next line.
						continue;
					}
					//if the corresponding lab (i.e. CHM2045 vs. CHM2045L) is found, dont show it except with explicit search
					else if (line.at(line.find(courseCode)+7)=='L'&&courseCode.find("L")==-1 ) {
						getline(theFile,line);
						continue;
					}
					// otherwise the course code is found in that line.
					else {
						found=true;
						Section* tempNewSection=new Section(); //creates a new section
						tempNewSection->setCode(courseCode);//sets that temporary section to have the course code
						for (int i=0;i<4;i++) {
							getline(theFile,line);
						}
						tempNewSection->setNum(line); 
						getline(theFile,line);
						for (int i=0;i<line.size();i++) { 
							if (isdigit(line.at(i))) { //only adds credits if they are a digit and not any other char
								int cred=line.at(i)-'0';
								tempNewSection->setCredits(cred);
								break;
							}
						}
						getline(theFile,line); //now first line that has meeting times and locations
						string days=""; //string of te days the class will meet.
						int endDay=0;
						int startDay=line.find(">"); //finds the tag that appears before the first day in the HTML
						for (int i=startDay+1;i<line.size();i++) {
							if (line.at(i)=='<') { //keeps going until next tag is felt.
								endDay=i;
								break;
							}
							days+=line.at(i); //adds the letter before the '<' to the string of days
						}
						endDay+=22; //moves 22 spots

						//repeats same process for each of the times on each of those days. 
						int endTime=0; 
						string times="";
						for (int i=endDay;i<line.size();i++) {
							if (line.at(i)=='<') {
								endTime=i;
								break;
							}
							times+=line.at(i);
						}
						endTime+=22;

						//repeats the same process to determine the name of the building
						string building="";
						int endBuild=0;
						for (int i=endTime;i<line.size();i++) {
							if (line.at(i)=='<') {
								endBuild=i;
								break;
							}
							building+=line.at(i);
						}
						endBuild+=22;

						//and the same process again to determine the room number
						string roomNum="";
						for (int i=endBuild;i<line.size();i++) {
							if (line.at(i)=='<') {
								break;	
							}
							roomNum+=line.at(i);
						}
						string location=building+roomNum;//the location is the combination of building and room number
						for (int k=0;k<times.size();k++){
							if(times.at(k)=='E'){ 			//Converts period E1 to 12, E2 to 13, E3 to 14.
								if(times.at(k+1) == '1'){
									times.replace(k,2,"12");
								}
								if(times.at(k+1) == '2'){
									times.replace(k,2,"13");
								}
								if(times.at(k+1) == '3'){
									times.replace(k,2,"13");
								}	
							}
						}
						//cout<<times<<endl;
						string mento=""; //nickname of Christian Madali. 
						for (int abel=0;abel<days.size();abel++) { //Loop gets rid of white space. Abel is a dummy variable.
							if (days.at(abel)!=' ') {
								mento+=days.at(abel);
							}
						}
						days=mento; //days is now the same except without white space.
						for (int k=0;k<times.size();k++) {
							if(times.at(k)=='-'){  //replaces hyphenated times with times in between
								int average=stoi(times.substr(0,k))+1;
								string avg=to_string(average);
								if(average != stoi(times.substr(k+1))){
									times=times.substr(0,k)+avg+times.substr(k+1);
								}//cout<<times<<endl;
							}
						}					
						for (int i=0;i<days.size();i++) {
							string ttimes = times;
							if (ttimes.find("1113")!=-1) { //special case if no hyphen is found
								tempNewSection->addMeeting(days.at(i),11,location);
								tempNewSection->addMeeting(days.at(i),12,location);
								tempNewSection->addMeeting(days.at(i),13,location);
								break;
							}
							if (ttimes.find("8910")!=-1) { //another special case to make sure 10 is last. (period 10 would be printed first)
								tempNewSection->addMeeting(days.at(i),8,location);
								tempNewSection->addMeeting(days.at(i),9,location);
								tempNewSection->addMeeting(days.at(i),10,location);
								break;
							}
							if(ttimes.find("10") != -1){ //if a two digit number is found for period it will be remove from string and added to meeting.
								int m = ttimes.find("10");
								tempNewSection->addMeeting(days.at(i),stoi(ttimes.substr(m, 2)),location);
								ttimes.erase(m, 2);
							}
							if(ttimes.find("11") != -1){
								int m = ttimes.find("11");
								tempNewSection->addMeeting(days.at(i),stoi(ttimes.substr(m, 2)),location);
								ttimes.erase(m, 2);
							}
							if(ttimes.find("12") != -1){
								int m = ttimes.find("12");
								tempNewSection->addMeeting(days.at(i),stoi(ttimes.substr(m, 2)),location);
								ttimes.erase(m, 2);
							}
							if(ttimes.find("13") != -1){
								int m = ttimes.find("13");
								tempNewSection->addMeeting(days.at(i),stoi(ttimes.substr(m, 2)),location);
								ttimes.erase(m, 2);
							}
							if(ttimes.find("14") != -1){
								int m = ttimes.find("14");
								tempNewSection->addMeeting(days.at(i),stoi(ttimes.substr(m, 2)),location);
								ttimes.erase(m, 2);
							}
							for (int j=0;j<ttimes.size();j++) { //then only 1 digit numbers will be found and added
								if (isalpha(days.at(i))&&isdigit(ttimes.at(j))) {
								tempNewSection->addMeeting(days.at(i),(int)(ttimes.at(j)-'0'),location);
								}
							}
						}
						getline(theFile,line);
						getline(theFile,line);
						getline(theFile,line);
						string name="";
						for (int i=0;i<line.size();i++) {
							if (line.at(i)=='<') {
								break;
							}
							name+=line.at(i);
						}
						tempNewSection->setName(name); //finds name of course
						getline(theFile,line);
						getline(theFile,line);
						tempNewSection->setProfessor(line); //finds name of professor
						getline(theFile,line);

						//The following lines are repeated for instances in which a course has more than one meeting style
						//i.e. COP3503 has lectures and discussions.
						if (line.find("br")!=-1) {
							getline(theFile,line);
						}
						for (int i=0;i<3;i++) {
							getline(theFile,line);
						}
						while (line.find("<td></td>")!=-1) { //repeats much of previous lines due to similar algorthm in finding relevant data
							for (int i=0;i<5;i++) {
								getline(theFile,line);
							}
							days="";
							endDay=0;
							startDay=line.find(">");
							for (int i=startDay+1;i<line.size();i++) {
								if (line.at(i)=='<') {
									endDay=i;
									break;
								}
								days+=line.at(i);
							}
							endDay+=22;
							endTime=0;
							times="";
							for (int i=endDay;i<line.size();i++) {
								if (line.at(i)=='<') {
									endTime=i;
									break;
								}
								times+=line.at(i);
							}
							endTime+=22;
							building="";
							endBuild=0;
							for (int i=endTime;i<line.size();i++) {
								if (line.at(i)=='<') {
									endBuild=i;
									break;
								}
								building+=line.at(i);
							}
							endBuild+=22;
							roomNum="";
							for (int i=endBuild;i<line.size();i++) {
								if (line.at(i)=='<') {
									break;	
								}
								roomNum+=line.at(i);
							}
							location=building+roomNum;
							for (int k=0;k<times.size();k++){
								if(times.at(k)=='E'){ 			//Converts period E1 to 12, E2 to 13, etc.
									if(times.at(k+1) == 1){
										times.replace(k,2,"12");
									}
									if(times.at(k+1) == 2){
										times.replace(k,2,"13");
									}
									if(times.at(k+1) == 3){
										times.replace(k,2,"14");
									}	
								}
							}
							for (int k=0;k<times.size();k++) { //replaces hyphenated times with all times between
								if(times.at(k)=='-') {
								int before = stoi(times.substr(0,k));
								int after = stoi(times.substr(k+1));
								if(abs(after-before) > 1){
									int average =(before + after)/2;
									string avg = "" + average;
									times.replace(k, avg.size(), avg);
								}
							}
							}
							string days2="";
							for(int sam = 0; sam < days.size(); sam++) { //removes whitespace from days
								if(days.at(sam) != ' ') {
									days2+=days.at(sam);
								}
							}
							days=days2;
							for (int k=0;k<times.size();k++) {
								if (times.at(k)=='-') {
									int average=stoi(times.substr(0,k))+1;
									string avg=to_string(average);
									if(average!=stoi(times.substr(k+1))){
										times=times.substr(0,k)+avg+times.substr(k+1);
									}
								}
							}
							for (int i=0;i<days.size();i++) {
								if(times.find("10") != -1){ //handles two digit times
									int m = times.find("10");
									tempNewSection->addMeeting(days.at(i),stoi(times.substr(m, 2)),location);
									times.erase(m, 2);
								}
								if(times.find("11") != -1){
									int m = times.find("11");
									tempNewSection->addMeeting(days.at(i),stoi(times.substr(m, 2)),location);
									times.erase(m, 2);
								}
								if(times.find("12") != -1){
									int m = times.find("12");
									tempNewSection->addMeeting(days.at(i),stoi(times.substr(m, 2)),location);
									times.erase(m, 2);
								}
								if(times.find("13") != -1){
									int m = times.find("13");
									tempNewSection->addMeeting(days.at(i),stoi(times.substr(m, 2)),location);
									times.erase(m, 2);
								}
								if(times.find("14") != -1){
									int m = times.find("14");
									tempNewSection->addMeeting(days.at(i),stoi(times.substr(m, 2)),location);
									times.erase(m, 2);
								}
								for (int j=0;j<times.size();j++) {
									if (isalpha(days.at(i))&&isdigit(times.at(j))) {
										tempNewSection->addMeeting(days.at(i),(int)(times.at(j)-'0'),location);
									}
								}
							}
							for (int i=0;i<7;i++) {
								getline(theFile,line);
							}	
						}
					tempCourse->addSection(tempNewSection); //adds section to course
					}
				}
			}
		}
		allCourses.addCourse(tempCourse); //after finding sections for a particular course
	}
	return allCourses;
}

SectionList createSchedule(CourseList desList){ //Takes in a list of courses and returns a list of sections.
	SectionList schedule; //SectionList of the Sections that will be put on the schedule.
	int credits = 0; //Current number of credits in the schedule.
	int maxCredits = 18; //or could be set to an optional max willing to take
	Course* tmpCourse = desList.getFirstCourse(); //Starts with the first course (highest priority).
	while (tmpCourse != NULL){ //Traverses through all desired courses until reaches end.
		if(credits + tmpCourse->getSections().getHead()->getCredits() > maxCredits)
			break;	 //Will stop if maximum allowed/desired credits is reached.
		else{
			Section* tmpSection = tmpCourse->getSections().getHead(); //starts with the first section of the course.
			while(tmpSection != NULL){
				bool conflicts; //True if the section conflicts with already made schedule. False otherwise.
				conflicts = false; //Start out as false until a conflict is found.
				if(tmpSection->getMeetings().getFirst()== NULL){ // Do not allow a course to be added if no available sections can be found.
					conflicts = true;
				}
				Section* test = schedule.getHead(); // Starts at the beginning of the already created schedule and searches for timing conflicts.
				while(test != NULL){
					if(test->doesConflict(tmpSection)){
						conflicts = true; //If there is a conflict, the new section will not be added.
						break;	
					}
					test = test->getNext(); //Tests ALL of the sections already in the schedule
				}
				if(!conflicts){ //Only adds a course if there is not a timing conflict with another course.
					Section* tempSection=new Section(); //Creates a new instance of the section to code by value rather than reference.
					tempSection->setName(tmpSection->getName());//This is necessary because of the two possibilities for the interpretation
					tempSection->setNum(tmpSection->getNum());// of the SectionList object.
					tempSection->setProfessor(tmpSection->getProfessor());
					tempSection->setCredits(tmpSection->getCredits());
					tempSection->setCode(tmpSection->getCode());
					tempSection->setMeetings(tmpSection->getMeetings());
					schedule.addSection(tempSection); //Adds the section to the schedule.
					credits += tmpCourse->getSections().getHead()->getCredits(); //Adds the credits to the total.
					break;
				}
				tmpSection = tmpSection->getNext(); //Moves on to next section
			}
		
		}
		tmpCourse = tmpCourse->getNext();	//Moves on to next course.
	}
	//Following line prints out number of credits for schedule.
	cout << "Number of credits in schedule:  " <<  credits << endl;
	return schedule;
}

int main() {
	cout << "Would you like to " << endl << "    (A) Look Up Sections" << endl << "    (B) Create Schedule(Beta)? "; //gives user choie
	string choice;
	cin >>choice;
	if (choice == "B")
		createSchedule(findCourses()).print();
	else if (choice == "A")
		findCourses().print();
	else {
		cout<<"Choice must be \"A\" or \"B\""<<endl;
	}
}
