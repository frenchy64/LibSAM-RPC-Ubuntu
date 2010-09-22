/*
 * Please do not edit this file. It was generated using rpcgen.
 */

#include <sys/types.h>
#include <sys/time.h>
#include "samrpc.h"

#define xdr_uint_t xdr_u_int
#define xdr_ushort_t xdr_u_short

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = {25, 0};


sam_st *
samstat_1(
statcmd *argp,
CLIENT *clnt)
{
	static sam_st clnt_res;

	(void)memset(&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, samstat, (xdrproc_t)xdr_statcmd, (caddr_t)argp,
			  (xdrproc_t)xdr_sam_st, (caddr_t)&clnt_res,
			  TIMEOUT) != RPC_SUCCESS) {
	    return(NULL);
	}
	return(&clnt_res);
}


sam_st *
samlstat_1(
statcmd *argp,
CLIENT * clnt)
{
	static sam_st clnt_res;

	(void)memset(&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, samlstat, (xdrproc_t)xdr_statcmd, (caddr_t)argp,
		      (xdrproc_t)xdr_sam_st, (caddr_t)&clnt_res,
		      TIMEOUT) != RPC_SUCCESS) {
		return(NULL);
	}
	return(&clnt_res);
}


int *
samarchive_1(
filecmd * argp,
CLIENT * clnt)
{
	static int clnt_res;

	(void)memset(&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, samarchive, (xdrproc_t)xdr_filecmd, (caddr_t)argp,
		      (xdrproc_t)xdr_int, (caddr_t)&clnt_res,
		      TIMEOUT) != RPC_SUCCESS) {
		return(NULL);
	}
	return(&clnt_res);
}

int *
samsetfa_1(
filecmd * argp,
CLIENT * clnt)
{
	static int clnt_res;

	(void)memset(&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, samsetfa, (xdrproc_t)xdr_filecmd, (caddr_t)argp,
		      (xdrproc_t)xdr_int, (caddr_t)&clnt_res,
		      TIMEOUT) != RPC_SUCCESS) {
		return(NULL);
	}
	return(&clnt_res);
}

int *
samsegment_1(
filecmd * argp,
CLIENT * clnt)
{
	static int clnt_res;

	(void)memset(&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, samsegment, (xdrproc_t)xdr_filecmd, (caddr_t)argp,
		      (xdrproc_t)xdr_int, (caddr_t)&clnt_res,
		      TIMEOUT) != RPC_SUCCESS) {
		return(NULL);
	}
	return(&clnt_res);
}

int *
samrelease_1(
filecmd * argp,
CLIENT * clnt)
{
	static int clnt_res;

	(void)memset(&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, samrelease, (xdrproc_t)xdr_filecmd, (caddr_t)argp,
		      (xdrproc_t)xdr_int, (caddr_t)&clnt_res,
		      TIMEOUT) != RPC_SUCCESS) {
		return(NULL);
	}
	return(&clnt_res);
}

int *
samstage_1(
filecmd * argp,
CLIENT * clnt)
{
	static int clnt_res;

	(void)memset(&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call(clnt, samstage, (xdrproc_t)xdr_filecmd, (caddr_t)argp,
		      (xdrproc_t)xdr_int, (caddr_t)&clnt_res,
		      TIMEOUT) != RPC_SUCCESS) {
		return(NULL);
	}
	return(&clnt_res);
}
