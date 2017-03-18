#ifndef _TEST_H_
#define _TEST_H_

#include "cmdline.hpp"
#include <vector> 

class Test : public Cmdline
{
public:
	Test();
	Test(string k);
	bool execute(vector<string> path);	
};

#endif
