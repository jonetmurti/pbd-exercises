/******************************************************************************************************
*   Title: PWMallPins.pde
*   Author: Paul Badger 2007
*   Formating: Seth Wolf 2015
*  
*   Action:
*   This program fades LED's on Arduino digital pins 2 through 13 in a sine-wave pattern.
*   A program to illustrate one way to implement a manual PWM loop.
*
*   It could be modified to also modulate pins 0 & 1 and the analog pins.
*   I didn't modulate pins 0 & 1 just because of the hassle of disconnecting
*   the LEDs on the RX and TX pins (0 & 1).
*  
*   The PWM loop, as written, operates at about 175 HZ and is flicker-free.
*   The trick to this is to reduce the computation process time in between the PWM loop cycles.
*   Long delays between the loops are going to show up as flicker. This is true especially of
*   "Serial.print" debug statements which seem to hog the processor during
*   transmission. Shorter (time-wise) statements will just dim the maximum brightness of
*   the LED's. There are a couple of lines of code (commented out) that implement a
*   potentiometer as a speed control for the dimming.
*  
*   How it works:
*   The PWM loop turns on all LED's whose values are greater than 0 at the start of the PWM loop.
*   value. It then turns off the LED's as the loop variable is equal to the channel's PWM modulation
*   Because the values are limited to 255 (just by the table), all LED's are turned
*   off at the end of the PWM loop. This has the side effect of making any extra math,
*   sensor reading and will increase the "off" period of the LED's duty cycle. Consequently
*   the brightest LED value (255), which is supposed to represent a "100%" duty cycle
*   (on all the time), doesn't really do that. More math and sensor reading will increase  
*   the "off time", dimming the LED's max brightness. You can make up for  
*   this dimming with smaller series resistors, since LED's can be overrated if they aren't
*   on all of the time.The up side of this arrangement is that the LED's stay flicker free.

*  
*   Note:
*   This program could easily be used to modulate motor speeds with the addition of driver transistors or MOSFET's.
*  
*************************************************************************************************************/

int LEDCount = 12;                        // Number of LEDs used in this project
int topValue = 14;                        // Largest Arduino pin number of the LED pin set (+1)
int pinNumber;                            // variable for pinNumber
int fractionRemainder;                    // variable for fraction Remainder
int channelCounter;                       // variable for channel Counter
int brightValue;                          // variable for LED brightness Value
int setCounter;                           // variable for loop set Counter
int potValue;                             // Variable read from the potentiometer
int pwmVal[14];                           // PWM values for the LEDs (0&1 included but not used) (change this value if topValue is modified)
long time;                                // variable for speed debuging
float pwmSpeed[14] = {                    // These constants set the rate of dimming (change this value if topValue is modified)
 0, 0, 1.2, 1.3, 1.4, 1.9, .9, .8, .5, 1.2, 1.37, 1.47, .3, 3.2}; // 12 values (one for each of the LEDs in the set)
