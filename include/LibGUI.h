#ifndef _MENUGUI_H
#define _MENUGUI_H

#include "resource.h"




#define DEFAULTCOLOR "Blue","Blue","Red","Red",NOFILL
#define NAMESIZE 20

void drawMenu(double width, double height, double fH, struct Control* ctrl);
void drawStatus(struct Control* ctrl, struct AccInfo* user);
void loginUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* f);
void registerUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* f);
void newBookUI(struct Control* ctrl, struct winFrame* frame, struct BookInfo* book);
void showBookUI(struct Control* ctrl, struct winFrame* frame, int limit, char* option);
void showBookEditUI(struct Control* ctrl, struct winFrame* frame, struct BookInfo* book);
int drawOperationRectangle(double x, double y, double w, double h, char* title, char* option1, char* option2);
int drawMsgRectangle(double x, double y, double w, double h, char* title, char* msg, char* option);
void newLibraryUI(struct Control* ctrl, const struct winFrame* frame, char* name);
bool validNewLibrary(const string s, int size);
void openFileUI(struct Control* ctrl, const struct winFrame* frame, const char* libDir, char* newDir);
void returnToMainFrame(struct Control* ctrl);
void drawBackGround(double x, double y, double w, double h, string color);
void accApplicationUI(struct Control* ctrl, struct winFrame* frame,int limit);
void bookApplicationUI(struct Control* ctrl, struct winFrame* frame, int limit);
void AccMenuAdminEditUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* frame, char* option);
void AccMenuEditUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* frame,char* option);
void AccMenuEditSelectUI(struct Control* ctrl, struct winFrame* frame,char* option, int limit);
void helpUI(struct Control* ctrl, struct winFrame* frame, char** s, int limit, int rows);
void setDateUI(struct Control* ctrl, struct RecInfo* rec, struct winFrame* f);
void bookSearchUI(struct Control* ctrl, char* text,struct winFrame* frame);
void accSearchUI(struct Control* ctrl, char* text, struct winFrame* frame);
void loadingUI(struct winFrame* frame);
void displayAccUI(struct Control* ctrl, struct winFrame* f);
void displayBookUI(struct Control* ctrl, struct winFrame* f);
#endif