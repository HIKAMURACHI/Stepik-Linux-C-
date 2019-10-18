#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(int argc, char * argv[])
{
    if (argc != 3) {
        exit(1);
    }

    key_t key_one, key_two;
    key_one = atoi(argv[1]);
    key_two = atoi(argv[2]);

    int i = 0;

    int shmid_one, shmid_two, shmid_sum;
    int *shared_one;
    int *shared_two;
    int *shared_sum;

    shmid_one = shmget(key_one, 1000, 0600);
    shared_one = (int *)shmat(shmid_one, NULL, 0);

    shmid_two = shmget(key_two, 1000, 0600);
    shared_two = (int *)shmat(shmid_two,NULL,0);

    /* Create key_t */
    key_t sum_mem_key = ftok("solution.c", 0);
    shmid_sum = shmget(sum_mem_key, 1000, IPC_CREAT | 0666);
    shared_sum = (int *)shmat(shmid_sum, (void *) 0, 0);
    for(i=0; i<100; i++) {
        shared_sum[i] = shared_one[i] + shared_two[i];
    }

    printf("%d\n", sum_mem_key);

    return 0;
}
