/*	catalog.h - SAM-FS library catalog information definitions.
 *
 *	Defines the SAM-FS catalog structure and functions.
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
 * $Id: catalog.h,v 1.9 2007/01/08 21:45:40 jdunn Exp $
 */

#ifdef sun
#pragma ident "$Id: catalog.h,v 1.9 2007/01/08 21:45:40 jdunn Exp $"
#endif


#ifndef SAM_CATALOG_H
#define SAM_CATALOG_H

#ifdef  __cplusplus
extern "C" {
#endif


#define BARCODE_LEN     36	/* length of barcode w/o null byte */
#define MAX_CAT		5		/* max number of open catalogs per user */

/*
 * catalog table
 */

struct sam_cat_tbl {
	time_t	audit_time;		/* Audit time */
	int	version;			/* Catalog version number */
	int	count;				/* Number of slots */
	char	media[4];		/* Media type, if entire catalog is one */
};

/*
 * catalog table entry.
 */

struct sam_cat_ent {
	uint_t  type;			/* Type of slot */
	uint_t	status;			/* Catalog entry status */
	char	media[4];		/* Media type */
	char	vsn[32];		/* VSN */
	int	access;			/* Count of accesses */
	uint_t	capacity;		/* Capacity of volume */
	uint_t	space;			/* Space left on volume */
	int	ptoc_fwa;		/* First word address of PTOC */
	int	reserved[3];		/* Reserved space */
	time_t	modification_time;	/* Last modification time */
	time_t	mount_time;		/* Last mount time */
	uchar_t	bar_code[BARCODE_LEN + 1];	/* Bar code (zero filled) */
};

/* slot type definitions */

#define CATALOG_SLOT_MEDIA		0	/* Slot contains media */
#define CATALOG_SLOT_DRIVE		1	/* Slot contains a drive */
#define CATALOG_SLOT_MAIL		2	/* Slot contains a mailbox */

/* defines for status word */

#define CSP_NEEDS_AUDIT	0x80000000
#define CSP_INUSE		0x40000000
#define CSP_LABELED		0x20000000
#define CSP_BAD_MEDIA		0x10000000

#define CSP_OCCUPIED		0x08000000
#define CSP_CLEANING		0x04000000
#define CSP_BAR_CODE		0x02000000
#define CSP_WRITEPROTECT	0x01000000

#define CSP_READ_ONLY		0x00800000
#define CSP_RECYCLE		0x00400000
#define CSP_UNAVAIL		0x00200000
#define CSP_EXPORT		0x00100000

#define	CS_NEEDS_AUDIT(status)		(((status)&CSP_NEEDS_AUDIT)!=0)
#define	CS_INUSE(status)		(((status)&CSP_INUSE)!=0)
#define	CS_LABELED(status)		(((status)&CSP_LABELED)!=0)
#define	CS_BADMEDIA(status)		(((status)&CSP_BAD_MEDIA)!=0)
#define	CS_OCCUPIED(status)		(((status)&CSP_OCCUPIED)!=0)
#define	CS_CLEANING(status)		(((status)&CSP_CLEANING)!=0)
#define	CS_BARCODE(status)		(((status)&CSP_BAR_CODE)!=0)
#define	CS_WRTPROT(status)		(((status)&CSP_WRITEPROTECT)!=0)
#define	CS_RDONLY(status)		(((status)&CSP_READ_ONLY)!=0)
#define	CS_RECYCLE(status)		(((status)&CSP_RECYCLE)!=0)
#define	CS_UNAVAIL(status)		(((status)&CSP_UNAVAIL)!=0)
#define	CS_EXPORT(status)		(((status)&CSP_EXPORT)!=0)


int	sam_opencat(const char *path, struct sam_cat_tbl *buf, size_t bufsize);
int	sam_getcatalog(int cat_handle, uint start_slot, uint end_slot,
		struct sam_cat_ent *buf, size_t entbufsize);
int	sam_closecat(int cat_handle);

#ifdef  __cplusplus
}
#endif

#endif  /* SAM_CATALOG_H */
