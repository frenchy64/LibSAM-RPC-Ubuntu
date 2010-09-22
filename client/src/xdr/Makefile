SRCS = sam_xdr.c

INCLUDE = /opt/SUNWsamfs/include
CFLAGS = -I${INCLUDE}

WHOAMI = sam_xdr.o

OBJS = ${SRCS:.c=.o}

all: ${WHOAMI}

${WHOAMI}: ${SRCS}
	rm -f ${WHOAMI}
	${CC} ${CFLAGS} -c  -o sam_xdr.o ${SRCS}

clean:
	@-rm -f ${WHOAMI} ${OBJS} *~ *.bak
