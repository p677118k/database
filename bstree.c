#include <stdio.h>
#include <stdlib.h> 

/* 自己参照構造体（再帰的データ構造） によるノード，木の定義 */
/* ノード（node 型): データと左の子，右の子からなる構造体 */
/* 木（bs_tree 型): 根ノードを指すポインタ */

typedef struct _node {
	int key; /* ノードのデータは整数（int） */
	struct _node *leftchild, *rightchild;
} node, *bs_tree; 

/*　新しいノードを動的に割り当てる */

node *new_node(void) 
{
	return (node *)malloc(sizeof(node));
}

/* 2分探索木 t から データ k をもつノードを探す． */
/* 見つかったらそのノードを指すポインタを返す． */
/* 失敗したら NULL を返す. */

node *search(int k, bs_tree t)
{
	if(t == NULL)
		return NULL;
	else if(k == t->key)
		return t;
	else if(k < t->key)
		return search(k, t->leftchild);
	else
		return search(k, t->rightchild);
}

/* 2分探索木 t にデータ k を挿入する． */

node *insert(int k, bs_tree t)
{
	if(t == NULL) {
		t = new_node();
		t->key = k; t->leftchild = t->rightchild = NULL;
	} else if(k < t->key)
		t->leftchild = insert(k, t->leftchild);
	else if(k > t->key)
		t->rightchild = insert(k, t->rightchild);
	return t;
}

/* 2分探索木 t の最小値を削除する． */
/* 削除した最小値は *min に与える，削除後の木を返す．*/
node *delete_min(int *min, bs_tree t)
{
	node *temp;
	if(t->leftchild == NULL) { /* 左の子がないので最小値がある */
		*min = t->key;
		temp = t->rightchild;
		free(t); /* メモリの解放 */
		t = temp;
	} else
		t->leftchild = delete_min(min, t->leftchild);
	return t;
}

/* 2分探索木 t からデータ k を削除する． */
node *delete(int k, bs_tree t)
{
	node *temp;
	if(t == NULL) return NULL; /* 何もしない */
	if(k < t->key)
		t->leftchild = delete(k, t->leftchild);
	else if(k > t->key)
		t->rightchild = delete(k, t->rightchild);
	else if(t->leftchild == NULL && t->rightchild == NULL) {
		free(t); t = NULL;
	} else if(t->leftchild == NULL) {
		temp = t->rightchild; free(t); t = temp;
	} else if(t->rightchild == NULL) {
		temp = t->leftchild; free(t); t = temp;
	} else /* 子を二つもっている */
		t->rightchild = delete_min(&(t->key), t->rightchild);
	return t;
}

/* 2分探索木の構造を表示する */
void print_tree(bs_tree t)
{
	if(t) {
		printf("(");
		printf("%d", t->key);
		print_tree(t->leftchild);
		print_tree(t->rightchild);
		printf(")");
	} else {
		printf(".");
	}
}

/* 2分探索木の要素をすべて昇順に表示する */
void list_tree(bs_tree t)
{
	if(t->leftchild != NULL)
		list_tree(t->leftchild);

	printf("%d ", t->key);

	if(t->rightchild != NULL)
		list_tree(t->rightchild);
}

/* 2分探索木の高さを求める関数 */
int height(bs_tree t)
{
	int lh,rh;

	if(t == NULL)
		return 0;

	lh = height(t->leftchild);
	rh = height(t->rightchild);

	if(lh >= rh){
		return lh+1;
	} else {
		return rh+1;
	}
}

int main(void)
{
	int i, k;
	bs_tree t = NULL;
	node *s;

	printf("k = ? (k > 0 -> 挿入, k < 0 -> 削除, k = 0 -> 終了)");
	scanf("%d", &k);
	while(k != 0) {
		if(k > 0) {
			printf("insert %d\n", k);
			t = insert(k, t);
		} else {
			k = -k;
			printf("delete %d\n", k);
			t = delete(k, t);
		}
		print_tree(t); printf("\n");
		list_tree(t); printf("\n");
		printf("height = %d\n", height(t));
		printf("k = ? (k > 0 -> 挿入, k < 0 -> 削除, k = 0 -> 終了)");
		scanf("%d", &k);
	}

	return 0;
}
