#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include "Credentials.h"
#include "Counter.h"
#include "Stopwatch.h"
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include "tools.h"

#pragma warning(disable:4996)

using namespace std;

void welcome(); // ask if public or staff
void staffMenu();
void publicMenu1();
void publicMenu2();
void publicMenu3();
void checkCombo();
void login();
void adminMenu();
void counterA(); // counterA menu
void counterB(); // counterB menu
void counterC(); // counterC menu
void ServingList(string c);
void processQueue(string x);
void confirmTerminateQ(string x);
void checkContainerSize();
void wCredentials(vector<Credentials> cred);
void rCredentials(vector<Credentials> *cred);
void admin_Registration();
void staffMenu2();
void pRecords(char x);
void counterRecord();

string probConverter(char x);

ofstream outfile;
ifstream infile;

int countPG = 0, countSG = 0, countPA = 0, countPB = 0, countPC = 0, countSA = 0, countSB = 0, countSC = 0, w = 0;
int recordCounter = 0;
queue<string> qPG, qPA, qPB, qPC, qSG, qSA, qSB, qSC; // these are the q containers
char sCheck, pCheck, school;
string Aserve, Bserve, Cserve, str, str1, str2;
//login name, time.
string LOGINNAME, LOGINSTARTTIME, LOGINENDTIME, LOGINDATE;
string *ptr1, *ptr2, *ptr3;


Stopwatch sw;

//Tools class
tools tool;

//Credential class
vector<Credentials> cred;


//CounterA class

Counter *a;
Counter record;


//Printing Record 

void pRecords(char x)
{
	ifstream iFile;
	string rLine, temp;

	char choice;

	temp = "counter";
	temp.append(1, x);
	temp.append("Log");
	temp.append(".txt");

	iFile.open(temp, ios::out);

	if (iFile.fail())
	{
		cout << "File does not exist!" << endl;
		cin.get();
		cout << "Invalid no records found!" << endl;
		adminMenu();
	}

	if (iFile.peek() == iFile.eof())						//check if first line is whitespace
		iFile.ignore(100, '\n');
	string temp1 = "Username", temp2 = "Qnum", temp3 = "Duration", temp4 = "ProbType", temp5 = "Description", temp6 = "Time", temp7 = "Date";
	cout << endl << "----------------------------------------------- " << x << " Records" << " -----------------------------------------------------" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << setw(12) << left << temp1 << "\t"
		<< setw(8) << left << temp6 << "\t"
		<< setw(10) << left << temp7 << "\t"
		<< setw(5) << left << temp2 << "\t"
		<< setw(7) << left << temp3 << "\t"
		<< setw(8) << left << temp4 << "\t"
		<< setw(20) << left << temp5
		<< endl << endl;

	while (!iFile.eof())
	{
		getline(iFile, rLine, '\n');
		cout << rLine << endl;
	}


	iFile.close();
	cout << endl << endl << "Key [B] to go back: ";
	cin >> choice;

	if (choice == 'B' || choice == 'b')
	{
		adminMenu();
	}
}


//For Registration & Login


void wCredentials(vector<Credentials> cred)
{
	ofstream oFile;
	oFile.open("Credentials.txt", ios::app);
	vector<Credentials>::iterator cpointer;

	for (cpointer = cred.begin(); cpointer < cred.end(); cpointer++)
	{
		oFile << endl << cpointer->convert_to_string();

	}

	oFile.close();
}

void rCredentials(vector<Credentials> *cred)
{
	string username, password;
	ifstream iFile;
	iFile.open("Credentials.txt", ios::out);

	if (iFile.fail())
	{
		cout << "File does not exist!" << endl;
		cout << "Program exits." << endl;
		cin.get();
		exit(0);
	}


	if (iFile.peek() == iFile.eof())						//check if first line is whitespace
		iFile.ignore(100, '\n');
	while (!iFile.eof())
	{
		iFile >> username;

		iFile >> password;


		iFile.ignore(100, '\n');
		Credentials admin(username, password);
		cred->push_back(admin);
	}


	iFile.close();

}

void admin_Registration()
{
	string temp, username, password;
	system("cls");
	cout << "Enter your username: ";
	cin >> username;
	outfile << username << "				";
	cout << "Enter your password: ";
	cin >> password;
	outfile << password << endl;

	Credentials admin(username, password);
	cred.push_back(admin);
	wCredentials(cred);


	system("cls");
	staffMenu2();
}

