#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Process creation (Parent and Child Process) */
void processCreation(){
	printf("\n[Process Creation] fork()\n");
	/* Prevent duplicate output after fork */
	fflush(stdout);

	pid_t pid = fork(); // Create Child

	if(pid < 0){
		perror("fork failed");
		_exit(1);
	/* Child Process Creation */
	}else if(pid == 0) {
		printf("Child process created.\n");
		printf("Child PID: %d\n",getpid());
		printf("Parent PID: %d\n",getppid());
		_exit(0);
	/* Parent Process Creation */
	}else{
		printf("Parent process created.\n");
       		printf("Parent PID : %d\n", getpid());
		printf("Child PID  : %d\n", pid);

		/* Parent waits for child demonstration */
		wait(NULL);
		printf("Parent waited for child process.\n");
	}
}

int main(){
	processCreation();
	return 0;
}
