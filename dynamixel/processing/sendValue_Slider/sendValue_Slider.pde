import processing.serial.*;
import controlP5.*;

ControlP5 cp5;
Serial motorPort;
float sendVal;

JSONObject motorMessage;;

void setup()
{
  size(1000,200);
  String portName = Serial.list()[0];
  println(portName);
  motorPort = new Serial(this, portName, 115200);
  
  motorMessage = new JSONObject();
  
    cp5 = new ControlP5(this);
  
 
  cp5.addSlider("sendVal")
     .setPosition(100,50)
     .setRange(0,5000)
     .setDecimalPrecision(2)
     .setSize(700,200)
     ;
  
}


void draw()
{
 background(0);
 stroke(255);
 
  
 //sendVal = mouseX;
 motorMessage.setFloat("motor1",sendVal);
 motorPort.write(motorMessage.toString());
 println(motorMessage.toString());
 

  
  
  
}
