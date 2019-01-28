/*------------------------------
program name:  ex10075.h
perfect date:2019.1.24
mcu:sn8f5713
 
-------------------------------*/ 
#ifndef _EX10075_H_
#define _EX10075_H_

		typedef union BYTEBITSDEF{
			unsigned char Byte;
			struct{
				unsigned char bit0:1;
				unsigned char bit1:1;
				unsigned char bit2:1;
				unsigned char bit3:1;
				unsigned char bit4:1;
				unsigned char bit5:1;
				unsigned char bit6:1;
				unsigned char bit7:1;
			} Bits;
		
} Bytebits;

//port define
//led
#define led0 P13
#define led1 P04
#define led2 P03
#define led3 P01
#define led4 P00
//key
#define key 	P06

//switch
#define sw_vo P05//output
#define sw_vt P07//temp.check
#define sw_vb P22//bat. volt. check
#define sw_dcin P21//dc input from socket
#define sw_vin P15//dc input from elastic pole
#define sw_chrg P20//charge

#define vdc P17//dc input from socket check
#define vin P14//dc input from elastic pole check
#define pg P16//charge status check

//user-defined status
#define KEY_PRESS_DOWN 0
#define KEY_RELEASE	1

#define LED_ON 1
#define LED_OFF 0

#define VO_ON 	1
#define VO_OFF 	0

#define IN_ON 	1
#define IN_OFF 	0

#define CHRG_ON 	0
#define CHRG_OFF 	1 

#define VB_ON 	1
#define VB_OFF 	0

#define VT_ON 	0
#define VT_OFF 	1

//external int. trigger edge
#define INT0Rising 	(1 << 0)//trigger by rising edge
#define INT0Falling	(2 << 0)//trigger by falling edge
#define INT0LevChge	(3 << 0)//tigger by level change
#define EINT0 			(1 << 0)//interrupt enable

#define INT1Rising 	(1 << 2)
#define INT1Falling	(2 << 2)
#define INT1LevChge	(3 << 2)
#define EINT1 			(1 << 2)

#define INT2Rising 	(1 << 4)
#define INT2Falling	(2 << 4)
#define INT2LevChge	(3 << 4)
#define EINT2 			(1 << 2)

//timer0
//R=TMOD
//T0M=bit[1:0]
#define T0Mode0 (0 << 0)//T0 mode0 13bit counter
#define T0Mode1 (1 << 0)//T0 mode1 16bit counter
#define T0Mode2 (2 << 0)//T0 mode2 8bit auto-reload counter
#define T0Mode3 (3 << 0)//T0 mode3 T0 two 8bit counter
//T0GATE=bit3
#define T0Gate (1 << 3)//T0 gating clock by INT0
//T0CT=bit2
#define T0ClkFcpu (0 << 2)//T0 clock source from Fcpu/12 
#define T0ClkExt 	(1 << 2) //T0 clock source from F_EXT0

//R=TCON0
//T0EXT=bit7
#define T0ExtFosc 	(0 << 7)//T0 clock from external Fosc
#define T0ExtFlosc 	(1 << 7)//T0 clock from external Flsoc
//T0RATE=bit[6:4]
#define T0ExtDiv128 (0 << 4) 
#define T0ExtDiv64 	(1 << 4)
#define T0ExtDiv32 	(2 << 4)
#define T0ExtDiv16 	(3 << 4)
#define T0ExtDiv8 	(4 << 4)
#define T0ExtDiv4 	(5 << 4)
#define T0ExtDiv2 	(6 << 4)
#define T0ExtDiv1 	(7 << 4)

//R=ADM
//adc channel 
//CHS=bit[4:0]  
#define AIN0 0
#define AIN1 1
#define AIN2 2
#define AIN3 3
#define AIN4 4
#define AIN5 5
#define AIN6 6
#define AIN7 7
#define AIN8 8//p20
#define AIN9 9
#define AIN10 10//p22
#define AIN11 11
#define AIN12 12
//AIN0 13 reserved
#define AIN14 14
#define VDD 15
#define VSS 16

#define VB AIN11
#define VT AIN12

//adc Vref
#define VREF2V (0 << 0)
#define VREF3V (1 << 0)
#define VREF4V (2 << 0)
#define VREFVDD (3 << 0)

//adc clock rate
//R=ADR
//ADCKS=bit[5:4]
#define AdcRateDiv16 	(0 << 4)
#define AdcRateDiv8		(1 << 4)
#define AdcRateDiv1 	(2 << 4)
#define AdcRateDiv2 	(3 << 4)


//timer constant
#define INTCOUNT 128

#define ONE_SECOND_COUNT (INTCOUNT << 0)//1s
#define ONE_SECOND_COUNT_MASK ONE_SECOND_COUNT-1

#define ONE_2_SECOND_COUNT (INTCOUNT >> 1)	//1s/(2^1) = 1/2 s
#define ONE_2_SECOND_COUNT_MASK ONE_2_SECOND_COUNT-1

#define ONE_4_SECOND_COUNT (INTCOUNT >> 2)	//1s/(2^2) = 1/4 s
#define ONE_4_SECOND_COUNT_MASK ONE_4_SECOND_COUNT-1

//led filcker
#define LED_FLICKER_COUNT	INTCOUNT
#define LED_FLICKER_COUNT_MASK 	LED_FLICKER_COUNT-1
#define LED_FLICKER_COUNT_END	(INTCOUNT >> 2)
//led operating disp
#define LED_OP_DISP_COUNT (INTCOUNT << 3)
#define LED_OP_DISP_COUNT_MASK 	LED_OP_DISP_COUNT-1
#define LED_OP_DISP_COUNT_END	3

//adc time
#define TIME_ADC (INTCOUNT << 0)	//1s*(2^2) = 4 s
#define TIME_ADC_MASK TIME_ADC-1

//1= 8ms
#define TIME_KS 6//key steady time=6*8ms

//1= 1/4s
#define TIME_KLP 8//key long press last time

//1=1s
#define TIME_UVD 180// under volt. delay 
#define TIME_SD 10//sleep delay time

//temperature
#define VT45	0x0252//45C
#define VT55 	0x01fe//50C
#define VT65 	0x0148//65C
#define VTNEG20 0x0f75//-20C
#define VTNEG5 	0x0add//-5C

//bat. volt
//under volt.
#define VB_LOW 	0x0901//3000mv
#define VB_LOWR 0x099b//3200mv
//full volt.
#define VBF 		0x0c81//4166mv
#define VBFR		0x0c35//4066mv

//vb level
//under condition of discharge
//great power bat. data
#define LEV3D		0x0bbc//3909mv
#define LEV2D		0x0ad2//3605mv
#define LEV1D		0x0aa1//3541mv
//release volt.
#define VRD 0x27//50mv
#define LEV3DR LEV3D+VRD
#define LEV2DR LEV2D+VRD
#define LEV1DR LEV1D+VRD

//under condition of charge
#define LEV3C		0x0c00//3996mv
#define LEV2C		0x0b52//3771mv
#define LEV1C		0x0aed//3639mv
//release volt.
#define VRC 0x27//50mv
#define LEV3CR LEV3C-VRC
#define LEV2CR LEV2C-VRC
#define LEV1CR LEV1C-VRC

#endif