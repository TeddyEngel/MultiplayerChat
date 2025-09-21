#include <stdio.h>
#include <stdlib.h>

void err_sys(const char* x)
{ 
    perror(x); 
    exit(1); 
}