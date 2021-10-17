/* Έργο Arduino για μετεωρολογικό σταθμό
Χρησιμοποιoύμε το πτερύγιο κατεύθυνσης ανέμου, τον μετρητή βροχής και το ανεμόμετρο  .
Αν και η τάση για έναν καταγραφέα καιρού είναι η λειτουργία του
για μεγάλο χρονικό διάστημα, λόγω του τρόπου με τον οποίο η Wiring.c υλοποιεί τη λειτουργία millis (),
αυτό θα πρέπει να επανεκκινηθεί μηνιαία. Οι λειτουργίες millis () ξεχειλίζουν
μετά από περίπου 49 ημέρες. Θα μπορούσαμε να το επιτρέψουμε εδώ και να το χειριστούμε
περιτύλιξη, αλλά έχετε μεγαλύτερα προβλήματα ούτως ή άλλως με την λειτουργία delay ()
σε υπερχείλιση, οπότε είναι καλύτερο να κάνουμε "επανεκκίνηση".
================================================== =======
ΑΝΕΜΟΜΕΤΡΟ
================================================== =======
Αυτό συνδέεται με τη γείωση Arduino στη μία πλευρά και την ακίδα 2 (για το
attachInterrupt (0, ...) από την άλλη.
Το pin 2 μπαίνει σε κατάσταση pullup και ο διακόπτης reed στο ανεμόμετρο θα το στείλει
να γειωθεί μία φορά ανά περιστροφή, η οποία θα προκαλέσει τη διακοπή.
Μετράμε τον αριθμό των περιστροφών σε 5 δευτερόλεπτα και διαιρούμε με 5.
Ένα Hz (στροφές/δευτερόλεπτο) αντιστοιχεί σε 1,492 μίλια/ώρα = 0,44704.
================================================== =======
ΑΝΕΜΟΔΕΙΚΤΗΣ
================================================== =======
Χρησιμοποιούμε έναν κλασικό διαχωριστή τάσης για να μετρήσουμε την αντίσταση
στνο πτερύγιο καιρού, το οποίο ποικίλλει ανάλογα με την κατεύθυνση.
Χρησιμοποιώντας αντίσταση 10K, η ένδειξη ADC θα είναι:
   1023 * (R/(10000+R))
όπου R είναι η άγνωστη αντίσταση του ανεμοδείκτη. Θα ελαττώσουμε
το εύρος 1023 σε 255, για να ταιριάζει με τα έγγραφα του φύλλου δεδομένων.
                  +5V
                   |
                   <
                   >     10K
                   <   αντιστάτης
                   <
                   >
                   |
 Analog Pin 5------|
                   |
                   -----------| προς ανεμοδείκτη
                              | (αντιστάτης)
                   -----------|
                   |
                   |
                 -----
                  ---
                   - 
The ADC values we get for each direction (based on a 255 max)
follow, assuming that pointing away from the assembly center
is sector zero. The sector number is just which 45-degree sector
it is, clockwise from the "away" direction. The direction
shown is assuming that "away" is West. Depending how
you orient the system, you'll have to adjust the directions.
Ακολουθούν οι τιμές ADC που λαμβάνουμε για κάθε κατεύθυνση (με βάση το μέγιστο 255), 
υποθέτοντας ότι δείχνει μακριά από το κέντρο συναρμολόγησης
είναι μηδενικός τομέας. Ο αριθμός τομέα είναι ακριβώς ποιος τομέας 45 μοιρών
είναι, δεξιόστροφα από την "μακριά" κατεύθυνση. Η κατεύθυνση
φαίνεται ότι υποτίθεται ότι το "μακριά" είναι Δυτική. Ανάλογα με το πώς
προσανατολίζουμε το σύστημα, θα πρέπει να προσαρμόσουμε τις οδηγίες. 
Τομέας   Τιμή  Κατεύθυνση
  0        18        W
  1        33        NW
  2        57        N
  7        97        SW
  3       139        NE
  6       183        S
  5       208        SE
  4       232        E
=========================================================*/

/* =========================================================
Βροχόμετρο
=========================================================
.011 ίντσες βροχής ή 0.03 cm, σύμφωνα με εγχειρίδιο δεδομένων.
Τα σχόλια στον υπόλοιπο κώδικα στα αγγλικά για χρήση και από αγγλόφωνους
*********************************************************************/
#define PIN_RAINGUAGE  3     // Digital port 3 pwm

float numbuckettip = 0;
float rainAmount = 0.0;
float rainRate = 0.0;



void setup() {
   Serial.begin(9600);

   pinMode(PIN_RAINGUAGE, INPUT);
   digitalWrite(PIN_RAINGUAGE, HIGH);
   attachInterrupt(1, countRainmeter, FALLING);
}

void loop() {
   

}


