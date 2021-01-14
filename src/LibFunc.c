#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>


#include "imgui.h"
#include "LibGUI.h"
#include "LibFunc.h"
#include "resource.h"

#include "LibGUI.h"

void copyBook(struct BookInfo* dest, struct BookInfo* src)
{
	for (int i = 0; i < NUMOFAUTHOR; i++) {
		strcpy(dest->authors[i], src->authors[i]);
	}
	dest->id = src->id;
	strcpy(dest->bookName, src->bookName);
	strcpy(dest->type, src->type);
	dest->status = src->status;
	for (int i = 0; i < NUMOFKEY; i++) {
		strcpy(dest->keywords[i], src->keywords[i]);
	}
	strcpy(dest->pubDate, src->pubDate);
	strcpy(dest->publisher, src->publisher);
	strcpy(dest->type, src->type);
}

int AboutSoftware(struct winFrame* f, struct Control* ctrl)
{
	double y = f->y + f->h / 6 * 4;
	double fh = GetFontHeight() * 1.5;
	SetPenColor("White");
	drawRectangle(f->x, f->y, f->w, f->h, FILL);
	SetPenColor("Blue");
	drawRectangle(f->x, f->y, f->w, f->h, NOFILL);
	MovePen(f->x + f->w / 5, y);
	DrawTextString("About this software:");
	MovePen(f->x + f->w / 5, y-=fh);
	DrawTextString("2020 version 1.0");
	MovePen(f->x + f->w / 5, y-=fh );
	DrawTextString("程序设计专题大作业");
	char s[] = { "确定" };
	double buttonw = TextStringWidth(s)*1.2;
	double buttonh = GetFontHeight() * 1.5;
	return button(GenUIID(0), f->x + f->w / 2 - buttonw / 2, f->y + buttonh / 2, buttonw, buttonh, s);
}

void InitAcc(struct AccInfo* acc)
{
	strcpy(acc->gender, NONE);
	acc->id = 0;
	strcpy(acc->newPwd, NONE);
	strcpy(acc->newUserName, NONE);
	strcpy(acc->newWork, NONE);
	acc->priority = 0;
	strcpy(acc->pwd, NONE);
	acc->request = 0;
	strcpy(acc->userName, NONE);
	strcpy(acc->work, NONE);
	acc->numOfconnect = 0;
}

void InitRec(struct RecInfo* rec)
{
	rec->acc = NULL;
	rec->book = NULL;
	strcpy(rec->borrowDate, MYDATE);
	strcpy(rec->returnDate, MYDATE);
	rec->status = 0;
}

void InitBook(struct BookInfo* book)
{
	for (int i = 0; i < NUMOFAUTHOR; i++) {
		strcpy(book->authors[i], NONE);
		
	}
	strcpy(book->bookName, NONE);
	strcpy(book->type, NONE);
	book->id = 0;
	for (int i = 0; i < NUMOFKEY; i++) {
		strcpy(book->keywords[i], NONE);
	}
	strcpy(book->pubDate, NONE);
	strcpy(book->publisher, NONE);
	book->status = 0;
	strcpy(book->type, NONE);
}
/*
void InitAccList(struct AccList* acc)
{
	acc->acc = NULL;
	acc->last = NULL;
	acc->next = NULL;
}

void InitRecList(struct RecList* rec)
{
	rec->rec = NULL;
	rec->next = NULL;
	rec->last = NULL;
}

void InitBookList(struct BookList* book)
{
	book->book = NULL;
	book->next = NULL;
	book->last = NULL;
}
*/
void InitAccFolder(struct AccFolder* folder)
{
	folder->allHead->next = NULL;
	folder->allHead->last = NULL;

	folder->chgHead->next = NULL;
	folder->chgHead->last = NULL;

	folder->newHead->next = NULL;
	folder->newHead->last = NULL;

	folder->numOfall = 0;
	folder->numOfChg = 0;
	folder->numOfNews = 0;
}

void InitRecFolder(struct RecFolder* folder)
{
	folder->borrowedHead->next = NULL;
	folder->borrowedHead->last = NULL;

	folder->borrowAppHead->next = NULL;
	folder->borrowAppHead->last = NULL;

	folder->numOfBorrowed = 0;
	folder->numOfBorrowApp = 0;
	folder->numOfReturned = 0;
	folder->numOfReturnApp = 0;

	folder->returnAppHead->next = NULL;
	folder->returnAppHead->last = NULL;

	folder->returnedHead->next = NULL;
	folder->returnedHead->last = NULL;
}

