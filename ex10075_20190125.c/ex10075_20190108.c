/* --------------------------------
program:ex10075_20190108
revise date:2019.1.24
mcu: sn8f5713
 ----------------------------------*/
 
#include "sn8f5713.h" 
#include "ex10075.h"


volatile Bytebits Bbituse;//tag relate to adc
#define bituse Bbituse.Byte
#define adc_command 			Bbituse.Bits.bit0
#define adc_convert_tag 	Bbituse.Bits.bit1
//#define vt_check_command 	Bbituse.Bits.bit2
#define vo_command 				Bbituse.Bits.bit3

#define vin_command				Bbituse.Bits.bit4
#define dcin_command			Bbituse.Bits.bit5

#define vb_check_tag			Bbituse.Bits.bit7
//#define vt_check_tag			Bbituse.Bits.bit6

volatile Bytebits Bbituse1;//tag relate to key press & operation
#define bituse1 Bbituse1.Byte
//key press tag
#define key_press_tag	Bbituse1.Bits.bit0//key press tag
#define kps_tag				Bbituse1.Bits.bit1//key press steady tag
#define krs_tag				Bbituse1.Bits.bit2//key relax steady tag
//long press key tag 
#define klp_tag				Bbituse1.Bits.bit3//key long press tag
#define klp_count_tag Bbituse1.Bits.bit4//key long press count tag


volatile Bytebits Bbituse2;
#define bituse2 Bbituse2.Byte
#define c_1			Bbituse2.Bits.bit0//led flicker 1hz	
#define c_2			Bbituse2.Bits.bit1//led flicker 0.5hz	
#define c_3			Bbituse2.Bits.bit2//led operating disp
#define c_4			Bbituse2.Bits.bit3//timer0 

#define sleep_tag 		Bbituse2.Bits.bit4
#define led_disp_tag 	Bbituse2.Bits.bit5
#define charge_tag 		Bbituse2.Bits.bit6
#define chrg_full_tag Bbituse2.Bits.bit7

volatile Bytebits Bbituse3;
#define bituse3 Bbituse3.Byte
#define vin_tag 	Bbituse3.Bits.bit0
#define vdc_tag 	Bbituse3.Bits.bit1
#define pg_tag 		Bbituse3.Bits.bit2


//next 3-bit effect to load op can't be changed
#define ot55_tag	Bbituse3.Bits.bit5//temperature over 55C
#define ot65_tag	Bbituse3.Bits.bit6//temperature over 65C
#define ut_tag 		Bbituse3.Bits.bit7//under temperature or ntc not connect

volatile Bytebits Bbituse4;//tag relate to bat. volt
#define bituse4 Bbituse4.Byte
//charge
#define lev1c_tag 		Bbituse4.Bits.bit0//1:cap.>=25%;0:cap<25%
#define lev2c_tag 		Bbituse4.Bits.bit1//cap.>=50%
#define lev3c_tag 		Bbituse4.Bits.bit2//cap.>=75%
#define lev4c_tag 		Bbituse4.Bits.bit3//bat. full
//discharge
#define lev1d_tag 		Bbituse4.Bits.bit4//cap.<=25%
#define lev2d_tag 		Bbituse4.Bits.bit5//cap.<=50%
#define lev3d_tag 		Bbituse4.Bits.bit6//cap.<=75%
#define lev4d_tag 		Bbituse4.Bits.bit7//cap.>75%

volatile Bytebits Bbituse5;
#define bituse5 Bbituse5.Byte
#define uv_tag 		Bbituse5.Bits.bit0//under volt.
#define uvd_end 	Bbituse5.Bits.bit1//under volt. delay time end



unsigned int intCount = 0;

//key press variable
unsigned char t_kps = 0;//key press steady time
unsigned char t_krs = 0;//key relax steady time
//long press key variable
unsigned char t_klp = 0;//key long press last time

unsigned char t_uvd = 0;//under volt. delay time
unsigned char t_sd = 0;//sleep delay time

