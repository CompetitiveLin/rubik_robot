#include <Servo.h>
#include<Stepper.h>
//测试1
//CD0L2D1L2R1B0D0R1U1L0U1B2R1B0D2F0R0D2F2O  
//打乱 
//CF2D2R1F1D2B1R0B2U0L1U0R0D1B1R0L2D0L2D1O 
//还原

//测试2
//CB0F0D1U1B0R1O
//打乱 
//CR0B1U0D0F1B1O
//还原

//测试3
//CD0U0L0R0B1F2U0O
//打乱 
//CU1F2B0R1L1U1D1O
//还原

//测试4
//CU0L2R2U1L2R2U1O
//打乱 
//CU0R2L2U0R2L2U1O
//还原
#define STEPPIN_F 2
#define DIRPIN_F 3
#define STEPPIN_B 4
#define DIRPIN_B 5
#define STEPPIN_L 6
#define DIRPIN_L 7
#define STEPPIN_R 8
#define DIRPIN_R 9
#define STEPPIN_U 10
#define DIRPIN_U 11
#define STEPPIN_D 12
#define DIRPIN_D 13
#define F_servo  A0
#define B_servo  A1
#define L_servo  A2
#define R_servo  A3
#define U_servo  A4
#define D_servo  A5
#define STEPPIN_T A6
#define DIRPIN_T A7
#define DELAY 0
#define DELAY1 40

#define F_SERVO_OPEN   0
#define F_SERVO_CLOSE  180
#define B_SERVO_OPEN   180
#define B_SERVO_CLOSE  0
#define L_SERVO_OPEN   0
#define L_SERVO_CLOSE  180
#define R_SERVO_OPEN   180
#define R_SERVO_CLOSE  0
#define U_SERVO_OPEN   80
#define U_SERVO_CLOSE  120   
#define D_SERVO_OPEN   180
#define D_SERVO_CLOSE  0
Servo Fservo;
Servo Bservo;
Servo Lservo;
Servo Rservo;
Servo Uservo;
Servo Dservo;
                     
void ActR2();           //右面旋转180度     
void ActRp();           //右面顺时针旋转90度
void ActR();            //右面逆时针旋转90度
void ActL2();           //左面旋转180度     
void ActLp();           //左面顺时针旋转90度
void ActL();            //左面逆时针旋转90度
void ActU2();           //上面旋转180度     
void ActUp();           //上面顺时针旋转90度
void ActU();            //上面逆时针旋转90度
void ActD2();           //下面旋转180度     
void ActDp();           //下面顺时针旋转90度
void ActD();            //下面逆时针旋转90度
void ActF2();           //前面旋转180度     
void ActFp();           //前面顺时针旋转90度
void ActF();            //前面逆时针旋转90度
void ActB2();           //后面旋转180度     
void ActBp();           //后面顺时针旋转90度
void ActB();            //后面逆时针旋转90度
void CLOSE();           //全部合住
void OPEN();            //全部打开
void IN();              //送入魔方
void OUT();             //送出魔方
                        
void TuneFArm90a();     //调试前
void TuneFArm90b();
void TuneFArm180a();

void TuneBArm90a();    //调试后
void TuneBArm90b();  
void TuneBArm180a();  

void TuneLArm90a();     //调试左
void TuneLArm90b();
void TuneLArm180a();

void TuneRArm90a();    //调试右
void TuneRArm90b(); 
void TuneRArm180a();  

void TuneUArm90a();     //调试上
void TuneUArm90b();
void TuneUArm180a();

void TuneDArm90a();    //调试下
void TuneDArm90b();  
void TuneDArm180a();  


unsigned char solve();  //解魔方主函数
void START();         //开始送到魔方位置
void FILSH();         //结束回到初始位置

char buf[256];//串口接收缓存

