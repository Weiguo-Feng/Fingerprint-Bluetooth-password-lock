/*****************
AS608ָ��ģ��ͷ�ļ�
�����ߣ���쿹�
���ڣ�2020.9.26
*****************/

#include <reg52.h>
#define uchar unsigned char

char PS_Search(uchar BufferID);

char PS_GenChar(uchar BufferID);

char PS_GetImage();

void Receive_Bytes(uchar *c,uchar len);

void Send_Bytes(uchar *c,uchar len);

void SendOneByte(unsigned char c);
