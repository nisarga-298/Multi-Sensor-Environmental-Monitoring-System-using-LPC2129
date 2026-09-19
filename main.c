#include <LPC21xx.H>
  #include "header.h"
  #include <stdio.h>
 #define green (1<<17)
 #define red (1<<18)
 #define water ((IOPIN0>>14)&1)
  int main()
 {
  unsigned int  a_value=0,a_value1;
  unsigned int ldr,soil;
  float temp=0,vout=0;
  char a[100];

  lcd_init();
  uart0_init(9600);
 adc_init();
  IODIR0|=green|red;
  uart0_tx_string("MULTI-SENSOR\r\n");
  while(1)
  {
  lcd_cmd(0x80);
  uart0_tx_string("\r\n--:Temp:--");
  lcd_string("Temp: ");
  ///temp///
  a_value=adc_read(1);
  vout=(a_value*3.3)/1023.0;
  temp=(vout-0.5)/0.01;

  lcd_cmd(0x80);
  lcd_string("Temp: ");
  //lcd_float(temp);
  sprintf(a,"\r\nTemp:%.2f c",temp);
  uart0_tx_string(a);

  ///soil////
 a_value1=adc_read(0);//p0.27
  soil=(a_value1/100)*1023;
   sprintf(a,"\r\nSoil Moisture:%d %%",soil);
  uart0_tx_string(a);

 ///ldr   ///
  ldr=adc_read(3);
  //sprintf(a,"\r\nTemp:%.2f\r\nSoil Moisture:%d",temp,soil);
  //uart0_tx_string(a);
  if(ldr>=600)
  {
  sprintf(a,"\r\nLight Level :Dark");
  uart0_tx_string(a);
  }

  else if(ldr>=200 &&ldr<600)
  {
  sprintf(a,"\r\nClimate:Normal" );
  uart0_tx_string(a);
  }
else
  {
  sprintf(a,"\r\nClimate:Sunny" );
   uart0_tx_string(a);
   }
   //water//
   lcd_cmd(0xc0);
   lcd_string("Status:");
   if(water==0)
   {
   sprintf(a,"\r\nWater Sensor:Not Detected\r\nSystem status:safe\r\nLed Status:Green\r\n");
  uart0_tx_string(a);
  lcd_string("SAFE");
   IOSET0=red;
   IOCLR0=green;
   }
   else
   {
   sprintf(a,"\r\nWater Sensor: Detected\r\nSystem status:Alert\r\nLed Status:red\r\n");
   uart0_tx_string(a);
 
   lcd_string("ALert");
   IOSET0=green;
   IOCLR0=red;
   }
   delay_ms(2000);
   }
 }
