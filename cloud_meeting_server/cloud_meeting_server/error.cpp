#include <errno.h>
#include "unp.h"
#include <stdarg.h>

static void err_doit(int errnoflag, int error, const char* fmt, va_list ap)
{
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE - 1, fmt, ap);	//用于向一个字符串缓冲区打印格式化字符串，且可以限定打印的格式化字符串的最大长度。

	if (errnoflag)
	{
		snprintf(buf + strlen(buf), MAXLINE - 1 - strlen(buf), ": %s", strerror(error));
	}
	strcat(buf, "\n");
	fflush(stdout);		//清空标准输出缓冲区, 保证快速输出
	fputs(buf, stderr);	//把字符串写入到屏幕标准错误流中，但不包括空字符
	fflush(NULL);		//将所有打开的文件数据更新
}

/*
* fatal error unrelated to a system call
* print a message and terminate
*/

void err_quit(const char* fmt, ...)
{
	va_list ap;			//va_list用于获取不确定个数的参数
	va_start(ap, fmt);	// 指针指向 fmt 之后的参数
	err_doit(1, errno, fmt, ap);
	va_end(ap);			//清空va_list可变参数列表
	exit(1);
}

void err_msg(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
}