void staffMenu2()
{
	char userInput;
	bool check = true;
	do {

		if (check == false) cout << endl << "-----Incorrect Input. Please try again-----" << endl << endl;
		cout << "Registration is successful!" << endl;
		cout << "To Login, please press L. " << endl;

		cout << endl << "Your Input: " << endl;
		cin >> userInput;

		if (userInput == 'L' || userInput == 'l' || userInput == 'B' || userInput == 'b')
			check = true;
		else
			check = false;
	} while (check == false);

	if (userInput == 'L' || userInput == 'l')
		login();
	else
		welcome();
}


int main() {

	welcome();

	system("pause");
}


//tools
void checkContainerSize()
{
	cout << "The PG size: " << qPG.size() << endl;
	cout << "The PA size: " << qPA.size() << endl;
	cout << "The PB size: " << qPB.size() << endl;
	cout << "The PC size: " << qPC.size() << endl;
	cout << "The SG size: " << qSG.size() << endl;
	cout << "The SA size: " << qSA.size() << endl;
	cout << "The SB size: " << qSB.size() << endl;
	cout << "The SC size: " << qSC.size() << endl;
}

void dateNtime()
{

	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream ong;
	ong << put_time(&tm, "Date: %d/%m/%Y, %a \nCurrent time: %H:%M:%S");
	auto tstr = ong.str();

	cout << tstr << endl;
}

//Welcome menu


void welcome() {
	system("CLS");
	bool check = true;





	char userInput;

	do {

		tool.printDateTime();


		cout << "--------------------------------" << endl;
		cout << "   Queue Numbering System       " << endl;
		cout << "--------------------------------" << endl;

		cout << "-----------Welcome--------------" << endl;

		if (check == false) cout << "------------Incorrect Input. Please try again------------" << endl;
		cout << "For Administrators, Press S. (To Counter Menu) " << endl;
		cout << "For Public Users, press P. (To Queuing Menu) " << endl;
		cout << endl << "Your Input: " << endl;
		cin >> userInput;

		if (userInput == 's' || userInput == 'S' || userInput == 'P' || userInput == 'p')
			check = true;
		else
			check = false;
	} while (check == false);

	if (userInput == 'S' || userInput == 's')
	{
		system("CLS");
		staffMenu();
	}
	else
	{
		publicMenu1();
	}


}

// To Counter Menu

void staffMenu() {
	system("CLS");
	char userInput;
	bool check = true;
	do {

		if (check == false) cout << endl << "-----Incorrect Input. Please try again-----" << endl << endl;
		cout << endl << "To Register, please press R. " << endl;
		cout << "To Login, please press L. " << endl;
		cout << "To go back, please press B." << endl;

		cout << endl << "Your Input: " << endl;
		cin >> userInput;

		if (userInput == 'R' || userInput == 'r' || userInput == 'L' || userInput == 'l' || userInput == 'B' || userInput == 'b')
			check = true;
		else
			check = false;
	} while (check == false);

	if (userInput == 'R' || userInput == 'r')
		admin_Registration();
	else if (userInput == 'L' || userInput == 'l')
		login();
	else
		welcome();


}

void login() {
	system("CLS");
	bool impt = true;
	string eName, ePass;

	cout << "Enter Username:  ";
	cin >> eName;
	cin.ignore(100, '\n');
	cout << "Enter Password:  ";
	cin >> ePass;
	cout << endl << endl;

	cred.clear();
	rCredentials(&cred); //read creadentials

	vector<Credentials>::iterator cpointer;


	for (cpointer = cred.begin(); cpointer != cred.end(); cpointer++)
	{
		if (cpointer->validate(eName, ePass) == true)
		{
			LOGINNAME = eName;
			LOGINSTARTTIME = tool.getCTime();
			adminMenu();
		}
	}
	cout << "\nLOGIN ERROR\nPlease check your username and password\n";
	login();
}

