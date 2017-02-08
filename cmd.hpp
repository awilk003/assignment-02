#include "cmdline.hpp"

class Cmd
{
	public:
		Cmd();
		void execute();
	protected:
		Cmdline* L;
		Cmdline* R;
};
