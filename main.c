
#include "initsys.h"
#include "argb2.h"

void Init_Device(void);

void Test_Color(void);
void MenuScreen();
void playScreen();
void Font_test(void);
void Pic_test(void);
void Test_shape(void);

#define TI1  (SCON1 & 0x02)
#define TI1_0  SCON1 &= ~0x02 
#define RI1  (SCON1 & 0x01) 
#define RI1_0  SCON1 &= ~0x01 

//#define OVR1   (SCON1 & 0x80)
#define OVR1_0  SCON1 &= ~0x80 



void putc(char tav)
		{
			SBUF0=tav;
			while(TI0==0);
			TI0=0;
		}
		
		char getc()
		{
			while(RI0==0);
			RI0=0;
			return SBUF0;
		}
void ClearFIFO(void)
{	
	char tav;	
	do
	{
		RI1_0;//SCON1=SCON1&0Xfe;
		tav=SBUF1;
	}
	while(RI1);//SCON1&1);
	OVR1_0;//SCON1=SCON1&0X7f; //clear ovr1 
}

char baby_rec;

void Init_Device(void);

sbit Tx=P0^0;
sbit Rx=P0^2;
sbit viber=P2^2;
void PUTCHAR1(char tav)
{
	SBUF1=tav;
	while(TI1==0); 
	TI1_0;//SCON1=SCON1&(~2);    //TI1 = 0;  
}

char GETCHAR1(void)
{
	//read from uart
	while(RI1==0); 

	RI1_0;//SCON1=SCON1&0Xfe;  //RI1=0;
	//tav=SBUF1;
	return(SBUF1);
}
int music=0;
int temp=0;
int m=1;

void main(void)
{
	S16 x=0, y=0,  ButtonNum;
	Init_Device();
	initSYS();

	
				
			
	viber=0;

	while(1) {
		    MenuScreen();
		
//while(1)
//{
//	baby_rec=GETCHAR1();
//	switch(baby_rec)
//	{case'v':LCD_drawButton(4,160, 250,70,70, 20, GREEN,BLACK,"music",2);
//	         break;
//	case'V':LCD_drawButton(4,160, 250,70,70, 20, RED,BLACK,"music",2);
//	         break;
//					 }}
//		delay_ms(1000);
//	if (music==1)
//			LCD_drawButton(4,160, 250,70,70, 20, GREEN,BLACK,"music",2);
//	else
//			LCD_drawButton(4,160, 250,70,70, 20, WHITE,BLACK,"music",2);
//	if (temp==1)
//			LCD_drawButton(1,80,130,70,70, 20, RED,YELLOW,"Temp",2);
//	else
//			LCD_drawButton(1,80,130,70,70, 20, WHITE,BLUE,"Temp",2);
//	
//		baby_rec=GETCHAR1();
//           delay_ms(1000);
     switch(baby_rec){
			 case 'A' :	viber=1;
				 SetTarget(1);// 0-LCD , 1- uart  			 
	                LCD_printCenter(10, 215,"ALARM...BABY TO SAFE ROOM" , 3,GREEN,BLACK);   //hebrew	
                               LCD_drawButton(3,320, 130,70,70, 20, RED,YELLOW,"sms",2);
			                         LCD_drawButton(1,160, 130,70,70, 20, RED,YELLOW,"alarm",2);
										            					SetTarget(1); 
                                          printf("**0532304023");
				                                	 delay_ms(2000);
			                               		 printf("##ALARM...BABY TO SAFE ROOM");
		                            			 delay_ms(1000);
			                        		 printf("$$");
                                  delay_ms(2000);  
					                      	SetTarget(0); 
																  
                                 	 viber=0;
																	break;
			 case 'C' :	viber=1;
			 LCD_drawButton(3,320, 130,70,70, 20, RED,BLACK,"sms",2);
			 LCD_drawButton(2,240, 130,70,70, 20, RED,WHITE,"crying",2);
				          SetTarget(1);// 0-LCD , 1- uart  			 
	                LCD_printCenter(10, 220,"BABY IS CRYING" , 3,GREEN, BLACK);   //hebrew	
                              
										            					SetTarget(1); 
                                          printf("**0532304023");
				                                	 delay_ms(2000);
			                               		 printf("##BABY IS CRYING");
		                            			 delay_ms(1000);
			                        		 printf("$$");
                                  delay_ms(2000);  
					                      	SetTarget(0); 
		
                                 	 viber=0;
							
																	   
																	 
																	break;
			 case 'V' :		viber=1;
			              SetTarget(1);// 0-LCD , 1- uart  			 
	                LCD_printCenter(10, 215,"ROOM TEMP HIGH- VENT ON" , 3,GREEN,BLACK);   //hebrew	
                                LCD_drawButton(3,320, 130,70,70, 20, RED,YELLOW,"sms",2);
																 LCD_drawButton(1,80,130,70,70, 20, RED,YELLOW,"Temp",2);
										            					SetTarget(1); 
                                          printf("**0532304023");
				                                	 delay_ms(2000);
			                               		 printf("##BABYS ROOM TEMPERATURE HIGH- VENT ON");
		                            			 delay_ms(1000);
			                        		 printf("$$");
                                  delay_ms(2000);  
					                      	SetTarget(0); 
																	temp=1;
		                              
                                 
 																		 viber=0;
																	break;
			 
			 case 'v' :		viber=1;
			              			 
	                LCD_printCenter(10, 215," ROOM TEMP LOW- VENT OFF" , 3,GREEN,BLACK);   //hebrew	
                                LCD_drawButton(3,320, 130,70,70, 20, RED,YELLOW,"sms",2);
																LCD_drawButton(1,80,130,70,70, 20, GREEN,BLACK,"Temp",2);
										            					SetTarget(1); 
                                          printf("**0532304023");
				                                	 delay_ms(2000);
			                               		 printf("##BABYS ROOM TEMPERATURE LOW- VENT OFF");
		                            			 delay_ms(1000);
			                        		 printf("$$");
                                  delay_ms(2000);  
					                      	SetTarget(0); 
		                              
 
temp=0; 
 viber=0; 
																	break;
								 case 'M' :		viber=1;
			              			 
	                LCD_printCenter(5, 215,"MUSIC ON" , 3,GREEN,BLACK);   //hebrew	
                                LCD_drawButton(3,320, 130,70,70, 20, RED,YELLOW,"sms",2);
																LCD_drawButton(4,160, 250,70,70, 20, GREEN,BLACK,"music",2);
										            					SetTarget(1); 
                                          printf("**0532304023");
				                                	 delay_ms(2000);
			                               		 printf("##BABYS MUSIC ON");
		                            			 delay_ms(1000);
			                        		 printf("$$");
                                  delay_ms(2000);  
					                      	SetTarget(0); 
		                              
 
temp=0; 
 viber=0; 
																	break;
																	
		 
		 
		 }
		
}//while
}//MAIN

	//}//main
