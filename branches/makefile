####################################################

OBJTREE	:= $(CURDIR)
SRCTREE	:= $(CURDIR)
export	OBJTREE SRCTREE

include	$(SRCTREE)/config.mk

####################################################

LIBS_RT	:= bootload/arch/lib.a
LIBS_RT	+= rtos/usr/app/lib.a
LIBS_RT	+= rtos/kernel/kernel/core/lib.a
LIBS_RT	+= rtos/kernel/kernel/pm/ts/lib.a
LIBS_RT	+= rtos/kernel/kernel/tm/lib.a
LIBS_RT	+= rtos/kernel/kernel/debug/lib.a
LIBS_RT	+= rtos/kernel/kernel/lib/lib.a
LIBS_RT	+= rtos/kernel/bsp/arch/lib.a
LIBS_RT	+= rtos/kernel/bsp/driver/lib.a

LIBS_TS	:= bootload/arch/lib.a
LIBS_TS	+= tsos/usr/app/lib.a
LIBS_TS	+= tsos/kernel/kernel/core/lib.a
LIBS_TS	+= tsos/kernel/kernel/pm/ts/lib.a
LIBS_TS	+= tsos/kernel/kernel/tm/lib.a
LIBS_TS	+= tsos/kernel/kernel/debug/lib.a
LIBS_TS	+= tsos/kernel/kernel/lib/lib.a
LIBS_TS	+= tsos/kernel/bsp/arch/lib.a
LIBS_TS	+= tsos/kernel/bsp/driver/lib.a

LIBS = $(LIBS_TS)

CDIR	:= $(dir $(LIBS))

####################################################

.PHONY: all
all: clean firmware.bin clean_dep

firmware.bin: firmware.elf
	$(OBJCOPY) $(OBJCFLAGS) -O binary $< $@

firmware.elf: mklibs
	$(LD) $(LDFLAGS) -o $@ $(LIBS)

.PHONY: mklibs
mklibs: 
	@for n in $(CDIR); \
	do \
		$(MAKE) -C $$n; \
	done

####################################################

.PHONY: clean_dep
clean_dep:
	@find -type f \( -name '.depend' \) -print | xargs rm -f
	@echo clear depend file complete!

####################################################

.PHONY: clean
clean:
	@find -type f \( -name '*.map' -o -name '*.asm' -o -name '*.elf' -o -name '*.bin' -o -name '*.o' -o -name '*.a' -o -name '.depend' \) -print | xargs rm -f
	@echo clear complete!

####################################################

.PHONY: disasm
disasm: all firmware.asm

firmware.asm:
	$(OBJDUMP) -D -b binary -m arm firmware.bin >> $@

####################################################
