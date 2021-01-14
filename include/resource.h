#ifndef _RESOURCE_H
#define _RESOURCE_H
#include <strlib.h>

/*button control*/
#define NOPRESS 0
#define OK 1
#define CANCEL -1

/*menu related*/
#define FILEMENU 0
#define BOOKMENU 1
#define IOMENU 2
#define ACCMENU 3
#define SEARCHMENU 4
#define HELPMENU 5

/*general*/
#define FILL 1
#define NOFILL 0
#define LEN20 20
#define LEN40 40
#define NONE "NONE"

/*user related*/
#define ADMIN 1
#define USER 2
#define GUEST 0

/*page/view related */
#define SHOWLIMIT 10
#define SORT 999

/*book related*/
#define VIEWBOOKID 11
#define VIEWBOOKNAME 12
#define VIEWBOOKKEYWD 13
#define VIEWBOOKAUTHOR 14
#define VIEWBOOKPUB 15
#define VIEWBOOKPUBDATE 16
#define VIEWBOOKOUT 17
#define VIEWBOOKTYPE 18


/*account related*/
#define VIEWALLACC 21
#define VIEWNEWACC 22
#define VIEWCHGACC 23
#define VIEWACCID 30
#define VIEWACCNAME 31
#define VIEWACCWORK 32

/*record related*/
#define VIEWBORROWAPP 24
#define VIEWRETURNAPP 25


/*menu/window related*/
#define STATUSSIZE 30
#define BKCOLOR "White"
#define FRAMECOLOR "Blue"
#define MAINFRAME 0
#define SECFRAME 1
#define THIRDFRAME 2
#define	FOURTHFRAME 3
#define FRAME(n) n
#define MENU(n) n-1
#define OPT(n) n


//BookInfo related
#define NUMOFKEY 5
#define NUMOFAUTHOR 3
#define MYDATE "YYYYMMDD"




/*to store account information*/
struct AccInfo
{
	char pwd[LEN20];
	char newPwd[LEN20];
	int id;
	char userName[LEN20];
	char newUserName[LEN20];
	char gender[LEN20];
	char work[LEN20];
	char newWork[LEN20];
	int request;/*0:no request, -1:change, 1:register*/
	int priority;
	int numOfconnect;
};


/*to store book information*/
struct BookInfo
{
	int id;
	char bookName[LEN20];
	char keywords[NUMOFKEY][LEN20];
	char authors[NUMOFAUTHOR][LEN20];
	char publisher[LEN20];
	char type[LEN20];
	char pubDate[LEN20];
	int status; /*-2:request for return, -1:borrowed, 1:inventory, 2:request for borrow*/
};


/*to store record information*/
struct RecInfo
{
	struct AccInfo* acc;
	struct BookInfo* book;
	int status; /*2:borrow request, 1:returned, -1:borrowed, -2:return request*/
	char borrowDate[LEN20];
	char returnDate[LEN20];
};

/*account info double linked list*/
struct AccList
{
	struct AccInfo* acc;
	struct AccList* next;
	struct AccList* last;
};

/*book info double linked list*/
struct BookList
{
	struct BookInfo* book;
	struct BookList* next;
	struct BookList* last;
};

/*record info double linked list*/
struct RecList
{
	struct RecInfo* rec;
	struct RecList* next;
	struct RecList* last;
};

/*window frame properities*/
struct winFrame
{
	double x;
	double y;
	double w;
	double h;
};

/*structure to hold info of a library*/
struct Library
{
	struct BookFolder* allBook;
	struct RecFolder* allRec;
	struct AccFolder* allAcc;
	char name[LEN40];
	int accid;
	int bookid;
};

/*structure to hold all the accounts in a library */
struct AccFolder
{
	int numOfall;/*excludes new accs*/
	int numOfNews;
	int numOfChg;
	struct AccList* allHead;/*includes accs with modification requests*/
	struct AccList* chgHead;/*accs with modification requests*/
	struct AccList* newHead;/*new accs*/
};

/*structure to hold all the records in a library */
struct RecFolder
{
	int numOfBorrowed;
	int numOfReturned;
	int numOfBorrowApp;
	int numOfReturnApp;
	struct RecList* borrowAppHead;
	struct RecList* returnAppHead;
	struct RecList* borrowedHead;
	struct RecList* returnedHead;
};

/*structure to hold all the books in a library */
struct BookFolder
{
	int numOfAll;
	int numOfInv;
	int numOfBorrowed;
	struct BookList* allHead;
	struct BookList* invHead;
	struct BookList* borrowedHead;
};

/*page controller*/
struct Pager
{
	struct AccList* accPtr;
	struct RecList* recPtr;
	struct BookList* bookPtr;
	int page;
	int pageOption;/*1:next page, -1:last page*/
	int maxPage;
};

/*item select control*/
struct Selector
{
	int itemNum;
	struct AccList* accPtr;
	struct RecList* recPtr;
	struct BookList* bookPtr;
};

/*main controller*/
struct Control
{
	int menuSelect;
	int optSelect;
	int menuLvl;
	char status[100];
	int buttonPressed;
	int fun;
	struct Pager* pager;
	struct Selector* item;
	int chgView;
	int view;
	int op;/*1:yes, -1:no, 2:view selected*/
};

#endif