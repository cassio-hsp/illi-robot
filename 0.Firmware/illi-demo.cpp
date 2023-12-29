//Pinos utilizados: 
//MOTOR_A1 = 32;
//MOTOR_A2 = 33;
//MOTOR_B1 = 25;
//MOTOR_B2 = 26;
//NEOPIXEL = 12;
//BUZZER = 32;

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_VL53L0X.h"

#include <ToneESP32.h>

#define BUZZER_PIN 17
#define BUZZER_CHANNEL 0

ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

#define PIN        12 
#define NUMPIXELS 16 
#define DELAYVAL 30 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float lidar_distance=0;
float distance_ps_filter=0;
int minimum_motor = 20;
int ramp_delay=0;

int ramp_control=0;
long time_A=0;
long time_B=0;

int MOTOR_A1 = 32;
int MOTOR_A2 = 33;
int MOTOR_B1 = 25;
int MOTOR_B2 = 26;

void play_tone(int escolha)
{
  /*
  #define NOTE_B0  31
  #define NOTE_C1  33
  #define NOTE_CS1 35
  #define NOTE_D1  37
  #define NOTE_DS1 39
  #define NOTE_E1  41
  #define NOTE_F1  44
  #define NOTE_FS1 46
  #define NOTE_G1  49
  #define NOTE_GS1 52
  #define NOTE_A1  55
  #define NOTE_AS1 58
  #define NOTE_B1  62
  #define NOTE_C2  65
  #define NOTE_CS2 69
  #define NOTE_D2  73
  #define NOTE_DS2 78
  #define NOTE_E2  82
  #define NOTE_F2  87
  #define NOTE_FS2 93
  #define NOTE_G2  98
  #define NOTE_GS2 104
  #define NOTE_A2  110
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_C3  131
  #define NOTE_CS3 139
  #define NOTE_D3  147
  #define NOTE_DS3 156
  #define NOTE_E3  165
  #define NOTE_F3  175
  #define NOTE_FS3 185
  #define NOTE_G3  196
  #define NOTE_GS3 208
  #define NOTE_A3  220
  #define NOTE_AS3 233
  #define NOTE_B3  247
  #define NOTE_C4  262
  #define NOTE_CS4 277
  #define NOTE_D4  294
  #define NOTE_DS4 311
  #define NOTE_E4  330
  #define NOTE_F4  349
  #define NOTE_FS4 370
  #define NOTE_G4  392
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_AS4 466
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_CS5 554
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F5  698
  #define NOTE_FS5 740
  #define NOTE_G5  784
  #define NOTE_GS5 831
  #define NOTE_A5  880
  #define NOTE_AS5 932
  #define NOTE_B5  988
  #define NOTE_C6  1047
  #define NOTE_CS6 1109
  #define NOTE_D6  1175
  #define NOTE_DS6 1245
  #define NOTE_E6  1319
  #define NOTE_F6  1397
  #define NOTE_FS6 1480
  #define NOTE_G6  1568
  #define NOTE_GS6 1661
  #define NOTE_A6  1760
  #define NOTE_AS6 1865
  #define NOTE_B6  1976
  #define NOTE_C7  2093
  #define NOTE_CS7 2217
  #define NOTE_D7  2349
  #define NOTE_DS7 2489
  #define NOTE_E7  2637
  #define NOTE_F7  2794
  #define NOTE_FS7 2960
  #define NOTE_G7  3136
  #define NOTE_GS7 3322
  #define NOTE_A7  3520
  #define NOTE_AS7 3729
  #define NOTE_B7  3951
  #define NOTE_C8  4186
  #define NOTE_CS8 4435
  #define NOTE_D8  4699
  #define NOTE_DS8 4978
  */

if(escolha == 1)
{
  buzzer.tone(NOTE_AS5, 400);
  buzzer.tone(NOTE_F5, 200);
  buzzer.tone(NOTE_AS5, 400);  
}
if(escolha == 2)
{
  buzzer.tone(NOTE_A5, 100);
  buzzer.tone(NOTE_D6, 400);
  buzzer.tone(NOTE_F6, 300);  
}
if(escolha == 3)
{
  buzzer.tone(NOTE_A6, 50);
  buzzer.tone(NOTE_B6, 50);
  buzzer.tone(NOTE_C7, 50);
  buzzer.tone(NOTE_D7, 50);
  buzzer.tone(NOTE_A7, 50);
  buzzer.tone(NOTE_E7, 50);
  buzzer.tone(NOTE_F7, 50);
  buzzer.tone(NOTE_G7, 50);
  buzzer.tone(NOTE_A7, 50);
  buzzer.tone(NOTE_B7, 50);
  buzzer.tone(NOTE_C8, 50);  
  buzzer.tone(NOTE_D8, 50);  
}
if(escolha == 4)
{
  buzzer.tone(NOTE_A6, 50);
  buzzer.tone(NOTE_B6, 100);
  buzzer.tone(NOTE_C7, 50);
  buzzer.tone(NOTE_D7, 100);
  buzzer.tone(NOTE_A7, 50);
  buzzer.tone(NOTE_E7, 50);  
}
if(escolha == 5)
{
  buzzer.tone(NOTE_F7, 10);
  buzzer.tone(NOTE_G7, 300);
  buzzer.tone(NOTE_F7, 200);
  buzzer.tone(NOTE_B7, 50);
  buzzer.tone(NOTE_C8, 50);  
  buzzer.tone(NOTE_A6, 50); 
}
if(escolha == 6)
{
  buzzer.tone(NOTE_A5, 300);
  buzzer.noTone();
  delay(500);
  buzzer.tone(NOTE_F5, 300);  
}
}

