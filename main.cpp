#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <cstring>
#include <cctype>

typedef struct Book
{
    int masosach, namxuatban, trangthaisach;
    char tensach[50], tentacgia[50], nhaxuatban[50];
} Book;

typedef struct BookNode
{
    Book sach;
    struct BookNode *nextbook;
} BookNode;

typedef struct Danhmucsach
{
    BookNode *bookHead; // Qu?n lý sách ??u tiên trong danh m?c sách
    BookNode *bookTail; // Qu?n lý sách cu?i cùng trong danh m?c sách
} Danhmucsach;

void Khoitao(Danhmucsach *danhmuc)
{
    danhmuc->bookHead = NULL; // Kh?i t?o không có sách nào ??u danh m?c sách
    danhmuc->bookTail = NULL; // Kh?i t?o không có sách nào cu?i danh m?c sách
}

BookNode *Khoitaosach(Book B)
{
    BookNode *BN = new BookNode; // C?p phát vùng nh? cho BookNode BN
    BN->sach = B; // truy?n sách B vào BookNode BN;
    BN->nextbook = NULL;
    return BN;
}

void Nhapsach(Book *sach)
{
    printf("Nhap ma so sach:");
    scanf("%d", &sach->masosach);
    printf("Nhap nam xuat ban:");
    scanf("%d", &sach->namxuatban);
    printf("Nhap ten sach:");
    fflush(stdin);
	gets(sach->tensach);
    printf("Nhap ten tac gia:");
    fflush(stdin);
    gets(sach->tentacgia);
    printf("Nhap nha xuat ban:");
    fflush(stdin);
    gets(sach->nhaxuatban);
    sach->trangthaisach = 1;
}

void InsertFirst(Danhmucsach *danhmuc, BookNode *BN)
{
    if(danhmuc->bookHead == NULL)
    {
        danhmuc->bookHead = danhmuc->bookTail = BN;
    }
    else
    {
        BN->nextbook = danhmuc->bookHead;
        danhmuc->bookHead = BN;
    }
}

void InsertLast(Danhmucsach *danhmuc, BookNode *BN)
{

    if(danhmuc->bookHead == NULL)
    {
        danhmuc->bookHead = danhmuc->bookTail = BN;
    }
    else
    {
        danhmuc->bookTail->nextbook = BN;
        danhmuc->bookTail = BN;
    }
}

void InsertAfter(Danhmucsach *danhmuc, BookNode *B)
{
    Book sach;
    printf("Nhap thong tin cuon sach can chen vao:");
    Nhapsach(&sach);
    BookNode *BN = Khoitaosach(sach);
    if(danhmuc->bookHead->sach.masosach == B->sach.masosach && danhmuc->bookHead->nextbook == NULL)
    {
        InsertLast(danhmuc, B);
    }
    else
    {
        for(BookNode *k = danhmuc->bookHead; k != NULL; k = k->nextbook)
        {
            if(k->sach.masosach == B->sach.masosach)
            {
                BookNode *Btmp = Khoitaosach(BN->sach);
                BookNode *i = k->nextbook;
                Btmp->nextbook = i;
                k->nextbook = Btmp;
            }
        }
    }
}

void Docfile(Danhmucsach *danhmuc)
{
    FILE *file = fopen("Filedanhsach.txt", "rb");
    if (file == NULL)
    {
        printf("Khong the mo tep de doc");
        Khoitao(danhmuc);
        return;
    }
    Book sach;
    while(fread(&sach, sizeof(Book),1,file)>0) {
        BookNode *BN = Khoitaosach(sach);
        InsertLast(danhmuc, BN);
    }
    printf("Da doc file\n");
    system("pause");
}

void XuatDanhSach(Danhmucsach *danhmuc)
{
	printf("						Bang danh muc sach\n") ;
	for(int i = 1; i <= 117; i++) printf("_");
	printf("\n|%15s|%25s|%15s|%20s|%15s|%20s|\n","Ma so sach","Ten sach","Ten tac gia","Ten nha xuat ban","Nam xuat ban","Trang thai sach");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 25;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
    for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
    {
    	printf("\n|%15d|%25s|%15s|%20s|%15d|", BN->sach.masosach, BN->sach.tensach, BN->sach.tentacgia, BN->sach.nhaxuatban, BN->sach.namxuatban);
    	if(BN->sach.trangthaisach)
        {
             printf("%20s|\n","Chua muon");
        }
        else
        {
             printf("%20s|\n","Da muon");
        }
        printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 25;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 20;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 20;i++) printf("_");
		printf("|");
    }
    printf("\n");
}

