#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void call_execv();
void call_execvp();
void call_execve();
void call_execl();
void call_execlp();
void call_execle();

int main(int argc, char *argv[])
{
	int rc = fork();

	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		// call_execv();
		// call_execvp();
		// call_execve();
		// call_execl();
		// call_execlp();
		call_execle();
	} else {
		wait(NULL);
		printf("goodbye\n");
	}

	return 0;
}

void call_execv()
{
	char *myargs[2];
	myargs[0] = strdup("/bin/ls");
	myargs[1] = NULL;
	execv(myargs[0], myargs);
}

void call_execvp()
{
	char *myargs[2];
	myargs[0] = strdup("ls");
	myargs[1] = NULL;
	execvp(myargs[0], myargs);
}

void call_execve()
{
	char *myargs[2];
	myargs[0] = strdup("/bin/ls");
	myargs[1] = NULL;
	execve(myargs[0], myargs, NULL);
}

void call_execl()
{
	char *arg0 = strdup("/bin/ls");
	execl(arg0, arg0, NULL);
}

void call_execlp()
{
	char *arg0 = strdup("ls");
	execlp(arg0, arg0, NULL);
}

void call_execle()
{
	char *arg0 = strdup("/bin/ls");
	execle(arg0, arg0, NULL, NULL);
}