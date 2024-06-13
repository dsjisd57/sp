#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Create child process for printing "George"
  int georgePid = fork();

  if (georgePid == 0) {
    // Child process (George)
    while (1) {
      printf("George\n");
      sleep(1);
    }
  } else if (georgePid > 0) {
    // Parent process
    // Create child process for printing "Mary"
    int maryPid = fork();

    if (maryPid == 0) {
      // Child process (Mary)
      while (1) {
        printf("Mary\n");
        sleep(2);
      }
    } else if (maryPid > 0) {
      // Parent process
      // Main loop for printing separators
      while (1) {
        printf("----------------\n");
        sleep(1);
      }
    } else {
      // Error handling for fork()
      perror("fork failed");
      exit(1);
    }
  } else {
    // Error handling for fork()
    perror("fork failed");
    exit(1);
  }

  return 0;
}
