#ifndef _ROUT_H_
#define _ROUT_H_


#include "cmdline.hpp"



class Rout
{
public:
	Rout();
	void truncate(const string &filename);
	void append(const string &filename);
	bool execute(const vector<string> &cmd);
	//virtual bool isValid() = 0;
};










#endif
