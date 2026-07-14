
/* C4mpus Student Portal Paging System */

#include <stdio.h>

#define TOTAL_PAGES 8
#define MAX_REQUESTS 50
#define MAX_FRAMES 10

/* Structure to store page information */
struct Page {
	int pageNumber;
	char pageName[30];
};

/* FIFO Page Replacement */
void fifo_simulation(int request[], int totalRequests, int frameCount)
{
	int frames[MAX_FRAMES]; /* Stores current page in physical memory */
	int i;
	int j;
	int found;
	int nextReplace = 0; /* Tells which frame should be replaced next */

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
            		if(frames[j] == request[i])
            		{
                		found = 1;
                		break;
            		}
       		}

        	printf("\nRequest %d : Page %d\n", i + 1, request[i]);

        	/* If page is already in memory */
        	if(found == 1)
        	{
            		printf("Result : Page Hit\n");
        	}
        	/* If page is not in memory */
        	else
        	{
            		printf("Result : Page Fault\n");

            		/* Replaces the oldest page */
            		frames[nextReplace] = request[i];

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
                		printf("[Page %d]\n", frames[j]);
            		}
		}
	}
}

int main()
{
    	struct Page pages[TOTAL_PAGES] = {
        	{0, "Dashboard"},
        	{1, "Routine"},
        	{2, "My Assignments"},
        	{3, "Attendance"},
        	{4, "Results"},
        	{5, "Books"},
        	{6, "Profile"},
        	{7, "Fees"},
    	};

    	int pageSize;
    	int logicalAddress;
    	int pageNumber;
    	int offset;
    	int frameCount;
    	int totalRequests;
    	int requests[MAX_REQUESTS];
    	int i;

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
        	printf("Requested Page : %s\n", pages[pageNumber].pageName);
    	}
    	else
    	{
        	printf("Requested Page : Invalid Page\n");
    	}

    	/* Displays number of frames */
    	printf("\nEnter number of frames: ");
    	scanf("%d", &frameCount);

    	/* Displays Total page requests */
    	printf("Enter total page requests: ");
    	scanf("%d", &totalRequests);

    	/* Displays page request sequence */
    	printf("\nEnter page request sequence\n");

    	for(i = 0; i < totalRequests; i++)
    	{
        	printf("Request %d : ", i + 1);
        	scanf("%d", &requests[i]);
    	}

    	/* Start FIFO simulation */
    	fifo_simulation(requests, totalRequests, frameCount);

    	return 0;
}
