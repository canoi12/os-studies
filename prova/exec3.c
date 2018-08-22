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
	int valor = 1;
	int pipe_ida[2];
	int pipe_volta[2];
	char buffer[TAM];
	if (argc > 1) {
		N = atoi(argv[1]);
	} else {
		printf("You need 1 or more numbers\n");
		return -1;
	}
	pid_t mpid = getpid(); // get pid
	int pipes_v[N+1];

	printf("Dad process PID=[%d] created\n", mpid);
	printf("Initial value is: %d\n", valor);

	int i = 0;
	for (i = 0; i < (N-1); i++) {
		pipe(pipe_ida); // create go pipe
		pipe(pipe_volta); // create back pipe

		pipes_v[i] = pipe_volta[WRITE]; // save write pipes in array
		pid = fork(); // create child

		if (pid == 0) { // if is child
			close(pipe_ida[WRITE]); // close go pipe for write
			close(pipe_volta[READ]); // close back pipe for read

			read(pipe_ida[READ], buffer, TAM); // read from go pipe
			valor = atoi(buffer); // convert value to int
			valor += i+2; // increments (i+2) on value
			printf("Child process PID=[%d] PPID=[%d] created\n", getpid(), getppid());
			printf("Current value is %d\n", valor);
			sprintf(buffer, "%d", valor); // write current value on buffer
			//write(pipe_volta[WRITE], buffer, TAM);
		} else { // if is dad
			close(pipe_ida[READ]); // close go pipe for read
			close(pipe_volta[WRITE]); // close back pipe for write
			sprintf(buffer, "%d", valor);
			write(pipe_ida[WRITE], buffer, TAM); // write value on go pipe
			wait(NULL);
			break;
		}
	}

	if (pid == 0) { // if is child
		write(pipes_v[0], buffer, TAM); // write value on first back pipe
		exit(0);
	}

	if (getpid() == mpid) { // if is main process
		read(pipe_volta[READ], buffer, TAM); // read from back pipe
		valor = atoi(buffer); // convert to int
		printf("Dad is gonna die\n");
		printf("Final value is %d\n", valor);
		printf("Dad died\n");
	} 
	return 0;
}
