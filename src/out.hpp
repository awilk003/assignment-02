#ifndef _ROUT_H_
#define _ROUT_H_


#include "cmdline.hpp"



class Rout
{
private:
	string file;
public:
	Rout();
	Rout(const string &filename);
	void truncate(const string &filename);
	void append(const string &filename);
	bool execute(const vector<string> &cmd, const char &flag);
	//virtual bool isValid() = 0;
};










#endif
