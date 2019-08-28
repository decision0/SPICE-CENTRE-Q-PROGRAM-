#pragma once
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Credentials
{
public:
	Credentials(string n, string p)
	{
		username = n;
		password = p;
	}
	~Credentials() {};


	string convert_to_string();
	bool validate(string eName, string ePass);
	bool return_username();


private:
	string username, password;

};