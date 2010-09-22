/* sefstructs.h - SAM-FS system error facility (_AML_SEF)  information.
 *
 *      Description:
 *          Definitions for SAM-FS system error facility
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

#if !defined(_AML_SEFSTRUCTS_H)
#define _AML_SEFSTRUCTS_H

#pragma ident "$Id: sefstructs.h,v 1.6 2007/01/08 21:45:37 jdunn Exp $"

/*
 * In the SCSI spec, the possible page codes returned in the "list of
 * supported pages" are 0 - 0x3F.
 */
#define SEF_MAX_PAGES	(0x3F + 1)

struct sef_hdr {

	/* the following fields will be filled in once at open */
	uint_t		sef_magic;				/* magic # for app to sync file posn */
	uint_t		sef_version;			/* version number */
	uint_t		sef_size;				/* size of this record, excl. header */
	uint16_t	sef_eq;					/* equipment number of this device */
	char		sef_devname[128];		/* pathname of device */
	uchar_t		sef_vendor_id[9];		/* vendor id from inquiry */
	uchar_t		sef_product_id[17];		/* product id from inquiry */
	uchar_t		sef_revision[5];		/* revision level from inquiry */
	uchar_t		sef_scsi_type;			/* device type from inquiry */

	/* the following fields must be filled in before each record is written */
	char		sef_vsn[32];			/* vsn of media that was mounted */
	time_t		sef_timestamp;			/* timestamp of this record */

};


struct sef_pginfo {
	ushort	pgcode;
	ushort	pglen;
};

/*
 * struct sef_devinfo contains the fields of sef information that are put in
 * the dev_ent_t structure--in the device table.
 */
struct sef_devinfo {
	struct sef_pginfo sef_pgs[SEF_MAX_PAGES];
	struct sef_hdr	*sef_hdr;	/* ptr to sef header for this device */
	uint8_t sef_inited;	/* indicates sef has been initialized for this dev */
};


/* Structure of a scsi-standard log sense page header */
struct sef_pg_hdr {
	uchar_t		page_code;
	uchar_t		reserved;
	ushort		page_len;
};

/* Structure of "supported pages" log sense page */
struct sef_supp_pgs {
	struct sef_pg_hdr	hdr;
	uchar_t		supp_pgs[SEF_MAX_PAGES];
};

#endif /* !defined(_AML_SEFSTRUCTS_H) */
