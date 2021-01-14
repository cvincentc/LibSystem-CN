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
#include <filesystem>
#include <fileapi.h>

#include <time.h>

#include "imgui.h"
#include "LibGUI.h"
#include "LibFunc.h"

char* menuListFile[] = { 
	"�ļ�",
	"ͼ����½�",
	"��",
	"���� | Ctrl-S",
	"�˳� | Ctrl-E" };	//menu1
char* menuListInventory[] = { //menu2
	"ͼ��",
	"����",
	"��ʾ",
	"�޸�",
	"ɾ��ͼ��" };

char* menuListIO[] = { //menu3
	"�軹",
	"����",
	"����",
	"���"};			

char* menuListAccount[] = { //menu4
	"�û�",
	"��¼ | Ctrl-L",
	"ע��","���",
	"�޸�",
	"ɾ��", 
	"ע�� | Ctrl-Q"};

char* menuSearch[] = {
	"����",
	"ͼ�����",
	"�û�����" };

char* menuListHelp[] = { //menu5
	"����",
	"���ڱ����",
	"ʹ�÷��� | Ctrl-H" };		

char** menus[] = { menuListFile,menuListInventory,menuListIO,menuListAccount, menuSearch, menuListHelp };
const int menu1Count = 5;
const int menu2Count = 5;
const int menu3Count = 4;
const int menu4Count = 7;
const int menu5Count = 3;
const int menu6Count = 3;



void drawMenu(double width, double height, double fH, struct Control* ctrl)
{
	double x = 0;
	double y = height;
	double h = fH * 1.5;
	double w = TextStringWidth("����") * 2; //�ؼ����
	double wlist = TextStringWidth("������� | Ctrl + X") * 1.2;
	int selection;
	// menu bar
	drawMenuBar(0, y - h, width-.01, h);

	if (ctrl->menuLvl==MAINFRAME){
		setMenuColors("Blue", "Blue", "Red", "Red", 0);
		//�ļ��˵�
		selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, menu1Count);
		if (selection > 0 && selection < menu1Count)
		{
			ctrl->menuSelect = FILEMENU;
			ctrl->optSelect = selection;
		}
		//ͼ��˵�
		selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListInventory, menu2Count);
		if (selection > 0 && selection < menu2Count)
		{
			ctrl->menuSelect = BOOKMENU;
			ctrl->optSelect = selection;
		}

		//�軹�˵�
		selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListIO, menu3Count);
		if (selection > 0 && selection < menu3Count)
		{
			ctrl->menuSelect = IOMENU;
			ctrl->optSelect = selection;
		}

		//�û��˵�
		selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListAccount, menu4Count);
		if (selection > 0 && selection < menu4Count)
		{
			ctrl->menuSelect = ACCMENU;
			ctrl->optSelect = selection;
		}

		//���Ҳ˵�
		selection = menuList(GenUIID(0), x + 4 * w, y - h, w, wlist, h, menuSearch, menu5Count);
		if (selection > 0 && selection < menu5Count)
		{
			ctrl->menuSelect = SEARCHMENU;
			ctrl->optSelect = selection;
		}

		//�����˵�
		selection = menuList(GenUIID(0), x + 5 * w, y - h, w, wlist, h, menuListHelp, menu6Count);
		if (selection > 0 && selection < menu6Count)
		{
			ctrl->menuSelect = HELPMENU;
			ctrl->optSelect = selection;
		}
	}
	else
	{
		setMenuColors("Blue", "Blue", "Blue", "Blue", 0);
		//�ļ��˵�
		selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, menu1Count);
		if(selection == 3 || selection == 4){
			ctrl->menuSelect = FILEMENU;
			ctrl->optSelect = selection;
			ctrl->menuLvl = MAINFRAME;
		}

		//ͼ��˵�
		selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListInventory, menu2Count);

		//�軹�˵�
		selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListIO, menu3Count);

		//�û��˵�
		selection = menuList(GenUIID(0), x + 3 * w, y - h, w, wlist, h, menuListAccount, menu4Count);
		if (selection == 1 || selection == 5) {
			ctrl->menuSelect = ACCMENU;
			ctrl->optSelect = selection;
			ctrl->menuLvl = MAINFRAME;
		}

		//���Ҳ˵�
		selection = menuList(GenUIID(0), x + 4 * w, y - h, w, wlist, h, menuSearch, menu5Count);

		//�����˵�
		selection = menuList(GenUIID(0), x + 5 * w, y - h, w, wlist, h, menuListHelp, menu6Count);
		if (selection == 2) {
			ctrl->menuSelect = HELPMENU;
			ctrl->optSelect = selection;
			ctrl->menuLvl = MAINFRAME;
		}

	}
	//ͼ�깤��
	double winwidth = GetWindowWidth();
	setButtonColors("White", "Blue", "White", "Red", 0);
	x = winwidth - w;
	y = y - 3 * h;
	if (button(GenUIID(0), x, y, w, h, "��¼")) {
		ctrl->menuSelect = ACCMENU;
		ctrl->optSelect = 1;
		ctrl->menuLvl = MAINFRAME;
	}
	MovePen(x + w * .9, y + h / 2);
	DrawEllipticalArc(h, h, 0, 0);

	y -= 2*h;
	if (button(GenUIID(0), x, y, w, h, "ע��")) {
		ctrl->menuSelect = ACCMENU;
		ctrl->optSelect = 6;
		ctrl->menuLvl = MAINFRAME;
	}
	MovePen(x + w * .9, y + h / 2);
	DrawEllipticalArc(h, h, 0, 0);

	y -= 2 * h;
	if (button(GenUIID(0), x, y, w, h, "����")) {
		ctrl->menuSelect = FILEMENU;
		ctrl->optSelect = 3;
		ctrl->menuLvl = MAINFRAME;
	}
	MovePen(x + w * .9, y + h / 2);
	DrawEllipticalArc(h, h, 0, 0);

	y -= 2 * h;
	if (button(GenUIID(0), x, y, w, h, "�˳�")) {
		ctrl->menuSelect = FILEMENU;
		ctrl->optSelect = 4;
		ctrl->menuLvl = MAINFRAME;
	}
	MovePen(x + w * .9, y + h / 2);
	DrawEllipticalArc(h, h, 0, 0);

	y -= 2 * h;
	if (button(GenUIID(0), x, y, w, h, "ʹ��˵��")) {
		ctrl->menuSelect = HELPMENU;
		ctrl->optSelect = 2;
		ctrl->menuLvl = MAINFRAME;
	}
	MovePen(x + w*1.3, y + h / 2);
	DrawEllipticalArc(h*2, h, 0, 0);
	setButtonColors("Blue", "Blue", "Red", "Red", 0);
}

