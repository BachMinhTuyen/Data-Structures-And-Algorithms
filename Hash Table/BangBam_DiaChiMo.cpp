#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
//#define hashTableSize 7
#define deleteItem -1
int* arr;
int size = 0;	//số phần tử trong HashTable
int hashTableSize = 7;
typedef int ItemType;
struct HashNode
{
	ItemType Key;
	HashNode* Next;
};
//=================================================
void menu();
void khoiTao();
int hashCode(int key);
int giaiQuyetDungDo(int b);
void insertNode(int key);
void display();
void CreateHashTable_FromFile();
void resize();

//=================================================
int main()
{
	int luaChon;
	ItemType x;
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
			CreateHashTable_FromFile();
			display();
			break;
		case 2:
			display();
			break;
		case 3:
			printf("\nNhap phan tu can them: ");
			scanf_s("%d", &x);
			insertNode(x);
			break;
		default:printf("\nLoi! Vui long lua chon lai");
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
}
void khoiTao()
{
	arr = new int[hashTableSize];
	for (int i = 0; i < hashTableSize; i++)
		arr[i] = -1;
}
int hashCode(int key)
{
	return key % hashTableSize;
}
int giaiQuyetDungDo(int b)
{
	for (int i = 0; i < hashTableSize; i++)
	{
		int index = (b + i) % hashTableSize;
		if (arr[index] == -1)
			return index;
	}
}
void insertNode(int key)
{
	int b = hashCode(key);
	int index = giaiQuyetDungDo(b);
	arr[index] = key;
	size++;
	resize();
}
void resize()
{
	int index_start, index, countOfColision;
	if (size > hashTableSize * 60 / 100)
	{
		int k = hashTableSize;
		hashTableSize = hashTableSize * 2;
		arr = (int*)realloc(arr, hashTableSize*sizeof(int));
		
		for (int t = k; t < hashTableSize; t++)
			arr[t] = -1;

		for (int i = 0; i < k; i++)
		{
			if (i != hashCode(arr[i]))
			{
				index_start = hashCode(arr[i]);
				index = index_start;
				countOfColision = 0;
				while (arr[index] != -1)
				{
					index = (index_start + ++countOfColision) % hashTableSize;
				}
				arr[index] = arr[i];
				arr[i] = deleteItem;
			}
		}
	}
}
void display()
{
	for (int i = 0; i < hashTableSize; i++)
	{
		if (arr[i] != -1)
		{
			printf("%d - ", i);
			printf("|%5d|", arr[i]);
		}
		else
		{
			printf("%d - ", i);
		}
		printf("\n");
	}
}
void CreateHashTable_FromFile()
{
	int n;
	ItemType x;
	khoiTao();
	FILE* f;
	fopen_s(&f, "DATA.txt", "rt");
	if (f == NULL)
	{
		printf("Mo file khong thanh cong!");
		_getch();
		return;
	}
	fscanf_s(f, "%d\n", &n);
	for (int i = 1; i <= n; i++)
	{
		fscanf_s(f, "%d ", &x);
		insertNode(x);
	}
	printf("\nDoc file thanh cong!\n");
	fclose(f);
}