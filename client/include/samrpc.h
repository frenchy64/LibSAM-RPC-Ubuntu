/* samrpc.h - SAM-FS user rpc library structures and definitions
 *
 * Definitions for SAM-FS user rpc library structures and definitions
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
 * $Id: samrpc.h,v 1.11 2007/01/08 21:45:41 jdunn Exp $
 */

#ifdef sun
#pragma ident "$Id: samrpc.h,v 1.11 2007/01/08 21:45:41 jdunn Exp $"
#endif


#ifndef SAMFS_H_RPCGEN
#define	SAMFS_H_RPCGEN

#include <rpc/rpc.h>
#include <sys/types.h>
#include <sys/time.h>
#ifndef SAM_STAT_H
#include "stat.h"
#endif

#ifdef  __cplusplus
extern "C" {
#endif

#define	MAX_VSN 32
#define	MAX_OPTS 24

struct filecmd {
	char *filename;
	char *options;
};

struct statcmd {
	char *filename;
	int size;
};

typedef struct filecmd filecmd;

typedef struct statcmd statcmd;

typedef struct sam_stat samstat_t;

struct sam_st {
	int result;
	samstat_t s;
};

typedef struct sam_st sam_st;
typedef struct sam_copy_s samcopy;

#define	xdr_uint_t	xdr_u_int
#define	xdr_time_t	xdr_long
#define	xdr_ushort_t	xdr_u_short
#define	xdr_ulong_t	xdr_u_long

#define	SamFS ((unsigned long)(0x20000002))
#define	SAMVERS ((unsigned long)(1))
#define	samstat ((unsigned long)(1))
extern  sam_st * samstat_1();
#define	samlstat ((unsigned long)(2))
extern  sam_st * samlstat_1();
#define	samarchive ((unsigned long)(3))
extern  int * samarchive_1();
#define	samrelease ((unsigned long)(4))
extern  int * samrelease_1();
#define	samstage ((unsigned long)(5))
extern  int * samstage_1();
#define	samsetfa ((unsigned long)(6))
extern  int * samsetfa_1();
#define	samsegment ((unsigned long)(7))
extern  int * samsegment_1();
extern int samfs_1_freeresult();

/* the xdr functions */
extern bool_t xdr_filecmd();
extern bool_t xdr_statcmd();
extern bool_t xdr_samstat_t();
extern bool_t xdr_sam_st();

#ifndef	SAM_LIB
extern	CLIENT	*clnt;
#endif /* !SAM_LIB */

#define	PROGNAME	"samfs"
#define	SAMRPC_HOST	"samhost"

/* Functions. */
int sam_initrpc(char *rpchost);
int sam_closerpc(void);

#ifdef  __cplusplus
}
#endif

#endif /* SAMFS_H_RPCGEN */
