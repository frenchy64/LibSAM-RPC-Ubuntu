/*
 * samrpc.c - RPC library calls for SamFS clients
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
static char rcs_id[] = "@(#)$Id: samrpc.c,v 1.10 2007/01/08 21:49:24 jdunn Exp $";
#endif /* lint */
#pragma ident "$Id: samrpc.c,v 1.10 2007/01/08 21:49:24 jdunn Exp $"

#define SAM_LIB 1

//#include <rpc/rpcent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "stat.h"
#include "samrpc.h"


/* Global data */
CLIENT *clnt;

static char sampath[PATH_MAX];
static int samlocal = 0;

char *
sam_filename(
char *fn)
{
	char *p;

	/* If it's already a complete path, keep it. */
	if (fn[0] == '/') return(fn);
	if (fn[0] == '\0') return(NULL);

	if (samlocal) {
		/*
		 * Construct a complete path relative to the current working
		 * directory.
		 */
		if ((fn[0] == '~') || (fn[0] == '$')) {
			return(NULL);
		}
		if ((p = getcwd(sampath, PATH_MAX)) == NULL) {
			return(NULL);
		}
		p = strcat(sampath, "/");
		p = strcat(sampath, fn);
		return(sampath);
	}
	else {
		return(NULL);
	}
}

/*
 * Initialize the RPC connection.
 */

int
sam_initrpc(
char *rpchost)
{
	struct rpcent *rpce;
	char *hostname;

	/* Get rpcent for program number */
	rpce = getrpcbyname(PROGNAME);
	if (!rpce) {
		/* Try getting the rpcent using the default program number */
		rpce = getrpcbynumber(SamFS);
		if ((!rpce) || (strcmp(PROGNAME, rpce->r_name))) {
			errno = EADDRNOTAVAIL;
			return(-1);
		}
	}
	/* Get name of sam host */
	if (rpchost) {
		hostname = rpchost;
	} else {
		if (!(hostname = getenv("SAMHOST"))) {
			hostname = SAMRPC_HOST;
		}
	}
	if (!strcmp(hostname, "localhost")) {
		samlocal = 1;
	}

	clnt = clnt_create(hostname, (u_long)rpce->r_number, SAMVERS,
			"netpath");
	if (clnt == (CLIENT *)NULL) {
		clnt_pcreateerror(hostname);
		return(-1);
	}
	auth_destroy(clnt->cl_auth);
	clnt->cl_auth = authunix_create_default();
	return(0);
}


/*
 * Archive the file and/or set archive attributes.
 */

int
sam_archive(
char *filename,
char *options)
{
	filecmd samarchive_arg;
	int *result;

	if (clnt == (CLIENT *)NULL) {
		errno = EDESTADDRREQ;
		return(-1);
	}
	samarchive_arg.filename = sam_filename(filename);
	if (samarchive_arg.filename == NULL) {
		errno = EINVAL;
		return(-1);
	}
	samarchive_arg.options = options;
	result = samarchive_1(&samarchive_arg, clnt);
	if (result == (int *)NULL) {
		clnt_perror(clnt, "sam_archive failed");
		return(-1);
	}
	return(0);

}


/*
 * Set attributes on a file or directory
 */

int
sam_setfa(
char *filename,
char *options)
{
	filecmd samsetfa_arg;
	int *result;

	if (clnt == (CLIENT *)NULL) {
		errno = EDESTADDRREQ;
		return(-1);
	}
	samsetfa_arg.filename = sam_filename(filename);
	if (samsetfa_arg.filename == NULL) {
		errno = EINVAL;
		return(-1);
	}
	samsetfa_arg.options = options;
	result = samsetfa_1(&samsetfa_arg, clnt);
	if (result == (int *)NULL) {
		clnt_perror(clnt, "sam_setfa failed");
		return(-1);
	}
	if (*result) {
		errno = *result;
		return(-1);
	} else {
		return(0);
	}

}


/*
 * Set segment attributes on a file or directory
 */

int
sam_segment(
char *filename,
char *options)
{
	filecmd samsegment_arg;
	int *result;

	if (clnt == (CLIENT *)NULL) {
		errno = EDESTADDRREQ;
		return(-1);
	}
	samsegment_arg.filename = sam_filename(filename);
	if (samsegment_arg.filename == NULL) {
		errno = EINVAL;
		return(-1);
	}
	samsegment_arg.options = options;
	result = samsegment_1(&samsegment_arg, clnt);
	if (result == (int *)NULL) {
		clnt_perror(clnt, "sam_segment failed");
		return(-1);
	}
	if (*result) {
		errno = *result;
		return(-1);
	} else {
		return(0);
	}

}


