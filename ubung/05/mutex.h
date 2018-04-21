#ifndef __MUTEX_H__
#define __MUTEX_H__

// es ist nur fuer tsl.o
int tsl(unsigned char *adr);

// eigene Defination
void mutex_lock(unsigned char* lock);
void mutex_unlock(unsigned char* lock);

#endif /* #ifndef __MUTEX_H__ */
