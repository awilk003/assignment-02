#include "cmdline.hpp"

class Semicolon : public Cmdline
{
	public:
		Semicolon(bool Left, Cmdline* Right);
		bool execute();
		bool isValid();
	protected:
		bool Lchild;
		Cmdline* Rchild;
};
