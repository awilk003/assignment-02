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

*Testing paths can be done by typing "test" followed by any flags and the file name 		ex:(test -f bin.rshell)

*Testing paths can also be done by putting any flags and the file name in between '[' and ']'	ex:([-f bin/rshell])
* Flags include:
 * '-e' Tests to see if the file or directory exists
 * '-f' Tests to see if the file exists
 * '-d' Tests to see if the directory exists
 * flags will default to '-e' if none are provided

*Can use redirection and piping
* '<'  Is used for input redirection 	(from file to program)
* '>'  Is used for output redirection   (from program to file, truncated)
* '>>' Is used for output redirection   (from program to file, appended)
* '|'  Is used for piping 		(output of program is input of chained program)

# Bugs:

*If the user creates a syntax error (ls &&& ps; vim somefile), the program will run until it reaches the syntax error (will run the command ls only)

*Can not make a directory or enter one.

*Command 'help' will not be recognized.

*When chaining commands with multiple '|', the output may have multiple instances.