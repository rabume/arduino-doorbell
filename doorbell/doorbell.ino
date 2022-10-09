#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include <ezButton.h>

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif


#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// A small helper
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

// create ezButton object that attach to pin 8;
ezButton button(8);  

void setup(void)
{

  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  
  while (!Serial);  // Required for Flora & Micro
  delay(500);

  Serial.begin(115200);

  // Initialise the module
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    // Perform a factory reset to make sure everything is in a known state
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Factory reset failed!"));
    }
  }

  // Disable command echo from Bluefruit 
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  
  // Print Bluefruit information 
  ble.info();

  // This demo only works with firmware 0.6.6 and higher!
  // Request the Bluefruit firmware rev and check if it is valid
  if ( !ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    error(F("This sketch requires firmware version " MINIMUM_FIRMWARE_VERSION " or higher!"));
  }

  // Enable HID Service
  Serial.println(F("Enable HID Services (including Control Key): "));
  if (! ble.sendCommandCheckOK(F( "AT+BLEHIDEN=On"  ))) {
    error(F("Failed to enable HID (firmware >=0.6.6?)"));
  }

  // Adding or removing services requires a reset
  Serial.println(F("Performing a SWet (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }
}

void loop(void)
{
  button.loop(); // MUST call the loop() function first
  
  if(button.isPressed()) {
      Serial.println("The button is pressed");
      ble.print("AT+BleHidControlKey=");
      ble.println("CALCULATOR");

      if( ble.waitForOK() ) {
        Serial.println( F("OK!") );
      } else {
        Serial.println( F("FAILED!") );
        // Failed, probably pairing is not complete yet
        Serial.println( F("Please make sure Bluefruit is paired and try again") );
      }
  }
}


