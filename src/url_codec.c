#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "url_codec.h"

static inline int _hex2char(unsigned char *dest,int src)
{
	if( NULL == dest ){
		return(0);
	}

	if( src <= 'Z' && src >= 'A' ){
		*dest = src - 'A' + 10;
	}
	else if( src <= 'z' && src >= 'a' ){
		*dest = src - 'a' + 10;
	}
	else if( isdigit(src) ){
		*dest = src - '0';
	}
	else{
		return(0);
	}
	return(1);
}

static inline int _char2hex(unsigned char *dest,int cx)
{
	static const char xtable[] = {'0', '1', '2', '3', '4', '5', '6', '7',
								  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	div_t ans;
	int rc;

	if( isalnum(cx) || '.' == cx || '-' == cx || '_' == cx ){
		*dest = cx;
		rc = 1;
	}
	else if( ' ' == cx ){
		*dest = '+';
		rc = 1;
	}
	else{
		ans = div(cx,0x10);
		*dest = '%';
		*(dest+1) = xtable[ans.quot];
		*(dest+2) = xtable[ans.rem];
		rc = 3;
	}

	return(rc);
}

static inline int _decode_pctstr(unsigned char *dest,const unsigned char *src)
{
	unsigned char byte1 = 0;
	unsigned char byte2 = 0;

	if( NULL == dest || NULL == src || *src != '%' ){
		return(0);
	}

	if( !_hex2char(&byte1,*++src) ){
		return(0);
	}
	if( !_hex2char(&byte2,*++src) ){
		return(0);
	}

	*dest = byte1 * 16 + byte2;
	return(1);
}

int nax_urldecode(char *dest,const char *src,int slen)
{
	int rc = 0;
	int ix;

	if( NULL == dest || NULL == src || slen <= 0 ){
		return(-1);
	}

	for( ix = 0; ix < slen; ){
		if( '%' == src[ix] ){
			if( !_decode_pctstr((unsigned char*)dest,(const unsigned char*)&src[ix]) ){
				return(-1);
			}
			dest++;
			ix += 3;
		}
		else if( '+' == src[ix] ){
			*dest++ = ' ';
			ix++;
		}
		else{
			*dest++ = src[ix++];
		}
		rc++;
	}

	*dest = '\0';
	return(rc);
}

int nax_urlencode(char *dest,const char *src,int slen)
{
	int ix;
	int jx;

	if( NULL == dest || NULL == src || slen <= 0 ){
		return(-1);
	}

	for( ix = 0, jx = 0; ix < slen; ix++ ){
		jx += _char2hex((unsigned char*)&dest[jx],(unsigned char)src[ix]);
	}

	dest[jx] = '\0';
	return(jx);
}

