/*Matthew Fritze
1360555
CMPUT 379
Assignment 1 */

#include "memchunk.h"
#define INACCESSIBLE -1
#define READABLE 0
#define WRITABLE 1

void signal_intr(int);
int readableTest(int *);
int writeableTest(int *); 
void insertNewChunk(int *, unsigned long, int, int, struct memchunk *); 

static sigjmp_buf env;

int get_mem_layout (struct memchunk *chunk_list, int size){
	int pageCount, pageSize = getpagesize(), lastRW = -1, curRW = 0, 
	memChunkIndex = 0, i, * memory = 0x0, * start = 0x0;
	unsigned long length;
	pageCount = 0xffffffff/pageSize; 

	signal(SIGSEGV, signal_intr);

	for(i = 0; i< pageCount; i++){
		if(!(curRW = readableTest(memory))){
			curRW = writeableTest(memory);
		}
		if(curRW != lastRW){
			if(memChunkIndex < size){
				length = (memory - start)*sizeof(int);
				insertNewChunk(start, length, lastRW, 
				 	memChunkIndex,chunk_list);
				start = memory;
			}
			lastRW = curRW;
			memChunkIndex++;
		} 
		memory += pageSize/sizeof(int);
	}
	return memChunkIndex;
}

void signal_intr(int signo){ 
	/* Restore the session to the statement
	before the memory access error */
	siglongjmp(env, 1);
}

int readableTest(int * memory){
	if(!sigsetjmp(env, 1)){ 
		/* Try to read from memory */
		int memTest = * memory;
		memTest++;
		return READABLE; 
	}
	return INACCESSIBLE; 
}

int writeableTest(int * memory){
	if(!sigsetjmp(env, 1)){
		/* Try to write to memory */
		* memory = * memory;
		return WRITABLE;
	}
	return READABLE;  
}

void insertNewChunk(int * memory, unsigned long length ,int RW,
int memChunkIndex, struct memchunk * chunk_list ){ 
	/*creates a new chunk and adds it to the chunklist.
	Also sets the size of the previous chunk */
	chunk_list[memChunkIndex].start = memory;
	chunk_list[memChunkIndex].length = length;
	chunk_list[memChunkIndex].RW = RW;
}