void AccMenuEditSelectUI(struct Control* ctrl, struct winFrame* f, char* option, int limit) {
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double yindent = GetFontHeight() * 1.5;
	double xindent = w / 16;
	int numOfViews = 2;
	double buttonWidth = TextStringWidth("��һҳ");
	double buttonWidth2 = TextStringWidth(option);
	double buttonHeight = GetFontHeight() * 2;
	static int pressed = NOPRESS;
	
	//ok/cancel option
	pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (ctrl->buttonPressed == NOPRESS && pressed != NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
		//return;
	}


	//last/next page
	x = f->x + f->w - 2 * xindent;
	y = y + h - 2 * yindent;
	if (button(GenUIID(0), x, y, buttonWidth, buttonHeight, "��һҳ")) {
		if (ctrl->buttonPressed == NOPRESS) {
			ctrl->pager->pageOption = 1;
		}
	}
	x = x - 2 * xindent;
	if (button(GenUIID(0), x, y, buttonWidth, buttonHeight, "��һҳ")) {
		if (ctrl->buttonPressed == NOPRESS) {
			ctrl->pager->pageOption = -1;
		}
	}
	SetPenColor(FRAMECOLOR);

	//draw a box for headers
	double z = f->w / 8;
	x = f->x + z / 10;
	y = f->y + h - yindent * 4;
	MovePen(f->x, f->y + h - yindent * 3);
	DrawLine(w, 0);
	char* fields[] = { "�û���:","�Ա�:","������λ:","����:" };
	for (int i = 0; i < 4; i++) {
		MovePen(x, y);
		DrawTextString(fields[i]);
		if (i == 1) x += z;
		else x += (2 * z);
	}
	x = f->x;
	y = f->y;
	MovePen(x, y + h - yindent * 4.5);
	DrawLine(w, 0);


	int id = 999;
	//set up showing data
	struct AccList* ptr2 = ctrl->pager->accPtr;
	y = f->y + h - yindent * 6;

	//place holder for display data
	char display[4][LEN20];

	//display data
	for (int i = 0; i < limit && ptr2; i++) {
		x = f->x;
		MovePen(x, y - yindent / 8);
		DrawLine(w, 0);
		x = x + z / 10;
		if (button(id--, f->x + w - z, y, buttonWidth2, buttonHeight, option)) {
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->item->itemNum = i + 1;
				ctrl->item->accPtr = ptr2;
			}
		}
		strcpy(display[0], ptr2->acc->userName);
		strcpy(display[1], ptr2->acc->gender);
		strcpy(display[2], ptr2->acc->work);
		strcpy(display[3], ptr2->acc->pwd);
		for (int i = 0; i < 4; i++) {
			MovePen(x, y);
			DrawTextString(display[i]);
			if (i == 1) x += z;
			else x += (2 * z);
		}
		SetPenColor(FRAMECOLOR);
		y -= yindent * 1.5;
		ptr2 = ptr2->next;

	}

	/*display page number*/
	char p[15] = "page:";
	char n[5];
	_itoa(ctrl->pager->page + 1, n, 10);
	strcat(p, n);
	MovePen(f->x, f->y);
	DrawTextString(p);

	/*display selected*/
	char select[30] = "δѡ��";
	if (ctrl->item->itemNum != 0) {
		//strcat(select, "ͨ��");
		strcpy(select, option);
		strcat(select, _itoa(ctrl->item->itemNum, n, 10));
	}
	
	//display item select number
	MovePen(f->x, f->y + yindent);
	DrawTextString(select);
}

void AccMenuEditUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* f, char* option)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double xindent = w / 8;
	double yindent = h / 12;
	double fontHeight = GetFontHeight() * 1.5;
	char* fields[] = { "���û���:","���û���:","���˺�����:","���˺�����:","�ɹ�����λ:","�¹�����λ:" };
	char* accFields[] = { acc->userName,acc->newUserName,acc->pwd,acc->newPwd,acc->work,acc->newWork };

	int len, temp=0, id = 88;
	double widths[] = { TextStringWidth(fields[0]),TextStringWidth(fields[2]),TextStringWidth(fields[4]) };
	static int pressed = NOPRESS;

	//ok/cancel button
	pressed = drawOperationRectangle(x, y, w, h, "", option, "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	if (ctrl->buttonPressed == NOPRESS)
		len = LEN20;
	else len = 0;

	/*display now showing*/
	char headder[50] = "";
	MovePen(f->x, f->y + h - fontHeight);
	DrawTextString(strcat(headder, "�޸��˺�"));
	x = x + 2 * xindent;
	y = y + h - 3 * yindent;
	for (int i = 0; i < 6; i++) {
		if ((i + 1) % 2 == 1)temp = 0;
		else temp = len;
		textbox(id--, x, y -= yindent, w/3, fontHeight, accFields[i], temp);
		MovePen(x - widths[i / 2], y+fontHeight*.25);
		DrawTextString(fields[i]);
	}
}

void AccMenuAdminEditUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* f, char* option) {
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double xindent = w / 8;
	double yindent = h / 12;
	double fontHeight = GetFontHeight() * 1.5;
	char* fields[] = { "���û���:","���û���:","���˺�����:","���˺�����:","�ɹ�����λ:","�¹�����λ:" };
	char* accFields[] = { acc->userName,acc->newUserName,acc->pwd,acc->newPwd,acc->work,acc->newWork };

	int len, temp = 0, id = 88;
	double widths[] = { TextStringWidth(fields[0]),TextStringWidth(fields[2]),TextStringWidth(fields[4]) };
	static int pressed = NOPRESS;

	//ok/cancel buttion
	pressed = drawOperationRectangle(x, y, w, h, "", option, "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}

	//if button pressed, lock text box
	if (ctrl->buttonPressed == NOPRESS)
		len = LEN20;
	else len = 0;

	/*display now showing*/
	char headder[50] = "";
	MovePen(f->x, f->y + h - fontHeight);
	DrawTextString(strcat(headder, "�޸��˺�"));
	x = x + 2 * xindent;
	y = y + h - 3 * yindent;
	for (int i = 0; i < 6; i++) {
		textbox(id--, x, y -= yindent, w / 3, fontHeight, accFields[i], len);
		MovePen(x - widths[i / 2], y + fontHeight * .25);
		DrawTextString(fields[i]);
	}
}

void loginUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* f)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double textboxHeight = GetFontHeight() * 1.5;
	double yindent = h / 4;
	double xindent = w / 5;
	int len1,len2;
	static int pressed = NOPRESS;
	
	//ok/cancel button
	pressed = drawOperationRectangle(x, y, w, h, "", "��¼", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	if (ctrl->buttonPressed == NOPRESS) {
		len1 = len2 = LEN20;
	}
	else {
		len1 = len2 = 0;
	}
	textbox(GenUIID(0), x + xindent * 2, y + yindent * 3, xindent * 2, textboxHeight, acc->userName, len1);
	textbox(GenUIID(0), x + xindent * 2, y + yindent * 2, xindent * 2, textboxHeight, acc->pwd, len2);
	SetPenColor(FRAMECOLOR);
	x = x + xindent;
	y = y + yindent * 2 + textboxHeight / 3;
	MovePen(x, y);
	DrawTextString("Password:");
	MovePen(x, y + yindent);
	DrawTextString("Username:");
}

void registerUI(struct Control* ctrl, struct AccInfo* acc, struct winFrame* f)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double textboxHeight = GetFontHeight() * 1.5;
	double yindent = h / 7;
	double xindent = w / 6;
	char* fields[] = { "�û���:","�Ա�(Male/Female):","������λ:","����:","ȷ������:" };
	int fieldNum = 5;
	int len1, len2, len3, id=0;
	static int pressed = NOPRESS;
	if (pressed == NOPRESS) pressed = drawOperationRectangle(x, y, w, h, "", "ע��", "ȡ��");
	else drawOperationRectangle(x, y, w, h, "", "ע��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	if (ctrl->buttonPressed == NOPRESS) {
		len1 = len2 = len3 = LEN20;
	}
	else {
		len1 = len3 = len2 = 0;
		
	}

	//instruction
	MovePen(x + xindent * .2, y + h - textboxHeight);
	DrawTextString("����20�������ַ�");

	//textboxes for data input
	textbox(GenUIID(0), f->x + xindent * 2, f->y + yindent * 6, xindent * 3, textboxHeight, acc->userName, len1+1);
	y = y + 6 * yindent + textboxHeight / 3;
	MovePen(x + xindent * 2 -TextStringWidth(fields[0]), y);
	DrawTextString(fields[0]);

	textbox(GenUIID(0), f->x + xindent * 2, f->y + yindent * 5, xindent * 3, textboxHeight, acc->gender, len3+1);
	y = y - yindent;
	MovePen(x + xindent * 2 - TextStringWidth(fields[1]), y);
	DrawTextString(fields[1]);

	textbox(GenUIID(0), f->x + xindent * 2, f->y + yindent * 4, xindent * 3, textboxHeight, acc->work, len1+1);
	y = y - yindent;
	MovePen(x + xindent * 2 - TextStringWidth(fields[2]), y);
	DrawTextString(fields[2]);

	textbox(GenUIID(0), f->x + xindent * 2, f->y + yindent * 3, xindent * 3, textboxHeight, acc->pwd, len2+1);
	y = y - yindent;
	MovePen(x + xindent * 2 - TextStringWidth(fields[3]), y);
	DrawTextString(fields[3]);

	textbox(GenUIID(0), f->x + xindent * 2, f->y + yindent * 2 , xindent * 3, textboxHeight, acc->newPwd, len2+1);
	y = y - yindent;
	MovePen(x + xindent * 2 - TextStringWidth(fields[4]), y);
	DrawTextString(fields[4]);

	SetPenColor(FRAMECOLOR);
}

