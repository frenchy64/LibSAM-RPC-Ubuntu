/* sam_attrtoa.c - Convert SAM-FS attributes to ASCII.
 *
 */

/*
 *    SAM-QFS_notice_begin
 *
 *      Solaris 2.x Sun Storage & Archiving Management File System
 *
 *      Copyright (c) 2007 Sun Microsystems, Inc.
 *      All Rights Reserved.
 *
 *      Government Rights Notice
 *      Use, duplication, or disclosure by the U.S. Government is
 *      subject to restrictions set forth in the Sun Microsystems,
 *      Inc. license agreements and as provided in DFARS 227.7202-1(a)
 *      and 227.7202-3(a) (1995), DRAS 252.227-7013(c)(ii) (OCT 1988),
 *      FAR 12.212(a)(1995), FAR 52.227-19, or FAR 52.227-14 (ALT III),
 *      as applicable.  Sun Microsystems, Inc.
 *
 *    SAM-QFS_notice_end
 */

#ifndef lint
static char rcs_id[] = "@(#)$Id: sam_attrtoa.c,v 1.9 2007/01/08 21:49:24 jdunn Exp $";
#endif /* lint */
#pragma ident "$Id: sam_attrtoa.c,v 1.9 2007/01/08 21:49:24 jdunn Exp $"


/* POSIX headers. */
#include <sys/types.h>

/* SAM-FS headers. */
#include "lib.h"
#include "stat.h"


/*
 *	Return attributes in ASCII from attribute field.
 */
char *			/* String returned */
sam_attrtoa(
int attr,		/* Attributes field */
char *string)	/* If not NULL, place string here */
{
	static char s[24];

	if (string == NULL)  string = s;
	string[0] = (SS_ISOFFLINE(attr)) ? 'O' : '-';
	if (SS_ISDAMAGED(attr))  string[0] = 'E';

	/* archive */
	string[1] = (SS_ISARCHIVE_N(attr)) ? 'n' : '-';
	string[2] = (SS_ISARCHIVE_A(attr)) ? 'a' : '-';
	string[3] = (SS_ISARCHIVE_R(attr)) ? 'r' : '-';

	/* release */
	string[4] = (SS_ISRELEASE_N(attr)) ? 'n' : '-';
	string[5] = (SS_ISRELEASE_A(attr)) ? 'a' : '-';
	string[6] = (SS_ISRELEASE_P(attr)) ? 'p' : '-';

	/* stage */
	string[7] = (SS_ISSTAGE_N(attr)) ? 'n' : '-';
	string[8] = (SS_ISSTAGE_A(attr)) ? 'a' : '-';
	string[9] = '-';

	string[10] = ' ';

	/* checksum & worm attributes */
    string[11] = (SS_ISCSGEN(attr)) ? 'g' : '-';
    string[12] = (SS_ISCSUSE(attr)) ? 'u' : '-';
    string[13] = (SS_ISCSVAL(attr)) ? 'v' : '-';
    string[14] = (SS_ISWORM(attr)) ? 'w' : '-';
    string[15] = (SS_ISREADONLY(attr)) ? 'R' : '-';
    string[16] = ' ';

    /* segment attributes */
    string[17] = (SS_ISSEGMENT_A(attr)) ? 's' : '-';
    if (SS_ISSEGMENT_F(attr))  {
        string[18] =  'I';
    } else if (SS_ISSEGMENT_S(attr))  {
        string[18] =  'S';
    } else string[18] = '-';
    string[19] = '\0';

	return(string);
}
