#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"
#include "semicolon.hpp"
#include "pound.hpp"
#include "or.hpp"
#include <vector>
#include <string>
#include <cstring>

//NOTE TO SELF: MAKE SURE TO MAKE THE DISTINCTION BETWEEN EXECUTE AND ISVALID, ISVALID CURRENTLY EXECUTES A FUNCTION

int main()
{
vector<char*> substr;
string uInput;
getline(cin, uInput);
//cout << uInput << endl;
string newInput;
for (int i = 0; i < uInput.size(); i++)
{
	if (uInput.at(i) != ' ')
	{
		newInput.push_back(uInput.at(i));
		
	}
	if (uInput[i] == ';' || uInput[i] == '#')
 	{
		newInput.erase(newInput.end()-1);
		char* temp = new char[newInput.length()+1];
		temp = strcpy(temp, newInput.c_str());
		substr.push_back(temp);
		newInput.clear();
		newInput.push_back(uInput.at(i));	
	}
	else if ((uInput[i] == '|' && uInput[i+1] == '|') ||(uInput[i] == '&' && uInput[i+1] == '&'))
	{
		newInput.erase(newInput.end()-1);
	//	newInput.erase(newInput.end()-1);
		newInput.push_back(uInput.at(i+1));
		char* temp = new char[newInput.length()+1];
		temp = strcpy(temp, newInput.c_str());
		substr.push_back(temp);
		newInput.clear();
		newInput.push_back(uInput.at(i));
		newInput.push_back(uInput.at(i+1));
//		newInput.erase(newInput.end()-1);
		i++;
	}
}

char* temp = new char[newInput.length()+1];
temp = strcpy(temp, newInput.c_str());
substr.push_back(temp);
newInput.clear();		
	
substr.push_back(NULL);
cout << "substr: " << endl;

for (int j = 0; j < substr.size(); j ++)
{
	cout << substr.at(j) <<  endl;
}

































/*
	Cmd* A = new Cmd("ls");
	Cmd* B = new Cmd("asdf");
	Semicolon* C = new Semicolon(false,A);
	Pound* D = new Pound(false, B);
	Or* E = new Or(false, A);
	if (E->isValid)
	{
		cout << "GOOD " << endl;
	}
	else
	{
		cout << "ERROR" << endl;
	}
*/
	return 0;
}

