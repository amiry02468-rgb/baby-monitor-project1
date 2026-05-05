
#include "initsys.h"
#include "argb2.h"
#define READ_FROM_AMPLIFIER  0 
#define NUM_SAMPLES 200
#define CAL_NUM_SAMPLES 200
#define CAL_START_FREQ 200
#define CAL_END_FREQ 2000
#define CAL_STEP 100
#define CAL_SAMPLING_RATE 8000
#define CAL_NUM_BINS 19
#define CAL_PLOT_X 10
#define CAL_PLOT_Y 90
#define CAL_PLOT_W 300
#define CAL_PLOT_H 120



void Init_Device(void);
#include <math.h> 
int ADC_IN(int num);
void Calibration(void);
float goertzel_mag(int numSamples,int TARGET_FREQUENCY,int SAMPLING_RATE);
int PreprocessSamples(int numSamples);
//int ADC_IN(int num);
//void PreprocessSamples(void);
void PreprocessSamplesN(int numSamples);
//int IsAlarmDetected(int numofinstans,int mag);
//int IsAlarmDetected_trial();
xdata int g_lastMaxAbs = 0;


#define NUM_OF_FREQ_TO_CHECK 2 
xdata int  NumInstans[NUM_OF_FREQ_TO_CHECK]; 
struct WaveProperty  
{
	 int freq; 
	 int Th_mag;
	 int Th_NumInstans;
};


int IsAlarmDetected2(struct WaveProperty wave_property_arr[]);

//xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK]={{700,15,5},{900,10,5}};
//xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK]={{700,35,5},{800,35,4}};
/*

xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK] =
{
    {640, 35, 10},
    {800, 35, 8}
};
*/

 // red alarm - the best try !!!!!
xdata struct WaveProperty wave_property_arr_red_alarm[NUM_OF_FREQ_TO_CHECK] =
{
    {640, 70, 50},
    {800, 70, 50}
};

 // baby cray !!!!!
xdata struct WaveProperty wave_property_arr_baby_cray[NUM_OF_FREQ_TO_CHECK] =
{
    {840, 90, 40},
    {800, 90, 40}
};




/* xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK] =
{
    {640, 35, 10},
    {800, 35, 8}
};
*/ 

//xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK]={{700,40,8},{800,100,15},{900,60,9}};
//xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK]={{700,70,8},{800,100,15},{1000,60,9},{900,60,9}};// frequencies
//xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK]={{353,20,30},{905,20,20}};                 
//xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK]={{800,100,20}};
//xdata struct WaveProperty wave_property_arr[NUM_OF_FREQ_TO_CHECK]={{800,150,20}};
xdata char my_string[20];          
xdata int data_in[210];
xdata int cal_mags[CAL_NUM_BINS];
xdata num=0;






void Test_Color(void);
void MenuScreen();
void StartScreen();
void Font_test(void);
void Pic_test(void);
void Test_shape(void);
sbit Tx=P0^0;
	void putch(char tav)
		{
			SBUF0=tav;
			while(TI0==0);
			TI0=0;
		}
/*		
		char getc()
		{
			while(RI0==0);
			RI0=0;
			return SBUF0;
		}
		*/
		
		
		void shidur(char tav)
			{
				int i=0;
				delay_us(300);
				Tx=0;
				delay_us(104);
				for (i=0;i<8;i++)
				{
				if ((tav&0x01)==0)
					Tx=0;
				else
					Tx=1;
				delay_us(102);
				tav=tav/2;
				}
				Tx=1;
			delay_us(300);
			}
			
		code char mp_s[8] = {0x7E, 0xFF, 0x06, 0x16, 0x00, 0x00, 0x00, 0xEF}; 
		code char mp_3[8] = {0x7E, 0xFF, 0x06, 0x0F, 0x00, 0x01, 0x01, 0xEF}; 
		char mp3[8];
		int i;
			void effects(char dir, char track)
			{
				mp3[5] = dir;
				mp3[6] = track;
				for (i=0; i<8; i++)
			shidur(mp3[i]);
			}
sbit vent=P2^7;
sbit noise_sens=P2^1;

