#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"
#include "semicolon.hpp"
#include "pound.hpp"
#include "or.hpp"
#include "and.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <boost/tokenizer.hpp>
#include <locale>
using namespace boost;


//NOTE TO SELF: MAKE SURE TO MAKE THE DISTINCTION BETWEEN EXECUTE AND ISVALID, ISVALID CURRENTLY EXECUTES A FUNCTION

int main()
{
string uInput = "";
//uInput = "ls; ls || ls && ls # ls ";
//char* newInput;
//newInput = strtok(uInput, " ");

while (getline(cin, uInput))
{	
	cout << "SSTARTED WHILE" << endl;
	if (uInput == "quit")
	{
		break;
	}
	vector<char> substr;
	tokenizer<> tok(uInput);
	bool isValid = true;

	string otemp;
	string atemp;	

	for (string::iterator i = uInput.begin(); i != uInput.end(); i++)
	{
		if ((*i) == ';')
		{
			substr.push_back((*i));
		}
		else if ((*i) == '|')
		{
			otemp.push_back('|');
			if (otemp == "||")
			{
				substr.push_back((*i));
				otemp.clear();
			}
		}
		else if ((*i) == '&')
		{
			atemp.push_back('&');
			if (atemp == "&&")
			{
				substr.push_back((*i));
				atemp.clear();
			}
		}
		else if ((*i) == '#')
		{
			break;
		}
	}
/*	if (substr.size() != 1)
	{
		for (unsigned i = 0; i < substr.size(); i++)
		{
			if (substr.at(i) == substr.at(i+1))
			{
				substr.erase(substr.begin() + (i+1));
			}
		}
	}
*/

	cout << "substr: " << endl;
	for (unsigned i = 0; i < substr.size(); i++)
	{
		cout << substr.at(i) << " ";
	}
	cout << endl;

	cout << "TOKENIZER" << endl;


	tokenizer<>::iterator i = tok.begin();
	Cmd* first = new Cmd((*i));
	isValid = first->execute((*i));
	i++;

	if (i != tok.end())
	{
		cout << "HIT MAJOR LOOP" << endl;	
		for (unsigned j = 0; j < substr.size(); j++)
		{
			if ((*i) == "quit")
			{
				break;
			}
			Cmd* uCmd = new Cmd((*i));
			switch(substr.at(j))
			{
				case ';':
				{
					cout << "HIT CASE SEMICOLON" << endl;
					Semicolon* sHolder = new Semicolon(isValid, uCmd);
					isValid = sHolder->execute((*i));	
				//	delete sHolder;	
					break;
				}
				case '|':
				{
					cout << "HIT CASE OR" << endl;
					Or* oHolder = new Or(isValid, uCmd);
					isValid = oHolder->execute(*i);
					//delete oHolder;
					break;
				}
				case '&':
				{
					cout << "HIT CASE AND" << endl;	
					And* aHolder = new And(isValid, uCmd);
					isValid = aHolder->execute((*i));
					//delete aHolder;
					break;
				}
				default:
				{
					j = substr.size();
					break;		
				}
			}
			i++;
		}
	}
	uInput.clear();
	substr.clear();
}

	return 0;
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
