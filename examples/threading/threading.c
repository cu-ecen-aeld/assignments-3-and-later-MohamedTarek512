#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
       // Wait to obtain the mutex
    struct thread_data* thread_func_args = (struct thread_data*) thread_param;

    usleep(thread_func_args->wait_to_obtain_ms * 1000);
    
    // Attempt to obtain the mutex
    if (pthread_mutex_lock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Failed to obtain mutex\n");
        thread_func_args->thread_complete_success = false;
        pthread_exit(&thread_func_args);
    }
        // Hold the mutex for the specified time
    usleep(thread_func_args->wait_to_release_ms * 1000);
    // Release the mutex
    if (pthread_mutex_unlock(thread_func_args->mutex) != 0) {
        ERROR_LOG("Failed to release mutex\n");
        thread_func_args->thread_complete_success = false;
        pthread_exit(thread_func_args);
    }
    
    thread_func_args->thread_complete_success = true;
    pthread_exit(thread_func_args);
    
    return thread_param;

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
     
         // Allocate memory for thread_data
    struct thread_data *data = (struct thread_data*) malloc(sizeof(struct thread_data));
    if (data == NULL) {
        ERROR_LOG("Failed to allocate memory for thread_data\n");
        return false;
    }
    
    // Initialize the thread_data structure
    data->mutex = mutex;
    data->wait_to_obtain_ms = wait_to_obtain_ms;
    data->wait_to_release_ms = wait_to_release_ms;
    data->thread_complete_success = false;
    
    // Create the thread
    if (pthread_create(thread, NULL, threadfunc, data) != 0) {
        ERROR_LOG("Failed to create thread\n");
        free(data);
        return false;
    }
    
    return true;
}