void frente_up(int value, int ramp_time)
{
  if(ramp_control == 0)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=minimum_motor;k<=value;k++)
    {
      analogWrite(MOTOR_A1, 0);
      analogWrite(MOTOR_A2, k);
      analogWrite(MOTOR_B1, k);
      analogWrite(MOTOR_B2, 0);
      delay(ramp_delay);
    }
    time_B = millis();
    ramp_control=1;
  }  
}

void frente_down(int value, int ramp_time)
{
  if(ramp_control == 1)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=value;k>=minimum_motor;k--)
    {
      analogWrite(MOTOR_A1, 0);
      analogWrite(MOTOR_A2, k);
      analogWrite(MOTOR_B1, k);
      analogWrite(MOTOR_B2, 0);
      delay(ramp_delay);
    }
    time_B = millis();
    ramp_control=0;
  }  
}

void re_up(int value, int ramp_time)
{
  if(ramp_control==0)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=minimum_motor;k<=value;k++)
    {
      analogWrite(MOTOR_A1, k);
      analogWrite(MOTOR_A2, 0);
      analogWrite(MOTOR_B1, 0);
      analogWrite(MOTOR_B2, k);
      delay(ramp_delay);
     }
     time_B = millis();
     ramp_control=1;  
  }  
}

void re_down(int value, int ramp_time)
{
  if(ramp_control==1)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=value;k>=minimum_motor;k--)
    {
      analogWrite(MOTOR_A1, k);
      analogWrite(MOTOR_A2, 0);
      analogWrite(MOTOR_B1, 0);
      analogWrite(MOTOR_B2, k);
      delay(ramp_delay);
     }
     time_B = millis();
     ramp_control=0;  
  }  
}

void giro_esquerda_up(int value, int ramp_time)
{
  if(ramp_control==0)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=minimum_motor;k<=value;k++)
    {
      analogWrite(MOTOR_A1, k);
      analogWrite(MOTOR_A2, 0);
      analogWrite(MOTOR_B1, k);
      analogWrite(MOTOR_B2, 0);
      delay(ramp_delay);
     }
     time_B = millis();
     ramp_control=1;  
  }  
}

void giro_esquerda_down(int value, int ramp_time)
{
  if(ramp_control==1)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=value;k>=minimum_motor;k--)
    {
      analogWrite(MOTOR_A1, k);
      analogWrite(MOTOR_A2, 0);
      analogWrite(MOTOR_B1, k);
      analogWrite(MOTOR_B2, 0);
      delay(ramp_delay);
     }
     time_B = millis();
     ramp_control=0;  
  }  
}

void giro_direita_up(int value, int ramp_time)
{
  if(ramp_control==0)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=minimum_motor;k<=value;k++)
    {
      analogWrite(MOTOR_A1, 0);
      analogWrite(MOTOR_A2, k);
      analogWrite(MOTOR_B1, 0);
      analogWrite(MOTOR_B2, k);
      delay(ramp_delay);
     }
     time_B = millis();
     ramp_control=1;  
  }  
}

void giro_direita_down(int value, int ramp_time)
{
  if(ramp_control==1)
  {
    ramp_delay = ramp_time/(value-minimum_motor);
    time_A = millis();
    for(int k=value;k>=minimum_motor;k--)
    {
      analogWrite(MOTOR_A1, 0);
      analogWrite(MOTOR_A2, k);
      analogWrite(MOTOR_B1, 0);
      analogWrite(MOTOR_B2, k);
      delay(ramp_delay);
     }
     time_B = millis();
     ramp_control=0;  
  }  
}

