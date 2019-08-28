#include "Credentials.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>



bool Credentials::return_username()
{
	return true;
}

string Credentials::convert_to_string()
{
	ostringstream o_stream;
	o_stream << setw(12) << left << username << ' ' << setw(8) << password;
	string str = o_stream.str();
	return str;
}


bool Credentials::validate(string eName, string ePass)
{
	if (username.compare(eName) == 0)
	{

		if (password.compare(ePass) == 0)
		{

			return true;
		}


	}

	return false;
}



