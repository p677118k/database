#include <stdio.h>
#include <string.h> /* strlen を使うため */
#include <time.h>   /* clock を使うため */
#define BUFF_SIZE 10000000
#ifndef REPEAT
#define REPEAT 10000
#endif

typedef unsigned char uchar;

uchar buff[BUFF_SIZE];

int hits = 0;

void output(int i)
{
	hits++; /* 実行時間を計るので、表示しないで単に回数をカウント */
}

/* read entire file to buffer, and return file size */
int read_file(uchar *buff)
{
	int i, c;

	for(i = 0; i < BUFF_SIZE - 1; i++) {
		c = getchar();
		if(c == EOF) break;
		buff[i] = c;
	}
	buff[i] = 0; /* null char */
	return i;
}

void match(uchar *p, uchar *t, int tlen)
	/* テキストの長さを strlen で求めると時間がかかるので、引数で渡すように変更 */
	/* パターンは短いのでそのまま */
{
	int i, j, plen = strlen(p), found;

	for(i = 0; i < tlen - plen + 1; i++) {
		found = 1;
		for(j = 0; j < plen; j++)
			if(p[j] != t[i + j]) {
				found = 0;
				break;
			}
		if(found)
			output(i);
	}
}

int main(int argc, uchar *argv[])
{
	uchar *pat;
	int file_size, st, et;
	int i;
	double t_na;

	if(argc != 2) {
		fprintf(stderr, "usage> search pattern\n");
		return 1;
	}
	file_size = read_file(buff);
	printf("file size = %d\n", file_size);
	printf("repeat = %d\n", REPEAT);
	pat = argv[1];

	st = clock();
	for(i = 0; i < REPEAT; i++)
		match(pat, buff, file_size);
	et = clock();
	t_na = (double)(et - st)/CLOCKS_PER_SEC;
	printf("Hits = %d\n", hits / REPEAT);
	printf("CPU = %.6lf(sec), %.3lf(nano sec/char)\n", 
			t_na, t_na * 1e9 / (REPEAT * file_size));
	printf("MATCHING SPEED = %.6lf(MB/sec)\n", 
			file_size * REPEAT / t_na / 1e6);

	return 0;
}