void counterRecord()
{
	bool z = true;
	char choice, order;
	do
	{

		cout << "                 --------------------------- Welcome to Records menu ------------------------------" << endl;
		cout << "                                  -.-.-.-.-.- Select a Record -.-.-.-.-.-.-.-.- " << endl;
		cout << " o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o" << endl;
		cout << "Key in [1] to view Counter A - Records" << endl;
		cout << "Key in [2] to view Counter B - Records" << endl;
		cout << "Key in [3] to view Counter C - Records" << endl;
		cout << "Key in [4] to go back to the main menu" << endl;
		cin >> choice;

		if (choice == '1')
		{
			order = 'A';
			pRecords(order);
		}
		else if (choice == '2')
		{
			order = 'B';
			pRecords(order);
		}
		else if (choice == '3')
		{
			order = 'C';
			pRecords(order);
		}
		else if (choice == '4')
		{
			adminMenu();
		}
		else
		{
			z = false;
			cout << "Invalid choice!" << endl << "Please key in again!" << endl;

		}

	} while (z == false);
}

void adminMenu() {

	system("CLS");
	bool z;
	do
	{
		z = true;

		char choice;
		cout << "                 --------------------------- Welcome to admin menu ------------------------------" << endl;
		cout << "                                  -.-.-.-.-.- Select a Counter -.-.-.-.-.-.-.-.- " << endl;
		cout << " o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o" << endl << endl;
		cout << "Key in [1] to assign to Counter A" << endl;
		cout << "Key in [2] to assign to Counter B" << endl;
		cout << "Key in [3] to assign to Counter C" << endl;
		cout << "Key in [4] for Counters' records" << endl;
		cout << "Key in [5] to log out" << endl;
		cout << "Key in [6] to go back to the main menu" << endl;
		cin >> choice;

		if (choice == '1')
		{
			counterA();

		}
		else if (choice == '2')
		{
			counterB();
		}
		else if (choice == '3')
		{
			counterC();
		}
		else if (choice == '5')
		{

			LOGINENDTIME = tool.getCTime();
			cout << endl << "You have successfully logout! " << endl << "Time: " << LOGINENDTIME;
			welcome();
		}
		else if (choice == '6') {
			welcome();
		}
		else if (choice == '4')
		{
			counterRecord();
		}
		else
		{
			z = false;
			cout << "Invalid choice!" << endl << "Please key in again!" << endl;

		}
	} while (z == false);


}

void counterA()
{
	system("CLS");
	char choice;
	string c;
	bool x;
	cout << setw(10) << "\t" << "[--------------- Welcome, to Counter A menu ---------------]" << endl; //middle 28
	cout << setw(19) << "\t" << "[--------------- Students ---------------]" << endl; //middle 10
	cout << setw(20) << internal << "[- School A -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl;
	cout << setw(20) << internal << "[- Next Waiting: -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- Next Waiting: -]" << endl << endl;
	if (qPA.empty() == 0)
		cout << setw(20) << internal << qPA.front();
	else
		cout << setw(20) << internal << "NIL";
	cout << setw(22) << "\t";
	if (qPG.empty() == 0)
		cout << setw(20) << internal << "\t" << qPG.front() << endl;
	else
		cout << setw(20) << internal << "\t" << "NIL" << endl << endl;
	cout << setw(16) << "\t     " << "[---------------  No. Of Waiting  ---------------]" << endl << endl;
	cout << setw(20) << internal << "[- School A -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl << endl;
	cout << setw(20) << internal << qPA.size() << setw(22) << "\t" << setw(20) << internal << "\t" << qPG.size() << "\t" << endl << endl;
	cout << endl;


	cout << setw(20) << "\t  " << "[--------------- Staffs ---------------]" << endl;
	cout << setw(20) << internal << "[- School A -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl;
	cout << setw(20) << internal << "[- Next Waiting: -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- Next Waiting: -]" << endl << endl;
	if (qSA.empty() == 0)
		cout << setw(20) << internal << qSA.front();
	else
		cout << setw(20) << internal << "NIL";
	cout << setw(22) << "\t";
	if (qSG.empty() == 0)
		cout << setw(20) << internal << qSG.front() << "\t" << endl;
	else
		cout << setw(20) << internal << "\t" << "NIL" << "\t" << endl << endl;

	cout << setw(16) << "\t     " << "[---------------  No. Of Waiting  ---------------]" << endl << endl;
	cout << setw(20) << internal << "[- School A -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl << endl;
	cout << setw(20) << internal << qSA.size() << setw(22) << "\t" << setw(20) << internal << "\t" << qSG.size() << "\t" << endl << endl;

	do
	{
		cout << "Hi, " << LOGINNAME << ". Time: "; tool.printTime(); cout << endl;
		int cnt = 0;
		if (cnt == 0) {
			cout << "[ REMINDER ] :- Priority is student/staff with specific prob! -:" << endl << endl;
			cnt++;
		}


		cout << "Press [1] to serve student (School A)" << endl;
		cout << "Press [2] to serve Student(General Problem)." << endl;
		cout << "Press [3] to serve staff (School A)" << endl;
		cout << "Press [4] to serve staff (General Problem)." << endl;
		cout << "Press [5] to go back" << endl;
		cout << "Choice: ";
		cin >> choice;
		cout << endl;

		if ((choice == '1') && (qPA.empty() != 1))
		{
			Aserve = qPA.front();
			x = true;
			c = "PAA";
			ServingList(c);

		}
		else if ((choice == '2') && (qPG.empty() != 1))
		{
			Aserve = qPG.front();
			x = true;
			c = "PGA";
			ServingList(c);

		}
		else if ((choice == '3') && (qSA.empty() != 1))
		{
			Aserve = qSA.front();
			x = true;
			c = "SAA";
			ServingList(c);
		}
		else if ((choice == '4') && (qSG.empty() != 1))
		{
			Aserve = qSG.front();
			x = true;
			c = "SGA";
			ServingList(c);
		}
		else if (choice == '5')
		{
			x = true;
			adminMenu();
		}
		else
		{
			cout << endl << "Error: Either there are no queue in your selection or you key in wrongly." << endl << endl;
			x = false;
		}



	} while (x != true);


	//timing

}