unsigned int vb = 0;//bat. volt.
unsigned int vt = 0;//temperature volt.
unsigned char adc_count = 0;
unsigned char s_led = 0;//led disp. status

void gpio_init(void)
{
		//port0
		P0 = 0;
		P0M = 0xbf;
		P0CON = 0x00;
		P0UR = 0x40;
	
		//port1
		P1 = 0;
		P1M = 0x2f;
		P1CON = 0;
		P1UR = 0x40;
		//port1 wake up
		P1W = 0x90;
	
		//port2
		P2 = 0;
		P2M = 0xe7;
		P2CON = 0x18;
		P2UR = 0;
	
}

void clock_init(void)
{
	CLKSEL = 0x05;//Fcpu=Fosc/4=8M
	CLKCMD = 0x69;
	CKCON = 0x00;//IROM=Fcpu/1=8M	
	SYSMOD |= 0x01;//flosc keep running in STOP mode
}

//initial T0
void timer0_init(void)
{	
		ET0 = 0;//T0 interrupt disable		
		TR0 = 0;//T0 function disable
		TMOD = 0;//value initial
		TCON0 = 0;//value initial
	
		//7.8ms interrupt
		TL0 = 131;
		TH0 = 131;
		//T0 mode2, clock source from Flsoc
		TMOD |= (T0Mode2 | T0ClkExt);
		//F_EXT0=Flosc,divider=1
		TCON0 |= (T0ExtDiv1 | T0ExtFlosc);
	
		ET0 = 1;//T0 interrupt enable		
		TR0 = 1;//T0 function enable
		//EAL = 1;//enable gobal int.	
}

void timer0_wakeup(void)
{	
		ET0 = 0;//T0 interrupt disable		
		TR0 = 0;//T0 function disable
		TMOD = 0;//value initial
		TCON0 = 0;//value initial
	
		//8min interrupt
		TL0 = 0x00;
		TH0 = 0x06;
		//T0 mode1, clock source from Flsoc
		TMOD |= (T0Mode1 | T0ClkExt);
		//F_EXT0=Flosc,divider=128
		TCON0 |= (T0ExtDiv128 | T0ExtFlosc);
	
		ET0 = 1;//T0 interrupt enable		
		TR0 = 1;//T0 function enable
}

void adc_init(void)
{
		//adc clock source
		ADR |= (1 << 7);//adc clock source=fosc
		ADR |= AdcRateDiv8;//adc clock rate
		//adc Vref
		VREFH &= (0 << 7);//enable internal Vref
		VREFH |= VREF2V;//Vref=2v
		//enable adc modul
		ADM |= (1 << 7);//adc enable
	
}

void var_init(void)
{
		bituse = 0;
		bituse1 = 0;
		bituse2 = 0;
		bituse3 = 0;
		bituse4 = 0;
		bituse5 = 0;
		
		led1 = LED_OFF;
		led2 = LED_OFF;
		led3 = LED_OFF;
		led4 = LED_OFF;
		led0 = LED_OFF;

		sw_vin = IN_OFF;//vin off
		sw_dcin = IN_OFF;//dcin off
		sw_vo = VO_OFF;//output off
		sw_chrg = CHRG_OFF;//charge ic disable
		sw_vt = VT_ON;//ntc switch on
		sw_vb = VB_ON;//ntc switch on
}

void clrwdt(void)
{
	WDTR = 0x5a;
}

void nop(unsigned char n)
{
		unsigned char i = 0;
		for(i; i <= n; i++)
		{
			clrwdt();
			_nop_();
		}
}

void init(void)
{
		clock_init();
		gpio_init();
		timer0_init();
		//int_init();
		adc_init();
		var_init();

}

