/************************************************
ָ������������
����51��Ƭ����BT06����ģ�顢AS608ָ��ģ�顢SG90���
�ܴ�������Լ300��

����1������ָ��������ָ�ƿ�Ա�
����2��������������ͨ��
����3����������ź����
�
�����ߣ���쿹�
���ڣ�2020.9.26
************************************************/

#include <reg52.h>
#include "sg90.h"
#include "as608.h"

unsigned char code table0[] = "Warning ";//�������ŷ���
unsigned char code table1[] = "FBI";//������������
unsigned char receive[3]={0};//������������ͨ��

int i=0, flag = 0,j=0;
void UsartInit();
void compare(unsigned char *temp);

sbit WAK = P2^4;//ָ�������Ӧλ
sbit vcc = VCC;

void main()
{
	UsartInit();
	TR0 = 0;
	receive[2] = '\0';
	while(1)
	{	
		if(receive[2] == 'I')//������������ƥ�������
		{
			compare(receive);//��ƥ��ɹ�����
			delay_ms(100);
			motor();//������У�����
			TR0 = 0;
			break;
		}
		if(WAK == 1)//ָ��ģ���Ӧ
		{	
			ES = 0;
			PS_GetImage();//��ȡָ��ͼ��
			PS_GenChar(0x01);//����ָ������
			if((PS_Search(0x01)) == 1)//��ָ�ƿ�Ա�
			{	
				motor();//����
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
	
	TH1 = 0xfd;//������9600������11.0592MHZ
	TL1 = 0xfd;
	
	SCON = 0x50;
	PCON = 0x0;
}

void compare(unsigned char *temp)//������������
{
	ES = 0;
	for(i=0; i<3; i++)
	{
		if(temp[i] == table1[i])
			flag++;			
	}
	if(flag == 3)//����ƥ��
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

void usart() interrupt 4  //�����жϺ���������3���ַ�
{
	
	receive[j] = SBUF;
	while(RI != 1);
	RI = 0;
	j++;
	if(j == 3)
		j = 0;
}
