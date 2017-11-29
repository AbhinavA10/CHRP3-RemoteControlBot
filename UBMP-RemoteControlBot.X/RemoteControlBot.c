/*==============================================================================
    Project: Remote Control
    Version: 1.3 				Date: June 21, 2016
    Target: UBMP1.0				Processor: PIC16F1459

    A program to send IR codes to the CHRP3 board.
==============================================================================*/
#include	"xc.h"				// XC general include file
#include    "math.h"
#include	"stdint.h"			// Include integer definitions
#include	"stdbool.h"			// Include Boolean (true/false) definitions
#include	"stdlib.h"
#include	"UBMP.h"			// Include UBMP constant symbols and functions

// Have Set linker ROM ranges to 'default,-0-B03' under "Memory model" pull-down.
// Have Set linker Code offset to '0xB04' under "Additional options" pull-down.
/*==============================================================================
    CHRP3 Motor direction constant definitions
 =============================================================================*/
#define FWD             0b00000110
#define BCKWD           0b00001001
#define STOP            0b00000000
#define FWDR            0b00000010
#define FWDL            0b00000100
#define BCKWDR          0b00000001
#define BCKWDL          0b00001000
#define RIGHTONSPOT     0b00001010
#define LEFTONSPOT      0b00000101

/*==============================================================================
    SIGNAL PULSE
        This function uses a number as in input for the number of pulses the 
        LED has to do. Essentially, the length of the pulse/signal
 =============================================================================*/
void signalPulse(unsigned char length) {
    for (length; length != 0; length--) {
        IRLED = 1;
        __delay_us(12);
        IRLED = 0;
        __delay_us(12); // 13 makes it 38.6kHz
    }
    __delay_us(600); // constant blank space after each pulse
    /*      SOME NOTES
     * 
     * 38kHz = 38ms = 38000us
     * 1000us = 1 ms
     * total time is 24.916 us
     * to calculate freq: 1 / total time (in x10^-6)
     *   
     */
}

/*==============================================================================
    TRANSMIT
        This function uses two 8bit numbers as inputs. It cycles through
        the for loop below converting the parallel data into serial data and then 
        sending it to the CHRP3 board as infrared pulses.
        The First input is that data to send, the second input is the device to 
        send it to. Data is transmitted first, and then the address.
 =============================================================================*/
void transmit(unsigned char cData, unsigned char cAddress) {
    signalPulse(96); // Send a startBit, 2.4ms
    /**/
    for (unsigned char i = 8; i != 0; i--) {
        if (cData & 0b00000001 == 1) { //check the least significant bit of data and compare it to "1"
            signalPulse(48); // if the bit was a 1, send a pulse value that represents "1", 1.2ms.
        } else {
            signalPulse(24); // Send a pulse value that represents 0, 0.6ms
        }
        cData = cData >> 1;
    }
    for (unsigned char i = 3; i != 0; i--) {
        if (cAddress & 0b00000001 == 1) {
            signalPulse(48); // 1.2ms, "1"
        } else {
            signalPulse(24); // 0.6ms, "0"
        }
        cAddress = cAddress >> 1;
    }
    __delay_ms(18);
}

/*==============================================================================
    Main program code.
==============================================================================*/
int main(void) {
    initOsc(); // Initialize oscillator
    initPorts(); // Initialize I/O pins and peripherals

    while (1) // Repeat the main loop continuously
    { // The logic structure below for the buttons is for "tank control"
        if (S3 == 0 && S4 == 0) {
            transmit(FWD, 0b00000101); // In the CHRP code, it will receive the value for FWD and place it in PORTB
        } else if (S2 == 0 && S5 == 0) { // We referenced the UBMP board to see which buttons should be pressed
            transmit(BCKWD, 0b00000101);
        } else if (S2 == 0 && S4 == 0) {
            transmit(RIGHTONSPOT, 0b00000101);
        } else if (S3 == 0 && S5 == 0) {
            transmit(LEFTONSPOT, 0b00000101);
        } else if (S3 == 0 && S2 == 1) { // redundant checking
            transmit(FWDL, 0b00000101);
        } else if (S2 == 0 && S3 == 1) {
            transmit(BCKWDL, 0b00000101);
        } else if (S5 == 0 && S4 == 1) {
            transmit(BCKWDR, 0b00000101);
        } else if (S4 == 0 && S5 == 1) {
            transmit(FWDR, 0b00000101);
        }
        if (S1 == 0) // Enter the bootloader if S1 is pressed.
        {
            asm("movlp 0x00");
            asm("goto 0x001C");
        }
    }
}