void key_check(void)
{		
		//key press check
		if(KEY_RELEASE == key)
				{
						//kps_tag reset
						kps_tag = 0;
						t_kps = 0;
						//key release ack.
						if(krs_tag)
								key_press_tag = 0;		
				}
				else 
						{
								//krs_tag reset
								krs_tag = 0;
								t_krs = 0;
								//key press ack.
								if(kps_tag)
									key_press_tag = 1;				
						}																	
				
		//key long press count
		if(klp_tag && (!klp_count_tag))
				{
						klp_count_tag = 1;
						vo_command = !vo_command;
				}
		//key long press tag reset
		if(!key_press_tag)
				{
						//key long press tag reset
						klp_tag = 0;
						t_klp = 0;
						klp_count_tag = 0;
				}		
				
}

void adc_channel(unsigned chs)
{
		ADM &= 0xe0;
		ADM |= chs;//set adc channel
		ADR |= (1 << 6);//adc channel enable		
}

unsigned int adc_value(void)
{
		unsigned char adc_h = 0;
		unsigned char adc_l = 0;		
		ADM |= (1 << 6);//start adc
		while(!(ADM & 0x20));
		adc_h = ADB;
		adc_l = ADR;
		return (((unsigned int)adc_h << 4) & 0x0ff0) | (adc_l & 0x0f);
		
}


//temperture check
void vt_check(void)
{
		//over temp.
		if(vt <= VT65)
				ot65_tag = 1;
				else if(vt <= VT55 )
						ot55_tag = 1;
		//under temp.
		if(vt >= VTNEG20)
				ut_tag = 1;
		//ot_tag reset
		if(vt > VT55)
				ot65_tag = 0;
		if(vt > VT45)
				ot55_tag = 0;
		//ut_tag reset
		if(vt < VTNEG5)
				ut_tag = 0;
}

/*------------------vb check.
cap.level: 
lev3 = 75%
lev2 = 50%
lev1 = 25%
-------------------------*/
void vb_check(void)
{	
	
		if(charge_tag)
				{
						if(((vb > VBF) || chrg_full_tag) || lev4c_tag)
								lev4c_tag = 1;
								else if((vb >= LEV3C) || lev3c_tag)//cap.>75%
										lev3c_tag = 1;
								else if((vb >= LEV2C) || lev2c_tag)//50%<cap.<75%
										lev2c_tag = 1;
								else if((vb >= LEV1C) || lev1c_tag)//25%<cap.<50%
										lev1c_tag = 1;
	
						//charge lev_tag reset	
						if(vb < VBFR)	
								lev4c_tag = 0;								
						if(vb < LEV3CR)
								lev3c_tag = 0;
						if(vb < LEV2CR)
								lev2c_tag = 0;
						if(vb < LEV1CR)
								lev1c_tag = 0;

						s_led = bituse4 & 0x0f;

				}	
				else//if(!charge_tag)
						{
								if((vb <= VB_LOW) || uv_tag)//under volt.
										{
												uv_tag = 1;
												bituse4 &= 0x0f;
										}
										else if((vb <= LEV1D) || lev1d_tag)//cap.<25%	
												{
														lev1d_tag = 1;
														bituse4 &= 0x1f;
												}
										else if((vb <= LEV2D) || lev2d_tag)//cap.=50-25%
												{
														lev2d_tag = 1;			
														bituse4 &= 0x3f;
												}
										else if((vb <= LEV3D) || lev3d_tag)//cap.=75-50%
												{
														lev3d_tag = 1;
														bituse4 &= 0x7f;
												}
										else lev4d_tag = 1;
										
								//uv_tag reset		
								if(vb > VB_LOWR)
										uv_tag = 0;	
								//discharge lev_tag reset
								if(vb > LEV1DR)
									lev1d_tag = 0;
								if(vb > LEV2DR)
									lev2d_tag = 0;
								if(vb > LEV3DR)
									lev3d_tag = 0;	

								s_led = (bituse4 >> 4) & 0x0f;

						}
								
}

