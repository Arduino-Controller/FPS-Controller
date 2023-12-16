#include <Mouse.h>
#include <Wire.h>
#include <Keyboard.h>

/*as
 SDA 2번 Pin, SCL 3번 Pin
 Int 7번 Pdw 박아야됨.
*/

#define MPU6050_INT_PIN 7  // 레오나르도에서는 무조건 박아주자
#define MPU6050_INT digitalPinToInterrupt(MPU6050_INT_PIN)

int xval, yval;
const int MPU_addr = 0x68;  // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();  //키보드 통신 시작

  //자이로스코프 코드
  Serial.println("start");

  Serial.print(MPU6050_INT);
  Serial.print(" on pin ");
  Serial.print(MPU6050_INT_PIN);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  pinMode(10, INPUT);  // 좌클릭 버튼

  Mouse.begin();
  pinMode(MPU6050_INT, INPUT);  // 자이로스코프 값 입력모드
  pinMode(9, INPUT_PULLUP);     // Z를 입력모드로
  pinMode(11, INPUT);  // 장전 버튼
  pinMode(A4, OUTPUT); //진동센서 A4핀

}

void loop() {
  
  //조이스틱 기능
  int x = analogRead(A0);  // 조이스틱 X축의 아날로그 신호를 x에 저장
  int y = analogRead(A1);  // 조이스틱 Y축의 아날로그 신호를 y에 저장
  int z = analogRead(9);

  //Joystick_zoom(x,y,z);

  //마우스 우클릭
  if (z < 50) {
    Mouse.click(MOUSE_RIGHT);
    delay(500);
  }

  //마우스 휠 이동
  if (200 < y && y < 1000) {
    Mouse.move(0, 0, 0);
  } else if (y >= 1000) {
    Mouse.move(0, 0, y);
  } else {
    Mouse.move(0, 0, 1);
  }





  //마우스 이동 기능
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  // 여기 위까지는 코드 건들지 않는 걸 추천. 여기 아래부터 수정 ㄱㄱ

  int lb = digitalRead(10);  // 1이면 누른 상태, 0이면 안 누른 상태임.

  float gyroY, gyroZ;
  int sens = 1500;
  gyroZ = GyZ / sens;
  gyroY = -GyY / sens;

  if (lb == 1)      // Leftsa button이 1이라는건 좌클릭을 하고 있다는 상태이므로
  {                 // 마우스를 누른 상태로 유지시켜주는 Mouse.press()를 사용함.
    Mouse.press();  // 좌클릭 한 상태 유지
    analogWrite(A4, 255); //진동세기 최대로!(변경가능)
    delay(100);
  }
  if (lb == 0) {
    Mouse.release();  //클릭 상태 해제
    analogWrite(A4, 0); //버튼 안눌리면 진동 없음
  }

  //Xiroscope(gyroY, gyroZ, lb);
  Mouse.move(gyroZ*8, gyroY*6);  // 마우스를 움직이는 함수





  //키보드 입력 기능
  xval = analogRead(A2);
  yval = analogRead(A3);
  Joystick_keyboard(xval,yval);

  if(xval>=800){Keyboard.press('w');}//버튼 입력
  else{Keyboard.release('w');}//버튼 입력 해제

  if(xval<200){Keyboard.press('s');}
  else{Keyboard.release('s');}

  if(yval<200){Keyboard.press('a');}
  else{Keyboard.release('a');}

  if(yval>=800){Keyboard.press('d');}
  else{Keyboard.release('d');}
  



  //장전 기능
  int r = digitalRead(11);
  //Button_R(r);
  if(r==1){
    
    Keyboard.press('r');
  }
  else{
    Keyboard.release('r');
  }



}

void Xiroscope(int gyroY, int gyroZ, int lb)  // 자이로, 버튼 값 확인용 시리얼 프린트 함수
{
  Serial.println("자이로스코프");
  Serial.print("X축: ");
  Serial.print(gyroZ);
  Serial.print(" // Y축: ");
  Serial.print(-gyroY);
  Serial.print(" // 좌 클릭: ");
  Serial.println(lb);
}

void Button_R(int r)  // 자이로, 버튼 값 확인용 시리얼 프린트 함수
{
  Serial.println("R 버튼");
  Serial.print("R버튼: ");
  Serial.println(r);
}

void Joystick_keyboard(int xval, int yval){
    Serial.println("키보드 조이스틱");
    Serial.print("X축: ");
    Serial.print(xval);
    Serial.print("  Y축: ");
    Serial.println(yval);
}

void Joystick_zoom(int x,int y,int z){
    
  Serial.println("줌 조이스틱");
  Serial.print("X: ");
  Serial.print(x);  //시리얼 모니터에 'X: x'를 표기
  Serial.print("  Y: ");
  Serial.print(y);  //시리얼 모니터에 'Y: y'를 표기
  Serial.print("  Z: ");
  Serial.println(z);  //시리얼 모니터에 'Z: z'를 표기
  
}
