
/* Task1: Process Management and Threading */
/* Scenario: Online Food Delivery System */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Mutex Synchronization mechanism applied */
// Shared resource for Synchronization
int completedTasks = 0;
pthread_mutex_t lock;

/* Process creation (Food Delivery System) */
void processCreation(){
	printf("\n[Food Delivery System]\n");
	printf("Creating customer order...\n");

	/* Prevent duplicate output after fork */
	fflush(stdout);

	pid_t pid = fork(); // Create Child

	if(pid < 0){
		perror("fork failed");
		_exit(1);
	/* Child Process Creation */
	}else if(pid == 0) {
		printf("Child process (Customer Order) created.\n");
		printf("Order Process PID: %d\n",getpid());
		printf("Food Delivery System PID: %d\n",getppid());
		_exit(0);
	/* Parent Process Creation */
	}else{
		printf("Parent process (Food Delivery System) started.\n");
       		printf("System PID : %d\n", getpid());
		printf("Order Process PID  : %d\n", pid);

		/* Parent waits for child demonstration */
		wait(NULL);
		printf("Parent process waited for the customer order process to finish.\n");
	}
}

/* Multiple Thread Creation */
void *restaurant(void *arg){

	/* Synchronization using Mutex */
	pthread_mutex_lock(&lock);

	printf("\n[Restaurant Thread]\n");
	printf("Preparing customer order...\n");

	sleep(2);
	completedTasks++;

	printf("Order prepared successfully.\n");
    	printf("Completed Tasks : %d\n", completedTasks);

	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}

void *delivery(void *arg) {

	/* Lock shared resource */
	pthread_mutex_lock(&lock);

	printf("\n[Delivery Thread]\n");
	printf("Delivering customer order...\n");

	sleep(2);
	completedTasks++;
	printf("Order delivered successfully.\n");
	printf("Completed Tasks : %d\n", completedTasks);

	/* Unlock shared resource */
	pthread_mutex_unlock(&lock);

	pthread_exit(NULL);
}

void *payment(void *arg) {

	/* Lock shared resource */
	pthread_mutex_lock(&lock);

	printf("\n[Payment Thread]\n");
	printf("Processing customer payment...\n");

	sleep(1);
	completedTasks++;

	printf("Payment completed successfully.\n");
	printf("Completed Tasks : %d\n", completedTasks);

	/* Unlock shared resource */
	pthread_mutex_unlock(&lock);
	pthread_exit(NULL);
}

/* Round Robin Scheduling Simulation */
void roundRobin(){

	int burst[] = {5,8,3};
	int remaining[] = {5,8,3};
	int quantum = 2;
	int i;
	int done;

	char tasks[3][30]=
	{
		"Restaurant",
        	"Delivery",
        	"Payment"
	};


	printf("\n[Round Robin Scheduling]\n");

	while(1){
		done = 1;
		for(i = 0; i < 3; i++){
			if(remaining[i] > 0){
				done = 0;
				if(remaining[i] > quantum){
					printf("%s executes for %d units\n", tasks[i], quantum);
					remaining[i] -= quantum;
				}else{
					printf("%s completed.\n", tasks[i]);
					remaining[i] = 0;
				}
			}
		}

		if(done)
			break;
	}
}

/* Main Function */
int main(){
	/* Process Creation*/
	processCreation();

	pthread_t thread1, thread2, thread3;

	/* Initialize Mutex */
	pthread_mutex_init(&lock, NULL);

	printf("\nMain Process ID: %d\n", getpid());

	/* Create Threads */
	pthread_create(&thread1, NULL, restaurant, NULL);
	pthread_create(&thread2, NULL, delivery, NULL);
	pthread_create(&thread3, NULL, payment, NULL);

	/* Wait for Threads */
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	/* Synchronization */
	printf("\n[Synchronization]\n");
	printf("All food delivery tasks completed successfully.\n");
	printf("Final Completed Tasks : %d\n", completedTasks);

	/* Round Robin Scheduling */
	roundRobin();

	/* Race Condition */
	printf("\n[Race Condition]\n");
	printf("Restaurant, Delivery and Payment threads share the same order information.\n");
	printf("Race Condition is prevented using a mutex.\n");

	/* Deadlock Prevention */
	printf("\n[Deadlock Prevention]\n");
	printf("Deadlock is prevented by locking and unlocking the mutex properly.\n");

	/* Destroy Mutex */
	pthread_mutex_destroy(&lock);

	printf("\nAll food delivery operations completed.\n");
	printf("Food Delivery System closed successfully.\n");

	return 0;
}

