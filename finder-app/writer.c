#include <string.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd, nr;
	
	if( argv[1] == NULL || argv[2] == NULL)
	{
		syslog(LOG_ERR, "Unsuficient arguments!");
		puts("Unsuficient arguments!");
		exit(EXIT_FAILURE);
	}


	fd = open(argv[1], O_CREAT|O_RDWR, 0644);



	if(fd == -1)
	{

		syslog(LOG_ERR, "file could not be open!"); //ToDo: explicitly state name of file 
	
		exit(EXIT_FAILURE);
	}

	nr =write(fd, argv[2], strlen(argv[2]));
	
	if(nr == -1)
	{

		syslog(LOG_ERR, "Could not write to file"); //ToDo: explicitly state name of file 

		exit(EXIT_FAILURE);

	}

	if( close(fd) == -1)
	{
		
		syslog(LOG_ERR, "Error to close file!"); //ToDo: explicitly state name of file
	        exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
	
