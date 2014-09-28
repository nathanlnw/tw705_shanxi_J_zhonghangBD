#include  <string.h>
#include "Menu_Include.h"
#include "Lcd.h"

#define width_hz   12
#define width_zf   6
#define top_line   14

static u8 License_Modify_Flag=0;// ==3���ڷ���   ==2  ==1Ҫ�޸��ַ�

static u8 License_SetFlag=1,License_SetFlag_temp=1;
static u8 License_set_noeffect=0;//�Ƿ��г��ƺ���Ҫ����    1����    2����Ҫ����
static u8 License_Type_flag=0;//==0ѡ���Ƿ�����==1��  ==2����
static u8 License_Type_Counter=0;//  0: ����    1:A-M         2:N-Z
unsigned char select_License[]={0x0C,0x06,0xFF,0x06,0x0C};

//-----  ���ͨҪ�� ----------------
unsigned char Car_HZ_code[31][2]={"��","��","��","��","��","��","��","��","��","��",\
                                  "��","³","��","��","��","��","��","��","ԥ","��",\
                                  "��","��","��","��","��","��","��","��","��","��",\
                                  "��"};  
unsigned char ABC_License_0_Z[36][1]={"0","1","2","3","4","5","6","7","8","9","A","B",\
	                                  "C","D","E","F","G","H","I","J","K","L","M","N",\
	                                  "O","P","Q","R","S","T","U","V","W","X","Y","Z"};



DECL_BMP(8,5,select_License);

/*
invert_last==0   ����ѡ��
invert_last==1   ����Ҫ�޸ĵ��ַ������·�ѡ��Ҫ�޸��ַ�������ʾ����
invert_last==2   ��Ҫ�޸ĵ��ַ�ѡ��
*/
void License_Type_Sel( u8 type1_2,u8 par,u8 invert_last)
{
	lcd_fill(0);
	lcd_text12(0,0,(char *)Menu_Car_license,License_SetFlag-1,LCD_MODE_SET);
	if(invert_last==1)
		{
		if(License_SetFlag_temp>3)
			lcd_text12(0+(License_SetFlag_temp-2)*6,0,(char *)&Menu_Car_license[License_SetFlag_temp-2],1,LCD_MODE_INVERT);
		else if(License_SetFlag_temp==3)//��ɫ��ʾ����
			lcd_text12(0,0,(char *)&Menu_Car_license[0],2,LCD_MODE_INVERT);	
		}
	else
		{
		if(invert_last==2)
			{
			if(License_SetFlag_temp>3)
				lcd_text12(0+(License_SetFlag_temp-2)*6,0,(char *)&Menu_Car_license[License_SetFlag_temp-2],1,LCD_MODE_INVERT);
			else if(License_SetFlag_temp==3)//��ɫ��ʾ����
				lcd_text12(0,0,(char *)&Menu_Car_license[0],2,LCD_MODE_INVERT);	
			}
		if(type1_2==1)
			{
			if(par<=20)
				{
				lcd_bitmap(par*width_zf, 14, &BMP_select_License, LCD_MODE_SET);
				lcd_text12(0,19,"0123456789ABCDEFGHIJ",20,LCD_MODE_SET);
				}
			else
				{
				lcd_bitmap((par-20)*width_zf, 14, &BMP_select_License, LCD_MODE_SET);
			    lcd_text12(0,19,"KLMNOPQRSTUVWXYZ",16,LCD_MODE_SET);
				}
			}
		else if(type1_2==0)
			{
			if(License_Type_Counter<=9)
				{
				lcd_bitmap(3+par*width_hz, 14, &BMP_select_License, LCD_MODE_SET);
		        lcd_text12(0,20,"���¸ʼ��������ɺ���",20,LCD_MODE_SET);
				}
			else if((License_Type_Counter>=10)&&(License_Type_Counter<=19))
				{
				lcd_bitmap(3+(par-10)*width_hz, 14, &BMP_select_License, LCD_MODE_SET);
		        lcd_text12(0,20,"��³������Ӷ���ԥ��",20,LCD_MODE_SET);
				}
			else if((License_Type_Counter>=20)&&(License_Type_Counter<=29))
				{
				lcd_bitmap(3+(par-20)*width_hz, 14, &BMP_select_License, LCD_MODE_SET);
		        lcd_text12(0,20,"�廦����������ش���",20,LCD_MODE_SET);
				} 
			else if(License_Type_Counter==30)
				{
				lcd_bitmap(3+(par-30)*width_hz, 14, &BMP_select_License, LCD_MODE_SET); 
		        lcd_text12(0,20,"��",2,LCD_MODE_SET);
				}
			}
		}
	lcd_update_all();
}


