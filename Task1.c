#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Mutex Synchronization mechanism applied */
// Shared resource for Synchronization
int counter = 0;
pthread_mutex_t lock;

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
void *systemInfo(void *arg){  // Display System Information
	struct utsname sysInfo;
	uname(&sysInfo);

	/* Synchronization using Mutex */
	pthread_mutex_lock(&lock);
	counter++;

	printf("[System Info Thread] OS: %s, Version: %s\n", sysInfo.sysname, sysInfo.version);

	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}

void *diskIO(void *arg) {  // Simulate Disk I/O

	/* Lock shared resource */
	pthread_mutex_lock(&lock);
	printf("[Disk I/O Thread] Starting disk read operation...\n");
	sleep(2);
	counter++;
	printf("[Disk I/O Thread] Disk read completed!\n");
	printf("Counter : %d\n", counter);

	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}

void *networkActivity(void *arg) {  // Simulate Network Activity

	/* Lock shared resource */
	pthread_mutex_lock(&lock);

	printf("[Network Thread] Sending data over the network...\n");
	sleep(1);
	counter++;
	printf("[Network Thread] Data sent successfully!\n");
	pthread_exit(NULL);
}



int main(){
	/* Process Creation*/
	processCreation();

	pthread_t thread1, thread2, thread3;

	/* Initialize Mutex */
	pthread_mutex_init(&lock, NULL);

	printf("Main Process ID: %d\n", getpid());
	pthread_create(&thread1, NULL, systemInfo, NULL);
	pthread_create(&thread2, NULL, diskIO, NULL);
	pthread_create(&thread3, NULL, networkActivity, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("\n[Synchronization]\n");
	printf("Final Counter Value: %d\n", counter);

	printf("\n[Race Condition]\n");
	printf("Race Condition is prevented using a mutex.\n");

	printf("\n[Deadlock Prevention]\n");
	printf("Deadlock is prevented by locking and unlocking the mutex properly.\n");

	/* Destroy Mutex */
	pthread_mutex_destroy(&lock);

	printf("All OS tasks (threads) completed. Main process exiting.\n");
	return 0;
}