void InitBookFolder(struct BookFolder* folder)
{
	folder->allHead->next = NULL;
	folder->allHead->last = NULL;

	folder->borrowedHead->next = NULL;
	folder->borrowedHead->last = NULL;

	folder->invHead->next = NULL;
	folder->invHead->last = NULL;
	folder->numOfAll = 0;
	folder->numOfBorrowed = 0;
	folder->numOfInv = 0;
}

void InitLibrary(struct Library* lib)
{
	InitAccFolder(lib->allAcc);
	InitBookFolder(lib->allBook);
	InitRecFolder(lib->allRec);
	strcpy(lib->name, NONE);
	lib->bookid = 0;
	lib->accid = 0;
}

void InitPager(struct Pager* pager)
{
	pager->accPtr = NULL;
	pager->bookPtr = NULL;
	pager->recPtr = NULL;
	pager->pageOption = 0;
	pager->maxPage = 0;
	pager->page = 0;
}

void InitSelector(struct Selector* select)
{
	select->accPtr = NULL;
	select->bookPtr = NULL;
	select->itemNum = 0;
	select->recPtr = NULL;
}

void InitControl(struct Control* ctrl)
{
	ctrl->buttonPressed = NOPRESS;
	ctrl->chgView = 0;
	ctrl->fun = 0;
	InitSelector(ctrl->item);
	ctrl->menuLvl = 0;
	ctrl->menuSelect = 0;
	ctrl->op = 0;
	ctrl->optSelect = 0;
	InitPager(ctrl->pager);
	strcpy(ctrl->status, "主界面");
	ctrl->view = 0;
}

void ResetLibrary(struct Library* lib)
{
	FreeAccFolder(lib->allAcc);
	FreeRecFolder(lib->allRec);
	FreeBookFolder(lib->allBook);
	InitLibrary(lib);
}

void FreeAccFolder(struct AccFolder* folder)
{
	struct AccList* ptr;
	//free double linked lists
	while (folder->chgHead->next) {
		ptr = folder->chgHead->next;
		folder->chgHead->next = folder->chgHead->next->next;
		ptr->acc = NULL;
		ptr->next = NULL;
		ptr->last = NULL;
		free(ptr);
		folder->numOfChg--;
	}
	while (folder->newHead->next) {
		ptr = folder->newHead->next;
		folder->newHead->next = folder->newHead->next->next;
		if (ptr->acc)free(ptr->acc);
		ptr->acc = NULL;
		ptr->next = NULL;
		ptr->last = NULL;
		free(ptr);
		folder->numOfNews--;
	}
	while (folder->allHead->next) {
		ptr = folder->allHead->next;
		folder->allHead->next = folder->allHead->next->next;
		if (ptr->acc)free(ptr->acc);
		ptr->acc = NULL;
		ptr->next = NULL;
		ptr->last = NULL;
		free(ptr);
		folder->numOfall--;
	}
	int n = folder->numOfNews + folder->numOfChg + folder->numOfall;
	if (n != 0) {
		InitConsole();
		printf("error in FreeAccFolder\n");
		system("pause");
	}
}

void FreeRecFolder(struct RecFolder* folder)
{
	struct RecList* ptr;
	while (folder->borrowAppHead->next) {
		ptr = folder->borrowAppHead->next;
		folder->borrowAppHead->next = folder->borrowAppHead->next->next;
		ptr->rec->acc = NULL;
		ptr->rec->book = NULL;
		ptr->last = NULL;
		ptr->next = NULL;
		free(ptr);
		folder->numOfBorrowApp--;
	}
	while (folder->borrowedHead->next) {
		ptr = folder->borrowedHead->next;
		folder->borrowedHead->next = folder->borrowedHead->next->next;
		ptr->rec->acc = NULL;
		ptr->rec->book = NULL;
		ptr->last = NULL;
		ptr->next = NULL;
		free(ptr);
		folder->numOfBorrowed--;
	}
	while (folder->returnAppHead->next) {
		ptr = folder->returnAppHead->next;
		folder->returnAppHead->next = folder->returnAppHead->next->next;
		ptr->rec->acc = NULL;
		ptr->rec->book = NULL;
		ptr->last = NULL;
		ptr->next = NULL;
		free(ptr);
		folder->numOfReturnApp--;
	}
	while (folder->returnedHead->next) {
		ptr = folder->returnedHead->next;
		folder->returnedHead->next = folder->returnedHead->next->next;
		ptr->rec->acc = NULL;
		ptr->rec->book = NULL;
		ptr->last = NULL;
		ptr->next = NULL;
		free(ptr);
		folder->numOfReturned--;
	}
	int n = folder->numOfBorrowApp + folder->numOfReturned + folder->numOfReturnApp + folder->numOfBorrowed;
	if (n != 0) {
		InitConsole();
		printf("error free recfolder\n");
		system("pause");
	}
}

