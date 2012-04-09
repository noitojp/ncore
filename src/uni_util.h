#ifndef __NAX_UNIXUTIL_H_
#define __NAX_UNIXUTIL_H_

#include <sys/select.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void nax_msleep(int msec);
extern int nax_symlink(const char *target, const char *link);
extern int nax_openmax(void);
extern int nax_poll_single_desc(int fd,int msec);

#ifdef __cplusplus
}
#endif

static inline int MY_FD_SET(fd_set *set,int fd,int max_fd)
{
	if( NULL == set ){
		return(max_fd);
	}

	FD_SET(fd,set);
	if( fd > max_fd ){
		max_fd = fd;
	}

	return(max_fd);
}

static inline int MY_FD_ISSET(int fd,fd_set *set)
{
	if( NULL == set || fd < 0 ){
		return(0);
	}

	return( FD_ISSET(fd,set) );
}

#endif
