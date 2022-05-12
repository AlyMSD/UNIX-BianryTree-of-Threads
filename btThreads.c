#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

#include "common.h"
#include "common_threads.h"

void *tree(void *arg);
int gettid();

int main(int argc, char *argv[]) {                    

    int ht;

    if (argc != 2) {
        fprintf(stderr, "usage: main #threads \n");
        exit(1);
    }

    ht = atoi(argv[1]);

    pthread_t p1;
    Pthread_create(&p1, NULL, tree, &ht);
    Pthread_join(p1, NULL);
    return 0;
}

// It is easier to write a recursive function than an iterative one.
// Remember arg is an address in the stack of the caller.
// I wouldnt modify the value at that location.
void* tree(void* arg) {
// create temp var to mod height var
    int* temp = (int*)arg;
    int height = *temp;
    // create thread vars to create left and right child nodes
    pthread_t lc, rc;
    // if at end of tree = leaf
    if (height == 0)
    {
        printf("Leaf Thread (id: %d", gettid());
        printf(") at height %d\n", height);
        return NULL;
    }
    // if not end create left and right child threads/nodes
    else{
      printf("Int. Thread (id: %d) at height %d\n", gettid(), height);
      height--;
      Pthread_create(&lc, NULL, tree, &height);
      Pthread_create(&rc, NULL, tree, &height);
    }
    //wait for finish
    Pthread_join(lc, NULL);
    Pthread_join(rc, NULL);
    
    
}

int
gettid(){
    return (syscall(SYS_gettid));
}