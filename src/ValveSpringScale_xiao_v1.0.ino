/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017

   Load cell - LCF-6 200kg

   Rotary Encoder GHB38-8G2048BMC526 from Amazon

   XIAO ESP32S3 from Seeed Studio

   The LoadFactor combined with the non-linearity IF statements put the middle of the PSI range most accurate
   and make a correction at both the low and high ends.  A calibrated spring from Rimac Tools, part # BB1902
   was used to adjust the PSI/Spring Length readings to close to within +/- 3 psi.  Most spring tolerances 
   are given to within 10% so this should be close enough for me.
   -------------------------------------------------------------------------------------
*/

#define ENCODER_A D2 // Pin for Encoder A
#define ENCODER_B D3 // Pin for Encoder B

//Library includes
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HX711_ADC.h>

#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

// Variables
int counter = 0;

// set touchpin numbers
const int touchPin = 2; //1 ESP32S3 XIAO

volatile int encoder_value = 0; // Global variable for storing the encoder position
const float InchConv = 0.000730;//Conversion factor counts to inches

// change with your threshold value
const int threshold = 2000;
// variable for storing the touch pin value 
int touchValue;

//Pins - esp32 set for 2004LCD I2C
const int sda = 4; //4 for XIAO ESP32S3
const int scl = 5; //5 for XIAO ESP32S3

//pins - set for ESP32S3 XIAO  BY tm
const int HX711_dout = 8; //8 XIAO mcu > HX711 dout pin DT
const int HX711_sck = 7;  //7 XIAO mcu > HX711 sck pin  SCK

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0; //not actually used in this version
unsigned long t = 0;
unsigned long lbs = 0;

//Initialize lcd variable
LiquidCrystal_I2C lcd(0x27, 20, 4); //i2c port, 20 chars, 4 lines

// Interupt routine for encoder activity
void encoder_isr() {
  // Reading the current state of encoder A and B
  int A = digitalRead(ENCODER_A);
  int B = digitalRead(ENCODER_B);

  // If the state of A changed, it means the encoder has been rotated
  if ((A == HIGH) != (B == LOW)) {
    encoder_value--;
  } else {
    encoder_value++;
  }
}

void setup(){
 
    //initialize the lcd display
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Starting scale..... ");

  //Serial.begin(115200); // Initialize serial communication if needed for testing
  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  // Attaching the ISR to encoder A
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoder_isr, CHANGE);

  LoadCell.begin();
     //LoadCell.setReverseOutput();     //uncomment to turn a negative output value to positive
  unsigned long stabilizingtime = 2000; // precision right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Timeout-check");
    while (1);
  }
  else
  {
    LoadCell.setCalFactor(21.00); // user set calibration value (float), needs some massaging as load cell is not completely linear
    LoadCell.tareNoDelay(); //tare
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tare Complete...");
    delay(3000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Tony's Spring Scale");
    lcd.setCursor(0,1);
    lcd.print("Spring @  ");
    lcd.setCursor(0,2);
    lcd.print("SprHgt @ ");
  }
}

void loop() {

  static boolean newDataReady = 0;
  const int serialPrintInterval = 100; //increase value to slow down print activity

  touchValue = analogRead(touchPin);
  
  if(touchValue > threshold){
    LoadCell.tareNoDelay();
    encoder_value = 0;
    lcd.setCursor(0,3);
    lcd.print("TARE..");
    delay(3000);
    lcd.setCursor(0, 3);
    lcd.print("       ");
    }  
  
  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      float grams = i;
      float lbs = i * 0.00220462;
      lbs = abs(lbs);

      // These IF statements make a correction at the low and high ends to correct for non-linearity of load cell
      if ((lbs > 2) && (lbs < 135))  {
        lbs = lbs + 6;
      }
      if (lbs > 220) {
        lbs = lbs - 4;
      }
                
      lcd.setCursor(11,1);
      lcd.print(lbs, 0);
      lcd.print("   lbs ");

      float inch = encoder_value * InchConv;
      //lcd.setCursor(5,2);
      //lcd.print("     ");
      lcd.setCursor(10, 2);
      lcd.print(String(abs(inch), 2));
      lcd.print(" inch");

      newDataReady = 0;
      t = millis();
    }
  }

}
