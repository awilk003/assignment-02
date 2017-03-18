#ifndef _PIPE_H_
#define _PIPE_H_

#include "cmdline.hpp"


class Pipe
{
public:
	Pipe();
	virtual bool execute(vector<string> cmd, string &input) = 0;
	//virtual bool isValid() = 0;

};

#endif
