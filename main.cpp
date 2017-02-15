#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"
#include "semicolon.hpp"
#include "pound.hpp"
#include "or.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <boost/tokenizer.hpp>
#include <locale>
using namespace boost;


//NOTE TO SELF: MAKE SURE TO MAKE THE DISTINCTION BETWEEN EXECUTE AND ISVALID, ISVALID CURRENTLY EXECUTES A FUNCTION

int main()
{
vector<char> substr;
string uInput;
//getline(cin, uInput);
//cout << uInput << endl;
uInput = "ls ; ls || ls && ls # ls";
//char* newInput;
//newInput = strtok(uInput, " ");

tokenizer<> tok(uInput);
for (string::iterator i = uInput.begin(); i != uInput.end(); i++)
{
	if (!isalpha(*i) && (*i) != ' ')
	{
		substr.push_back((*i));
	}
}
/*for (int i = 0; i < uInput.size(); i++)
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
*/

cout << "substr: " << endl;
for (unsigned i = 0; i < substr.size(); i++)
{
	cout << substr.at(i) << " ";
}
cout << endl;
cout << "TOKENIZER" << endl;
string temp;
for (tokenizer<>::iterator i = tok.begin(); i != tok.end(); i++)
{
	temp = (*i);
	cout << temp <<  endl;
}

Cmd* A = new Cmd(temp);
A->execute(temp);































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

