#include <string.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd, nr;
	
	if( argc == 0)
	{
		syslog(LOG_ERR, "Unsuficient arguments!");
		return 1;
	}


	fd = open(argv[1], O_RDWR| O_CREAT);



	if(fd == -1)
	{

		syslog(LOG_ERR, "file could not be open!"); //ToDo: explicitly state name of file 
		return 1;
	}

	nr =write(fd, argv[2], strlen(argv[2]));
	
	if(nr == -1)
	{

		syslog(LOG_ERR, "Could not write to file"); //ToDo: explicitly state name of file 
		return 1;

	}

	return 0;
}
	
