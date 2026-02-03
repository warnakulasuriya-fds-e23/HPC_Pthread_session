#include <pthread.h>
#include <stdio.h>

void* thread_func(void* arg) {
    /* large local array → uses stack */
    int arr[100000];   // ~400 KB on stack
    printf("Thread running safely\n");
    return NULL;
}

int main() {
    pthread_t t;
    pthread_attr_t attr;
    size_t stacksize;

    /* initialize thread attributes */
    pthread_attr_init(&attr);

    /* set stack size explicitly */
    stacksize = 1024 * 1024;   // 1 MB
    pthread_attr_setstacksize(&attr, stacksize);

    /* create thread with custom stack size */
    pthread_create(&t, &attr, thread_func, NULL);

    pthread_join(t, NULL);
    return 0;
}
