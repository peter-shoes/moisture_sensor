#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

Adafruit_IS31FL3731_Wing ledmatrix = Adafruit_IS31FL3731_Wing();
int a0[10] = {0,0,0,0,0,0,0,0,0,0};
int a1[10] = {0,0,0,0,0,0,0,0,0,0};
int a2[10] = {0,0,0,0,0,0,0,0,0,0};

void print_arr(int a[10]);



// uint8_t sweep[] = {1, 2, 3, 4, 6, 8, 10, 15, 20, 30, 40, 60, 60, 40, 30, 20, 15, 10, 8, 6, 4, 3, 2, 1};
uint8_t sweep[] = {255,255,255,255,0,0,0,0};

void setup() {
  Serial.begin(9600);
  Serial.println("ISSI swirl test");

  if (! ledmatrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
}

void loop() {
  for (int i=0; i<10; i++) 
  {
    a0[i] = analogRead(A0);
    a1[i] = analogRead(A1);
    a2[i] = analogRead(A2);
    delay(100);
  }
  Serial.print("A0: ");
  print_arr(a0);
  Serial.print("A1: ");
  print_arr(a1);
  Serial.print("A2: ");
  print_arr(a2);
}

void print_arr(int a[10])
{
  for(int i =0; i < 10; i++) {
    Serial.print(a[i]);
    Serial.print(" ");
  }
  Serial.println();
}