void LuuFile(Danhmucsach *danhmuc)
{
    FILE *file = fopen("Filedanhsach.txt", "wb"); // M? file ?? ghi (binary mode)
    if (file == NULL)
    {
        printf("Khong the mo tep de ghi");
        return;
    }

    // Duy?t qua danh sách liên k?t và ghi thông tin t?ng cu?n sách vào file
    for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
    {
        fwrite(&(BN->sach), sizeof(Book),1,file);
    }

    fclose(file); // ?óng file sau khi ghi xong
}

void Eraseid(Danhmucsach *danhmuc, int id)
{
	if(danhmuc->bookHead == NULL)
	{
		return;
	}
	else
	{
		for(BookNode *BN = danhmuc->bookHead; BN != danhmuc->bookTail; BN = BN->nextbook)
		{
			if(BN->nextbook->sach.masosach == id)
			{
				if(BN->nextbook == danhmuc->bookTail)
				{
					delete danhmuc->bookTail;
					BN->nextbook = NULL;
					danhmuc->bookTail = BN;
					printf("Cuon sach co ma so '%d' da duoc xoa.\n\n", id);
					return;
				}
				else
				{
					BookNode *B = BN->nextbook;
					BN->nextbook = B->nextbook;
					delete B;
					printf("Cuon sach co ma so '%d' da duoc xoa.\n\n", id);
					return;
				}
			}
		}
		printf("Khong co cuon sach nao co ma so la '%d'.\n\n",id);
	}
}

void EraseNameBook(Danhmucsach *danhmuc, char name[50])
{
	if(danhmuc->bookHead == NULL)
	{
		return;
	}
	else
	{
		for(BookNode *BN = danhmuc->bookHead; BN != danhmuc->bookTail; BN = BN->nextbook)
		{
			if(strcmp(BN->nextbook->sach.tensach, name) == 0)
			{
				if(BN->nextbook == danhmuc->bookTail)
				{
					delete danhmuc->bookTail;
					BN->nextbook = NULL;
					danhmuc->bookTail = BN;
					printf("Cuon sach co ten '%s' da duoc xoa.\n\n", name);
					return;
				}
				else
				{
					BookNode *B = BN->nextbook;
					BN->nextbook = B->nextbook;
					delete B;
					printf("Cuon sach co ten '%s' da duoc xoa.\n\n", name);
					return;
				}
			}
		}
		printf("Khong co cuon sach nao co ten la '%s'.\n\n",name);
	}
}

void EraseNameAuthor(Danhmucsach *danhmuc, char author[50])
{
	if(danhmuc->bookHead == NULL)
	{
		return;
	}
	else
	{
		int tmp = 0;
		BookNode *BN = danhmuc->bookHead;
		while(BN != danhmuc->bookTail)
		{
			if(strcmp(BN->nextbook->sach.tentacgia, author) == 0)
			{
				if(BN->nextbook == danhmuc->bookTail)
				{
					delete danhmuc->bookTail;
					BN->nextbook = NULL;
					danhmuc->bookTail = BN;
					tmp++;


				}
				else
				{
					BookNode *B = BN->nextbook;
					BN->nextbook = B->nextbook;
					delete B;
					tmp++;

				}
			}
			else
			{
				BN = BN->nextbook;
			}
		}
		if(tmp) printf("Tat ca cac cuon sach co tac gia la '%s' da duoc xoa.\n", author);
		else printf("Khong co cuon sach nao co tac gia la '%s'.\n", author);
	}
}

void EraseFirst(Danhmucsach *danhmuc)
{
	if(danhmuc->bookHead == NULL)
	{
		return;
	}
	else
	{
		BookNode *BN = danhmuc->bookHead;
		danhmuc->bookHead = danhmuc->bookHead->nextbook;
		delete BN;
	}
}

void EraseAfter(Danhmucsach *danhmuc, int id)
{
	if(danhmuc->bookHead == NULL)
	{
		return;
	}
	else
	{
		for(BookNode *BN = danhmuc->bookHead; BN != danhmuc->bookTail; BN = BN->nextbook)
		{
			if(BN->sach.masosach == id)
			{
				if(BN->nextbook == danhmuc->bookTail)
				{
					delete danhmuc->bookTail;
					BN->nextbook = NULL;
					danhmuc->bookTail = BN;
					return;
				}
				else
				{
					BookNode *B = BN->nextbook;
					BN->nextbook = B->nextbook;
					delete B;
					return;
				}
			}
		}
//		printf("Khong co cuon sach nao co ma so la %d\n",id);
	}
}