void charge_check(void)
{	
		//vin_tag
		if(vin)
				{
						nop(100);
						if(vin)
							vin_tag = 1;
				}else
						{
								nop(100);
								if(!vin)
									vin_tag = 0;
						}
		//vdc_tag
		if(vdc)
				{
						nop(100);
						if(vdc)
							vdc_tag = 1;
				}else
						{
								nop(100);
								if(!vdc)
									vdc_tag = 0;
						}
		//pg_tag				
		if(pg)
				{
						nop(100);
						if(pg)
							pg_tag = 1;
				}else
						{
								nop(100);
								if(!pg)
									pg_tag = 0;
						}						
				
		//charge check
		if(vin_tag || vdc_tag)
				charge_tag = 1;
				else charge_tag = 0;
		if(charge_tag && pg_tag)
				chrg_full_tag = 1;
				else chrg_full_tag = 0;		
}

//operation
void op(void)
{
		//charge input control
		if((!ot55_tag) && (!ot65_tag) && (!ut_tag))
				{
						sw_chrg = CHRG_ON;
						if(vin_tag && vdc_tag) 
								{
										if(!dcin_command)
												{
														vin_command = 1;
														dcin_command = 0;
												}
								}
								else if(vin_tag)
										{
												if(!dcin_command)
													{
															vin_command = 1;
															dcin_command = 0;
													}
										}
								else if(vdc_tag)
										{
												dcin_command = 1;
												vin_command = 0;
										}
								else
										{
												vin_command = 0;
												dcin_command = 0;
										}										
										
				}
				else
						{
								vin_command = 0;
								dcin_command = 0;	
								sw_chrg = CHRG_OFF;
						}	
		if(vin_command)
				sw_vin = IN_ON;
				else sw_vin = IN_OFF;
		if(dcin_command)
				sw_dcin = IN_ON;
				else sw_dcin = IN_OFF;	
		
		//output control
		if(vo_command && (!ot65_tag) && (!uvd_end))
				sw_vo = VO_ON;
				else sw_vo = VO_OFF;
		
		//led disp. tag
		//condition:vo_command/charge
		if(vo_command || charge_tag)
				led_disp_tag = 1;
				else led_disp_tag = 0;
		//test
		//led_disp_tag = 1;
}

//loe power dissipation
void low_power_dissipation(void)
{
		//sleep
		if(sleep_tag)
				{			
						sw_chrg = CHRG_OFF;
						sw_vb = VB_OFF;
						sw_vt = VT_OFF;
						led0 = LED_OFF;
						ADM &= (0 << 7);//adc disable					  
					  timer0_wakeup();					
						//sleep tag reset
						sleep_tag = 0;
						t_sd = 0;
						//sleep
						STOP();						
						timer0_init();
						ADM |= (1 << 7);//adc enable					
						sw_vb = VB_ON;
						sw_vt = VT_ON;
						//sw_chrg = CHRG_ON;
						adc_command = 1;
					
				}
}


