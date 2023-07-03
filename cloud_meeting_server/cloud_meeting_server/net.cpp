#include "unp.h"

/*
* get peer ipv4 (network order)
*/

//fd: 文件描述符(file descriptor)
uint32_t getpeerip(int fd)
{
	sockaddr_in peeraddr;
	socklen_t addrlen;
	if (getpeername(fd, (sockaddr*)&peeraddr, &addrlen) < 0)
	{
		err_msg("getpeername error");
		return -1;
	}
	return peeraddr.sin_addr.s_addr;
}

int Select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* execpfds, struct timeval* timeout)
{
	int n;
	for (;;)
	{
		if ((n == select(nfds, readfds, writefds, execpfds, timeout)) < 0)
		{
			if (error == EINTR)
			{
				continue;
			}
			else
			{
				break;
			}
		}
	}

	return n;	//can return 0 on timeout
}

ssize_t Readn(int fd, void* buf, size_t size)
{
	ssize_t lefttoread = size, hasread = 0;
	char* ptr = (char*)buf;
	while (lefttoread > 0)
	{
		if ((hasread = read(fd, ptr, lefttoread)) < 0)
		{
			if (errno == EINTR)
			{
				hasread = 0;
			}
			else
			{
				return -1;
			}
		}
		else if (hasread == 0)	//eof
		{
			break;
		}
		lefttoread -= hasread;
		ptr += hasread;
	}
	return size - lefttoread;
}

ssize_t writen(int fd, const void* buf, size_t n)
{
	ssize_t lefttowrite = n, haswrite = 0;
	char* ptr = (char*)buf;
	while (lefttowrite > 0)
	{
		if ((haswrite = write(fd, ptr, lefttowrite)) < 0)
		{
			if (haswrite < 0 && errno == EINTR)
			{
				haswrite = 0;
			}
			else
			{
				return -1;	//error
			}
		}
		lefttowrite -= haswrite;
		ptr += haswrite;
	}
	return n;
}

char* Sock_ntop(char* str, int size, const sockaddr* sa, socklen_t salen)
{
	switch (sa->sa_family)
	{
	case AF_INET:
		{
			struct sockaddr_in* sin = (sturct sockaddr_in*) sa;
			if (inet_ntop(AF_INET, &sin->sin_addr, str, size) == NULL)
			{
				err_msg("inet_ntop error");
				return NULL;
			}
			if (ntohs(sin->sin_port) > 0)
			{
				//snprintf用于格式化输出字符串，并将结果写入到指定的缓冲区
				snprintf(str + strlen(str), size - strlen(str), ":%d", ntohs(sin->sin_port));
			}
			return str;
		}
	case AF_INET6:
		{
			struct sockaddr_in6* sin = (struct sockaddr_in6*)sa;
			if (inet_ntop(AF_INET6, &sin->sin6_addr, str, size) == NULL)
			{
				err_msg("inet_ntop error");
				return NULL;
			}
			if (ntohs(sin->sin6_port) > 0)
			{
				snprintf(str + strlen(str), size - strlen(str), ":%d", ntohs(sin->sin6_port));
			}
			return str;
		}
	default:
		return "server error";
	}
	return NULL;
}


void Setsockopt(int fd, int level, int optname, const void* optval, socklen_t optlen)
{
	if (setsockopt(fd, level, optname, optval, optlen) < 0)
	{
		err_msg("setsockopt error");
	}
}

void Close(int fd)
{
	if (close(fd) < 0)
	{
		err_msg("Close error");
	}
}

void Listen(int fd, int backlog)
{
	if (listen(fd, backlog) < 0)
	{
		err_quit("listen error");
	}
}

int Tcp_connect(const char* host, const char* serv)
{

}