static void msg( void *p)
{

}
static void show(void)
{
License_set_noeffect=1;

lcd_fill(0);
lcd_text12(0,3,"���ó��ƺ�",10,LCD_MODE_INVERT);
lcd_text12(0,18,"�����ճ���",10,LCD_MODE_SET);
lcd_update_all();
}


static void keypress(unsigned int key)
{
	switch(KeyValue)
		{
		case KeyValueMenu:
			//��ѡ��" �˵�" ѡ����Ҫ�޸ĵ��ַ�
			if((License_Type_flag==1)&&(License_Modify_Flag==0))//����ѡ�����һ��
				{
				if(License_SetFlag>1)//δ�����˳�
					{
					License_Modify_Flag=1;//???
	                //ѡ�н�Ҫ�޸ĵ��ַ�
					License_SetFlag_temp=License_SetFlag;
					if(License_SetFlag==3)
						License_Type_Sel(0,License_Type_Counter,1);
					else
						License_Type_Sel(1,License_Type_Counter,1);
					}
				else
					{					
					License_SetFlag=1;

					License_Type_flag=0;//�������ѡ�������ѡ��
					License_Type_Counter=0;//  0: ����    1:A-M         2:N-Z

					License_set_noeffect=0;
					memset(Menu_Car_license,0,sizeof(Menu_Car_license));
					pMenuItem=&Menu_0_loggingin;
					pMenuItem->show();
					}
				}
			//ѡ��Ҫ�޸��ٴΰ�" �˵� "�˳�������ѡ��
			else if(License_Modify_Flag==1)
				{
				License_Modify_Flag=0;

				License_SetFlag=1;

				License_Type_flag=0;//�������ѡ�������ѡ��
				License_Type_Counter=0;//  0: ����    1:A-M         2:N-Z

				License_set_noeffect=0;
				memset(Menu_Car_license,0,sizeof(Menu_Car_license));
				pMenuItem=&Menu_0_loggingin;
				pMenuItem->show();
				}
			break;
		case KeyValueOk:
			//ѡ���Ƿ����ó��ƺ�
			if(License_Type_flag==0)
				{
				if(License_set_noeffect==2)
					{
					License_SetFlag=1;

					License_Type_flag=0;//�������ѡ�������ѡ��
	                License_Type_Counter=0;//  0: ����    1:A-M         2:N-Z
	                License_set_noeffect=0;

			        
 
                    //==================================================== 
                    //   û���ó��ƺ�ʱΪ   1
                    License_Not_SetEnable=1;


					//===================================================
					//д�복�ƺ��Ƿ����ñ�־
		            DF_WriteFlashSector(DF_License_effect,0,&License_Not_SetEnable,1); 
				    //������һ��
					CarSet_0_counter=2;//���õ�2��
					//rt_kprintf("\r\n������һ��");
					pMenuItem=&Menu_0_loggingin;
					pMenuItem->show();
					}
				else if(License_set_noeffect==1)//��ʼ���ó��ƺ�
					{
					License_set_noeffect=0;//�˳�������ѡ��ѡ��
					License_Not_SetEnable=0;
					//д�복�ƺ��Ƿ����ñ�־
		            DF_WriteFlashSector(DF_License_effect,0,&License_Not_SetEnable,1); 
					
					CounterBack=0;
					License_Type_Counter=0;
					License_Type_Sel(0,License_Type_Counter,0);

					License_Type_flag=1;

					//rt_kprintf("\r\n��ʼ���ó��ƺ�");
				
					}	
				}
			//���ó��ƺſ�ʼ
			else if(License_Modify_Flag==1)
				{
				License_Modify_Flag=2;
				if(License_SetFlag_temp>3)
					License_Type_Sel(1,License_Type_Counter,2);
				else
					License_Type_Sel(0,License_Type_Counter,2);
				}
			else if(License_Modify_Flag==2)
				{
				License_Modify_Flag=1;
				if(License_SetFlag_temp==3)
					{
					memcpy(&Menu_Car_license[License_SetFlag_temp-3],Car_HZ_code[License_Type_Counter],2);
					License_Modify_Flag=0;
					License_Type_Counter=0;
					License_Type_Sel(1,License_Type_Counter,0);//�޸��꺺����ʾ�ַ�
					//License_SetFlag_temp=License_SetFlag;//=====
					//rt_kprintf("\r\n �޸�  ����");
					}
				else
					{
					Menu_Car_license[License_SetFlag_temp-2]=ABC_License_0_Z[License_Type_Counter][0];
					License_Modify_Flag=0;
					License_Type_Counter=0;
					License_Type_Sel(1,License_Type_Counter,0);
					//rt_kprintf("\r\n �޸�  �ַ�");
					}
				}
			else if(License_Type_flag==1)
				{
				if(License_SetFlag==1)
					{
					memcpy(Menu_Car_license,Car_HZ_code[License_Type_Counter],2);
					License_SetFlag++;	
					License_SetFlag++;
					//rt_kprintf("\r\n���  ����");
					License_Type_Counter=0;
					License_Type_Sel(1,License_Type_Counter,0);
					}
				else if((License_SetFlag>=3)&&(License_SetFlag<=8))
					{
					Menu_Car_license[License_SetFlag-1]=ABC_License_0_Z[License_Type_Counter][0];
					License_SetFlag++;	
					//rt_kprintf("\r\n���  �ַ�");
					
					License_Type_Counter=0;
					License_Type_Sel(1,License_Type_Counter,0);
					}		
				else if(License_SetFlag==9)
					{
					//License_Type_flag=10;//======
					if(MENU_set_carinfor_flag==1)
						{
						//rt_kprintf("\r\n���ƺ�������ɣ����˵������أ�%s",Menu_Car_license);
						//���ƺ�
						memset(Vechicle_Info.Vech_Num,0,sizeof(Vechicle_Info.Vech_Num));
						memcpy(Vechicle_Info.Vech_Num,Menu_Car_license,strlen((const char*)Menu_Car_license));
					    DF_WriteFlashSector(DF_Vehicle_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
						WatchDog_Feed();
						DF_WriteFlashSector(DF_VehicleBAK_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
						WatchDog_Feed();
						DF_WriteFlashSector(DF_VehicleBAK2_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info)); 
						WatchDog_Feed();
					    DF_WriteFlashSector(DF_VehicleBAK2_Struct_offset,0,(u8*)&Vechicle_Info,sizeof(Vechicle_Info));
						}
					
				    License_Type_flag=2;
					License_SetFlag=10;
					lcd_fill(0);
					lcd_text12(18,3,"���ƺ��������",14,LCD_MODE_SET);
					lcd_text12(6,18,"��ȷ�ϼ�������һ��",18,LCD_MODE_SET);
					lcd_update_all();
					}
				}
			else if(License_SetFlag==10)
				{
				//rt_kprintf("\r\n������һ��");
				License_SetFlag=1;

				License_Type_flag=0;//�������ѡ�������ѡ��
                License_Type_Counter=0;//  0: ����    1:A-M         2:N-Z
                License_set_noeffect=0;

				CarSet_0_counter=3;//���õ�2��
				//rt_kprintf("\r\n������һ��");
				pMenuItem=&Menu_0_loggingin;
				pMenuItem->show();
				}

			break;
		case KeyValueUP:
			if(License_Type_flag==0)
				{
				License_set_noeffect=1;
				lcd_fill(0);
				lcd_text12(0,3,"���ó��ƺ�",10,LCD_MODE_INVERT);
				lcd_text12(0,18,"�����ճ���",10,LCD_MODE_SET);
				lcd_update_all();
				}
			else if(License_Modify_Flag==1)
        		{
                if(License_SetFlag_temp>3)
                    License_SetFlag_temp--;
                License_Type_Sel(1,0,1);
                rt_kprintf("\r\nLicense_SetFlag_temp=%d",License_SetFlag_temp);
        		}
            else if(License_Modify_Flag==2)
        		{
                if(License_SetFlag>=3)
					{
					if(License_Type_Counter==0)
						License_Type_Counter=35;
					else if(License_Type_Counter>=1)
						License_Type_Counter--;
					if(License_SetFlag_temp>3)
						License_Type_Sel(1,License_Type_Counter,2);
					else
						License_Type_Sel(0,License_Type_Counter,2);
					}
				else
					{
					if(License_Type_Counter==0)
						License_Type_Counter=30;
					else if(License_Type_Counter>=1)
						License_Type_Counter--;
					
					License_Type_Sel(0,License_Type_Counter,2);
					}
        		}
			else
				{
				if(License_SetFlag>=3)
					{
					if(License_Type_Counter==0)
						License_Type_Counter=35;
					else if(License_Type_Counter>=1)
						License_Type_Counter--;
					
					License_Type_Sel(1,License_Type_Counter,0);
					}
				else
					{
					if(License_Type_Counter==0)
						License_Type_Counter=30;
					else if(License_Type_Counter>=1)
						License_Type_Counter--;
					
					License_Type_Sel(0,License_Type_Counter,0);
					}
				}
				
			break;
		case KeyValueDown:
			if(License_Type_flag==0)
				{
				License_set_noeffect=2;
				lcd_fill(0);
				lcd_text12(0,3,"���ó��ƺ�",10,LCD_MODE_SET);
				lcd_text12(0,18,"�����ճ���",10,LCD_MODE_INVERT);
				lcd_update_all();
				}
		    else if(License_Modify_Flag==1)
        		{
                if(License_SetFlag_temp<License_SetFlag)
                    License_SetFlag_temp++;
                License_Type_Sel(1,0,1);
    			
                rt_kprintf("\r\nLicense_SetFlag_temp=%d",License_SetFlag_temp);
        		}
            else if(License_Modify_Flag==2)
        		{
                if(License_SetFlag>=3)
					{
					License_Type_Counter++;
					if(License_Type_Counter>35)
						License_Type_Counter=0;

					if(License_SetFlag_temp>3)
						License_Type_Sel(1,License_Type_Counter,2);
					else
						License_Type_Sel(0,License_Type_Counter,2);
					}
				else
					{
					License_Type_Counter++;
					if(License_Type_Counter>30)
						License_Type_Counter=0;
					
					License_Type_Sel(0,License_Type_Counter,2);
					}
        		}
			else 
				{
				if(License_Type_flag==1)//ѡ����0-9  A-M  N-Z
					{
					if(License_SetFlag>=3)
						{
						License_Type_Counter++;
						if(License_Type_Counter>35)
							License_Type_Counter=0;
						
						License_Type_Sel(1,License_Type_Counter,0);
						}
					else
						{
						License_Type_Counter++;
						if(License_Type_Counter>30)
							License_Type_Counter=0;
						
						License_Type_Sel(0,License_Type_Counter,0);
						}
					//rt_kprintf("\r\n(down)License_Type_Counter=%d",License_Type_Counter);
					}
				}
				
			break;
		}
	KeyValue=0;
}


static void timetick(unsigned int systick)
{

}

ALIGN(RT_ALIGN_SIZE)
MENUITEM	Menu_0_1_license=
{
	"���ƺ�",
	6,
	&show,
	&keypress,
	&timetick,
	&msg,
	(void*)0
};