void counterB()
{

	system("CLS");
	char choice;
	string c;
	bool x;
	cout << setw(10) << "\t" << "[--------------- Welcome, to Counter B menu ---------------]" << endl; //middle 28
	cout << setw(19) << "\t" << "[--------------- Students ---------------]" << endl; //middle 10
	cout << setw(20) << internal << "[- School B -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl;
	cout << setw(20) << internal << "[- Next Waiting: -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- Next Waiting: -]" << endl << endl;
	if (qPB.empty() == 0)
		cout << setw(20) << internal << qPB.front();
	else
		cout << setw(20) << internal << "NIL";
	cout << setw(22) << "\t";
	if (qPG.empty() == 0)
		cout << setw(20) << internal << "\t" << qPG.front() << endl;
	else
		cout << setw(20) << internal << "\t" << "NIL" << endl << endl;
	cout << setw(16) << "\t     " << "[---------------  No. Of Waiting  ---------------]" << endl << endl;
	cout << setw(20) << internal << "[- School B -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl << endl;
	cout << setw(20) << internal << qPB.size() << setw(22) << "\t" << setw(20) << internal << "\t" << qPG.size() << "\t" << endl << endl;
	cout << endl;


	cout << setw(20) << "\t  " << "[--------------- Staffs ---------------]" << endl;
	cout << setw(20) << internal << "[- School B -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl;
	cout << setw(20) << internal << "[- Next Waiting: -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- Next Waiting: -]" << endl << endl;
	if (qSB.empty() == 0)
		cout << setw(20) << internal << qSB.front();
	else
		cout << setw(20) << internal << "NIL";
	cout << setw(22) << "\t";
	if (qSG.empty() == 0)
		cout << setw(20) << internal << qSG.front() << "\t" << endl;
	else
		cout << setw(20) << internal << "\t" << "NIL" << "\t" << endl << endl;

	cout << setw(16) << "\t     " << "[---------------  No. Of Waiting  ---------------]" << endl << endl;
	cout << setw(20) << internal << "[- School B -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl << endl;
	cout << setw(20) << internal << qSB.size() << setw(22) << "\t" << setw(20) << internal << "\t" << qSG.size() << "\t" << endl << endl;

	do
	{
		cout << "Hi, " << LOGINNAME << ". Time: "; tool.printTime(); cout << endl;
		int cnt = 0;
		if (cnt == 0) {
			cout << "[ REMINDER ] :- Priority is student/staff with specific prob! -:" << endl << endl;
			cnt++;
		}


		cout << "Press [1] to serve student (School B)" << endl;
		cout << "Press [2] to serve Student(General Problem)." << endl;
		cout << "Press [3] to serve staff (School B)" << endl;
		cout << "Press [4] to serve staff (General Problem)." << endl;
		cout << "Press [5] to go back" << endl;
		cout << "Choice: ";
		cin >> choice;
		cout << endl;

		if ((choice == '1') && (qPB.empty() != 1))
		{
			Bserve = qPB.front();
			c = "PBB";
			ServingList(c);

		}
		else if ((choice == '2') && (qPG.empty() != 1))
		{
			Bserve = qPG.front();
			c = "PGB";
			ServingList(c);

		}
		else if ((choice == '3') && (qSB.empty() != 1))
		{
			Bserve = qSB.front();
			c = "SBB";
			ServingList(c);
		}
		else if ((choice == '4') && (qSG.empty() != 1))
		{
			Bserve = qSG.front();
			c = "SGB";
			ServingList(c);
		}
		else if (choice == '5')
		{
			adminMenu();
		}
		else
		{
			cout << endl << "Error: Either there are no queue in your selection or you key in wrongly." << endl << endl;

			x = false;
		}



	} while (x == false);
}

