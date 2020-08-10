# Basic Shell

This project has been realized in the scope of the course CMPS 272 "Operating Systems", at the American University of Beirut. The main shell is written in C, and calls separate Java files to execute most commands. The shell also supports pipes to re-route output of certain commands as input to other commands.

### Makefile arguments :

- *all* : Compile the main shell and all its commands.  

- *cleanFiles*: Remove all generated files from previous compilations

### Supported commands :

- *ls* : List all files and folders in the current directory.

- *generate* : Generate two random values.

- *sum* : Takes two values, and outputs the sum.

- *subtract* : Takes two values, and outputs the difference.

- *tee* : This command is directly implemented in the main shell in C, but it executes in another process with a fork and takes its input from the output of the other commands listed above.
