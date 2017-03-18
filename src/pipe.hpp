#ifndef _PIPE_H_
#define _PIPE_H_

#include "cmdline.hpp"


class Pipe
{
public:
	Pipe();
	bool execute(const vector<string> &cmd, string &input);
	//virtual bool isValid() = 0;

};

#endif
