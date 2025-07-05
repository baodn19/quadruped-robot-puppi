#include "Servo1.h"        //导入库函数Servo1.h

TwoWire IIC = TwoWire(0);                   //初始化IIC的IO口
Servo1 pwm = Servo1(0x40, IIC);  //实例化pwm

#define S_SCL   33                //定义时钟线的IO口为GPIO33
#define S_SDA   32                //定义数据线的IO口为GPIO32

#define SERVO_FREQ 50
             
#define LEG0 0
#define LEG1 1               

//设置舵机摆臂初始位置
int Position = 86;

//初始化舵机                                    
void ServoSetup(){                 
  IIC.begin(S_SDA, S_SCL, 26000000);        //打开IIC通道
  pwm.begin();
  pwm.setOscillatorFrequency(26000000);       
  pwm.setPWMFreq(SERVO_FREQ);             //刷新频率为50Hz
  Wire.setClock(100000);                   //修改IIC时钟频率为100KHz
  delay(10);
}

//转动舵机摆臂
void servoDebug(byte servoID, int offset){   
  if(Position<=484){              //原pwm小于等于484时开始步进操作
    Position += offset;           //舵机在原来的位置上摆动offset
    pwm.setPWM(servoID, 0, Position);  //令指定舵机摆动到指定位置
  }else{
    Position  = 86;
    pwm.setPWM(servoID,0,Position);
  }
}

void setup() {
  ServoSetup();
  pwm.setPWM(1,0,386);      //为防止0号舵机摆动过程被1号舵机阻碍，需先将1号舵机设置到一定的角度给0号舵机预留空间      
  pwm.setPWM(0,0,86);       //初始化舵机摆臂位置
}

void loop() {
    servoDebug(0,1);       //0号舵机以偏移量1步进
    delay(50);             //系统暂停50ms
}