vent_off=0;
vent_on=1;
int tempsens;
int noise;
int i;
int v=0;
void main(void)
{
	S16 x=0, y=0,  ButtonNum;
	Init_Device();
	initSYS();
  StartScreen();
		delay_ms(1500);

	while(1)
	{
		MenuScreen();
		delay_ms(2000);
	  tempsens = ADC_IN(4);//p2^5   read temp from adc
   	LCD_print2C(20, 220, "babys room temp is:", 3, GREEN, BLACK);
    tempsens=tempsens/5;    
    printf("%d C  ",tempsens);
		
	  if (tempsens>21)
		{
	      vent=vent_on;
				LCD_print2C(20, 250, "vent   on:", 3,GREEN, BLACK);
			  LCD_drawButton(1,30, 100,100,60, 20, GREEN,BLUE,"VENTA",2);
			if (v==0)
			{
		 SetTarget(1); 
			  putch('V');
		SetTarget(0);
		}
			v=1;
	}
		else
		{   vent=vent_off;
			LCD_print2C(20, 250, "vent off:", 3, WHITE,BLACK);
			LCD_drawButton(1,30, 100,100,60, 20, WHITE,BLUE,"VENTA",2);
			if (v==1)
			{
	//	SetTarget(1); 
	//		  putch('v');
	//  SetTarget(0);
			}
			v=0;
		}
		 delay_ms(3500);
				LCD_print2C(20, 220, "                           ", 3, GREEN, BLACK);
			LCD_print2C(20, 250, "                             ", 3,GREEN, BLACK);
		//	LCD_print2C(10,200, "scanning alarm/crying baby:", 3, GREEN, BLACK);
	    delay_ms(3500);
	  // test noise 
	//	while(noise_sens==1);// wait for noise 
		//if (noise_sens==0)
		//{
			//while (IsAlarmDetected2(&wave_property_arr_red_alarm[0])==0);
			LCD_fillScreen(BLACK);
		for(i=0;i<1;i++)
	{
		LCD_print2C(20, 175, "scanning alarm freq:", 2, GREEN, BLACK);
		delay_ms(2000);
		if ((IsAlarmDetected2(wave_property_arr_red_alarm)==1))
		{
		//	LCD_print2C(20, 155, "scanning alarm freq:", 2, GREEN, BLACK);
	//	while (IsAlarmDetected2(wave_property_arr_red_alarm)==0);
		//noise = ADC_IN(READ_FROM_AMPLIFIER);//p2.0
   	LCD_print2C(20, 140, "RED ALARM DETECTED  :", 2, GREEN, BLACK);
		delay_ms(3000);
    //while(T_IRQ);
	//	SetTarget(1); 
	//		  putch('A');
	//	SetTarget(0);
		}
	}
	LCD_fillScreen(BLACK);
		for(i=0;i<1;i++)
	{
		
		LCD_print2C(20, 175, "scanning babys crying freq:", 2, GREEN, BLACK);
		delay_ms(2000);
		if((IsAlarmDetected2(wave_property_arr_baby_cray))==1)
		{
		//LCD_print2C(20, 155, "scanning babys crying freq:", 2, GREEN, BLACK);
		//while (IsAlarmDetected2(wave_property_arr_baby_cray)==0);
		//noise = ADC_IN(READ_FROM_AMPLIFIER);//p2.0
   	LCD_print2C(20, 155, ":", 2, GREEN, BLACK);
			delay_ms(3000);
 /*   SetTarget(1); 
			  putch('C');
		SetTarget(0);*/
		}
			SetTarget(1); 
			  putch('M');
		SetTarget(0);
		for(i=0;i<8;i++)
     	mp3[i]=mp_3[i];
	effects(1,4);
	delay_ms(2000);
		
		
	//MenuScreen();
	//LCD_print2C(10,200, "scanning alarm/crying baby:", 3, GREEN, BLACK);
	//delay_ms(500);
   // while(1); 
  //  printf("%d  ",noise);
			
		}
		
		
		}//while
	}//main
		//delay_ms(3000);
