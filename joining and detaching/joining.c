#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *task(void *arg)
{
    printf("Thread: working...\n");
    sleep(2);
    printf("Thread: done\n");
    return NULL;
}

int main()
{
    pthread_t t;

    pthread_create(&t, NULL, task, NULL);

    printf("Main: waiting for thread\n");
    pthread_join(t, NULL);

    printf("Main: thread finished\n");
    return 0;
}