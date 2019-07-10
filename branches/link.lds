/*
 *	This is a link script for project.
*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
	. = 0x31000000;

	__code_start = .;
	__text_start = .;
	. = ALIGN(4);
	.text :
	{
		bootload/arch/start.o(.text)
		*(.text)
	}

	. = ALIGN(4);
	.rodata : 
	{ 
		*(.rodata) 
	}

	. = ALIGN(4);
	.data : 
	{ 
		*(.data) 
	}
	. = ALIGN(4);
	__text_end = .;

	. = ALIGN(4);
	__bss_start = .;
	.bss : 
	{ 
		*(.bss) 
	}
	__bss_end = .;
	__code_end = .;
}