void MenuScreen() {
	LCD_fillScreen(BLACK);
	LCD_printCenter(0, 20,"PARENTS ROOM" , 4,YELLOW, BLACK);   		
	LCD_printCenter (0 ,70 ,"baby's room status",3, WHITE, BLACK);
	LCD_drawButton(1,80,130,70,70, 20, WHITE,BLUE,"Temp",2);
	LCD_drawButton(1,160, 130,70,70, 20, WHITE,BLUE,"alarm",2);
	LCD_drawButton(2,240, 130,70,70, 20, WHITE,BLUE,"crying",2);
	LCD_drawButton(3,320, 130,70,70, 20, WHITE,BLUE,"sms",2);
	LCD_drawButton(4,160, 250,70,70, 20, WHITE,BLUE,"music",2);
	LCD_setText2Color(WHITE,BLACK);
}
void playScreen() {
	LCD_fillScreen(BLACK);
	LCD_printCenter(0, 20,"PARENTS ROOM" , 4,YELLOW, BLACK);   		
	LCD_printCenter (0 ,70 ,"baby's room status",3, WHITE, BLACK);
	LCD_drawButton(1,80,150,70,70, 20, WHITE,BLUE,"Temp",2);
	LCD_drawButton(1,160, 150,70,70, 20, WHITE,BLUE,"alarm",2);
	LCD_drawButton(2,240, 150,70,70, 20, WHITE,BLUE,"crying",2);
	LCD_drawButton(3,320, 150,70,70, 20, WHITE,BLUE,"sms",2);
	
	LCD_setText2Color(WHITE,BLACK);
}
void Test_Color(void) {
	LCD_fillScreen(RED);
	delay_ms(1000);
	LCD_fillScreen(GREEN);
	delay_ms(1000);	
	LCD_fillScreen(BLUE);
	delay_ms(1000);
	LCD_fillScreen(BLACK);
}

void Font_test(void) {
	int x=1234;
	LCD_fillScreen(BLACK);
	LCD_print2C(20,30,"abcd",1,WHITE,BLACK);
	LCD_print2C(80,30,"xyz",2,WHITE,BLACK);
	LCD_printC(20,60,"3.95' ILI9488 320X480",3,YELLOW);
	LCD_printC(20,120,"Test 2017-11-23",3,GREEN);
	LCD_println("");
	LCD_setTextSize(2);
	LCD_setText1Color(WHITE);
	LCD_println("ABCDabcd1234");
	LCD_println("~!@#$%^&*()_+{}:<>?/|-+.");
	LCD_setTextSize(2);
	LCD_setText1Color(YELLOW);
	LCD_printHebln("אבגדהוזחטיכלמנסעפצקרשת");
	LCD_println("ABCDE");
	printf("x=%d  \n",x);
	printf("abcdABCD1234",x);
	while(T_IRQ);
}

void Pic_test(void) {
	LCD_fillScreen(BLACK);	
  LCD_DrawBitmap16(100, 100, gImage_argb2);
	LCD_DrawBitmap16(150, 150, gImage_argb2);
	LCD_DrawBitmap16(200, 200, gImage_argb2);
	while(T_IRQ);
}

void Test_shape(void) {
	LCD_fillScreen(BLACK);
	LCD_drawRect(10,20,100,100,RED); 
	LCD_fillRect(50,100,80,80,BLUE); 	
	LCD_fillRoundRect(100,150,40,40,10,YELLOW); 	
	LCD_drawCircle(120,120,30,GREEN);
	LCD_fillCircle(120,120,20,WHITE);
	LCD_drawTriangle(110,10,160,200,200,100,RED);
	LCD_fillTriangle(0,0,0,80,80,0,RED);
	while(T_IRQ);
}

