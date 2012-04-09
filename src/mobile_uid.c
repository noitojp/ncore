#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include "str_util.h"
#include "mobile_uid.h"

#define DOCOMO_UID_LEN 7
#define DOCOMO_LONG_UID_LEN 40
#define AU_PREFIX_LEN 14
#define AU_MIDDLE_LEN 17
#define AU_SAFIX_STR ".ezweb.ne.jp"
#define AU_SAFIX_LEN 12
#define AU_UID_LEN 29
#define SOFTBANK_UID_LEN 16

int verify_mobile_uidstr(const char *uid)
{
	int len;

	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	len = nax_strnlen(uid,DOCOMO_LONG_UID_LEN);
	return(verify_mobile_uid(uid,len));
}

int verify_mobile_uid(const char *uid,int len)
{
	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	switch(len){
		case DOCOMO_UID_LEN:
			return(is_docomo_uid(uid,len));
		case SOFTBANK_UID_LEN:
			return(is_softbank_uid(uid,len));
		case AU_UID_LEN:
			return(is_au_uid(uid,len));
		case DOCOMO_LONG_UID_LEN:
			return(is_docomo_long_uid(uid,len));
		default:
			return(0);
	}
}

int is_docomo_uidstr(const char *uid)
{
	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( !is_docomo_uid(uid,DOCOMO_UID_LEN) ){
		return(0);
	}

	if( uid[DOCOMO_UID_LEN] != '\0' ){
		return(0);
	}

	return(1);
}

int is_docomo_long_uidstr(const char *uid)
{
	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( !is_docomo_long_uid(uid,DOCOMO_LONG_UID_LEN) ){
		return(0);
	}

	if( uid[DOCOMO_LONG_UID_LEN] != '\0' ){
		return(0);
	}

	return(1);
}

int is_au_uidstr(const char *uid)
{
	if( NULL == uid || '\0' == *uid ){
		return(0);
	}


	if( !is_au_uid(uid,AU_UID_LEN) ){
		return(0);
	}

	if( uid[AU_UID_LEN] != '\0' ){
		return(0);
	}

	return(2);
}

int is_softbank_uidstr(const char *uid)
{
	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( !is_softbank_uid(uid,SOFTBANK_UID_LEN) ){
		return(0);
	}

	if( uid[SOFTBANK_UID_LEN] != '\0' ){
		return(0);
	}

	return(3);
}

int is_docomo_uid(const char *uid,int len)
{
	int ix;

	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( len != DOCOMO_UID_LEN ){
		return(0);
	}

	for( ix = 0; ix < DOCOMO_UID_LEN; ix++ ){
		if( !isalnum(uid[ix]) ){
			return(0);
		}
	}

	return(1);
}

int is_docomo_long_uid(const char *uid,int len)
{
	int ix;

	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( len != DOCOMO_LONG_UID_LEN ){
		return(0);
	}

	for( ix = 0; ix < DOCOMO_LONG_UID_LEN; ix++ ){
		if( !isalnum(uid[ix]) ){
			return(0);
		}
	}

	return(1);
}

int is_au_uid(const char *uid,int len)
{
	int ix;

	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( len != AU_UID_LEN ){
		return(0);
	}

	for( ix = 0; ix < AU_PREFIX_LEN; ix++ ){
		if( !isdigit(uid[ix]) ){
			return(0);
		}
	}

	if( uid[ix++] != '_' ){
		return(0);
	}

	for( ; ix < AU_MIDDLE_LEN; ix++ ){
		if( !isalpha(uid[ix]) ){
			return(0);
		}
	}

	if( strncmp(&uid[ix],AU_SAFIX_STR,(size_t)AU_SAFIX_LEN) == 0 ){
		return(2);
	}

	return(0);
}

int is_softbank_uid(const char *uid,int len)
{
	int ix;

	if( NULL == uid || '\0' == *uid ){
		return(0);
	}

	if( len != SOFTBANK_UID_LEN ){
		return(0);
	}

	for( ix = 0; ix < SOFTBANK_UID_LEN; ix++ ){
		if( !isalnum(uid[ix]) ){
			return(0);
		}
	}

	return(3);
}

