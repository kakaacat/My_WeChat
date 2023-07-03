#ifndef MSG_H
#define MSG_H

#include <queue>
#include "unp.h"
#include "unpthread.h"
#include "netheader.h"
#define MAXSIZE 10000
#define MB (1024*1024)

enum STATUS
{
	CLOSE = 0,
	ON = 1,
};

struct MSG
{
	char* ptr;
	int len;
	int targetfd;
	MSG_TYPE msgType;
	uint32_t ip;
	Image_Format format;

	MSG()
	{

	}

	MSG(MSG_TYPE msg_type, char* msg, int length, int fd)
	{
		msgType = msg_type;
		ptr = msg;
		len = length;
		targetfd = fd;
	}
};


struct SEND_QUEUE
{
private:
	pthread_mutex_t lock;	//互斥锁
	pthread_cond_t cond;
	std::queue<MSG> send_queue;

public:
	SEND_QUEUE()
	{
		lock = PTHREAD_MUTEX_INITIALIZER;
		cond = PTHREAD_COND_INITIALIZER;
	}

	void push_msg(MSG msg)
	{
		Pthread_mutex_lock(&lock);
		while (send_queue.size() >= MAXSIZE)
		{
			Pthread_cond_wait(&cond, &lock);	//pthread_cond_wait() 用于阻塞当前线程，等待别的线程使用pthread_cond_signal()或pthread_cond_broadcast来唤醒它。
		}
		send_queue.push(msg);
		Pthread_mutex_unlock(&lock);
		Pthread_cond_signal(&cond);		//pthread_cond_signal函数的作用是发送一个信号给另外一个正在处于阻塞等待状态的线程,使其脱离阻塞状态,继续执行.
										//如果没有线程处在阻塞等待状态,pthread_cond_signal也会成功返回。
	}

	MSG pop_msg()
	{
		Pthread_mutex_lock(&lock);
		while (send_queue.empty())
		{
			Pthread_cond_wait(&cond, &lock);
		}
		MSG msg = send_queue.front();
		send_queue.pop();
		Pthread_mutex_unlock(&lock);
		Pthread_cond_signal(&cond);
		return msg;
	}

	void clear()
	{
		Pthread_mutex_lock(&lock);
		while (!send_queue.empty())
		{
			send_queue.pop();
		}
		Pthread_mutex_unlock(&lock);
	}
};

#endif // !MSG_H


/* class 和 struct 的区别
* 1.默认的继承访问权。class默认的是private，struct默认的是public
* 2.默认的访问权限。struct作为数据结构的实现体，它默认的数据访问控制是public
*	而class作为对象的实现体，它默认的成员变量访问控制是private
* 3.class这个关键字还用于定义模板参数，就像typename。但struct关键字不用于定义模板参数。
*/