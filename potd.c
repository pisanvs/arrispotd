#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

static const int table1[] = {15, 15, 24, 20, 24, 13, 14, 27, 32, 10, 29, 14, 32, 29, 24, 23, 32,
						     24, 29, 29, 14, 29, 10, 21, 29, 34, 27, 16, 23, 30, 14, 22, 24, 17,
							 13};

static const int table2[] = {0, 1, 2, 9, 3, 4, 5, 6, 7, 8, 1, 4, 3, 9, 0, 7, 8, 2, 5, 6, 7, 2, 8,
						     9, 4, 1, 6, 0, 3, 5, 6, 3, 5, 9, 1, 8, 2, 7, 4, 0, 4, 7, 0, 9, 5, 2,
						     3, 1, 8, 6, 5, 6, 1, 9, 8, 0, 4, 3, 2, 7};

static const char anum[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
							'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
							'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(int argc, char **argv) {
	// initialize values
	(void)argc;
	*argv++;
	if (*argv == NULL) {
		printf("must provide seed (try MPSJKMDHAI)\n");
		return 1;
	}
	
	char *userSeed = *argv;
	char *startSeed = malloc(61);
	memset(startSeed, 0, 61);
	int list1[8];
	int list2[8];
	int list3[8];
	int list4[10];
	int list5[10];
	char *finseed = malloc(11);
	memset(finseed, 0, 11);
	int seedten[10];
	int seedeig[8];

	// get seed
	strncat(startSeed, userSeed, 20);
	strncat(startSeed, userSeed, 20);
	strncat(startSeed, userSeed, 20);
	snprintf(finseed, 11, "%s", startSeed);
	//strncat(finseed, startSeed, 10);

	for (int i = 0; i < 10; i++)
		seedten[i] = finseed[i];
	for (int i = 0; i < 8; i++)
		seedeig[i] = finseed[i];

	//for (int i = 0; i < 10; i++)
	//	printf("%d ", seedten[i]);
	//printf("\n");
	//for (int i = 0; i < 8; i++)
	//	printf("%d ", seedeig[i]);
	//printf("\n");

	free(startSeed);
	free(finseed);

	// --- parse datetime ---
	time_t t = time(NULL);
	struct tm time = *localtime(&t);

	int year, month, dom, dow = 0;
	// t is time elapsed since UNIX epoch, so add 1900 and get last 2 digits
	year = (time.tm_year + 1900) % 100;
	// likewise, add one month
	month = time.tm_mon + 1;
	// no need to operate on month day
	dom = time.tm_mday;
	// weekday must be zero index and start on monday
	dow = time.tm_wday - 1;
	// --- parse datetime ---
	
	// build lists

	// LIST 1	
	for (int i = 0; i < 5; i++)
		list1[i] = table1[dow * 5 + i];

	list1[5] = dom;
	if (((year + month) - dom) < 0)
		list1[6] = (((year + month) - dom) + 36) % 36;
	else
		list1[6] = ((year + month) - dom) % 36;

	list1[7] = (((3 + ((year + month) % 12)) * dom) % 37) % 36;

	// LIST 2
	for (int i = 0; i < 8; i++)
		list2[i] = seedeig[i] % 36;

	// LIST 3
	int l3sum = 0;
	for (int i = 0; i < 8; i++) {
		list3[i] = (((list1[i] + list2[i])) % 36);
		l3sum = (l3sum + list3[i]);
	} 
	list3[8] = l3sum % 36;
	int num8 = list3[8] % 6;
	list3[9] = (int)pow(num8, 2);
	
	// LIST 4
	for (int i = 0; i < 10; i++)
		list4[i] = list3[table2[num8 * 10 + i]];

	// LIST 5
	for (int i = 0; i < 10; i++)
		list5[i] = (seedten[i] + list4[i]) % 36;

	// build final POTD
	char potd[10];
	for (int i = 0; i < 10; i++)
		potd[i] = anum[list5[i]];

	printf("%s\n", potd);

}
