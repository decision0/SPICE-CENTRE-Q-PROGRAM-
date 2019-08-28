#pragma once
#include <iostream>
#include <string>
using namespace std;

class Counter
{
public:
	Counter() {};
	~Counter() {};

	void setQno(string g);
	void setProbType(string h);
	void setDuration(double j);
	void setDesc(string k);
	void setLoginName(string l);
	string getLoginName();
	string getQno();
	string getprobType();
	double getDuration();
	string getDesc();


private:
	string Qno, probType, desc, lgname;
	double duration;

};