void bookApplicationUI(struct Control* ctrl, struct winFrame* f, int limit)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double yindent = GetFontHeight() * 1.5;
	double xindent = w / 16;
	char* views[] = { "��������","��������" };
	double buttonWidth1 = TextStringWidth(views[0]);
	double buttonWidth2 = TextStringWidth("��һҳ");
	double buttonWidth3 = TextStringWidth("ͨ��");
	double buttonHeight = GetFontHeight() * 2;
	static int pressed = NOPRESS;

	pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
		//return;
	}

	y = y + h - buttonHeight * 2;
	x = x + xindent;
	if (button(GenUIID(0), x, y, buttonWidth1, buttonHeight, "��������")) {
		if (ctrl->buttonPressed == NOPRESS) {
			if (ctrl->view != VIEWBORROWAPP) {
				ctrl->chgView = 1;
				ctrl->view = VIEWBORROWAPP;
			}
		}
	}
	x = x + buttonWidth1 * 1.5;
	if (button(GenUIID(0), x, y, buttonWidth1, buttonHeight, "��������")) {
		if (ctrl->buttonPressed == NOPRESS) {
			if (ctrl->view != VIEWRETURNAPP) {
				ctrl->chgView = 1;
				ctrl->view = VIEWRETURNAPP;
			}
		}
	}
	x = f->x + w - 2 * xindent;
	if (button(GenUIID(0), x, y, buttonWidth2, buttonHeight, "��һҳ")) {
		if (ctrl->buttonPressed == NOPRESS) {
			if(ctrl->pager->page < ctrl->pager->maxPage)
				ctrl->pager->pageOption = 1;
		}
	}

	x = x - 2 * xindent;
	if (button(GenUIID(0), x, y, buttonWidth2, buttonHeight, "��һҳ")) {
		if (ctrl->buttonPressed == NOPRESS) {
			if (ctrl->pager->page > 0)
				ctrl->pager->pageOption = -1;
		}
	}
	SetPenColor(FRAMECOLOR);

	double z = f->w / 8;
	x = f->x + z / 10;
	y = f->y + h - yindent * 4;
	MovePen(f->x, f->y + h - yindent * 3);
	DrawLine(w, 0);
	char* fields[] = { "�û�id:","�û���:","ͼ��id:","ͼ����" };
	for (int i = 0; i < 4; i++) {
		MovePen(x, y);
		DrawTextString(fields[i]);
		if (i == 1) x += z;
		else x += (2 * z);
	}
	x = f->x;
	y = f->y;
	MovePen(x, y + h - yindent * 4.5);
	DrawLine(w, 0);
	int id = 999;
	struct RecList* ptr2 = ctrl->pager->recPtr;
	
	y = f->y + h - yindent * 6;
	//x = x + z / 10;

	char display[4][LEN20];

	for (int i = 0; i < limit && ptr2; i++) {
		x = f->x;
		MovePen(x, y - yindent / 8);
		DrawLine(w, 0);
		x = x + z / 10;
		if (button(id--, x + w - z, y, buttonWidth3, buttonHeight, "ͨ��")) {
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->item->itemNum = i + 1;
				ctrl->item->recPtr = ptr2;
				ctrl->op = 1;
			}
		}
		if (button(id--, x + w - z * .5, y, buttonWidth3, buttonHeight, "���")) {
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->item->itemNum = i + 1;
				ctrl->item->recPtr = ptr2;
				ctrl->op = -1;
			}
		}
		SetPenColor(FRAMECOLOR);
		char n[10] = { "" };
		strcpy(display[0], _itoa(ptr2->rec->acc->id, n, 10));
		strcpy(display[1], ptr2->rec->acc->userName);
		strcpy(display[2], _itoa(ptr2->rec->book->id, n, 10));
		strcpy(display[3], ptr2->rec->book->bookName);
		for (int i = 0; i < 4; i++) {
			MovePen(x, y);
			DrawTextString(display[i]);
			if (i == 1) x += z;
			else x += (2 * z);
		}
		y -= yindent * 1.5;
		ptr2 = ptr2->next;

	}
	/*display page number*/
	char p[15] = "page:";
	char n[5];
	_itoa(ctrl->pager->page + 1, n, 10);
	strcat(p, n);
	MovePen(f->x, f->y);
	DrawTextString(p);

	/*display selected*/
	char select[30] = "δѡ��";
	if (ctrl->op == 1) {
		strcat(select, "ͨ��");
	}
	else if (ctrl->op == -1) {
		strcat(select, "���");
	}
	_itoa(ctrl->item->itemNum, n, 10);
	strcat(select, n);
	MovePen(f->x, f->y + yindent);
	DrawTextString(select);

	/*display now showing*/
	char headder[50] = "";
	MovePen(f->x, f->y + h - yindent);
	DrawTextString(strcat(headder, views[ctrl->view - VIEWBORROWAPP]));
}

