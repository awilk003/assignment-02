#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Cmdline
{
	public:
		Cmdline( string cmd1, string cmd2 = "" );
		virtual void execute() = 0;
	protected:
		string Lcmd;
		string Rcmd;
};
