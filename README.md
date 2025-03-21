42 Pipex

Introduction
The *Pipex* project is part of the 42 curriculum. The goal is to recreate the functionality of shell piping (`|`) and redirection (`<`, `>`).
The program handles the execution of two commands with input and output redirection through pipes.

Objective
The objective of this project is to understand how Unix processes and pipes work by:
- Creating child processes using `fork()`.
- Redirecting input and output using `dup2()`.
- Managing inter-process communication through pipes (`pipe()`).
- Executing commands using `execve()`.
- Manipulating file descriptors and handling errors correctly.

Mandatory Part
The program should behave like:
```bash
./pipex infile "cmd1" "cmd2" outfile
```
It replicates the shell command:
```bash
< infile cmd1 | cmd2 > outfile
```

Requirements
- **Input file**: Read-only.
- **Output file**: Created or overwritten if it exists.
- **Error Handling**: Proper error messages and return codes.

Testing
You can test the program by comparing its output to the shell command's output.
```
Project Structure
- `src/`: Directory containing source files.
- `libft/`: Directory of libft project.
- `Includes/`: Directory containing header files.
- `Makefile`: Compilation rules.
