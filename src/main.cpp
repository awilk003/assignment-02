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


void print(vector<string> input)
{
	cout << "NEW PRINT" << endl;
	cout << "START";
	for (unsigned i = 0; i < input.size(); i++)
	{
		cout  << input.at(i) << ", ";
	}
	cout << "END";
	cout << endl;
}

bool run(bool isValid, vector<string> cmds )
{
	vector<string> temp;
	if (cmds.at(0) == "quit")
	{
		exit(1); //IF FIRST COMMAND IS QUIT EXIT IMMEDIATLY
		cout << "SHOULD HAVE QUIT" << endl;
	}

	unsigned j = 0;

	print(cmds);

	if (cmds.at(j) == "[" || cmds.at(j) == "test")
	{
		if (cmds.at(j) == "[")
		{
			j++;
			while (cmds.at(j) != "]")
			{
				temp.push_back(cmds.at(j));
				j++;
			}
			Test* tHolder = new Test("A");
			tHolder->execute(temp);
			print(temp);
			temp.clear();
			j++;
		}
		else
		{	//FIX TEST PARSING
			j++;
			while (j < cmds.size() && (cmds.at(j) != "&&"))
			{
				temp.push_back(cmds.at(j));
				j++;
			}
			Test* tHolder = new Test("A");
			tHolder->execute(temp);
			print(temp);
			temp.clear();
			j++;
		}
	}
	else	
	{
		Cmd* first = new Cmd(cmds.at(j)); // BECAUSE FIRST COMMAND DOES NOT HAVE A PARSER IN FRONT OF IT WE HARDCODED IT
		while (j < cmds.size())
		{
			if (cmds.at(j) == "&&" || cmds.at(j) == "||" || cmds.at(j) == ";")
			{	
				break;
			}
			temp.push_back(cmds.at(j));
			j++;
		}
		print(temp);
		isValid = first->execute(temp); // SET ISVALID TO WHETHER OR NOT THE COMMAND WAS VALID OR NOT FOR POSSIBLE NEXT COMMAND}
		temp.clear();
	}

	cout << "J " << j << endl;

	if (cmds.size() != 1) // IF ONLY ONE COMMAND THEN WILL NOT RUN
	{	
		for (; j < cmds.size(); j++)	//ITERATING THROUGH THE PARSER VECTOR
		{
		     if ((cmds.at(j) == ";" || cmds.at(j) == "||" || cmds.at(j) == "&&" || cmds.at(j) == "#" || cmds.at(j) == "[" || cmds.at(j) == "test"))
		     {
				Cmd* uCmd = new Cmd(cmds.at(j));		// CREATE NEW COMMANDS FOR EACH PARSER
				if (cmds.at(j) == ";")
				{
					//cout << "HIT CASE SEMICOLON" << endl;
					j++;
					if (cmds.at(j) == "[")	
					{	
						j++;
						while (cmds.at(j) != "]")
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						print(temp);
						Test* tHolder = new Test("A");
						isValid = tHolder->execute(temp);
						temp.clear();
						j++;
					}
					else if (cmds.at(j) == "test")
					{	
						j++;	
						while (j < cmds.size() && (cmds.at(j) != "||" || cmds.at(j) != "&&" || cmds.at(j) != ";"))
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						Test* tHolder = new Test("A");
						tHolder->execute(temp);
						print(temp);
						temp.clear();
						j++;
					}
					else
					{
						while (j < cmds.size())
						{
							if (cmds.at(j) == "&&" || cmds.at(j) == "||" || cmds.at(j) == ";")
							{	
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}
						print(temp);
						Semicolon* sHolder = new Semicolon(isValid, uCmd);	// CREATE SEMICOLON OBJECT WHEN SEMICOLON IS DETECTED;
						isValid = sHolder->execute(temp);			// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
						temp.clear();						//	delete sHolder;	
						j++;
					}
				}
				else if (cmds.at(j) == "||" )
				{
					//cout << "HIT CASE OR" << endl;
					j++;
					if (cmds.at(j) == "[" && !isValid)	
					{	
						j++;
						while (cmds.at(j) != "]")
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						print(temp);
						Test* tHolder = new Test("A");
						isValid = tHolder->execute(temp);
						temp.clear();
						j++;
					}
					else if (cmds.at(j) == "test" && !isValid)
					{	
						j++;	
						while (j < cmds.size() && (cmds.at(j) != "||" || cmds.at(j) != "&&" || cmds.at(j) != ";"))
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						Test* tHolder = new Test("A");
						tHolder->execute(temp);
						print(temp);
						temp.clear();
						j++;
					}
					else	
					{
						while (j < cmds.size())
						{
							if (cmds.at(j) == "&&" || cmds.at(j) == "||" || cmds.at(j) == ";")
							{	
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}
						print(temp);
						Or* oHolder = new Or(isValid, uCmd); 	//CREATE OR OBJECT WHEN "|" SYMBOL IS DETECTED
						isValid = oHolder->execute(temp);		//EXECUTES COMMAND AND CHECKS/SETS VALIDITY
						temp.clear();
						j++;							//delete oHolder;
					}
				}
				else if (cmds.at(j) == "&&")
				{
					j++;
					if (cmds.at(j) == "[")	
					{	
						j++;
						while (cmds.at(j) != "]")
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						print(temp);
						Test* tHolder = new Test("A");
						isValid = tHolder->execute(temp);
						temp.clear();
						j++;
					}
					else if (cmds.at(j) == "test")
					{	
						j++;	
						while (j < cmds.size() && (cmds.at(j) != "||" || cmds.at(j) != "&&" || cmds.at(j) != ";"))
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						Test* tHolder = new Test("A");
						tHolder->execute(temp);
						print(temp);
						temp.clear();
						j++;
					}
					else
					{
						while (j < cmds.size())
						{
							if (cmds.at(j) == "&&" || cmds.at(j) == "||" || cmds.at(j) == ";")
							{	
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}
					//cout << "HIT CASE AND" << endl;	
						print(temp);			    
						And* aHolder = new And(isValid, uCmd);	//CREATE AND OBJECT WHEN "&" SYMBOL IS DETECTED
						isValid = aHolder->execute(temp);	// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
						temp.clear();					//delete aHolder;
						j++;
					}
				}
				else if (cmds.at(j) == "#")
				{
					break;
				}
			}
			else
			{
				temp.push_back(cmds.at(j));
			}
		}
	   }
	   return isValid;
}


vector<string> parse (string uInput)
{
	vector<string> substr;			// USED TO HOLD PARSERS
	typedef tokenizer<char_separator<char> > Tok;		// USED TO HOLD COMMANDS
	char_separator<char> sep(" ", ";&|[]()", keep_empty_tokens);
	Tok tok(uInput, sep);
	for (Tok::iterator i = tok.begin(); i != tok.end(); i++)
	{
		if ((*i) != "")
		{
	//		cout << "TOK"<< (*i) << endl;
			substr.push_back((*i));
		}
	//				    substr.push_back(" ");
	}


/*
	for (unsigned i = 0; i < substr.size(); i++)	
	{
		size_t found = substr.at(i).find("test");	
		if (found != string::npos)
		{
			substr.push_back(substr.at(i).substr(4, substr.at(i).length()));
			substr.at(i) = "test";
		}
	}
*/	
	for (unsigned i = 0; i < substr.size(); i++)	
	{
		if (substr.at(i) == "test")
		{	
			while (i < substr.size()-2) 
			{
				if (substr.at(i+1) == "&" || substr.at(i+1) == "|" || substr.at(i+1) == ";")
				{
					
				}
				else
				{//	cout << "HIT IF " << endl;
					substr.at(i+1) += " " + substr.at(i+2);
					substr.erase(substr.begin() + (i+2));
				}
				i++;
			}	
		}
	}

//for (unsigned i = 0; i < substr.size(); i++)
//{
//	cout << "SUBSTR" << substr.at(i) << endl;
//}

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

//	cout << "PAST && AND ||" << endl;
	
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

/*	for (unsigned x = 0; x < substr.size(); x++)
	{
		if (substr.at(x) == "[" && substr.size() >= (x+3) )
		{
			substr.erase(substr.begin() + (x+3));
		}	
	}

*/
//substr.erase(substr.begin() + 3);


/*	for (unsigned i = 0; i < substr.size(); i++)
	{	
		if (isspace( substr.at(i).at(substr.at(i).length()-1) ) != 0) {substr.at(i).erase(substr.at(i).end() - 1);}
	}*/

	for (unsigned i = 0; i < substr.size(); i++)
	{
		while (substr.at(i).at(substr.at(i).length()-1) == ' ')
		{
			substr.at(i).erase(substr.at(i).end()-1);
		}		
	}
//ciout << "PAST FIRST FRONT CLEANING" << endl;
/*for (unsigned x = 0; x < substr.size(); x++)
{
	cout << "SUBSTR:" << substr.at(x) << "END" << endl; 
}*/
	for (unsigned i = 0; i < substr.size(); i++)
	{
		while (substr.at(i).at(0) == ' ')
		{
			substr.at(i).erase(substr.at(i).begin());
		}		
	}
//cout << "PAST FIRST ROUND OF CLEANING" << endl;
/*	for (unsigned i = 0; i < substr.size(); i++)	
	{
		size_t found = substr.at(i).find("test");			
		if (found != string::npos)
		{
			substr.insert(substr.begin() + (i+1), substr.at(i).substr(4, substr.at(i).length()));
			substr.at(i) = "test";
		}
	}
*/
/*	for (unsigned i = 0; i < substr.size(); i++)	
	{
		if (substr.at(i) == "test")
		{	
			while (i < substr.size()-2) 
			{
				if (substr.at(i) != "&&" || substr.at(i) != "||" || substr.at(i) != ";")
				{
					substr.at(i+1) += " " + substr.at(i+2);
					substr.erase(substr.begin() + (i+2));
				}
				i++;
			}	
		}
	}
*/

//cout << "PAST TEST PARSER" << endl;	

	for (unsigned i = 0; i < substr.size(); i++)
	{	
		if (isspace( substr.at(i).at(substr.at(i).length()-1) ) != 0) {substr.at(i).erase(substr.at(i).end() - 1);}
	}

	for (unsigned i = 0; i < substr.size(); i++ )
	{
		if (isspace(substr.at(i).at(0)) != 0) {substr.at(i).erase(substr.at(i).begin());}
	}

//	cout << "TESTING CMDS:" << endl;		
//	for (unsigned i = 0; i < substr.size(); i++)
//	{
//		cout << "BEFORE" << substr.at(i) << endl;
/*		if ((substr.at(i) != "&&" || substr.at(i) != "||" || substr.at(i) != ";" || substr.at(i) != "(" || substr.at(i) != ")")) 
		{
			if (i+1 < substr.size() && (substr.at(i+1) != "&&" || substr.at(i+1) != "||" || substr.at(i+1) != ";" || substr.at(i+1) != "(" || substr.at(i+1) != ")"))
			{
				substr.at(i) += " " + substr.at(i+1);
				substr.erase(substr.begin()+(i+1));
				i--;
			}
		}*/ 
	//	{
	//		substr.at(i) += " " + substr.at(i+1);
	//		substr.erase(substr.begin()+(i+1));
	//	}

//		cout << "AFTER" <<  substr.at(i) << endl;
//	}
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
//			cout << "TOK" << (*i) << endl;
			substr.push_back(*i);
		}
		
	}
	
	for (unsigned i = 0; i < substr.size(); i++)
	{
		while (substr.at(i).at(0) == ' ')
		{
			substr.at(i).erase(substr.at(i).begin());
		}		
	}

	for (unsigned i = 0; i < substr.size(); i++)
	{
		while (substr.at(i).at(substr.at(i).length()-1) == ' ')
		{
			substr.at(i).erase(substr.at(i).end()-1);
		}		
	}



//	cout << "TESTING SUBSTR" << endl;
//	for (unsigned j = 0; j < substr.size(); j++)
//	{
//		cout << substr.at(j) << "END"  << endl;
//	}
//	cout << "END SUBSTR" << endl;
	return substr;

}

bool pRun (bool isValid, string connector, vector<string> cmd)
{
//cout << "CONNECTOR" << connector << "END" << endl;
	if (connector == "||")
	{
		if (!isValid)
		{
			return run(isValid, cmd);
		}
		else
		{
//cout << "HIT ELSE" << endl;
			return isValid;
		}
	}	
	else if (connector == "&&")
	{
		if (isValid)	
		{
			return run(isValid, cmd);
		}
		else
		{
			return isValid;
		}
	}
	else if (connector == ";")
	{
		return run(isValid, cmd);
	}
	cout << "HIT EXCEPTION, RETURNING FALSE" << endl;
	return false;
}


void pExecute(bool isValid, vector<string> test)
{
	string connector;
	
	for (unsigned i = 0; i < test.size(); i++)
	{	
		vector<string> temp;
		if (test.at(i) == ")")
		{
			unsigned r = i-1;
			while (test.at(r) != "(")
			{
				temp.insert(temp.begin(), test.at(r));
				r--;
			}
			if (temp.empty())
			{
				cout << "Syntax error near ')'" << endl;
				return;
			}
			isValid = run(isValid, temp);
			while (test.at(i) != "(" )
			{
	//			cout << "BEING ERASED" << test.at(0+i) << endl;
				test.erase(test.begin() + (i));
				i--;
			}
			test.erase(test.begin() + (i));
			if (!test.empty())
			{
//	cout << "HIT IF" << " I" << i <<  endl;
				connector = test.at(i);
				test.erase(test.begin() + (i));
			}
			break;
		}

	}




	for (unsigned i = 0; i < test.size(); i++)
	{

		vector<string> temp;
		if (test.at(i) == "(")
		{	
			for (unsigned k = 0; k < test.size(); k++)
			{
				if (test.at(k) == ")")
				{
		//cout << "HIT SECOND IFiASDFASDFASDFASDFASDFASDFSADF" << endl;
					unsigned r = k-1;
					while (test.at(r) != "(")
					{
						temp.insert(temp.begin(), test.at(r));
						r--;
					}
					if (temp.empty())
					{
						cout << "Syntax error near ')'" << endl;
						return;
					}
					else
					{
						isValid = pRun(isValid, connector, temp);
						while (test.at(k) != "(" )
						{
//							cout << "BEING ERASED" << test.at(k) << endl;
							test.erase(test.begin() + (k));
							k--;
						}
						test.erase(test.begin() + (k));
					}
					if (!test.empty())
					{
						connector = test.at(k);
						test.erase(test.begin() + (k));
					}
					
				}
			}
		}
		else if (test.at(i) != "(")
		{
			for (unsigned k = 0; k < test.size(); k++)
			{
				if (test.at(k) == "(" || test.at(k) == ")")
				{
					test.erase(test.begin() + k);
				}
			}
			isValid = run(isValid, test);
			break;			
		}
	}
}	
/*
			temp = parse(test.at(i-1));
			isValid = pRun(isValid, connector, temp);
			test.erase(test.begin() + (i-2), test.begin() + (i));
			if (!test.empty())	
			{
				connector = test.at(0);
				test.erase(test.begin());
			}

//begin cpp
	vector< vector<string> > pcmds;
	vector<int> positions;
	for (unsigned i = 0; i < test.size(); i++)
	{
		if (test.at(i) == "(")
		{
			positions.push_back(i);
		}	
	}
	for (unsigned i = positions.size()-1; i >= 0; i++)
	{	
//	cout << "INPUT" << test.at(i) << "END" <<  endl;
		vector<string> temp;
		if ( i+1 < test.size()-1)
		{
			if (test.at(i+1) != ")")
			{
				temp = parse(test.at(i+1));
				isValid = run(isValid, temp);
				test.erase(test.begin()+(positions.at(i)), test.begin() + (positions.at(i)+2));
				break;		
			}
		}
	}
	
	for (unsigned i = positions.size()-2; i >= 0; i++)
	{	
		vector<string> temp;
		if ( i+1 < test.size()-1)
		{
			if (test.at(i+1) != ")")
			{
				vector<string> temporary;
				temp = parse(test.at(i+1));
				temporary.push_back(temp.at(1));
				isValid = pRun(isValid, temp.at(0), temporary);
				test.erase(test.begin()+positions.at(i), test.begin() + (positions.at(i)+2));
				break;		
			}
		}
	}

				

else if (test.at(i) == "&&" || test.at(i) == "||" || test.at(i) == ";")
					{
cout << "HIT IF" << endl;
						temp.push_back(test.at(i));
						pcmds.push_back(temp);
					}	
				}

*/			
					
/*
				for (unsigned i = 0; i < test.size(); i++)
				{	
					cout << "INPUT" << test.at(i) << "END" <<  endl;
					vector<string> temp;
					if ( test.at(i) == "(")
					{
						temp.push_back(test.at(i+1));
						pcmds.push_back(temp);
					}
					else if (test.at(i) == "&&" || test.at(i) == "||" || test.at(i) == ";")
					{
cout << "HIT IF" << endl;
						temp.push_back(test.at(i));
						pcmds.push_back(temp);
					}	
				}

					for (unsigned i = 0; i < pcmds.size(); i++)
				{
					//cout << "TEST" << test.at(i) << endl;
					cout << "PCMDS:";
					for (unsigned t = 0; t < pcmds.at(i).size(); t++)
					{
						cout << pcmds.at(i).at(t) << " ";
					}
cout << endl;
				}

				for (unsigned i = 0; i < pcmds.size(); i++)
				{
					pcmds.at(i) = parse(pcmds.at(i).at(0));
					isValid = run(isValid, pcmds.at(i));
					if (i+1 < pcmds.size()-1)
					{
						isValid = pRun(isValid, pcmds.at(i+1).at(0), pcmds.at(i+2));
						i += 2;		
					}
				}

			}
		}
}
*/



//	2/26/17 fix the spacing issue in parse, IE echo

int main()
{
	char uname[100];
	string uInput = "";
	char* ulgn = getlogin();
	gethostname(uname, 100);
	puts(uname);
	bool isValid = true;			// USED IN && AND || TO DETERMINE IF PREVIOUS COMMAND WAS VALID
	int opCounter = 0;
	int clCounter = 0;
	cout << "Beginning Terminal" << endl << "Enter 'quit' to exit the program" << endl;
	cout << ulgn << "@" << uname << "$ ";
	while (getline(cin, uInput))
	{
//cout << "NEW INPUT" << endl;
		if (!uInput.empty() && uInput.at(0) != '#')
		{
			//vector< vector <string> > pcmd;
			vector<string> bcmd = parse(uInput);
//			for (unsigned m = 0; m < bcmd.size(); m++)
//			{
//				cout <<"BCMD" << bcmd.at(m) << "END" << endl;
//			}	
			vector<string> test = parse(uInput);
		/*	for (unsigned i = 0; i < test.size(); i++)
			{
				cout << "TEST" << test.at(i) << endl;
			}
		*/	
			for (unsigned i = 0; i < test.size(); i++)
			{
				if (test.at(i) == "(")
				{
					opCounter += 1;
				}
				else if (test.at(i) == ")")
				{
					clCounter += 1;			
				}
			}
	
		/*	for (unsigned i = 0; i < test.size(); i++)
			{
				cout << "TESTV" << test.at(i) << "END" << endl;
			}
*/
			if (opCounter != 0 && clCounter != 0)
			{
				if (opCounter != clCounter)
				{
					cout << "ERROR UNEVEN AMOUNT OF OPEN AND CLOSE PARENS" << endl;
				}
				else if (test.at(0) == "(") 
				{
					pExecute(isValid, test);
				}
				else
				{
					bool error = false;
					for (unsigned i = 0; i < test.size(); i++)
					{
						if (test.at(i) == ")")
						{		
							if (test.at(i-1) ==  "(")
							{
								cout << "Syntax error near ')'" << endl;
								error = true;
								break;
							}
						}
					}
					if (!error)
					{
						for (unsigned i = 0; i < test.size(); i++)
						{
							if (test.at(i) == "(" || test.at(i) == ")")
							{
								test.erase(test.begin()+i);
							}
						}
						isValid = run(isValid, test);
					}
				}
			}

			else
			{
				isValid = run(isValid, bcmd);
			}		

			if (isValid) {} // temp
//			vector<string> temp = parse(uInput);
//			bool holder = run(isValid, temp);
//			if (holder) {}
			//cout << "RUNNING CMDS" << endl;
			//isValid = run(isValid, temp);
		}
		opCounter = 0;
		clCounter = 0;
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


