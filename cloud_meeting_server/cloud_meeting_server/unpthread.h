#ifndef UNPTHREAD_H
#define UNPTHREAD_H

/* Our own header for the programs that use threads.
   Include this file, instead of "unp.h". */
#include <pthread.h>
#include "unp.h"

typedef void * (THREAD_FUNC) (void *);	//定义一个函数，void *是一种无类型指针

typedef struct
{
	pthread_t thread_tid;
}Thread;

typedef struct
{
	pid_t child_pid;	//process id
	int child_pipefd;	//parent`s stream pipe to/from child
	int child_status;	//0=ready
	int total;
}Process;

typedef struct Room //single
{
	int navail;
	Process* pptr;
	pthread_mutex_t lock;

	Room(int n)
	{
		navail = n;
		pptr = (Process*)Calloc(n, sizeof(Process));	/*C 库函数 void *calloc(size_t nitems, size_t size) 分配所需的内存空间，并返回一个指向它的指针。
														malloc 和 calloc 之间的不同点是，malloc 不会设置内存为零，而 calloc 会设置分配的内存为零。*/
		lock = PTHREAD_MUTEX_INITIALIZER;
	}
}Room;

void	Pthread_create(pthread_t*, const pthread_attr_t*,
	void* (*)(void*), void*);
void	Pthread_join(pthread_t, void**);
void	Pthread_detach(pthread_t);
void	Pthread_kill(pthread_t, int);

void	Pthread_mutexattr_init(pthread_mutexattr_t*);
void	Pthread_mutexattr_setpshared(pthread_mutexattr_t*, int);
void	Pthread_mutex_init(pthread_mutex_t*, pthread_mutexattr_t*);
void	Pthread_mutex_lock(pthread_mutex_t*);
void	Pthread_mutex_unlock(pthread_mutex_t*);

void	Pthread_cond_broadcast(pthread_cond_t*);
void	Pthread_cond_signal(pthread_cond_t*);
void	Pthread_cond_wait(pthread_cond_t*, pthread_mutex_t*);
void	Pthread_cond_timedwait(pthread_cond_t*, pthread_mutex_t*,
	const struct timespec*);

void	Pthread_key_create(pthread_key_t*, void (*)(void*)); /*void (*)(void*)是一个抽象出来的函数指针的模型 ，用来为专门应对这一类事物的复杂交互提供便利， 
															 比如有了类型就能声“名”出未初始化的对象用来做参数甚至为该类事物提供动态分配的没名字的对象 ， 以及批量操作对象*/
void	Pthread_setspecific(pthread_key_t, const void*);
void	Pthread_once(pthread_once_t*, void (*)(void));

void     Pthread_detach(pthread_t);


#endif // !UNPTHREAD_H
