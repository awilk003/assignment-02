#include <iostream>
#include "cmdline.hpp"
#include "cmd.hpp"
#include "semicolon.hpp"
#include "pound.hpp"
#include "or.hpp"
#include "and.hpp"
#include "test.hpp"
#include "in.hpp"
#include "out.hpp"
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

//Print function used for debugging
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

bool isConnector (string input)
{
	if (input == ";" || input == "||" || input == "&&")
	{
		return true;
	}
	return false;
}

string findSymbol(vector<string> cmds, int j)
{
	string listofsymbols = "<>>";
	string symbol;
	for (unsigned k = j; k < cmds.size(); k++)
	{
		if (listofsymbols.find(cmds.at(k)) != string::npos)
		{
			symbol = cmds.at(k);
			break;
		}
		else if (isConnector(cmds.at(k)))
		{
			break;
		}
	}
	return symbol;
}



bool run(bool isValid, vector<string> cmds )
{
	vector<string> temp; //TEMPORARY VECTOR OF COMMANDS TO BE PASSED INTO THE EXECUTE FUNCTION
	if (cmds.at(0) == "quit")
	{
		exit(1); //IF FIRST COMMAND IS QUIT EXIT IMMEDIATLY
		cout << "SHOULD HAVE QUIT" << endl;
	}

	unsigned j = 0;
	string symbol = findSymbol(cmds, j);
	if (!symbol.empty())
	{ 
		string path;	
		for(; j < cmds.size(); j++)
		{
			if (cmds.at(j) == symbol)
			{
				path = cmds.at(j+1);
				break;
			}
			else if (isConnector(cmds.at(j)))
			{
				break;
			}
			else
			{	
				temp.push_back(cmds.at(j));
			}
		}
		if (symbol == "<")
		{
			Input* inHolder = new Input(path);
			inHolder->execute(temp);
			temp.clear();			
		//	delete inHolder;
		}
		else
		{
			if (symbol == ">")
			{
				cout << "SINGLE GREATE" << endl;
				Rout* rHolder = new Rout(path);
				rHolder->execute(temp, 't');
			}
			else 
			{
				Rout* rHolder = new Rout(path);
				rHolder->execute(temp, 'a');
			}
			temp.clear();
		//	delete rHolder;
		}
	}

	//HARDCODED FIRST COMMAND WITH NO CONNECTOR IN THE BEGGINNING
	else if (cmds.at(j) == "[" || cmds.at(j) == "test")
	{
		//CHECKS FOR THE SPECIAL COMMANDS OF [] AND TEST
		if (cmds.at(j) == "[")
		{
			j++;
			while (cmds.at(j) != "]")
			{
				temp.push_back(cmds.at(j));
				j++;
			}
			Test* tHolder = new Test("A");
			isValid = tHolder->execute(temp);
		//	delete tHolder;
			temp.clear();
			j++;
		}
		else
		{	
			j++;
			while (j < cmds.size()) 
			{
				if (isConnector(cmds.at(j)))
				{
					break;
				}
				temp.push_back(cmds.at(j));
				j++;
			}		
			Test* tHolder = new Test("A");

			isValid = tHolder->execute(temp);
		//	delete tHolder;
			temp.clear();	
		}
	}
	else	
	{
		//IF COMMAND CAN BE RUN NORMALLY, RUNS THE NORMAL COMMANDS
		Cmd* first = new Cmd(cmds.at(j)); 
		while (j < cmds.size())
		{
			if (isConnector(cmds.at(j)))
			{	
				break;
			}
			temp.push_back(cmds.at(j));
			j++;
		}
		isValid = first->execute(temp); // SET ISVALID TO WHETHER OR NOT THE COMMAND WAS VALID OR NOT FOR POSSIBLE NEXT COMMAND}
	//	delete first;
		temp.clear();
	}
	j--;
	
	if (cmds.size()  > 2) // IF ONLY ONE COMMAND THEN WILL NOT RUN
	{		
		for (; j < cmds.size(); j++)	// ITERATING THROUGH THE PARSER VECTOR, CREATING AND RUNNING THE CORRECT COMMANDS DEPENDING ON THE PARSER, EACH CASE CHECKS FOR THE RIGHT 
						// PARSER AND CONSTRUCTS THE OBJECT ACCORDINGLY. EACH RUN ALSO CHECKS FOR THE "QUIT" COMMAND
		{ 		
		   	if (isConnector(cmds.at(j))) 
			{
				Cmd* uCmd = new Cmd(cmds.at(j));					// CREATE NEW COMMANDS FOR EACH PARSER
				if (cmds.at(j) == ";")
				{
					j++;
					if (cmds.at(j) == "quit") 					// QUITS IF QUIT IS DETECTED
					{
						exit(1);
					}
					
					symbol = findSymbol(cmds, j);
					
					if (!symbol.empty())
					{
						if (symbol == "<")
						{
							string path;	
							for(; j < cmds.size(); j++)
							{
								if (cmds.at(j) == "<")
								{
									path = cmds.at(j+1);
									break;
								}
	
								if (isConnector(cmds.at(j)))
								{
									break;
								}
								else
								{
									temp.push_back(cmds.at(j));
								}
							}	

							Input* inHolder = new Input(path);
							inHolder->execute(temp);
							temp.clear();	
						}
					}
		
					else if (cmds.at(j) == "[")						//CHECKS FOR SPECIAL COMMAND []
					{	
						j++;
						while (cmds.at(j) != "]")
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						Test* tHolder = new Test("A");
						isValid = tHolder->execute(temp);
				//		delete tHolder;
						temp.clear();
						j++;
					}		
					else if (cmds.at(j) == "test")					// CHECKS FOR SPECIAL COMMAND TEST
					{	
						j++;
						while (j < cmds.size()) 
						{
							if (isConnector(cmds.at(j)))
							{
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}		
						Test* tHolder = new Test("A");
						isValid = tHolder->execute(temp);
					//	delete tHolder;
						temp.clear();	
					}
					else 								// CREATED AND RUNS SEMICOLON OBJECT WITH PAST ISVALID PARAMETER
					{
						while (j < cmds.size())
						{
							if (isConnector(cmds.at(j)))
							{	
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}
						if (!temp.empty())
						{
							Semicolon* sHolder = new Semicolon(isValid, uCmd);	// CREATE SEMICOLON OBJECT WHEN SEMICOLON IS DETECTED;
							isValid = sHolder->execute(temp);			// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
					//		delete sHolder;
							temp.clear();			
						}
					}
					j--;
				}
				else if (cmds.at(j) == "||" )
				{
					j++;
					if (cmds.at(j) == "quit")					// CATCHES AND QUITS IF "QUIT" IS DETECTED
					{
						exit(1);
					}
					symbol = findSymbol(cmds, j);
					
					if (!symbol.empty())
					{
						if (symbol == "<")
						{
							string path;	
							for(; j < cmds.size(); j++)
							{
								if (cmds.at(j) == "<")
								{
									path = cmds.at(j+1);
									break;
								}
	
								if (isConnector(cmds.at(j)))
								{
									break;
								}
								else
								{
									temp.push_back(cmds.at(j));
								}
							}	

							Input* inHolder = new Input(path);
							inHolder->execute(temp);
							temp.clear();	
						}
					}
		

					else if (cmds.at(j) == "[")						// CHECKS FOR SPECIAL COMMAND []
					{	
						j++;
						if (!isValid)
						{
							while (cmds.at(j) != "]")
							{
								temp.push_back(cmds.at(j));
								j++;
							}
							Test* tHolder = new Test("A");
							isValid = tHolder->execute(temp);
							temp.clear();
					//		delete tHolder;
							j++;
						}
					}
					else if (cmds.at(j) == "test")					// CHECKS FOR SPECIAL COMMAND TEST
					{		
						if (!isValid)
						{
							j++;
							while (j < cmds.size()) 
							{
								if (isConnector(cmds.at(j)))
								{
									break;
								}
								temp.push_back(cmds.at(j));
								j++;
							}		
							Test* tHolder = new Test("A");
							isValid = tHolder->execute(temp);
				//			delete tHolder;
							temp.clear();
						}
					}
					else								// CREATES OR OBJECT AND RUNS IT
					{
						while (j < cmds.size())
						{
							if (isConnector(cmds.at(j)))
							{	
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}
						if (!temp.empty())
						{
							Or* oHolder = new Or(isValid, uCmd); 		//CREATE OR OBJECT WHEN "|" SYMBOL IS DETECTED
							isValid = oHolder->execute(temp);		//EXECUTES COMMAND AND CHECKS/SETS VALIDITY
						//	delete oHolder;
							temp.clear();						
						}
					}
					j--;
				}
				else if (cmds.at(j) == "&&")
				{
					j++;
					if (cmds.at(j) == "quit")					//QUITS IF "QUIT" IS DETECTED
					{
						exit(1);
					}

					symbol = findSymbol(cmds, j);
					
					if (!symbol.empty())
					{
						if (symbol == "<")
						{
							string path;	
							for(; j < cmds.size(); j++)
							{
								if (cmds.at(j) == "<")
								{
									path = cmds.at(j+1);
									break;
								}
	
								if (isConnector(cmds.at(j)))
								{
									break;
								}
								else
								{
									temp.push_back(cmds.at(j));
								}
							}	

							Input* inHolder = new Input(path);
							inHolder->execute(temp);
							temp.clear();	
						}
					}
		


					else if(cmds.at(j) == "[")						//CHECKS FOR AND RUNS SPECIAL COMMAND []
					{	
						j++;
						while (cmds.at(j) != "]")
						{
							temp.push_back(cmds.at(j));
							j++;
						}
						Test* tHolder = new Test("A");
						isValid = tHolder->execute(temp);
					//	delete tHolder;
						temp.clear();
						j++;
					}
					else if (cmds.at(j) == "test")					//CHECKS FOR AND RUNS SPECIAL COMMAND TEST
					{	
						j++;
						while (j < cmds.size()) 
						{
							if (isConnector(cmds.at(j)))
							{
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}		
						Test* tHolder = new Test("A");
						isValid = tHolder->execute(temp);
					//	delete tHolder;
						temp.clear();
					}
					else								//CREATES THE "&&" OBJECT AND RUNS ACCORDING TO VALIDITY
					{
						while (j < cmds.size())
						{
							if (isConnector(cmds.at(j)))
							{	
								break;
							}
							temp.push_back(cmds.at(j));
							j++;
						}

						if (!temp.empty())
						{
							And* aHolder = new And(isValid, uCmd);		//CREATE AND OBJECT WHEN "&" SYMBOL IS DETEC
							isValid = aHolder->execute(temp);		// EXECUTES COMMAND AND CHECKS/SETS VALIDITY
						//	delete aHolder;
							temp.clear();				
						}
					}
					j--;
				}
				else if (cmds.at(j) == "#")						//IF # DETECTED STOPS RUNNING
				{
					break;
				}
				//delete uCmd;
			}
		}
	   }
	   return isValid;
}


vector<string> parse (string uInput)
{
	vector<string> substr;										// USED TO HOLD PARSERS
	typedef tokenizer<char_separator<char> > Tok;							// USED TO HOLD COMMANDS
	char_separator<char> sep(" ", ";&|[]()#<>", keep_empty_tokens);					// USED TO SEPERATE " ", AND SEPERATE AND KEEP:  ;, &, |, [, ], (, ), AND #
	Tok tok(uInput, sep);							
	for (Tok::iterator i = tok.begin(); i != tok.end(); i++)					// PUSHES BACK THE SEPERATED WORDS, STOPPING IF # IS DETECTED
	{
		if ((*i) == "#")
		{
			break;
		}
		else if ((*i) != "")
		{
			substr.push_back((*i));							// PUSHES BACK EACH SEPERATED COMMAND TO RETURNED SUBSTR
		}	

	}


	for (unsigned i = 0; i < substr.size()-1; i++)							// LOOPS THROUGH TO CHECK FOR  && AND ||, RATHER THAN JUST & AND |
	{
		if ((substr.at(i) == "&" || substr.at(i) == "|" || substr.at(i) == ">") && substr.at(i) == substr.at(i+1))
		{
			substr.at(i) = substr.at(i) + substr.at(i+1);
			substr.erase(substr.begin() + (i+1));
		}
/*
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
*/
	}


	int last = substr.size()-1;									// CHECKS THE LAST PART THE COMMANDS IN ORDER TO CHECK FOR ENDING "&&" OR "||"

	if (substr.at(last) == "&" || substr.at(last) == "|")
	{
		substr.at(last-1) = substr.at(last-1) + substr.at(last);	
		substr.erase(substr.begin() + last);
	}
												// ERASES ANY ERRANT SPACES THAT MAY HAVE MADE IT IN
	for (unsigned i = 0; i < substr.size(); i++)
	{
		while (substr.at(i).at(substr.at(i).length()-1) == ' ')
		{
			substr.at(i).erase(substr.at(i).end()-1);
		}		
	}

	for (unsigned i = 0; i < substr.size(); i++)
	{
		while (substr.at(i).at(0) == ' ')
		{
			substr.at(i).erase(substr.at(i).begin());
		}		
	}

	print(substr);
	return substr;

}

// A SPECIAL VERSION OF RUN THAT IS USD IN ORDER TO TO MAINTAIN THE PRIORITY THAT COMES WITH THE USE OF PARENTHESIS
bool pRun (bool isValid, string connector, vector<string> cmd)
{
	if (connector == "||")										// CHECKS FOR THE || CONNECTOR AND RUNS ACCORDINGLY
	{	
		if (!isValid)
		{
			return run(isValid, cmd);
		}
		else
		{
			return isValid;
		}
	}	
	else if (connector == "&&")									// CHECKS FOR THE && CONNECTOR AND RUNS ACCPRDINGLY
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
	else if (connector == ";")									// CHECKS FOR THE ; CONNECTOR AND RUNS ACCODRINGLY
	{
		return run(isValid, cmd);
	}
	cout << "HIT EXCEPTION, RETURNING FALSE" << endl;						// IF THIS IS EVER DISPLAYED AND ERROR HAS OCCURED
	return false;
}

// A SPECIAL VERSION OF EXECUTE THAT ACCOUNTS OF THE PRIORITY OF THE USE OF PARANTHESIS
void pExecute(bool isValid, vector<string> test)				
{
	string connector;										// USED TO HOLDER THE CONNECTOR IN THE EVENT OF A MULTIPLE COMMAND INPUT
	for (unsigned i = 0; i < test.size(); i++)							// USED TO CREATE A SUBVECTOR THAT RUNS ALL COMMANDS WITHIN A PARANTHESIS
	{	
		if (test.at(i) == "(")
		{
			vector<string> temp;								// TEMPORARY COMMAND VECTOR
			while (test.at(i) != ")")
			{
				i++;
			}
			if (test.at(i) == ")")								// RUNS UNTIL A CLOTHES PARANTEHSIS, AND THEREFORE END OF PRIORITY COMMAND
			{
				unsigned r = i-1;
				while (test.at(r) != "(")						// RUNS BACKWARDS TO OBTAIN ALL COMMANDS AND ADDS THEM TO TEMP
				{
					temp.insert(temp.begin(), test.at(r));
					r--;
				}
				if (temp.empty())							// CASE IN EVENT USED INPUTS ()
				{
					cout << "Syntax error near ')'" << endl;
					return;
				}
				isValid = run(isValid, temp);						// RUNS NOW PRIORITIZED COMMAND
				while (test.at(i) != "(" )
				{
					test.erase(test.begin() + (i));					// ERASES PRIORITIZED COMMAND FROM MAIN VECTOR 
					i--;
				}
				test.erase(test.begin() + (i));						// ERASES LEFT OVER "("
				if (!test.empty())							// CHECKS IF THERE ARE MORE COMMANDS TO RUN, IF SO SETS CONNECTOR AND ERASES IT
				{
					connector = test.at(i);
					test.erase(test.begin() + (i));
				}
				break;										// END AFTER FIRST COMMAND
			}
		}
		else
		{
				vector<string> temp;
				while (i < test.size())
				{
					if (test.at(i) == "&&" || test.at(i) == "||" || test.at(i) == ";")
					{	
						break;
					}
	 				temp.push_back(test.at(i));
					i++;	
				}
				while (i != 0)
				{
					test.erase(test.begin());
					i--;
				}
				isValid = run(isValid, temp);
				temp.clear();
				if (!test.empty())
				{
					connector = test.at(0);
				//	cout << "CONNECTOR" << connector << endl;
					test.erase(test.begin());
				}
				break;
		}

	}




	while (!test.empty())							// NOW BEINGS RUN THROUGH REST OF COMMANDS, IF THEY EXIST
	{
		vector<string> temp;									// SIMILAIR PROCESS TO PREVIOUS, EXCEPT NOW ACCOUTING FOR EXTRA CONNECTORS
		if (test.at(0) == "(")
		{	
			for (unsigned k = 0; k < test.size(); k++)					// ITERATES THROUGH TEST
			{
				if (test.at(k) == ")")							// SIMILARLY CHECKS THROUGH TO FIND END OF PARENS
				{
					unsigned r = k-1;
					while (test.at(r) != "(")
					{
						temp.insert(temp.begin(), test.at(r));			// PUSH_BACK ALL COMMANDS THAT ARE BETWEEN () TO TEMP
						r--;
					}	
					if (temp.empty())						// CHECKS CASE ()
					{
						cout << "Syntax error near ')'" << endl;
						return;
					}
					else
					{
						isValid = pRun(isValid, connector, temp);		// RUN COMMANDS IN TEMP
						temp.clear();
						while (test.at(k) != "(" )
						{
							test.erase(test.begin() + (k));			// ERASES ALL COMMANDS THAT WERE JUST EXECUTED FOR NEXT LOOP
							k--;
						}
						test.erase(test.begin() + (k));				// ERASES ERRANT ")"
					}
					if (!test.empty())						// IF THE VECTOR IS EMPTY, FINISHE DURNNING ELSE SET UP FOR NEXT ITERATION
					{
						connector = test.at(k);
						test.erase(test.begin() + (k));
					}
				}
			}
		}
		else if (test.at(0) != "(")								// IF OPEN PARENS IS NOT DETECTED, THE LOGICALLY PRIORITY NO LONGER MATTER
		{
			while( !test.empty() && (test.at(0) != "&&") && (test.at(0) != "||") && (test.at(0) != ";"))
			{
				temp.push_back(test.at(0));
				test.erase(test.begin());
			}
			isValid = pRun(isValid, connector, temp);					// RUNS REMAINING COMMANDS
			temp.clear();
			if (!test.empty())
			{
				connector = test.at(0);
				test.erase(test.begin());
			}
				
		}
	}
}	


//	2/26/17 fix the spacing issue in parse, IE echo

int main()
{
	char uname[100];
	string uInput = "";
	char* ulgn = getlogin();
	gethostname(uname, 100);
	puts(uname);
	bool isValid = true;										// USED IN && AND || TO DETERMINE IF PREVIOUS COMMAND WAS VALID
	int opCounter = 0;										// USED TO COUNT NUMBER OF "("
	int clCounter = 0;										// USED TO COUNT NUMBER OF ")"
	int opsCounter = 0;										// USED TO COUNT NUMBER OF "["
	int clsCounter = 0;										// USED TO COUNT NUMBER OF "]"
	cout << "Beginning Terminal" << endl << "Enter 'quit' to exit the program" << endl;		// BEGGINNING OUTPUT MESSAGE
	cout << ulgn << "@" << uname << "$ ";								// EXTRA CREDIT
	while (getline(cin, uInput))									// LOOPS WHILE GETTING USER INPUT
	{
		if (!uInput.empty() && uInput.at(0) != '#')						
		{
			vector<string> test = parse(uInput);						// TEST IS THE COMMAND VECTOR
			
			for (unsigned i = 0; i < test.size(); i++)					// CHECKS FOR IF NUMBER OF "[" AND "]" ARE THE SAME
			{
				if (test.at(i) == "#")
				{
					break;
				}
				else if (test.at(i) == "[")							
				{
					opsCounter++;
				}
				else if (test.at(i) == "]")
				{
					clsCounter++;
				}
			}

			if (opsCounter != clsCounter)							
			{
				cout << "Syntax error near ']'" << endl;	
			}
			else
			{	
				for (unsigned i = 0; i < test.size(); i++)
				{
					if (test.at(i) == "#")
					{
						break;
					}
					else if (test.at(i) == "(")
					{
						opCounter += 1;
					}
					else if (test.at(i) == ")")
					{
						clCounter += 1;			
					}
				}
		
				if (opCounter != 0 && clCounter != 0)					// CHECKS IF THE NUMBER OF "(" AND ")" ARE THE SAME
				{
					if (opCounter != clCounter)
					{
						cout << "ERROR UNEVEN AMOUNT OF OPEN AND CLOSE PARENS" << endl;
					}
					else 
					{
						pExecute(isValid, test);				// IF PARENS ARE DETECTED THEN RUN THE PRIORITIZED VERSION OF RUN
					}
/*
					else
					{
						bool error = false;					// USED TO CHECK FOR CASE "()"
						for (unsigned i = 0; i < test.size(); i++)		// CHECKS TO SEE IF CASE "()" IS TRUE
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
					}
*/
				}
				else
				{
					isValid = run(isValid, test);					// IF PARENS ARE NOT DETECTED THEN RUN NORMALLY
				}	
			}	
		}
		opCounter = 0;										// CLEARED FOR NEXT ITERATION	
		clCounter = 0;										// CLEARED FOR NEXT ITERATION
		opsCounter = 0;										// CLEARED FOR NEXT ITERATION
		clsCounter = 0;										// CLEARED FOR NEXT IERATION
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