void setup() {
  Serial.begin(9600);
  pinMode(STEPPIN_F, OUTPUT);
  pinMode(DIRPIN_F, OUTPUT);
  pinMode(STEPPIN_B, OUTPUT);
  pinMode(DIRPIN_B, OUTPUT);
  pinMode(STEPPIN_L, OUTPUT);
  pinMode(DIRPIN_L, OUTPUT);
  pinMode(STEPPIN_R, OUTPUT);
  pinMode(DIRPIN_R, OUTPUT);
  pinMode(STEPPIN_U, OUTPUT);
  pinMode(DIRPIN_U, OUTPUT);
  pinMode(STEPPIN_D, OUTPUT);
  pinMode(DIRPIN_D, OUTPUT);
  pinMode(STEPPIN_T, OUTPUT);
  pinMode(DIRPIN_T, OUTPUT);
  Fservo.attach(F_servo);
  Bservo.attach(B_servo);
  Lservo.attach(L_servo);
  Rservo.attach(R_servo);
  Uservo.attach(U_servo);
  Dservo.attach(D_servo);
  Fservo.write(0);
  Bservo.write(180);
  Lservo.write(0);
  Rservo.write(180);
  Uservo.write(80);
  Dservo.write(180);
}

void loop() {
  Serial.println("power on");
  while(1)
  {
    for(int i=0; i<256; i++)
    {
      buf[i] = 0;
    }
    if(Serial.available()) 
    {
          int n = Serial.readBytesUntil('\n', buf, 256);  
    }
    if(solve() == 0)
    {
      Serial.println("finish \n");
      break;
    }   
    delay(1000);
  }
//   OPEN();
   while(1);
}


////////////////////////////////

void CLOSE()
{
  Uservo.write(U_SERVO_CLOSE);
  Dservo.write(D_SERVO_CLOSE); 
  Fservo.write(F_SERVO_CLOSE);
  Bservo.write(B_SERVO_CLOSE);  
  Lservo.write(L_SERVO_CLOSE);
  Rservo.write(R_SERVO_CLOSE);      
}
void OPEN()
{
  Uservo.write(U_SERVO_OPEN);
  Dservo.write(D_SERVO_OPEN); 
  Fservo.write(F_SERVO_OPEN);
  Bservo.write(B_SERVO_OPEN);  
  Lservo.write(L_SERVO_OPEN);
  Rservo.write(R_SERVO_OPEN);      
}
void START()
{
  IN();
  delay(500);
  Uservo.write(U_SERVO_CLOSE);
  delay(500);
  Dservo.write(D_SERVO_CLOSE);
  delay(500); 
  Fservo.write(F_SERVO_CLOSE);
  Bservo.write(B_SERVO_CLOSE); 
  delay(500); 
  Lservo.write(L_SERVO_CLOSE);
  Rservo.write(R_SERVO_CLOSE);  
  delay(1000);   
}
void FILSH()
{
  IN();
  delay(500);
  Fservo.write(F_SERVO_OPEN);
  Bservo.write(B_SERVO_OPEN); 
  Lservo.write(L_SERVO_OPEN);
  Rservo.write(R_SERVO_OPEN);  
  Uservo.write(U_SERVO_OPEN);
  delay(500);
  Dservo.write(D_SERVO_OPEN);
  delay(500);  
  OUT();   
}
void ActR2()
{
CLOSE();
TuneRArm180a();  
  delay(DELAY);   
}

void ActRp()
{
  CLOSE();
  TuneRArm90b(); 
  delay(DELAY);  
}

void ActR()
{
  CLOSE();
  TuneRArm90a(); 
  delay(DELAY); 
}

void ActL2()
{
  CLOSE();
  TuneLArm180a(); 
  delay(DELAY);   
}

void ActLp()
{
 CLOSE();
 TuneLArm90b(); 
  delay(DELAY);   
}

void ActL()
{
  CLOSE();
 TuneLArm90a(); 
  delay(DELAY);  
}

void ActU2()
{
  CLOSE();
  TuneUArm180a(); 
  delay(DELAY);  
}

void ActUp()
{
  CLOSE();
 TuneUArm90b(); 
  delay(DELAY);  
}

void ActU()
{
  CLOSE();
 TuneUArm90a(); 
  delay(DELAY);  
}

void ActD2()
{
  CLOSE();
  TuneDArm180a(); 
  delay(DELAY);
}

void ActDp()
{
  CLOSE();
  TuneDArm90b(); 
  delay(DELAY);
}

void ActD()
{
  CLOSE();
  TuneDArm90a(); 
  delay(DELAY);
}

void ActF2()
{
  CLOSE();
TuneFArm180a(); 
  delay(DELAY);   
}

void ActFp()
{
  CLOSE();
TuneFArm90b(); 
  delay(DELAY);     
}

void ActF()
{
  CLOSE();
TuneFArm90a(); 
  delay(DELAY);   
}

