#include <stdio.h>
#define MEM_SZ 1024

#define HEAD *mem[0]

char in_buf[64];
char mem[MEM_SZ];


//pi
void __xxd(char* base, int start, int num) {
	char* ptr = base + start;
	for (int i=0; i<num; i++) {
		if (i % 16 == 0)
			printf("%08x: ", i);
		if (i % 2)
			printf("%02x ", ptr[i]);
		else
			printf("%02X", ptr[i]);
		if (i % 16 == 15)
			printf("\n");
	}
}

void xxd(char* base, int len, int offset) {
	char line_buf[17];
	for (line_pos = offset; line_pos+offset

}

int main() {
#ifdef DBG
	for (int i=0; i<MEM_SZ; i++) {
		mem[i] = 'A';
	}
#endif
	xxd(mem, 0, 32);
}