void counterC()
{
	char choice;
	string c;
	bool x = false;
	cout << setw(10) << "\t" << "[--------------- Welcome, to Counter C menu ---------------]" << endl; //middle 28
	cout << setw(19) << "\t" << "[--------------- Students ---------------]" << endl; //middle 10
	cout << setw(20) << internal << "[- School C -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl;
	cout << setw(20) << internal << "[- Next Waiting: -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- Next Waiting: -]" << endl << endl;
	if (qPC.empty() == 0)
		cout << setw(20) << internal << qPC.front();
	else
		cout << setw(20) << internal << "NIL";
	cout << setw(22) << "\t";
	if (qPG.empty() == 0)
		cout << setw(20) << internal << "\t" << qPG.front() << endl;
	else
		cout << setw(20) << internal << "\t" << "NIL" << endl << endl;
	cout << setw(16) << "\t     " << "[---------------  No. Of Waiting  ---------------]" << endl << endl;
	cout << setw(20) << internal << "[- School C -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl << endl;
	cout << setw(20) << internal << qPC.size() << setw(22) << "\t" << setw(20) << internal << "\t" << qPG.size() << "\t" << endl << endl;
	cout << endl;


	cout << setw(20) << "\t  " << "[--------------- Staffs ---------------]" << endl;
	cout << setw(20) << internal << "[- School C -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl;
	cout << setw(20) << internal << "[- Next Waiting: -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- Next Waiting: -]" << endl << endl;
	if (qSC.empty() == 0)
		cout << setw(20) << internal << qSC.front();
	else
		cout << setw(20) << internal << "NIL";
	cout << setw(22) << "\t";
	if (qSG.empty() == 0)
		cout << setw(20) << internal << qSG.front() << "\t" << endl;
	else
		cout << setw(20) << internal << "\t" << "NIL" << "\t" << endl << endl;

	cout << setw(16) << "\t     " << "[---------------  No. Of Waiting  ---------------]" << endl << endl;
	cout << setw(20) << internal << "[- School C -]" << setw(22) << "\t" << setw(20) << internal << "\t" << "[- General -]" << endl << endl;
	cout << setw(20) << internal << qSC.size() << setw(22) << "\t" << setw(20) << internal << "\t" << qSG.size() << "\t" << endl << endl;


	do
	{
		cout << "Hi, " << LOGINNAME << ". Time: "; tool.printTime(); cout << endl;
		int cnt = 0;
		if (cnt == 0) {
			cout << "[ REMINDER ] :- Priority is student/staff with specific prob! -:" << endl << endl;
			cnt++;
		}


		cout << "Press [1] to serve student (School C)" << endl;
		cout << "Press [2] to serve Student(General Problem)." << endl;
		cout << "Press [3] to serve staff (School C)" << endl;
		cout << "Press [4] to serve staff (General Problem)." << endl;
		cout << "Press [5] to go back" << endl;
		cout << "Choice: ";
		cin >> choice;
		cout << endl;

		if ((choice == '1') && (qPC.empty() != 1))
		{
			Cserve = qPC.front();
			c = "PCC";

			ServingList(c);

		}
		else if ((choice == '2') && (qPG.empty() != 1))
		{
			Cserve = qPG.front();
			c = "PGC";
			ServingList(c);

		}
		else if ((choice == '3') && (qSC.empty() != 1))
		{
			Cserve = qSC.front();
			c = "SCC";
			ServingList(c);
		}
		else if ((choice == '4') && (qSG.empty() != 1))
		{
			Cserve = qSG.front();
			c = "SGC";

			ServingList(c);
		}
		else if (choice == '5')
		{
			adminMenu();
		}
		else
		{
			cout << endl << "Error: Either there are no queue in your selection or you key in wrongly." << endl << endl;
			x = false;
		}

	} while (x == false);
}



