#include "urlsafe_base64.h"

static const char _basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
static const unsigned char _pr2six[256] = {
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 62, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
	64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 63,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

int nax_encode64_urlsafe(char *dest,const char *src,int slen)
{
	char *d;
	const unsigned char *s;
	int ix;

	if(NULL == dest || NULL == src || slen <= 0){
		return 0;
	}

	d = dest;
	s = (const unsigned char*)src;
	for( ix = 0; ix < slen - 2; ix += 3 ){
		*d++ = _basis_64[(s[ix] >> 2) & 0x3f];
		*d++ = _basis_64[((s[ix] & 0x3) << 4) | ((int)(s[ix + 1] & 0xf0) >> 4)];
		*d++ = _basis_64[((s[ix + 1] & 0xf) << 2) | ((int)(s[ix + 2] & 0xc0) >> 6)];
		*d++ = _basis_64[s[ix + 2] & 0x3f];
	}

	if( ix < slen ){
		*d++ = _basis_64[(s[ix] >> 2) & 0x3f];
		if( (slen - 1) == ix ){
			*d++ = _basis_64[((s[ix] & 0x3) << 4)];
		}
		else{
			*d++ = _basis_64[((s[ix] & 0x3) << 4) | ((int)(s[ix + 1] & 0xf0) >> 4)];
			*d++ = _basis_64[((s[ix + 1] & 0xf) << 2)];
		}
	}
	*d = '\0';
	return d - dest;
}

int nax_decode64_urlsafe(unsigned char *dest,const char *src,int slen)
{
	int rc = 0;
	int ix;
	
	if(NULL == dest || NULL == src || slen <= 0){
		return 0;
	}

	while( slen >= 4 ){
		*dest++ = (unsigned char)(_pr2six[src[0]] << 2 | _pr2six[src[1]] >> 4);
		*dest++ = (unsigned char)(_pr2six[src[1]] << 4 | _pr2six[src[2]] >> 2);
		*dest++ = (unsigned char)(_pr2six[src[2]] << 6 | _pr2six[src[3]]);
		slen -= 4;
		src += 4;
		rc += 3;
	}

	switch( slen ){
	case 1:
		*dest++ = (unsigned char)(_pr2six[src[0]] << 2);
		break;
	case 2:
		*dest++ = (unsigned char)(_pr2six[src[0]] << 2 | _pr2six[src[1]] >> 4);
		*dest++ = (unsigned char)(_pr2six[src[1]] << 4);
		rc += 1;
		break;
	case 3:
		*dest++ = (unsigned char)(_pr2six[src[0]] << 2 | _pr2six[src[1]] >> 4);
		*dest++ = (unsigned char)(_pr2six[src[1]] << 4 | _pr2six[src[2]] >> 2);
		*dest++ = (unsigned char)(_pr2six[src[2]] << 6);
		rc += 2;
		break;
	}

	return rc;
}

