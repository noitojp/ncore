#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include "str_util.h"
#include "pc_uid.h"

#define PC_UID_LEN 36

int verify_pc_uidstr(const char *uid)
{
	int len;

	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	len = nax_strnlen(uid,PC_UID_LEN);
	return(verify_pc_uid(uid,len));
}

int verify_pc_uid(const char *uid,int len)
{
	int ix;

	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( len != PC_UID_LEN ){
		return(0);
	}

	for( ix = 0; ix < PC_UID_LEN; ix++ ){
		switch(ix){
			case 8:
			case 13:
			case 18:
			case 23:
				if( uid[ix] != '-' ){
					return(0);
				}
				break;
			default:
				if( !isalnum(uid[ix]) ){
					return(0);
				}
				break;
		}
	}

	return(1);
}