void FreeBookFolder(struct BookFolder* folder)
{
	struct BookList* ptr;
	while (folder->borrowedHead->next) {
		ptr = folder->borrowedHead->next;
		folder->borrowedHead->next = folder->borrowedHead->next->next;
		ptr->book = NULL;
		ptr->last = NULL;
		ptr->next = NULL;
		free(ptr);
		folder->numOfBorrowed--;
	}
	while (folder->invHead->next) {
		ptr = folder->invHead->next;
		folder->invHead->next = folder->invHead->next->next;
		ptr->book = NULL;
		ptr->last = NULL;
		ptr->next = NULL;
		free(ptr);
		folder->numOfInv--;
	}

	while (folder->allHead->next) {
		ptr = folder->allHead->next;
		folder->allHead->next = folder->allHead->next->next;
		ptr->book = NULL;
		ptr->last = NULL;
		ptr->next = NULL;
		free(ptr);
		folder->numOfAll--;
	}
	int n = folder->numOfAll + folder->numOfInv + folder->numOfBorrowed;
	if (n != 0) {
		InitConsole();
		printf("error freebookfolder\n");
		system("pause");
	}
}

void nextLvl(struct Control* ctrl, char* s)
{
	switch (ctrl->menuLvl) {
	case 0:
		ctrl->menuLvl = 1;
		InitPager(ctrl->pager);
		InitSelector(ctrl->item);
		break;
	case 1:
		ctrl->menuLvl = 2;
		break;
	case 2:
		ctrl->menuLvl = 3;
		break;
	case 3:
		break;
	}
	ctrl->buttonPressed = NOPRESS;
	ctrl->chgView = 0;
	changeStatus(ctrl, s);
}

void changeStatus(struct Control* ctrl, char* s)
{
	strcpy(ctrl->status, s);
}

void exitLvl(struct Control* ctrl, char* s)
{
	switch (ctrl->menuLvl) {
	case 0:
		InitPager(ctrl->pager);
		InitSelector(ctrl->item);
		ctrl->menuLvl = 0;
		ctrl->menuSelect = MENU(0);
		ctrl->optSelect = OPT(0);
		break;
	case 1:
		InitPager(ctrl->pager);
		InitSelector(ctrl->item);
		ctrl->menuLvl = 0;
		ctrl->menuSelect = MENU(0);
		ctrl->optSelect = OPT(0);
		break;
	case 2:
		ctrl->menuLvl = 1;
		break;
	case 3:
		ctrl->menuLvl = 2;
		break;
	}
	ctrl->chgView = 0;
	ctrl->op = 0;
	ctrl->buttonPressed = NOPRESS;
	ctrl->fun = 0;
	changeStatus(ctrl, s);
}

void changePageBook(struct Pager* pager, int limit)
{
	if (pager->pageOption == 1 && pager->page < pager->maxPage ) {
		for (int i = 0; i < limit && pager->bookPtr && pager->bookPtr->next; i++) {
			pager->bookPtr = pager->bookPtr->next;
		}
		pager->page++;
	}
	else if(pager->pageOption == -1 && pager->page > 0) {
		for (int i = 0; i < limit && pager->bookPtr && pager->bookPtr->last; i++) {
			pager->bookPtr = pager->bookPtr->last;
		}
		pager->page--;
	}
	pager->pageOption = 0;
}

