#include <IRremote.h>
#include <IRremoteInt.h>

/*
 * Auto Aoratos - demonstrates home automation with IR control over devices in room
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 April, 2014
 * Copyright 2014 Andrew Free
 * http://andrewfree.com
 */

IRsend irsend;

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void light_off(int dud);
void light_on(int dud);
void light_brightness_change(int dud);
void light_color_green(int dud);
void light_color_red(int dud);
void light_color_purple(int dud);

struct command {
  char* functionName;
  void (*function)(int z);
};

// array of command structures
// Send commands ex:  light_on:1, light_off:1
struct command commands[] = {
  {"light_off",light_off},
  {"light_on",light_on},
  {"light_brightness_change",light_brightness_change},
  {"light_color_green",light_color_green},
  {"light_color_red",light_color_red},
  {"light_color_purple",light_color_purple},
};

void setup() {
    Serial.begin(9600);
    inputString.reserve(200); // reserve 200 bytes for the inputString:
}

// Main loop //
void loop() {
  if (stringComplete) { // If serialEvent() found complete newline it would put it into inputString and set stringComplete true
    bool matched_command = false; 
    String cmd_opt = getValue(inputString, ':', 1);
    if (cmd_opt.length() > 1) {
       inputString = getValue(inputString, ':', 0);
    }
    for(int i=0;i < (sizeof(commands)/sizeof(commands[0]));i++){      
      if(inputString.equals(commands[i].functionName)){
        commands[i].function(cmd_opt.toInt());
        Serial.println("200");
        matched_command = true;
        break;
      }
    }
    inputString = "";
    stringComplete = false;
    if (matched_command == false) {
      Serial.println("404");
    }
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  int count = 0;
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

// Returns substrigs of data split but n
 String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// Light IR Functions //

      // Lumonosity //

void light_on(int dud) {
   irsend.sendNEC(0xF740BF, 32); // On lights
   delay(14);
}

void light_off(int dud) {
  irsend.sendNEC(0xF7C03F, 32); // Off lights
  delay(14);
}

void light_brightness_down() {
  irsend.sendNEC(0xF7807F, 32); // Brightness down one
  delay(14);
}

void light_brightness_up() {
  irsend.sendNEC(0xF700FF, 32); // Brightness up one.
  delay(14);
}

void light_brightness_change(int change) {
  bool positive = change > 0;
  if (positive == false) {
    for (int b = change; b < 0; b++) {
     delay(400);
     light_brightness_down();
    }
  }
  else {
    for(int b = change; b > 0; b--) {
     delay(400);
     light_brightness_up();
    }
  }
}
      // Colors //

void light_color_purple(int dud) {
   irsend.sendNEC(0xF7D02F, 32); // Lights purple
   delay(14);
}

void light_color_blue() { // Lights blue
  irsend.sendNEC(0xF7609F, 32);
  delay(14);
}

void light_color_green(int dud) { // Lights green
  irsend.sendNEC(0xF7A05F, 32);
  delay(14);
}

void light_color_red(int dud) { // Lights red
  irsend.sendNEC(0xF720DF, 32);
  delay(14);
}

void light_color_white() { // Lights white
  irsend.sendNEC(0xF7E01F, 32);
  delay(14);
}

void light_color_orange() { // Orange
  irsend.sendNEC(0xF710EF, 32);
  delay(14);
}

void light_color_yellow() { // Lights yellow
  irsend.sendNEC(0xF7906F, 32);
  delay(14);
}

void light_color_cyan() { // Lights cyan
  irsend.sendNEC(0xF750AF, 32);
  delay(14);
}

     // Changing colors //

void light_jump_3() { // Light jump 3
  irsend.sendNEC(0xF730CF, 32);
  delay(14);
}

void light_jump_7() { // light jump 7
  irsend.sendNEC(0xF7B04F, 32);
  delay(14);
}

void light_fade_3() { // Light fade 3
  irsend.sendNEC(0xF7708F, 32);
  delay(14);
}

void light_fade_7() { // Light fade 7
  irsend.sendNEC(0xF7F00F, 32);
  delay(14);
}

    // Changing to music //

void light_music_1() { // Music button 1
  irsend.sendNEC(0xF708F7, 32);
  delay(14);
}

void light_music_2() { // Muisc button 2
  irsend.sendNEC(0xF78877, 32);
  delay(14);
}

void light_music_3() { // Music button 3
  irsend.sendNEC(0xF748B7, 32);
  delay(14);
}
void light_music_4() { // Music button 4
  irsend.sendNEC(0xF7C837, 32);
  delay(14);
}

