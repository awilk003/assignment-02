#include "cmd.hpp"


class Pound : public Cmdline
{
	public:
		Pound(bool Right, Cmdline* Left);
		bool execute();
		bool isValid();
	protected:
		Cmdline* Lchild;
		Cmdline* Rchild;
};
