/*Linux网络常用函数库头文件*/
#ifndef __unp_h
#define __unp_h

#include <sys/types.h>	//basic system data types
#include <sys/socket.h> //basic socket definitions
#include <sys/time.h>	//timeval{} for select()
#include <time.h>		//timespec{} for pselect()
#include <netinet/in.h>	//sockaddr_in{} and other Internet defns
#include <arpa/inet.h>	//inet(3) functions	提供IP地址转换函数
#include <errno.h>
#include <fcntl.h>		//for nonblocking
#include <netdb.h>		//提供设置及获取域名的函数
#include <signal.h>		//提供对信号操作的函数
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>	//for S_xxx file mode constants
#include <sys/uio.h>	//for iovec{} and readv/writev
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>		//for Unix domain sockets
#include <arpa/inet.h>
#include <pthread.h>	//提供多线程操作的函数


#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>	// for convenience
#endif // HAVE_SYS_SELECT_H

#ifdef HAVE_SYS_SYSCTL_H
#include <sys/sysctl.h>
#endif // HAVE_SYS_SYSCTL_H

#ifdef HAVE_POLL_H
#include <poll.h>		//for convenience
#endif // HAVE_POLL_H

#ifdef HAVE_STRINGS_H
#include <strings.h>	//for convenience
#endif // HAVE_STRINGS_H


/* Thress headers are normally needed for socket/file ioctl`s:
* <sys/ioctl.h> <sys/filio.h> <sys/sockio.h>
*/
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif // HAVE_SYS_IOCTL_H

#ifdef HAVE_SYS_FILIO_H
#include <sys/filio.h>
#endif // HAVE_SYS_FILIO_H

#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif // HAVE_SYS_SOCKIO_H

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif // HAVE_PTHREAD_H

#ifdef HAVE_NET_IF_DL_H
#include <net/if_dl.h>
#endif // HAVE_NET_IF_DL_H

/*OSF/1 actually disables recv() and send() in <sys/socket.h>*/
#ifdef __osf__
#undef recv
#undef send
#define recv(a,b,c,d) recvfrom(a,b,c,d,0,0)
#define send(a,b,c,d) sendto(a,b,c,d,0,0)
#endif // __osf__





#endif // !__unp_h
