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

tools::tools()
{
}


tools::~tools()
{
}

void tools::printDateTime()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream ong;
	ong << put_time(&tm, "Date: %d/%m/%Y, %a \nCurrent time: %H:%M:%S");
	auto tstr = ong.str();

	cout << tstr << endl;
}

void tools::printDate()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream ong;
	ong << put_time(&tm, "%d/%m/%Y");
	auto tstr = ong.str();

	cout << tstr << endl;
}

void tools::printTime()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream ong;
	ong << put_time(&tm, "%H:%M:%S");
	auto tstr = ong.str();

	cout << tstr << endl;
}

void tools::printDay()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream ong;
	ong << put_time(&tm, "%A");
	auto tstr = ong.str();

	cout << tstr << endl;
}

string tools::getCDate()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream ong;
	ong << put_time(&tm, "%d/%m/%Y");
	auto tstr = ong.str();

	return tstr;
}

string tools::getCTime()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream ong;
	ong << put_time(&tm, "%H:%M:%S");
	auto tstr = ong.str();

	return tstr;
}
