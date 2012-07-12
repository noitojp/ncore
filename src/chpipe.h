#ifndef __NAX_CHPIPE_H_
#define __NAX_CHPIPE_H_

#include <sys/types.h>

typedef struct{
	pid_t pid;
	int pipe;
} nax_chpipe_t;

#ifdef __cplusplus
extern "C" {
#endif

extern nax_chpipe_t* nax_popen2(const char *cmd);
extern int nax_pwrite(const nax_chpipe_t *p,const char *src,int siz);
extern int nax_pread(const nax_chpipe_t *p,char *dest,int siz);
extern void nax_pclose2(nax_chpipe_t *p);

#ifdef __cplusplus
}
#endif

#endif