void EraseLast(Danhmucsach *danhmuc)
{
	if(danhmuc->bookHead == NULL)
	{
		return;
	}
	else
	{
		for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
		{
			if(BN->nextbook == danhmuc->bookTail)
			{
				delete danhmuc->bookTail;
				BN->nextbook = NULL;
				danhmuc->bookTail = BN;
				return;
			}
		}
	}
}

void FindNameBook(Danhmucsach *danhmuc, char name[50])
{
	printf("				Thong tin nhung cuon sach co ten la %s\n", name) ;
	for(int i = 1; i <= 117; i++) printf("_");
	printf("\n|%15s|%25s|%15s|%20s|%15s|%20s|\n","Ma so sach","Ten sach","Ten tac gia","Ten nha xuat ban","Nam xuat ban","Trang thai sach");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 25;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
    for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
    {
    	if(strcmp(BN->sach.tensach, name) == 0)
		{
	    	printf("\n|%15d|%25s|%15s|%20s|%15d|", BN->sach.masosach, BN->sach.tensach, BN->sach.tentacgia, BN->sach.nhaxuatban, BN->sach.namxuatban);
	    	if(BN->sach.trangthaisach)
	        {
	             printf("%20s|\n","Chua muon");
	        }
	        else
	        {
	             printf("%20s|\n","Da muon");
	        }
	        printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 25;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 20;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 20;i++) printf("_");
			printf("|");
		}
    }
    printf("\n");
    system("pause");
}

void FindNameAuthor(Danhmucsach *danhmuc, char author[50]){
	printf("				Thong tin nhung cuon sach cua tac gia: %s\n", author) ;
	for(int i = 1; i <= 117; i++) printf("_");
	printf("\n|%15s|%25s|%15s|%20s|%15s|%20s|\n","Ma so sach","Ten sach","Ten tac gia","Ten nha xuat ban","Nam xuat ban","Trang thai sach");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 25;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
    for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
    {
    	if(strcmp(BN->sach.tentacgia, author) == 0)
		{
	    	printf("\n|%15d|%25s|%15s|%20s|%15d|", BN->sach.masosach, BN->sach.tensach, BN->sach.tentacgia, BN->sach.nhaxuatban, BN->sach.namxuatban);
	    	if(BN->sach.trangthaisach)
	        {
	             printf("%20s|\n","Chua muon");
	        }
	        else
	        {
	             printf("%20s|\n","Da muon");
	        }
	        printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 25;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 20;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 20;i++) printf("_");
			printf("|");
		}
    }
    printf("\n");
    system("pause");
}

void FindNamePublisher(Danhmucsach *danhmuc, char publisher[50])
{
	printf("				Thong tin nhung cuon sach co nha xuat ban la %s\n", publisher) ;
	for(int i = 1; i <= 117; i++) printf("_");
	printf("\n|%15s|%25s|%15s|%20s|%15s|%20s|\n","Ma so sach","Ten sach","Ten tac gia","Ten nha xuat ban","Nam xuat ban","Trang thai sach");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 25;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 15;i++) printf("_");
	printf("|");
	for(int i = 1; i <= 20;i++) printf("_");
	printf("|");
    for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
    {
    	if(strcmp(BN->sach.nhaxuatban, publisher) == 0)
		{
	    	printf("\n|%15d|%25s|%15s|%20s|%15d|", BN->sach.masosach, BN->sach.tensach, BN->sach.tentacgia, BN->sach.nhaxuatban, BN->sach.namxuatban);
	    	if(BN->sach.trangthaisach)
	        {
	             printf("%20s|\n","Chua muon");
	        }
	        else
	        {
	             printf("%20s|\n","Da muon");
	        }
	        printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 25;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 20;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 15;i++) printf("_");
			printf("|");
			for(int i = 1; i <= 20;i++) printf("_");
			printf("|");
		}
    }
    printf("\n");
    system("pause");
}

int CheckBorrowed(Danhmucsach *danhmuc)
{
	for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
    {
    	if(BN->sach.trangthaisach == 0)
		{
	    	return 1;
		}
    }
    return 0;
}

int CheckUnBorrowed(Danhmucsach *danhmuc)
{
	for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
    {
    	if(BN->sach.trangthaisach)
		{
	    	return 1;
		}
    }
    return 0;
}