//while(noise_sens==1);	
	/*	if (noise_sens==0)
		{
				 noise = ADC_IN(16);//p2.0
   	LCD_print2C(20, 280, "babys  noise:", 3, GREEN, BLACK);
      
    printf("%d  ",noise);
			if(noise>830)
			{
	 	
			LCD_drawButton(2,190, 100,100,60, 20, RED,BLUE,"CRYING",2);
						SetTarget(1); 
			   putch('C');
					SetTarget(0);}
			else  if(noise<830)
			{
				LCD_drawButton(3,300, 100,100,60, 20, RED,BLUE,"ALARM",2);
						SetTarget(1); 
			   putch('A');
					SetTarget(0);}		
		else
			{
				LCD_drawButton(2,190, 100,100,60, 20,WHITE,BLUE,"CRYING",2);
				LCD_drawButton(3,300, 100,100,60, 20,WHITE,BLUE,"ALARM",2);
			 //  putchar('A');}
			}
		}
			
	//LCD_drawButton(1,80, 150,100,60, 20, GREEN,BLUE,"vent",2);
//delay_ms(2000);
		
//	vent=0;
//	LCD_drawButton(1,80, 150,100,60, 20, WHITE,BLUE,"vent",2);
//				delay_ms(2000);
	}
}
/*
	while(1) {
		if(!T_IRQ) {
			delay_ms(10);
			x = ReadTouchX();
			y = ReadTouchY();
			LCD_setCursor (25, 100);
			ButtonNum= ButtonTouch(x, y);
			printf("x=%d y=%d  b=%d   ", x, y,ButtonNum);

			if(ButtonNum==0){  
				Test_Color();
				MenuScreen();
			}
			else if(ButtonNum==1){ 
				Font_test();
				MenuScreen();
			}
			else if(ButtonNum==2){
				Pic_test();
				MenuScreen();				
			}
			else if(ButtonNum==3) {
				Test_shape();
				MenuScreen();
			}
		}	
	}
}
*/
void StartScreen() {
	LCD_fillScreen(BLACK);
	LCD_printCenter(0, 50,"ALERT SYSTEM BABYS ROOM" ,3,RED, BLACK);   
	LCD_printCenter (0 ,120,"BY Amir & Lian",4, PINK, BLACK);
	//LCD_clearButton();	
//	LCD_drawButton(1,80, 150,100,60, 20, WHITE,BLUE,"VENTA",2);
//	LCD_drawButton(2,190, 150,100,60, 20, WHITE,BLUE,"CRYING,",2);
//	LCD_drawButton(3,300, 150,100,60, 20, WHITE,BLUE,"ALARM",2);
	LCD_setText2Color(WHITE,BLACK);
}

