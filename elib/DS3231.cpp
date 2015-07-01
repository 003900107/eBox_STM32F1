
#include "DS3231.h"
	


uint8_t DS3231::BcdToDec(uint8_t BCDCode)
{
	u8 temp,Dec;
	temp = (BCDCode >> 4) * 10;
	Dec = (BCDCode & 0x0f) + temp;
	return Dec;
}
uint8_t DS3231::DecToBcd(uint8_t Dec)
{
	u8 temp,temp2,Bcd;
	temp = Dec / 10;
	temp2 = Dec % 10;
	
	Bcd =  (temp << 4) + temp2;
	
	return Bcd;
}

void	DS3231::getTime(DateTime *t)
{
	readByte(DS3231_WriteAddress,DS3231_YEAR,&buf[6]);			//��ݵ���λ
	readByte(DS3231_WriteAddress,DS3231_MONTH,&buf[5]);			//�·�
	readByte(DS3231_WriteAddress,DS3231_DAY,&buf[4]);				//����
	readByte(DS3231_WriteAddress,DS3231_WEEK,&buf[3]);			//��
	readByte(DS3231_WriteAddress,DS3231_HOUR,&buf[2]);			//ʱ
	readByte(DS3231_WriteAddress,DS3231_MINUTE,&buf[1]);		//��
	readByte(DS3231_WriteAddress,DS3231_SECOND,&buf[0]);		//��


//	timer.w_year,timer.w_month,timer.w_date,timer.hour,timer.min,timer.sec
/******����ȡ��ʮ����������ת��Ϊʮ��������******/
	t->year 	=BcdToDec(buf[6]);
	t->month	=BcdToDec(buf[5]);
	t->date	=BcdToDec(buf[4]);
	t->week 		=BcdToDec(buf[3]);
	t->hour		=BcdToDec(buf[2]);
	t->min			=BcdToDec(buf[1]);
	t->sec	    =BcdToDec(buf[0]);	
}
void	DS3231::setTime(DateTime *t)
{
		DateTime tBCD;
		tBCD.week = DecToBcd(t->week);
		tBCD.year = DecToBcd(t->year);
		tBCD.month = DecToBcd(t->month);
		tBCD.date = DecToBcd(t->date);
		tBCD.hour = DecToBcd(t->hour);
		tBCD.min = DecToBcd(t->min);
		tBCD.sec = DecToBcd(t->sec);
   
    writeByte(DS3231_WriteAddress,DS3231_WEEK,tBCD.week);   //�޸���
		writeByte(DS3231_WriteAddress,DS3231_YEAR,tBCD.year);   //�޸���
    writeByte(DS3231_WriteAddress,DS3231_MONTH,tBCD.month);  //�޸���
    writeByte(DS3231_WriteAddress,DS3231_DAY,tBCD.date);    //�޸���
    writeByte(DS3231_WriteAddress,DS3231_HOUR,tBCD.hour);   //�޸�ʱ
    writeByte(DS3231_WriteAddress,DS3231_MINUTE,tBCD.min); //�޸ķ�
    writeByte(DS3231_WriteAddress,DS3231_SECOND,tBCD.sec ); //�޸���
}
	
