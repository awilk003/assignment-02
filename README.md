# rshell

Rshell is a custom bash terminal.  It can output commands as if using the bash terminal itself.

# Features Include:

*Running single commands

*Running multiple commands with connectors (; || && # are implemented currently)
	* ';' The command following the semicolon will execute 
	* '||' The command following the vertical bars will execute only if the command before the vertical bars fail
	* '&&' The command following the ampersands will execute only if the command before the ampersands succeeds
	* '#' Any input after the pound sign will treated as a comment

*Exit command to close program

*Test cases provided in the "tests" directory

# Bugs:

*Using the command "echo" does not seem to work