void accApplicationUI(struct Control* ctrl, struct winFrame* f, int limit) {
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double yindent = GetFontHeight() * 1.5;
	double xindent = w / 16;
	char views[2][15] = { "��ע���û�","������Ϣ�û�"};
	//int numOfViews = 2;
	double buttonWidth1 = TextStringWidth(views[1]);
	double buttonWidth2 = TextStringWidth("��һҳ");
	double buttonWidth3 = TextStringWidth("ͨ��");
	double buttonHeight = GetFontHeight() * 2;
	static int pressed = NOPRESS;

	pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	
	//view acc option buttion
	/*
	x = f->x + xindent;
	
	for (int i = VIEWNEWACC; i < VIEWNEWACC + 2; i++) {
		if (i == 0)x = x + xindent;
		else x = x + buttonWidth1*1.5;
		if (button(GenUIID(0) + i, x, y, buttonWidth1, buttonHeight, views[i])) {
			if (ctrl->buttonPressed == NOPRESS) {
				if (ctrl->view != i) {
					ctrl->chgView = 1;
					ctrl->view = i;
				}
			}
		}
	}
	*/
	y = y + h - buttonHeight * 2;
	x = x + xindent;
	if (button(GenUIID(0), x, y, buttonWidth1, buttonHeight, "��ע���û�")) {
		if (ctrl->buttonPressed == NOPRESS) {
			if (ctrl->view != VIEWNEWACC) {
				ctrl->chgView = 1;
				ctrl->view = VIEWNEWACC;
			}
		}
	}
	x = x + buttonWidth1 * 1.5;
	if (button(GenUIID(0), x, y, buttonWidth1, buttonHeight, "������Ϣ�û�")) {
		if (ctrl->buttonPressed == NOPRESS) {
			if (ctrl->view != VIEWCHGACC) {
				ctrl->chgView = 1;
				ctrl->view = VIEWCHGACC;
			}
		}
	}
	x = f->x + w - 2 * xindent;
	if (button(GenUIID(0), x, y, buttonWidth2, buttonHeight, "��һҳ")) {
		if (ctrl->buttonPressed == NOPRESS) {
			ctrl->pager->pageOption = 1;
		}
	}
	
	x = x - 2 * xindent;
	if (button(GenUIID(0), x, y, buttonWidth2, buttonHeight, "��һҳ")) {
		if (ctrl->buttonPressed == NOPRESS) {
			ctrl->pager->pageOption = -1;
		}
	}
	/*
	struct AccList* ptr = AccCtrl->accPtr->next;
	for (int i = 0; i < limit && ptr; i++) {
		if (button(GenUIID(0), x, y, buttonWidth2, buttonHeight, "��һҳ")) {
			if (menuCtrl->buttonPressed == NOPRESS) {
				AccCtrl->pageOption = 1;
			}
		}
	}*/
	SetPenColor(FRAMECOLOR);
	//v
	//char buf[] = "01234567890123456789";
	//double sepLen = TextStringWidth(buf);
	
	double z = f->w / 8;
	x = f->x + z/10;
	y = f->y + h - yindent*4;
	MovePen(f->x, f->y + h - yindent * 3);
	DrawLine(w, 0);
	char* fields[] = { "�û���:","�Ա�:","������λ:","����:"};
	for (int i = 0; i < 4; i++) {
		MovePen(x, y);
		DrawTextString(fields[i]);
		if (i == 1) x += z;
		else x += (2 * z);
	}
	x = f->x;
	y = f->y;
	MovePen(x, y + h - yindent * 4.5);
	DrawLine(w,0);
	int id = 999;
	struct AccList* ptr2 = ctrl->pager->accPtr;
	y = f->y + h - yindent * 6;
	//x = x + z / 10;

	char display[4][LEN20];
	
	for (int i = 0; i < limit && ptr2; i++) {
		x = f->x;
		MovePen(x, y-yindent/8);
		DrawLine(w, 0);
		x = x + z / 10;
		if (button(id--, x + w - z, y, buttonWidth3, buttonHeight, "ͨ��")) {
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->item->itemNum = i + 1;
				ctrl->item->accPtr = ptr2;
				ctrl->op = 1;
			}
		}
		if(button(id--, x + w - z * .5, y, buttonWidth3, buttonHeight, "���")) {
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->item->itemNum = i + 1;
				ctrl->item->accPtr = ptr2;
				ctrl->op = -1;
			}
		}
		if (button(id--, x + w - z * 1.5, y, buttonWidth3, buttonHeight, "�鿴")) {
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->item->itemNum = i + 1;
				ctrl->item->accPtr = ptr2;
				ctrl->op = 2;
			}
		}
		SetPenColor(FRAMECOLOR);

		strcpy(display[0], ptr2->acc->userName);
		strcpy(display[1], ptr2->acc->gender);
		strcpy(display[2], ptr2->acc->work);
		strcpy(display[3], ptr2->acc->pwd);
		for (int i = 0; i < 4; i++) {
			MovePen(x, y);
			DrawTextString(display[i]);
			if (i == 1) x += z;
			else x += (2 * z);
		}
		y -= yindent*1.5;
		ptr2=  ptr2->next;

	}
	/*display page number*/
	char p[15] = "page:";
	char n[5];
	_itoa(ctrl->pager->page + 1, n, 10);
	strcat(p, n);
	MovePen(f->x, f->y);
	DrawTextString(p);

	/*display selected*/
	char select[30] = "δѡ��";
	if (ctrl->op == 1) {
		strcpy(select,"ͨ��");
	}
	else if(ctrl->op == -1){
		strcpy(select, "���");
	}
	else if (ctrl->op == 2) {
		strcpy(select, "�鿴");
	}
	_itoa(ctrl->item->itemNum, n, 10);
	strcat(select, n);
	MovePen(f->x, f->y + yindent);
	DrawTextString(select);

	/*display now showing*/
	char headder[50] = "";
	MovePen(f->x, f->y + h - yindent);
	DrawTextString(strcat(headder, views[ctrl->view - VIEWNEWACC]));
}


void showBookUI(struct Control* ctrl, struct winFrame* frame, int limit, char* option)
{
	double x = frame->x;
	double y = frame->y;
	double w = frame->w;
	double h = frame->h;
	double yindent = GetFontHeight() * 1.5;
	double xindent = w / 16;
	char* views[] = { "id", "����", "�ؼ���", "����", "������", "��������", "�ѽ��" ,"����"};
	double buttonWidth = TextStringWidth(views[5]);
	double buttonHeight = GetFontHeight() * 2;
	static int pressed = NOPRESS;
	char option1[] = "ȷ��";
	char option2[] = "�˳�";
	struct BookList* ptr;

	if (strcmp(option, "") != 0)strcpy(option1, option);

	//if (ctrl->buttonPressed == NOPRESS) pressed = drawOperationRectangle(x, y, w, h, "", option1, option2);
	//else drawOperationRectangle(x, y, w, h, "", option1, option2);
	pressed = drawOperationRectangle(x, y, w, h, "", option1, option2);
	if (pressed != NOPRESS && ctrl->buttonPressed==NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
		//return;
	}

	//view option button
	y = y + h - buttonHeight * 2;
	for (int i = 0; i < 8; i++) {
		if (i == 0)x = x + xindent/4;
		else x = x + 2 * xindent;
		if (button(GenUIID(0) + i, x, y, buttonWidth, buttonHeight, views[i])) {
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->view = i + VIEWBOOKID;
				//ctrl->chgView = 1;
				//curBook = SBctrl->bookHead;?
				//SBctrl->selectedItem = 0;
			}
		}
		SetPenColor(FRAMECOLOR);
	}

	//last page button
	x = frame->x + xindent;
	y -= yindent * 1.5;
	if (button(GenUIID(0), x, y, buttonWidth, buttonHeight, "��һҳ")) {
		if (ctrl->pager->page > 0 && ctrl->buttonPressed == NOPRESS) {
			ctrl->pager->pageOption = -1;
		}
	}
	x = x + xindent * 2;
	if (button(GenUIID(0), x, y, buttonWidth, buttonHeight, "��һҳ")) {
		if ((ctrl->pager->page < ctrl->pager->maxPage) && (ctrl->buttonPressed == NOPRESS)) {
			ctrl->pager->pageOption = 1;
		}
	}

	if (button(GenUIID(0), x + xindent * 2, y, buttonWidth, buttonHeight, "����")) {
		if (ctrl->buttonPressed == NOPRESS) {
			ctrl->op = SORT;
		}
	}
	SetPenColor(FRAMECOLOR);

	x = frame->x + xindent;
	char id[10];
	MovePen(frame->x, frame->y);
	char pageNum[10] = "page";
	DrawTextString(strcat(pageNum, _itoa(ctrl->pager->page + 1, id, 10)));
	char display[70];
	char displays[NUMOFKEY][LEN20];
	
	ptr = ctrl->pager->bookPtr;
	if (ctrl->view == VIEWBOOKKEYWD) {
		char* keys[] = { "keyword1","keyword2", "keyword3", "keyword4", "keyword5" };
		for (int i = 0; i < NUMOFKEY; i++) {
			MovePen(x + i * xindent * 3, y - yindent * 1);
			DrawTextString(keys[i]);
		}
	}

	if (ctrl->view == VIEWBOOKAUTHOR) {
		char* keys[] = { "Author1","Author2", "Author3"};
		for (int i = 0; i < NUMOFAUTHOR; i++) {
			MovePen(x + i * xindent * 5, y - yindent * 1);
			DrawTextString(keys[i]);
		}
	}

	MovePen(frame->x, y - yindent * 2);
	DrawLine(frame->w, 0);
	y -= yindent*2;
	for (int i = 0; (i < limit) && ptr; i++) {

		y -= yindent;
		if (strcmp(option, "") != 0)
			if (button(GenUIID(0) + i, x + w - xindent - buttonWidth, y, buttonWidth / 2.5, buttonHeight / 2, option)) {
				if (ctrl->buttonPressed == NOPRESS) {
					ctrl->item->itemNum = i + 1;
					ctrl->item->bookPtr = ptr;
				}
			}
		switch (ctrl->view) {
		case VIEWBOOKAUTHOR:
			for (int i = 0; i < NUMOFAUTHOR; i++) {
				strcpy(displays[i], ptr->book->authors[i]);
			}
			break;
		case VIEWBOOKID:
			strcpy(display, _itoa(ptr->book->id, id, 10));
			break;
		case VIEWBOOKKEYWD:
			for (int i = 0; i < NUMOFKEY; i++) {
				strcpy(displays[i], ptr->book->keywords[i]);
			}
			break;
		case VIEWBOOKNAME:
			strcpy(display, ptr->book->bookName);
			break;
		case VIEWBOOKOUT:
			//if(true) out ...
			//else out...
			if (ptr->book->status == -1)strcpy(display, "���");
			else if (ptr->book->status == 1) strcpy(display, "���");
			else if (ptr->book->status == 2)strcpy(display, "�����");
			else if (ptr->book->status == -2)strcpy(display, "�����");
			else strcpy(display, "����");
			break;
		case VIEWBOOKPUB:
			strcpy(display, ptr->book->publisher);
			break;
		case VIEWBOOKPUBDATE:
			strcpy(display, ptr->book->pubDate);
			break;
		case VIEWBOOKTYPE:
			strcpy(display, ptr->book->type);
			break;
		}
		if (ctrl->view == VIEWBOOKKEYWD) {
			for (int i = 0; i < NUMOFKEY; i++) {
				MovePen(x + i * xindent * 3,y);
				DrawTextString(displays[i]);
			}
			SetPenColor(FRAMECOLOR);
		}
		else if (ctrl->view == VIEWBOOKAUTHOR) {
			for (int i = 0; i < NUMOFAUTHOR; i++) {
				MovePen(x + i * xindent * 5, y);
				DrawTextString(displays[i]);
			}
			SetPenColor(FRAMECOLOR);
		}
		else {
			MovePen(x, y);
			DrawTextString(display);
		}
		ptr = ptr->next;
	}
	_itoa(ctrl->item->itemNum, id, 10);
	strcpy(display, option);
	strcat(display, id);
	MovePen(frame->x, frame->y + yindent);
	DrawTextString(display);
	//pressed = NOPRESS;
}

