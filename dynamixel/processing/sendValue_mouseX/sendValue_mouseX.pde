import processing.serial.*;

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
}


void draw()
{
 sendVal = mouseX;
 motorMessage.setFloat("motor1",mouseX);
 motorPort.write(motorMessage.toString());
 //println(motorMessage.toString());
 
 
  
  
  
}
