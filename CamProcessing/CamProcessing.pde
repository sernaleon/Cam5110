import processing.video.*;
import processing.serial.*;

Capture cam;
Serial arduino;

byte toSend, offset,x;
int column, rows;
    
void setup() {
  size(84, 48);
  arduino = new Serial(this, Serial.list()[0], 115200);  
  cam = new Capture(this, 640, 480);
  cam.start();
}

void draw() {
  if (cam.available()) {
    cam.read();
    cam.filter(THRESHOLD,.4);    
    image(cam, 0, 0,84,48); 
    loadPixels();
    for(rows = 0; rows < 4032; rows+=672){
      for(x = 0; x < 84; x++) {    
        for(column=0, toSend=0, offset=0; column < 672; column+= 84, offset++){   
          toSend |= pixels[column+x+rows] > -2 ? 0 : 1 << offset;   
        } 
        arduino.write(toSend); 
      }
    }
  }
}
