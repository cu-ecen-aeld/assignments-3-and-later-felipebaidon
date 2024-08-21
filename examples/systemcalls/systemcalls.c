#include "systemcalls.h"
#include <string.h>
/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

    bool result  = false;

    if(system( cmd) != -1)
	    result = true;

    return result;
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
    char * command[count+1];
    int i, status;
    pid_t pid, finishedPid;
    bool ret  = false;

    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    
    fflush(stdout);
    pid = fork();

    if(pid == -1)
    {
	    perror("fork");
    }
    else if( pid > 0)
    {
	    printf("do_exec: I am the parent of pid %d\n", pid);
	    finishedPid = waitpid(pid, &status, 0);
	    printf("do_exec: child %d returned with status: %d\n", finishedPid, status);

	    if(finishedPid == -1)
	    {
		   perror("wait");
    	    }
   	    else
        	{
			if(WIFEXITED (status))
			{
				printf("do_exec: Normal termination with exit status %d\n", WEXITSTATUS(status));
				printf("do_exec: pid of terminated child is: %d\n", finishedPid);
			
				if(!WEXITSTATUS(status))
					ret = true;	
			}
		}
    }
    else
    {
	    printf("do_exec: I am the child %d\n", pid);

	    if(execv(command[0], command) == -1)
	    {
            	perror("execv");
		puts("error returning false");
	        exit(EXIT_FAILURE);	
	    }
    }

    va_end(args);
    return ret;
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
    int i, ret, status, fd;
    pid_t pid, finishedPid;
    
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

   fd = open( outputfile, O_CREAT| O_WRONLY, 0644);
   if (fd < 0) 
   {
	perror("open");
	return false;
   }

    fflush(stdout);
    pid = fork();

    if(pid == -1)
    {
	    close(fd);
	    perror("fork");
	    return false;
    }
    else if( pid > 0)
    {
	    printf("exec_redirect: I am the parent of pid %d\n", pid);
	    finishedPid = waitpid(pid, &status, 0);
	    if(finishedPid == -1)
	    {
		   perror("wait");
    	    }
   	    else
        	{
			if(WIFEXITED (status))
				printf("exec_redirect: Normal termination with exit status %d\n", WEXITSTATUS(status));

			printf("exec_redirect: pid of terminated child is: %d\n", finishedPid);
			
			if(!WEXITSTATUS(status))
				ret = true;
	    close(fd);
	
		}
    }
    else
    {

	    printf("exec_redirect: I am the child %d\n", pid);

	    if(dup2(fd,1) < 0)
	    {
		    perror("dup2");
		    exit(EXIT_FAILURE); 
	    }


	    close(fd);
	    ret = execv(command[0],command);
	    perror("execv");
            exit(EXIT_FAILURE); 
    }

    va_end(args);

    return ret;
}
