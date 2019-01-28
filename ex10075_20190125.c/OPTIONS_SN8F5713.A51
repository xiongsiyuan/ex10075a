$NOMOD51
;------------------------------------------------------------------------------
;
;  Copyright (c) 2018 SONiX Technology Co., Ltd.
;  Version 1.0 - SN8F5713, SN8F5712, SN8F5711, SN8F57111, Add code option address for MP5
;  Version 1.1 - Remove LVD option description
;  Version 1.2 - Repair an error, omission, etc.
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;
;  This preference, such as watchdog, external reset pin, and clock source, is preloaded 
;  during the microcontroller's power-on. It is strongly recommanded to use configuration 
;  wizard to set these parameters up appropriately.
;
;------------------------------------------------------------------------------
ROM_SIZE		EQU		0x2000
;
;	<o.0..1> Program Memory Security <0x03=> Security Disable <0x02=> Security Enable <0x00=> Security Configuration
	SECURITY_SET    EQU     0x03		;	{0x1FFF}
;   <i> Security Disable: all address ROM data can be accessed.	
;   <i> Security Enable: all address ROM data are protected.
;   <i> Security Configuration: all address ROM data are protected expect address 0x1F00 ~ 0x1FDF, only address 0x1F00 ~ 0x1FDF ROM data can be accessed.
;
;   <o.2..4> CPU Clock Source <0x07=> IHRC 32 MHz <0x03=> IHRC 32 MHz with RTC <0x01=> X'tal 12 MHz <0x00=> X'tal 4 MHz <0x02=> External Clock
    CLOCKSRC_SET    EQU     0x1C		;	{0x1FFB}
;   <i> IHRC 32 MHz: on-chip internal clock with or without Timer 0 real time clock.
;   <i> X'tal 12 MHz: off-chip crystal between 4 MHz and 16 MHz.
;   <i> X'tal 4 MHz: off-chip crystal between 1 MHz and 4 MHz.
;   <i> External Clock: external clock input from XIN pin.
;
;   <o> Noise Filter <0x01=> Disable <0x00=> Enable
    NOISEFILT_SET   EQU     0x01		;	{0x1FFC}
	
;	<o> Noise Detect <0x01=> Disable <0x00=> Enable
    HOLD_CK1_SET   EQU     0x01		;	{0x1FFB}

;	<o.1> CK Fine-Tuning <0x01=> Disable <0x00=> Enable
    CK_Fine_Tuning_SET   EQU     0x02		;	{0x1FFB}	

;	<o.2> ISP Program Area  <0x01=> All Page <0x00=> Page 248~ Page 254
    ISP_EN   EQU     0x04		;	{0x1FFF}
;   <i> All Page: all address can perform ISP function.
;   <i> Page 248~ Page 254: only address 0x1F00 ~ 0x1FDF can perform ISP function.
			
;  <h> Reset Sources
;
;       <o.4..5> External Reset / GPIO Shared Pin <0x00=> Reset with De-bounce <0x02=> Reset without De-bounce <0x03=> GPIO
        RESETPIN_SET    EQU     0x30	;	{0x1FFC}
;       <i> Reset with De-bounce: Triggers reset if this pin is pulled low over 8 ms.
;       <i> Reset without De-bounce: Triggers reset immediately if this pin is pulled low.
;       <i> GPIO: The shared pin is reserved for general purpose input/output.
;       <i> The de-bounce period is based on Internal Low R-C Clock which has a gentle inaccuracy.
;
;       <o.4..7> Watchdog Reset <0x00=> Always <0x05=> Enable <0x0A=> Disable
        WATCHDOG_SET    EQU     0x50	;	{0x1FFF}
;       <i> Always: Trun on watchdog function including Normal, IDLE, and SLEEP mode.
;       <i> Enable: Turn on watchdog function only in Normal mode.
;       <i> Disable: Turn off watchdog function.
;
;       <o.6..7> Watchdog Overflow Period <0x00=> 64 ms <0x01=> 128 ms <0x02=> 256 ms <0x03=> 512 ms
        WATCHCLK_SET    EQU     0x00	;	{0x1FFC}
;       <i> The watchdog overflow period is based on Internal Low R-C Clock which has a gentle inaccuracy.
;   </h>

    CSEG    AT      0x1FF6
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      0xFF
    DB      0xFF	
    DB      CK_Fine_Tuning_SET + HOLD_CK1_SET + CLOCKSRC_SET 
    DB      WATCHCLK_SET + RESETPIN_SET + 0x06+ NOISEFILT_SET
    DB		0x5A
	DB		0xA5
    DB      WATCHDOG_SET + SECURITY_SET+ ISP_EN 
    END
