#include "cmdline.hpp"

class Semicolon : public Cmdline
{
	public:
		Semicolon();
		void execute(string uCmd);
	protected:
		Cmdline* Lchild;
		Cmdline* Rchild;
};
