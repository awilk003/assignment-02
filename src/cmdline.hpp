#ifndef _CMDLINE_H_
#define _CMDLINE_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;

class Cmdline
{
	public:
		Cmdline();
		virtual bool execute(vector<string> cmd) = 0;
		//virtual bool isValid() = 0;
};

#endif