void changePageAcc(struct Pager* pager, int limit)
{
	if (pager->pageOption == 1 && pager->page < pager->maxPage) {
		for (int i = 0; i < limit && pager->accPtr && pager->accPtr->next; i++) {
			pager->accPtr = pager->accPtr->next;
		}
		pager->page++;
	}
	else if (pager->pageOption == -1 && pager->page > 0) {
		for (int i = 0; i < limit && pager->accPtr && pager->accPtr->last; i++) {
			pager->accPtr = pager->accPtr->last;
		}
		pager->page--;
	}
	pager->pageOption = 0;
}

void changePageRec(struct Pager* pager, int limit)
{
	if (pager->pageOption == 1 && pager->page < pager->maxPage) {
		for (int i = 0; i < limit && pager->recPtr && pager->recPtr->next; i++) {
			pager->recPtr = pager->recPtr->next;
		}
		pager->page++;
	}
	else if (pager->pageOption == -1 && pager->page > 0) {
		for (int i = 0; i < limit && pager->recPtr && pager->recPtr->last; i++) {
			pager->recPtr = pager->recPtr->last;
		}
		pager->page--;
	}
	pager->pageOption = 0;
}

int showMsgBox(struct winFrame* f, char* msg) {
	return drawMsgRectangle(f->x, f->y, f->w, f->h, "", msg, "确定");
}

int calPage(double h, int rows)
{
	double fh = GetFontHeight() * 2;
	int n = (int)(h / fh);
	int max;
	if (rows % n == 0)max = rows / n;
	else max = rows / n + 1;
	return max;
}

int fileMenuNewLib(const char* name, const char* libDir)
{
	if (strcmp(name, "") == 0)return 0;
	static char dir[100] = { "" };
	char newFileName[100] = "library_";
	strcpy(dir, libDir);
	strcat(newFileName, name);
	strcat(dir, newFileName);
	FILE* fp;
	fp = fopen(dir, "r");
	if (!fp) {			//file doesnt not eixt, can make new lib
		return 1;
	}	
	else {				//file already exist
		fclose(fp);
		return 0;
	}
		
}

void insertBook(struct BookList* book, struct BookList* head)
{
	if(head->next) head->next->last = book;
	book->next = head->next;
	book->last = head;
	head->next = book;
}

void insertRec(struct RecList* rec, struct RecList* head) {
	if (head->next)head->next->last = rec;
	rec->next = head->next;
	rec->last = head;
	head->next = rec;
}

void insertAcc(struct AccList* acc, struct AccList* head) {
	if (head->next)head->next->last = acc;
	acc->next = head->next;
	acc->last = head;
	head->next = acc;
}

struct AccInfo* verifyAcc(struct AccInfo* accTemp, struct AccList* head) { 
	struct AccList* accPtr = head->next;
	struct AccList* ptr = head->next;
	while (accPtr) {	//find account
		if (strcmp(accPtr->acc->userName, accTemp->userName) == 0) {
			if (strcmp(accPtr->acc->pwd, accTemp->pwd) == 0)
				return accPtr->acc;
			else return NULL;
		}
		accPtr = accPtr->next;
	}
	return NULL;
}

void deleteBook(int bookid, struct Library* lib) {
	struct BookList* ptr;
	/*delete from inventroy double linked list*/
	ptr = lib->allBook->invHead->next;
	while (ptr) {
		if (ptr->book->id == bookid) {
			ptr->last->next = ptr->next;
			if (ptr->next)
				ptr->next->last = ptr->last;
			//else ptr->last->next = NULL;
			ptr->next = NULL;
			ptr->last = NULL;
			ptr->book = NULL;
			free(ptr);
			lib->allBook->numOfInv--;
			break;
		}
		ptr = ptr->next;
	}
	/*delete from all books double linked list*/
	ptr = lib->allBook->allHead->next;
	while (ptr) {
		if (ptr->book->id == bookid) {
			ptr->last->next = ptr->next;
			if (ptr->next)
				ptr->next->last = ptr->last;
			//else ptr->last->next = NULL;
			ptr->next = NULL;
			ptr->last = NULL;
			free(ptr->book);
			ptr->book = NULL;
			free(ptr);
			lib->allBook->numOfAll--;
			break;
		}
		ptr = ptr->next;
	}
}

