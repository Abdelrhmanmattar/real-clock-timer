/*
 * _7SEGMENT.c
 *
 * Created: 5/18/2023 7:09:32 PM
 *  Author: abdelrhman mattar
 */ 
#include "DIO.h"
#include "7SEGMENT.h"
void seven_seg_vinit(char port_name)
{
	dio_setport(port_name,0xff);
}

void seven_seg_write(char portname,unsigned char number)
{
	unsigned char arr[]={ 0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f};
	dio_writeport(portname,arr[number]);
	
}
