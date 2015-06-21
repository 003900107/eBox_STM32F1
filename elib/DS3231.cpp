
#include "DS3231.h"
	
	

uint8_t DS3231::write_byte(uint8_t addr, uint8_t write_data)
{
		_start();
		_send_byte(DS3231_WriteAddress);
    if (_wait_ack() == 0)
        return 0;
		
		_send_byte(addr);
    if (_wait_ack() == 0)
        return 0;

   
		_send_byte(write_data);
    if (_wait_ack() == 0)
        return 0;
		_stop();

    delay_us(10);      
    return 1;
}
uint8_t DS3231::read_current(void)
{
    unsigned char read_data;
		_start();
		_send_byte(DS3231_ReadAddress);
		if (_wait_ack() == 0)
       return (0);

		read_data = _read_byte();
		_send_no_ack();
		_stop();
    return read_data;
}
uint8_t DS3231::read_random(uint8_t random_addr)
{
		_start();
		_send_byte(DS3231_WriteAddress);
		if (_wait_ack() == 0)
       return (0);
		
		_send_byte(random_addr);
		if (_wait_ack() == 0)
       return (0);
		

    return(read_current());
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

void	DS3231::get_time(DateTime *t)
{
	buf[6]=read_random(DS3231_YEAR);			//��ݵ���λ
	buf[5]=read_random(DS3231_MONTH);	   	//�·�
	buf[4]=read_random(DS3231_DAY);		//����
	buf[3]=read_random(DS3231_WEEK);
	buf[2]=read_random(DS3231_HOUR) & 0x3f;		//ʱ
	buf[1]=read_random(DS3231_MINUTE);		//��
	buf[0]=read_random(DS3231_SECOND);	    	//��

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
void	DS3231::set_time(DateTime *t)
{
		DateTime tBCD;
		tBCD.week = DecToBcd(t->week);
		tBCD.year = DecToBcd(t->year-2000);
		tBCD.month = DecToBcd(t->month);
		tBCD.date = DecToBcd(t->date);
		tBCD.hour = DecToBcd(t->hour);
		tBCD.min = DecToBcd(t->min);
		tBCD.sec = DecToBcd(t->sec);
   
    write_byte(DS3231_WEEK,tBCD.week);   //�޸���
		write_byte(DS3231_YEAR,tBCD.year);   //�޸���
    write_byte(DS3231_MONTH,tBCD.month);  //�޸���
   
    write_byte(DS3231_DAY,tBCD.date);    //�޸���
   
    write_byte(DS3231_HOUR,tBCD.hour);   //�޸�ʱ
   
    write_byte(DS3231_MINUTE,tBCD.min); //�޸ķ�
   
    write_byte(DS3231_SECOND,tBCD.sec ); //�޸���
}
	
