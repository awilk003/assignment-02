#include "cmd.hpp"

class Semicolon : public Cmdline
{
	public:
		Semicolon(bool Left, Cmdline* Right);
		bool execute();
		bool isValid();
	protected:
		Cmdline* Lchild;
		Cmdline* Rchild;
};
