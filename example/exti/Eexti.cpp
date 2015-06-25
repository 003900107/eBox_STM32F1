
#include "ebox.h"
#include "uartx.h"
#include "exti.h"
#include "interrupts.h"

//����ж�����û���ⲿ��������������
//������exti.cpp�еĳ�ʼ��������
//���������ڲ�������������
uint32_t xx;
uint8_t flag;
EXTIx ex(7,EXTI_Trigger_Falling);

void exit()
{
	xx++;
	flag = 1;
}
void setup()
{
	eBoxInit();
	uart3.begin(115200);
	ex.attachInterrupt(exit);
}


int main(void)
{
	setup();
	while(1)
	{
		if(flag == 1)
		{
			uart3.printf("\r\nxx = %d",xx);
			flag = 0;
		}
	}


}




