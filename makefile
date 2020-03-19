#-*-makefile-*-

TARGETS = \
    visual

all All: $(TARGETS)

################################################################################
INCPATH = -I/usr/local/include
LIBPATH = -L. -L/lib/x86_64-linux-gnu
LIBS = -lglut -lGLU -lGL -lGLw -lXt -lXext -lX11 -ljpeg -lm 
DEBUGFLAGS = -O3
CFLAGS = -DD32 $(DEBUGFLAGS) $(INCPATH)
SRCS = \
	visual.c 

OBJS = $(SRCS:.c=.o)

.SUFFIXES:	.c

.c.o:	
	cc -c $< $(CFLAGS)


visual:  clean $(OBJS)
	LDOPTS= \
	cc -o visual $(CFLAGS) $(OBJS) $(LIBPATH) $(LIBS) 

clean:
	rm -f visual $(OBJS) core

print:
	listing visual.c $(SRCS)
