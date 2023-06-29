﻿/*Linux网络常用函数库头文件
  以及一些项目中用到的宏定义
*/

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


#ifndef INADDR_NONE
/* $$.Ic INADDR_NONE$$ */
#define	INADDR_NONE	0xffffffff	// should have been in <netinet/in.h>
#endif // INADDR_NONE

#ifndef SHUT_RD				// these three Posix.1g names are quite new
#define SHUT_RD	  0			//shutdown for reading
#define SHUT_WR   1			//shutdown for writing
#define SHUT_RDWR 2			//shutdown for reading and writing
/* $$.Ic SHUT_RD$$ */
/* $$.Ic SHUT_WR$$ */
/* $$.Ic SHUT_RDWR$$ */
#endif // !SHUT_RD

/* *INDENT-OFF* */
#ifndef INET_ADDRSTRLEN
/* $$.Ic INET_ADDRSTRLEN$$ */
#define INET_ADDRRSTRLEN	16	/* "ddd.ddd.ddd.ddd\0"
                                    1234567890123456 */
#endif // !INET_ADDRSTRLEN

/*Define following even if IPv6 not supported, so we can always allocate 
    an adequately-sized buffer, without #ifdefs in the code.*/
#ifndef INET6_ADDRSTRLEN
/* $$.Ic INET6_ADDRSTRLEN$$ */
#define INET6_ADDRSTRLEN    64  /* max size of IPv6 address string:
                   "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:xxxx" or
                   "xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:ddd.ddd.ddd.ddd\0"
                    1234567890123456789012345678901234567890123456 */
#endif // !INET6_ADDRSTRLEN
/* *INDENT-ON* */

// Define bzero() as a macro if it`s not in standard C library.
#ifndef HAVE_BZERO
#define bzero(ptr,n)    memset(ptr, 0, n)
/* $$.If bzero$$ */
/* $$.If memset$$ */
#endif // !HAVE_BZERO

//Older resolvers do not have gethostbyname2()
#ifndef HAVE_GETHOSTBYNAME2
#define gethostbyname2(host,family) gethostbyname((host))
#endif // !HAVE_GETHOSTBYNAME2

///* The structure returned by recvfrom_flags() */
//struct in_pktinfo {
//  struct in_addr	ipi_addr;	/* dst IPv4 address */
//  int				ipi_ifindex;/* received interface index */
//};
/* $$.It in_pktinfo$$ */
/* $$.Ib ipi_addr$$ */
/* $$.Ib ipi_ifindex$$ */

/* We need the newer CMSG_LEN() and CMSG_SPACE() macros, but few
   implementations support them today.  These two macros really need
    an ALIGN() macro, but each implementation does this differently. */
#ifndef CMSG_LEN
/* $$.Ic CMSG_LEN$$ */
#define CMSG_LEN(size)  (sizeof(struct cmsghdr) + (size))
#endif // !CMSG_LEN
#ifndef CMSG_SPACE
/* $$.Ic CMSG_SAPCE$$ */
#define CMSG_SAPCE(size)    (sizeof(struct cmsghdr) + (size))
#endif // !CMSG_SPACE

/* Posix.1g requires the SUN_LEN() macro but not all implementations DefinE
   it (yet).  Note that this 4.4BSD macro works regardless whether there is
   a length field or not. */
#ifndef SUN_LEN
/* $$.Im SUN_LEN$$ */
#define SUN_LEN(su) \
    (sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))
#endif // !SUN_LEN

/* Posix.1g renames "Unix domain" as "local IPC".
   But not all systems DefinE AF_LOCAL and PF_LOCAL (yet). */
#ifndef AF_LOCAL
#define AF_LOCAL    AF_UNIX
#endif // !AF_LOCAL
#ifndef PF_LOCAL
#define PF_LOCAL    PF_UNIX
#endif // !PF_LOCAL

/* Posix.1g requires that an #include of <poll.h> DefinE INFTIM, but many
    systems still DefinE it in <sys/stropts.h>.  We don't want to include
    all the streams stuff if it's not needed, so we just DefinE INFTIM here.
    This is the standard value, but there's no guarantee it is -1. */
#ifndef INFTIM
#define INFTIM  (-1)    //infinite poll timeout
/* $$.Ic INFTIM$$ */
#ifdef HAVE_POLL_H
#define INFTIM_UNPH     //tell unpxti.h we defined it
#endif // HAVE_POLL_H
#endif // !INFTIM

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define LISTENQ 1024    //2nd argument to listen()

/* Miscellaneous constants */
#define MAXLINE     4096    //max text line length
#define MAXSOCKADDR 128     //max socket address structure size
#define BUFFSIZE    8192   //buffer size for reads and writes

//Define some port number that can be used for client-servers
#define SERV_PORT       9877            //TCP and UDP client-servers
#define SERV_PORT_STR   "9877"          //TCP and UDP client-servers
#define UNIXSTR_PATH    "/tem/unix.str" //Unix domain stream cli-serv
#define UNIXDG_PATH     "/tem/unix.dg"  //Unix domain datagram cli-serv
/* $$.ix [LISTENQ]~constant,~definition~of$$ */
/* $$.ix [MAXLINE]~constant,~definition~of$$ */
/* $$.ix [MAXSOCKADDR]~constant,~definition~of$$ */
/* $$.ix [BUFFSIZE]~constant,~definition~of$$ */
/* $$.ix [SERV_PORT]~constant,~definition~of$$ */
/* $$.ix [UNIXSTR_PATH]~constant,~definition~of$$ */
/* $$.ix [UNIXDG_PATH]~constant,~definition~of$$ */


//Following shortens all the type casts of pointer arguments
#define SA struct sockaddr

#define FILE_MODE   (S_IRUSR | S_IWUSR  | S_IRGRP | S_IROTH)
                    /* default file access permissions for new files */
#define DIR_MODE    (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
                    /* default permissions for new directories */

typedef void    Sigfunc(int);   //for signal handlers

#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define MAX(a,b)    ((a) > (b) ? (a) : (b))

/* end unph */


/* prototypes for our own library functions */



#endif // !__unp_h
