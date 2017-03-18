#include "test.hpp"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



class Input : public Test 
{
	public:
		Input(string file);
		bool execute(vector<string> cmd);
	private:
		bool Lchild;
		vector<string> infile;
		string filename;
		bool check(vector<string> path);
};
