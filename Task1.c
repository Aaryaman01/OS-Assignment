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
/* Multiple Thread Creation */
void *systemInfo(void *arg){
	struct utsname sysInfo;
	uname(&sysInfo);
	printf("[System Info Thread] OS: %s, Version: %s\n", sysInfo.sysname, sysInfo.version);
	pthread_exit(NULL);
}
void *diskIO(void *arg) {
	printf("[Disk I/O Thread] Starting disk read operation...\n");
	sleep(2);
	printf("[Disk I/O Thread] Disk read completed!\n");
	pthread_exit(NULL);
}
void *networkActivity(void *arg) {
	printf("[Network Thread] Sending data over the network...\n");
	sleep(1);
	printf("[Network Thread] Data sent successfully!\n");
	pthread_exit(NULL);
}

int main(){
	processCreation();
	pthread_t thread1, thread2, thread3;
	printf("Main Process ID: %d\n", getpid());
	pthread_create(&thread1, NULL, systemInfo, NULL);
	pthread_create(&thread2, NULL, diskIO, NULL);
	pthread_create(&thread3, NULL, networkActivity, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("All OS tasks (threads) completed. Main process exiting.\n");
	return 0;
}