void stop_movement()
{
  analogWrite(MOTOR_A1, 0);
  analogWrite(MOTOR_A2, 0);
  analogWrite(MOTOR_B1, 0);
  analogWrite(MOTOR_B2, 0);
}

void neopixel_boot()
{
  for(int i=0; i<NUMPIXELS; i++) 
  {   
    pixels.setPixelColor(i, pixels.Color(100, 0, 0));
    pixels.show();  
    delay(DELAYVAL); 
  }

  for(int i=0; i<NUMPIXELS; i++) 
  {     
    pixels.setPixelColor(i, pixels.Color(0, 100, 0));
    pixels.show();   
    delay(DELAYVAL);
  }

  for(int i=0; i<NUMPIXELS; i++) 
  { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 100));
    pixels.show(); 
    delay(DELAYVAL); 
  }
}

void neopixel_stop()
{
  for(int i=0; i<NUMPIXELS; i++) 
  { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show(); 
    delay(DELAYVAL); 
  }
   pixels.show();  
}

void neopixel_forward()
{
  for(int i=0; i<8; i++) 
  { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 100));
    pixels.show();
    delay(DELAYVAL);      
  }    
}

void neopixel_reverse()
{
  for(int i=8; i<16; i++) 
  { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 100));
    pixels.show(); 
    delay(DELAYVAL);     
  }  
}

void neopixel_fade_blue()
{
  for(int i=0; i<100; i++) 
  { 
    pixels.setPixelColor(0, pixels.Color(0, 0, i));
    pixels.setPixelColor(1, pixels.Color(0, 0, i));
    pixels.setPixelColor(2, pixels.Color(0, 0, i));
    pixels.setPixelColor(3, pixels.Color(0, 0, i));
    pixels.setPixelColor(4, pixels.Color(0, 0, i));
    pixels.setPixelColor(5, pixels.Color(0, 0, i));
    pixels.setPixelColor(6, pixels.Color(0, 0, i));
    pixels.setPixelColor(7, pixels.Color(0, 0, i));
    pixels.setPixelColor(8, pixels.Color(0, 0, i));
    pixels.setPixelColor(9, pixels.Color(0, 0, i));
    pixels.setPixelColor(10, pixels.Color(0, 0, i));
    pixels.setPixelColor(11, pixels.Color(0, 0, i));
    pixels.setPixelColor(12, pixels.Color(0, 0, i));
    pixels.setPixelColor(13, pixels.Color(0, 0, i));
    pixels.setPixelColor(14, pixels.Color(0, 0, i));
    pixels.setPixelColor(15, pixels.Color(0, 0, i));    
    pixels.show(); 

    delay(10);    
  }
  delay(100);
  
  for(int i=100; i>=0; i--) 
  { 
    pixels.setPixelColor(0, pixels.Color(0, 0, i));
    pixels.setPixelColor(1, pixels.Color(0, 0, i));
    pixels.setPixelColor(2, pixels.Color(0, 0, i));
    pixels.setPixelColor(3, pixels.Color(0, 0, i));
    pixels.setPixelColor(4, pixels.Color(0, 0, i));
    pixels.setPixelColor(5, pixels.Color(0, 0, i));
    pixels.setPixelColor(6, pixels.Color(0, 0, i));
    pixels.setPixelColor(7, pixels.Color(0, 0, i));
    pixels.setPixelColor(8, pixels.Color(0, 0, i));
    pixels.setPixelColor(9, pixels.Color(0, 0, i));
    pixels.setPixelColor(10, pixels.Color(0, 0, i));
    pixels.setPixelColor(11, pixels.Color(0, 0, i));
    pixels.setPixelColor(12, pixels.Color(0, 0, i));
    pixels.setPixelColor(13, pixels.Color(0, 0, i));
    pixels.setPixelColor(14, pixels.Color(0, 0, i));
    pixels.setPixelColor(15, pixels.Color(0, 0, i));    
    pixels.show(); 

    delay(10);    
  }
  delay(100);  
}

void neopixel_fade_green()
{
  for(int i=0; i<100; i++) 
  { 
    for(int k=0;k<=NUMPIXELS;k++)
    {
    pixels.setPixelColor(k, pixels.Color(0, i, 0));
    pixels.show();        
    }
    delay(10);    
  }
  delay(100);
  
  for(int i=100; i>=100; i--) 
  { 
    for(int k=0;k<=NUMPIXELS;k++)
    {
    pixels.setPixelColor(k, pixels.Color(0, i, 0));
    pixels.show();        
    }
    delay(10);    
  }
  delay(100);
}

