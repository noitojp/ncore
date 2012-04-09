#ifndef __NAX_COMPRESS_H_
#define __NAX_COMPRESS_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int nax_gzip(char *dest,int destlen,const char *src,int srclen,int level);
extern int nax_gunzip(char *dest,int destlen,const char *src,int srclen);

#ifdef __cplusplus
}
#endif

#endif