void newBookUI(struct Control* ctrl, struct winFrame* frame, struct BookInfo* book)
{
	double x = frame->x;
	double y = frame->y;
	double w = frame->w;
	double h = frame->h;
	double yindent = GetFontHeight() * 1.5;
	static int pressed = NOPRESS;
	char msg[] = "��������(YYYYMMDD)��";
	double xindent = TextStringWidth(msg)*1.1;
	int id = 1;
	if(pressed == NOPRESS ) pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	else drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (ctrl->menuLvl == 1) {
		if (pressed != NOPRESS) {
			ctrl->buttonPressed = pressed;
			pressed = NOPRESS;
		}
		x = x + w / 8;
		y = y + h - yindent * 3;
		w = w / 2;
		h = yindent;

		char msg1[]="����:";
		MovePen(x, y);
		DrawTextString(msg1);
		textbox(GenUIID(id++), x + xindent, y, w, h, book->bookName,20);
		SetPenColor(FRAMECOLOR);

		char msg2[]="�ؼ���:";
		for (int i = 0; i < 5; i++) {
			//strcat(msg2);
			y -= yindent*1.1;
			MovePen(x, y);
			DrawTextString(msg2);
			textbox(GenUIID(id++), x + xindent, y, w, h, book->keywords[i], 20);
			SetPenColor(FRAMECOLOR);
		}
		char msg3[] = "����:";
		for (int i = 0; i < 3; i++) {
			y -= yindent*1.1;
			MovePen(x, y);
			DrawTextString(msg3);
			textbox(GenUIID(id++), x + xindent, y, w, h, book->authors[i], 20);
			SetPenColor(FRAMECOLOR);
		}
		char msg4[] = "�����磺";
		y -= yindent*1.1;
		MovePen(x, y);
		DrawTextString(msg4);
		textbox(GenUIID(id++), x + xindent, y, w, h, book->publisher, 20);
		SetPenColor(FRAMECOLOR);

		char msg5[] = "��������(YYYYMMDD)��";
		y -= yindent*1.1;
		MovePen(x, y);
		DrawTextString(msg5);
		textbox(GenUIID(id++), x + xindent, y, w, h, book->pubDate, 9);
		SetPenColor(FRAMECOLOR);

		char msg6[] = "���ࣺ";
		y -= yindent * 1.1;
		MovePen(x, y);
		DrawTextString(msg6);
		textbox(GenUIID(id++), x + xindent, y, w, h, book->type, 20);
		SetPenColor(FRAMECOLOR);
	}
}


void showBookEditUI(struct Control* ctrl, struct winFrame* f, struct BookInfo* book)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double yindent = GetFontHeight() * 1.5;
	static int pressed = NOPRESS;
	char msg[] = "��������(YYYYMMDD)��";
	double xindent = TextStringWidth(msg) * 1.1;
	int id = 11;
	int len;
	if (pressed == NOPRESS) pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	else drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	//if (ctrl->frameLvl == 3) {
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	if (ctrl->buttonPressed != NOPRESS)
		len = 0;
	else len = LEN20;

	x = x + w / 8;
	y = y + h - yindent * 3;
	w = w / 2;
	h = yindent;

	//char msg1[] = "����:";
	textbox(GenUIID(id++), x + xindent, y, w, h, book->bookName, len);
	MovePen(x, y);
	DrawTextString("����:");

	//char msg2[] = "�ؼ���:";
	for (int i = 0; i < 5; i++) {
		//strcat(msg2);
		y -= yindent * 1.1;
		textbox(GenUIID(id++), x + xindent, y, w, h, book->keywords[i], len);
		MovePen(x, y);
		DrawTextString("�ؼ���:");
		//SetPenColor(FRAMECOLOR);
	}
	//char msg3[] = "����:";
	for (int i = 0; i < 3; i++) {
		y -= yindent * 1.1;
		textbox(GenUIID(id++), x + xindent, y, w, h, book->authors[i], len);
		MovePen(x, y);
		DrawTextString("����:");
		//SetPenColor(FRAMECOLOR);
	}
	//char msg4[] = "�����磺";
	y -= yindent * 1.1;
	textbox(GenUIID(id++), x + xindent, y, w, h, book->publisher, len);
	MovePen(x, y);
	DrawTextString("�����磺");
	//SetPenColor(FRAMECOLOR);

	//char msg5[] = "��������(YYYYMMDD)��";
	y -= yindent * 1.1;
	textbox(GenUIID(id++), x + xindent, y, w, h, book->pubDate, len);
	MovePen(x, y);
	DrawTextString("�������ڣ�");
	SetPenColor(FRAMECOLOR);

	y -= yindent * 1.1;
	textbox(GenUIID(id++), x + xindent, y, w, h, book->type, len);
	MovePen(x, y);
	DrawTextString("���ͣ�");
	SetPenColor(FRAMECOLOR);
	
}

void displayBookUI(struct Control* ctrl, struct winFrame* f)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double yindent = GetFontHeight() * 1.5;
	static int pressed = NOPRESS;
	char msg[] = "��������(YYYYMMDD)��";
	double xindent = TextStringWidth(msg) * 1.1;
	int id = 11;
	struct BookInfo* book = ctrl->item->bookPtr->book;
	pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	
	x = x + w / 8;
	y = y + h - yindent * 3;
	w = w / 2;
	h = yindent;

	//char msg1[] = "����:";
	MovePen(x + xindent, y);
	DrawTextString(book->bookName);
	MovePen(x, y);
	DrawTextString("����:");

	//char msg2[] = "�ؼ���:";
	for (int i = 0; i < 5; i++) {
		//strcat(msg2);
		y -= yindent * 1.1;
		MovePen(x + xindent, y);
		DrawTextString(book->keywords[i]);
		MovePen(x, y);
		DrawTextString("�ؼ���:");
	}
	//char msg3[] = "����:";
	for (int i = 0; i < 3; i++) {
		y -= yindent * 1.1;
		MovePen(x + xindent, y);
		DrawTextString(book->authors[i]);
		MovePen(x, y);
		DrawTextString("����:");
		//SetPenColor(FRAMECOLOR);
	}
	//char msg4[] = "�����磺";
	y -= yindent * 1.1;
	MovePen(x + xindent, y);
	DrawTextString(book->publisher);
	MovePen(x, y);
	DrawTextString("�����磺");
	//SetPenColor(FRAMECOLOR);

	//char msg5[] = "��������(YYYYMMDD)��";
	y -= yindent * 1.1;
	MovePen(x + xindent, y);
	DrawTextString(book->pubDate);
	MovePen(x, y);
	DrawTextString("�������ڣ�");
	SetPenColor(FRAMECOLOR);

	y -= yindent * 1.1;
	MovePen(x + xindent, y);
	DrawTextString(book->type);
	MovePen(x, y);
	DrawTextString("���ͣ�");
	SetPenColor(FRAMECOLOR);

	y -= yindent * 1.1;
	MovePen(x + xindent, y);
	switch (book->status) {
	case -2:
		DrawTextString("���������");
		break;
	case -1:
		DrawTextString("���");
		break;
	case 1:
		DrawTextString("���");
		break;
	case 2:
		DrawTextString("���������");
		break;
	}
	MovePen(x, y);
	DrawTextString("״̬��");
}


