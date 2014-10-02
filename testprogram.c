/*Matthew Fritze
1360555
CMPUT 379
Assignment 1 */

#include "memchunk.h"

#define SIZE 13
#define INACCESSIBLE -1
#define READABLE 0
#define WRITABLE 1

void displayMemoryChunks(struct memchunk *, int);
void testChunks(struct memchunk *);
int testRead(unsigned long, int *, int);
int testWrite(unsigned long, int *, int);
int testInaccessible(unsigned long length, int * start);


int main(int argc, char ** argv){
	/* Tests the functionality of 
	the get_mem_layout function */
	struct memchunk memStatusList[SIZE];
	int foundSize;

	foundSize = get_mem_layout(memStatusList, SIZE);
	displayMemoryChunks(memStatusList, foundSize);
	testChunks(memStatusList);
	return 0;
}

void testChunks(struct memchunk * cList){
	/* Tests each chunk to see if 
	its Read-Write Status matches 
	the access rights */
	int i, RW, status, pSize = getpagesize();
	for(i=0; i < SIZE; i++){
		RW = cList[i].RW;
		if(RW == READABLE){
			status = testRead(cList[i].length,
				cList[i].start, pSize);
			if(status == READABLE){
				printf("Block %d READABLE Pass\n", i);
			}else{
				printf("Block %d READABLE Fail\n", i);
			}
		}else if(RW == WRITABLE){
			status = testWrite(cList[i].length,
				cList[i].start, pSize);
			if(status == WRITABLE){
				printf("Block %d WRITABLE Pass\n", i);
			}else{
				printf("Block %d WRITABLE Fail\n", i);
			}
		}else{
			printf("Block %d INACCESSIBLE\n", i);				
		}
	}
}

int testRead(unsigned long length, int * start, int pSize){
	/* Tests each page in the chunk 
	to see if it can be read */
	int memTest, i;
	for(i = 0; i < length/pSize ; i++){
		memTest = * (start + ((i*pSize)/ sizeof(int)));
	}
	memTest++;
	return READABLE;

}

int testWrite(unsigned long length, int * start, int pSize){
	/* Tests each page in the chunk 
        to see if it can be written to */
	int *memTest, i;
	for(i = 0; i < length/pSize ; i++){
		memTest = (start + ((i*pSize)/ sizeof(int)));
		*memTest = * memTest;
	}
        return WRITABLE;

	return INACCESSIBLE;
}


void displayMemoryChunks(struct memchunk * memList, int foundSize){
	/* See the status of 
	each of the blocks found in 
	memory, by the get_mem_layout */
	int i;
	printf("foundize: %d\n", foundSize);

	for(i = 0; i < SIZE; i++){
	printf("index: %d \tMemory at: %p \t RW Status: %d \t Length: %lu\n"
		,i,(int*) memList[i].start, memList[i].RW, memList[i].length);
	}
}
