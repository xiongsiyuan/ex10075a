/*--------------------------------------------------------------------------
SN8F5713.H

Header file for SNOiX SN8F5713 microcontroller.
Copyright (c) 2017 SONiX Technology Co., Ltd.

Version 1.0    2017-10-12
--------------------------------------------------------------------------*/

#ifndef __SN8F5713_H__
#define __SN8F5713_H__

/*      Register      */
sfr     P0       = 0x80;
  sbit  P07      = P0^7;
  sbit  P06      = P0^6;
  sbit  P05      = P0^5;
  sbit  P04      = P0^4;
  sbit  P03      = P0^3;
  sbit  P02      = P0^2;
  sbit  P01      = P0^1;
  sbit  P00      = P0^0;
sfr     SP       = 0x81;
sfr     DPL      = 0x82;
sfr     DPH      = 0x83;
sfr     WDTR     = 0x86;
sfr     PCON     = 0x87;
sfr     TCON     = 0x88;
  sbit  TF1      = TCON^7;
  sbit  TR1      = TCON^6;
  sbit  TF0      = TCON^5;
  sbit  TR0      = TCON^4;
  sbit  IE1      = TCON^3;
  sbit  IE0      = TCON^1;
sfr     TMOD     = 0x89;
sfr     TL0      = 0x8A;
sfr     TL1      = 0x8B;
sfr     TH0      = 0x8C;
sfr     TH1      = 0x8D;
sfr     CKCON    = 0x8E;
sfr     PEDGE    = 0x8F;
sfr     P1       = 0x90;
  sbit  P17      = P1^7;
  sbit  P16      = P1^6;
  sbit  P15      = P1^5;
  sbit  P14      = P1^4;
  sbit  P13      = P1^3;
  sbit  P12      = P1^2;
  sbit  P11      = P1^1;
  sbit  P10      = P1^0;
sfr     P1W      = 0x91;
sfr     DPC      = 0x93;
sfr     PECMD    = 0x94;
sfr16   PEROM    = 0x95;
sfr     PEROML   = 0x95;
sfr     PEROMH   = 0x96;
sfr     PERAM    = 0x97;
sfr     S0CON    = 0x98;
  sbit  SM0      = S0CON^7;
  sbit  SM1      = S0CON^6;
  sbit  SM20     = S0CON^5;
  sbit  REN0     = S0CON^4;
  sbit  TB80     = S0CON^3;
  sbit  RB80     = S0CON^2;
  sbit  TI0      = S0CON^1;
  sbit  RI0      = S0CON^0;
sfr     S0BUF    = 0x99;
sfr     IEN2     = 0x9A;
sfr     P0CON    = 0x9E;
sfr     P1CON    = 0x9F;
sfr     P2       = 0xA0;
  sbit  P25      = P2^5;
  sbit  P24      = P2^4;
  sbit  P23      = P2^3;
  sbit  P22      = P2^2;
  sbit  P21      = P2^1;
  sbit  P20      = P2^0;
sfr     PW1M	 = 0xA1;
sfr16   PW1Y	 = 0xA2;
sfr     PW1YL    = 0xA2;
sfr     PW1YH    = 0xA3;
sfr16   PW10D    = 0xA4;
sfr     PW10DL   = 0xA4;
sfr     PW10DH   = 0xA5;
sfr16   PW11D    = 0xA6;
sfr     PW11DL   = 0xA6;
sfr 	PW11DH	 = 0xA7;
sfr     IEN0     = 0xA8;
  sbit   EAL     = IEN0^7;
  sbit   EI2C    = IEN0^6;
  sbit   EU0RX   = IEN0^5; 
  sbit   EU0TX   = IEN0^4;
  sbit   ET1     = IEN0^3;
  sbit   EX1     = IEN0^2;
  sbit   ET0     = IEN0^1;
  sbit   EX0     = IEN0^0;
sfr     IP0      = 0xA9;
sfr     S0RELL   = 0xAA;
sfr16   PW12D    = 0xAB;
sfr     PW12DL   = 0xAB;
sfr     PW12DH   = 0xAC;
sfr16   PW13D    = 0xAD;
sfr     PW13DL   = 0xAD;
sfr     PW13DH   = 0xAE;
sfr16	CSC		 = 0xB1;
sfr     CSCH     = 0xB1;
sfr     CSCL     = 0xB2;
sfr     CCAL     = 0xB3;
sfr     PWCH     = 0xB6;
sfr     IP1      = 0xB9;
sfr     S0RELH   = 0xBA;
sfr16   PW14D    = 0xBB;
sfr     PW14DL   = 0xBB;
sfr     PW14DH   = 0xBC;
sfr16   PW15D    = 0xBD;
sfr     PW15DL   = 0xBD;
sfr     PW15DH   = 0xBE;
sfr     IRCON2   = 0xBF;
sfr     CSCON    = 0xC0;
  sbit  CSEN     = CSCON^7;
  sbit  CSS	     = CSCON^6;
  sbit  CSG1	 = CSCON^5;
  sbit  CSDRY    = CSCON^4;
  sbit  CSH3     = CSCON^3;
  sbit  CSH2     = CSCON^2;
  sbit  CSH1     = CSCON^1;
  sbit  CSH0     = CSCON^0;	
