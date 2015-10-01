#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 10000  /* 最大データ数 */

typedef long ElementType;


void BubbleSort(ElementType Data[], int n)
{
	int i,j;
	ElementType temp;

	for (i = 0; i < n-1; i++) {
		for (j = n-1; j > i; j--) {
			if (Data[j-1] > Data[j]) {
				temp = Data[j-1];
				Data[j-1] = Data[j];
				Data[j] = temp;
			}
		}
	}
}


void SelectionSort(ElementType Data[], int n)
{
	int i,j;
	ElementType temp;

	for (i = 0; i < n-1; i++) {
		for (j = i+1; j < n; j++) {
			if (Data[i] > Data[j]) {
				temp = Data[i];
				Data[i] = Data[j];
				Data[j] = temp;
			}
		}
	}
}


void InsertionSort(ElementType Data[], int n)
{
	int i,j;
	ElementType temp;

	for (i = 1; i < n; i++) {
		temp = Data[i];
		for (j = i; j > 0 && Data[j-1] > temp; j--) {
			Data[j] = Data[j-1];
		}
		Data[j] = temp;
	}
}


int FindPivot(ElementType Data[], int i, int j)
{
	int k;

	for(k=i+1; k<=j; k++){
		if(Data[i] < Data[k])
			return k;
		else if(Data[i] > Data[k])
			return i;
	}
	return -1;
}


int Partition(ElementType Data[], int i, int j, ElementType Pivot)
{

	int L, R;
	ElementType temp;

	L = i;
	R = j;

	do {

		while(Data[L] < Pivot) L++;
		while(Data[R] >= Pivot) R--;

		if (L < R) {
			temp = Data[L];
			Data[L] = Data[R];
			Data[R] = temp;
		}
	} while (L < R);

	return L;
}


void QuickSort(ElementType Data[], int i, int j)
{
	int pivotindex, k;

	pivotindex = FindPivot(Data, i, j);

	if (pivotindex >= 0) {
		k = Partition(Data, i, j, Data[pivotindex]);
		QuickSort(Data, i, k-1);
		QuickSort(Data, k, j);
	}
}


void GenData(ElementType Data[], int n, int w)
	/* 配列 Data に n 個の乱数を発生させる。ただし、乱数の範囲は 0 ～ w - 1 */
{
	int i;
	for(i = 0; i < n; i++)
		Data[i] = random(w);  /* あるいは、Data[i] = random() % w; */
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
		printf("%4d", *(Data++));
	printf("\n");
}


