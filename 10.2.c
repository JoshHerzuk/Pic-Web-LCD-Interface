#include <P18F67J60.h>
#pragma config WDT = OFF
#pragma config FOSC = HSPLL
#pragma config XINST = OFF
#define button PORTBbits.RB0
#define RS PORTBbits.RB1
#define RW PORTBbits.RB2
#define EN PORTBbits.RB3
#define ldata PORTE


void delay (unsigned int );
void lcdInit (void);
void lcdCmd (unsigned char command);
void lcdData (unsigned char data);
void main(void)
{
	
ADCON1 = 0x06; //Sets RA0-RA5 & RE0-RE2 to digital mode
CMCON = 0x07; //Disable Comparators on RD0-RD3
TRISE = 0;
TRISB = 0;
TRISBbits.RB0 = 1;
lcdInit();	
	while(1){
		if(button == 1){
			unsigned char count[] = "COUNTER-(0-99)";
			unsigned int i = 0;
			unsigned int Tens, Ones;
			lcdCmd(0x81);	
			while (count[i] != '\0'){
				lcdData(count[i]);
				i++;
			}
			for(i = 0; i<100; i++){
				Tens = i / 10;
				Ones = i % 10;
				lcdCmd(0xC7);
				lcdData(0x30 + Tens);
				lcdData(0x30 + Ones);
				delay(500);
				while(button == 0);
		
			}
		}
	 
			
		
			
	}

}

void delay (unsigned int itime){

	unsigned int i; unsigned int j;
	for(i = 0; i < itime; i++)
		for(j = 0; j < 165; j++);
}

void lcdCmd (unsigned char command){

	unsigned char command_upper = (command>>4);
	unsigned char command_lower = (command&0x0F);
	ldata = command_upper;
	RS = 0;
	RW = 0;
	EN = 1;
	delay(30);
	EN = 0;
	ldata = command_lower;
	RS = 0;
	RW = 0;
	EN = 1;
	delay(30);
	EN = 0;
	
}

void lcdData (unsigned char data){

	unsigned char data_upper = (data>>4);
	unsigned char data_lower = (data&0x0F);
	ldata = data_upper;
	RS = 1;
	RW = 0;
	EN = 1;
	delay(30);
	EN = 0;
	ldata = data_lower;
	RS = 1;
	RW = 0;
	EN = 1;
	delay(30);
	EN = 0;
}

void lcdInit (void){
	
	delay(15);
	lcdCmd(0x28);
	lcdCmd(0x0C);
	lcdCmd(0x01);
	lcdCmd(0x06);
	lcdCmd(0x80);
}



	