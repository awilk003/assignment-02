#include "cmdline.hpp"

class Semicolon : public Cmdline
{
	public:
		Semicolon(bool Left, Cmdline* Right);
		bool execute(string cmd);
	protected:
		bool Lchild;
		Cmdline* Rchild;
};
