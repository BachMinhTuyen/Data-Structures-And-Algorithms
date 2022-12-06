#include<stdio.h>
#include<conio.h>
typedef int ItemType;
struct TNode
{
	ItemType Info;
	TNode* Left;
	TNode* Right;
};
struct BSTree
{
	TNode* Root;
};
void initBSTree(BSTree& bst);
TNode* createTNode(ItemType x);
void showTNode(TNode* p);
int isEmpty(BSTree bst);
int insertTNode(TNode*& root, TNode* p);
void createBSTree_FromFile(BSTree& bst);
void traverseLNR(TNode* root);
int countTNode(TNode* root);
int countTNodeLeaf(TNode* root);
int countTNodeNoLeaf(TNode* root);
int countTNodeMedium_01(TNode* root);
int countTNodeMedium_02(TNode* root);
int countTNodeX(TNode* root, int x);
int countTNodeLeafLevelK(TNode* root, int k);
int main()
{
	BSTree bst;
	int x, k;
	//Tạo cây từ file
	createBSTree_FromFile(bst);
	traverseLNR(bst.Root);
	printf("\nTong so nut tren cay: %d", countTNode(bst.Root));
	printf("\nTong so nut la tren cay: %d", countTNodeLeaf(bst.Root));
	printf("\nTong so nut khong phai nut la tren cay: %d", countTNodeNoLeaf(bst.Root));
	printf("\nTong so nut trung gian tren cay (cach 1): %d", countTNodeMedium_01(bst.Root));
	printf("\nTong so nut trung gian tren cay (cach 2): %d", countTNodeMedium_02(bst.Root));
	printf("\nNhap x = "); scanf_s("%d", &x);
	printf("\nTong so nut co gia tri bang %d la: %d", x, countTNodeX(bst.Root, x));
	printf("\nNhap muc k = "); scanf_s("%d", &k);
	printf("\nTong so nut o muc %d la: %d", k, countTNodeLeafLevelK(bst.Root, k));
	_getch();
	return 0;
}
void initBSTree(BSTree& bst)
{
	bst.Root = NULL;
}
TNode* createTNode(ItemType x)
{
	TNode* p = new TNode;
	if (p == NULL)
	{
		printf("\nKhong Du Bo Nho De Cap Phat!");
		_getch();
		return NULL;
	}
	p->Info = x;
	p->Left = NULL;
	p->Right = NULL;
	return p;
}
void showTNode(TNode* p)
{
	printf("%5d", p->Info);
}
int isEmpty(BSTree bst)
{
	if (bst.Root == NULL)
		return 1;//Cây rỗng
	return 0;//Cây không rỗng
}
int insertTNode(TNode*& root, TNode* p)
{
	if (p == NULL)
		return 0;	//Không thành công
	//Nếu gốc chưa có
	if (root == NULL)
	{
		root = p;
		return 1;	//Thành công
	}
	//Nếu gốc có giá trị bằng giá trị thêm vào ==> Không thêm vào nữa
	if (root->Info == p->Info)
		return 0;	//Bị trùng nút
	//Nếu chưa có con trái ==> thêm bên trái
	if (root->Info > p->Info)
		insertTNode(root->Left, p);
	//Ngược lại nếu chưa có con phải ==> thêm bên phải
	else
		insertTNode(root->Right, p);
	return 1;	//Thành công
}
/*		File "DATA.txt"
16
10 8 9 5 4 17 15 16 20 11 12 13 19 7 25 6
*/
//Tương tự như mảng 1 chiều trong file
void createBSTree_FromFile(BSTree& bst)
{
	int n;
	ItemType x;
	initBSTree(bst);
	FILE* f;
	fopen_s(&f, "DATA.txt", "rt");
	if (f == NULL)
	{
		printf("\nKhong Mo File Thanh Cong!");
		return;
	}
	fscanf_s(f, "%d\n", &n);
	for (int i = 1; i <= n; i++)
	{
		fscanf_s(f, "%d ", &x);
		TNode* p = createTNode(x);
		insertTNode(bst.Root, p);
	}
	printf("\nTao cay thanh cong!\n");
	fclose(f);
}
//Duyệt cây theo Left - Node - Right (traverse LNR)
void traverseLNR(TNode* root)
{
	if (root == NULL)
		return;
	traverseLNR(root->Left);
	showTNode(root);
	traverseLNR(root->Right);
}

//Đếm số nút trên cây
int countTNode(TNode* root)
{
	if (!root) return 0;
	int cnl = countTNode(root->Left);
	int cnr = countTNode(root->Right);
	return (1 + cnl + cnr);
}
//Đếm số nút lá
int countTNodeLeaf(TNode* root)
{
	if (!root) return 0;
	int cnl = countTNodeLeaf(root->Left);
	int cnr = countTNodeLeaf(root->Right);
	if (!root->Left && !root->Right)
		return (1 + cnl + cnr);
	return (cnl + cnr);
}
//Đếm số nút không phải là nút lá
int countTNodeNoLeaf(TNode* root)
{
	if (!root) return 0;
	int cnl = countTNodeNoLeaf(root->Left);
	int cnr = countTNodeNoLeaf(root->Right);
	if (root->Left || root->Right)
		return (1 + cnl + cnr);
	return (cnl + cnr);
}
/*
	Đếm số nút trung gian(tất cả các nút trừ nút gốc và nút lá)
*/
int countTNodeMedium_01(TNode* root)
{
	//tổng số nút
	int cn = countTNode(root);
	if (cn <= 2)
		return 0;
	//tổng số nút lá
	int cnl = countTNodeLeaf(root);
	return cn - cnl - 1;
}
//hoặc 
int countTNodeMedium_02(TNode* root)
{
	//tổng số nút không là nút lá
	int n = countTNodeNoLeaf(root);
	if (n > 0)
		return n - 1;
	return 0;
}
//Đếm số nút có giá trị = x
int countTNodeX(TNode* root, int x)
{
	if (!root)
		return 0;
	int nlx = countTNodeX(root->Left, x);
	int nrx = countTNodeX(root->Right, x);
	if (root->Info == x)
		return 1 + nlx + nrx;
	return nlx + nrx;
}
//Đếm các nút lá ở mức k
int countTNodeLeafLevelK(TNode* root, int k)
{
	if (!root)
		return 0;
	if (k == 0 && !root->Left && !root->Right)
		return 1;
	k--; //mức k giảm dần về 0
	int nl = countTNodeLeafLevelK(root->Left, k);
	int nr = countTNodeLeafLevelK(root->Right, k);
	return nl + nr;
}