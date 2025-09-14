#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>

#define TABLE_SIZE 5
#define PARTS 5


// function to re arrange the lru cache based on the most recently used.
void arrageUsed(int* used, int last_used){
    int pos = 0;


    for(int i = 0; i<PARTS; i++){
        if(last_used == used[i]){
            pos = i;
        }
    }

    for(int i = pos; i<PARTS; i++){
        used[i] = used [i+1];

    }
    used[PARTS-1] = last_used;
}


int checkSlot(int bin){
	// returns -1 if bin is not on the workbench
	// returns the slot of the passed bin
	for(int slot = 0; slot<5; slot++){
		if(binInSlot(slot)==bin){
			return slot;
		}	
	}
	return -1;
}

int checkEmptySlot(){		
	// returns -1 if no empty slots 
	// returns first empty slot
	for(int i=0; i<5; i++){
		if(binInSlot(i)==-1){
			return i;
		}
	}
	return -1;
}

int main(int argc, char **argv) {
	if (argc<2) { printf("Please invoke as %s <order_file>\n",argv[0]); 	return 1; }
	if (!openOrder(argv[1])) { return 1; }

	int lru[5] = {0,0,0,0,0};
	int flag = 0; // Flag is 0 if bin is not on table
	int slots_used = 0; // Slots used on the bench
	int slot;


	do {
		int pn=nextPartNumber();
		int bin=pn/10;

			flag = 0;
			
			// checking if the required bin is already on the bench
			for(int slot = 0; slot<5; slot++){
				if(binInSlot(slot) == bin){
					flag=1;
				}	
			};
			
			// If bin is not on workbench
			if(flag == 0){
				if(slots_used == 5){
					// When there are no spots left on the table
					slot = checkSlot(lru[0]);
					fetchBin(bin, slot);
					
				}else{
					// when there are spots left on the table 
					slot = checkEmptySlot();
					fetchBin(bin, slot);
					slots_used++;
				}
			}

			// re-arranging lru cache based on the most recently used bin
			arrageUsed(lru, bin);

	} while(fetchNextPart());
	closeOrder();
	return 0;
}
