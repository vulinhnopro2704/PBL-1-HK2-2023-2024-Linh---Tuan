#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>

typedef char STRING[50];

typedef struct Book
{
    int masosach, namxuatban;
    STRING tensach, tentacgia, nhaxuatban;
    bool trangthaisach;
} Book;


typedef struct BookNode
{
    Book sach;
    struct BookNode *nextbook;
} BookNode;

typedef struct Danhmucsach
{
    BookNode *bookHead; // Quản lý sách đầu tiên trong danh mục sách
    BookNode *bookTail; // Quản lý sách cuối cùng trong danh mục sách
} Danhmucsach;

void Khoitao(Danhmucsach *danhmuc)
{
    danhmuc->bookHead = NULL; // Khởi tạo không có sách nào đầu danh mục sách
    danhmuc->bookTail = NULL; // Khởi tạo không có sách nào cuối danh mục sách
}

BookNode *Khoitaosach (Book *B)
{
    BookNode *BN = (BookNode*)malloc(sizeof(BookNode)); // Cấp phát vùng nhớ cho BookNode BN
    BN->sach = *B; // truyền sách B vào BookNode BN;
    BN->nextbook = NULL;
    return BN;
}


void InsertLast(Danhmucsach *danhmuc, BookNode *BN)
{
    BN->nextbook = NULL; // khởi tạo sai số tiếp theo
    if(danhmuc->bookHead == NULL) // danh mục sách rỗng
    {
        danhmuc->bookHead = BN;
        danhmuc->bookTail = BN;
    }
    else // danh mục sách không rỗng
    {
        danhmuc->bookTail->nextbook = BN; // liên kết node mới vào cuối danh mục sach
        danhmuc->bookTail = BN; // cập nhật lại Node cuối trong danh mục sách
    }
}

void InsertFirst(Danhmucsach *danhmuc, BookNode *BN)
{
    if (danhmuc->bookHead == NULL) // danh mục sách rỗng
    {
        danhmuc->bookHead = BN;
        danhmuc->bookTail = BN;
        BN->nextbook = NULL;
    }
    else // danh mục sách không rỗng
    {
        BN->nextbook = danhmuc->bookHead; // liên kết node mới vào đầu danh mục sách
        danhmuc->bookHead = BN; // cập nhật lại Node đầu trong danh mục sách
    }
}

Book input()
{
	Book x;
	printf("Ma So sach: "); scanf("%d", &x.masosach);
	fflush(stdin);
	printf("\nTen sach: "); gets(x.tensach);
	fflush(stdin);
	printf("\nTen tac gia: "); gets(x.tentacgia);
	fflush(stdin);
	printf("\nNha Xuat ban: "); gets(x.nhaxuatban);
	printf("\nNam Xuat ban: "); scanf("%d", &x.namxuatban);
	x.trangthaisach = true;
	printf("\n");
	return x; 
}



int main() 
{ 
	int n;
	printf("Nhap so sach can luu: "); scanf("%d", &n);
	Book *x = (Book*)malloc(n * sizeof(Book));
	for (int i = 0; i < n; ++i)
	{
		x[i] = input();
	} 
    return 0;
}