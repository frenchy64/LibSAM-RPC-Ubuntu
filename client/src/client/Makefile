SRCS = samrpc.c samfs_clnt.c sam_attrtoa.c

INCLUDE = /opt/SUNWsamfs/include
CFLAGS = -I${INCLUDE}

LIBOBJS = ${SRCS:.c=.o} ../xdr/sam_xdr.o

all: libsamrpc.a .WAIT libsamrpc.so

libsamrpc.a: ${LIBOBJS}
	@ar ruc libsamrpc.a ${LIBOBJS}

libsamrpc.so: ${LIBOBJS}
	@${CC} -G -o libsamrpc.so ${LIBOBJS}

clean:
	@-rm -f *.o *.a *.so *~ *.bak *.ln
