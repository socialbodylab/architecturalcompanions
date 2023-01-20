import processing.serial.*;
import controlP5.*;

ControlP5 cp5;
Serial motorPort;
float sendVal1;
float sendVal2;
JSONObject motorMessage;

float maxVal = 15340;

void setup()
{
  size(1000,500);
  String portName = Serial.list()[0];
  println(portName);
  motorPort = new Serial(this, portName, 115200);
  
  motorMessage = new JSONObject();
  
    cp5 = new ControlP5(this);
  
 
  cp5.addSlider("sendVal1")
     .setPosition(100,50)
     .setRange(0,maxVal)
     .setDecimalPrecision(2)
     .setSize(700,200)
     ;
     
       cp5.addSlider("sendVal2")
     .setPosition(100,260)
     .setRange(0,maxVal)
     .setDecimalPrecision(2)
     
     .setSize(700,200)
     ;
  
}


void draw()
{
 background(0);
 stroke(255);
 
  
 //sendVal = mouseX;
 motorMessage.setFloat("motor1",sendVal1);
  motorMessage.setFloat("motor2",sendVal2);
  motorMessage.setFloat("maxVal",maxVal);
 motorPort.write(motorMessage.toString());
 println(motorMessage.toString());
 

  
  
  
}
