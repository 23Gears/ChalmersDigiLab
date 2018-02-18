
import processing.serial.*;
import cc.arduino.*;

Arduino arduino;
int rotPos = 90;
boolean grip = false;
int gripMaxValue = 180;
int gripMinValue = 100;

void setup() {
  size(500,500);
  //fullScreen();
  println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[0], 57600);

  arduino.pinMode(5, Arduino.SERVO);
  arduino.pinMode(9, Arduino.SERVO);
  arduino.pinMode(10, Arduino.SERVO);
 
}

void draw() {
  background(52);
  
  int rotPos = (int)map(mouseX, 0, width , 180, 0 );    //Mapping analog sensor values to actual degrees of rotation
  int liftPos = (int)map(mouseY, 0, height , 180, 0);


  arduino.servoWrite(10, rotPos);
  arduino.servoWrite(5, liftPos);
  if(grip){
    background(244,85,7);
    arduino.servoWrite(9,gripMaxValue);
  }
  else{
    arduino.servoWrite(9,gripMinValue);
  }

  rect(0,(height/2)-15,mouseX, 30);
  rect((width/2)-15,0,30,mouseY);
  textSize(30);
  text(rotPos,10,30);
  text(liftPos,10,60);

}

void mouseClicked() {
  grip = !grip;
}