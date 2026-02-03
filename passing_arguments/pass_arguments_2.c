/* 
   This array stores a separate message for each thread.
   Each thread will receive its own message through the structure,
   instead of accessing this array directly.
*/
char *messages[NUM_THREADS];

/* 
   This structure is used to bundle multiple arguments together.
   Instead of passing only one value to a thread, we group all
   required data into a single structure.

   The structure contains:
   - a thread ID
   - a computed sum value
   - a pointer to a message string
*/
struct thread_data
{
   int thread_id;    // Unique ID for each thread
   int sum;          // Sum value calculated in main()
   char *message;    // Message specific to the thread
};

/* 
   This array creates a separate structure instance for each thread.
   Each thread will receive the address of its own structure element.
   Because each thread uses a different array index, there is no
   data sharing or race condition.
*/
struct thread_data thread_data_array[NUM_THREADS];

/* 
   Thread function.
   As required by Pthreads, the function accepts a single void* argument.
*/
void *PrintHello(void *threadarg)
{
   int taskid, sum;
   char *hello_msg;

   /* 
      Pointer used to access the structure passed from main().
   */
   struct thread_data *my_data;

   sleep(1);

   /* 
      The argument received by the thread is a generic void*.
      It is cast back to a pointer to struct thread_data so that
      the thread can access all the fields inside the structure.
   */
   my_data = (struct thread_data *) threadarg;

   /* 
      Each thread retrieves its own data from the structure.
      This demonstrates how multiple arguments are accessed
      inside the thread.
   */
   taskid    = my_data->thread_id;
   sum       = my_data->sum;
   hello_msg = my_data->message;

   printf("Thread %d: %s  Sum=%d\n", taskid, hello_msg, sum);

   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc, t, sum;

   sum = 0;

   /* Initialize messages for each thread */
   messages[0] = "English: Hello World!";
   messages[1] = "French: Bonjour, le monde!";
   messages[2] = "Spanish: Hola al mundo";
   messages[3] = "Klingon: Nuq neH!";
   messages[4] = "German: Guten Tag, Welt!";
   messages[5] = "Russian: Zdravstvuy, mir!";
   messages[6] = "Japan: Sekai e konnichiwa!";
   messages[7] = "Latin: Orbis, te saluto!";

   /* 
      Create threads.
      Before creating each thread, the main function fills one
      structure instance with thread-specific data.
   */
   for(t = 0; t < NUM_THREADS; t++) {

      sum = sum + t;

      /* Fill the structure for this specific thread */
      thread_data_array[t].thread_id = t;
      thread_data_array[t].sum       = sum;
      thread_data_array[t].message   = messages[t];

      printf("Creating thread %d\n", t);

      /* 
         Instead of passing a single variable, we pass the address
         of the structure. This allows the thread to receive multiple
         arguments through one pointer.

         Since each thread receives a different structure address,
         this approach is thread-safe.
      */
      rc = pthread_create(&threads[t], NULL,
                          PrintHello,
                          (void *) &thread_data_array[t]);

      if (rc) {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   pthread_exit(NULL);
}