// Interrupt handler for raingauge. Called each time the reed 
// switch triggers (one tip of bucket). 

void countRainmeter() { 
static unsigned long lastmillis = 0; 
unsigned long m = millis(); 
 if (m - lastmillis < 200){ 
// ignore interrupt: probably a bounce problem 
  }
  else{ 
   numbuckettip++;
   rainAmount = numbuckettip*0.011*2.54;

   Serial.print("RAIN: ");
  Serial.print( rainAmount,2);
  Serial.println(" cm");
 // Serial.println(m);
  } 
  lastmillis = m; 
}






#include <TimeLib.h>
#include <Wire.h>

#define BME280_ADDRESS 0x76
unsigned long int hum_raw,temp_raw,pres_raw;
signed long int t_fine;

uint16_t dig_T1;
 int16_t dig_T2;
 int16_t dig_T3;
uint16_t dig_P1;
 int16_t dig_P2;
 int16_t dig_P3;
 int16_t dig_P4;
 int16_t dig_P5;
 int16_t dig_P6;
 int16_t dig_P7;
 int16_t dig_P8;
 int16_t dig_P9;
 int8_t  dig_H1;
 int16_t dig_H2;
 int8_t  dig_H3;
 int16_t dig_H4;
 int16_t dig_H5;
 int8_t  dig_H6;

// raingauge
int i=0;
float rain=0.0;
const int REED_PIN = 3; // Pin connected to reed switch,has to be a PWM pin
const int LED_PIN = 13; // LED pin - active-high
int proximity =0;
int old_val = 0;                //Old value of reed switch





void readTrim()
{
    uint8_t data[32],i=0;                      // Fix 2014/04/06
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(0x88);
    Wire.endTransmission();
    Wire.requestFrom(BME280_ADDRESS,24);       // Fix 2014/04/06
    while(Wire.available()){
        data[i] = Wire.read();
        i++;
    }
    
    Wire.beginTransmission(BME280_ADDRESS);    // Add 2014/04/06
    Wire.write(0xA1);                          // Add 2014/04/06
    Wire.endTransmission();                    // Add 2014/04/06
    Wire.requestFrom(BME280_ADDRESS,1);        // Add 2014/04/06
    data[i] = Wire.read();                     // Add 2014/04/06
    i++;                                       // Add 2014/04/06
    
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(0xE1);
    Wire.endTransmission();
    Wire.requestFrom(BME280_ADDRESS,7);        // Fix 2014/04/06
    while(Wire.available()){
        data[i] = Wire.read();
        i++;    
    }
    dig_T1 = (data[1] << 8) | data[0];
    dig_T2 = (data[3] << 8) | data[2];
    dig_T3 = (data[5] << 8) | data[4];
    dig_P1 = (data[7] << 8) | data[6];
    dig_P2 = (data[9] << 8) | data[8];
    dig_P3 = (data[11]<< 8) | data[10];
    dig_P4 = (data[13]<< 8) | data[12];
    dig_P5 = (data[15]<< 8) | data[14];
    dig_P6 = (data[17]<< 8) | data[16];
    dig_P7 = (data[19]<< 8) | data[18];
    dig_P8 = (data[21]<< 8) | data[20];
    dig_P9 = (data[23]<< 8) | data[22];
    dig_H1 = data[24];
    dig_H2 = (data[26]<< 8) | data[25];
    dig_H3 = data[27];
    dig_H4 = (data[28]<< 4) | (0x0F & data[29]);
    dig_H5 = (data[30] << 4) | ((data[29] >> 4) & 0x0F); // Fix 2014/04/06
    dig_H6 = data[31];                                   // Fix 2014/04/06
}
void writeReg(uint8_t reg_address, uint8_t data)
{
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(reg_address);
    Wire.write(data);
    Wire.endTransmission();    
}


void readData()
{
    int i = 0;
    uint32_t data[8];
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(0xF7);
    Wire.endTransmission();
    Wire.requestFrom(BME280_ADDRESS,8);
    while(Wire.available()){
        data[i] = Wire.read();
        i++;
    }
    pres_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    temp_raw = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
    hum_raw  = (data[6] << 8) | data[7];
}


signed long int calibration_T(signed long int adc_T)
{
    
    signed long int var1, var2, T;
    var1 = ((((adc_T >> 3) - ((signed long int)dig_T1<<1))) * ((signed long int)dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((signed long int)dig_T1)) * ((adc_T>>4) - ((signed long int)dig_T1))) >> 12) * ((signed long int)dig_T3)) >> 14;
    
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T; 
}