void MenuScreen() {
	LCD_fillScreen(BLACK);
	LCD_printCenter(0, 10," BABYS ROOM" ,3,RED, BLACK);   
	
	LCD_clearButton();	
	LCD_drawButton(1,30, 100,100,60, 20, WHITE,BLUE,"VENTA",2);
	LCD_drawButton(2,150, 100,100,60, 20, WHITE,BLUE,"CRYING,",2);
	LCD_drawButton(3,270, 100,100,60, 20, WHITE,BLUE,"ALARM",2);
	LCD_drawButton(4,390, 100,100,60, 20, WHITE,BLUE,"MUSIC",2);
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

int ADC_IN(int num) {
  AMX0N = 0x1F;  // negtive input= GND
  AMX0P = num;
  delay_us(1);
  AD0BUSY = 1;  // start conversion
  while (!AD0INT)
    ;          // wait end convesion
  AD0INT = 0;  // clear ADC0 conversion complete flag
  return (ADC0);
}


#define MIN_SIGNAL_PP  8
#define TARGET_LEVEL   200
#define MAX_LEVEL      500
#define MAX_WEAK_BLOCKS 40


int IsAlarmDetected2(struct WaveProperty wave_property_arr[])
{
	
	int weakBlocks = 0;
  int signalStarted = 0;
	int mag_temp,detect;
	int j,i;
	int k=0;
	num=0;
	LCD_fillScreen(BLACK);
	LCD_print2C(20, 155, "scanning alarm/bany crying freq:", 2, YELLOW, BLACK);
	for(j=0;j<NUM_OF_FREQ_TO_CHECK;j++)
	{
		NumInstans[j] = 0;	
	}
	
	// from chatGPT //wait for real signal 
	while (signalStarted == 0)
	{
    for (i = 0; i < NUM_SAMPLES; i++)
    {
        data_in[i] = 2*ADC_IN(READ_FROM_AMPLIFIER);
        delay_us(112);
    }

    if (PreprocessSamples(NUM_SAMPLES) == 1)
    {
        signalStarted = 1;
      LCD_setCursor (10, 300);
			printf("real signal start processing "); 
			
    }
		else 
		{
		  LCD_setCursor (10, 300);
			printf("no real signal "); 
		}
  }
	
	
  for(j=0;j<600/NUM_OF_FREQ_TO_CHECK;j++)
	{		
	  for(i=0;i<NUM_SAMPLES;i++)   
		 { 
				data_in[i]=2*ADC_IN(READ_FROM_AMPLIFIER);	//P2.0 num=0 read from amplifier 
			 //data_in[i]=ADC_IN(READ_FROM_AMPLIFIER);	//P2.0 num=0 read from amplifier 
				delay_us(112);//dt sample
			  
	   }	
		 
/*		 
     //PreprocessSamples();
     if (PreprocessSamples(NUM_SAMPLES) == 0)
		 {
       	LCD_setCursor (10, 280);
				printf("no real signal "); 
			  weakBlocks++;
     }
		 //LCD_setCursor (10, 300);
     //printf("Real signal ");	
*/		 
		 if ((k % 20) == 0)
		{
    LCD_setCursor(10, 220);
    printf("maxAbs=%d weak=%d", g_lastMaxAbs, weakBlocks);
		}
		 
		 
    for(i=0;i<NUM_OF_FREQ_TO_CHECK;i++)
		 {
			 mag_temp=(int)(goertzel_mag(NUM_SAMPLES,wave_property_arr[i].freq,8000));
			 k++;	
	    //sprintf(my_string,"m=%3d f=%3d i=%d",mag_temp,wave_property_arr[i].freq,NumInstans[i]);
if ((k%20==0) || (k%20==1))
{
       
			LCD_setCursor (10, 100);
			if (i==0) 
			{  
				LCD_setCursor (10, 0);
				printf("m=%3d f=%3d i=%d",mag_temp,wave_property_arr[i].freq,NumInstans[i]);
			}

			if (i==1) 
			{  
				LCD_setCursor (10,100);
				printf("m=%3d f=%3d i=%d",mag_temp,wave_property_arr[i].freq,NumInstans[i]);
			}

			if (i==2) 
			{  
				LCD_setCursor (10, 150);
				printf("m=%3d f=%3d i=%d",mag_temp,wave_property_arr[i].freq,NumInstans[i]);
			}
			
			if (i==3) 
			{  
				LCD_setCursor (10, 200);
				printf("m=%3d f=%3d i=%d",mag_temp,wave_property_arr[i].freq,NumInstans[i]);
			}
		
} 			  
			 
		//	 if (i==1) LCD_print2C(20,100,my_string,2,RED, BLACK);
		//	 if (i==2) LCD_print2C(20,200,my_string,2,RED, BLACK);
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
			 		 
//		   if (i==0) lcd_string_line(1,0,my_string);
//			 if (i==1) lcd_string_line(2,0,my_string);
//			 if (i==2) lcd_string_line(1,0,my_string);
//       wait_ms(50); 			 
			 if (mag_temp > wave_property_arr[i].Th_mag)
			 {
				 //NumInstans[i] = NumInstans[i] + 1;
				 NumInstans[i]++;
			 }
		 }
 		 
	 }
	 
	 detect=1;
	 for(i=0;i<NUM_OF_FREQ_TO_CHECK;i++)
	 {
		 if (NumInstans[i] < wave_property_arr[i].Th_NumInstans)
		 {
        LCD_setCursor (10, 240);
				printf("detect = 0 due to f=%3d ins=%d",wave_property_arr[i].freq,NumInstans[i]);
  
			  detect = 0 ;
        break;
		 }			 
	 }
	 
	 
   /* check if toomany blocks were waeks  */
	if (weakBlocks > MAX_WEAK_BLOCKS)
	{
			LCD_setCursor(10, 230);
			printf("detect = 0 weak=%d", weakBlocks);

			detect = 0;
	}


	 
	 return(detect);
}





float goertzel_mag(int numSamples,int TARGET_FREQUENCY,int SAMPLING_RATE)
{

	int     k,i;
	float analog;
	float   floatnumSamples;
	float   omega,sine,cosine,coeff,q0,q1,q2,magnitude,real,imag;
	float   scalingFactor = numSamples / 2.0;

	floatnumSamples = (float) numSamples;
	k = (int) (0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
	omega = (2.0 * 3.14 * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0=0;
	q1=0;
	q2=0;

	for(i=0; i<numSamples; i++)
	{
		analog=data_in[i];
		q0 = coeff * q1 - q2 + analog;
		q2 = q1;
		q1 = q0;
	}

	// calculate the real and imaginary results
	// scaling appropriately
	real = (q1 - q2 * cosine) / scalingFactor;
	imag = (q2 * sine) / scalingFactor;

	magnitude = sqrt(real*real + imag*imag);

	return magnitude;
}




int PreprocessSamples(int numSamples)
{
    int i;
    long avg = 0;
    int maxAbs = 1;
    long temp;

    for (i = 0; i < numSamples; i++)
        avg += data_in[i];

    avg = avg / numSamples;

    for (i = 0; i < numSamples; i++)
    {
        data_in[i] = data_in[i] - avg;

        if (data_in[i] < 0)
        {
            if (-data_in[i] > maxAbs)
                maxAbs = -data_in[i];
        }
        else
        {
            if (data_in[i] > maxAbs)
                maxAbs = data_in[i];
        }
    }
    
		g_lastMaxAbs = maxAbs;
    /*if the real signal is small probably there is no real signal  */
    if (maxAbs < MIN_SIGNAL_PP)
        return 0;

    /* programmble dynamic amplifier  */
    for (i = 0; i < numSamples; i++)
    {
        temp = (long)data_in[i] * TARGET_LEVEL / maxAbs;

        if (temp > MAX_LEVEL)
            temp = MAX_LEVEL;

        if (temp < -MAX_LEVEL)
            temp = -MAX_LEVEL;

        data_in[i] = (int)temp;
    }

    return 1;
}



void Calibration(void)
{
    int i, f, idx;
    int maxMag;
    int bar_w;
    int h, x, y;

    LCD_fillScreen(BLACK);
    LCD_print2C(10, 10, "CALIBRATION", 2, WHITE, BLACK);
    LCD_print2C(10, 40, "Play tone. Touch to exit.", 1, WHITE, BLACK);

    bar_w = CAL_PLOT_W / CAL_NUM_BINS;
    if (bar_w < 3) bar_w = 3;

    while (T_IRQ)
    {
        for (i = 0; i < CAL_NUM_SAMPLES; i++)
        {
            data_in[i] = 2 * ADC_IN(READ_FROM_AMPLIFIER);
            delay_us(112);
        }

        //PreprocessSamplesN(CAL_NUM_SAMPLES);

        maxMag = 1;
        idx = 0;
        for (f = CAL_START_FREQ; f <= CAL_END_FREQ; f += CAL_STEP)
        {
            cal_mags[idx] = (int)(goertzel_mag(CAL_NUM_SAMPLES, f, CAL_SAMPLING_RATE));
            if (cal_mags[idx] > maxMag)
                maxMag = cal_mags[idx];
            idx++;
        }

        LCD_fillRect(CAL_PLOT_X, CAL_PLOT_Y, CAL_PLOT_W, CAL_PLOT_H, BLACK);

        for (i = 0; i < CAL_NUM_BINS; i++)
        {
            h = (cal_mags[i] * (CAL_PLOT_H - 2)) / maxMag;
            if (h < 1) h = 1;
            x = CAL_PLOT_X + (i * bar_w);
            y = CAL_PLOT_Y + (CAL_PLOT_H - h);
            LCD_fillRect(x, y, bar_w - 2, h, GREEN);
        }
    }
    while(!T_IRQ);
}







