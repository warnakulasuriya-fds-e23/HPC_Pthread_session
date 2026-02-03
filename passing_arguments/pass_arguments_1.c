/******************************************************************************
* FILE: hello_arg1.c
* DESCRIPTION:
*   A "hello world" Pthreads program which demonstrates one safe way
*   to pass arguments to threads during thread creation.
*
*   Each thread receives a unique integer ID and prints a message
*   associated with that ID.
*
* AUTHOR: Blaise Barney
* LAST REVISED: 08/04/15
******************************************************************************/

// Required header files for Pthreads, input/output, and standard utilities
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // For sleep()

// Macro defining the total number of threads to be created
// In this program, 8 threads will be created
#define NUM_THREADS 8

// Global array of string pointers
// Each index stores a message that will be printed by a specific thread
// Since it is global, all threads can safely access this array
char *messages[NUM_THREADS];

/*
 * This function is executed by each thread.
 * According to Pthreads rules:
 *   - It must accept a single void* argument
 *   - It must return a void* value
 */
void *PrintHello(void *threadid)
{
   long taskid;  // Variable to store the thread ID

   sleep(1);     // Pause to allow all threads to be created before printing

   // The argument is received as a void*
   // It is cast back to a long to retrieve the thread ID
   taskid = (long) threadid;

   // Each thread prints its ID and the message at the corresponding index
   printf("Thread %ld: %s\n", taskid, messages[taskid]);

   // Terminates the current thread cleanly
   pthread_exit(NULL);
}

/*
 * Main function where thread creation happens
 */
int main(int argc, char *argv[])
{
   // Array to store thread identifiers
   pthread_t threads[NUM_THREADS];

   // Array to store unique IDs for each thread
   long taskids[NUM_THREADS];

   int rc, t;

   // Initializing the messages array
   // Each message corresponds to one thread index
   messages[0] = "English: Hello World!";
   messages[1] = "French: Bonjour, le monde!";
   messages[2] = "Spanish: Hola al mundo";
   messages[3] = "Klingon: Nuq neH!";
   messages[4] = "German: Guten Tag, Welt!";
   messages[5] = "Russian: Zdravstvuy, mir!";
   messages[6] = "Japan: Sekai e konnichiwa!";
   messages[7] = "Latin: Orbis, te saluto!";

   // Loop runs once for each thread to be created
   for(t = 0; t < NUM_THREADS; t++) {

      // Assign a unique ID to each thread
      // Stored in the taskids array to ensure it remains valid
      taskids[t] = t;

      printf("Creating thread %d\n", t);

      /*
       * pthread_create():
       *  - &threads[t] : address of the thread identifier
       *  - NULL        : default thread attributes
       *  - PrintHello  : function to be executed by the thread
       *  - (void *)taskids[t] : thread ID passed as a void* argument
       */
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *) taskids[t]);

      // Error handling for thread creation
      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   // Terminates the main thread
   // Allows other threads to continue execution
   pthread_exit(NULL);
}
