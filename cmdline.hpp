#ifndef CMDLINE_H
#define CMDLINE_H

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class Cmdline
{
	public:
		Cmdline();
		virtual void execute() = 0;

};

#endif
