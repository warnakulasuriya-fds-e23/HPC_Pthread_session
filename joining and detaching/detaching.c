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
    pthread_detach(t);

    printf("Main: not waiting\n");
    sleep(3); // allow thread to finish
    return 0;
}