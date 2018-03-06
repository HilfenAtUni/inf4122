#ifndef __MY_MUTEX_H__
#define __MY_MUTEX_H__

// es ist nur fuer tsl.o
int my_tsl(unsigned char *adr);

// eigene Defination
void my_mutex_lock(unsigned char* lock);
void my_mutex_unlock(unsigned char* lock);

#endif /* #ifndef __MY_MUTEX_H__ */