void BorrowedBooks(Danhmucsach *danhmuc)
{
	if(CheckBorrowed(danhmuc))
	{
		printf("				  Thong tin nhung cuon sach da cho muon\n") ;
		for(int i = 1; i <= 117; i++) printf("_");
		printf("\n|%15s|%25s|%15s|%20s|%15s|%20s|\n","Ma so sach","Ten sach","Ten tac gia","Ten nha xuat ban","Nam xuat ban","Trang thai sach");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 25;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 20;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 20;i++) printf("_");
		printf("|");
	    for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
	    {
	    	if(BN->sach.trangthaisach == 0)
			{
		    	printf("\n|%15d|%25s|%15s|%20s|%15d|", BN->sach.masosach, BN->sach.tensach, BN->sach.tentacgia, BN->sach.nhaxuatban, BN->sach.namxuatban);
		    	if(BN->sach.trangthaisach)
		        {
		             printf("%20s|\n","Chua muon");
		        }
		        else
		        {
		             printf("%20s|\n","Da muon");
		        }
		        printf("|");
				for(int i = 1; i <= 15;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 25;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 15;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 20;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 15;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 20;i++) printf("_");
				printf("|");
			}
	    }
	    printf("\n");
	}
	else
	{
		printf("Khong co cuon sach nao da cho muon\n");
	}
}

void UnBorrowedBooks(Danhmucsach *danhmuc)
{
	if(CheckUnBorrowed(danhmuc))
	{
		printf("				  Thong tin nhung cuon sach chua cho muon\n") ;
		for(int i = 1; i <= 117; i++) printf("_");
		printf("\n|%15s|%25s|%15s|%20s|%15s|%20s|\n","Ma so sach","Ten sach","Ten tac gia","Ten nha xuat ban","Nam xuat ban","Trang thai sach");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 25;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 20;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 15;i++) printf("_");
		printf("|");
		for(int i = 1; i <= 20;i++) printf("_");
		printf("|");
	    for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
	    {
	    	if(BN->sach.trangthaisach)
			{
		    	printf("\n|%15d|%25s|%15s|%20s|%15d|", BN->sach.masosach, BN->sach.tensach, BN->sach.tentacgia, BN->sach.nhaxuatban, BN->sach.namxuatban);
		    	if(BN->sach.trangthaisach)
		        {
		             printf("%20s|\n","Chua muon");
		        }
		        else
		        {
		             printf("%20s|\n","Da muon");
		        }
		        printf("|");
				for(int i = 1; i <= 15;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 25;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 15;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 20;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 15;i++) printf("_");
				printf("|");
				for(int i = 1; i <= 20;i++) printf("_");
				printf("|");
			}
	    }
	    printf("\n");
	}
	else
	{
		printf("Tat ca cac cuon sach da duoc muon\n");
	}
}

void BorrowBooks(Danhmucsach *danhmuc)
{
	int id;
	UnBorrowedBooks(danhmuc);
	if(CheckUnBorrowed(danhmuc))
	{
		printf("Chon ma so cuon sach ban muon muon: ");
		fflush(stdin);
		scanf("%d",&id);
		for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
		{
			if(BN->sach.masosach == id)
			{
				BN->sach.trangthaisach = 0;
				printf("Cuon sach co ma so '%d' da duoc muon.\n\n", id);
				return;
			}
		}
	}
}

void ReturnBook(Danhmucsach *danhmuc, int id)
{
	for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
	{
		if(BN->sach.masosach == id)
		{
			BN->sach.trangthaisach = 1;
			printf("Cuon sach co ma so '%d' da duoc tra.\n\n", id);
			return;
		}
	}
	printf("Khong co cuon sach nao co ma so '%d'.\n", id);
}

void AlphabetNameBook(Danhmucsach *danhmuc)
{
	for(BookNode *i = danhmuc->bookHead; i != NULL; i = i->nextbook)
	{
		BookNode *tmp = i;
		for(BookNode *j = i->nextbook; j != NULL; j = j->nextbook)
		{
			if(strcmp(tmp->sach.tensach, j->sach.tensach) > 0)
			{
				tmp = j;
			}
		}
		Book t = tmp->sach;
		tmp->sach = i->sach;
		i->sach = t;
	}
	XuatDanhSach(danhmuc);
}

int NameOfAuthor(char *a)
{
	int i;
	for (i = strlen(a) - 1; i > 0; i --)
	{
		if (a[i] == ' ') return (int) toupper(a[i + 1]);
	}
	return (int) toupper(a[i]);
}

