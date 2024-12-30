#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define N 5

void
spin()
{
  int i;
  for(i = 0; i < 1000000; i++) {
    asm("nop"); // CPU busy work
  }
}

int
main(void)
{
  int pid;
  int priorities[N] = {20, 10, 30, 5, 15}; // Different priorities

  for(int i = 0; i < N; i++) {
    pid = fork();
    if(pid == 0) {
      // Child process
      setpriority(priorities[i]);
      printf(1, "Child %d with priority %d\n", getpid(), priorities[i]);
      spin(); // Simulate some work
      printf(1, "Child %d finished\n", getpid());
      exit();
    }
  }

  for(int i = 0; i < N; i++) {
    wait(); // Wait for all children to finish
  }

  printf(1, "All children finished\n");

  exit();
}
