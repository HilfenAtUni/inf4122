#include <stdio.h>
#include "mutex.h"

void mutex_lock(unsigned char* lk)
{
	unsigned char stat;
	do{
		stat = tsl(lk);
	}while(0 != stat);
}

void mutex_unlock(unsigned char* lk)
{
	*lk = 0;
}