void swapnode(BookNode *a, BookNode *b)
{
	Book tmp = a->sach;
	a->sach = b->sach;
	b->sach = tmp;
}

void AlphabetNameAuthor(Danhmucsach *danhmuc)
{
	int min = NameOfAuthor(danhmuc->bookHead->sach.tentacgia);
	for(BookNode *i = danhmuc->bookHead; i != NULL; i = i->nextbook)
	{
		for (BookNode *j = i->nextbook; j != NULL; j = j->nextbook)
		{
			if (NameOfAuthor(i->sach.tentacgia) > NameOfAuthor(j->sach.tentacgia))
			{
				swapnode(i,j);
			}
		}
	}
	XuatDanhSach(danhmuc);
}

void AlphabetPublisher(Danhmucsach *danhmuc)
{
	for(BookNode *i = danhmuc->bookHead; i != NULL; i = i->nextbook)
	{
		BookNode *tmp = i;
		for(BookNode *j = i->nextbook; j != NULL; j = j->nextbook)
		{
			if(strcmp(tmp->sach.nhaxuatban, j->sach.nhaxuatban) > 0)
			{
				tmp = j;
			}
		}
		Book t = tmp->sach;
		tmp->sach = i->sach;
		i->sach = t;
	}
	XuatDanhSach(danhmuc);
}

void LatestBook(Danhmucsach *danhmuc)
{
	for(BookNode *i = danhmuc->bookHead; i != NULL; i = i->nextbook)
	{
		BookNode *tmp = i;
		for(BookNode *j = i->nextbook; j != NULL; j = j->nextbook)
		{
			if(tmp->sach.namxuatban < j->sach.namxuatban)
			{
				tmp = j;
			}
		}
		Book t = tmp->sach;
		tmp->sach = i->sach;
		i->sach = t;
	}
	XuatDanhSach(danhmuc);
}

void XemDanhSachTheoThuTu(Danhmucsach *danhmuc)
{
	while(1)
	{
		system("cls");
		char lc3;
		printf("Xem danh sach theo thu tu:\n");
		printf("x. Theo van alphabet cua ten sach.\n");
		printf("y. Theo van alphabet cua ten tac gia.\n");
		printf("z. Theo van alphabet cua ten nha xuat ban.\n");
		printf("t. Sach duoc xuat ban moi nhat (theo nam).\n");
		printf("i. Thoat.\n");
		printf("Vui long nhap lua chon cua ban: ");
		fflush(stdin);
		scanf("%c", &lc3);
		switch(lc3)
		{
			case 'x':
			{
				AlphabetNameBook(danhmuc);
				system("pause");
				break;
			}
			case 'y':
			{
				AlphabetNameAuthor(danhmuc);
				system("pause");
				break;
			}
			case 'z':
			{
				AlphabetPublisher(danhmuc);
				system("pause");
				break;
			}
			case 't':
			{
				LatestBook(danhmuc);
				system("pause");
				break;
			}
			case 'i':
			{
				return;
			}
		}
	}
}

void EditNameBook(Danhmucsach *danhmuc, char name[50], int id)
{
	for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
	{
		if(BN->sach.masosach == id)
		{
			strcpy(BN->sach.tensach, name);
			printf("Da sua ten sach thanh '%s'.\n", name);
			return;
		}
	}
}

void EditNameAuthor(Danhmucsach *danhmuc, char author[50], int id)
{
	for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
	{
		if(BN->sach.masosach == id)
		{
			strcpy(BN->sach.tentacgia, author);
			printf("Da sua tac gia cuon sach thanh '%s'.\n", author);
			return;
		}
	}
}

void EditNamePublisher(Danhmucsach *danhmuc, char publisher[50], int id)
{
	for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
	{
		if(BN->sach.masosach == id)
		{
			strcpy(BN->sach.nhaxuatban, publisher);
			printf("Da sua ten nha xuat ban thanh '%s'.\n", publisher);
			return;
		}
	}
}

void EditPublishingYear(Danhmucsach *danhmuc, int publishingyear, int id)
{
	for(BookNode *BN = danhmuc->bookHead; BN != NULL; BN = BN->nextbook)
	{
		if(BN->sach.masosach == id)
		{
			BN->sach.namxuatban = publishingyear;
			printf("Da sua nam xuat ban thanh '%d'.\n", publishingyear);
			return;
		}
	}
}

