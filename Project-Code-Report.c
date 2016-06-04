/*
@Author : Mayur Khatri
Description: Smart Energy Meter 
Last Edited: 01-May-2016
Implementatation: GSM Module shield implementation with arduino tested with LCD.

*/
#include <SoftwareSerial.h>
#include <LiquidCrystal.h> // Importing LCD Library file
/*
 * RS: Pin 12
 * EN: Pin 11
 * D4: Pin 5
 * D5: Pin 4
 * D6: Pin 3
 * D7: Pin 2
 */
LiquidCrystal lcd (12, 11, 5, 4, 3, 2); //lcd display pin
 
char mobileNumber; // Will hold the incoming character from the GSM shield
SoftwareSerial SIM900(9, 10);
const int voltageSensor = A0; // voltage pin
const int currentSensor = A1; // current pin
int mVperAmp = 66; // use 100 for 20A Module and 66 for 30A Module
double sumWH = 0.00000;
float WH = 0;//energy consumption in watt hour 
double sumRupees = 0.00000;//Total energy consumption in rupees 
float rupees = 0;//energy consumption in rupees
double Voltage = 0;//AC supply peak voltage
double vrms = 0;//AC supply rms voltage
double current = 0;//load peak current
double irms = 0;//load rms current
double power = 0;//

void setup()
{ 
 
 Serial.begin(19200); 
 SIM900.begin(19200);
 delay(500); 
 SIM900.print("AT+CLIP=1\r"); // turn on caller ID notification , to get missed call number
 delay(100);  
 lcd.begin(16,2); // Display Columms, Rows and Size
 lcd.clear(); 

}

// Used to send Total Energy Consumption Billing to Customer
void sendBilling()
{
  SIM900.println("AT+CLIP=1\r");
  SIM900.println("AT+CMGF=1");    // Setting the GSM Module in Text mode
  delay(1000);  
  SIM900.println("AT+CMGS=\"XXXXXXXXXX\"\r"); // Sending Energy Consumption to Customer's Mobile Number
  delay(1000);
  
    SIM900.print("Dear Customer, Your Energy Consumption is :");
    SIM900.print(sumWH);
    SIM900.print(" and Total Billing is Rs. ");
    SIM900.print(sumRupees);
  
  delay(100);
  SIM900.println((char)26); // ASCII code of CTRL+Z
  delay(100);
}


void energyCalculations()
{
  // getting voltage from Input PIN
 Voltage = getVPP(0);
 vrms = (Voltage / 2.0) * 0.707 * 575; //find total voltage
  Serial.print("VOLTAGE : "); 
  Serial.print(vrms);
  Serial.println("Volt"); 
 // getting current from Input PIN
 current = getVPP(1);
 irms = (current / 2.0) * 0.707 * 1000 / mVperAmp; 
 // Serial.print("CURRENT :"); 
 // Serial.print(irms);
 // Serial.println("Amps"); 
 power=(vrms * irms * 0.3099);
 
 //Serial.print("POWER :"); 
// Serial.print(power);
 //Serial.println("watt"); 


 WH = (power / 3600);
 //Serial.print("ENERGY CONSUMED :"); 
 //Serial.print(WH);
 //Serial.println("Watt-Hour"); 

 sumWH = sumWH + WH;
 //Serial.print("TOTAL ENERGY CONSUMED :"); 
 //Serial.print(sumWH);
 //Serial.println("Watt-Hour"); 

 
 rupees = getReading();
 // Serial.print("ENERGY CONSUMED IN RUPEES :"); 
 //Serial.print(rupees);
 // Serial.println("Rs."); 

 sumRupees = sumRupees + rupees ;
 //Serial.print("TOTAL ENERGY CONSUMED IN RUPEES :"); 
 //Serial.print(sumRupees);
 //Serial.println("Rs."); 
 //Serial.println(""); // print the next sets of parameter after a blank line

 lcd.setCursor(1,0); // set the cursor at 1st col and 1st row
 lcd.print(vrms);
 lcd.print("v ");
 lcd.print(irms);
 lcd.print("A");
 lcd.setCursor(1,1); // set the cursor at 1st col and 2nd row
 lcd.print(power);                                                                                
 lcd.print("w");
 //delay(1000);
 lcd.clear(); // clear the screen
 lcd.setCursor(1,0); // set the cursor at 1st col and 1st row
 lcd.print(WH);
 lcd.print("WH ");                                                                                                 
 lcd.setCursor(1,1); // set the cursor at 1st col and 2nd row
 lcd.print(rupees);
 lcd.print("Rs.");
 //delay(1000);
 lcd.clear(); // clear the screen
 lcd.setCursor(1,0); // set the cursor at 1st col and 1st row 
 lcd.print(sumWH);
 lcd.print("Total WH ");
 lcd.setCursor(1,1); // set the cursor at 1st col and 2nd row
 lcd.print(sumRupees);
 lcd.print("Total Rs.");
 //delay(1000);
 lcd.clear();

}

