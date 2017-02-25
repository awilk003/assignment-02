#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"
#include "semicolon.hpp"
#include "pound.hpp"
#include "or.hpp"
#include "and.hpp"
#include "test.hpp"
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


bool run(bool isValid, vector<string> cmds )
{
	if (cmds.at(0) == "quit")
	{
		exit(1); //IF FIRST COMMAND IS QUIT EXIT IMMEDIATLY
	}
	//cout << "MADE IT TO FIRST CMD" << endl << cmds.at(0) << "TEST" <<  endl;	
	//cout << "CMD: " << cmds.at(0) << endl;
	cout << "CMD: " << cmds.at(0) << endl;
	if (cmds.at(0) == "[" || cmds.at(0) == "test")
	{
		if (cmds.at(0) == "[")
		{
			string pathHolder;
			unsigned counter = 1;
			while (cmds.at(0+counter) != "]")
			{
				pathHolder += cmds.at(0+counter);
				counter++;
			}
			Test* tHolder = new Test();
			tHolder->execute(cmds.at(1));
			cout << "PATHHOLDER" << pathHolder << endl;
		}
		else
		{
			Test* tHolder = new Test();
			tHolder->execute(cmds.at(1));
			cout << "PATHHOLDER " << cmds.at(1) << endl;		
		}

	}
	else	
	{
		Cmd* first = new Cmd(cmds.at(0)); // BECAUSE FIRST COMMAND DOES NOT HAVE A PARSER IN FRONT OF IT WE HARDCODED IT
		isValid = first->execute(cmds.at(0)); // SET ISVALID TO WHETHER OR NOT THE COMMAND WAS VALID OR NOT FOR POSSIBLE NEXT COMMAND}
	}
	if (cmds.size() % 2 == 1 && cmds.size() != 1) // IF ONLY ONE COMMAND THEN WILL NOT RUN
	{
		for (unsigned j = 1; j < cmds.size(); j++)	//ITERATING THROUGH THE PARSER VECTOR
		{
		     if (cmds.at(j) == ";" || cmds.at(j) == "||" || cmds.at(j) == "&&" || cmds.at(j) == "#" || cmds.at(j) == "[" || cmds.at(j) == "test")
		     {	
				Cmd* uCmd = new Cmd(cmds.at(j));		// CREATE NEW COMMANDS FOR EACH PARSER
				if (cmds.at(j) == ";")
				{
				//				cout << "HIT CASE SEMICOLON" << endl;
					Semicolon* sHolder = new Semicolon(isValid, uCmd);	// CREATE SEMICOLON OBJECT WHEN SEMICOLON IS DETECTED;
					isValid = sHolder->execute(cmds.at(j + 1));			// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
												//	delete sHolder;	
				}
				else if (cmds.at(j) == "||")
				{
				//				    cout << "HIT CASE OR" << endl;
					Or* oHolder = new Or(isValid, uCmd); 	//CREATE OR OBJECT WHEN "|" SYMBOL IS DETECTED
					isValid = oHolder->execute(cmds.at(j + 1));		//EXECUTES COMMAND AND CHECKS/SETS VALIDITY
												//delete oHolder;
				}
				else if (cmds.at(j) == "&&")
				{
				//				    cout << "HIT CASE AND" << endl;	
					And* aHolder = new And(isValid, uCmd);	//CREATE AND OBJECT WHEN "&" SYMBOL IS DETECTED
					isValid = aHolder->execute(cmds.at(j + 1));	// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
											//delete aHolder;
				}
				else if (cmds.at(j) == "[" || cmds.at(j) == "test")
				{
					string pathHolder;
					unsigned counter = 0;
					while (cmds.at(j+counter) != "]")
					{
						pathHolder += cmds.at(j+counter);
						counter++;
					}
					cout << "PATHHOLDER" << pathHolder << endl;
				//	Test* tHolder = new Test("A");
				//	isValid = tHolder->execute(pathHolder);
				}
				else if (cmds.at(j) == "#")
				{
					break;
				}
			}
		}
	   }
	//	uInput.clear(); //CLEARED FOR NEXT USER INPUT
	//	substr.clear();	//CLEARED FOR NEXT USER INPUT
		cmds.clear();
	return isValid;
}


