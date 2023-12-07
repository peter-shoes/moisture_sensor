#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

#define DEBUG       true
#define DEBUG_SLEEP 100             // 0.1 seconds, how often we read in debug mode
#define OP_SLEEP    3600000         // one hour, how often we read during normal operation
#define READ_SLEEP  100             // 0.1 seconds, time between reading during read step 
#define S_READ_BUF  10              // size of our read buffer per sensor (preprocessor OK)
#define SCREEN_HI   100
#define SCREEN_LO   20 

#define V_AIR       590             // sensor measurement for air (ground truth)
#define V_DRY_SOIL  520             // sensor measurement for dry soil (ground truth)
#define V_WET_SOIL  356             // sensor measurement for wet soil (ground truth)
#define V_WATER     321             // sensor measurement for pure water or very wet soil (ground truth)
#define v_OPTIMAL   450             // estimate of what an optimal moisture level would be

// define global vars
Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();
int a0_buf[S_READ_BUF];
int a1_buf[S_READ_BUF];
int a2_buf[S_READ_BUF];
int normalized_reading = 0;
int last_moisture_value = 0;
int moisture_value = 0;

// define functions
void print_arr(int a[S_READ_BUF], String name);
void read_data();
void normalize_data();
void reading_to_value();
void update_display(int val);

void setup() {
  // setup serial
  Serial.begin(9600);
  Serial.println("Serial begin ...");

  // begin display comms
  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }

  // begin display
  update_display(0);
}

void loop() {
  // if we're not in debug mode, sleep for duty cycle reasons
  if (DEBUG) {delay(DEBUG_SLEEP);}
  else {delay(OP_SLEEP);}

  // get measurements (Sensor Data Extraction)
  read_data();
  
  // if we're debugging, print those measurements
  print_arr(a0_buf, "A0: ");
  print_arr(a1_buf, "A1: ");
  print_arr(a2_buf, "A2: ");
  
  // normalize measurements (Preprocessing)
  normalize_data();

  
  // convert measurements to percentage moisture (Feature Extraction / Classification)
  reading_to_value();
  
  // update display (Meaningful Output)
  if (abs(last_moisture_value - moisture_value) > 10)
  {
    update_display(moisture_value);
  }
}


void print_arr(int a[S_READ_BUF], String name)
{
  Serial.print(name);
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
    a0_buf[i] = analogRead(A0);
    a1_buf[i] = analogRead(A1);
    a2_buf[i] = analogRead(A2);
    delay(READ_SLEEP);
  }
}


void normalize_data()
{
  // Here, we want to take the raw data and turn it into a single useful value
  // begin by computing averages for each buffer
  int a0_avg = 0;
  int a1_avg = 0;
  int a2_avg = 0;
  for (int i=0; i < S_READ_BUF; i++)
  {
    a0_avg += a0_buf[i];
    a1_avg += a1_buf[i];
    a2_avg += a2_buf[i];
  }
  a0_avg /= S_READ_BUF;
  a1_avg /= S_READ_BUF;
  a2_avg /= S_READ_BUF;

  // we want to be sure that each value is not weighing too much on the total average
  // so we want to weigh each by its standard deviation
  // for now this is okay
  normalized_reading = (a0_avg+a1_avg+a2_avg)/3;
}


void reading_to_value()
{
  // update the cached value
  last_moisture_value = moisture_value;
  // Now we must convert the reading we have gotten into a usable moisture value
  // we know the sensors are bounded by our ground truths for air and water
  // so let's convert this to a value between 0 and 100 based on those bounds
  moisture_value = (float(V_AIR - normalized_reading)/float(V_AIR-V_WATER))*100;

  // but we want to bound this value explicitly, so let's take care of that
  if (moisture_value > 100) {moisture_value = 100;}
  if (moisture_value < 0) {moisture_value = 0;}
}


void update_display(int val)
{
  // Serial.println("updating display");
  // Now we want to display this value as a percentage of the pixels on the screen
  // because the bounds of the screen itself may be difficult to view, let's create a bounding box
  ledmatrix.drawFastVLine(0,0,8,SCREEN_LO);
  ledmatrix.drawFastVLine(14,0,8,SCREEN_LO);
  ledmatrix.drawFastHLine(0,0,15, SCREEN_LO);
  ledmatrix.drawFastHLine(0,6,15, SCREEN_LO);

  // then we need to clear the bars so that they can be written over
  for (int i=1; i<14; i++)
  {
    ledmatrix.drawFastVLine(i, 1, 5, 0);
  }
  // now we can actually do some conversions
  // we have a value from 0-100, and we want to convert that into a value from 1-14, since we have 14 available bars
  for (int i=1; i<(val*0.14); i++)
  {
    ledmatrix.drawFastVLine(14-i, 1, 5, SCREEN_HI);
  }
}

