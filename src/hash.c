#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include "hash.h"

int nax_get_str_javahash(int *hash,const char *src)
{
	if( NULL == hash || NULL == src ){
		return(0);
	}

	return( nax_get_javahash(hash,src,(int)strlen(src)) );
}

int nax_get_javahash(int *hash,const char *src,int len)
{
	int ix;
	int tmp;

	if( NULL == hash || NULL == src || len <= 0 ){
		return(0);
	}

	*hash = 0;
	for( ix = 0; ix < len; ){
		if( 0x00 == ((unsigned char)src[ix] & 0x80 )){
			tmp = (unsigned char)src[ix];
			ix++;
		}
		else if( 0xC0 == ((unsigned char)src[ix] & 0xE0 )){
			if( ix + 2 > len ){
				return(0);
			}

			tmp = (((unsigned char)src[ix] & 0x1F)<<6)  + ((unsigned char)src[ix+1] & 0x3F);
			ix += 2;
		}
		else if( 0xE0 == ((unsigned char)src[ix] & 0xF0 )){
			if( ix + 3 > len ){
				return(0);
			}

			tmp = (((unsigned char)src[ix] & 0x0F)<<12) + (((unsigned char)src[ix+1] & 0x3F)<<6) + ((unsigned char)src[ix+2] & 0x3F);
			ix += 3;
		}
		else if( 0xF0 == ((unsigned char)src[ix] & 0xF8 )){
			if( ix + 4 > len ){
				return(0);
			}

			tmp = (((unsigned char)src[ix] & 0x07)<<18) + (((unsigned char)src[ix+1] & 0x3F)<<12) + (((unsigned char)src[ix+2] & 0x3F)<<6) + ((unsigned char)src[ix+3] & 0x3F);
			ix += 4;
		}
		else{
			return(0);
		}

		*hash = *hash * 31 + tmp;
	}

	return(1);
}