void ActB2()
{
  CLOSE();
TuneBArm180a(); 
  delay(DELAY);
}

void ActBp()
{
  CLOSE();
TuneBArm90b(); 
  delay(DELAY);
}

void ActB()
{
  CLOSE();
TuneBArm90a(); 
  delay(DELAY);
}

unsigned char solve()
{
  int i;
  i = 0;
 if(buf[0] !=0)
 {
    Serial.println("start");

    delay(DELAY);
    i = 0;
    while (buf[i] != 0)
    {
      switch(buf[i])
      {
      case 'R':
        if (buf[i+1] == '2')
        {
          Serial.println("R2");
          ActR2();
          i+=2;
        }
        else if (buf[i+1] == '1')
        {
          Serial.println("R'");
          ActRp();
          i+=2;
        }
        else if (buf[i+1] == '0')
        {
          Serial.println("R");
          ActR();
          i+=2;
        }
        else
        {
          Serial.println("error");
          return 1;
        }
        break;
        
      case 'L':
        if (buf[i+1] == '2')
        {
          Serial.println("L2");
          ActL2();
          i+=2;
        }
        else if (buf[i+1] =='1')
        {
          Serial.println("L'");
          ActLp();
          i+=2;
        }
        else if (buf[i+1] == '0')
        {
          Serial.println("L");
          ActL();
          i+=2;
        }
        else
        {
          Serial.println("error");
          return 1;
        }
        break;

      case 'U':
        if (buf[i+1] == '2')
        {
          Serial.println("U2");
          ActU2();
          i+=2;
        }
        else if (buf[i+1] == '1')
        {
          Serial.println("U'");
          ActUp();
          i+=2;
        }
        else if (buf[i+1] == '0')
        {
          Serial.println("U");
          ActU();
          i+=2;
        }
        else
        {
          Serial.println("error");
          return 1 ;
        }
        break;

      case 'D':
        if (buf[i+1] == '2')
        {
          Serial.println("D2");
          ActD2();
          i+=2;
        }
        else if (buf[i+1] == '1')
        {
          Serial.println("D'");
          ActDp();
          i+=2;
        }
        else if (buf[i+1] == '0')
        {
          Serial.println("D");
          ActD();
          i+=2;
        }
        else
        {
          Serial.println("error");
          return 1;
        }
        break;

      case 'F':
        if (buf[i+1] == '2')
        {
          Serial.println("F2");
          ActF2();
          i+=2;
        }
        else if (buf[i+1] == '1')
        {
          Serial.println("F'");
          ActFp();
          i+=2;
        }
        else if (buf[i+1] == '0')
        {
          Serial.println("F");
          ActF();
          i+=2;
        }
        else
        {
          Serial.println("error");
          return 1;
        }
        break;

      case 'B':
        if (buf[i+1] == '2')
        {
          Serial.println("B2");
          ActB2();
          i+=2;
        }
        else if (buf[i+1] == '1')
        {
          Serial.println("B'");
          ActBp();
          i+=2;
        }
        else if (buf[i+1] == '0')
        {
          Serial.println("B");
          ActB();
          i+=2;
        }
        else
        {
          Serial.println("error");
          return 1;
        }
        break;
        case 'C':
        if (buf[i] == 'C')
        {
          Serial.println("START");
          START();
          i+=1;
        }
        else
        {
          Serial.println("error");
          return 1;
        }
        break;
        case 'O':
        if (buf[i] == 'O')
        {
          Serial.println("FILSH");
          FILSH();
          i+=1;
        }
        else
        {
          Serial.println("error");
          return 1;
        }
        break;
        
      default:
        Serial.println("error or end");
        return 0;
        break;
      }
    }
  
  } else if(buf[0] == 0)
  {
    Serial.println("cube");
    return 1;
  }
  else 
  {
    Serial.println("error!");
  }
}
void TuneFArm90b()//调试左臂
{
digitalWrite(DIRPIN_F, HIGH);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_F, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_F, LOW);
    delayMicroseconds(DELAY1);
  }
  //STEPPIN_LEFT(HIGH,DELAY10);
}
void TuneFArm90a()//调试左臂
{
digitalWrite(DIRPIN_F, LOW);
  // 反向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_F, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_F, LOW);
    delayMicroseconds(DELAY1);
  }
    //STEPPIN_LEFT(LOW,DELAY10);
}

