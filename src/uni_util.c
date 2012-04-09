#include <sys/types.h>
#include <linux/limits.h>
#include <sys/time.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include "uni_util.h"

#define _OPEN_MAX_GUESS 256

#ifdef OPEN_MAX
static int _openmax = OPEN_MAX;
#else
static int _openmax = 0;
#endif

void nax_msleep(int msec)
{
	struct timeval tv;

	tv.tv_sec = msec / 1000;
	tv.tv_usec = (msec % 1000) * 1000;
	select(0,NULL,NULL,NULL,&tv);
}

int nax_symlink(const char *target, const char *link)
{
	char tmp_path[PATH_MAX + 1];

	if( NULL == target || NULL == link ){
		return(-1);
	}

    snprintf(tmp_path,sizeof(tmp_path),"%s.%ld.%d",link,time(NULL),getpid());
	if( symlink(target,tmp_path) < 0 ){
		fprintf(stderr,"ERROR: can't create symlink %s to %s\n",link,target);
		return(-1);
	}

	if( rename(tmp_path,link) < 0 ){
		unlink(tmp_path);
		fprintf(stderr,"ERROR: can't create symlink %s to %s\n",link,target);
		return(-1);
	}

	return(0);
}

int nax_openmax(void)
{
	if( _openmax != 0 ){
		return(_openmax);
	}

	errno = 0;
	if( (_openmax = sysconf(_SC_OPEN_MAX)) < 0 ){
		if( 0 == errno ){
			_openmax = _OPEN_MAX_GUESS;
		}
		else{
			fprintf(stderr,"ERROR: sysconf error for _SC_OPEN_MAX: %s\n",strerror(errno));
		}
	}

	return(_openmax);
}

int nax_poll_single_desc(int fd,int msec)
{
	int max_fd = -1;
	fd_set readfds;
	struct timeval tv;
	int ret;

	FD_ZERO(&readfds);
	max_fd = MY_FD_SET(&readfds,fd,max_fd);
	tv.tv_sec = msec / 1000;
	tv.tv_usec = (msec % 1000) * 1000;
	ret = select(max_fd+1,&readfds,NULL,NULL,&tv);
	if( ret <= 0 ){
		return(ret);
	}

	if( MY_FD_ISSET(fd,&readfds) ){
		return(fd);
	}
	else{
		return(-1);
	}
}

