#include "order.h"
#include "bench.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv) {
	if (argc<2) { printf("Please invoke as %s <order_file>\n",argv[0]); 	return 1; }
	if (!openOrder(argv[1])) { return 1; }
	do {
		int pn=nextPartNumber();
		int bin=pn/10;
		/* Replace the following code with a better implementation */

			if (binInSlot(0)!=bin) { fetchBin(bin,0); } /* Always use slot 0 */

		/* End of simple implementation */
	} while(fetchNextPart());
	closeOrder();
	return 0;
}
