#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include "base64.h"

static inline char _conv2char(int ch)
{
	static const char _conv_arr[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/'
	};

	if( ch < 0 || ch > 0x3f ){
		return('=');
	}

	return( _conv_arr[ch] );
}

static inline char _conv2bit(int ch)
{
	if( ch >= 'A' && ch <= 'Z' ){
		return( ch - 'A' );
	}
	else if( ch >= 'a' && ch <= 'z' ){
		return( ch - 'a' + 0x1a );
	}
	else if( ch >= '0' && ch <= '9' ){
		return( ch - '0' + 0x34 );
	}
	else if( '+' == ch ){
		return(0x3e);
	}
	else if( '/' == ch ){
		return(0x3f);
	}
	else if( '=' == ch ){
		return('\0');
	}

	return(-1);
}

int nax_encode64(char *dest,const char *src,int srclen)
{
	int ix;
	int jx;

	if(NULL == dest || NULL == src){
		return(-1);
	}

	for( ix = 0, jx = 0; ix < srclen; ix += 3, jx += 4 ){
		dest[jx] = _conv2char((unsigned char)src[ix] >> 2);

		if( ix + 1 >= srclen ){
			dest[jx + 1] = _conv2char(((unsigned char)src[ix] & 0x03) << 4);
			dest[jx + 2] = '=';
			dest[jx + 3] = '=';
			dest[jx + 4] = '\0';
			return(jx + 4);
		}

		dest[jx + 1] = _conv2char((((unsigned char)src[ix] & 0x03) << 4) + (((unsigned char)src[ix + 1]) >> 4));
		if( ix + 2 >= srclen ){
			dest[jx + 2] = _conv2char(((unsigned char)src[ix + 1] & 0x0f) << 2);
			dest[jx + 3] = '=';
			dest[jx + 4] = '\0';
			return(jx + 4 );
		}

		dest[jx + 2] = _conv2char( (((unsigned char)src[ix + 1] & 0x0f) << 2) + (((unsigned char)src[ix + 2]) >> 6));
		dest[jx + 3] = _conv2char((unsigned char)src[ix + 2] & 0x3f);
		dest[jx + 4] = '\0';
	}

	return(jx);
}

int nax_decode64(char *dest,const char *src,int srclen)
{
	int ix;
	int jx;
	int ret;
	int nprbytes;
	int tmp_char[4];

	if( (srclen % 4) != 0 ){
		return(-1);
	}

	nprbytes = srclen;
	for( ix = srclen - 1; ix >= 0; ix-- ){
		if( '=' == src[ix] ){
			nprbytes--;
		}
		else{
			break;
		}
	}

	for( ix = 0, jx = 0; ix < srclen; ix += 4, jx += 3 ){
		tmp_char[0] = _conv2bit((unsigned char)src[ix]);
		tmp_char[1] = _conv2bit((unsigned char)src[ix + 1]);
		tmp_char[2] = _conv2bit((unsigned char)src[ix + 2]);
		tmp_char[3] = _conv2bit((unsigned char)src[ix + 3]);
		dest[jx] = (tmp_char[0] << 2) + (tmp_char[1] >> 4);
		dest[jx + 1] = (tmp_char[1] << 4) + (tmp_char[2] >> 2);
		dest[jx + 2] = (tmp_char[2] << 6) + tmp_char[3];
		dest[jx + 3] = '\0';
	}

	ret = ((nprbytes + 3) / 4) * 3;
	ret -= (4 - nprbytes) & 3;
	return(ret);
}

