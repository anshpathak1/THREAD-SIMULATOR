#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mtx;

void* simulate_work(void* arg)
{
    int id = *(int*)arg;

    pthread_mutex_lock(&mtx);
    printf("[Thread %d] RUNNING in One-to-Many model\n", id);
    pthread_mutex_unlock(&mtx);

    sleep(1);

    pthread_mutex_lock(&mtx);
    printf("[Thread %d] FINISHED\n", id);
    pthread_mutex_unlock(&mtx);

    return NULL;
}

void many_to_one()
{
    printf("\n--- MANY TO MANY MODEL ---\n");
    printf("Many user threads mapped to LIMITED kernel threads\n\n");

    pthread_t threads[3];
    int thread_ids[3];

    for (int i = 0; i < 3; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, simulate_work, &thread_ids[i]>);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main()
{
    int choice;

    pthread_mutex_init(&mtx, NULL);

    printf("REAL-TIME MULTI-THREADED APPLICATION SIMULATOR\n");
    printf("1. Many-to-One Model\n");
    printf("2. One-to-Many Model\n");
    printf("3. Many-to-Many Model\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            many_to_one();
            break;
        case 2:
            one_to_many();
            break;
         case 3:
            many_to_many();
            break;
        default:
            printf("Invalid choice\n");
    }

    pthread_mutex_destroy(&mtx);
    return 0;
}