float pwmFloats[14];                      // Brightness values for each LED (change this value if topValue is modified)
unsigned char sinewave[] =                // Preset 256 values of a binary conversions of a sine wave
{
0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,
0xb0,0xb3,0xb6,0xb9,0xbc,0xbf,0xc1,0xc4,0xc7,0xc9,0xcc,0xce,0xd1,0xd3,0xd5,0xd8,
0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xed,0xef,0xf0,0xf2,0xf3,0xf5,
0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfc,0xfd,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfd,0xfc,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,
0xf6,0xf5,0xf3,0xf2,0xf0,0xef,0xed,0xec,0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
0xda,0xd8,0xd5,0xd3,0xd1,0xce,0xcc,0xc9,0xc7,0xc4,0xc1,0xbf,0xbc,0xb9,0xb6,0xb3,
0xb0,0xae,0xab,0xa8,0xa5,0xa2,0x9f,0x9c,0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x63,0x60,0x5d,0x5a,0x57,0x54,0x51,
0x4f,0x4c,0x49,0x46,0x43,0x40,0x3e,0x3b,0x38,0x36,0x33,0x31,0x2e,0x2c,0x2a,0x27,
0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x13,0x12,0x10,0x0f,0x0d,0x0c,0x0a,
0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x03,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x05,0x06,0x07,0x08,
0x09,0x0a,0x0c,0x0d,0x0f,0x10,0x12,0x13,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
0x25,0x27,0x2a,0x2c,0x2e,0x31,0x33,0x36,0x38,0x3b,0x3e,0x40,0x43,0x46,0x49,0x4c,
0x4f,0x51,0x54,0x57,0x5a,0x5d,0x60,0x63,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
  Serial.begin(9600);
  DDRD=0xFC; // Arduino digital pins 0 to 7 - Configure all pins as read/write and output except for the serial pins, 0 & 1
  DDRB=0xFF; // Arduino digital pins 8 to 13 - Configure all pins as read/write and output
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
/** Time = millis(); */                                     // This is for testing the loop speed (remove commented bracket)
/** For (setCounter=0; setCounter<1000; setCounter++){ */   // This is for testing the loop speed (remove commented bracket)
/** potValue = analogread(0);  */                           // Sets potValue control to manually change speed of fading (remove line below)
  for (pinNumber=0; pinNumber<topValue; pinNumber++){       // Calculate a new PWM value every time through the loop (Cycle back to 0 after 11)
    fractionRemainder = (fractionRemainder + 1) % LEDCount; // Calculate a new fraction Remainder every time - modulo operator makes it
    channelCounter = fractionRemainder + 2;                 // Add 2 to the result for cycling the selected channel(pin) numbers
    pwmFloats[channelCounter] = (pwmFloats[channelCounter] + pwmSpeed[channelCounter]);
/** pwmFloats[channelCounter] = (pwmFloats[channelCounter] + ((pwmSpeed[channelCounter]*15*(float)potValue)/1023)); */  // implements potentiometer control
      if (pwmFloats[channelCounter] >= 256){                            // Wrap around sine table values that are larger than 256
      pwmFloats[channelCounter] = pwmFloats[channelCounter] - 256;      //
    }                                                                   //
    else if  (pwmFloats[channelCounter] < 0){                           //
      pwmFloats[channelCounter] = pwmFloats[channelCounter] + 256;      // Wrap around sinewave table index values that are less than 0
    }                                                                   //
    pwmVal[channelCounter] = sinewave[(int)pwmFloats[channelCounter]];  // Convert the float value to an integer and get the value out of the sinewave index
  }                                                                     //
  PORTD = 0xFC;                                                         // Reset all outputs except serial pins 0 & 1
  PORTB = 0xFF;                                                         // Reset and turn on all pins of ports D & B
  for (setCounter=0; setCounter<3; setCounter++){                       // This adds more repetitions of the loop below to reduce the processing time of the loop above
  // Increase this value until you start to perceive any flicker in the LEDs
  // then back off and reduce the value
  // Decreasing value configures for a more responsive sensor input read process

    for (brightValue=0; brightValue<256; brightValue++){    // Cycle through the 256  values to find a match
      for( pinNumber=2; pinNumber<topValue; pinNumber++){   // start with 2 to avoid serial pins
        if (brightValue == pwmVal[pinNumber]){              // If it found a standard value matching one of the pins
          if (pinNumber < 8){                               // Corresponds to PORTD pin group
          // bit-shift a one into the proper bit then reverse the whole byte
          // equivalent to the line below but around 4 times faster
          // digitalWrite(pinNumber, LOW);
            PORTD = PORTD & (~(1 << pinNumber));            // Arduino digital pins 0 to 7
          }                                                 //
          else{                                             //
            PORTB = PORTB & (~(1 << (pinNumber-8)));        // Corresponds to PORTB (same as digitalWrite(pin, LOW);) on Port B pins
          }                                                 //
        }
      }
    }
  }
/**  } */                                                   // This is for the testing loop speed (remove the commented bracket)
/**  Serial.println((millis() - time), DEC);    */          // speed test code
}