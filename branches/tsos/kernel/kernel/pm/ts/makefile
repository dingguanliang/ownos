####################################################

include $(SRCTREE)/rules.mk
include $(SRCTREE)/config.mk

####################################################

LIB		= lib.a

SRCS 	:= $(wildcard *.S *.c)
OBJS 	:= $(addsuffix .o, $(basename $(SRCS)))

####################################################

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)
	
sinclude .depend

####################################################
