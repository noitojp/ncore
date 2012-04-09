#ifndef __NAX_URLCODEC_H_
#define __NAX_URLCODEC_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int nax_urldecode(char *dest,const char *src,int slen);
extern int nax_urlencode(char *dest,const char *src,int slen);

#ifdef __cplusplus
}
#endif

#endif
