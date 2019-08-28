#include "Counter.h"



void Counter::setQno(string g) {
	Qno = g;
}

void Counter::setProbType(string h) {
	probType = h;
}

void Counter::setDuration(double i) {
	duration = i;
}

void Counter::setDesc(string j) {
	desc = j;
}

void Counter::setLoginName(string l)
{
	lgname = l;
}
string  Counter::getQno()
{
	return Qno;
}
string Counter::getprobType()
{
	return probType;
}
double Counter::getDuration()
{
	return duration;
}

string Counter::getDesc() {
	return desc;
}

string Counter::getLoginName()
{
	return lgname;
}
