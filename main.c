#include <stdio.h>

#define MEM_SZ 512
#define IN_BUF_SZ 64

#define HEAD mem[0]
#define IN_BUF mem + MEM_SZ - IN_BUF_SZ

#define MIN(a, b) (a) < (b) ? (a) : (b)


char in_buf[64];
unsigned char mem[MEM_SZ];


void xxd(unsigned char* base, int len, int offset) {
	char ascii_buf[17];
	int max_addr = len + offset;
	for (int i=offset; i<max_addr; i+=16) {
		printf("%08X: ", i);
		int line_len = MIN(16, max_addr - i); //ob1?
		ascii_buf[line_len] = 0;
		int j;
		for (j=0; j<line_len; j++) {
			unsigned char chr = base[i + j];
			printf("%02X", chr);
			if (j % 2)
				putchar(' ');
			if (chr >= ' ' && chr <= '~')
				ascii_buf[j] = chr;
			else
				ascii_buf[j] = '.';
		}
		int padding_len = (16 - line_len) * 2 + (16 - line_len + 1) / 2 + 1; //+1?
		char padding_buf[39];
		padding_buf[padding_len] = 0;
		for (int i=0; i<padding_len; i++)
			padding_buf[i] = ' ';
		printf(padding_buf);
		printf(ascii_buf);
		putchar('\n');
	}
}

int main() {
#ifdef DBG
	for (int i=0; i<MEM_SZ; i++) {
		mem[i] = 'A';
	}
#endif
	HEAD = 128;
	while (1) {
		xxd(mem, MEM_SZ, 0);
		fgets(IN_BUF, IN_BUF_SZ, stdin);
	}
}
