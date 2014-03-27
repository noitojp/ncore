#ifndef __NAX_BASE64_URLSAFE_H_
#define __NAX_BASE64_URLSAFE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int nax_encode64_urlsafe(char *dest,const char *src,int srclen);
extern int nax_decode64_urlsafe(uint8_t *dest,const char *src,int srclen);

#ifdef __cplusplus
}
#endif

#endif