void registerAcc(struct AccInfo* accTemp, struct Library* lib) {
	struct AccInfo* newInfo = (struct AccInfo*)malloc(sizeof(struct AccInfo));
	/*set up new account info*/
	copyAcc(newInfo, accTemp);
	newInfo->priority = USER;
	newInfo->id = lib->accid++;
	newInfo->numOfconnect = 0;
	newInfo->request = 1;
	/*add account to account registration double linked list*/
	struct AccList* ptr = (struct AccList*)malloc(sizeof(struct AccList));
	ptr->acc = newInfo;
	insertAcc(ptr, lib->allAcc->newHead);
	lib->allAcc->numOfNews++;

}

void accEditApplication(struct AccInfo* temp, struct AccInfo* user, struct Library* lib)
{
	static int found = 0;
	copyAcc(user, temp);
	InitAcc(temp);
	/*if account not already has an account change request, add new*/
	if (user->request != -1) {
		struct AccList* ptr = (struct AccList*)malloc(sizeof(struct AccList));
		ptr->acc = user;
		insertAcc(ptr, lib->allAcc->chgHead);
		lib->allAcc->numOfChg++;
		user->request = -1;
		user->numOfconnect++;
	}
	
}

void addBook(struct BookInfo* book, struct Library* lib)
{
	/*set up book info*/
	struct BookInfo* newbookInfo = (struct BookInfo*)malloc(sizeof(struct BookInfo));
	copyBook(newbookInfo, book);
	newbookInfo->status = 1;
	newbookInfo->id = lib->bookid++;

	/*insert book in all book dlinked list*/
	struct BookList* newbook = (struct BookList*)malloc(sizeof(struct BookList));
	newbook->book = newbookInfo;
	insertBook(newbook, lib->allBook->allHead);
	lib->allBook->numOfAll++;

	/*insert book in inventory dlinked list*/
	struct BookList* newbook2 = (struct BookList*)malloc(sizeof(struct BookList));
	newbook2->book = newbookInfo;
	insertBook(newbook2, lib->allBook->invHead);
	lib->allBook->numOfInv++;
}

void borrowApplication(struct Control* ctrl, struct AccInfo* user, struct Library* lib){
	/*set up new record info*/
	struct RecInfo* newRecInfo = (struct RecInfo*)malloc(sizeof(struct RecInfo));
	newRecInfo->acc = user;
	newRecInfo->book = ctrl->item->bookPtr->book;
	newRecInfo->book->status = 2;
	strcpy(newRecInfo->borrowDate, "YYYYMMDD");
	strcpy(newRecInfo->returnDate, "YYYYMMDD");
	newRecInfo->status = 2;

	/*insert record to borrow applications dlinked list*/
	struct RecList* recPtr = (struct RecList*)malloc(sizeof(struct RecList));
	recPtr->rec=newRecInfo;
	insertRec(recPtr, lib->allRec->borrowAppHead);
	lib->allRec->numOfBorrowApp++;
}

void returnApplication(struct Control* ctrl, struct AccInfo* user, struct Library* lib) {
	struct RecList* recPtr = lib->allRec->borrowedHead->next;

	/*find record from borrowed record,
	change status of borrowed record,
	add new return appliction record*/
	while (recPtr) {
		if (recPtr->rec->book->id == ctrl->item->bookPtr->book->id) {
			recPtr->rec->status = -2;
			recPtr->rec->book->status = -2;
			struct RecList* recPtr2 = (struct RecList*)malloc(sizeof(struct RecList));
			recPtr2->rec = recPtr->rec;
			insertRec(recPtr2, lib->allRec->returnAppHead);
			lib->allRec->numOfReturnApp++;
			break;
		}
		recPtr = recPtr->next;
	}
}

int existAcc(struct AccInfo* accTemp, struct Library* lib) {
	struct AccList* lstPtr = lib->allAcc->allHead->next;
	/*search all accounts to see if usernames is duplicated*/
	while (lstPtr) {
		if (strcmp(lstPtr->acc->userName, accTemp->userName) == 0)
			return 1;
		lstPtr = lstPtr->next;
	}
	return 0;
}

