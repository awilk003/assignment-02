#include "cmdline.hpp"

class Semicolon : public Cmdline
{
	public:
		Semicolon();
		void execute();
	protected:
		Cmdline* Lchild;
		Cmdline* Rchild;
};