/*
 * Release disk space and/or set release attributes.
 */

int
sam_release(
char *filename,
char *options)
{
	filecmd samrelease_arg;
	int *result;

	if (clnt == (CLIENT *)NULL) {
		errno = EDESTADDRREQ;
		return(-1);
	}
	samrelease_arg.filename = sam_filename(filename);
	if (samrelease_arg.filename == NULL) {
		errno = EINVAL;
		return(-1);
	}
	samrelease_arg.options = options;
	result = samrelease_1(&samrelease_arg, clnt);
	if (result == (int *)NULL) {
		clnt_perror(clnt, "sam_release failed");
		return(-1);
	}
	if (*result) {
		errno = *result;
		return(-1);
	} else {
		return(0);
	}
}


/*
 * Copy the off-line file to disk and/or set staging attributes.
 */

int
sam_stage(
char *filename,
char *options)
{
	filecmd samstage_arg;
	int *result;

	if (clnt == (CLIENT *)NULL) {
		errno = EDESTADDRREQ;
		return(-1);
	}
	samstage_arg.filename = sam_filename(filename);
	if (samstage_arg.filename == NULL) {
		errno = EINVAL;
		return(-1);
	}
	samstage_arg.options = options;
	result = samstage_1(&samstage_arg, clnt);
	if (result == (int *)NULL) {
		clnt_perror(clnt, "sam_stage failed");
		return(-1);
	}
	if (*result) {
		errno = *result;
		return(-1);
	} else {
		return(0);
	}
}


/*
 * Obtain file attributes about the file.
 * Read, write or execute permission of the named file is not required,
 * but all directories in the path name must be searchable.
 */

int
sam_stat(
const char *filename,
struct sam_stat *statbuf,
size_t bufsize)
{
	sam_st *result_1;
	statcmd samstat_1_arg;
	int size;

	if (clnt == (CLIENT *)NULL) {
		errno = EDESTADDRREQ;
		return(-1);
	}
	samstat_1_arg.filename = sam_filename((char *)filename);
	if (samstat_1_arg.filename == NULL) {
		errno = EINVAL;
		return(-1);
	}
	samstat_1_arg.size = bufsize;
	result_1 = samstat_1(&samstat_1_arg, clnt);
	if (result_1 == (sam_st *)NULL) {
		clnt_perror(clnt, "sam_stat failed");
		return(-1);
	}
	if (result_1->result) {
		errno = result_1->result;
		return(-1);
	}
	/*
	 * Copy the stat structure returned to the user's specified location.
	 */
	size = (bufsize <= sizeof(struct sam_stat)) ?
		bufsize : sizeof(struct sam_stat);
	(void)memcpy(statbuf, &result_1->s, size);
	return(0);
}


/*
 * Obtain file attributes similar to sam_stat, except when the named file
 * is a symbolic link.  In this case, sam_lstat returns information about
 * the link.
 */

int
sam_lstat(
const char *filename,
struct sam_stat *statbuf,
size_t bufsize)
{
	sam_st *result_1;
	statcmd samlstat_1_arg;
	int size;

	if (clnt == (CLIENT *)NULL) {
		errno = EDESTADDRREQ;
		return(-1);
	}
	samlstat_1_arg.filename = sam_filename((char *)filename);
	if (samlstat_1_arg.filename == NULL) {
		errno = EINVAL;
		return(-1);
	}
	samlstat_1_arg.size = bufsize;
	result_1 = samlstat_1(&samlstat_1_arg, clnt);
	if (result_1 == (sam_st *)NULL) {
		clnt_perror(clnt, "sam_lstat failed");
		return(-1);
	}
	if (result_1->result) {
		errno = result_1->result;
		return(-1);
	}
	/*
	 * Copy the stat structure returned to the user's specified location.
	 */
	size = (bufsize <= sizeof(struct sam_stat)) ?
		bufsize : sizeof(struct sam_stat);
	(void)memcpy(statbuf, &result_1->s, sizeof(struct sam_stat));
	return(0);
}


/*
 * Close the rpc connection.
 */

int
sam_closerpc()
{
	if (clnt == (CLIENT *)NULL) {
		return(0);
	}
	auth_destroy(clnt->cl_auth);
	clnt_destroy(clnt);
	return(0);
}