vector<string> parse (string uInput)
{
	vector<string> substr;			// USED TO HOLD PARSERS
	typedef tokenizer<char_separator<char> > Tok;		// USED TO HOLD COMMANDS
	char_separator<char> sep("", ";(&&)(||)[]", keep_empty_tokens);
	Tok tok(uInput, sep);
	for (Tok::iterator i = tok.begin(); i != tok.end(); i++)
	{
		if ((*i) != "")
		{
			substr.push_back((*i));
		}
	//				    substr.push_back(" ");
	}
	for (unsigned i = 0; i < substr.size()-1; i++)
	{
		if ((substr.at(i) == "&" || substr.at(i) == "|") && substr.at(i) == substr.at(i+1))
		{
			substr.at(i) = substr.at(i) + substr.at(i+1);
			substr.erase(substr.begin() + (i+1));
		}
		else if ((substr.at(i) == "&" || substr.at(i) == "|") && substr.at(i) != substr.at(i+1))
		{
			if (i == 0)
			{
				substr.at(i) = substr.at(i) + substr.at(i+1);
				substr.erase(substr.begin() + (i+1));
			}
			else	
			{
				substr.at(i) = substr.at(i-1) + substr.at(i) + substr.at(i+1);
				substr.erase(substr.begin() + (i-1));
				substr.erase(substr.begin() + (i+1));
			}
		}
	}
	int last = substr.size()-1;
	if (substr.at(last) == "&" || substr.at(last) == "|")
	{
		substr.at(last-1) = substr.at(last-1) + substr.at(last);	
		substr.erase(substr.begin() + last);
	}



/*	for (unsigned i = 0; i < substr.size(); i++)
	{
		cout << "SUBSTR" << substr.at(i) << endl;
	}
*/

	for (unsigned i = 0; i < substr.size(); i++)	
	{
		size_t found = substr.at(i).find("test");	
		if (found != string::npos)
		{
			substr.push_back(substr.at(i).substr(4, substr.at(i).length()));
			substr.at(i) = "test";
		}
	}
	for (unsigned i = 0; i < substr.size(); i++)
	{	
		if (isspace( substr.at(i).at(substr.at(i).length()-1) ) != 0) {substr.at(i).erase(substr.at(i).end() - 1);}
	}

	for (unsigned i = 0; i < substr.size(); i++ )
	{
		if (isspace(substr.at(i).at(0)) != 0) {substr.at(i).erase(substr.at(i).begin());}
	}


	cout << "TESTING CMDS:" << endl;		
	for (unsigned i = 0; i < substr.size(); i++)
	{
		cout << substr.at(i) << endl;
	}
	return substr;

}


vector<string> pParse (string uInput)
{
	vector<string> substr;			// USED TO HOLD PARSERS
	typedef tokenizer<char_separator<char> > Tok;		// USED TO HOLD COMMANDS
	char_separator<char> sep("", "()", keep_empty_tokens);
	Tok tok(uInput, sep);
	for (Tok::iterator i = tok.begin(); i != tok.end(); i++)
	{
		if ((*i) != "")
		{
			cout << "TOK" << (*i) << endl;
			substr.push_back(*i);
		}
		
	}
	cout << "TESTING SUBSTR" << endl;
	for (unsigned j = 0; j < substr.size(); j++)
	{
		cout << substr.at(j) << endl;
	}
	cout << "END SUBSTR" << endl;
	return substr;

}


int main()
{
	char uname[100];
	string uInput = "";
	char* ulgn = getlogin();
	gethostname(uname, 100);
	puts(uname);
	bool isValid = true;			// USED IN && AND || TO DETERMINE IF PREVIOUS COMMAND WAS VALID

	cout << "Beginning Terminal" << endl << "Enter 'quit' to exit the program" << endl;
	cout << ulgn << "@" << uname << "$ ";
	while (getline(cin, uInput))
	{
		if (!uInput.empty() && uInput.at(0) != '#')
		{
//			vector< vector <string> > CMD;
			/*
			vector<string> test = pParse(uInput);
			for (unsigned i = 0; i < test.size(); i++)
			{
				if (i ==  )
				{
						
				}
			}	*/		
			vector<string> temp = parse(uInput);
			bool holder = run(isValid, temp);
			if (holder) {}
			//cout << "RUNNING CMDS" << endl;
			//isValid = run(isValid, temp);
		}
		cout << ulgn << "@" << uname << "$ ";
	}

	return 0;
}


/*

			//DEBUGGING TOOLS
			if (substr.size() != 1)
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

			// END DEBUGGING TOOLS
*/		

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
switch(substr.at(j))			// CASE USED TO DETERMINE WHICH PARSER WAS PASSED IN BY USER
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

	string icmd;
	vector<string> cmds;
	for (unsigned i = 0; i < substr.size(); i++)
	{
		icmd.append(substr.at(i));
		if (icmd.substr(icmd.length() - 1) == ";")
		{ 
			cmds.push_back(icmd.substr(0, icmd.length() - 1));
			cmds.push_back(";");
			icmd.clear();
		}
		else if (icmd.at(0) == ';')
		{
			cmds.push_back(";");
			cmds.push_back(icmd.substr(1, icmd.length()));
			icmd.clear();
		}
		else if (icmd.substr(icmd.length() - 1) == "|")
		{
			if (icmd.at(icmd.size() - 2) == '|')
			{
				cmds.push_back(icmd.substr(0, icmd.length() - 2));
				cmds.push_back("||");
				icmd.clear();
			}
		}
		else if (icmd.substr(icmd.length() - 1) == "&")
		{
			if (icmd.at(icmd.size() - 2) == '&')
			{
				cmds.push_back(icmd.substr(0, icmd.length() - 2));
				cmds.push_back("&&");
				icmd.clear();
			}
		}
		else if (icmd.substr(icmd.length() - 1) == "#")
		{
			cmds.push_back("#");
			break;
		}
		icmd.append(" ");
	}
	if (icmd != " ") {cmds.push_back(icmd);}
*/


