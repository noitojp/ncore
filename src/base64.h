#ifndef __NAX_BASE64_H_
#define __NAX_BASE64_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int nax_encode64(char *dest,const char *src,int srclen);
extern int nax_decode64(char *dest,const char *src,int srclen);

#ifdef __cplusplus
}
#endif

#endif
