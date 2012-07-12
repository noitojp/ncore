#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "chpipe.h"

nax_chpipe_t* nax_popen(const char *cmd)
{
	nax_chpipe_t *rc = NULL;
	int pipe[2] = {-1,-1};
	pid_t pid = -1;
	int ret;

	rc = (nax_chpipe_t*)malloc(sizeof(nax_chpipe_t));
	if( NULL == rc ){
		goto error;
	}

	ret = socketpair(AF_LOCAL,SOCK_STREAM,0,pipe);
	if( ret < 0 ){
		goto error;
	}

	pid = fork();
	if( pid < 0 ){
		goto error;
	}
	else if( 0 == pid ){
		close(pipe[0]); pipe[0] = -1;
		dup2(pipe[1],STDIN_FILENO);
		dup2(pipe[1],STDOUT_FILENO);
		close(pipe[1]); pipe[1] = -1;
		execl("/bin/sh","sh","-c",cmd,NULL);
		exit(1);
	}
	else{
		close(pipe[1]); pipe[1] = -1;
	}

	rc->pid = pid;
	rc->pipe = pipe[0];
	return(rc);

 error:
	if( pipe[0] >= 0 ){ close(pipe[0]);}
	if( pipe[1] >= 0 ){ close(pipe[1]);}
	free(rc); rc = NULL;
	return(NULL);
}

int nax_pwrite(const nax_chpipe_t *p,const char *src,int siz)
{
	if( NULL == p || NULL == src || siz < 0 || p->pipe < 0 ){ return(-1); }
	return( (int)write(p->pipe,src,siz) );
}

int nax_pread(const nax_chpipe_t *p,char *dest,int siz)
{
	if( NULL == p || NULL == dest || siz < 0 || p->pipe < 0 ){ return(-1); }
	return( (int)read(p->pipe,dest,siz) );
}

void nax_pclose(nax_chpipe_t *p)
{
	int status;

	if( NULL == p ){ return; }
	if( p->pipe >= 0 ){ close(p->pipe); p->pipe = -1; }
	if( p->pid > 0){ waitpid(p->pid,&status,0); }
	free(p);
	return;
}