unsigned long int calibration_P(signed long int adc_P)
{
    signed long int var1, var2;
    unsigned long int P;
    var1 = (((signed long int)t_fine)>>1) - (signed long int)64000;
    var2 = (((var1>>2) * (var1>>2)) >> 11) * ((signed long int)dig_P6);
    var2 = var2 + ((var1*((signed long int)dig_P5))<<1);
    var2 = (var2>>2)+(((signed long int)dig_P4)<<16);
    var1 = (((dig_P3 * (((var1>>2)*(var1>>2)) >> 13)) >>3) + ((((signed long int)dig_P2) * var1)>>1))>>18;
    var1 = ((((32768+var1))*((signed long int)dig_P1))>>15);
    if (var1 == 0)
    {
        return 0;
    }    
    P = (((unsigned long int)(((signed long int)1048576)-adc_P)-(var2>>12)))*3125;
    if(P<0x80000000)
    {
       P = (P << 1) / ((unsigned long int) var1);   
    }
    else
    {
        P = (P / (unsigned long int)var1) * 2;    
    }
    var1 = (((signed long int)dig_P9) * ((signed long int)(((P>>3) * (P>>3))>>13)))>>12;
    var2 = (((signed long int)(P>>2)) * ((signed long int)dig_P8))>>13;
    P = (unsigned long int)((signed long int)P + ((var1 + var2 + dig_P7) >> 4));
    return P;
}

