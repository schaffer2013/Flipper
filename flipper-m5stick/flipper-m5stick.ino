#include <M5StickC.h>

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float mag= 0.0F;
float angle= 0.0F;
float activeAcc[3];
float origin[3]={0,0,0};
float FRONT[3]={0,0,1};
float TOP[3]={-1,0,0};
float RIGHT[3]={0,1,0};
float BACK[3]={0,0,-1};
float BOTTOM[3]={1,0,0};
float LEFT[3]={0,-1,0};

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(40, 0);
  M5.Lcd.println("IMU TEST");
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.println("  X       Y       Z");
//  M5.Lcd.setCursor(0, 50);
//  M5.Lcd.println("  Pitch   Roll    Yaw");
}

float temp = 0;
/*****************************************
M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
M5.IMU.getAccelData(&accX,&accY,&accZ);
M5.IMU.getAhrsData(&pitch,&roll,&yaw);
M5.IMU.getTempData(&temp);
*****************************************/
void loop() {
  // put your main code here, to run repeatedly:
    M5.IMU.getAccelData(&accX,&accY,&accZ);
//  M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);

  activeAcc[0]=accX;
  activeAcc[1]=accY;
  activeAcc[2]=accZ;
  

  mag=threedDist(activeAcc,origin);

//  M5.IMU.getAccelData(&accX,&accY,&accZ);
//  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
//  M5.IMU.getTempData(&temp);
  
//  M5.Lcd.setCursor(0, 20);
//  M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ);
//  M5.Lcd.setCursor(140, 20);
//  M5.Lcd.print("o/s");
  M5.Lcd.setCursor(0, 20);
  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
//  M5.Lcd.setCursor(140, 30);
//  M5.Lcd.print("G");
//  M5.Lcd.setCursor(0, 60);
//  M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw);

  float minAngle=999.0F;
  char orientation[10]=""; 

  //FRONT
  angle=angleBetween(activeAcc,FRONT);
  if (angle<minAngle){
    strcpy(orientation,"FRONT    ");
    minAngle=angle;
  }
    //TOP
  angle=angleBetween(activeAcc,TOP);
  if (angle<minAngle){
    strcpy(orientation,"TOP      ");
    minAngle=angle;
  }
    //RIGHT
  angle=angleBetween(activeAcc,RIGHT);
  if (angle<minAngle){
    strcpy(orientation,"RIGHT    ");
    minAngle=angle;
  }
  //BACK
  angle=angleBetween(activeAcc,BACK);
  if (angle<minAngle){
    strcpy(orientation,"BACK     ");
    minAngle=angle;
  }
    //BOTTOM
  angle=angleBetween(activeAcc,BOTTOM);
  if (angle<minAngle){
    strcpy(orientation,"BOTTOM   ");
    minAngle=angle;
  }
    //LEFT
  angle=angleBetween(activeAcc,LEFT);
  if (angle<minAngle){
    strcpy(orientation,"LEFT     ");
    minAngle=angle;
  }

  M5.Lcd.setCursor(0, 50);
  M5.Lcd.printf(orientation);
  
//  M5.Lcd.setCursor(0, 60);
//  M5.Lcd.printf("Angle : %.2f ", angle);

  M5.Lcd.setCursor(0, 70);
  M5.Lcd.printf("Magnitude : %.2f ", mag);
  delay(200);
}

float threedDist(float pos1[3], float pos2[3]){
  return sqrt(pow(pos1[0]-pos2[0],2)+pow(pos1[1]-pos2[1],2)+pow(pos1[2]-pos2[2],2));
}

float dot(float pos1[3], float pos2[3]){
  return (pos1[0]*pos2[0]+pos1[1]*pos2[1]+pos1[2]*pos2[2]);
}

float angleBetween(float pos1[3], float pos2[3]){
  float origin[3]={0,0,0};
  float dotP=dot(pos1,pos2);
  float mag1=threedDist(pos1,origin);
  float mag2=threedDist(pos2,origin);
  return acos(dotP/(mag1*mag2));
}