void approveAccChg(struct Control* ctrl, struct Library* lib) {
	/*remove from account edit dlinked list*/
	struct AccList* ptr = ctrl->item->accPtr;
	ptr->last->next = ptr->next;
	if (ptr->next)ptr->next->last = ptr->last;
	ptr->next = NULL;
	ptr->last = NULL;

	/*apply changes*/
	if (!(strcmp(ptr->acc->newPwd, "") == 0 
		|| strcmp(ptr->acc->newPwd, "NONE") == 0)) {
		strcpy(ptr->acc->pwd, ptr->acc->newPwd);
		strcpy(ptr->acc->newPwd, "NONE");
	}
	if (!(strcmp(ptr->acc->newUserName, "") == 0
		|| strcmp(ptr->acc->newUserName, "NONE") == 0)) {
		strcpy(ptr->acc->userName, ptr->acc->newUserName);
		strcpy(ptr->acc->newUserName, "NONE");
	}
	if (!(strcmp(ptr->acc->newWork, "") == 0
		|| strcmp(ptr->acc->newWork, "NONE") == 0)) {
		strcpy(ptr->acc->work, ptr->acc->newWork);
		strcpy(ptr->acc->newWork, "NONE");
	}

	/*change user status*/
	ptr->acc->request = 0;
	ctrl->item->accPtr->acc->numOfconnect--;
	ptr->acc = NULL;
	free(ptr);
	ctrl->item->accPtr = NULL;
	lib->allAcc->numOfChg--;
}

void approveAccReg(struct Control* ctrl, struct Library* lib) {
	struct AccList* ptr = ctrl->item->accPtr;
	/*remove account from registration dlinked list*/
	ptr->last->next = ptr->next;
	if (ptr->next)ptr->next->last = ptr->last;
	ptr->next = NULL;
	ptr->last = NULL;

	/*alter account info*/
	ptr->acc->id = lib->accid++;
	ptr->acc->priority = USER;
	ptr->acc->request = 0;
	ptr->acc->numOfconnect = 0;
	/*insert account in all account dlinked list*/
	insertAcc(ptr, lib->allAcc->allHead);
	lib->allAcc->numOfall++;
	lib->allAcc->numOfNews--;
	ctrl->item->accPtr = NULL;
}

void approveBorrow(struct Control* ctrl, struct Library* lib) {
	struct RecList* ptr = ctrl->item->recPtr;
	/*remove record from borrow application dlink list*/
	ptr->last->next = ptr->next;
	if (ptr->next)ptr->next->last = ptr->last;
	ptr->next = NULL;
	ptr->last = NULL;

	/*change record status*/
	ptr->rec->status = -1;

	/*change book status*/
	ptr->rec->book->status = -1;

	/*insert record to borrowed out dlinked list*/
	insertRec(ptr, lib->allRec->borrowedHead);

	/*up date library record count*/
	lib->allRec->numOfBorrowApp--;
	lib->allRec->numOfBorrowed++;
	ctrl->item->recPtr = NULL;
}

void approveReturn(struct Control* ctrl, struct Library* lib) {
	struct RecList* ptr = ctrl->item->recPtr;
	/*remove record from return applications*/
	ptr->last->next = ptr->next;
	if (ptr->next)ptr->next->last = ptr->last;
	ptr->next = NULL;
	ptr->last = NULL;

	/*change record status*/
	ptr->rec->status = 1;

	/*change book status*/
	ptr->rec->book->status = 1;

	/*insert record to returned records*/
	insertRec(ptr, lib->allRec->returnedHead);

	struct RecList* list = lib->allRec->borrowedHead->next;
	while (list) {
		if (list->rec->book->id == ptr->rec->book->id) {
			list->last->next = list->next;
			if (list->next)list->next->last = list->last;
			list->next = NULL;
			list->last = NULL;
			list->rec = NULL;
			free(list);
			break;
		}
	}

	/*update library record acount*/
	lib->allRec->numOfReturned++;
	lib->allRec->numOfBorrowed--;
	lib->allRec->numOfReturnApp--;
	ctrl->item->recPtr = NULL;
}

void rejectBorrow(struct Control* ctrl, struct Library* lib) {
	/*remove record from borrow applications
	 and delete record*/
	ctrl->item->recPtr->rec->book->status = 1;
	deleteRec(ctrl->item->recPtr);
	ctrl->item->recPtr = NULL;
	lib->allRec->numOfBorrowApp--;
}

