
#include "DS3231.h"
	
	

uint8_t DS3231::writeByte(uint8_t addr, uint8_t write_data)
{
		start();
		sendByte(DS3231_WriteAddress);
    if (waitAck() == 0)
        return 0;
		
		sendByte(addr);
    if (waitAck() == 0)
        return 0;

   
		sendByte(write_data);
    if (waitAck() == 0)
        return 0;
		stop();

    delay_us(10);      
    return 1;
}
uint8_t DS3231::readCurrent(void)
{
    unsigned char read_data;
		start();
		sendByte(DS3231_ReadAddress);
		if (waitAck() == 0)
       return (0);

		read_data = receiveByte();
		sendNoAck();
		stop();
    return read_data;
}
uint8_t DS3231::readRandom(uint8_t random_addr)
{
		start();
		sendByte(DS3231_WriteAddress);
		if (waitAck() == 0)
       return (0);
		
		sendByte(random_addr);
		if (waitAck() == 0)
       return (0);
		

    return(readCurrent());
}

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
	buf[6]=readRandom(DS3231_YEAR);			//��ݵ���λ
	buf[5]=readRandom(DS3231_MONTH);	   	//�·�
	buf[4]=readRandom(DS3231_DAY);		//����
	buf[3]=readRandom(DS3231_WEEK);
	buf[2]=readRandom(DS3231_HOUR) & 0x3f;		//ʱ
	buf[1]=readRandom(DS3231_MINUTE);		//��
	buf[0]=readRandom(DS3231_SECOND);	    	//��

//	timer.w_year,timer.w_month,timer.w_date,timer.hour,timer.min,timer.sec
/******����ȡ��ʮ����������ת��Ϊʮ��������******/
	t->year 	=BcdToDec(buf[6])+2000;
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
		tBCD.year = DecToBcd(t->year-2000);
		tBCD.month = DecToBcd(t->month);
		tBCD.date = DecToBcd(t->date);
		tBCD.hour = DecToBcd(t->hour);
		tBCD.min = DecToBcd(t->min);
		tBCD.sec = DecToBcd(t->sec);
   
    writeByte(DS3231_WEEK,tBCD.week);   //�޸���
		writeByte(DS3231_YEAR,tBCD.year);   //�޸���
    writeByte(DS3231_MONTH,tBCD.month);  //�޸���
   
    writeByte(DS3231_DAY,tBCD.date);    //�޸���
   
    writeByte(DS3231_HOUR,tBCD.hour);   //�޸�ʱ
   
    writeByte(DS3231_MINUTE,tBCD.min); //�޸ķ�
   
    writeByte(DS3231_SECOND,tBCD.sec ); //�޸���
}
	
