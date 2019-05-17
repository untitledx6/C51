#include<reg52.h>
#include<intrins.h>
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
#define LCD_data P0
void lcd_init();  //LCD初始化
bit lcd_busy(void);	//LCD验忙
void lcd_wcmd(unsigned char cmd);//LCD写指令
void lcd_wdat(unsigned char dat);//LCD写数据
void lcd_pos(unsigned char pos); //LCD光标定位
void delay(unsigned char n);
unsigned char diap_1[16] = "long ge";
unsigned char diap_2[10] = "N B !";
void main()
{
	unsigned int i, m = 0;
	lcd_init();		   //液晶初始化
		lcd_pos(0);
		while (diap_1[m] != '\0')
		{
			lcd_wdat(diap_1[m]);
			m++;
		}

		lcd_pos(0x44); //设置显示位置为第二行
		m = 0;
		for (i = 0; i <= 5; i++)
		{
			lcd_wdat(diap_2[i]); //显示字符
		}
}

bit lcd_busy()	   //判断液晶是否忙碌
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

void lcd_wcmd(unsigned char cmd)			//写指令函数
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

void lcd_wdat(unsigned char dat)			 //写显示函数
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

void lcd_init()							  //初始化设定
{
lcd_wcmd(0x38); //16*2显示，5*7点阵，8
lcd_wcmd(0x0c); //显示开，关光标
lcd_wcmd(0x06); //写一个字符指针后地址
lcd_wcmd(0x01); //清除LCD的显示内容
}

void lcd_pos(unsigned char pos)			  //液晶定位函数
{
lcd_wcmd(pos | 0x80); //数据指针=80+地址
}
void delay(unsigned char n) {
	unsigned char i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < 255; j++);
	}
}


