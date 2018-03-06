#include <stdio.h>
#include "my_mutex.h"

void my_mutex_lock(unsigned char* lk)
{
	unsigned char stat;
	do{
		stat = my_tsl(lk);
	}while(0 != stat);
}

void my_mutex_unlock(unsigned char* lk)
{
	*lk = 0;
}