// To queuing Menu    



void ServingList(string x)
{
	system("CLS");
	char choice;
	string strTest;
	bool check = true;




	cout << "       [ -------------------------------- Serving List -----------------------------------  ]" << endl;
	cout << "       0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o" << endl;
	cout << setw(20) << internal << "[- Counter A -]" << setw(18) << "\t" << setw(20) << internal << "[- Counter B -]" << setw(18) << "\t" << setw(20) << internal << "[- Counter C -]" << endl;
	cout << setw(20) << internal << Aserve << setw(18) << "\t" << setw(20) << internal << Bserve << setw(18) << "\t" << setw(20) << internal << Cserve << endl;

	do
	{
		if (!check) cout << "Invalid Input. Please try again" << endl;
		cout << endl << "To go back, Enter B." << endl;
		cout << "Confirm Guy is here press c" << endl;
		cout << "Choice: ";
		cin >> choice;

		if (choice == 'B' || choice == 'b' || choice == 'c' || choice == 'C')
			check = true;
		else
			check = false;



	} while (!check);

	if (choice == 'B' || choice == 'b') {
		if (x == "PAA" || x == "PGA" || x == "SAA" || x == "SGA")
			counterA();
		if (x == "PBB" || x == "PGB" || x == "SBB" || x == "SGB")
			counterB();
		if (x == "PCC" || x == "PGC" || x == "SCC" || x == "SGC")
			counterC();
	}
	else
		processQueue(x);


}

string probConverter(char x) {
	if (x == 'G')
		return "General";
	else
		return "Specific";

}

