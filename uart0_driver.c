 #include<lpc21xx.h>
#include"header.h"
 #define THRE ((U0LSR>>5)&1)
 #define RDR (U0LSR&1)
 void uart0_init(unsigned int baud)
 {
  unsigned int pclk,result=0;
  if(VPBDIV==0)
  pclk=15000000;
  else if(VPBDIV==0x01)
  pclk=60000000;
  else if(VPBDIV==0x02)
  pclk=30000000;
  result=pclk/(16*baud);
  PINSEL0 |=0x05;
  U0DLL=result&0xff;
  U0DLM=(result>>8)&0xff;
 U0LCR=0x03;
}
void uart0_tx(unsigned char data)
  {
  U0THR=data;
  while(THRE==0);
  }
 
  void uart0_tx_string(char *ptr)
  {
  while(*ptr!=0)
  {
  uart0_tx(*ptr);
  ptr++;
  }
  }
 
  void uart0_tx_integer(signed int num)
  {
  char a[10];
  int i;
  if(num<0)
  {
  uart0_tx('-');
  num=-num;
  }
  if(num==0)
  {
  uart0_tx('0');
  return;
 }
 51 for(i=0;num;num=num/10,i++)
  a[i]=num%10+48;
  for(i=i-1;i>=0;i--)
  uart0_tx(a[i]);
  }
  void uart0_tx_float(float f)
  {
 int num;
 if(f<0)
{
 uart0_tx('-');
 f=-f;
 }
 if(f==0)
 {
 uart0_tx_string("0.0");
 return;
 }
 num=f;
 uart0_tx_integer(num);
 uart0_tx('.');
 num=(f-num)*1000000;
 uart0_tx_integer(num);

 }
  unsigned char uart0_rx(void)
  {
  while(RDR==0);
   return U0RBR;
}
