/* sefvals.h - SAM-FS system error facility (SEF)  information.
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

#if !defined(_AML_SEFVALS_H)
#define _AML_SEFVALS_H

#pragma ident "$Id: sefvals.h,v 1.11 2007/01/08 21:45:37 jdunn Exp $"

#define         SEF_INITED        1 /* sef_inited dev ready */
#define         SEF_NOT_SUPPORTED 2 /* sef_inited dev log sns pgs not supported */

/*
 * Use a macro to specify which log sense pages we're interested in.
 * Right now, those are:
 * 02	write error counter page
 * 03	read error counter page
 * 06	nonmedia error page
 *
 * If the list log sense pages used for SEF is changed then SEFPAGE
 * needs to be changed.
 */

#define		SEF_WR_ERR_LOG_PG 	2
#define		SEF_RD_ERR_LOG_PG 	3
#define		SEF_NON_MEDIA_LOG_PG 	6

#define		SEFPAGE(pg)\
	((pg == SEF_WR_ERR_LOG_PG || pg == SEF_RD_ERR_LOG_PG || \
	  pg == SEF_NON_MEDIA_LOG_PG) ? \
		B_TRUE : B_FALSE)

#define		SEF_INQ_TP_TYPE		1
#define		SEF_INQ_MC_TYPE		8

#define		SEFMAGIC	0x94F

#define		SEFVERSION	1

#define		SEFFILE		SAM_VARIABLE_PATH"/sef/sefdata"

/* sysevent handler class, subclass, vendor, publisher */
#define SEF_SE_CLASS "Device"        /* class */
#define SEF_SE_SUBCLASS "SEF"        /* subclass */
#define SEF_SE_VENDOR "SUNW"         /* vendor */
#define SEF_SE_PUBLISHER "SUNWsamfs" /* publisher */

/* sysevent handler macros for read and write error counters found in
   log sense pages 2 and 3 */
#define SEF_VENDOR "VENDOR"	/* string - inquiry vendor */
#define SEF_PRODUCT "PRODUCT"	/* string - inquiry product */
#define SEF_REV "REV"		/* string - inquiry revision */
#define SEF_USN "USN"		/* string - inquiry unit serial number */
#define SEF_TOD "TOD"		/* int32 - time of day */
#define SEF_EQ_ORD "EQ_ORD"	/* int16 - mcf eq ordinal */
#define SEF_NAME "NAME"		/* string - device name */
#define SEF_VERSION "VERSION"	/* byte - inquiry version */
#define SEF_INQ_TYPE "INQ_TYPE"	/* byte - inquiry peripheral dev type */
#define SEF_MEDIA_TYPE "MEDIA_TYPE" /* string - samfs media type */
#define SEF_VSN "VSN"		/* string - volume serial number */
#define SEF_LABEL_TIME "LABEL_TIME" /* string - label timestamp */
#define SEF_SET "SET"           /* string - mcf family set name */
#define SEF_FSEQ "FSEQ"         /* int16 - family set eq ord */ 
#define SEF_WHERE "WHERE"       /* byte - SEF location poll or unload  */

/* write log sense page 2 */ 
#define SEF_LP2_PC0 "LP2_PC0"   /* uint32 - errors corrected without substantial delay */
#define SEF_LP2_PC1 "LP2_PC1"   /* uint32 - errors corrected with possible delays */
#define SEF_LP2_PC2 "LP2_PC2"   /* uint32 - total rewrites */
#define SEF_LP2_PC3 "LP2_PC3"   /* uint32 - total errors corrected */
#define SEF_LP2_PC4 "LP2_PC4"   /* uint32 - total times correction algorithm processed */
#define SEF_LP2_PC5 "LP2_PC5"   /* uint64 - total bytes processed */
#define SEF_LP2_PC6 "LP2_PC6"   /* uint32 - total uncorrected errors */

/* read log sense page 3 */ 
#define SEF_LP3_PC0 "LP3_PC0"   /* uint32 - errors corrected without substantial delay */
#define SEF_LP3_PC1 "LP3_PC1"   /* uint32 - errors corrected with possible delays */
#define SEF_LP3_PC2 "LP3_PC2"   /* uint32 - total rereads */
#define SEF_LP3_PC3 "LP3_PC3"   /* uint32 - total errors corrected */
#define SEF_LP3_PC4 "LP3_PC4"   /* uint32 - total times correction algorithm processed */
#define SEF_LP3_PC5 "LP3_PC5"   /* uint64 - total bytes processed */
#define SEF_LP3_PC6 "LP3_PC6"   /* uint32 - total uncorrected errors */

/* vsn or barcode empty string */
#define SEF_EMPTY_STR "\"\""

#endif /* !defined(_AML_SEFVALS_H) */
