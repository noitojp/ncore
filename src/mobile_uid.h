#ifndef __NAX_MOBILE_UID_H_
#define __NAX_MOBILE_UID_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int verify_mobile_uidstr(const char *uid);
extern int verify_mobile_uid(const char *uid,int len);

extern int is_docomo_uidstr(const char *uid);
extern int is_docomo_long_uidstr(const char *uid);
extern int is_au_uidstr(const char *uid);
extern int is_softbank_uidstr(const char *uid);

extern int is_docomo_uid(const char *uid,int len);
extern int is_docomo_long_uid(const char *uid,int len);
extern int is_au_uid(const char *uid,int len);
extern int is_softbank_uid(const char *uid,int len);

#ifdef __cplusplus
}
#endif

#endif