void processQueue(string x) {
	system("CLS");
	double time;
	char choice, probPlace;
	string desc, place, probPlace2;
	a = new Counter;

	sw.Start();



	for (int p = 0; p != 10; p++)
		cout << endl;
	cout << "You are currently serving: ";
	if (x == "PAA" || x == "PGA" || x == "SAA" || x == "SGA")
		cout << "	                                                          " << Aserve << endl;
	if (x == "PBB" || x == "PGB" || x == "SBB" || x == "SGB")
		cout << "	                                                          " << Bserve << endl;
	if (x == "PCC" || x == "PGC" || x == "SCC" || x == "SGC")
		cout << "	                                                          " << Cserve << endl;

	cout << "Enter the description of what the problem is about: ";
	cin.ignore();
	getline(cin, desc);
	bool check = false;

	do {
		if (desc.empty()) cout << "Invalid Input. Please try again: " << endl;
		else
		{
			cout << endl << "Press [T] if you are done with this Queue" << endl;
			cout << "Press [B] to resume" << endl;
			cout << "Choice: ";
			cin >> choice;
		}
		if (choice == 'T' || choice == 't')
			check = true;
		else check = false;

	} while (!check);

	if (check) {

		sw.Stop();
		time = sw.ElapsedMilliseconds() / 1000;


		for (int p = 0; p != 10; p++)
			cout << endl;
		system("CLS");

		if (x == "PAA" || x == "PGA" || x == "SAA" || x == "SGA") {


			cout << setw(20) << "[CONFIRM DETAILS]" << endl << endl;
			cout << "QNO :" << Aserve << endl;
			cout << "Elapsed Time: " << time << endl;
			cout << "Prob Type: " << probConverter(Aserve.at(1)) << endl;

			a->setLoginName(LOGINNAME);
			a->setQno(Aserve);
			a->setDuration(time);
			a->setProbType(probConverter(Aserve.at(1)));
		}
		if (x == "PBB" || x == "PGB" || x == "SBB" || x == "SGB") {

			cout << setw(20) << "[CONFIRM DETAILS]" << endl << endl;
			cout << "QNO :" << Bserve << endl;
			cout << "Elapsed Time: " << time << endl;
			cout << "Prob Type: " << probConverter(Bserve.at(1)) << endl;

			a->setLoginName(LOGINNAME);
			a->setQno(Bserve);
			a->setDuration(time);
			a->setProbType(probConverter(Bserve.at(1)));
		}
		if (x == "PCC" || x == "PGC" || x == "SCC" || x == "SGC") {

			cout << setw(20) << "[CONFIRM DETAILS]" << endl << endl;
			cout << setw(20) << "[CONFIRM DETAILS]" << endl << endl;
			cout << "QNO :" << Cserve << endl;
			cout << "Elapsed Time: " << time << endl;
			cout << "Prob Type: " << probConverter(Cserve.at(1)) << endl;

			a->setLoginName(LOGINNAME);
			a->setQno(Cserve);
			a->setDuration(time);
			a->setProbType(probConverter(Cserve.at(1)));
		}


		cout << "desc : " << desc << endl;
		a->setDesc(desc);

		do {
			if (!check) cout << "Invalid Input. Please try again: " << endl;
			cout << "Correct? Press X to confirm: ";
			cin >> choice;


			if (choice == 'X' || choice == 'x') {

				place = to_string(recordCounter);


				if (x == "PBB" || x == "PGB" || x == "SBB" || x == "SGB") {
					outfile.open("counterBLog.txt", fstream::app);
					outfile << setw(12) << left << a->getLoginName() << "\t";
					outfile << setw(8) << left << tool.getCTime() << "\t";
					outfile << setw(10) << left << tool.getCDate() << "\t";
					outfile << setw(5) << left << a->getQno() << "\t";
					outfile << setw(7) << left << a->getDuration() << "\t" << "\t";
					outfile << setw(8) << left << a->getprobType() << "\t";
					outfile << setw(20) << left << a->getDesc() << endl;
				}
				if (x == "PCC" || x == "PGC" || x == "SCC" || x == "SGC") {
					outfile.open("counterCLog.txt", fstream::app);
					outfile << setw(12) << left << a->getLoginName() << "\t";
					outfile << setw(8) << left << tool.getCTime() << "\t";
					outfile << setw(10) << left << tool.getCDate() << "\t";
					outfile << setw(5) << left << a->getQno() << "\t";
					outfile << setw(7) << left << a->getDuration() << "\t" << "\t";
					outfile << setw(8) << left << a->getprobType() << "\t";
					outfile << setw(20) << left << a->getDesc() << endl;
				}
				if (x == "PAA" || x == "PGA" || x == "SAA" || x == "SGA") {
					outfile.open("counterALog.txt", fstream::app);
					outfile << setw(12) << left << a->getLoginName() << "\t";
					outfile << setw(8) << left << tool.getCTime() << "\t";
					outfile << setw(10) << left << tool.getCDate() << "\t";
					outfile << setw(5) << left << a->getQno() << "\t";
					outfile << setw(7) << left << a->getDuration() << "\t" << "\t";
					outfile << setw(8) << left << a->getprobType() << "\t";
					outfile << setw(20) << left << a->getDesc() << endl;
				}


				outfile.close();
				confirmTerminateQ(x);
			}
			else check = false;

		} while (!check);


	}



}



void confirmTerminateQ(string x) {
	double time;

	//Save all details into text counter
	//Details means time, qnum, prob type and prob desc

	if (x == "PAA")
	{
		qPA.pop();
		cout << "Error on PAA" << endl;
		counterA();
	}
	else if (x == "PGA")
	{
		qPG.pop();
		counterA();
	}
	else if (x == "SAA")
	{
		qSA.pop();
		counterA();
	}
	else if (x == "SGA")
	{
		qSG.pop();
		counterA();
	}
	else if (x == "PBB")
	{
		qPB.pop();
		counterB();
	}
	else if (x == "PGB")
	{
		qPG.pop();
		counterB();
	}
	else if (x == "SBB")
	{
		qSB.pop();
		counterB();
	}
	else if (x == "SGB")
	{
		qSG.pop();
		counterB();
	}
	else if (x == "PCC")
	{
		qPC.pop();
		counterC();

	}
	else if (x == "PGC")
	{
		qPG.pop();
		counterC();
	}
	else if (x == "SCC")
	{
		qSC.pop();
		counterC();

	}
	else if (x == "SGC")
	{
		qSG.pop();
		counterC();
	}
	else
		cout << endl << endl << "Error on ConfirmTerminateQ" << endl;

}

void publicMenu1() {
	system("CLS");
	bool x = false;

	do
	{
		cout << "Enter P if you are a Student." << endl;
		cout << "Enter S if you are a staff member. " << endl;
		cout << "To go back, Enter B." << endl;
		cout << endl << "Your Input: " << endl;
		cin >> sCheck;

		if (sCheck == 'P' || sCheck == 'p' || sCheck == 's' || sCheck == 'S' || sCheck == 'B' || sCheck == 'b')
			x = true;
		else
			x = false;
	} while (x == false);

	if (sCheck == 'B' || sCheck == 'b')
		welcome();

	if (sCheck == 'p')
		sCheck = 'P';
	if (sCheck == 's')
		sCheck = 'S';

	publicMenu2();
}

