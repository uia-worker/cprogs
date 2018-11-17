#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// GLOBAL SCOPE
int g = 0;

// FUNCTION CAN BE CALLED BY ALL THREADS
void *myThread(void *vargp) {
  // LOCAL SCOPE, scope of myThread and A LOCAL VARIABLE
  //int *myid = (int *) (size_t) vargp;
  // LOCAL SCOPE, scope of myThread and A LOCAL STATIC VARIABLE
  static int s = 0;
  // Change the static and the global variables
  ++s; ++g;
  // Print the argument (local variable), static (local) and global variable
  printf("vargp: %d, Static: %d, Global: %d\n", (int) vargp, ++s, ++g);
  return NULL;
}

int main() {
  pthread_attr_t attr;
  pthread_t posixThreadID;
  int i;
  int returnVal;
  int threadError;
  returnVal = pthread_attr_init(&attr);
  //assert(!returnVal);
  returnVal = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  //assert(!returnVal);

  // Create 3 THREADS
  for (i=0;i<3;i++) {
    //pthread_create(&tid, NULL, myThread, (void *) (size_t) i);
    threadError = pthread_create(&posixThreadID, &attr, &myThread, (void *) (size_t) i);
    //usleep(100*1000);
  }
  returnVal = pthread_attr_destroy(&attr);

  if (threadError != 0) {
    printf("threadError");
  }

  //pthread_exit(NULL);
  return 0;
}
