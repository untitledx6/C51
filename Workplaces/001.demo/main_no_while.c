#include<reg52.h>
#include<intrins.h>
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
#define LCD_data P0
void lcd_init();  //LCD��ʼ��
bit lcd_busy(void);	//LCD��æ
void lcd_wcmd(unsigned char cmd);//LCDдָ��
void lcd_wdat(unsigned char dat);//LCDд����
void lcd_pos(unsigned char pos); //LCD��궨λ
void delay(unsigned char n);
unsigned char diap_1[16] = "long ge";
unsigned char diap_2[10] = "N B !";
void main()
{
	unsigned int i, m = 0;
	lcd_init();		   //Һ����ʼ��
		lcd_pos(0);
		while (diap_1[m] != '\0')
		{
			lcd_wdat(diap_1[m]);
			m++;
		}

		lcd_pos(0x44); //������ʾλ��Ϊ�ڶ���
		m = 0;
		for (i = 0; i <= 5; i++)
		{
			lcd_wdat(diap_2[i]); //��ʾ�ַ�
		}
}

bit lcd_busy()	   //�ж�Һ���Ƿ�æµ
{
 bit result;
 RS=0;
 RW=1;
 EN=1;
 _nop_();
 delay(10);
 result=(bit)(P0&0x80);
 delay(10);
 EN=0;
 return result;

}

void lcd_wcmd(unsigned char cmd)			//дָ���
{
  while(lcd_busy());
 	RS = 0;
 	RW = 0;
 	EN = 0;
 	delay(10);
	_nop_();
	_nop_();
	LCD_data = cmd;
	delay(10);
	_nop_();
 	EN = 1;
 	delay(10);
	_nop_();
 	EN = 0;
}

void lcd_wdat(unsigned char dat)			 //д��ʾ����
{
	while(lcd_busy());
	RS = 1;
	RW = 0;
	EN = 0;
	delay(10);
	LCD_data = dat;
	_nop_();
	delay(10);
	EN = 1;
	_nop_();
	delay(10);
	EN = 0;
}

void lcd_init()							  //��ʼ���趨
{
lcd_wcmd(0x38); //16*2��ʾ��5*7����8
lcd_wcmd(0x0c); //��ʾ�����ع��
lcd_wcmd(0x06); //дһ���ַ�ָ����ַ
lcd_wcmd(0x01); //���LCD����ʾ����
}

void lcd_pos(unsigned char pos)			  //Һ����λ����
{
lcd_wcmd(pos | 0x80); //����ָ��=80+��ַ
}
void delay(unsigned char n) {
	unsigned char i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < 255; j++);
	}
}


