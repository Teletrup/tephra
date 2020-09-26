#include <stdio.h>
#include "colors.h"
#include "opcodes.h"
#include "mem.h"


char* getByteForm(int addr, char val) {
	if (addr == PC_ADDR || addr == PC_ADDR + 1)
		return FG_RED BG_BLACK BYTE_FORM COLOR_RESET;
	if (addr == PC_VAL || addr == PC_VAL + 1)
		return FG_BLACK BG_RED BYTE_FORM COLOR_RESET;
	if (addr >= IN_BUF)
		return FG_MAGENTA BG_BLACK BYTE_FORM COLOR_RESET;
	//TODO coloring instructions
	return BYTE_FORM;
	//Should it output reset after every byte?
	//Should I even benchmark it?
}

void xxd(unsigned char* base, int len, int offset, char* (*ffun) (int, char)) {
	char ascii_buf[17];
	int limit = len + offset;
	for (int i=offset; i<limit; i+=16) {
		printf("%08X: ", i);
		int line_len = MIN(16, limit - i);
		ascii_buf[line_len] = 0;
		int j;
		for (j=0; j<line_len; j++) {
			unsigned char chr = base[i + j];
			printf(ffun(i + j, chr), chr);
			if (j % 2)
				putchar(' ');
			if (chr >= ' ' && chr <= '~')
				ascii_buf[j] = chr;
			else
				ascii_buf[j] = '.';
		}
		int padding_len = (16 - line_len) * 2 + (16 - line_len + 1) / 2 + 1;
		char padding_buf[40];
		padding_buf[padding_len] = 0;
		for (int i=0; i<padding_len; i++)
			padding_buf[i] = ' ';
		printf("%s%s", ascii_buf, padding_buf);
		putchar('\n');
	}
}

int main() {
	PC_VAL = 257;
	while (1) {
		printf(CLEAR);
		xxd(mem_g, MEM_SZ, 0, getByteForm);
		printf("\n");
		fgets(mem_g + IN_BUF, IN_BUF_SZ, stdin);
		PC_VAL++;
	}
}