void drawStatus(struct Control* ctrl,struct AccInfo* user)
{
	double h = GetFontHeight() * 1.5;
	double w = GetWindowWidth();
	char recentCtrlMsg[] = { "status: " };
	double y = h;
	double x = 0;
	MovePen(x, y);
	SetPenColor("Blue");
	DrawLine(w, 0);
	y = h / 4;
	drawLabel(x, y, recentCtrlMsg);
	SetPenColor("Brown");
	drawLabel(x + TextStringWidth(recentCtrlMsg), y, ctrl->status);
	drawLabel (x + w - TextStringWidth(user->userName), y, user->userName);

}












int drawOperationRectangle(double x, double y, double w, double h,char * title, char * option1, char * option2)
{
	char buttonStr[] = "@BUTTON@";
	double buttonWidth = TextStringWidth(buttonStr);
	double buttonHeight = GetFontHeight() * 2;
	bool ok = FALSE, cancel = FALSE;
	drawBackGround(x, y, w, h, BKCOLOR);
	drawRectangle(x, y, w, h, NOFILL);
	double xindent = w / 10;
	ok = button(GenUIID(0), x + xindent, y, buttonWidth, buttonHeight, option1);
	SetPenColor("Blue");
	cancel = button(GenUIID(0), x + w - xindent - buttonWidth, y, buttonWidth, buttonHeight, option2);
	SetPenColor("Blue");
	if (ok)return OK;
	else if (cancel)return CANCEL;
	else return NOPRESS;
}

int drawMsgRectangle(double x, double y, double w, double h, char* title, char* msg, char* option)
{
	char buttonStr[] = "@BUTTON@";
	double buttonWidth = TextStringWidth(buttonStr);
	double buttonHeight = GetFontHeight() * 2;
	bool ok = FALSE;
	//setMenuColors("Grey", "Black", "Grey", "Black", NOFILL);
	//drawRectangle(x, y, w, h, NOFILL);
	SetPenColor("Light Gray");
	drawRectangle(x, y, w, h, FILL);
	setMenuColors("Blue", "Blue", "Red", "Red", NOFILL);
	drawBox(x, y, w, h, NOFILL, msg, 'L', "Black");
	ok = button(GenUIID(0), (x+w/2)-buttonWidth/2, y*1.1, buttonWidth, buttonHeight, option);
	if (ok)return OK;
	else return NOPRESS;
}

void newLibraryUI(struct Control* ctrl,const struct winFrame* frame, char* name)
{
	char* label = menuListFile[ctrl->optSelect];
	char newLibMsg[]="�½�ͼ�������";
	static int pressed = NOPRESS;
	int len;
	if(ctrl->buttonPressed == NOPRESS) pressed = drawOperationRectangle(frame->x, frame->y, frame->w, frame->h, label, "ȷ��", "ȡ��");
	else drawOperationRectangle(frame->x, frame->y, frame->w, frame->h, label, "ȷ��", "ȡ��");
	MovePen(frame->x * 2 - TextStringWidth(newLibMsg), frame->y * 2 + GetFontHeight() / 2);
	DrawTextString(newLibMsg);

	//setTextBoxColors("Blue", "Blue", "Red", "Red", 0);
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS)
	{
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	//textbox(GenUIID(0), frame->x * 2, frame->y * 2, frame->w / 2, GetFontHeight() * 2, newLibName, 19);
	if (ctrl->buttonPressed == NOPRESS)
		len = LEN20;
	else len = 0;

	textbox(GenUIID(0), frame->x * 2, frame->y * 2, frame->w / 2, GetFontHeight() * 2, name, len);
	SetPenColor("Blue");
}

void openFileUI(struct Control* ctrl,const struct winFrame* frame, const char * libDir, char *newDir )
{
	double x = frame->x;
	double y = frame->y;
	double w = frame->w;
	double h = frame->h;
	char* label = menuListFile[ctrl->optSelect];
	static int pressed=NOPRESS;
	double fontHeight = GetFontHeight();
	double xindent;
	char buttonMsg[] = "ѡ��";
	string prompt1 = "ѡ���ļ�";
	string prompt2 = "���ļ�:";
	double promptWidth = TextStringWidth(prompt2);
	double buttonWidth = TextStringWidth(buttonMsg);
	int id = 0;

	//to handle files
	HANDLE hFind;
	WIN32_FIND_DATA findData;	
	static char dir[100] = "" ;
	//char dirNew[100] = {""};
	static char fileSelected[100] = "";

	//operation window
	pressed = drawOperationRectangle(x, y, w, h, label, "��", "ȡ��");
	//SetPenColor("Blue");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		if (pressed == CANCEL) {
			strcpy(fileSelected, "");
		}
		else if (pressed == OK) {
			strcpy(newDir, libDir);
			strcat(newDir, fileSelected);
			if (strcmp(fileSelected, "") == 0) {
				strcpy(dir, "");
				strcpy(newDir, "");
			}
			else {
				strcpy(newDir, libDir);
				strcat(newDir, fileSelected);
				strcpy(fileSelected, "");
			}
			
		}
		pressed = NOPRESS;
	}
	//open default directory
	strcpy(dir, libDir);
	strcat(dir, "\\library*");
	hFind = FindFirstFile(dir, &findData);

	//display window headder
	MovePen(x, y + h - fontHeight * 1.5);
	DrawLine(w, 0);
	x = x + w / 50;
	y = y + h - fontHeight;
	MovePen(x, y);
	DrawTextString(prompt1);

	//display first file
	y = y - fontHeight*2;
	MovePen(x, y);
	DrawTextString(findData.cFileName);
	xindent = TextStringWidth(findData.cFileName);
	if (button(GenUIID(id++), x + xindent, y, buttonWidth, fontHeight, buttonMsg) != NOPRESS)
		strcpy(fileSelected, findData.cFileName);
	SetPenColor(FRAMECOLOR);

	//display consecutive files
	while (FindNextFile(hFind, &findData))
	{
		y -= fontHeight;
		//MovePen(x, y);
		//DrawTextString(findData.cFileName);
		xindent = TextStringWidth(findData.cFileName);
		if (button(GenUIID(id++), x + xindent, y, buttonWidth, fontHeight, buttonMsg) != NOPRESS)
			strcpy(fileSelected, findData.cFileName);
		MovePen(x, y);
		DrawTextString(findData.cFileName);
		SetPenColor(FRAMECOLOR);
	}

	//display "���ļ�" selection
	x = frame->x + frame->w / 6;
	y = frame->y + buttonWidth*1.5;
	MovePen(x, y);
	DrawTextString(prompt2);
	MovePen(x + promptWidth, y);
	DrawTextString(fileSelected);


}

void returnToMainFrame(struct Control * Ctrl)
{


}