sfr     CSCON1   = 0xC1;
sfr     CSCON2   = 0xC2;
sfr     SGMOD1   = 0xC3;
sfr     SGMOD2   = 0xC4;
sfr16   PW16D    = 0xC9;
sfr     PW16DL   = 0xC9;
sfr     PW16DH   = 0xCA;
sfr16   PW17D    = 0xCB;
sfr     PW17DL   = 0xCB;
sfr     PW17DH   = 0xCC;
sfr     SYSMOD   = 0xCE;
sfr     PSW      = 0xD0;
  sbit  CY       = PSW^7;
  sbit  AC       = PSW^6;
  sbit  F0       = PSW^5;
  sbit  RS1      = PSW^4;
  sbit  RS0      = PSW^3;
  sbit  OV       = PSW^2;
  sbit  F1       = PSW^1;
  sbit  P        = PSW^0;
sfr     ADM      = 0xD2;
sfr     ADB      = 0xD3;
sfr     ADR      = 0xD4;
sfr     VREFH    = 0xD5;
sfr     P2CON    = 0xD6;
sfr     S0CON2   = 0xD8;
  sbit  BD       = S0CON2^7;
  sbit  URMX     = S0CON2^0;
sfr     ADT      = 0xD9;
sfr     I2CDAT   = 0xDA;
sfr     I2CADR   = 0xDB;
sfr     I2CCON   = 0xDC;
sfr     I2CSTA   = 0xDD;
sfr     SMBSEL   = 0xDE;
sfr     SMBDST   = 0xDF;
sfr     ACC      = 0xE0;
sfr     P0OC     = 0xE4;
sfr     CLKSEL   = 0xE5;
sfr     CLKCMD   = 0xE6;
sfr     TCON0    = 0xE7;
sfr     MD0      = 0xE9;
sfr     MD1      = 0xEA;
sfr     MD2      = 0xEB;
sfr     MD3      = 0xEC;
sfr     MD4      = 0xED;
sfr     MD5      = 0xEE;
sfr     ARCON    = 0xEF;
sfr     B        = 0xF0;
sfr     P0UR     = 0xF1;
sfr     P1UR     = 0xF2;
sfr     P2UR     = 0xF3;
sfr     P0BIAS   = 0xF4;
sfr     P1BIAS   = 0xF5;
sfr     SRST     = 0xF7;
sfr     P0M      = 0xF9;
sfr     P1M      = 0xFA;
sfr     P2M      = 0xFB;
sfr16   FRQ      = 0xFC;
sfr     FRQL     = 0xFC;
sfr     FRQH     = 0xFD;
sfr     FRQCMD   = 0xFE;
sfr     PFLAG    = 0xFF;

/*      Interrupt Vector      */
#define ISRInt0    0
#define ISRPwm1    1
#define ISRUartTX  2
#define ISRAdc     3
#define ISRCS      5
#define ISRInt2    8
#define ISRUartRX  10
#define ISRTimer0  12
#define ISRInt1    16
#define ISRI2c     18
#define ISRTimer1  20

/*      C51 Macros      */
#ifdef __C51__
#include <intrins.h>
#define IDLE() {PCON |= 0x01;}
#define STOP() {PCON |= 0x02;}
#define PISP(ROM_ADDRESS, RAM_ADDRESS) {PERAM = (RAM_ADDRESS); PEROM = ((ROM_ADDRESS) & 0xFFE0); PECMD = 0x5A; _nop_(); _nop_();}
#define BISP(ROM_ADDRESS, RAM_ADDRESS) {PERAM = (RAM_ADDRESS); PEROM = ((ROM_ADDRESS) & 0xFFFF); PECMD = 0x1E; _nop_(); _nop_();}


#endif  // __C51__

#ifndef uint8_t
#define uint8_t unsigned char
#endif  // uint8_t

#ifndef uint16_t
#define uint16_t unsigned int
#endif  // uint16_t

#ifndef uint32_t
#define uint32_t unsigned long
#endif  // uint32_t

#endif  // __SN8F5713_H__
