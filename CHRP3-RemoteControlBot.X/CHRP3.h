/*==============================================================================
    CHRP 3.1 (PIC18F25K50) symbolic constant definitions.
==============================================================================*/

// TODO - Add other user constant definitions for CHRP3 hardware here.

// Inputs read the Port registers (eg. RC0). Outputs write to the port latches
// (eg. LATC0). Create different symbolic names for pins that will be both
// inputs and outputs using the appropriate PORT and LAT pin names.

// PORTA I/O device definitions

#define	Q1			PORTAbits.RA0		// Phototransistor Q1 input
#define	Q2			PORTAbits.RA1		// Phototransistor Q2 input
#define	VR1			PORTAbits.RA2		// Potentiometer VR1 input
#define	T1			PORTAbits.RA3		// Temperature sensor T1 input
#define	LED2		LATAbits.LATA4		// Run LED, LED2 output
#define	RUNLED      LATAbits.LATA4		// Run LED, LED2 output
#define	LCDBL		LATAbits.LATA4		// LCD LED backlight cathode output
#define	LCDLED		LATAbits.LATA4		// LCD LED backlight cathode output
#define	VM			PORTAbits.RA5		// Motor supply voltage divider input
#define	BEEPER		LATAbits.LATA6		// Piezo beeper P1 output
#define	P1			LATAbits.LATA6		// Piezo beeper P1 output
#define	LED12		LATAbits.LATA7		// Floor/phototransistor LED (LED12) output

// PORTB I/O device definitions

#define LED10		LATBbits.LATB0		// LED10 output (LSB)
#define M1A			LATBbits.LATB0		// Motor 1 A output (Left Motor)
#define S2			PORTBbits.RB0		// Switch S2 input
#define	LED9		LATBbits.LATB1		// LED9 output
#define M1B			LATBbits.LATB1		// Motor 1 B output (Left Motor)
#define S3			PORTBbits.RB1		// Switch S3 input
#define LED8		LATBbits.LATB2		// LED8 output
#define M2A			LATBbits.LATB2		// Motor 2 A output (Right Motor)
#define	S4			PORTBbits.RB2		// Switch S4 input
#define LED7		LATBbits.LATB3		// LED7 output
#define M2B			LATBbits.LATB3		// Motor 2 B output (Right Motor)
#define S5			PORTBbits.RB3		// Switch S5 input
#define LED6		LATBbits.LATB4		// LED6 output
#define	S6			PORTBbits.RB4		// Switch S6 input
#define LED5		LATBbits.LATB5		// LED5 output
#define S7			PORTBbits.RB5		// Switch S7 input
#define LED4		LATBbits.LATB6		// LED4 output
#define LED3		LATBbits.LATB7		// LED3 output (MSB)

// PORTC I/O device definitions

#define H2			PORTCbits.RC0		// External I/O header H2 input
#define LCDE		LATCbits.LATC0		// LCD Enable output
#define SERVO1		LATCbits.LATC0		// Servo 1 output (external header H2)
#define H3			PORTCbits.RC1		// External I/O header H3 input
#define LCDRW		LATCbits.LATC1		// LCD Read/!Write output
#define	SERVO2		LATCbits.LATC1		// Servo 2 output (external header H3)
#define	H4			PORTCbits.RC2		// External I/O header H4 input
#define LCDRS		LATCbits.LATC2		// LCD Register Select output
#define	SERVO3		LATCbits.LATC2		// Servo 3 output (external header H4)
#define LED11		LATCbits.LATC6		// Communication/sensor LED, LED11 output
#define IR			PORTCbits.RC7		// IR demodulator U5 input
#define U5			PORTCbits.RC7		// IR demodulator U5 input

// PORTE input pin definition

#define	S1			PORTEbits.RE3		// Switch S1 input

// Analogue-digital converter input channel definitions

#define AN0			0b00000000		// Analogue channel 0 input
#define	ADQ1		0b00000000		// Q1 phototransistor A-D input channel (Ch0)
#define AN1			0b00000100		// A-D channel 1 input
#define	ADQ2		0b00000100		// Q2 phototransistor A-D input channel (Ch1)
#define AN2			0b00001000		// A-D channel 2 input
#define	ADVR1		0b00001000		// Potentiometer VR1 A-D input channel (Ch2)
#define AN3			0b00001100		// A-D channel 3 input
#define	ADT1		0b00001100		// Temperature sensor T1 A-D input channel (Ch3)
#define AN4			0b00010000		// A-D channel 4 input
#define	ADVM		0b00010000		// Motor voltage divider A-D input channel (Ch4)
#define ADTD		0b01110000		// PICmicro on-die temperature diode

// Clock frequency for delay macros and simulation

#define _XTAL_FREQ	48000000		// Processor clock frequency for time delays

// TODO - Add function prototypes for all functions in CHRP3.c here.

void initOsc(void); // Oscillator initialization function prototype.
void initPorts(void); // Port initialization function prototype.
void initANA(void); // Analogue PORTA initialization function.