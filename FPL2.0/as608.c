/**************
AS608Դ�ļ�
�����ߣ���쿹�
���ڣ�2020.9.26
**************/

#include <reg52.h>
#include "as608.h"

uchar xdata Data_buff[32];//���ڽ���ָ�Ƶ����ݰ�


void Send_Bytes(uchar *c,uchar len)//��ָ��ģ�����������ֽ�
{
	uchar i = 0;
	for(i=0; i<len; i++)
	{
		SBUF = *(c+i);
		while(!TI);
		TI = 0;
	}
}


void Receive_Bytes(uchar *c,uchar len)//���������ֽ�
{
	uchar i = 0;
	for(i=0; i<len; i++)
	{
		while(!RI);
		*(c+i) = SBUF;
		RI = 0;
	}        
}


char PS_GetImage()//���ͻ�ȡͼ���ָ��
{

	uchar *ps2 = "\xef\x01\xff\xff\xff\xff\x01\x00\x03\x01\x00\x05";//ָ���

	Send_Bytes(ps2,12);//����
	Receive_Bytes(Data_buff,12);//�������ݰ�
	if(Data_buff[9] == 0x00&&Data_buff[11]==0x0a)//�����Ƿ��ȡ�ɹ�
	{                                                           
		return 1;        
	}
	return (-1);        
}

char PS_GenChar(uchar BufferID)//��ȡָ��ͼ������������ŵ�buffer��
{

	uchar *ps1 = "\xef\x01\xff\xff\xff\xff\x01\x00\x04\x02\x01\x00\x08";//��ŵ�buffer1��ָ���
	uchar *ps2 = "\xef\x01\xff\xff\xff\xff\x01\x00\x04\x02\x02\x00\x09";//��ŵ�buffer2��ָ���
	if(BufferID == 0x01)
	{
		Send_Bytes(ps1,13);
	}
	else
	{
		Send_Bytes(ps2,13);
	}
	Receive_Bytes(Data_buff,12);//�������ݰ�
	
	if(Data_buff[9]==0x00 && Data_buff[11]==0x0a)//�ж������Ƿ������Ҵ�ųɹ�
	{                                                           
		return 1;        
	}
	return (-1);        
}

char PS_Search(uchar BufferID)//����ָ�ƿ⺯��
{

	uchar *ps1 = "\xef\x01\xff\xff\xff\xff\x01\x00\x08\x04\x01\x00\x00\x01\x2b\x00\x3a";//����buffer1ָ��
	uchar *ps2 = "\xef\x01\xff\xff\xff\xff\x01\x00\x08\x04\x02\x00\x00\x01\x2b\x00\x3b";//����buffer2ָ��
	if(BufferID == 0x01)
	{
		Send_Bytes(ps1,17);
	}
	else
	{
		Send_Bytes(ps2,17);
	}   
	Receive_Bytes(Data_buff,16);//�������ݰ�
	
	if(Data_buff[9] == 0x00)//�ж��Ƿ���ָ�ƿ�ָ��ƥ��        
	{                                                           
		return 1;        
	}
	return (-1);        
}

