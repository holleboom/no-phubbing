// Graphing sketch


// This program takes ASCII-encoded strings
// from the serial port at 9600 baud and graphs them. It expects values in the
// range 0 to 1023, followed by a newline, or newline and carriage return

// Created 20 Apr 2005
// Updated 18 Jan 2008
// by Tom Igoe
// This example code is in the public domain.

import processing.serial.*;
import g4p_controls.*;

int startTime;
int elapsed;
PFont font;


Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph

float angle; 
float hsb_map;

float hue;
float brightness;
float saturation;

PImage bg;



void setup () {
  // set the window size:
  size(1280, 800);   
  colorMode(HSB);  
  myPort = new Serial(this, Serial.list()[2], 9600);
  myPort.bufferUntil('\n');
  
  //hint(ENABLE_NATIVE_FONTS);
  font = createFont("ProximaNova-Semibold", 16, true); 
  textFont(font, 32); 
}
void draw () {
  // everything happens in the serialEvent()  
  
  translate(0,height/5);
  smooth();
    


  if (angle<25) {

    startTime = millis();
    float hue = map(angle, 0, 25, 125, 150);
    float saturation = 70;
    float brightness = map(angle, 0, 45, 150, 200);
    background(hue, saturation, brightness);
    fill(hue, saturation, brightness);
  }
  else {
    elapsed = millis() - startTime;
    float hue = 0;
    float saturation = map(angle, 25, 40, 70, 150);
    float brightness = map(angle, 25, 40, 200, 255);
    background(hue, saturation, brightness);
    fill(hue, saturation, brightness);
  }

  textAlign(CENTER);
  strokeWeight(2);
  stroke(0, 0, 255);
  
  fill(0,0,255);
  if (elapsed>0) {
    text(float(elapsed)/1000, width/2, (height/4)*2.5);
  }


  fill(0, 0, 255);
  noStroke();
  ellipse(width/2, height/2, width/100, width/100);

  //    

  
  noStroke();

  //Phone variables
  int phoneWidth = width/3;
  int phoneHeight = 5;  

  
  //Meter
  noFill();
  stroke(0, 0, 255);
  strokeWeight(3);
  arc(width/2, height/2, phoneWidth*0.9, phoneWidth*0.9, -PI, 0.5*-PI);

  textSize(14);
  textAlign(CENTER);
  text("COOL",width/4+75, (height/2)+5);
  text("ONGEZELLIG",width/2, (height/4)-25);
    
    textSize(60);
    fill(0,0,255);
    text("GEEN GEPHUB IN DEZE PUB.",width/2, height/15);
  
  translate((width/2), (height/2));

  noStroke();
  fill(255);
  rotate(radians(angle)+2*PI); 
  rect(-phoneWidth/2, -phoneHeight/2, phoneWidth/2, phoneHeight, 5, 5, 5, 5);
}

void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    // trim off any whitespace:
    inString = trim(inString);
    // convert to an int and map to the screen height:
    angle = int(inString); 
    hsb_map = map(angle, 0, 90, 0, 255);
  }
}

