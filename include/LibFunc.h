#ifndef _LIBFUNC_H
#define _LIBFUNC_H


#include "resource.h"
void copyBook(struct BookInfo* newb, struct BookInfo* oldb);


/*initialize account info*/
void InitAcc(struct AccInfo* acc);

/*initialize record info*/
void InitRec(struct RecInfo* rec);

/*initialize book info*/
void InitBook(struct BookInfo* book);

/*initialize account dlinked list pointers in a library*/
void InitAccFolder(struct AccFolder* folder);

/*initialize record dlinked list pointers in a library*/
void InitRecFolder(struct RecFolder* folder);

/*initialize book dlinked list pointers in a library*/
void InitBookFolder(struct BookFolder* folder);

/*initialize pointers inside library*/
void InitLibrary(struct Library* lib);

/*initialize page control*/
void InitPager(struct Pager* pager);

/*initialize selector control*/
void InitSelector(struct Selector* select);

/*initialize main control*/
void InitControl(struct Control* ctrl);

/*free data from library*/
void ResetLibrary(struct Library* lib);

/*free data from account dlinked lists in library*/
void FreeAccFolder(struct AccFolder* folder);

/*free data from record dlinked lists in library*/
void FreeRecFolder(struct RecFolder* folder);

/*free data from book dlinked lists in library*/
void FreeBookFolder(struct BookFolder* folder);

/*enter next window*/
void nextLvl(struct Control* ctrl, char* s);

/*change status bar display*/
void changeStatus(struct Control* ctrl, char* s);

/*go previous level*/
void exitLvl(struct Control* ctrl, char* s);

/*change pages showing books*/
void changePageBook(struct Pager* pager, int limit);

/*change pages showing accounts*/
void changePageAcc(struct Pager* pager, int limit);

/*change pages showing records*/
void changePageRec(struct Pager* pager, int limit);

/*show message window*/
int showMsgBox(struct winFrame* f, char* msg);

/*show about software message window*/
int AboutSoftware(struct winFrame* frame, struct Control* ctrl);

/*calculate pages for user guide*/
int calPage(double h, int rows);

/*account registration operation*/
void registerAcc(struct AccInfo* accTemp, struct Library* lib);

/*approve account edit*/
void approveAccChg(struct Control* ctrl, struct Library* lib);

/*approve account registration*/
void approveAccReg(struct Control* ctrl, struct Library* lib);

/*approve book borrow request*/
void approveBorrow(struct Control* ctrl, struct Library* lib);

/*approve book return request*/
void approveReturn(struct Control* ctrl, struct Library* lib);

/*reject borrow request, remove request from request list*/
void rejectBorrow(struct Control* ctrl, struct Library* lib);

/*reject return request, remove request from request list*/
void rejectReturn(struct Control* ctrl, struct Library* lib);

/*make an account edit application, add application to application list*/
void accEditApplication(struct AccInfo* temp, struct AccInfo* user,struct Library* lib);

/*delete account info from library(all/chg/news)*/
void deleteFromLib(struct AccInfo* acc, struct Library* lib);

/*add new book to library*/
void addBook(struct BookInfo* book, struct Library* lib);

/*insert record to a record list*/
void insertRec(struct RecList* rec, struct RecList* head);

/*create new library*/
int fileMenuNewLib(const char* name, const char* dir);

/*make borrow application and insert the new application to application dlinked list*/
void borrowApplication(struct Control* ctrl,struct AccInfo* user, struct Library* lib);

/*make return application and insert the new application to application dlinked list*/
void returnApplication(struct Control* ctrl, struct AccInfo* user, struct Library* lib);

/*verify account for login, if username and password match
data in system, return account pointer,
else return NULL*/
struct AccInfo* verifyAcc(struct AccInfo* accTemp, struct AccList* head);

/*delete book from library*/
void deleteBook(int bookid, struct Library* lib);

/*insert book to the beginning of a dlinked list*/
void insertBook(struct BookList* book, struct BookList* head);

/*insert account to the beginning of a dlinked list*/
void insertAcc(struct AccList* acc, struct AccList* head);

/*search if record already exits*/
int searchRecord(struct Control* ctrl, struct AccInfo* user, struct RecList* rec);

/*insert book to a dlinked list in ascending order*/
void bookInsertAscend(struct BookList* book, struct BookList* head, int view);

/*insert account to a dlinked list in ascending order*/
void accInsertAscend(struct AccList* accs, struct AccList* head, int view);

/*sort books in library in ascending order according to current view*/
void sortBooks(struct Control* ctrl, struct Library* lib);

/*sort accs in library in ascending order according to current view
note: to be implemented when needed*/
void sortAccs(struct Control* ctrl, struct Library* lib);

/*given number of item "num" and show "limit", calculate the maximum page*/
int calMaxPage(const int num, const int limit);

/*search books that contain "text" according to viewing option,
and make a search result dlinked list*/
int bookSerchFun(struct Control* ctrl, struct BookList* books, struct BookList* head, char* text);

/*search accounts that contain "text" according to viewing option,
and make a search result dlinked list*/
int accSerchFun(struct Control* ctrl, struct AccList* accs, struct AccList* head, char* text);

/*log off*/
int existAcc(struct AccInfo* accTemp,struct Library* lib);

/*delete account from account dlinked list*/
void deleteAcc(struct AccList* acc);

/*delete record from record dlinked list*/
void deleteRec(struct RecList* rec);

/*copy account info from src to dest*/
void copyAcc(struct AccInfo* dest, struct AccInfo* src);
#endif