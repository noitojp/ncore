#ifndef __NAX_STRUTIL_H_
#define __NAX_STRUTIL_H_

#include <stdio.h>

typedef struct{
	int len;
	char *ptr;
} nax_token_t;

#ifdef __cplusplus
extern "C" {
#endif

extern int nax_rstrip(char *str,const char *chs);
extern int nax_fastsplitc(char **index,char *str,char dlmt,int isize);
extern int nax_fastsplitt(nax_token_t *index,const char *str,char dlmt,int isize);
extern int nax_strlcpy(char *dest,const char *src,int len);
extern int nax_strnlen(const char *str,int max_len);
extern char* nax_strdup(const char *src,int src_len);
extern nax_token_t nax_strtok_r(const char *str,char delim,char **saveptr);
extern const char *nax_basename(const char *path);

#ifdef __cplusplus
}
#endif

static inline int nax_is_null_or_empty(const char *str)
{
	if( NULL == str || '\0' == *str ){
		return(1);
	}

	return(0);
}

#endif
