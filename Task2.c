
/* C4mpus Student Portal Paging System */

#include <stdio.h>

#define TOTAL_PAGES 8
#define MAX_REQUESTS 50
#define MAX_FRAMES 10

/* Stores all C4mpus portal page */
char pages[TOTAL_PAGES][30] =
{
	"Dashboard",
        "Routine",
       	"My Assignments",
        "Attendance",
        "Results",
        "Books",
        "Profile",
        "Fees",
};

/* FIFO Page Replacement */
void fifo_simulation(int requests[], int totalRequests, int frameCount)
{
	int frames[MAX_FRAMES]; /* Physical memory frames */
	int i;
	int j;
	int found;
	int nextReplace = 0; /* Tells which frame should be replaced next */

	/* Statistics */
	int hits = 0;
	int pageFaults = 0;
	float hitRatio;
	float missRatio;

	/* Makes all frames empty */
	for(i = 0; i < frameCount; i++)
	{
		frames[i] = -1;
	}
	printf("\nFIFO Simulation\n");

	/* Checks every page request */
    	for(i = 0; i < totalRequests; i++)
    	{
        	found = 0;

        	/* Checks if page is already in memory */
        	for(j = 0; j < frameCount; j++)
        	{
            		if(frames[j] == requests[i])
            		{
                		found = 1;
                		break;
            		}
       		}

        	printf("\nRequest %d : %s\n", i + 1, pages[requests[i]]);

        	/* If page is already in memory */
        	if(found == 1)
        	{
			hits++;  /* Increases hit count */
            		printf("Result : Page Hit\n");
        	}
        	/* If page is not in memory */
        	else
        	{
			pageFaults++;  /* Increases page fault count */
            		printf("Result : Page Fault\n");

            		/* Replaces the oldest page */
            		frames[nextReplace] = requests[i];

           		 /* Moves to next frame */
            		nextReplace++;

            		/* Goes back to first frame after last frame */
            		if(nextReplace == frameCount)
            		{
                		nextReplace = 0;
            		}
        	}

        	/* Displays current memory frames */
        	printf("Memory Frames\n");

        	for(j = 0; j < frameCount; j++)
        	{
            		if(frames[j] == -1)
            		{
                		printf("[Empty]\n");
            		}
            		else
            		{
                		printf("[%s]\n",pages[frames[j]]);
            		}
		}
	}
	/* Calculates hit and miss ratios */
	hitRatio = (float)hits / totalRequests;
	missRatio = (float)pageFaults / totalRequests;

	/* Displays FIFO statistics */
	printf("\nFIFO Statistics\n");
	printf("Total Requests : %d\n", totalRequests);
	printf("Hits : %d\n", hits);
	printf("Page Faults : %d\n", pageFaults);
	printf("Hit Ratio : %.2f\n", hitRatio);
	printf("Miss Ratio : %.2f\n", missRatio);
}

/* LRU Page Replacement */
void lru_simulation(int requests[], int totalRequests, int frameCount)
{
	int frames[MAX_FRAMES];
	int recent[MAX_FRAMES];
	int i;
	int j;
	int found;
	int emptyFrame;
	int leastRecent;

	/* Statistics */
	int hits = 0;
	int pageFaults = 0;
	float hitRatio;
	float missRatio;

	/* Makes all frames empty */
	for(i = 0; i < frameCount; i++)
	{
		frames[i] = -1;
		recent[i] = -1;
	}
	printf("\nLRU Simulation\n");

	/* Checks every page request */
	for(i = 0; i < totalRequests; i++)
	{
		found = 0;
		/* Checks if page is already in memory */
		for(j = 0; j < frameCount; j++)
		{
			if(frames[j] == requests[i])
			{
				found = 1;
				/* Updates last used time */
				recent[j] = i;
				break;
			}
		}
		printf("\nRequest %d : %s\n", i + 1, pages[requests[i]]);
		if(found == 1)
		{
			hits++; /* Increases hit count */
			printf("Result : Page Hit\n");
		}
		else
		{
			pageFaults++; /* Increases page fault count */
			printf("Result : Page Fault\n");
			emptyFrame = -1;

			/* Checks for empty frame */
			for(j = 0; j < frameCount; j++)
			{
				if(frames[j] == -1)
				{
					emptyFrame = j;
					break;
				}
			}

			/* If empty frame exists */
			if(emptyFrame != -1)
			{
				frames[emptyFrame] = requests[i];
				recent[emptyFrame] = i;
			}
			else
			{
				/* Finds least recently used page */
				leastRecent = 0;
				for(j = 1; j < frameCount; j++)
				{
					if(recent[j] < recent[leastRecent])
					{
						leastRecent = j;
					}
				}

				/* Replaces least recently used page */
				frames[leastRecent] = requests[i];
				recent[leastRecent] = i;
			}
		}
		/* Displays memory frames */
		printf("Memory Frames\n");
		for(j = 0; j < frameCount; j++)
		{
			if(frames[j] == -1)
			{
 				printf("[Empty]\n");
			}
			else
			{
				printf("[%s]\n", pages[frames[j]]);
			}
		}
	}
	/* Calculates hit and miss ratios */
	hitRatio = (float)hits / totalRequests;
	missRatio = (float)pageFaults / totalRequests;

	/* Displays LRU statistics */
	printf("\nLRU Statistics\n");
	printf("Total Requests : %d\n", totalRequests);
	printf("Hits : %d\n", hits);
	printf("Page Faults : %d\n", pageFaults);
	printf("Hit Ratio : %.2f\n", hitRatio);
	printf("Miss Ratio : %.2f\n", missRatio);
}

