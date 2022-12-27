#define _CRT_SECURE_NO_WARINGS_
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAXSIZE 27
struct SinhVien
{
	int maSV;
	char tenSV[31];
	int namSinh;
	float Diem;
};
typedef SinhVien ItemType;
struct HashNode
{
	ItemType Key;
	HashNode* Next;
};
HashNode* bucket[MAXSIZE];

void menu();
int hashFunction(int key);
void initBucket();
void push(int b, int x);
void insertAfter(HashNode* p, int k);
void place(int b, ItemType k);
int isEmptyBucket(int b);
void createHashTable_FromFile();
void traverse();
void traverseBucket(int b);
//HashNode* search(int k);
//int search(int k);
//int pop(int b);
//int deleteAfter(HashNode* p);
//void Remove(int k);

int main()
{
	int luaChon, x;
	HashNode* pf;

	for (;;)
	{
		system("cls");
		menu();
		printf("Nhap lua chon: ");
		scanf_s("%d", &luaChon);
		if (luaChon == 0)
			break;
		switch (luaChon)
		{
		case 1:
			createHashTable_FromFile();
			traverse();
			break;
		case 2:
			traverse();
			break;
		/*case 3:
			traverse();
			printf("\n\nNhap gia tri can tim: ");
			scanf_s("%d", &x);
			pf = search(x);
			if (pf == NULL)
				printf("\nKhong tim thay \'%d\' tren bang bam", x);
			else
				printf("\nTim thay gia tri \'%d\' tren bang bam", pf->Key);
			break;
		case 4:
			traverse();
			printf("\n\nNhap gia tri can xoa: ");
			scanf_s("%d", &x);
			Remove(x);
			break;*/
		default:printf("\nLoi! Vui long nhap lai lua chon");
			break;
		}
		_getch();
	}
	return 0;
}
void menu()
{
	printf("0. Thoat chuong trinh\n");
	printf("1. Tao bang bam tu file\n");
	printf("2. Xuat bang bam\n");
	//printf("3. Tim kiem phan tu tren bang bam\n");
	//printf("4. Xoa phan tu co khoa k\n");
}
int hashFunction(int key)
{
	return (key % MAXSIZE);
}
void initBucket()
{
	for (int b = 0; b < MAXSIZE; b++)
		bucket[b] = NULL;
}
void push(int b, ItemType x)
{
	HashNode* p = new HashNode;
	p->Key = x;
	p->Next = bucket[b];
	bucket[b] = p;
}
void insertAfter(HashNode* p, ItemType k)
{
	if (p == NULL)
		printf("\nKhong them vao node moi duoc");
	else
	{
		HashNode* q = new HashNode;
		q->Key = k;
		q->Next = p->Next;
		p->Next = q;
	}
}
void place(int b, ItemType k)
{
	HashNode* p, *q;
	q = NULL;
	for (p = bucket[b]; p != NULL && k.maSV > p->Key.maSV; p = p->Next)
		q = p;
	if (q == NULL)
		push(b, k);
	else
		insertAfter(q, k);
}
int isEmptyBucket(int b)
{
	return (bucket[b] == NULL ? 1 : 0);
}
void insert(ItemType k)
{
	int b = hashFunction(k.maSV);
	place(b, k);
}
void createHashTable_FromFile()
{
	int n;
	ItemType x;
	initBucket();
	FILE* f;
	fopen_s(&f, "DATA.txt", "rt");
	if (f == NULL)
	{
		printf("Mo file khong thanh cong!");
		_getch();
		return;
	}
	fscanf_s(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf_s(f, "%d#%[^\#]#%d#%f\n", &x.maSV, x.tenSV, sizeof(x.tenSV), &x.namSinh, &x.Diem);
		insert(x);
	}
	printf("\nDoc file thanh cong!\n");
	fclose(f);
}
void traverse()
{
	for (int b = 0; b < MAXSIZE; b++)
	{
		//Loại bỏ những bucket rỗng
		if (isEmptyBucket(b))
			continue;

		printf("\nBucket[%d] = ", b);
		traverseBucket(b);
	}
}
void traverseBucket(int b)
{
	for (HashNode* p = bucket[b]; p != NULL; p = p->Next)
		printf("\t| %5d | %15s | %8d | %5.2f|\n\t", p->Key.maSV, p->Key.tenSV, p->Key.namSinh, p->Key.Diem);
}
//HashNode* search(ItemType k)
//{
//	int b = hashFunction(k.maSV);
//	for (HashNode* p = bucket[b]; p != NULL; p = p->Next)
//	if (k.maSV == p->Key.maSV)
//		return p;
//	return NULL;
//}
//int search(int k)
//{
//	int b = hashFunction(k);
//	HashNode* p = bucket[b];
//	while (k > p->Key && p!= NULL)
//		p = p->Next;
//	if(p == NULL || k != p->Key)
//		return -1;
//	else 
//		return b;//trả về vị trí bucket
//}

//int pop(int b)
//{
//	HashNode* p;
//	ItemType k;
//	if (isEmptyBucket(b))
//	{
//		printf("\nBucket %d bi rong, khong xoa duoc");
//		return 0;
//	}
//	p = bucket[b];
//	k = p->Key;
//	bucket[b] = p->Next;
//	delete p;
//	return k.maSV;
//}
//int deleteAfter(HashNode* p)
//{
//	HashNode* q;
//	int k;
//	if (p == NULL || p->Next == NULL)
//	{
//		printf("\nKhong xoa Node duoc");
//		return 0;
//	}
//	q = p->Next;
//	k = q->Key;
//	p->Next = q->Next;
//	delete q;
//	return k;
//}
//void Remove(int k)
//{
//	int b;
//	HashNode* p, *q;
//	b = hashFunction(k);
//	p = bucket[b];
//	q = p;
//	while (p != NULL && p->Key != k)
//	{
//		q = p;
//		p = p->Next;
//	}
//	if (p == NULL)
//		printf("\nKhong co Node co khoa la: %d", b);
//	else if (p == bucket[b])
//	{
//		pop(b);
//		printf("\nXoa thanh cong");
//	}
//	else
//	{
//		deleteAfter(q);
//		printf("\nXoa thanh cong");
//	}
//}
