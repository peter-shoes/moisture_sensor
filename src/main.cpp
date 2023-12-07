#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

#define DEBUG       true
#define DEBUG_SLEEP 1000            // one second, how often we read in debug mode
#define OP_SLEEP    1000 * 60 * 60  // one hour, how often we read during normal operation
#define READ_SLEEP  10000           // ten seconds, time between reading during read step 
#define S_READ_BUF  10              // size of our read buffer per sensor (preprocessor OK)
#define V_AIR       570             // sensor measurement for air (ground truth)
#define V_DRY_SOIL  520             // sensor measurement for dry soil (ground truth)
#define V_WET_SOIL  356             // sensor measurement for wet soil (ground truth)
#define V_WATER     321             // sensor measurement for pure water or very wet soil (ground truth)
#define v_OPTIMAL   450             // estimate of what an optimal moisture level would be

// define global vars
Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();
int a0[S_READ_BUF];
int a1[S_READ_BUF];
int a2[S_READ_BUF];
int normalized_reading;

// define functions
void print_arr(int a[10]);
void read_data();
void normalize_data();
void update_display(int val);
int reading_to_value(int reading);

void setup() {
  // setup serial
  Serial.begin(9600);

  // begin display comms
  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
}

void loop() {
  // if we're not in debug mode, sleep for duty cycle reasons
  if (DEBUG) {delay(DEBUG_SLEEP);}
  else {delay(OP_SLEEP);}
  
  // get measurements (Sensor Data Extraction)
  // if we're debugging, print those measurements
  // normalize measurements (Preprocessing)
  // convert measurements to percentage moisture (Feature Extraction / Classification)
  // update display (Meaningful Output)
}

void print_arr(int a[S_READ_BUF])
{
  for(int i =0; i < S_READ_BUF; i++) {
    Serial.print(a[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void read_data()
{
    for (int i=0; i<S_READ_BUF; i++) 
  {
    a0[i] = analogRead(A0);
    a1[i] = analogRead(A1);
    a2[i] = analogRead(A2);
    delay(READ_SLEEP);
  }
  Serial.print("A0: ");
  print_arr(a0);
  Serial.print("A1: ");
  print_arr(a1);
  Serial.print("A2: ");
  print_arr(a2);
}

void normalize_data()
{
}

void update_display(int val)
{
}

int reading_to_value(int reading)
{
}