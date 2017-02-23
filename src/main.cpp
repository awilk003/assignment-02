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
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
using namespace boost;


//ALL COMMENTED CODE WAS USED FOR DEBUGGING PURPOSES, WITH THE EXCEPTION OF THE CODE OUTSIDE IF MAIN, WHICH IS SCRAPPED PREVIOUS ATTEMPTS.


int main()
{
	char uname[100];
	string uInput = "";
	char* ulgn = getlogin();
	gethostname(uname, 100);
	puts(uname);

	cout << "Beginning Terminal" << endl << "Enter 'quit' to exit the program" << endl;
	cout << ulgn << "@" << uname << "$ ";
	while (getline(cin, uInput))
	{
		if (!uInput.empty() && uInput.at(0) != '#')
		{
			vector<char> substr;			// USED TO HOLD PARSERS
			tokenizer<> tok(uInput);		// USED TO HOLD COMMANDS
			bool isValid = true;			// USED IN && AND || TO DETERMINE IF PREVIOUS COMMAND WAS VALID

			string otemp;				//TEMP STRING IN ORDER TO CORRECTLY ADDED THE "||" SYMBOL TO SUBSTR
			string atemp;				//TEMP STRING IN ORDER TO CORRECTLY ADDED THE "&&" SYMBOL TO SUBSTR

			for (string::iterator i = uInput.begin(); i != uInput.end(); i++) // ITERATES THROUGH USER INPUT IN ORDER TO FIND PARSERS
			{
				if ((*i) == ';')
				{
					substr.push_back((*i)); // IF SYMBOL == ';' ADDED TO SUBSTR
				}
				else if ((*i) == '|')
				{
					otemp.push_back('|'); // PUSH BACK THE CHAR '|' TO ATEMP
					if (otemp == "||")
					{
						substr.push_back((*i)); //IF OTEMP = "||" THEN ADD A OR SYMBOL TO SUBSTR, USED TO MAKE SURE USER INPUT "||' AND NOT "|'
						otemp.clear(); // CLEAR OTEMP FOR NEXT RUN
					}
				}
				else if ((*i) == '&')
				{
					atemp.push_back('&'); // PUSH BACK THE CHAR '&' TO ATEMP
					if (atemp == "&&")
					{
						substr.push_back((*i)); //IF OTEMP = "&" THEN ADD A OR SYMBOL TO SUBSTR, USED TO MAKE SURE USER INPUT "&&' AND NOT "&'
						atemp.clear(); // CLEAR ATEMP FOR NEXT RUN
					}
				}
				else if ((*i) == '#')
				{
					substr.push_back((*i));
					break; // STOPS PARSING ALL TOGETHER IF '#' IS DETECTED
				}
			}
			//DEBUGGING TOOLS
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
			cout << "substr: " << endl;
			for (unsigned i = 0; i < substr.size(); i++)
			{
			cout << substr.at(i) << " ";
			}
			cout << endl;
			//	cout << "TOKENIZER" << endl;
			for (tokenizer<>::iterator k = tok.begin(); k != tok.end(); k++)
			{
			//	cout << "K " << (*k) << endl;
			if ((*k) == "quit")
			{
			return 0;
			}
			}
			*/
			// END DEBUGGING TOOLS
			tokenizer<>::iterator i = tok.begin(); // STARTING TO PARSE COMMANDS
			if ((*i) == "quit")
			{
				return 0; //IF FIRST COMMAND IS QUIT EXIT IMMEDIATLY
			}
			Cmd* first = new Cmd((*i)); // BECAUSE FIRST COMMAND DOES NOT HAVE A PARSER IN FRONT OF IT WE HARDCODED IT
			isValid = first->execute((*i)); // SET ISVALID TO WHETHER OR NOT THE COMMAND WAS VALID OR NOT FOR POSSIBLE NEXT COMMAND}
			i++; // INCREMENTED TOKENIZER ITERATOR

			if (i != tok.end()) // IF ONLY ONE COMMAND THEN WILL NOT RUN
			{
				for (unsigned j = 0; j < substr.size(); j++)	//ITERATING THROUGH THE PARSER VECTOR
				{
					Cmd* uCmd = new Cmd((*i));		// CREATE NEW COMMANDS FOR EACH PARSER
					switch (substr.at(j))			// CASE USED TO DETERMINE WHICH PARSER WAS PASSED IN BY USER
					{
					case ';':
					{
						//				cout << "HIT CASE SEMICOLON" << endl;
						Semicolon* sHolder = new Semicolon(isValid, uCmd);	// CREATE SEMICOLON OBJECT WHEN SEMICOLON IS DETECTED;
						isValid = sHolder->execute((*i));			// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
																	//	delete sHolder;	
						break;
					}
					case '|':
					{
						//				    cout << "HIT CASE OR" << endl;
						Or* oHolder = new Or(isValid, uCmd); 	//CREATE OR OBJECT WHEN "|" SYMBOL IS DETECTED
						isValid = oHolder->execute(*i);		//EXECUTES COMMAND AND CHECKS/SETS VALIDITY
															//delete oHolder;
						break;
					}
					case '&':
					{
						//				    cout << "HIT CASE AND" << endl;	
						And* aHolder = new And(isValid, uCmd);	//CREATE AND OBJECT WHEN "&" SYMBOL IS DETECTED
						isValid = aHolder->execute((*i));	// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
															//delete aHolder;
						break;
					}
					default:
					{
						j = substr.size();	// IF HASH DETECTED BREAK OUT OF THE LOOP
						break;
					}
					}
					i++;	//INCREMENT TOKENIZER CLASS TO NEXT COMMAND TO MATCH NEXT PARSER
				}
			}
			uInput.clear(); //CLEARED FOR NEXT USER INPUT
			substr.clear();	//CLEARED FOR NEXT USER INPUT
			cout << ulgn << "@" << uname << "$ ";
		}

	}

	return 0;
}




// OLD CODE KEPT JUST IN CASE
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