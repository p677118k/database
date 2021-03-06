#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDATA 1000000
typedef long ElementType;

void BubbleSort(ElementType Data[], int n)
{
	int i,j,temp;
	for (i = 0; i < n - 1; i++)
		for (j = n - 1; j > i; j--)
			if (Data[j - 1] > Data[j]) {
				temp = Data[j - 1];
				Data[j  - 1] = Data[j];
				Data[j] = temp;
			}
}

void SelectionSort(ElementType Data[], int n)
{
	int i,j;
	ElementType temp;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if (Data[i] > Data[j]) {
				temp = Data[i];
				Data[i] = Data[j];
				Data[j] = temp;
			}
}


void InsertionSort(ElementType Data[], int n)
{
	int i,j;
	ElementType temp;
	for (i = 1; i < n; i++) {
		temp = Data[i];
		for (j = i; j > 0 && Data[j-1] > temp; j--)
			Data[j] = Data[j - 1];
		Data[j] = temp;
	}
}

/* quick sort のための 関数群 FindPivot, Partition, QuickSort */
int FindPivot(ElementType Data[], int i, int j)
{
	int k=i+1;
	while(k<=j){
		if(Data[i]>Data[k])
			return i;
		if(Data[i]<Data[k])
			return k;
		k++;
	}
	return -1;
}

int Partition(ElementType Data[], int i, int j,int x){
	int l=i,r=j;
	while(l<=r){
		while(l<=j && Data[l]<x)
			l++;
		while(r>=i && Data[r]>=x)
			r--;
		if(l>r)
			break;
		int t=Data[l];
		Data[l]=Data[r];
		Data[r]=t;
		l++;
		r--;
	}
	return l;
}

void QuickSort(ElementType Data[], int i, int j){
	if(i==j)
		return;
	int p=FindPivot(Data,i,j);
	if(p!=-1){
		int k=Partition(Data,i,j,Data[p]);
		QuickSort(Data,i,k-1);
		QuickSort(Data,k,j);
	}
}

int comp(const void *a, const void *b)
{
	    return *(int*)a - *(int*)b;
}

void GenData(ElementType Data[], int n, int w)
	/* 配列 Data に n 個の乱数を発生させる。ただし、乱数の範囲は 0 ～ w - 1 */
{
	int i;
	for(i = 0; i < n; i++)
		Data[i] = random() % w;  /* あるいは、Data[i] = random() % w; */
}

void CopyData(ElementType d[], ElementType s[], int n)
	/* 配列 d から 配列 s に n 個のデータをコピーする */
	/* 同じ連数データをコピーして異なるアルゴリズムでソートするときに使う */
{
	int i;

	for(i = 0; i < n; i++)
		d[i] = s[i];
}

void PrintData(ElementType Data[], int n)
	/* ソートがきちんとできているか確認するデバックのために配列のデータを表示する */
{
	if(n > 20) return; /* データが多い時は表示しない */

	while(n--)
		printf("%4ld", *(Data++));
	printf("\n");
}

