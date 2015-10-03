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

void make_di(uchar *p,int d1[])
{
	int i, len=strlen(p);

	for(i=0; i<=255; i++)
		d1[i]=len;
	for(i=0; i<len-1; i++)
		d1[p[i]]=len-(i+1);
}

void BM(uchar *p, uchar *t, int d1[])
{
	int plen=strlen(p), tlen=strlen(t), i=plen-1, j, k;
	uchar lastch = p[i], ch;
	while(i<tlen) {
		ch=t[i];
		if(ch==lastch) {
			for(k=i-1, j=plen-2; j>=0 && t[k]==p[j]; k--, j--);
			if(j<0) {
				output(k+1);
			}
		}
		i+=d1[ch];
	}
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
	unsigned int file_size, st, et;
	int i;
	double t_na;
	int d1[255];

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


	st = clock();
	make_di(pat, d1);
	for(i=0; i<REPEAT; i++) {
		BM(pat, buff, d1);
	}
	et = clock();
	t_na = (double)(et - st)/CLOCKS_PER_SEC;
	printf("Hits = %d\n", hits / REPEAT);
	printf("CPU = %.6lf(sec), %.3lf(nano sec/char)\n",
			t_na, t_na * 1e9 / (REPEAT * file_size));
	printf("MATCHING SPEED = %.6lf(MB/sec)\n",
			file_size * REPEAT / t_na / 1e6);

	return 0;
}

/*
パターンの長さを短(１文字)、中(4文字)、長(7文字)、テキストの長さを短(724文字)、長(649190文字)として、Naive法とBM法の計算速度の比較を行った結果を以下に示す。
パターン短、テキスト短
・Naive法
	MATCHING SPEED = 149.232196(MB/sec)
・BM法
	MATCHING SPEED = 102.930096(MB/sec)

パターン中、テキスト短
・Naive法
	MATCHING SPEED = 138.207502(MB/sec)
・BM法
	MATCHING SPEED = 394.700976(MB/sec)

パターン長、テキスト短
・Naive法
	MATCHING SPEED = 130.681203(MB/sec)
・BM法
	MATCHING SPEED = 554.874310(MB/sec)

・パターン短、テキスト長
・Naive法
	MATCHING SPEED = 99.888782(MB/sec)
・BM法
	MATCHING SPEED = 35.315435(MB/sec)

パターン中、テキスト長
・Naive法
	MATCHING SPEED = 99.665017(MB/sec)
・BM法
	MATCHING SPEED = 121.603781(MB/sec)

パターン長、テキスト長
・Naive法
	MATCHING SPEED = 99.445650(MB/sec)
・BM法
	MATCHING SPEED = 199.024497(MB/sec)

*/