bool validNewLibrary(const string s, int size) {
	int len = strlen(s);
	if (len <= 0 || len >= size)return FALSE;
	else return TRUE;
}

void drawBackGround(double x, double y, double w, double h, string color)
{
	SetPenColor(color);
	drawRectangle(x, y, w, h, FILL);
	SetPenColor(FRAMECOLOR);
}


void helpUI(struct Control* ctrl, struct winFrame* f, char** s, int limit, int rows)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	char butt[] = { "ȷ��" };
	double buttonw = TextStringWidth(butt) * 1.5;
	double buttonh = GetFontHeight() * 1.5;

	SetPenColor("White");
	drawRectangle(x, y, w, h, FILL);
	SetPenColor("Blue");
	drawRectangle(x, y, w, h, NOFILL);

	if (button(GenUIID(0), x + w / 2 - buttonw / 2, y + w / 20, buttonw, buttonh, butt))
		ctrl->buttonPressed = OK;

	x = x + w - 5 * buttonw;
	y = y + h *.9;

	//SetPenColor(FRAMECOLOR);
	if (button(GenUIID(0), x, y, buttonw, buttonh, "��һҳ"))
		if (ctrl->pager->page > 0)
			ctrl->pager->page--;

		
		
	if (button(GenUIID(0), x + 2 * buttonw, y, buttonw, buttonh, "��һҳ"))
		if (ctrl->pager->page + 1 < ctrl->pager->maxPage)
			ctrl->pager->page++;

	SetPenColor(FRAMECOLOR);

	x = f->x + w * .1;
	y = f->y + h * .9;
	int j = ctrl->pager->page * limit;
	for (int i = 0 ; i < limit && j < rows ;i++,j++) {
		MovePen(x, y);
		DrawTextString(s[j]);
		y -= buttonh;

	}
	char page[10] = "Page:";
	char n[5];
	strcat(page, _itoa(ctrl->pager->page + 1,n,10));
	drawLabel(f->x, f->y, page);

}

void setDateUI(struct Control* ctrl, struct RecInfo* rec,struct winFrame* f) {
	double xindent = f->w / 6;
	double yindent = f->h / 6;
	double x = f->x;
	double y = f->y;
	double fh = GetFontHeight() * 1.5;
	static int pressed;
	pressed = drawOperationRectangle(x, y, f->w, f->h, "", "ȷ��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}

	x = x + xindent*2;
	y = y + yindent * 5;
	MovePen(x, y);
	DrawTextString(rec->acc->userName);
	char msg1[] = "�û���:";
	double width1 = TextStringWidth(msg1);
	MovePen(x- width1 * 1.1, y);
	DrawTextString(msg1);
	

	y -= yindent;
	MovePen(x, y);
	DrawTextString(rec->book->bookName);
	char msg2[] = "ͼ����:";
	MovePen(x - width1 * 1.1, y);
	DrawTextString(msg2);
	

	y -= yindent;
	textbox(GenUIID(0), x, y, xindent * 3, fh, rec->borrowDate, LEN20);
	char msg3[] = "��������:";
	double width2 = TextStringWidth(msg3);
	MovePen(x - width2 * 1.1, y);
	DrawTextString(msg3);
	

	y -= yindent;
	textbox(GenUIID(0), x, y, xindent * 3, fh, rec->returnDate, LEN20);
	char msg4[] = "��������:";
	MovePen(x - width2 * 1.1, y);
	DrawTextString(msg4);
	

	
}

void accSearchUI(struct Control* ctrl, char* text, struct winFrame* f) {
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double xindent = w / 16;
	double yindent = h / 10;
	char* options[] = { "�û�ID����","�û�������", "�û���������"};
	double buttonw = TextStringWidth(options[2]) * 1.2;
	double buttonh = GetFontHeight() * 1.5;
	double boxw = TextStringWidth("01234567890123456789000");
	int id = 99;
	static int pressed = NOPRESS;
	pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	y = y + h - yindent;
	x = x - xindent * 2;
	int i = 0;
	for (; i < 3; i++) {
		if (button(id++, x += buttonw * 1.1, y, buttonw, buttonh, options[i]))
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->view = VIEWACCID + i;
				ctrl->chgView = 1;
			}
	}

	char msg1[LEN20];
	if (ctrl->view <= VIEWACCWORK && ctrl->view >= VIEWACCID) {
		strcpy(msg1, options[ctrl->view - VIEWACCID]);
	}
	else strcpy(msg1, "δѡ��");
	SetPenColor(FRAMECOLOR);
	x = f->x + w - boxw * 1.2;
	MovePen(x - TextStringWidth(msg1), y);
	DrawTextString(msg1);
	textbox(id++, x, y, boxw, buttonh, text, LEN20);

	SetPenColor(FRAMECOLOR);
	drawRectangle(f->x + xindent, f->y + yindent * 2, xindent * 14, yindent * 6, NOFILL);

	y = y - buttonh * 1.2;
	if (button(id++, x, y, buttonw / 2, buttonh, "����"))
		ctrl->op = 1;

	if (button(id++, f->x + xindent, f->y + yindent, buttonw / 2, buttonh, "��һҳ"))
		if (ctrl->pager->page > 0)
			ctrl->pager->pageOption = -1;

	if (button(id++, f->x + xindent * 2.5, f->y + yindent, buttonw / 2, buttonh, "��һҳ"))
		if (ctrl->pager->page < ctrl->pager->maxPage)
			ctrl->pager->pageOption = 1;

	SetPenColor(FRAMECOLOR);

	x = f->x + xindent * 1.1;
	y = f->y + yindent * 7.5;


	if (ctrl->view == VIEWACCID) {
		char* ops[] = { "�û�ID","�û���","����" };
		for (int i = 0; i < 3; i++) {
			MovePen(f->x + xindent + i * xindent * 4, y);
			DrawTextString(ops[i]);
		}
	}
	else if (ctrl->view == VIEWACCNAME) {
		char* ops[] = { "�û���","�û�ID","����" };
		for (int i = 0; i < 3; i++) {
			MovePen(f->x + xindent + i * xindent * 4, y);
			DrawTextString(ops[i]);
		}
	}
	else if (ctrl->view == VIEWACCWORK) {
		char* ops[] = { "����","�û���","�û�ID" };
		for (int i = 0; i < 3; i++) {
			MovePen(f->x + xindent + i * xindent * 4, y);
			DrawTextString(ops[i]);
		}
	}
	MovePen(f->x + xindent, y*.99);
	DrawLine(xindent * 14, 0);

	char num[5];
	struct AccList* ptr = ctrl->pager->accPtr;
	for (int i = 0; i < 10 && ptr; i++) {
		y -= buttonh * 1.1;
		if (button(id++, f->x + f->w - xindent * 2, y, buttonw / 3, buttonh, "�鿴")) {
			ctrl->item->itemNum = i + 1;
			ctrl->item->accPtr = ptr;
			ctrl->op = 2;
		}
		switch (ctrl->view) {
		case VIEWACCID:
			MovePen(f->x + xindent, y);
			DrawTextString(_itoa(ptr->acc->id,num,10));
			MovePen(f->x + xindent + xindent * 4, y);
			DrawTextString(ptr->acc->userName);
			MovePen(f->x + xindent + 2 * xindent * 4, y);
			DrawTextString(ptr->acc->work);
			break;
		case VIEWACCNAME:
			MovePen(f->x + xindent, y);
			DrawTextString(ptr->acc->userName);
			MovePen(f->x + xindent + xindent * 4, y);
			DrawTextString(_itoa(ptr->acc->id, num, 10));
			MovePen(f->x + xindent + 2 * xindent * 4, y);
			DrawTextString(ptr->acc->work);
			break;
		case VIEWACCWORK:
			MovePen(f->x + xindent, y);
			DrawTextString(ptr->acc->work);
			MovePen(f->x + xindent + xindent * 4, y);
			DrawTextString(_itoa(ptr->acc->id, num, 10));
			MovePen(f->x + xindent + 2 * xindent * 4, y);
			DrawTextString(ptr->acc->userName);
			break;
		}
		ptr = ptr->next;
	}
	SetPenColor(FRAMECOLOR);
	x = f->x;
	y = f->y;
	char page[LEN20] = "page:";
	strcat(page, _itoa(ctrl->pager->page, num, 10));
	MovePen(x, y);
	DrawTextString(page);

	MovePen(x, y + buttonh);
	char item[LEN20] = "item:";
	strcat(item, _itoa(ctrl->item->itemNum, num, 10));
	DrawTextString(item);
}


