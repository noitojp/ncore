#ifndef __NAX_PC_UID_H_
#define __NAX_PC_UID_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int verify_pc_uidstr(const char *uid);
extern int verify_pc_uid(const char *uid,int len);

#ifdef __cplusplus
}
#endif

#endif