int main(int argc, char *argv[])
{
	int i;
	int data_size = 10000 /* データ数 */, width = 100 /* 乱数の範囲（幅) */;
	ElementType *data, *d1, *d2, *d3, *d4;
	/* data: 乱数を入れる配列, d1, d2, d3, d4: ソートに渡す data のコピー用 */
	int s1,e1; /* clock の記録、始めと終わり。その差で計算時間になる */
	int s2=0,e2=0; //BubbleSortのclockの記録(s2:始め，e2:終わり)の合計
	int s3=0,e3=0; //SelectionSortのclockの記録(s3:始め，e3:終わり)の合計
	int s4=0,e4=0; //InsertionSortのclockの記録(s4:始め，e4:終わり)の合計
	int s5=0,e5=0; //QucikSortのclockの記録(s5:始め，e5:終わり)の合計
	int cnt=0;	//カウント数

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

	while(cnt<10){

		if(data_size >= 100000) break;

		random(time(NULL));

		GenData(data, data_size, width);
		CopyData(d2, data, data_size);
		//PrintData(d2, data_size);

		printf("Bubble Sort\n");
		s1 = clock(); /* ソート実行前のシステム時間 */
		BubbleSort(d2, data_size);
		e1 = clock(); /* 実行後 */
		PrintData(d2, data_size);

		s2 += s1;
		e2 += e1;
		cnt++;
	}

	/* selectionsort の呼び出し */

	cnt = 0;
	while(cnt<10){

		if(data_size >= 100000) break;

		random(time(NULL));

		GenData(data, data_size, width);
		CopyData(d3, data, data_size);
		//PrintData(d3, data_size);

		printf("Selection Sort\n");
		s1 = clock();
		SelectionSort(d3, data_size);
		e1 = clock();
		PrintData(d3, data_size);

		s3 += s1;
		e3 += e1;
		cnt++;
	}

	/* insertinsort の呼び出し */

	cnt =0;
	while(cnt<10){

		if(data_size >= 100000) break;

		random(time(NULL));

		GenData(data, data_size, width);
		CopyData(d1, data, data_size);
		//PrintData(d1, data_size);

		printf("Insertion Sort\n");
		s1 = clock();
		InsertionSort(d1, data_size);
		e1 = clock();
		PrintData(d1, data_size);

		s4 += s1;
		e4 += e1;
		cnt++;
	}

	/* quicksort の呼び出し */

	cnt =0;
	while(cnt<10){

		random(time(NULL));

		GenData(data, data_size, width);
		CopyData(d4, data, data_size);
		//PrintData(d4, data_size);

		printf("Quick Sort\n");
		s1 = clock();
		QuickSort(d4, 0, data_size - 1);
		e1 = clock();
		PrintData(d4, data_size);

		s5 += s1;
		e5 += e1;
		cnt++;
	}


	/*各ソートの計算時間*/

	printf("Bubble CPU = %0.3lf\n", (double)(e2 - s2)/(CLOCKS_PER_SEC * 10));
	printf("Selection CPU = %0.3lf\n", (double)(e3 - s3)/(CLOCKS_PER_SEC * 10));
	printf("Insertion CPU = %0.3lf\n", (double)(e4 - s4)/(CLOCKS_PER_SEC * 10));
	printf("Quick CPU = %0.3lf\n", (double)(e5 - s5)/(CLOCKS_PER_SEC * 10));
	/* clock を CLOCKS_PER_SEC で割ると秒 */
	return 0;
}

/*　実行結果

  各ソートのデータ数＼乱数の範囲を変化させたときの値を以下の表に示す．

  データ数＼乱数の範囲|	   100		|     10000
  -----------------------------------------------------
  |Bubble:0		|Bubble:0
  1000		|Selection:0.002|Selection:0.002
  |Insertion:0.002|Insertion:0.002
  |Quick:0		|Quick:0
  -----------------------------------------------------
  |Bubble:0.159	|Bubble:0.159
  10000		|Selection:0.037|Selection:0.169
  |Insertion:0.022|Insertion:0.022
  |Quick:0		|Quick:0.002
  -----------------------------------------------------
  |Bubble:15.653	|Bubble:15.669
  100000		|Selection:3.073|Selection:8.435
  |Insertion:2.154|Insertion:2.192
  |Quick:0.005	|Quick:0.006
  -----------------------------------------------------
  |Bubble:*		|Bubble:*
  1000000		|Selection:*	|Selection:*
  |Insertion:*	|Insertion:*
  |Quick:0.03		|Quick:0.059
  -----------------------------------------------------
  (*:省略)

  　表より，Bubbleソートではデータ数が増加する度に計算時間も増加している．
  しかし，乱数の範囲を変化させても計算時間の変化は見られなかった．
  　次に，Selectinソートではデータ数が増加する度に計算時間も増加しているが，
  Bubbleソートよりは速い．
  しかし，乱数の範囲を広くすると同じデータ数でも計算時間が増加していることがわかる．
  　次に，Insertionソートではデータ数が増加する度に計算時間も増加しているが，
  素朴なソート法の中では一番速い．
  また，Bubbleソートと同様に乱数の範囲を変化させても計算時間の変化は見られなかった．
  　最後に，Quickソートではデータ数が増加する度に計算時間も増加はしているが，
  素朴なソートに比べて，圧倒的に計算時間が速いことがわかる．
  また，乱数の範囲が狭いときはあまり変化は見られなかったが，広くなると同じデータ数でも
  計算時間が遅くなっていることがわかる．

  以上の結果から，Quick > Insertion > Selection > Bubbleの関係で高速にソートできた．
  また，Bubble・Insertionソートはばらつきに影響されなく，Selection・Quickソートは
  ばらつきに影響されることがわかる．

 */