int main()
{

    	int pageSize;
    	int logicalAddress;
    	int pageNumber;
    	int offset;
    	int frameCount;
    	int totalRequests;
    	int requests[MAX_REQUESTS];
    	int i;
	int choice;

    	printf("C4mpus Student Portal Paging System\n");

    	printf("Enter page size: ");
    	scanf("%d", &pageSize);

    	printf("Enter logical address: ");
    	scanf("%d", &logicalAddress);

    	/* Calculating Page Number */
    	pageNumber = logicalAddress / pageSize;

    	/* Calculating Offset */
    	offset = logicalAddress % pageSize;

    	/* Displays page details */
    	printf("\nLogical Address : %d\n", logicalAddress);
    	printf("Page Number : %d\n", pageNumber);
    	printf("Offset : %d\n", offset);

    	/* Checks if page exists */
    	if(pageNumber >= 0 && pageNumber < TOTAL_PAGES)
    	{
        	printf("Requested Page : %s\n", pages[pageNumber]);
    	}
    	else
    	{
        	printf("Requested Page : Invalid Page\n");
    	}

    	/* Displays number of frames */
    	printf("\nEnter number of frames: ");
    	scanf("%d", &frameCount);

	/* Checks if frame count is valid */
	if(frameCount <= 0 || frameCount > MAX_FRAMES)
	{
		printf("Invalid frame count.\n");
		return 0;
	}

    	/* Displays Total page requests */
    	printf("Enter total page requests: ");
    	scanf("%d", &totalRequests);

	/* Checks if total requests are valid */
	if(totalRequests <= 0 || totalRequests > MAX_REQUESTS)
	{
    		printf("Invalid number of requests.\n");
    		return 0;
	}

    	/* Displays page request sequence */
    	printf("\nEnter page request sequence\n");

    	for(i = 0; i < totalRequests; i++)
    	{
        	printf("Request %d : ", i + 1);
        	scanf("%d", &requests[i]);

		/*Checks if page number is valid*/
		if(requests[i] < 0 || requests[i] >= TOTAL_PAGES)
		{
			printf("Invalid page number.\n");
			return 0;
		}
	}

    	/* Choose Algorithm */
	printf("\n");
	printf("1. FIFO\n");
	printf("2. LRU\n");
	printf("3. Both\n");
	printf("\nChoose Algorithm : ");
	scanf("%d", &choice);

	/* Run selected Algorithm */
	if(choice == 1)
	{
    		fifo_simulation(requests, totalRequests, frameCount);
	}
	else if(choice == 2)
	{
		lru_simulation(requests, totalRequests, frameCount);
	}
	else if(choice == 3)
	{
		fifo_simulation(requests, totalRequests, frameCount);
		printf("\n");
		lru_simulation(requests, totalRequests, frameCount);
	}
	else
	{
		printf("Invalid Choice\n");
	}
    	return 0;
}
