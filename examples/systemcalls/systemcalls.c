#include "systemcalls.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // Include this header for system(), execv(), and other standard library functions
#include <unistd.h> // Include this header for fork(), execv(), and other system calls
#include <fcntl.h> // Include this header for open()
#include <stdarg.h> // Include this header for variadic functions
#include <stdbool.h> // Include this header for the bool type
#include <sys/types.h> // Include this header for pid_t type
#include <sys/wait.h> // Include this header for waitpid()


/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
int err = 0 ;
err=system(cmd);

	if(err != 0)
	{
		return false ;
	}

    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    pid_t pid; 
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/
  pid = fork();
  if (pid < 0) {
    perror("fork");

    return false;
  }

  if (pid == 0) {
    // Child process: replace current process with the command
    if (execv(command[0], command) == -1) {
      perror("execv");
      _exit(EXIT_FAILURE);  // Use _exit to avoid potential issues with atexit handlers
    }
  } else {
    // Parent process: wait for child to finish execution
 
    if (waitpid(pid, &status, 0) == -1) {
      return false;
}
   }

    // Check child process exit status
    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
      return false;
    }
      return true;
  }

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
int status;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/
 
 
    pid_t pid = fork();
    if (pid == -1) {
        // Fork failed
        return false;
    } else if (pid == 0) {
        // Child process

        // Open the file for writing
        int fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
             return false;
        }

        // Redirect standard output to the file
        if (dup2(fd, STDOUT_FILENO) == -1) {
            close(fd);
            return false;
        }

        // Close the file descriptor as it's no longer needed after dup2
        close(fd);

 if (command[0][0] != '/') {
        return false;
    }
        // Execute the command
        execv(command[0], command);

        // If execv returns, an error occurred
       return false;
    } else {
        // Parent process
   
        waitpid(pid, &status, 0);
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
}
    va_end(args);

    return true;
}
