#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#undef RAND_MAX
#define RAND_MAX 255

unsigned char checksum(unsigned char p1, unsigned char p2,unsigned char p3) {
	unsigned char checksum = ((21 * p1 * p1) + (19*p2) - (3 * p3)) % 255;
	return checksum;
}

void change_color(int color) {
	unsigned char command[64];

	memset(&command, 0xff, 64);

	command[0] = 0x11;
	command[1] = (unsigned char) color;
	command[3] = 0x55; //(unsigned char) rand();
	command[2] = checksum(command[0], command[1], command[3]);

	FILE* fd;
	fd = fopen("/dev/hidraw0", "wb");
	if(fd == NULL) { printf("error %d\n", errno); }
	fwrite(&command, sizeof(unsigned char), 64, fd);

	fclose(fd);
}

int main(int argc, char *argv[]) {

	int color = atoi(argv[1]);

	change_color(color);
	return 0;
}
