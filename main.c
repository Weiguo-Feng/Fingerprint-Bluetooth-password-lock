/************************************************
指纹蓝牙密码锁
基于51单片机、BT06蓝牙模块、AS608指纹模块、SG90舵机
总代码量：约300行

功能1：接收指纹特征与指纹库对比
功能2：接收蓝牙串口通信
功能3：舵机接收信号驱�
�
制作者：冯炜国
日期：2020.9.26
************************************************/

#include <reg52.h>
#include "sg90.h"
#include "as608.h"

unsigned char code table0[] = "Warning ";//蓝牙开门反馈
unsigned char code table1[] = "FBI";//蓝牙开门密码
unsigned char receive[3]={0};//接收蓝牙串口通信

int i=0, flag = 0,j=0;
void UsartInit();
void compare(unsigned char *temp);

sbit WAK = P2^4;//指纹密码感应位
sbit vcc = VCC;

void main()
{
	UsartInit();
	TR0 = 0;
	receive[2] = '\0';
	while(1)
	{	
		if(receive[2] == 'I')//进入蓝牙密码匹配的条件
		{
			compare(receive);//若匹配成功发送
			delay_ms(100);
			motor();//电机运行，开门
			TR0 = 0;
			break;
		}
		if(WAK == 1)//指纹模块感应
		{	
			ES = 0;
			PS_GetImage();//获取指纹图像
			PS_GenChar(0x01);//下载指纹特征
			if((PS_Search(0x01)) == 1)//与指纹库对比
			{	
				motor();//开门
			}
			ES = 1;
			break;
		}
	}		
}


void UsartInit()
{
	EA = 1;
	ES = 1;
	TR1 = 1;
	TMOD = 0x20;
	
	TH1 = 0xfd;//波特率9600，晶振11.0592MHZ
	TL1 = 0xfd;
	
	SCON = 0x50;
	PCON = 0x0;
}

void compare(unsigned char *temp)//蓝牙回馈函数
{
	ES = 0;
	for(i=0; i<3; i++)
	{
		if(temp[i] == table1[i])
			flag++;			
	}
	if(flag == 3)//进入匹配
	{
		for(i=0; i<8; i++)
		{
			SBUF = table0[i];
			while(TI != 1);
			TI = 0;
		}
		receive[2] = '\0';
	}
	receive[2] = '\0';
	flag = 0;
	ES = 1;
}

void usart() interrupt 4  //串口中断函数，接收3个字符
{
	
	receive[j] = SBUF;
	while(RI != 1);
	RI = 0;
	j++;
	if(j == 3)
		j = 0;
}