unsigned long int calibration_H(signed long int adc_H)
{
    signed long int v_x1;
    
    v_x1 = (t_fine - ((signed long int)76800));
    v_x1 = (((((adc_H << 14) -(((signed long int)dig_H4) << 20) - (((signed long int)dig_H5) * v_x1)) + 
              ((signed long int)16384)) >> 15) * (((((((v_x1 * ((signed long int)dig_H6)) >> 10) * 
              (((v_x1 * ((signed long int)dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) + (( signed long int)2097152)) * 
              ((signed long int) dig_H2) + 8192) >> 14));
   v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((signed long int)dig_H1)) >> 4));
   v_x1 = (v_x1 < 0 ? 0 : v_x1);
   v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);
   return (unsigned long int)(v_x1 >> 12);   
}



// **********************************************************************
#define uint  unsigned int
#define ulong unsigned long

#define PIN_ANEMOMETER  2     // Digital 2
#define PIN_RAINGUAGE  3     // Digital 2
#define PIN_VANE        A3     // Analog 5

// How often we want to calculate wind speed or direction
#define MSECS_CALC_WIND_SPEED 5000
#define MSECS_CALC_WIND_DIR   5000

volatile int numRevsAnemometer = 0; // Incremented in the interrupt
ulong nextCalcSpeed;                // When we next calc the wind speed
ulong nextCalcDir;                  // When we next calc the direction
ulong time;                         // Millis() at each start of loop().
ulong hourTime = 3600000;

float numBuckettip = 0;
float rainAmount = 0.0;
float rainRate = 0.0;

// ADC readings:
#define NUMDIRS 8
ulong   adc[NUMDIRS] = {27, 45, 77, 118, 161, 196, 230, 256};

// These directions match 1-for-1 with the values in adc, but
// will have to be adjusted as noted above. Modify 'dirOffset'
// to which direction is 'away' (it's West here).
char *strVals[NUMDIRS] = {"E","SE","S","NE","SW","N","NW","W"};
// {"W","NW","N","SW","NE","S","SE","E"};
byte dirOffset=0;

//=======================================================
// Initialize
//=======================================================
void setup() {
   Serial.begin(9600);

 pinMode(PIN_RAINGUAGE, INPUT);
   digitalWrite(PIN_RAINGUAGE, HIGH);
   attachInterrupt(1, countRainmeter, FALLING);

   // setup form bme280
    uint8_t osrs_t = 1;             //Temperature oversampling x 1
    uint8_t osrs_p = 1;             //Pressure oversampling x 1
    uint8_t osrs_h = 1;             //Humidity oversampling x 1
    uint8_t mode = 3;               //Normal mode
    uint8_t t_sb = 5;               //Tstandby 1000ms
    uint8_t filter = 0;             //Filter off 
    uint8_t spi3w_en = 0;           //3-wire SPI Disable
    
    uint8_t ctrl_meas_reg = (osrs_t << 5) | (osrs_p << 2) | mode;
    uint8_t config_reg    = (t_sb << 5) | (filter << 2) | spi3w_en;
    uint8_t ctrl_hum_reg  = osrs_h;
    pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
    Wire.begin();
    
    writeReg(0xF2,ctrl_hum_reg);
    writeReg(0xF4,ctrl_meas_reg);
    writeReg(0xF5,config_reg);
    readTrim();      
    // **********************************
    
   pinMode(PIN_ANEMOMETER, INPUT);
   digitalWrite(PIN_ANEMOMETER, HIGH);
   pinMode(PIN_RAINGUAGE, INPUT);
   digitalWrite(PIN_RAINGUAGE, HIGH);
   attachInterrupt(0, countAnemometer, FALLING);
   attachInterrupt(1, countRainmeter, FALLING);
   nextCalcSpeed = millis() + MSECS_CALC_WIND_SPEED;
   nextCalcDir   = millis() + MSECS_CALC_WIND_DIR;
}

//=======================================================
// Main loop.
//=======================================================
void loop() {
   // for bme280
    double temp_act = 0.0, press_act = 0.0,hum_act=0.0;
    signed long int temp_cal;
    unsigned long int press_cal,hum_cal;

      int proximity = digitalRead(REED_PIN); // Read the state of the switch
  
  // int proximity = LOW;
  if ((proximity == LOW)  && (old_val == HIGH)) // If the pin reads low, the switch is closed.
  {
  //   Serial.println(proximity);
    delay(1); 
    // Serial.println("Switch closed");
    old_val=proximity;
     i=i+1;
     rain=0.03*i;
    digitalWrite(LED_PIN, HIGH); // Turn the LED on
    Serial.print("Rain Height=");
      Serial.print(rain);
      Serial.println(" mm");
  }
  else
  {
    digitalWrite(LED_PIN, LOW); // Turn the LED off
    old_val=proximity;
  }
    readData();
    
    temp_cal = calibration_T(temp_raw);
    press_cal = calibration_P(pres_raw);
    hum_cal = calibration_H(hum_raw);
    temp_act = (double)temp_cal / 100.0;
    press_act = (double)press_cal / 100.0;
    hum_act = (double)hum_cal / 1024.0;
    Serial.print("TEMP : ");
    Serial.print(temp_act);
    Serial.print(" DegC  PRESS : ");
    Serial.print(press_act);
    Serial.print(" hPa  HUM : ");
    Serial.print(hum_act);
    Serial.println(" %");    
    
    delay(1000);
// ends bme280

   
   time = millis();

   if (time >= nextCalcSpeed) {
      calcWindSpeed();
      nextCalcSpeed = time + MSECS_CALC_WIND_SPEED;
   }
   if (time >= nextCalcDir) {
      calcWindDir();
      nextCalcDir = time + MSECS_CALC_WIND_DIR;
   }
   if(time >=hourTime){
     
   }
}

//=======================================================
// Interrupt handler for anemometer. Called each time the reed
// switch triggers (one revolution).
//=======================================================
void countAnemometer() {
   numRevsAnemometer++;
}
//======================================================= 
// Interrupt handler for rainmeter. Called each time the reed 
// switch triggers (one tip of bucket). 
//======================================================= 
void countRainmeter() { 
static unsigned long lastmillis = 0; 
unsigned long m = millis(); 
  if (m - lastmillis < 200){ 
// ignore interrupt: probably a bounce problem 
  }else{ 
   numBuckettip++;
   rainAmount = numBuckettip*0.011;
   Serial.print("RAIN: ");
  Serial.println( rainAmount,3);
  } 
  lastmillis = m; 
}


//=======================================================
// Find vane direction.
//=======================================================
void calcWindDir() {
   int val;
   byte x, reading;

   val = analogRead(PIN_VANE);
   val >>=2;                        // Shift to 255 range
   reading = val;

   // Look the reading up in directions table. Find the first value
   // that's >= to what we got.
   for (x=0; x<NUMDIRS; x++) {
      if (adc[x] >= reading)
         break;
   }
   //Serial.println(reading, DEC);
   x = (x + dirOffset) % 8;   // Adjust for orientation
   Serial.print("  Dir: ");
   Serial.println(strVals[x]);
   // digital clock display of the time
  // setTime(hr,min,sec,day,month,yr); Another way to set
  /* setTime(9,15,0,29,5,2017); // Another way to set
 Serial.print(hour());
 printDigits(minute());
 printDigits(second());
 Serial.print(" ");
 Serial.print(day());
 Serial.print(" ");
 Serial.print(month());
 Serial.print(" ");
 Serial.print(year()); */
 Serial.println(); 
}


//=======================================================
// Calculate the wind speed, and display it (or log it, whatever).
// 1 rev/sec = 1.492 mph
//=======================================================
void calcWindSpeed() {
   int x, iSpeed;
   // This will produce mph * 10
   // (didn't calc right when done as one statement)
   long speed = 14920;
   speed *= numRevsAnemometer;
   speed /= MSECS_CALC_WIND_SPEED;
   iSpeed = speed;         // Need this for formatting below

   Serial.print("Wind speed: ");
   x = iSpeed / 10;
   Serial.print(x);
   Serial.print('.');
   x = iSpeed % 10;
   Serial.print(x);
Serial.print( " mph=");
Serial.print(x*0.4470);
Serial.print( " m/s");



   numRevsAnemometer = 0;        // Reset counter
}

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
