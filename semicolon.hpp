#include "cmd.hpp"

class Semicolon : public Cmd
{
	public:
		Semicolon(Cmd* Right, Cmd* Left);
		bool execute();
	protected:
		Cmd* Lchild;
		Cmd* Rchild;
};
