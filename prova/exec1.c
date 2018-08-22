#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char ** argv) {
	int N;
	pid_t pid;
	if (argc > 1) {
		N = atoi(argv[1]); // read from default entry
	} else {
		printf("You need to put 1 or more numbers\n");
		return -1;
	}
	pid_t mpid = getpid(); // get father PID
	printf("Dad process created PID=[%d]\n", getpid());

	for (int i = 0; i < N-1; i++) {
		pid = fork(); // create child
		if (pid == 0) { // if is child
			printf("Child process created PID=[%d] PPID=[%d]\n", getpid(), getppid());
		} else { // if is dad
			wait(NULL);
			break;
		}
	}

	if (getpid() == mpid) {
		printf("Process dad will gonna die\n");
	}
	return 0;
}
