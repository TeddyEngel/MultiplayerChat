#include <sys/socket.h>

#include "err_sys.h"

int Socket(int family, int type, int protocol)
{
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		err_sys("Socket Eorror");
	return n;
}