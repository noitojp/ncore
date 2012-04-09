#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "str_util.h"

static inline int _is_target(int ch,const char *chs)
{
	int ix;

	for( ix = 0; chs[ix]; ix++ ){
		if( ch == chs[ix] ){
			return(1);
		}
	}

	return(0);
}

int nax_rstrip(char *str,const char *chs)
{
	int len;

	if( NULL == str || NULL == chs ){
		return(-1);
	}

	len = strlen(str);
	while( len > 0 && _is_target(str[len-1],chs) ){
		str[len-1] = '\0';
		len--;
	}

    return(len);
}

int nax_fastsplitc(char **index,char *str,char dlmt,int isize)
{
	int ix = 0;
	int jx = 0;

	if( NULL == index || NULL == str || isize <= 1 ){
		return(-1);
	}

	for( index[ix] = &str[jx]; str[jx]; jx++ ){
		if( str[jx] != dlmt ){
			continue;
		}

		if( ix >= isize - 2 ){
			break;
		}

		str[jx] = '\0';
		index[++ix] = &str[jx+1];
	}

	index[++ix] = NULL;
	return(ix);
}

int nax_fastsplitt(nax_token_t *index,const char *str,char dlmt,int isize)
{
	int ix = 0;
	int jx = 0;
	int len = 0;

	if( NULL == index || NULL == str || isize <= 1 ){
		return(-1);
	}

	for( index[ix].ptr = &str[jx]; str[jx]; jx++ ){
		if( str[jx] != dlmt ){
			len++;
			continue;
		}

		if( ix >= isize - 2 ){
			len = strlen(index[ix].ptr);
			break;
		}

		index[ix].len = len; len = 0;
		index[++ix].ptr = &str[jx+1];
	}

	index[ix++].len = len;
	index[ix].ptr = NULL;
	index[ix].len = 0;
	return(ix);
}

int nax_strlcpy(char *dest,const char *src,int len)
{
	int ix;

	if( NULL == dest || NULL == src || len <= 0 ){
		return(-1);
	}

	for( ix = 0; src[ix] != '\0' && ix < len - 1; ix++ ){
		dest[ix] = src[ix];
	}

	dest[ix] = '\0';
	return(ix);
}

int nax_strnlen(const char *str,int max_len)
{
	int ix;

	if( NULL == str || max_len <= 0 ){
		return(-1);
	}

	for( ix = 0; str[ix] != '\0' && ix < max_len; ix++){
		;
	}

	if( max_len == ix && str[ix] != '\0' ){
		return(-1);
	}

	return(ix);
}

char* nax_strdup(const char *src,int src_len)
{
	char *rc = NULL;

	rc = (char*)malloc(src_len + 1);
	if( NULL == rc ){
		return(NULL);
	}

	memcpy(rc,src,src_len);
	rc[src_len] = '\0';
	return(rc);
}

nax_token_t nax_strtok_r(const char *str,char delim,char **saveptr)
{
	nax_token_t rc = {0,NULL};
	int ix;

	if( NULL == saveptr || ( NULL == str && '\0' == **saveptr ) ){
		return(rc);
	}

	if( str != NULL ){
		rc.ptr = str;
	}
	else{
		rc.ptr = *saveptr;
	}

	for(ix = 0; rc.ptr[ix] != '\0' && rc.ptr[ix] != delim; ix++ );
	if( rc.ptr[ix] == delim ){
		*saveptr = &rc.ptr[ix+1];
	}
	else{
		*saveptr = &rc.ptr[ix];
	}
	rc.len = ix;
	return(rc);
}

// TODO: nax_strtoull
// TODO: nax_strtoll
// TODO: nax_strtoul
// TODO: nax_strtol

const char *nax_basename(const char *path)
{
	const char *rc = (const char*)path;

	for( ; *path != '\0'; path++ ){
		if( '/' == *path ){
			rc = path + 1;
		}
	}

	if( '\0' == *rc ){
		return(NULL);
	}

	return(rc);
}