//timer0 int.
void timer0_isr(void) interrupt ISRTimer0
{
	intCount++;
	c_4 = ~c_4;
		//timer 1/4s
	if(0==(intCount & ONE_4_SECOND_COUNT_MASK))
		{	
				//last time of key long press 
				if(key_press_tag && (!klp_tag))
						{
								t_klp++;
								if(t_klp >= TIME_KLP)
										klp_tag = 1;
						}	
				
		}//end 1/4s timer

		//timer 1/2s
	if(0==(intCount & ONE_2_SECOND_COUNT_MASK))
		{
				c_2 = !c_2;
		}//end 1/2s timer
		
	//timer 1s 
	if(0 == (intCount & ONE_SECOND_COUNT_MASK))	
		{
				//under volt. cut off delay
				if(uv_tag && vo_command && (!uvd_end) )
						{
								t_uvd++;
								if(t_uvd >= TIME_UVD)
										uvd_end = 1;
						}
				//uv_tag reset
				if((!uv_tag) || charge_tag || (!vo_command)) 
						{
								t_uvd = 0;
								uvd_end = 0;
						}
						
				//sleep delay timer
				//if(key & (!sleep_tag))//for test
				if((!led_disp_tag) && (!adc_command) && (!sleep_tag))
						{
								t_sd++;
								if(t_sd >= TIME_SD)
										sleep_tag = 1;
						}
						
		}//end 1s timer

		//key steady timer	
		//key press steady timer
		if((KEY_PRESS_DOWN == key) && (0 == kps_tag))
				{
						t_kps++;
						if(t_kps >= TIME_KS)
								kps_tag = 1;	
				}
		//key relax steady timer
		if((KEY_RELEASE == key) && (0 == krs_tag))
				{
						t_krs++;
						if(t_krs >= TIME_KS)
								krs_tag = 1;	
				}

	
		//led flicker timer
		c_1 = LED_OFF;
		if((intCount & LED_FLICKER_COUNT_MASK) < LED_FLICKER_COUNT_END)
				c_1 = LED_ON;
		//led operating disp.	
		c_3 = LED_OFF;		
		if((intCount & LED_OP_DISP_COUNT_MASK) < LED_OP_DISP_COUNT_END)
				c_3 = LED_ON;			
		//operating indicator
		led0 = c_3;
		
		//timer0 interrupt test
		//led0 = c_4;
		
		//adc command
		if(0 == (intCount & TIME_ADC_MASK))
			{
					adc_command = 1;
					adc_convert_tag = ~adc_convert_tag;
			}

		//led_disp
		if(led_disp_tag)
		{		
				if(ot55_tag || ot65_tag || ut_tag)
						{
								led4 = c_2;
								led3 = c_2;
								led2 = c_2;
								led1 = c_2;														
						}
				else{
				if((s_led & 0x08) != 0)
						{
								led4 = LED_ON;
								led3 = LED_ON;
								led2 = LED_ON;
								led1 = LED_ON;
						}
				else if((s_led & 0x04) != 0)//rsoc=75
						{
								if(charge_tag)
										led4 = c_1;
										else led4 = LED_OFF;
								led3 = LED_ON;
								led2 = LED_ON;
								led1 = LED_ON;								
						}
				else if((s_led & 0x02) != 0)//rsoc=50
						{
								led4 = LED_OFF;
								if(charge_tag)
										led3 = c_1;
										else led3 = LED_OFF;
								led2 = LED_ON;
								led1 = LED_ON;								
						}						
				else if((s_led & 0x01) != 0)//rsoc=25
						{
								led4 = LED_OFF;
								led3 = LED_OFF;
								if(charge_tag)
										led2 = c_1;
										else led2 = LED_OFF;
								led1 = LED_ON;								
						}	
				else //s_led=0x00
						{
								led4 = LED_OFF;
								led3 = LED_OFF;
								led2 = LED_OFF;
								//if(charge_tag)
										led1 = c_1;
										//else led1 = LED_ON;	
						}	
				}
		}else//if(!led_disp_tag)
				{
						led4 = LED_OFF;
						led3 = LED_OFF;
						led2 = LED_OFF;
						led1 = LED_OFF;						
				}	
					
			
}

main()
{
		init();
		EAL = 1;//enable gobal int.	
		while (1)
		{
				clrwdt();
				key_check();

				if(adc_command)
					{
						if(!adc_convert_tag)
							{
								//vb adc
								adc_channel(VB);
								nop(100);
								vb = adc_value();
								//convert to vt channal advance
								adc_channel(VT);
								adc_count++;
							}
							else
								{									
									//vt adc
									adc_channel(VT);
									nop(100);
									vt = adc_value();						
									//convert to vb channal advance
									adc_channel(VB);
									adc_count++;
								}
						if(adc_count >= 2)	
							{
								adc_count = 0;
								adc_command = 0;
							}							
					}
				vb_check();
				vt_check();
				charge_check();	
				op();
				//sleep
				low_power_dissipation();										
					
		}//end while(1)
}