void rejectReturn(struct Control* ctrl, struct Library* lib) {
	/*remove record from borrow applications
	 and delete record*/
	ctrl->item->recPtr->rec->book->status = -1;
	deleteRec(ctrl->item->recPtr);
	ctrl->item->recPtr = NULL;
	lib->allRec->numOfReturnApp--;
}

void deleteAcc(struct AccList* acc) {
	acc->last->next = acc->next;
	if (acc->next) acc->next->last = acc->last;
	if(acc->acc) free(acc->acc);
	acc->acc = NULL;
	acc->last = NULL;
	acc->next = NULL;
	free(acc);
}

void deleteRec(struct RecList* rec) {
	rec->last->next = rec->next;
	if (rec->next)rec->next->last = rec->last;
	rec->next = NULL;
	rec->last = NULL;
	rec->rec->acc = NULL;
	rec->rec->book = NULL;
	free(rec);
}

void copyAcc(struct AccInfo* dest, struct AccInfo* src) {
	strcpy(dest->gender, src->gender);
	dest->id = src->id;
	strcpy(dest->newPwd, src->newPwd);
	strcpy(dest->newUserName, src->newUserName);
	strcpy(dest->newWork , src->newWork);
	dest->priority = src->priority;
	strcpy(dest->pwd, src->pwd);
	dest->request = src->request;
	strcpy(dest->userName, src->userName);
	strcpy(dest->work, src->work);

}

void deleteFromLib(struct AccInfo* acc, struct Library* lib) {
	struct AccList* ptr;
	if (acc->request == -1) {
		ptr = lib->allAcc->chgHead->next;
		while (ptr) {
			if (ptr->acc->id == acc->id) {
				ptr->acc = NULL;
				deleteAcc(ptr);
				lib->allAcc->numOfChg--;
				break;
			}
			ptr = ptr->next;
		}
		ptr = lib->allAcc->allHead->next;
		while (ptr) {
			if (ptr->acc->id == acc->id) {
				deleteAcc(ptr);
				lib->allAcc->numOfall--;
				break;
			}
			ptr = ptr->next;
		}
	}
	else if(acc->request == 1) {
		ptr = lib->allAcc->newHead->next;
		while (ptr) {
			if (ptr->acc->id == acc->id) {
				ptr->acc = NULL;
				deleteAcc(ptr);
				lib->allAcc->numOfNews--;
				break;
			}
			ptr = ptr->next;
		}
	}
	

}

int searchRecord(struct Control* ctrl, struct AccInfo* user, struct RecList* head) {
	struct RecList* ptr = head->next;
	while (ptr) {
		if (ptr->rec->acc->id == user->id
			&& ptr->rec->book->id == ctrl->item->bookPtr->book->id)
			return 1;
		ptr = ptr->next;
	}
	return 0;
}

void sortBooks(struct Control* ctrl, struct Library* lib)
{
	struct BookList* newHead = (struct BookList*)malloc(sizeof(struct BookList));
	/*temp new head*/
	newHead->next = newHead->last = NULL;
	newHead->book = NULL;
	struct BookList* ptr = NULL;

	/*insertion sort*/
	while (lib->allBook->allHead->next) {
		ptr = lib->allBook->allHead->next;
		lib->allBook->allHead->next = ptr->next;
		bookInsertAscend(ptr, newHead, ctrl->view);
	}
	lib->allBook->allHead->next = newHead->next;

	ctrl->pager->page = 0;
	ctrl->pager->bookPtr = lib->allBook->allHead->next;
}

int calMaxPage(const int num, const int limit) {
	if (num % limit == 0)
		return num / limit - 1;
	else return num / limit;
}

