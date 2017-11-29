/*==============================================================================
    Project: CHRP-ReceiverBot
    Version: 1.5				Date: June 21, 2016
    Target: CHRP3.1				Processor: PIC18F25K50

    This program is for receiving IR signals and processing them. The motors 
    will then switch on/off depending on the values of the IR signal received,
    effectively moving the robot. Based off the SONY IRC Protocol
==============================================================================*/

#include    "xc.h"              // XC compiler general include file

#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "CHRP3.h"           // Include CHRP3 constant symbols and functions

// Have Set linker ROM ranges to 'default,-0-1FFF,-2006-2007,-2016-2017' under "Memory model" pull-down.
// Have Set linker Code offset to '0x2000' under "Additional options" pull-down.
// Have Set Instruction freq. to 48Mhz.
/*==============================================================================
    Variables needed for receiving an 8-bit IR Signal
 =============================================================================*/
unsigned char receivedBitLength = 0;
unsigned char receivedDeviceAddress = 0;
unsigned char receivedData = 0;
#define STOP            0b00000000

/*==============================================================================
    RECEIVE BIT
 =============================================================================*/
unsigned char receiveBit(void) { // like IRbit
    unsigned char counter = 0; //cBitTimer
    while (IR == 0) { // when the value of IR is low, then it is receiving a signal
        __delay_us(100);
        counter++; // every 100us, we add 1 to a counter to use later (it tells how long the pulse was)
        if (counter > 26) return (0); // our pulse lengths are all under 26
    }
    return (counter);
}

/*==============================================================================
    RECEIVE DATA
        Function to process the incoming data
 =============================================================================*/
unsigned char receiveData(void) {
    unsigned char cData = 0;
    for (unsigned char i = 8; i != 0; i--) {
        while (IR == 1); // after getting the previous signal, we wait for a signal again.
        receivedBitLength = receiveBit(); // get the new bit after getting a new signal
        if (receivedBitLength > 3 && receivedBitLength < 9) { // the bit received is a 0 (0.6ms)
            if (i != 1) cData = cData >> 1; // since the bit is a zero, we can just shift the 
            // contents over for the next bit if it's not the last bit
        } else if (receivedBitLength > 9 && receivedBitLength < 15) { // the bit received is a 1 (1.2ms)
            cData = (cData | 0b10000000); // add a value of 1 to the most significant bit of "data"
            if (i != 1) cData = cData >> 1; // shift the contents over for the next bit if it's not the last bit
        } else {
            return (0); // error
        }
    }
    return (cData);
}

/*==============================================================================
    RECEIVE ADDRESS
        Function to process the device address
 =============================================================================*/
unsigned char receiveAddress(void) {
    unsigned char cAddress = 0;
    for (unsigned char i = 3; i != 0; i--) {
        while (IR == 1); // after getting the previous signal, we wait for a signal again.
        receivedBitLength = receiveBit(); // get the new bit after getting a new signal
        if (receivedBitLength > 3 && receivedBitLength < 9) { // the bit received is a 0
            cAddress = cAddress >> 1; // since the bit is a zero, we can just shift the 
            // contents over for the next bit
        } else if (receivedBitLength > 9 && receivedBitLength < 15) { // the bit received is a 1
            cAddress = (cAddress | 0b10000000); // add a value of 1 to the most significant bit of "data"
            cAddress = cAddress >> 1; // shift the contents over for the next bit
        } else {
            return (0);
        }
    }
    cAddress = cAddress >> 1; // need to shift it over four more bits 
    cAddress = cAddress >> 1; //because we received 3 bits
    cAddress = cAddress >> 1;
    cAddress = cAddress >> 1;
    return (cAddress);
}

/*==============================================================================
    RECEIVE TRANSMISSION
        Function to process the incoming data and address if a startbit was received
  =============================================================================*/
void receiveTransmission(void) {
    receivedBitLength = receiveBit();
    if (receivedBitLength > 22 && receivedBitLength < 26) { // this means the pulse was a StartBit
        receivedData = receiveData();
        receivedDeviceAddress = receiveAddress();
    } else {
        receivedData = 0;
        receivedDeviceAddress = 0;
    }
}

/*==============================================================================
    Main program code.
==============================================================================*/
int main(void) {
    initOsc(); // Initialize oscillator and wait for it to stabilize
    initPorts(); // Initialize CHRP3 I/O and peripherals
    while (1) {
        PORTB = STOP;
        while (IR == 1); // when IR =0, we are receiving a signal
        receiveTransmission();
        if (receivedDeviceAddress == 0b00000101) {
            PORTB = receivedData;
        }
        __delay_ms(18);

        if (S1 == 0) // Start the bootloader if S1 is pressed
        {
            asm("goto 0x001C");
        }
    }
}