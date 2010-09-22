/* lib.h - SAM-FS API library functions.
 *
 * Definitions for SAM-FS API library functions.
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

/*
 * $Id: lib.h,v 1.11 2007/01/08 21:45:40 jdunn Exp $
 */

#ifdef sun
#pragma ident "$Id: lib.h,v 1.11 2007/01/08 21:45:40 jdunn Exp $"
#endif


#ifndef	SAMLIB_H
#define SAMLIB_H

#ifdef linux
#include <sam/linux_types.h>	/* uint_t */
#endif /* linux */

#ifdef  __cplusplus
extern "C" {
#endif

int sam_archive(const char *name, const char *opns);
char *sam_attrtoa(int attr, char *string);
int sam_cancelstage(const char *name);
char *sam_devstr(uint_t p);
int sam_release(const char *name, const char *opns);
int sam_ssum(const char *name, const char *opns);
int sam_stage(const char *name, const char *opns);
int sam_setfa(const char *name, const char *opns);
int sam_segment(const char *name, const char *opns);
int sam_advise(const int fildes, const char *opns);

#ifdef  __cplusplus
}
#endif

#endif /* SAMLIB_H */