void Luachon1(Danhmucsach *danhmuc)
{
    while(1)
    {
        char lc2;
        printf("1. Khoi tao danh sach:\n");
        printf("a. Khoi tao danh muc sach rong\n");
        printf("b. Doc tu file\n");
        printf("Nhap lua chon cua ban:");
        fflush(stdin);
        scanf("%c", &lc2);
        switch(lc2)
        {
        	case 'a':
	        {
				printf("Khoi tao danh muc sach rong");
	            Khoitao(danhmuc);
	            return;
	        }
        	case 'b':
	        {
	            Docfile(danhmuc);
	            return;
	        }
	        default:
	        {
	            printf("Lua chon khong hop le, vui long nhap lai:\n");
	            system("pause");
	        }
	    }
    }
}

void Luachon2(Danhmucsach *danhmuc)
{
    char lc2;
    while(1)
    {
    	system("cls");
        printf("2. Them mot cuon sach vao danh sach:\n");
        printf("a. Them vao dau danh sach\n");
        printf("b. Them vao sau mot cuon sach nao do\n");
        printf("c. Them vao cuoi danh sach\n");
        printf("d. Thoat\n");
        printf("Vui long nhap lua chon cua ban:");
        fflush(stdin);
        scanf("%c", &lc2);
        switch(lc2)
        {
        	case'a':
	        {
			 	printf("a) Them vao dau danh sach:\n");
	            Book sach;
	            Nhapsach(&sach);
	            BookNode *BN = Khoitaosach(sach);
	            InsertFirst(danhmuc, BN);
	            printf("Da them cuon sach cua ban vao dau danh sach\n");
	            system("pause");
	            break;
	        }
        	case 'b':
        	{
	            printf("b) Them vao sau mot cuon sach nao do");
	            Book sach;
	            printf("Nhap thong tin cuon sach o truoc cuon sach can chen vao:\n");
	            Nhapsach(&sach);
	            fflush(stdin);
	            BookNode *B = Khoitaosach(sach);
	            InsertAfter(danhmuc, B);
	            printf("Da them cuon sach cua ban vao danh sach\n");
	            system("pause");
	            break;
        	}
        	case 'c':
        	{
	            printf("c) Them vao cuoi danh sach:\n");
	            Book sach;
	            Nhapsach(&sach);
	            BookNode *BN = Khoitaosach(sach);
	            InsertLast(danhmuc, BN);
	            printf("Da them cuon sach cua ban vao cuoi danh sach\n");
	            system("pause");
	            break;
        	}
       		case 'd':
        	{
            	return;
        	}
        	default:
       		{
            printf("Lua chon chua ban khong hop le, vui long nhap lai:\n");
            system("pause");
        	}
    	}
    }
}

