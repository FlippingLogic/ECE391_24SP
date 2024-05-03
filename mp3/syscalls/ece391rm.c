#include <stdint.h>

#include "ece391support.h"
#include "ece391syscall.h"

#define BUFSIZE 1024

int main(){
    int32_t fd;
    uint8_t filename[BUFSIZE];

    if (0 != ece391_getargs (filename, BUFSIZE)) {
        ece391_fdputs (1, (uint8_t*)"could not read argument\n");
        return 3;
    }

    // check if this file exists
    if ( -1 == ece391_open (filename)) {
	    ece391_fdputs (1, (uint8_t*)"file does not exist\n");
	    return 3;
	}

    // open a dentry, get fd for operation
    if (-1 == (fd = ece391_open ((uint8_t*)"."))) {
        ece391_fdputs (1, (uint8_t*)"directory open failed\n");
	    return 3;
    }

    // use dwrite to create a new file
    if ( -1 == ece391_write (fd, filename, -1) ){
        ece391_fdputs (1, (uint8_t*)"file removal failed\n");
        return 3;
    }

    if( -1 == ece391_close(fd) ){
        ece391_fdputs (1, (uint8_t*)"file descriptor closing failed\n");
        return 3;
    }

    ece391_fdputs (1, (uint8_t*)"file removed successfully\n");
    return 0;

}