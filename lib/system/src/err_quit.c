#include <stdio.h>
#include <stdlib.h>

void err_quit(const char* error)
{ 
    printf(error);
    exit(1); 
}