void bookInsertAscend(struct BookList* book, struct BookList* head, int view)
{
	struct BookList* ptr = head;
	while (ptr->next) {
		/*sort books according to views*/
		if (view == VIEWBOOKID) {
			if (book->book->id <= ptr->next->book->id) 
				break;
		}
		else if (view == VIEWBOOKAUTHOR) {
			if (strcmp(book->book->authors[0], ptr->next->book->authors[0]) <= 0)
				break;
		}
		else if (view == VIEWBOOKKEYWD) {
			if (strcmp(book->book->keywords[0], ptr->next->book->keywords[0]) <= 0)
				break;
		}
		else if (view == VIEWBOOKNAME) {
			if (strcmp(book->book->bookName, ptr->next->book->bookName) <= 0)
				break;
		}
		else if (view == VIEWBOOKPUB) {
			if (strcmp(book->book->publisher, ptr->next->book->publisher) <= 0)
				break;
		}
		else if (view == VIEWBOOKPUBDATE) {
			if (atoi(book->book->pubDate) <= atoi(ptr->next->book->pubDate))
				break;
		}
		else if (view == VIEWBOOKTYPE) {
			if (strcmp(book->book->type, ptr->next->book->type) <= 0)
				break;
		}
		ptr = ptr->next;
	}
	book->next = ptr->next;
	book->last = ptr;
	if (ptr->next) ptr->next->last = book;
	ptr->next = book;
}

void accInsertAscend(struct AccList* accs, struct AccList* head, int view)
{
	struct AccList* ptr = head;
	/*sort account according to views*/
	while (ptr->next) {
		if (view == VIEWACCID) {
			if (accs->acc->id <= ptr->next->acc->id)
				break;
		}
		else if (view == VIEWACCNAME) {
			if (strcmp(accs->acc->userName, ptr->next->acc->userName) <= 0)
				break;
		}
		else if (view == VIEWACCWORK) {
			if (strcmp(accs->acc->work, ptr->next->acc->work) <= 0)
				break;
		}
		ptr = ptr->next;
	}
	accs->next = ptr->next;
	accs->last = ptr;
	if (ptr->next) ptr->next->last = accs;
	ptr->next = accs;
}

int bookSerchFun(struct Control* ctrl, struct BookList* books, struct BookList* head, char* text) {
	struct BookList* ptr = books;
	int count = 0;
	while (ptr) {
		int found = 0;
		if (ctrl->view == VIEWBOOKAUTHOR) {
			for (int i = 0; i < NUMOFAUTHOR; i++) {
				if (FindString(text, ptr->book->authors[i],0) != -1) {
					found = 1;
				}		
			}
		}
		else if (ctrl->view == VIEWBOOKID) {
			if (ptr->book->id == atoi(text)) {
				struct BookList* found = (struct BookList*)malloc(sizeof(struct BookList));
				found->book = ptr->book;
				found->next = NULL;
				found->last = head;
				head->next = found;
				return 1;
			}
		}
		else if (ctrl->view == VIEWBOOKKEYWD) {
			for (int i = 0; i < NUMOFKEY; i++) {
				if (FindString(text, ptr->book->keywords[i], 0) != -1) {
					found = 1;
				}
			}
		}
		else if (ctrl->view == VIEWBOOKNAME) {
			if (FindString(text, ptr->book->bookName, 0) != -1) {
				found = 1;
			}
		}
		if (found == 1) {
			struct BookList* bookptr = (struct BookList*)malloc(sizeof(struct BookList));
			bookptr->book = ptr->book;
			bookptr->last = NULL;
			bookptr->next = NULL;
			bookInsertAscend(bookptr, head, ctrl->view);
			count++;
		}
		ptr = ptr->next;
	}
	return count;
}

int accSerchFun(struct Control* ctrl, struct AccList* accs, struct AccList* head, char* text) {
	struct AccList* ptr = accs;
	int count = 0;
	while (ptr) {
		int found = 0;
		if (ctrl->view == VIEWACCID) {
			if (ptr->acc->id == atoi(text)) {
				struct AccList* accPtr = (struct AccList*)malloc(sizeof(struct AccList));
				accPtr->acc = ptr->acc;
				accPtr->last = head;
				accPtr->next = NULL;
				head->next = accPtr;
				return 1;
			}
		}
		else if (ctrl->view == VIEWACCNAME) {
			if (FindString(text, ptr->acc->userName, 0) != -1)
				found = 1;
	
		}
		else if (ctrl->view == VIEWACCWORK) {
			if (FindString(text, ptr->acc->work, 0) != -1) 
				found = 1;
		}
		if (found == 1) {
			
			struct AccList* accptr = (struct AccList*)malloc(sizeof(struct AccList));
			accptr->acc = ptr->acc;
			accptr->last = NULL;
			accptr->next = NULL;
			accInsertAscend(accptr, head, ctrl->view);
			count++;
		}
		ptr = ptr->next;
	}
	return count;
}