void bookSearchUI(struct Control* ctrl, char* text, struct winFrame* f) {
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double xindent = w / 16;
	double yindent = h / 10;
	char* options[] = { "��Ų���","����ģ������", "�ؼ���ģ������","����ģ������"};
	double buttonw = TextStringWidth(options[2]) * 1.2;
	double buttonh = GetFontHeight() * 1.5;
	double boxw = TextStringWidth("01234567890123456789000");
	int id = 99;
	static int pressed = NOPRESS;
	pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}
	y = y + h - yindent;
	x = x - xindent*2;
	int i = 0;
	for (; i < 4; i++) {
		if (button(id++, x += buttonw * 1.1, y, buttonw, buttonh, options[i]))
			if (ctrl->buttonPressed == NOPRESS) {
				ctrl->view = VIEWBOOKID + i;
				ctrl->chgView = 1;
			}
				
	}

	char msg1[LEN20];
	if (ctrl->view <= VIEWBOOKAUTHOR && ctrl->view >= VIEWBOOKID) {
		strcpy(msg1, options[ctrl->view-VIEWBOOKID]);
	}
	else strcpy(msg1, "δѡ��");
	SetPenColor(FRAMECOLOR);
	x = f->x + w - boxw * 1.2;
	MovePen(x - TextStringWidth(msg1), y);
	DrawTextString(msg1);
	textbox(id++, x , y, boxw, buttonh, text, LEN20);
	
	SetPenColor(FRAMECOLOR);
	drawRectangle(f->x + xindent, f->y + yindent * 2, xindent * 14, yindent * 6, NOFILL);

	y = y - buttonh * 1.2;
	if (button(id++, x, y, buttonw / 2, buttonh, "����"))
		ctrl->op = 1;

	if (button(id++, f->x + xindent, f->y + yindent, buttonw / 2, buttonh, "��һҳ"))
		if (ctrl->pager->page > 0)
			ctrl->pager->pageOption = -1;

	if (button(id++, f->x + xindent * 2.5, f->y + yindent, buttonw / 2, buttonh, "��һҳ"))
		if (ctrl->pager->page < ctrl->pager->maxPage)
			ctrl->pager->pageOption = 1;

	SetPenColor(FRAMECOLOR);

	x = f->x + xindent * 1.1;
	y = f->y + yindent * 7.5;
	
	
	if (ctrl->view == VIEWBOOKAUTHOR) {
		char* authors[] = { "author1","author2","author3" };
		for (int i = 0; i < NUMOFAUTHOR; i++) {
			MovePen(f->x + xindent + i*xindent*4, y);
			DrawTextString(authors[i]);
		}
	}
	else if (ctrl->view == VIEWBOOKID) {
		MovePen(f->x + xindent, y);
		DrawTextString("ͼ���");
	}
	else if (ctrl->view == VIEWBOOKKEYWD) {
		char* keys[] = { "keyword1","keyword2","keyword3","keyword4","keyword5" };
		for (int i = 0; i < NUMOFKEY; i++) {
			MovePen(f->x + xindent + i * xindent * 2.5, y);
			DrawTextString(keys[i]);
		}
	}
	else if (ctrl->view == VIEWBOOKNAME) {
		MovePen(f->x + xindent, y);
		DrawTextString("ͼ����");
	}
	MovePen(f->x + xindent, y*.99);
	DrawLine(xindent * 14, 0);

	char num[5];
	struct BookList* ptr = ctrl->pager->bookPtr;
	for (int i = 0; i < 10 && ptr; i++) {
		y -= buttonh*1.1;
		if (button(id++, f->x + f->w - xindent * 2, y, buttonw / 3, buttonh, "�鿴")) {
			ctrl->item->itemNum = i + 1;
			ctrl->item->bookPtr = ptr;
			ctrl->op = 2;
		}
		switch (ctrl->view) {
		case VIEWBOOKAUTHOR:
			for (int i = 0; i < NUMOFAUTHOR; i++) {
				MovePen(f->x + xindent + i * xindent * 4, y);
				DrawTextString(ptr->book->authors[i]);
			}
			break;
		case VIEWBOOKID:
			MovePen(x, y);
			DrawTextString(_itoa(ptr->book->id,num,10));
			break;
		case VIEWBOOKKEYWD:
			for (int i = 0; i < NUMOFKEY; i++) {
				MovePen(f->x + xindent + i * xindent * 2.5, y);
				DrawTextString(ptr->book->keywords[i]);
			}
			break;
		case VIEWBOOKNAME:
			MovePen(x, y);
			DrawTextString(ptr->book->bookName);
			break;
		}
		ptr = ptr->next;
	}
	SetPenColor(FRAMECOLOR);
	x = f->x;
	y = f->y;
	char page[LEN20] = "page:";
	strcat(page, _itoa(ctrl->pager->page, num, 10));
	MovePen(x, y);
	DrawTextString(page);

	MovePen(x, y + buttonh);
	char item[LEN20] = "item:";
	strcat(item, _itoa(ctrl->item->itemNum, num, 10));
	DrawTextString(item);
}

void loadingUI(struct winFrame* f) {
	SetPenColor("Gray");
	drawRectangle(f->x, f->y, f->w, f->h, FILL);
	SetPenColor("Brown");
	MovePen(f->x + f->w / 2, f->y + f->h / 2);
	DrawTextString("Loading..............");
	Pause(.25);
}


void displayAccUI(struct Control* ctrl, struct winFrame* f)
{
	double x = f->x;
	double y = f->y;
	double w = f->w;
	double h = f->h;
	double xindent = w / 8;
	double yindent = h / 12;
	double fontHeight = GetFontHeight() * 1.5;
	char* fields[] = { "���û���:","���û���:","���˺�����:","���˺�����:","�ɹ�����λ:","�¹�����λ:","�Ա�:","Ȩ��:","����ͽ���:" };
	struct AccInfo* acc = ctrl->item->accPtr->acc;
	char* accFields[] = { acc->userName,acc->newUserName,acc->pwd,acc->newPwd,acc->work,acc->newWork,acc->gender};

	int id = 88;
	double widths[] = { TextStringWidth(fields[0]),TextStringWidth(fields[2]),TextStringWidth(fields[4]) };
	static int pressed = NOPRESS;
	pressed = drawOperationRectangle(x, y, w, h, "", "ȷ��", "ȡ��");
	if (pressed != NOPRESS && ctrl->buttonPressed == NOPRESS) {
		ctrl->buttonPressed = pressed;
		pressed = NOPRESS;
	}

	/*display now showing*/
	char headder[50] = "";
	MovePen(f->x, f->y + h - fontHeight);
	DrawTextString(strcat(headder, "�˺���Ϣ"));
	x = x + 3 * xindent;
	y = y + h - yindent;
	char num[5];
	for (int i = 0; i < 9; i++) {
		if (i == 7) {
			MovePen(x*1.1, y -= yindent);
			if (acc->priority == ADMIN) {
				DrawTextString("����Ա");
			}
			else DrawTextString("��ͨ�û�");
		}
		else if (i == 8) {
			MovePen(x * 1.1, y -= yindent);
			DrawTextString(_itoa(acc->numOfconnect, num, 10));
		}
		else {
			MovePen(x * 1.1, y -= yindent);
			DrawTextString(accFields[i]);
		}
		MovePen(x - widths[1], y);
		DrawTextString(fields[i]);
	}
}