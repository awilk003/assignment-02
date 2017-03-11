#ifndef _ROUT_H_
#define _ROUT_H_


#include "cmdline.hpp"



class Rout
{
public:
	Rout();
	void truncate(string filename);
	void append(string filename);
	bool execute(vector<string> cmd);
	//virtual bool isValid() = 0;
};










#endif
