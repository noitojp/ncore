#include <sys/types.h>
#include <errno.h>
#include <zlib.h>
#include "compress.h"

int nax_gzip(char *dest,int destlen,const char *src,int srclen,int level)
{
	z_stream zs;
	int rc;
	int ret;

	zs.zalloc = Z_NULL;
	zs.zfree = Z_NULL;
	zs.opaque = Z_NULL;
	ret = deflateInit_(&zs,level,ZLIB_VERSION,(int)sizeof(z_stream));
	if( ret != Z_OK ){
		return(ret);
	}

	zs.next_in = (const Bytef*)src;
	zs.avail_in = srclen;
	zs.next_out = (Bytef*)dest;
	zs.avail_out = destlen;
	ret = deflate(&zs,Z_FINISH);
	while( Z_OK == ret ){
		ret = deflate(&zs,Z_FINISH);
	}
	deflateEnd(&zs);

	if( ret != Z_STREAM_END ){
		return(ret);
	}
	else{
		rc = destlen - (int)(zs.avail_out);
		return(rc);
	}
}

int nax_gunzip(char *dest,int destlen,const char *src,int srclen)
{
	z_stream zs;
	int rc;
	int ret;

	zs.zalloc = Z_NULL;
	zs.zfree = Z_NULL;
	zs.opaque = Z_NULL;
	ret = inflateInit_(&zs,ZLIB_VERSION,(int)sizeof(z_stream));
	if( ret != Z_OK ){
		return(ret);
	}

	zs.next_in = (const Bytef*)src;
	zs.avail_in = srclen;
	zs.next_out = (Bytef*)dest;
	zs.avail_out = destlen;
	ret = inflate(&zs,Z_FINISH);
	while( Z_OK == ret ){
		ret = inflate(&zs,Z_FINISH);
	}
	inflateEnd(&zs);

	if( ret != Z_STREAM_END ){
		return(ret);
	}
	else{
		rc = destlen - (int)(zs.avail_out);
		return(rc);
	}
}