void neopixel_boomerang_color()
{
    for(int k=0;k<=NUMPIXELS;k++)
    {
    pixels.setPixelColor(k, pixels.Color(200, 0, 0));
    delay(50); 
    pixels.show();        
    }

    for(int k=0;k<=NUMPIXELS;k++)
    {
    pixels.setPixelColor(k, pixels.Color(0, 200, 0));
    delay(50); 
    pixels.show();        
    }
    

    for(int k=0;k<=NUMPIXELS;k++)
    {
    pixels.setPixelColor(k, pixels.Color(0, 0, 200));
    delay(50); 
    pixels.show();        
    }
    
}

void neopixel_wave_red()
{        
  for(int k=0;k<=NUMPIXELS;k++)
    {
    pixels.setPixelColor(k, pixels.Color(200, 0, 0));
    delay(50); 
    pixels.show();        
    }
    
}

void neopixel_wave_re()
{        
  for(int k=8;k<=NUMPIXELS;k++)
    {
    pixels.setPixelColor(k, pixels.Color(230, 0, 230));
    delay(50); 
    pixels.show();        
    }
    
}


void lidar()
{
  lidar_distance=0;
  for(int k=0;k<=9;k++)
  {    
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);   
    if (measure.RangeStatus != 4) 
    {   
      //Serial.println(measure.RangeMilliMeter);  
    } 
    else 
    {
      Serial.println(" out of range ");
    }
    lidar_distance = lidar_distance + ((measure.RangeMilliMeter/10.0) - 2.0);    //2.0 eh offset calibração. -2cm
  }
  distance_ps_filter = lidar_distance/10.0;
  Serial.println("Distance (cm): ");
  Serial.println(distance_ps_filter);
}

void setup() 
{
  Serial.begin(115200);
  pixels.begin(); 
  neopixel_stop();
  
  /*
  Serial.println("VL53L0X:");
  if (!lox.begin()) 
  {
    Serial.println(F("Failed to boot VL53L0X"));
    play_tone(6);
    while(1);
  }
  */
  
  pinMode(MOTOR_A1, OUTPUT);    //Motor B (1)
  pinMode(MOTOR_A2, OUTPUT);    //Motor B (2)
  pinMode(MOTOR_B1, OUTPUT);    //Motor A (1)
  pinMode(MOTOR_B2, OUTPUT);     //Motor A (2)
  delay(1000);
  
  play_tone(1); 
  delay(500); 
  pixels.setPixelColor(0, pixels.Color(200, 200, 200)); 
  pixels.setPixelColor(7, pixels.Color(200, 200, 200));
  pixels.show();  
  delay(250);
  neopixel_stop();  
  pixels.setPixelColor(1, pixels.Color(200, 200, 200)); 
  pixels.setPixelColor(6, pixels.Color(200, 200, 200));
  pixels.show();  
  delay(250);
  neopixel_stop();  
  pixels.setPixelColor(2, pixels.Color(200, 200, 200)); 
  pixels.setPixelColor(5, pixels.Color(200, 200, 200));
  pixels.show();  
  delay(250);
  neopixel_stop();  
  pixels.setPixelColor(3, pixels.Color(200, 200, 200)); 
  pixels.setPixelColor(4, pixels.Color(200, 200, 200));
  pixels.show();  
  delay(250);

  neopixel_stop();      
  neopixel_boot();
  neopixel_stop(); 
    
}

void loop() 
{  
  //lidar();
  pixels.clear();    
  play_tone(2); 
  neopixel_forward();  
  frente_up(200,500); 
  delay(500);
  frente_down(200,500);
  delay(500); 
   
  neopixel_wave_red();
  play_tone(3); 
  giro_direita_up(200, 500);   
  delay(3320);
  giro_direita_down(200, 500);
  delay(3320);
  
  neopixel_wave_re();
  re_up(200,500);
  delay(500);  
  re_down(200,500);  
  delay(500);

  play_tone(4);
  stop_movement();  
  neopixel_boomerang_color();
  delay(30000);   
  
  
  pixels.clear(); 
  
  /*while(true)
  {
    lidar();
    Serial.print("Distance (cm): ");
    Serial.println(distance_ps_filter);
    if(distance_ps_filter <= 10 )
    {
      Serial.println("Condition 1");
      lidar_re();   
    }
    if(distance_ps_filter > 10)
    {
      Serial.println("Condition 2");
      lidar_frente();    
    }  
  } */   
    
}