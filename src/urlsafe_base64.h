#ifndef __NAX_BASE64_URLSAFE_H_
#define __NAX_BASE64_URLSAFE_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int nax_encode64_urlsafe(char *dest,const char *src,int slen);
extern int nax_decode64_urlsafe(unsigned char *dest,const char *src,int slen);

#ifdef __cplusplus
}
#endif

#endif

