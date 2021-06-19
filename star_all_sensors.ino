

#include <LiquidCrystal.h>
//#include <Ubidots.h>
String apiKey = "649940GN3RPQE4VS";
 
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;
float tur;
float tur1;
float vol = 0.0,l_minute;
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
unsigned long flow_frequency;

LiquidCrystal lcd(12, 11, 6, 5, 4, 3); 
float temp1;           // to include LM 35 sensor
int resval = 0;  // holds the value
int respin = A0; // sensor pin used

//const char *TOKEN = "BBFF-I5CApGkf9HLHKLXewp1tK8Lhwh26H9";
//const char *DEVICE_LABEL = "sens";
//const char *APN = "jionet";
//const char *VARIABLE_LABEL = "Temperature"; 

  
//client(TOKEN);
//client(APN);

void flow () // Interrupt function to increment flow
{
   flow_frequency++;
}

void setup() { 
  Serial.begin(9600);
  
  
 
  // set up the LCD's number of columns and rows: 
      lcd.begin(20, 4);
  {
//   Serial.begin(9600);
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt



   lcd.setCursor(0,0);
   lcd.print("Sensing water");
   lcd.setCursor(0,1);
   lcd.print("   quality...  ");

   delay(500);
   lcd.clear();
}
  


  pinMode(13, OUTPUT);
//  Serial.begin(115200);
//  client.setDebug(true);// Set true to make available debug messages



} 
 

void loop() { 

    // Print a message to the LCD. 
  lcd.print("WaterLvl: "); 
 lcd.setCursor(9, 0); // set the cursor to column 9, line 0
  resval = analogRead(respin); //Read data from analog pin and store it to resval variable
   
  if (resval<=100){ lcd.print("  Empty  "); } 
  else if (resval>100 && resval<=300){ lcd.print("    Low     "); }
  else if (resval>300 && resval<=330){ lcd.print("    Medium      "); } 
  else if (resval>330){ lcd.print("   High    "); }
  
 lcd.setCursor(0, 1);
  lcd.print("TEMP:");
  temp1 = analogRead(A1);                                                    //temp = temp * 0.48828125;  //temp=temp*(5.0/1023.0)*100;
  temp1=temp1*4500/(10240);
  lcd.print(temp1  );
  delay(500);                                         //Let system settle



for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth value
  { 
    buf[i]=analogRead(A2);
    delay(5);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=2.8*phValue;                      //convert the millivolt into pH value
// lcd.setCursor(0, 2);
  lcd.print("  pH:");  
  lcd.print(phValue,2);
  lcd.print(" ");
  digitalWrite(13, HIGH);       
  delay(800);
   digitalWrite(13, LOW);

    /*NTU = a * TSS^b is the formula for calculating turbidity where:
    NTU = Turbidity Measurement
    TSS = Suspended solids measurement in mg/L (40,000 is an estimated amount in an 1 litre of sample)
    a = regression coefficient (0.00000125)
    b = regression coefficient, approximately equal to 1 (we take it as 1)
    */

   tur = analogRead(A3);
//   delay(100);
  tur1 = tur*0.00000125*40000; //Min = 0, Max = 51
  lcd.setCursor(0,2);
   lcd.print("Turbidity: ");
   lcd.print(tur1);
   delay(500);

//   currentTime = millis();
//   // Every second, calculate and print litres/hour
//   if(currentTime >= (cloopTime + 1000))
//   {
//    cloopTime = currentTime; // Updates cloopTime
//    if(flow_frequency != 0)
//    {
      
       l_minute = (flow_frequency / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      lcd.setCursor(1,3);
      lcd.print("FRate: ");
      lcd.print(l_minute);
      lcd.print(" L/M         ");
//      l_minute = l_minute/60;
//      vol = vol +l_minute;
//      lcd.print("Vol:");
//      lcd.print(vol);
//      lcd.print(" L");
//      flow_frequency = 0; // Reset Counter
//      Serial.print(l_minute, DEC); // Print litres/hour
//      Serial.println(" L/Sec");
//    }
//    else {
//      lcd.setCursor(0,4);
//      Serial.println(" flow rate = 0 ");
//
//      lcd.print("Rate: ");
//      lcd.print( flow_frequency );
//      lcd.print(" L/M");
//
//      lcd.print("Vol:");
//      lcd.print(vol);
//      lcd.print(" L");
//    
//    }

//}
//
//Serial.write(temp1);
//Serial.write(tur1);
//Serial.write(1_minute);
//
//Serial.print(temp1);
//Serial.print(tur1);
//Serial.print(l_minute);
}

//     float value = client.get(sens, Temperature);
//  
//  if(value!=ERROR_VALUE){
//    Serial.print("Getting variable value: ");
//    Serial.println(value);
//  }
