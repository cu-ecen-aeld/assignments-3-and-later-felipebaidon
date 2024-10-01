#define _GNU_SOURCE
#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
     
   
    //puts("Waiting to obtain");   
    usleep(thread_func_args -> wait_to_obtain_us);
    //puts("mutex locked");   
   int retval = pthread_mutex_lock(thread_func_args -> the_mutex);
     if(retval)
     {
	     errno = retval;
	     perror("pthread_mutex_lock");
	     pthread_exit(thread_func_args); 
     }
    
   usleep(thread_func_args -> wait_to_release_us);
    //puts("mutex unlocked");   
    retval = pthread_mutex_unlock(thread_func_args -> the_mutex);
    if(retval)
     {
	     errno = retval;
	     perror("pthread_mutex_unlock");
	     pthread_exit(thread_func_args); 
     }

    thread_func_args -> thread_complete_success = true;
	
    return thread_func_args;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

     int retval = 0;

     //puts("PERFORMING MEMORY ALLOCATION");   
     struct thread_data* thread_func_args = (struct thread_data*) malloc(sizeof(struct thread_data));
     if(thread_func_args == NULL)
     {
	     puts("Error allocating memory!");
	     exit(1);

     }
      

     //puts("MEMORY ALLOCATION SUCCESFULL");   
     thread_func_args -> wait_to_release_us = (unsigned int)(wait_to_release_ms * 1000);
     thread_func_args -> wait_to_obtain_us = (unsigned int)(wait_to_obtain_ms * 1000);
     thread_func_args -> the_mutex = mutex;
     thread_func_args -> thread_complete_success = false;

     //puts("STARTING THREAD");   

     retval = pthread_create(thread, NULL , threadfunc, (void*)thread_func_args);

     if(retval)
     {
	     errno = retval;
	     perror("pthread_create");
	     return false;
     }
     else
     {
	     return true;
     }

}

/*int main(void)
{
    pthread_t threadID;
    pthread_mutex_t mutex  = PTHREAD_MUTEX_INITIALIZER;
    int timeToObtain = 20;
    int timeToRelease = 20;

    bool retval =  start_thread_obtaining_mutex(&threadID, &mutex, timeToObtain, timeToRelease);
    
    printf("Start thread function returned with %d\n", retval);

    return 0;

}*/
