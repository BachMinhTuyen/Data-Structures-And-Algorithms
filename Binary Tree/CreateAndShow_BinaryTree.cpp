#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
struct TNode
{
	int info;
	TNode* left;
	TNode* right;
};
struct BTree
{
	TNode* root;
};
void initBTree(BTree& bt);
TNode* createTNode(int x);
void showTNode(TNode* p);
int isEmpty(BTree bt);
void insertTNode(TNode*& root, TNode* p);
void createBTree_Automatic(BTree& bt);
void createBTree_FromKeyboard(BTree& bt);
void createBTree_FromArray(BTree& bt);
void traverseNLR(TNode* root);
void traverseNRL(TNode* root);
void traverseLNR(TNode* root);
void traverseLRN(TNode* root);
void traverseRNL(TNode* root);
void traverseRLN(TNode* root);
int main()
{
	BTree bt;
	//Tạo cây tự động
	createBTree_Automatic(bt);

	//Tạo cây từ bàn phím
	//createBTree_FromKeyboard(bt);

	printf("\n\nDuyet theo Node - Left - Right: ");
	traverseNLR(bt.root);

	printf("\n\nDuyet theo Node - Right - Left: ");
	traverseNRL(bt.root);

	printf("\n\nDuyet theo Left - Node - Right: ");
	traverseLNR(bt.root);

	printf("\n\nDuyet theo Left - Right - Node: ");
	traverseLRN(bt.root);

	printf("\n\nDuyet theo Right - Node - Left: ");
	traverseRNL(bt.root);

	printf("\n\nDuyet theo Right - Left - Node: ");
	traverseRLN(bt.root);

	_getch();
	return 0;
}
void initBTree(BTree& bt)
{
	bt.root = NULL;
}
TNode* createTNode(int x)
{
	TNode* p = new TNode;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho De Cap Phat!");
		_getch();
		return NULL;
	}
	p->info = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}
void showTNode(TNode* p)
{
	printf("%5d", p->info);
}
int isEmpty(BTree bt)
{
	if (bt.root == NULL)
		return 1;//Cây rỗng
	return 0;//Cây không rỗng
}
void insertTNode(TNode*& root, TNode* p)
{
	if (p == NULL)
		return;
	//Nếu gốc chưa có
	if (root == NULL)
	{
		root = p;
		return;
	}
	//Nếu chưa có con trái ==> thêm bên trái
	if (root->left == NULL)
		insertTNode(root->left, p);
	//Ngược lại nếu chưa có con phải ==> thêm bên phải
	else if (root->right == NULL)
		insertTNode(root->right, p);
	//Ngược lại nếu có cả 2 bên trái phải ==> thêm vào cây con
	else
	{
		//Tạo số chẵn lẻ ngẫu nhiên
		int x = rand() % 2;
		//Nếu ra chẵn ==> thêm vào nhánh bên trái
		if (x == 0)
			insertTNode(root->left, p);
		//Ngược lại ra lẻ ==> thêm vào nhánh bên phải
		else
			insertTNode(root->right, p);
	}
}
void createBTree_Automatic(BTree& bt)
{
	int n, x;
	printf("\nNhap so nut cua cay: ");
	scanf_s("%d", &n);

	//khởi tạo Binary Tree
	initBTree(bt);

	srand((unsigned)time(NULL));
	for (int i = 1; i <= n; i++)
	{
		//random từ a tới b:  a + rand() % b - a + 1
		//Tạo số ngẫu nhiên trong đoạn [-99,99]
		int x = -99 + rand() % 199;
		TNode* p = createTNode(x);
		insertTNode(bt.root, p);
	}
	printf("\nDa tao cay thanh cong!");
}
void createBTree_FromKeyboard(BTree& bt)
{
	int n, x;
	printf("Nhap so nut cua cay: ");
	scanf_s("%d", &n);

	//khởi tạo Binary Tree
	initBTree(bt);

	for (int i = 1; i <= n; i++)
	{
		printf("Nhap nut thu %d: ", i);
		scanf_s("%d", &x);
		TNode* p = createTNode(x);
		insertTNode(bt.root, p);
	}
}
void createBTree_FromArray(BTree& bt)
{

}
//Duyệt cây theo Node - Left - Right (traverse NLR)
void traverseNLR(TNode* root)
{
	if (root == NULL)
		return;
	showTNode(root);
	traverseNLR(root->left);
	traverseNLR(root->right);
}
//Duyệt cây theo Node - Right - Left (traverse NRL)
void traverseNRL(TNode* root)
{
	if (root == NULL)
		return;
	showTNode(root);
	traverseNRL(root->right);
	traverseNRL(root->left);
}
//Duyệt cây theo Left - Node - Right (traverse LNR)
void traverseLNR(TNode* root)
{
	if (root == NULL)
		return;
	traverseLNR(root->left);
	showTNode(root);
	traverseLNR(root->right);
}
//Duyệt cây theo Left - Right - Node (traverse LRN)
void traverseLRN(TNode* root)
{
	if (root == NULL)
		return;
	traverseLRN(root->left);
	traverseLRN(root->right);
	showTNode(root);
}
//Duyệt cây theo Right - Node - Left (traverse RNL)
void traverseRNL(TNode* root)
{
	if (root == NULL)
		return;
	traverseRNL(root->right);
	showTNode(root);
	traverseRNL(root->left);
}
//Duyệt cây theo Right - Left - Node (traverse RLN)
void traverseRLN(TNode* root)
{
	if (root == NULL)
		return;
	traverseRLN(root->right);
	traverseRLN(root->left);
	showTNode(root);
}