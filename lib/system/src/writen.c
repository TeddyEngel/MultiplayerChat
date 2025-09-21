#include <errno.h>
#include <unistd.h>

ssize_t writen(int fd, const void *buf, size_t n)
{
    size_t left = n;
    const char *p = buf;
    while (left > 0)
    {
        ssize_t written = write(fd, p, left);
        if (written <= 0)
        {
            if (errno == EINTR)
                continue; // retry
            return -1; // error
        }
        left -= written;
        p += written;
    }
    return n;
}
