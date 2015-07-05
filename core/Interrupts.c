#include "interrupts.h"
#include "mcuconfig.h"
callbackFun timOneCallbackTable[5];
callbackFun gTimxCallbackTable[TIM_NUM +1];
callbackFun extiCallbackTable[EXTI_LINE_NUM + 1];
callbackFun UARTCallbackTable[USART_NUM * 2];//֧�ִ��ڵ�rx��tx�ж�
callbackFun rtcCallbackTable[3];//


void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_OW) != RESET)
	{	
		rtcCallbackTable[0]();
		RTC_ClearITPendingBit(RTC_IT_OW);
	}	
	if (RTC_GetITStatus(RTC_IT_ALR) != RESET)
	{	
		rtcCallbackTable[1]();
		RTC_ClearITPendingBit(RTC_IT_ALR);
	}	
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{	

		rtcCallbackTable[2]();
		RTC_ClearITPendingBit(RTC_IT_SEC);
	}
}

void TIM1_UP_IRQHandler(void)
{

 if(TIM_GetITStatus(TIM1 , TIM_IT_Update) == SET)
 {
  TIM_ClearITPendingBit(TIM1 , TIM_FLAG_Update);
		timOneCallbackTable[0]();
 }
}
void TIM2_IRQHandler(void)
{

 if(TIM_GetITStatus(TIM2 , TIM_IT_Update) == SET)
 {
  TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
		gTimxCallbackTable[2]();
 }
}
void TIM3_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM3 , TIM_IT_Update) == SET)
 {
  TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);
		gTimxCallbackTable[3]();
 }
}
void TIM4_IRQHandler(void)
{
 if(TIM_GetITStatus(TIM4 , TIM_IT_Update) == SET)
 {
  TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);
		gTimxCallbackTable[4]();
 }
}
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[0]();
    EXTI_ClearITPendingBit(EXTI_Line0);     //����жϱ�־λ
  }  	
}
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[1]();

    EXTI_ClearITPendingBit(EXTI_Line1);     //����жϱ�־λ
  }  	
}
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {

		extiCallbackTable[2]();

    EXTI_ClearITPendingBit(EXTI_Line2);     //����жϱ�־λ
  }  	
}
void EXTI3_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line3) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[3]();
    EXTI_ClearITPendingBit(EXTI_Line3);     //����жϱ�־λ
  }  	
}
void EXTI4_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line4) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[4]();
    EXTI_ClearITPendingBit(EXTI_Line4);     //����жϱ�־λ
  }  	
}

void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line5) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[5]();
    EXTI_ClearITPendingBit(EXTI_Line5);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line6) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[6]();
    EXTI_ClearITPendingBit(EXTI_Line6);     //����жϱ�־λ
  }  
  if(EXTI_GetITStatus(EXTI_Line7) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[7]();
    EXTI_ClearITPendingBit(EXTI_Line7);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line8) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[8]();
    EXTI_ClearITPendingBit(EXTI_Line8);     //����жϱ�־λ
  }	
  if(EXTI_GetITStatus(EXTI_Line9) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[9]();
    EXTI_ClearITPendingBit(EXTI_Line9);     //����жϱ�־λ
  }   

}

void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line10) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[10]();
    EXTI_ClearITPendingBit(EXTI_Line10);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line11) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[11]();
    EXTI_ClearITPendingBit(EXTI_Line11);     //����жϱ�־λ
  }  
  if(EXTI_GetITStatus(EXTI_Line12) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[12]();
    EXTI_ClearITPendingBit(EXTI_Line12);     //����жϱ�־λ
  }   
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[13]();
    EXTI_ClearITPendingBit(EXTI_Line13);     //����жϱ�־λ
  }	
  if(EXTI_GetITStatus(EXTI_Line14) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[14]();
    EXTI_ClearITPendingBit(EXTI_Line14);     //����жϱ�־λ
  }   
  if(EXTI_GetITStatus(EXTI_Line15) != RESET) //ȷ���Ƿ������EXTI Line�ж�
  {
		extiCallbackTable[15]();
    EXTI_ClearITPendingBit(EXTI_Line15);     //����жϱ�־λ
  }   

}
void USART1_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		UARTCallbackTable[0]();
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		return;
	}
	if(USART_GetITStatus(USART1,USART_IT_TXE)==SET)
	{
		UARTCallbackTable[1]();
		USART_ClearITPendingBit(USART1,USART_IT_TXE);
	}
}
void USART2_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		UARTCallbackTable[2]();
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		return;
	}	
	if(USART_GetITStatus(USART2,USART_IT_TXE)==SET)
	{
		UARTCallbackTable[3]();
		USART_ClearITPendingBit(USART2,USART_IT_TXE);
	}
}
void USART3_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET)
	{
		UARTCallbackTable[4]();
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		return;
	}
	if(USART_GetITStatus(USART3,USART_IT_TXE)==SET)
	{
		UARTCallbackTable[5]();
		USART_ClearITPendingBit(USART3,USART_IT_TXE);
	}
}