void publicMenu2() {

	system("CLS");
	bool x = false;
	do
	{
		cout << "Enter G if you have a General Problem." << endl;
		cout << "Enter S if you have a Specific Problem. " << endl;
		cout << "To go back, Enter B." << endl;
		cout << endl << "Your Input: " << endl;
		cin >> pCheck;

		if (pCheck == 'G' || pCheck == 'g' || pCheck == 'S' || pCheck == 's' || pCheck == 'B' || pCheck == 'b')
			x = true;
		else
			x = false;
	} while (x != true);

	if (pCheck == 'B' || pCheck == 'b')
		publicMenu1();

	if (pCheck == 'g')
		pCheck = 'G';
	if (pCheck == 's')
		pCheck = 'S';


	if (pCheck == 'G') {
		checkCombo();
		system("CLS");
	}
	else
		publicMenu3();
}

void publicMenu3() {
	system("CLS");
	bool x = false;
	do
	{
		cout << "Enter X if you are from school A." << endl;
		cout << "Enter Y if you are from school B." << endl;
		cout << "Enter Z if you are from school C." << endl;

		cout << "To go back, Enter B." << endl;
		cout << endl << "Your Input: " << endl;
		cin >> school;

		if (school == 'X' || school == 'x' || school == 'Y' || school == 'y' || school == 'B' || school == 'b' || school == 'Z' || school == 'z')
			x = true;
		else
			x = false;
	} while (x == false);

	if (school == 'X' || school == 'x')
		pCheck = 'A';
	if (school == 'Y' || school == 'y')
		pCheck = 'B';
	if (school == 'Z' || school == 'z')
		pCheck = 'C';
	if (school == 'B' || school == 'b')
		publicMenu2();




	checkCombo();

}

// ---------------------- Queue Interface's functions ---------------------------- //
void checkCombo()
{
	string str;

	if (sCheck == 'P' && pCheck == 'G')
	{
		countPG++; //counter
		w = countPG; //w is integer
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qPG.push(str);



		cout << endl << "QueueNo:" << qPG.back() << endl << endl;
		welcome();


	}
	else if (sCheck == 'S' && pCheck == 'G')
	{
		countSG++;
		w = countSG;
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qSG.push(str);
		cout << endl << "QueueNo:" << qSG.back() << endl << endl;
		welcome();
	}
	else if (sCheck == 'P' && pCheck == 'A')
	{
		countPA++;
		w = countPA;
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qPA.push(str);
		cout << endl << "QueueNo:" << qPA.back() << endl << endl;
		welcome();
	}
	else if (sCheck == 'P' && pCheck == 'B')
	{
		countPB++;
		w = countPB;
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qPB.push(str);
		cout << endl << "QueueNo:" << qPB.back() << endl << endl;
		welcome();
	}
	else if (sCheck == 'P' && pCheck == 'C')
	{
		countPC++;
		w = countPC;
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qPC.push(str);
		cout << endl << "QueueNo:" << qPC.back() << endl << endl;
		welcome();

	}
	else if (sCheck == 'S' && pCheck == 'A')
	{
		countSA++;
		w = countSA;
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qSA.push(str);
		cout << endl << "QueueNo:" << qSA.back() << endl << endl;
		welcome();
	}
	else if (sCheck == 'S' && pCheck == 'B')
	{
		countSB++;
		w = countSB;
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qSB.push(str);
		cout << endl << "QueueNo:" << qSB.back() << endl << endl;
		welcome();
	}
	else if (sCheck == 'S' && pCheck == 'C')
	{
		countSC++;
		w = countSC;
		string place;

		if (w < 10)
			place = "00";
		else if (w < 100)
			place = "0";
		else
			place = "";

		string str;
		str.push_back(sCheck);
		string str1;
		str1.push_back(pCheck);
		string str2;
		str2 = to_string(w);

		str.append(str1);
		str.append(place);
		str.append(str2);

		qSC.push(str);

		cout << endl << "QueueNo:" << qSC.back() << endl << endl;
		welcome();
	}
	else
		cout << "Error" << endl;

}