void loop()
{





energyCalculations();
gsm();


//if(SIM900.available() > 0)
//  {
//   Serial.println("Inside SIM900 avaialble");
//   Serial.write(SIM900.read()); 
//   delay(200);
//  }
   

}

void gsm() 
{
  //Serial.println("Inside GSM");
  if(SIM900.available() > 0)
  {
    //Serial.println("SIM900 is available");   

    delay(10);
    mobileNumber = SIM900.read();
    Serial.print(mobileNumber); 
    if(mobileNumber == 'X')
      {
        delay(10);
        mobileNumber = SIM900.read();
        if(mobileNumber == 'X')
        {
          delay(10);
          mobileNumber = SIM900.read();
          if(mobileNumber == 'X')
            {
              delay(10);
              mobileNumber = SIM900.read();
              if(mobileNumber == 'X')
                {
                    delay(10);
                    mobileNumber = SIM900.read();
                    if(mobileNumber == 'X')
                    {
                        delay(10);
                        mobileNumber = SIM900.read();
                        if(mobileNumber == 'X')
                        {
                          delay(10);
                          mobileNumber = SIM900.read();
                          if(mobileNumber == 'X')
                          {
                            delay(10);
                            mobileNumber = SIM900.read();
                            if(mobileNumber == 'X')
                            {
                              delay(10);
                              mobileNumber = SIM900.read();
                              if(mobileNumber == 'X')
                              {
                                delay(10);
                                mobileNumber = SIM900.read();
                                if(mobileNumber == 'X')
                                {
                                 // delay(10);
                                  Serial.println("Number Matched !");
                                  Serial.println("Sending Billing to Customer");
                                  //delay(90000);
                                  sendBilling();
                                }
                              }
                            }
                          }
                        }
                    }
                }
            
          
             }
        }
      }
                
    
    
    

  }
}


float getVPP(int pinValue)
{
  // pinValue = 0 means it is Voltage Input , pinValue = 1 means it is Current Input
  float result;
  
  int readValue;             // value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis() - start_time) < 1000) //sample for 1 Sec
   {
        if(pinValue == 0)
       {
          // reading Voltage Input PIN
          readValue = analogRead(voltageSensor);
       }
       else if(pinValue == 1)
       {  
          // reading Current Input PIN
            readValue = analogRead(currentSensor);       
       }
       
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the maximum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0) / 1024.0;
      
   return result;
 }

  
 float getReading()
 { 

 float solution;
 
 if(sumWH <= 50)
  solution = (WH * 3.15);
 if(( sumWH > 50 ) && ( sumWH <= 100 ))
  solution = ( WH * 3.60 );
 if(( sumWH > 100 ) && (sumWH <= 250))
  solution = (WH * 4.25);
 if(sumWH > 250)
  solution = (WH * 5.20);
 
 return solution;
 
 }
