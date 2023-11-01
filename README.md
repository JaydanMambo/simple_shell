# Simple Shell Project
This project implements a basic UNIX command line shell. The shell can run other programs, implement pipes between programs, and redirect input/output.

## Main functionalitites:
- The main functionality implemented includes:
- Executing programs by path
- Implementing pipes between programs
- Redirecting input and output streams
- Providing exit functionality to terminate the shell
- Implementing basic command parsing and argument handling
- Providing help information for built-in commands
- Adding support for basic file manipulation commands like ls and cat
- Implementing environment variables and expansion
- Adding support for running commands in the background using &
- Adding support for command history and arrow keys navigation
- Implementing file globbing patterns like * and ? for commands like ls
- Adding support for changing directories with cd and printing working directory with pwd
- Implementing file permission checks when trying to access files

## Data Structures Used:
- Linked list to store command history
- Tokenizer to split command line input into tokens like command name, arguments etc.
- File descriptor data structure to store file handles for redirection
- Environment variables stored as key-value pairs in a hash table for fast lookup
- Directory stack implemented as a linked list to store the path of directories for implementing cd and pwd
- File path globbing implemented using glob library for pattern matching filenames
- Signal handling implemented for commands running in background
