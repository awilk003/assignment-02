#include "cmdline.hpp"

class Semicolon : public Cmdline
{
	public:
		Semicolon(bool Left, Cmdline* Right);
		void execute(string cmd);
		bool isValid();
	protected:
		bool Lchild;
		Cmdline* Rchild;
};
