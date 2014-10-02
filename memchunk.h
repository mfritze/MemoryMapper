/*Matthew Fritze
1360555
CMPUT 379
Assignment 1 */

#include <stdio.h>
#include <signal.h>
#include "unistd.h"
#include <setjmp.h>

struct memchunk { 
            void *start; 
            unsigned long length; 
            int RW; 
};

int get_mem_layout (struct memchunk *chunk_list, int size);