void Luachon3(Danhmucsach *danhmuc)
{
	char lc2;
	while(1)
	{
		system("cls");
		printf("3. Xoa mot cuon sach khoi danh sach\n");
        printf("a. Theo ma so\n");
        printf("b. Theo ten sach\n");
        printf("c. Theo ten tac gia\n");
        printf("d. Xoa cuon sach o dau danh sach\n");
        printf("e. Xoa cuon sach o sau cuon sach co ma so nao do\n");
        printf("f. Xoa cuon sach o cuoi danh sach\n");
        printf("g. Thoat\n");
        printf("Vui long nhap lua chon cua ban:");
        fflush(stdin);
        scanf("%c", &lc2);
        switch(lc2)
        {
        	case 'a':
        	{
        		int id;
        		printf("a) Xoa mot cuon sach theo ma so sach:\n");
        		printf("Vui long nhap ma so sach cua cuon sach can xoa:");
        		fflush(stdin);
        		scanf("%d", &id);
        		Eraseid(danhmuc, id);
        		system("pause");
        		break;
			}
			case 'b':
			{
				char name[50];
				printf("b) Xoa mot cuon sach theo ten sach:\n");
        		printf("Vui long nhap ten cua cuon sach can xoa:");
        		fflush(stdin);
        		gets(name);
        		EraseNameBook(danhmuc, name);
        		system("pause");
				break;
			}
			case 'c':
        	{
        		char author[50];
				printf("c) Xoa tat ca cuon sach theo ten tac gia:\n");
        		printf("Vui long nhap ten cua tac:");
        		fflush(stdin);
        		gets(author);
        		EraseNameAuthor(danhmuc, author);
        		system("pause");
        		break;
			}
			case 'd':
			{
				printf("d) Xoa cuon sach o dau danh sach:\n");
				EraseFirst(danhmuc);
				system("pause");
				break;
			}
			case 'e':
        	{
        		int id;
        		printf("e) Xoa cuon sach o sau cuon sach co ma so nao do:\n");
        		printf("Vui long nhap ma so sach cua cuon sach can xoa:");
        		fflush(stdin);
        		scanf("%d", &id);
        		EraseAfter(danhmuc, id);
        		system("pause");
        		break;
			}
			case 'f':
			{
				printf("f) Xoa cuon sach o cuoi danh sach:\n");
				EraseLast(danhmuc);
				system("pause");
				break;
			}
			case 'g':
			{
				return;
			}
			default:
			{
				printf("Lua chon chua ban khong hop le, vui long nhap lai:\n");
            	system("pause");
			}
		}
	}
}
void Luachon4(Danhmucsach *danhmuc)
{
	char lc2;
	while(1)
	{
		system("cls");
		printf("4. Tim kiem sach\n");
		printf("a. Theo ten sach\n");
		printf("b. Theo ten tac gia\n");
		printf("c. Theo ten nha xuat ban\n");
		printf("d. Thoat\n");
		printf("Vui long nhap lua chon cua ban: ");
		fflush(stdin);
		scanf("%c",&lc2);
		switch(lc2)
		{
			case 'a':
			{
				system("cls");
				printf("4. Tim kiem sach\n");
				printf("a. Theo ten sach\n");
				char name[50];
				printf("Vui long nhap ten sach ban muon tim kiem:");
				fflush(stdin);
				gets(name);
				FindNameBook(danhmuc, name);
				break;
			}
			case 'b':
			{
				system("cls");
				printf("4. Tim kiem sach\n");
				printf("b. Theo ten tac gia\n");
				char author[50];
				printf("Vui long nhap ten tac gia ban muon tim kiem:");
				fflush(stdin);
				gets(author);
				FindNameAuthor(danhmuc, author);
				break;
			}
			case 'c':
			{
				system("cls");
				printf("4. Tim kiem sach\n");
				printf("c. Theo ten nha xuat ban\n");
				char publisher[50];
				printf("Vui long nhap ten nha xuat ban ban muon tim kiem:");
				fflush(stdin);
				gets(publisher);
				FindNamePublisher(danhmuc, publisher);
				break;
			}
			case 'd':
			{
				return;
			}
			default:
			{
				printf("Lua chon chua ban khong hop le, vui long nhap lai:\n");
            	system("pause");
			}
		}
	}
}

void Luachon5(Danhmucsach *danhmuc)
{
	char lc2;
	while(1)
	{
		system("cls");
		printf("5. Chuc nang xem danh sach.\n");
        printf("a. Xem toan bo danh muc sach trong danh sach.\n");
        printf("b. Xem nhung cuon sach dang cho muon.\n");
        printf("c. Xem nhung cuon sach chua cho muon.\n");
        printf("d. Xem danh sach theo thu tu\n");
        printf("e. Thoat\n");
        printf("Vui long nhap lua chon cua ban:");
        fflush(stdin);
        scanf("%c", &lc2);
        switch(lc2)
        {
        	case 'a':
        	{
        		XuatDanhSach(danhmuc);
        		system("pause");
        		break;
			}
			case 'b':
			{
				BorrowedBooks(danhmuc);
				system("pause");
				break;
			}
			case 'c':
        	{
        		UnBorrowedBooks(danhmuc);
        		system("pause");
        		break;
			}
			case 'd':
			{
				XemDanhSachTheoThuTu(danhmuc);
				break;
			}
			case 'e':
        	{
        		return;
			}
			default:
			{
				printf("Lua chon chua ban khong hop le, vui long nhap lai:\n");
            	system("pause");
			}
		}
	}
}

void Luachon6(Danhmucsach *danhmuc)
{
	char lc2;
	while(1)
	{
		system("cls");
		printf("6. Chuc nang muon/tra sach\n");
		printf("a. Muon sach\n");
		printf("b. Tra sach\n");
		printf("c. Thoat\n");
		printf("Vui long nhap lua chon cua ban: ");
		fflush(stdin);
		scanf("%c",&lc2);
		switch(lc2)
		{
			case 'a':
			{
				system("cls");
				printf("6. Chuc nang muon/tra sach\n");
				printf("a. Muon sach\n");
				BorrowBooks(danhmuc);
				system("pause");
				break;
			}
			case 'b':
			{
				system("cls");
				printf("6. Chuc nang muon/tra sach\n");
				printf("b. Tra sach\n");
				int id;
				printf("Vui long nhap ma so sach ban muon tra: ");
				fflush(stdin);
				scanf("%d", &id);
				ReturnBook(danhmuc, id);
				system("pause");
				break;
			}
			case 'c':
			{
				return;
			}
			default:
			{
				printf("Lua chon chua ban khong hop le, vui long nhap lai:\n");
            	system("pause");
			}
		}
	}
}