void TuneFArm180a()//调试左臂
{
digitalWrite(DIRPIN_F, LOW);
  // 正向转1圈（200脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_F, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_F, LOW);
    delayMicroseconds(DELAY1);
      //STEPPIN_LEFT(LOW,800);
  }
}
///
void TuneBArm90b()//调试左臂
{
digitalWrite(DIRPIN_B, HIGH);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_B, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_B, LOW);
    delayMicroseconds(DELAY1);
  }
  //STEPPIN_LEFT(HIGH,DELAY10);
}
void TuneBArm90a()//调试左臂
{
digitalWrite(DIRPIN_B, LOW);
  // 反向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_B, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_B, LOW);
    delayMicroseconds(DELAY1);
  }
    //STEPPIN_LEFT(LOW,DELAY10);
}

void TuneBArm180a()//调试左臂
{
digitalWrite(DIRPIN_B, LOW);
  // 正向转1圈（200脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_B, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_B, LOW);
    delayMicroseconds(DELAY1);
      //STEPPIN_LEFT(LOW,800);
  }
}
///
void TuneLArm90b()//调试左臂
{
digitalWrite(DIRPIN_L, HIGH);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_L, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_L, LOW);
    delayMicroseconds(DELAY1);
  }
}
void TuneLArm90a()//调试左臂
{
digitalWrite(DIRPIN_L, LOW);
  // 反向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_L, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_L, LOW);
    delayMicroseconds(DELAY1);
  }
}

void TuneLArm180a()//调试左臂
{
digitalWrite(DIRPIN_L, LOW);
  // 正向转1圈（200脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_L, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_L, LOW);
    delayMicroseconds(DELAY1);
  }
}
void TuneRArm90b()//调试右臂
{
digitalWrite(DIRPIN_R, HIGH);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_R, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_R, LOW);
    delayMicroseconds(DELAY1);
  }
}
void TuneRArm90a()
{
digitalWrite(DIRPIN_R, LOW);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_R, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_R, LOW);
    delayMicroseconds(DELAY1);
  }
}

void TuneRArm180a()
{
digitalWrite(DIRPIN_R, LOW);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_R, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_R, LOW);
    delayMicroseconds(DELAY1);
  }
}
void TuneUArm90b()//调试左臂
{
digitalWrite(DIRPIN_U, HIGH);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_U, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_U, LOW);
    delayMicroseconds(DELAY1);
  }
}
void TuneUArm90a()//调试左臂
{
digitalWrite(DIRPIN_U, LOW);
  // 反向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_U, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_U, LOW);
    delayMicroseconds(DELAY1);
  }
}

void TuneUArm180a()//调试左臂
{
digitalWrite(DIRPIN_U,LOW);
  // 正向转1圈（200脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_U, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_U, LOW);
    delayMicroseconds(DELAY1);
  }
}
void TuneDArm90b()//调试左臂
{
digitalWrite(DIRPIN_D, HIGH);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_D, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_D, LOW);
    delayMicroseconds(DELAY1);
  }
}
void TuneDArm90a()//调试左臂
{
digitalWrite(DIRPIN_D, LOW);
  // 反向转0.5圈（100脉冲）
  for (int x = 0; x < 800; x ++) {
    digitalWrite(STEPPIN_D, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_D, LOW);
    delayMicroseconds(DELAY1);
  }
}

void TuneDArm180a()//调试左臂
{
 digitalWrite(DIRPIN_D, LOW);
  // 正向转1圈（200脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_D, HIGH);
    delayMicroseconds(DELAY1);
    digitalWrite(STEPPIN_D, LOW);
    delayMicroseconds(DELAY1);
  }
}
void IN()//调试T
{
digitalWrite(DIRPIN_T, HIGH);
  // 正向转0.5圈（100脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_T, HIGH);
    delayMicroseconds(50);
    digitalWrite(STEPPIN_T, LOW);
    delayMicroseconds(50);
  }
}
void OUT()//调试T
{
digitalWrite(DIRPIN_T, LOW);
  // 反向转0.5圈（100脉冲）
  for (int x = 0; x < 1600; x ++) {
    digitalWrite(STEPPIN_T, HIGH);
    delayMicroseconds(50);
    digitalWrite(STEPPIN_T, LOW);
    delayMicroseconds(50);
  }
}