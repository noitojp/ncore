#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include "urlsafe_base64.h"

static inline char _conv2char(uint8_t ch)
{
	static const char _conv_arr[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '-', '_'
	};

	return( _conv_arr[ch] );
}

static inline uint8_t _conv2bit(uint8_t *d,char ch)
{
	if( ch >= 'A' && ch <= 'Z' ){
		*d = ch - 'A';
	}
	else if( ch >= 'a' && ch <= 'z' ){
		*d = ch - 'a' + 0x1a;
	}
	else if( ch >= '0' && ch <= '9' ){
		*d = ch - '0' + 0x34;
	}
	else if( '-' == ch ){
		*d = 0x3e;
	}
	else if( '_' == ch ){
		*d = 0x3f;
	}
	else{
		return(0);
	}

	return(1);
}

int nax_encode64_urlsafe(char *dest,const char *src,int srclen)
{
	int ix;
	int jx;

	if(NULL == dest || NULL == src){
		return(-1);
	}

	for( ix = 0, jx = 0; ix < srclen; ix += 3, jx += 4 ){
		dest[jx] = _conv2char((uint8_t)src[ix] >> 2);

		if( ix + 1 >= srclen ){
			dest[jx + 1] = _conv2char(((uint8_t)src[ix] & 0x03) << 4);
			dest[jx + 2] = '\0';
			return(jx + 2);
		}

		dest[jx + 1] = _conv2char((((unsigned char)src[ix] & 0x03) << 4) + (((unsigned char)src[ix + 1]) >> 4));
		if( ix + 2 >= srclen ){
			dest[jx + 2] = _conv2char(((unsigned char)src[ix + 1] & 0x0f) << 2);
			dest[jx + 3] = '\0';
			return(jx + 3 );
		}

		dest[jx + 2] = _conv2char((((unsigned char)src[ix + 1] & 0x0f) << 2) + (((unsigned char)src[ix + 2]) >> 6));
		dest[jx + 3] = _conv2char((unsigned char)src[ix + 2] & 0x3f);
		dest[jx + 4] = '\0';
	}

	return(jx);
}

int nax_decode64_urlsafe(uint8_t *dest,const char *src,int srclen)
{
	int rc;
	int ix;
	int jx;

	if( NULL == dest || NULL == src ){
		return(0);
	}

	for( ix = 0, jx = 0; ix < srclen; ix += 4, jx += 3 ){
		uint8_t tmp[4];

		memset(tmp,'\0',sizeof(tmp));
		if( !_conv2bit(&tmp[0],(char)src[ix]) ){ return(0); }
		if( srclen > ix + 1 ){
			if( !_conv2bit(&tmp[1],(char)src[ix+1]) ){ return(0); }
		}
		if( srclen > ix + 2 ){
			if( !_conv2bit(&tmp[2],(char)src[ix+2]) ){ return(0); }
		}
		if( srclen > ix + 3 ){
			if( !_conv2bit(&tmp[3],(char)src[ix+3]) ){ return(0); }
		}

		if( ix + 3 < srclen ){
			dest[jx] = (tmp[0] << 2) + (tmp[1] >> 4);
			dest[jx + 1] = (tmp[1] << 4) + (tmp[2] >> 2);
			dest[jx + 2] = (tmp[2] << 6) + tmp[3];
		}
		else if( ix + 2 < srclen ){
			dest[jx] = (tmp[0] << 2) + (tmp[1] >> 4);
			dest[jx + 1] = (tmp[1] << 4) + (tmp[2] >> 2);
			dest[jx + 2] = tmp[2] << 6;
		}
		else if( ix + 1 < srclen ){
			dest[jx] = (tmp[0] << 2) + (tmp[1] >> 4);
			dest[jx + 1] = tmp[1] << 4;
		}
		else if( ix < srclen ){
			dest[jx] = tmp[0] << 2;
		}
	}

	rc = ((srclen + 3) / 4) * 3;
    rc -= (4 - srclen) & 3;
	return(rc);
}