void Luachon7(Danhmucsach *danhmuc)
{
	XuatDanhSach(danhmuc);
	int id;
	printf("Vui long nhap ma so cua cuon sach ban muon thay doi noi dung:");
	fflush(stdin);
	scanf("%d", &id);
	char lc2;
	while(1){
		system("cls");
		XuatDanhSach(danhmuc);
		printf("Ban muon chinh sua cuon sach co ma so '%d'.\n", id);
		printf("Danh sach cac thao tac:\n");
		printf("a. Chinh sua ten sach\n");
		printf("b. Chinh sua ten tac gia\n");
		printf("c. Chinh sua ten nha xuat ban\n");
		printf("d. Chinh sua nam xuat ban\n");
		printf("e. Chinh sua trang thai sach\n");
		printf("f. Chinh sua ma so sach\n");
		printf("g. Thoat.\n");
		printf("Vui long nhap lua chon cua ban:");
		fflush(stdin);
		scanf("%c", &lc2);
		switch(lc2)
		{
			case 'a':
			{
				printf("a. Chinh sua ten sach.\n");
				char name[50];
				printf("Ten sach ban muon sua lai la:");
				fflush(stdin);
				gets(name);
				EditNameBook(danhmuc, name, id);
				system("pause");
				break;
			}
			case 'b':
			{
				printf("b. Chinh sua ten tac gia.\n");
				char author[50];
				printf("Ten tac gia ban muon sua lai la:");
				fflush(stdin);
				gets(author);
				EditNameAuthor(danhmuc, author, id);
				system("pause");
				break;
			}
			case 'c':
			{
				printf("c. Chinh sua ten nha xuat ban.\n");
				char publisher[50];
				printf("Ten nha xuat ban ban muon sua lai la:");
				fflush(stdin);
				gets(publisher);
				EditNamePublisher(danhmuc, publisher, id);
				system("pause");
				break;
			}
			case 'd':
			{
				printf("d. Chinh sua nam xuat ban.\n");
				int publishingyear;
				printf("Nam xuat ban ban muon sua lai la:");
				fflush(stdin);
				scanf("%d", &publishingyear);
				EditPublishingYear(danhmuc, publishingyear, id);
				system("pause");
				break;
			}
			case 'g':
			{
				return;
			}
		}
	}
}

void menu(int lc1, Danhmucsach *danhmuc)
{
    while(1)
    {
    	system("cls");
        printf("\n================= Menu =================\n");
        printf("1. Khoi tao danh sach\n");
        printf("2. Them mot cuon sach vao danh sach\n");
        printf("3. Xoa mot cuon sach khoi danh sach\n");
        printf("4. Tim kiem sach\n");
        printf("5. Chuc nang xem danh sach\n");
        printf("6. Chuc nang muon/tra sach\n");
        printf("7. Chuc nang chinh sua noi dung cua sach\n");
        printf("8. Luu file\n");
        printf("0. Thoat\n");
        printf("================== End ==================\n");
        printf("Nhap lua chon:");
        fflush(stdin);
        scanf("%d", &lc1);
        switch (lc1)
        {
            case 1:
            {
                Luachon1(danhmuc);
                break;
            }
            case 2:
            {
                Luachon2(danhmuc);
                break;
            }
            case 3:
            {
            	Luachon3(danhmuc);
            	break;
			}
			case 4:
			{
				Luachon4(danhmuc);
				break;
			}
            case 5:
            {
                Luachon5(danhmuc);
                break;
            }
            case 6:
            {
            	Luachon6(danhmuc);
            	break;
			}
			case 7:
			{
				Luachon7(danhmuc);
				break;
			}
            case 8:
            {
                LuuFile(danhmuc);
                break;
            }
            case 0:
            {
                return;
            }
			system("pause");
        }
    }
}

int main() {
    Danhmucsach danhmuc;
    int lc1;
    menu(lc1, &danhmuc);
    return 0;
}
