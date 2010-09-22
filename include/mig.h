/* mig.h - Migration Toolkit 
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
 * $Id: mig.h,v 1.11 2007/01/08 21:45:41 jdunn Exp $
 */

#ifdef sun
#pragma ident "$Id: mig.h,v 1.11 2007/01/08 21:45:41 jdunn Exp $"
#endif

#ifndef _SAM_MIG_H
#define _SAM_MIG_H

#include <sys/types.h>
#include <sys/stat.h>
#include "stat.h"

#ifdef  __cplusplus
extern "C" {
#endif

#if !defined(_SAM_TYPES_H)
typedef unsigned short media_t;
typedef unsigned short equ_t;
typedef char  vsn_t[32];
#endif /* !defined _SAM_TYPES_H */

/* Media type is made up of the constant 0x8000 inclusively or'ed with
 * the ascii bit representation of the second character of the
 * acsii media type.  If the acsii media type is "za", then the
 * internal media type is 0x8041.  If its "z5", then the internal
 * media type is 0x8035. */

typedef struct {
  offset_t    offset;                   /* offset from beginning of file */
  offset_t    size;                     /* size of file to stage in */
  long long   position;                 /* position from meta data */
  ino_t       inode;                    /* file system inode number */
  vsn_t       vsn;                      /* vsn from meta data */
  equ_t       fseq;                     /* sam-fs file system equment numner */
  media_t     media_type;               /* sam-fs internal media type */
  void        *tp_data;                 /* generic pointer for tp use */
}tp_stage_t;

#if !defined (_AML_DEVICE_H)
#define DT_THIRD_PARTY  0x8000
#define IS_THIRD_PARTY (t) ((t & 0xFF00) == DT_THIRD_PARTY)
#endif /* !defined _AML_DEVICE_H */


/* Function prototypes */

/* The following are functions that must be provided by the third party
 * developer. */
int usam_mig_initialize(int);
int usam_mig_stage_file_req(tp_stage_t *);  
int usam_mig_cancel_stage_req(tp_stage_t *);

/* The following functions are provided by the SAM-FS third party
 * interface. */
int sam_mig_stage_error (tp_stage_t *, int);
int sam_mig_stage_file (tp_stage_t *);
int sam_mig_stage_write (tp_stage_t *, char *, int, offset_t);
int sam_mig_stage_end (tp_stage_t *, int);
char *sam_mig_mount_media(char *, char *);
int sam_mig_release_device(char *);
int sam_mig_open_device(const char *, int);
int sam_mig_close_device(int);

/* The following functions are used to build the name space for the
 * third party files. */
int sam_mig_create_file (char *, struct sam_stat *);

/* The following functions are used to set the rearchive flag
 */
int sam_mig_rearchive (char *, char **, char *);

#ifdef  __cplusplus
}
#endif

#endif  /* _SAM_MIG_H */
