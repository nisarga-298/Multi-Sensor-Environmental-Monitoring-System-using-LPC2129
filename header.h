///delay

 extern void delay_ms(unsigned int ms);
 extern void delay_sec(unsigned int sec);

//lcd
 extern void lcd_data(unsigned char data);
 extern void lcd_cmd(unsigned char cmd);
 extern void lcd_init(void);
 extern void lcd_string(char *ptr);
 extern void lcd_integer(signed int num);
 extern void lcd_float(float f);

 //uart0

 extern void uart0_init(unsigned int baud);
 extern void uart0_tx(unsigned char data);
 extern void uart0_tx_string(char *ptr);
 extern void uart0_tx_integer(signed int num);
 extern void uart0_tx_float(float f);
extern unsigned char uart0_rx(void);
 
 
  //adc
  extern void adc_init(void);
 extern unsigned char adc_read(unsigned int ch_num);
