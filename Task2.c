
/* Memory Management Simulation */
/* C4mpus Student Portal Paging System */

#inlcude <stdio.h>
#define TOTAL_PAGES 8

/* Structure to store page information */
struct Page {
	int pageNumber;
	char pageName[30];
};

int main(){
	struct Page pages[TOTAL_PAGES] = 
	{
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

	printf("C4mpus Student Portal Paging System");
	printf("Enter page size: ");
	scanf("%d", &pageSize);
	printf("Enter logical address: ");
	scanf("%d", &logicalAddress);

        /* Calculating Page Number */
	pageNumber = logicalAddress / pageSize;

        /* Calculating Offset */
	offset = logicalAddress % pageSize;

	printf("\nLogical Address : %d\n", logicalAddress);
	printf("Page Number : %d\n", pageNumber);
	printf("Offset : %d\n", offset);

	if(pageNumber >= 0 && pageNumber < TOTAL_PAGES)
	{
		printf("Requested Page : %s\n", pages[pageNumber].pageName);
	}
	else
	{
		printf("Requested Page : Invalid Page\n");
	}
	return 0;
}
