/*
 * listio.h - QFS listio definitions.
 *
 * Defines the QFS listio input structure and functions.
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
 * $Id: listio.h,v 1.5 2007/01/08 21:45:41 jdunn Exp $
 */

#ifdef sun
#pragma ident "$Id: listio.h,v 1.5 2007/01/08 21:45:41 jdunn Exp $"
#endif


#ifndef	QFS_LISTIO_H
#define	QFS_LISTIO_H

#include <sys/types.h>

#ifdef  __cplusplus
extern "C" {
#endif


typedef int64_t qfs_lio_handle_t;
int qfs_lio_init(qfs_lio_handle_t *hdl);
int qfs_lio_write(int fd,
                  int mem_list_count, void **mem_addr, size_t *mem_count,
                  int file_list_count, offset_t *file_off, offset_t *file_len,
                  qfs_lio_handle_t *hdl);
int qfs_lio_read (int fd,
                  int mem_list_count, void **mem_addr, size_t *mem_count,
                  int file_list_count, offset_t *file_off, offset_t *file_len,
                  qfs_lio_handle_t *hdl);
int qfs_lio_wait(qfs_lio_handle_t *hdl);

#ifdef  __cplusplus
}
#endif

#endif /* _QFS_LISTIO_H */
