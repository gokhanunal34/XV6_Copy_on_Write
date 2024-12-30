#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

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
  int priorities[N] = {15, 10, 45, 50, 150}; // Different priorities

  for(int i = 0; i < N; i++) {
    pid = fork();
    if(pid == 0) {
      // Child process
      setpriority(priorities[i]);
      printf(1, "Child %d with priority %d started\n", getpid(), priorities[i]);
      sleep(10); // Add sleep to visualize the scheduler's behavior
      spin(); // Simulate some work
      printf(1, "Child %d with priority %d finished\n", getpid(), priorities[i]);
      exit();
    }
  }

  for(int i = 0; i < N; i++) {
    wait(); // Wait for all children to finish
  }

  printf(1, "All children finished\n");

  exit();
}
