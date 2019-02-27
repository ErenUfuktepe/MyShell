# MyShell

My shell program displays the command line prompt “myshell>” and waits for the user's
command. It reads the user’s next command, parses it into separate tokens that are used to fill the
argument vector for the command to be executed, and executes it.

Program supports the following built-in commands 

1) cd <directory> : change the current directory to <directory>

If the <directory> argument is not present, program changes the working directory to
the path stored in the $HOME environment variable.

2) dir : print the current working directory

3) history : print 10 most recently entered commands in your shell

4) findloc <command> : print the location of the executable file corresponding to the given command

5) bye : terminate the shell process.


A background process is indicated by placing an ampersand (’&’) character at the end of an input line.(gedit&)

For a pipe in the command line, you need to connect stdout of the left command to stdin of
the command following the "|". For example, if the user types "ls -al | sort", then the “ls”
command is run with stdout directed to a Unix pipe, and that the sort command is run with
stdin coming from that same pipe.

Compile: gcc main.c queue.c build_in_commands.c system_commands.c -o myshell.out