int main(int argc, char *argv[])
{
	//int i;
	int data_size = MAXDATA /* データ数 */, width = 100 /* 乱数の範囲（幅) */;
	ElementType *data, *d1, *d2, *d3, *d4, *d5;
	/* data: 乱数を入れる配列, d1, d2, d3, d4: ソートに渡す data のコピー用 */
	int s1,e1; /* clock の記録、初めと終わり。その差で計算時間になる */

	if(argc > 1) { /* argv[1] は、第１引数でデータ数　*/
		data_size = atoi(argv[1]); /* 数字列を数に変換 */
		fprintf(stderr, "data size = %d\n", data_size);
	}
	if(argc > 2) { /* argv[2] は、第2引数でデータ幅　*/
		width = atoi(argv[2]);
		fprintf(stderr, "width (range of data) = %d\n", width);
	}
	/* 配列 data, d1, d2, d3, d4 を動的に割り当てる */
	data = (ElementType *)malloc(sizeof(ElementType) * data_size);
	d1 = (ElementType *)malloc(sizeof(ElementType) * data_size);
	d2 = (ElementType *)malloc(sizeof(ElementType) * data_size);
	d3 = (ElementType *)malloc(sizeof(ElementType) * data_size);
	d4 = (ElementType *)malloc(sizeof(ElementType) * data_size);
	d5 = (ElementType *)malloc(sizeof(ElementType) * data_size);
	//randomize(); /* 乱数の初期化、呼び出すごとに異なる乱数発生 */
	/* あるいは、　srandom(time(NULL)); */
	srandom(time(NULL));
	GenData(data, data_size, width);
	PrintData(data, data_size);
	CopyData(d1, data, data_size);
	CopyData(d2, data, data_size);
	CopyData(d3, data, data_size);
	CopyData(d4, data, data_size);
	CopyData(d5, data, data_size);

	if(MAXDATA<=100000){
		printf("Bubble Sort\n");
		s1 = clock(); /* ソート実行前のシステム時間 */
		BubbleSort(d2, data_size);
		e1 = clock(); /* 実行後 */
		PrintData(d2, data_size);
		printf("CPU = %0.3lf\n", (double)(e1 - s1)/CLOCKS_PER_SEC);
		/* clock を CLOCKS_PER_SEC で割ると秒 */
		printf("Selection Sort\n");
		s1 = clock();
		SelectionSort(d3, data_size);
		e1 = clock();
		PrintData(d3, data_size);
		printf("CPU = %0.3lf\n", (double)(e1 - s1)/CLOCKS_PER_SEC);

		printf("Insertion Sort\n");
		s1 = clock();
		InsertionSort(d1, data_size);
		e1 = clock();
		PrintData(d1, data_size);
		printf("CPU = %0.3lf\n", (double)(e1 - s1)/CLOCKS_PER_SEC);
	}

	/* quicksort の呼び出し */
	printf("Quick Sort\n");
	s1 = clock();
	QuickSort(d4, 0, data_size - 1); // この引数に注意
	e1 = clock();
	PrintData(d4, data_size);
	printf("CPU = %0.3lf\n", (double)(e1 - s1)/CLOCKS_PER_SEC);

	/* qsort の呼び出し */
	printf("qsort\n");
	s1 = clock();
	qsort(d5, data_size, sizeof(ElementType), comp);
	e1 = clock();
	PrintData(d5, data_size);
	printf("CPU = %0.3lf\n", (double)(e1 - s1)/CLOCKS_PER_SEC);
	return 0;
}

/*
要素数を1000、10000、100000、1000000とした時の各ソートアルゴリズムの実行時間は以下のようになった。
Bubble Sort
　CPU = 0.007, 0.330, 32.808, -----
Selection Sort
　CPU = 0.005, 0.122, 11.812, -----
Insertion Sort
　CPU = 0.003, 0.078, 7.654, -----
Quick Sort
　CPU = 0.000, 0.001, 0.006, 0.057
qsort
　CPU = 0.000, 0.001, 0.012, 0.135

以上の結果より、実行時間は、クイックソート、挿入法、選択法、バブルソートの順に短くなっていると分かる。
各アルゴリズムの計算時間は、以下のようになっている。
バブルソート	O(n^2)
	選択法		O(n^2)
	挿入法		O(n^2)
	クイックソート	O(nlogn)

	クイックソート以外のアルゴリズムに関しては、いずれも同じO(n^2)となっているが、計算時間に差が生じる結果となっている。
	バブルソートと選択法では、共に比較回数は同じであるが、選択法の方がより少ない交換回数でソートを行うことが出来る。
	また、選択法と挿入法では、共に交換回数は同じであるが、挿入法の方がより少ない比較回数でソートを行うことが出来る。
	このことは、今回の測定で得られた結果からも明らかである。

	次に、自作した関数QuickSortとライブラリ関数qsortを比較すると、自作した関数の実行時間の方が短いと分かる。
	その要因としては、ライブラリ関数であるためライブラリの呼び出しに時間が掛かっていることが考えられる。
*/
