#include "Menu_Include.h"
#include <string.h>


unsigned char noselect_TirExspd[]={0x3C,0x7E,0xC3,0xC3,0xC3,0xC3,0x7E,0x3C};//����
unsigned char select_TirExspd[]={0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C};//ʵ��

DECL_BMP(8,8,select_TirExspd); DECL_BMP(8,8,noselect_TirExspd); 

static unsigned char menu_pos=0;
static PMENUITEM psubmenu[2]=
{
	&Menu_4_1_pilao,
	&Menu_4_2_chaosu,
};
static void menuswitch(void)
{
unsigned char i=0;
	
lcd_fill(0);
lcd_text12(0,3,"Υ��",4,LCD_MODE_SET);
lcd_text12(0,17,"��ʻ",4,LCD_MODE_SET);
for(i=0;i<2;i++)
	lcd_bitmap(30+i*11, 5, &BMP_noselect_TirExspd, LCD_MODE_SET);
lcd_bitmap(30+menu_pos*11,5,&BMP_select_TirExspd,LCD_MODE_SET);
lcd_text12(30,19,(char *)(psubmenu[menu_pos]->caption),psubmenu[menu_pos]->len,LCD_MODE_SET);
lcd_update_all();
}
static void msg( void *p)
{
}
static void show(void)
{
    MenuIdle_working=0;//clear
    menu_pos=0;
	menuswitch();
}


static void keypress(unsigned int key)
{
switch(KeyValue)
	{
	case KeyValueMenu:
		pMenuItem=&Menu_1_menu;
		pMenuItem->show();
		CounterBack=0;
		break;
	case KeyValueOk:
			pMenuItem=psubmenu[menu_pos];//ƣ�ͼ�ʻ
			pMenuItem->show();
		break;
	case KeyValueUP:
			menu_pos=0;
			menuswitch();
		break;
	case KeyValueDown:
			menu_pos=1;
			menuswitch();
		break;
	}
KeyValue=0;
}


static void timetick(unsigned int systick)
{

	CounterBack++;
	if(CounterBack!=MaxBankIdleTime)
		return;
	CounterBack=0;
	pMenuItem=&Menu_1_Idle;
	pMenuItem->show();
}

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_4_InforTirExspd=
{
    "Υ���ʻ",
	8,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};

