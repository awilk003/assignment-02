#ifndef _BACKUP_H_
#define _BACKUP_H_


#include "cmdline.hpp"



class Backup
{
private:
	string file;
public:
	Backup();
	Backup(const string &filename);
	bool execute(const vector<string>);
	//virtual bool isValid() = 0;
};










#endif
