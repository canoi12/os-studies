#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TAM 12
#define WRITE 1
#define READ 0

int main(int argc, char ** argv) {
	int N;
	pid_t pid;
	int pipe_ida[2];
	int pipe_volta[2];
	char buffer[TAM];
	if (argc > 1) {
		N = atoi(argv[1]);
	} else {
		printf("You need to put 1 or more numbers\n");
		return -1;
	}

	printf("Dad process created PID=[%d] current value is %d\n", getpid(), N);

	pipe(pipe_ida); // created go pipe
	pipe(pipe_volta); // created back pipe
	pid = fork(); // create child
	if (pid == 0) { // if is child

		close(pipe_ida[WRITE]); // close go pipe write side
		close(pipe_volta[READ]); // close back pipe read side

		printf("Child process created PID=[%d] PPID=[%d]\n", getpid(), getppid());

		read(pipe_ida[READ], buffer, TAM); // read from pipe
		N = atoi(buffer); // convert value to int
		N++; // increments

		printf("Child PID=[%d] PPID=[%d] increments value, %d\n", getpid(), getppid(), N);
		
		sprintf(buffer, "%d", N); // write back to buffer
		write(pipe_volta[WRITE], buffer, TAM); // write in the back pipe

		close(pipe_ida[READ]); // close go pipe for read
		close(pipe_volta[WRITE]); // close back pipe for write
	} else {
		close(pipe_ida[READ]); // close go pipe for read
		close(pipe_volta[WRITE]); // close back pipe for write

		N++; // increments value
		printf("Dad PID=[%d] increments value, %d\n", getpid(), N);
		sprintf(buffer, "%d", N); // write value to buffer
		write(pipe_ida[WRITE], buffer, TAM); // write buffer on pipe
		wait(NULL); // wait from child process finish
		while (read(pipe_volta[READ], buffer, TAM) > 0); // read from back pipe
		N = atoi(buffer); // convert to int

		close(pipe_ida[WRITE]); // close go pipe for write
		close(pipe_volta[READ]); // close back pipe for read

		printf("Dad process died, final value is %d\n", N);
	}

	return 0;
}
