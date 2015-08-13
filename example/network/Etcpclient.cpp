
#include "ebox.h"
#include "w5500.h"
#include "tcp.h"
USART uart1(USART1,PA9,PA10);

  u8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};/*����Mac����*/
  u8 lip[4]={192,168,1,111};/*����lp����*/
  u8 sub[4]={255,255,255,0};/*����subnet����*/
  u8 gw[4]={192,168,1,1};/*����gateway����*/
	
  u8 rip[4]={192,168,1,102};/*����lp����*/
	u8 data[20] = "\r\n data";
  u8 ip[6];
	
W5500 w5500(PA4,SPI1,PA5,PA6,PA7,PA2,PA3);
	
TCPCLIENT tcp;


void ethEvent()
{
	u8 tmp2,tmp3;

	tmp2 = eth->getSIR();
	tmp3 = eth->getSn_IR(SOCKET0);
	if(tmp2&SIR_0)
	{
		eth->setSIR(SIR_0);/*SIR�ĵ�0λ��1*/
	}
	
	if(tmp3&Sn_IR_RECV)
	{
		eth->setSn_IR(SOCKET0, Sn_IR_RECV);/*Sn_IR�ĵ�2λ��1*/
		tcp.recvFlag = 1;
	}


}
void setup()
{
	eBoxInit();
	uart1.begin(9600);

	w5500.begin(mac,lip,sub,gw);
	w5500.attchInterruputEvent(ethEvent);
	attachEthToSocket(&w5500);
	
  w5500.getMAC (ip);
  uart1.printf("mac : %02x.%02x.%02x.%02x.%02x.%02x\r\n", ip[0],ip[1],ip[2],ip[3],ip[4],ip[5]);
  w5500.getIP (ip);
  uart1.printf("IP : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  w5500.getSubnet(ip);
  uart1.printf("mask : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  w5500.getGateway(ip);
  uart1.printf("GW : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  uart1.printf("Network is ready.\r\n");
	
	tcp.begin(SOCKET0,3000);	
	tcp.connect(rip,8080);

	

}
u16 len;
int main(void)
{
	setup();

	while(1)
	{
		
		if(tcp.recvFlag == 1)
		{
			len = tcp.interruptRecv();
			uart1.printf("\r\n============================");		
			uart1.printf("\r\n���ض˿�:%d",tcp.localPort );
			uart1.printf("\r\n��Ϣ��Դ:%d.%d.%d.%d:%d", tcp.remoteIP[0],tcp.remoteIP[1],tcp.remoteIP[2],tcp.remoteIP[3],tcp.remotePort);
			uart1.printf("\r\n���ݳ���:%d",len);		
			uart1.printf("\r\n��������:");		
			uart1.printf((const char *)tcp.buf);
			tcp.send(tcp.buf,len);
		}




		

	}


}



