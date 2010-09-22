/*
 * rminfo.h - SAM-FS removable media file access definitions.
 *
 * Defines the SAM-FS removable media file access structure and functions.
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
 * $Id: rminfo.h,v 1.13 2007/01/08 21:45:41 jdunn Exp $
 */

#ifdef sun
#pragma ident "$Id: rminfo.h,v 1.13 2007/01/08 21:45:41 jdunn Exp $"
#endif


#ifndef SAM_RMINFO_H
#define	SAM_RMINFO_H


#ifdef	linux
#include <linux/types.h>
#else	/* linux */
#include <sys/types.h>
#endif	/* linux */

#ifndef SAM_STAT_H
#include "pub/stat.h"
#endif /* SAM_STAT_H */

#ifdef  __cplusplus
extern "C" {
#endif

/* Allocate sam_rminfo structure based on the number of vsns. */

#define	MAX_VOLUMES 256		/* Maximum number of overflow vsns */

#define	SAM_RMINFO_SIZE(n) (sizeof(struct sam_rminfo) + ((n) - 1) * \
		sizeof(struct sam_section))

/* Begin: 32-bit align copyin() structs for amd64 only due to 32-bit x86 ABI */
#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
#pragma pack(4)
#endif

#if defined(__sparcv9) || defined(__amd64)

struct sam_rminfo {
	ushort_t flags;		/* Access flags */
	ushort_t unused;
	char	media[4];	/* Media type */
	time_t	creation_time;	/* Time file created */
	u_longlong_t position;	/* Current position on the media */
	u_longlong_t required_size;	/* Required size on a request */
	uint_t	block_size;	/* Media block size */

	/* For optical media */
	char	file_id[32];	/* Recorded file name */
	int	version;	/* Version number */
	char	owner_id[32];	/* Owner identifier */
	char	group_id[32];	/* Group identifier */
	char	info[160];	/* User information */

	/* For all media. */
	short	n_vsns;		/* Number of VSNs available */
	short	c_vsn;		/* Current VSN */
	struct sam_section section[1];	/* VSNs information */
};

#else   /* __sparcv9 || __amd64 */

struct sam_rminfo {
	ushort_t flags;		/* Access flags */
	ushort_t unused;
	char	media[4];	/* Media type */
	ulong_t	pad0;
	time_t	creation_time;	/* Time file created */
	u_longlong_t position;	/* Current position on the media */
	u_longlong_t required_size;	/* Required size on a request */
	uint_t	block_size;	/* Media block size */

	/* For optical media */
	char	file_id[32];	/* Recorded file name */
	int	version;	/* Version number */
	char	owner_id[32];	/* Owner identifier */
	char	group_id[32];	/* Group identifier */
	char	info[160];	/* User information */

	/* For all media. */
	short	n_vsns;		/* Number of VSNs available */
	short	c_vsn;		/* Current VSN */
	struct sam_section section[1];	/* VSNs information */
};

#endif   /* __sparcv9 || __amd64 */

/* End: 32-bit align copyin() structs for amd64 only due to 32-bit x86 ABI */
#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
#pragma pack()
#endif


/* Flags. */
#define	RI_blockio 	0x0001	/* Use block I/O for data transfers */
#define	RI_bufio   	0x0002	/* Use buffered block I/O for data transfers */
#define	RI_foreign	0x0004	/* Open Non SAM tape for read only access */
#define	RI_nopos    0x0008	/* For block I/O, don't position media on mount */

int sam_readrminfo(const char *path, struct sam_rminfo *buf, size_t bufsize);
int sam_request(const char *path, struct sam_rminfo *buf, size_t bufsize);

#ifdef  __cplusplus
}
#endif

#endif  /* SAM_RMINFO_H */
