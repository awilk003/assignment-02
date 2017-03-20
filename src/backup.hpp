#ifndef _BACKUP_H_
#define _BACKUP_H_


#include "cmdline.hpp"
#include "in.hpp"


class Backup
{
public:
	Backup();
	Backup(const string &filename);
	bool execute(const vector<string> &lhs, const vector<string> &rhs, int (& currFD)[2]);
	string checkSymbol(vector<string> input, string& path);
	//virtual bool isValid() = 0;
};


class mPipe : public Backup
{
	public:
	mPipe();
	bool execute(const vector<string> &lhs, const vector<string> &rhs, int (& currFD)[2]);

};









#endif
