#ifndef _BACKUP_H_
#define _BACKUP_H_


#include "cmdline.hpp"



class Backup
{
public:
	Backup();
	Backup(const string &filename);
	bool execute(const vector<string> &lhs, const vector<string &rhs);
	//virtual bool isValid() = 0;
};










#endif
