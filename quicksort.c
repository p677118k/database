#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef long ElementType;

void PrintData(ElementType Data[], int n)
/* ソートがきちんとできているか確認するデバックのために配列のデータを表示する */
{
	if(n > 20) return; /* データが多い時は表示しない */

	while(n--)
		printf("%4d", *(Data++));
	printf("\n");
}

int FindPivot(ElementType Data[], int i, int j)
{
	int k=i+1;
	while(k<=j && Data[i]==Data[k])
		k++;
	if(k>j)
		return -1;
	if(Data[i]>=Data[k])
		return i;
	return k;
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
		l++; r--;
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

int main(void)
{
	ElementType a[5];
	a[0]=2;
	a[1]=3;
	a[2]=1;
	a[3]=5;
	a[4]=4;
	PrintData(a,5);
	QuickSort(a,0,4);
	PrintData(a,5);
	return 0;
}
