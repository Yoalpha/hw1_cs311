#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>

int lastUsed[5];
int time  = 0;

// This is my LRU cache implementation i dont use a doubly linked list with a hashmap because i think it is unecessary, in this case our cache is going to be of size 5 so we could just use an array 
// that has a last_used_time which lets me know which slot was used last and i evict that if i cant place a bin


// Returns -1 if a bin is not in the slot
int findSlotforBin(int bin){
	for(int i = 0; i < 5; i++){
		if(binInSlot(i) == bin){
			return i;
		}
	}
	return -1;
}

// Returns index that had the earliest time
int chooseEvictionSlot(){
	int minimum = INT_MAX;
	int slot = -1;
	for (int i = 0 ; i < 5; i++){
		if(lastUsed[i] < minimum){
			minimum = lastUsed[i];
			slot = i;
		}
	} 
	return slot;
}

// Returns the first empty index in the slots
int findEmptySpace(){
	for(int i = 0; i < 5; i++){
		if(binInSlot(i) == -1){
			return i;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	if (argc<2) { printf("Please invoke as %s <order_file>\n",argv[0]); 	return 1; }
	if (!openOrder(argv[1])) { return 1; }
	do {
		printf("time=%d | lastUsed: ", time);
		for (int i = 0; i < 5; i++) {
    			printf("%d ", lastUsed[i]);
		}
		printf("\n");
		int pn=nextPartNumber();
		int bin=pn/10;
		/* Replace the following code with a better implementation */
		int slot = findSlotforBin(bin);
		
		if (slot != -1){
			printf("the bin is in the slot");
			printf("\n");
			lastUsed[slot] = time++;
		}
		else{
		int insert = findEmptySpace();
		if (insert == -1){
			printf("we are evicting right now");
			printf("\n");
			int eviction_index = chooseEvictionSlot();
			lastUsed[eviction_index] = time++;
			fetchBin(bin,eviction_index);
		}
		else{
				fetchBin(bin,insert);
				lastUsed[insert] = time++;
				printf("we are in the normal insert");
					printf("\n");
			
		}
		}
		/* End of simple implementation */
	} while(fetchNextPart());
	closeOrder();
	return 0;
}
