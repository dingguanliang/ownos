####################################################
#
#	This is a rules file for generation depend file.
#
####################################################

.depend: $(SRCTREE)/config.mk $(SRCS)
	@for f in $(SRCS); \
	do \
		g=`basename $$f | sed -e 's/\(.*\)\.\w/\1.o/'`; \
		$(CC) -M $(CPPFLAGS) -MQ $$g $$f >> $@; \
	done
	@echo generate depend file!

####################################################
