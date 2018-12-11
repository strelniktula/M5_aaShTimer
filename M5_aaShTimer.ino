#include <driver/adc.h>
#include <M5Stack.h>

byte sh1 = 0;
int shnum = 0; /// число выстрелов
float ShootTime = 0; /// время выстрела
float G;
int th = 0; /// задержка до старта
boolean start = false; /// старт
//boolean st_time = false;
//float lastshoot = 0;
//float fshoot = 0;
//int shootcount =0;
float FireonLed;


//int delay=0;
//boolean pt=true;

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  displ(ShootTime);
  shoot1(0);
  shN(0);
  G = millis();

  pinMode(22, INPUT_PULLUP); /// порт звукового датчика
  pinMode(21, OUTPUT); /// порт светодиода

  digitalWrite(21,LOW);

  M5.Lcd.setTextFont(1); M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Lcd.setCursor( 16, 10); M5.Lcd.print("- ActionAir Shot Timer -");
  M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Lcd.setCursor( 35, 215); M5.Lcd.print("START");
  M5.Lcd.setCursor( 230, 215); M5.Lcd.print("Reset");
  //M5.Lcd.setCursor( 130, 215); M5.Lcd.print("Shoot");
  M5.Lcd.setCursor( 115, 215); M5.Lcd.print("Delay:"); M5.Lcd.print(th / 10 % 10); M5.Lcd.print(th % 10);

  M5.Lcd.setTextFont(2); M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 25, 50); M5.Lcd.print("1'S");
  M5.Lcd.setCursor( 185, 50); M5.Lcd.print("Sht");

  M5.Lcd.drawRoundRect(10, 45, 300, 160, 10, TFT_WHITE);
  M5.Lcd.drawRoundRect(6, 41, 308, 168, 12, TFT_WHITE);
  M5.Lcd.drawLine(20, 85, 300, 85, TFT_YELLOW);

}

void loop() {

  if (M5.BtnA.wasPressed() && !start) {
    ShootTime = 0;
    sh1 = 0;
    shnum = 0; shN(shnum);
    G = millis();
    displ(ShootTime);
    shoot1(0);
    countdown(th);
    M5.Speaker.tone(1500, 300);
    //delay(300);
    start = true;
  };

  if (M5.BtnB.wasPressed() && !start) {
    th++;
    if (th > 10) {
      th = 0;
    };
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextFont(1); M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor( 115, 215); M5.Lcd.print("Delay:"); M5.Lcd.print(th / 10 % 10); M5.Lcd.print(th % 10);
  }


  if (M5.BtnC.wasPressed()) {
    ShootTime = 0;
    shoot1(0);
    shnum = 0; shN(shnum);
    G = millis();
    displ(ShootTime);
    start = false;
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextFont(1); M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor( 115, 215); M5.Lcd.print("Delay:"); M5.Lcd.print(th / 10 % 10); M5.Lcd.print(th % 10);
  };

  if (digitalRead(22) == HIGH && start) {
    ShootTime = millis() - G;
    FireonLed=millis(); digitalWrite(21,HIGH); 
    shnum++;
    shN(shnum);
    displ(ShootTime);
    if (sh1 == 0) {
      shoot1(ShootTime);
      sh1 = 1;
    }
    delay(50);
  }

  if (millis()-FireonLed > 1000) {
    digitalWrite(21,LOW); 
    }
    
  M5.update();
}

void displ(long ti) {

  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Lcd.setTextFont(7);

  int x = 25; int d = 65; int y = 100;
  long time = ti; //millis();
  int sec1 = time / 1000 % 10;
  int sec2 = time / 10000 % 10;
  int sec3 = time / 100000 % 10;
  int dec1 = time % 1000 / 100;
  int dec2 = time % 100 / 10;

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( x, y); M5.Lcd.print(sec3);
  M5.Lcd.setCursor( x + d, y); M5.Lcd.print(sec2);
  M5.Lcd.setCursor( x + 2 * d, y); M5.Lcd.print(sec1);
  //M5.Lcd.setCursor( x+3*d, y); M5.Lcd.print(":");
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor( 10 + x + 3 * d, y); M5.Lcd.print(dec1);
  M5.Lcd.setCursor( 15 + x + 4 * d - d / 2, y); M5.Lcd.print(dec2);
}

void shoot1(long ti) {

  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Lcd.setTextFont(2);

  //int x = 210; int d = 15; int y = 14;
  int x = 75; int d = 15; int y = 50;
  long time = ti; //millis();
  int sec1 = time / 1000 % 10;
  int sec2 = time / 10000 % 10;
  int sec3 = time / 100000 % 10;
  int dec1 = time % 1000 / 100;
  int dec2 = time % 100 / 10;

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( x, y); M5.Lcd.print(sec3);
  M5.Lcd.setCursor( x + d, y); M5.Lcd.print(sec2);
  M5.Lcd.setCursor( x + 2 * d, y); M5.Lcd.print(sec1);
  M5.Lcd.setCursor( 6 + x + 3 * d, y); M5.Lcd.print("'");
  M5.Lcd.setCursor( x + 4 * d, y); M5.Lcd.print(dec1);
  M5.Lcd.setCursor( x + 5 * d, y); M5.Lcd.print(dec2);
}

void shN(int s) {

  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Lcd.setTextFont(2);

  int x = 240; int d = 15; int y = 50;
  //long time=ti;//millis();
  int sec1 = s / 1 % 10;
  int sec2 = s / 10 % 10;
  int sec3 = s / 100 % 10;
  //  int dec1=time%1000/100;
  //  int dec2=time%100/10;

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( x - d / 3, y); M5.Lcd.print("#");
  M5.Lcd.setCursor( x + d, y); M5.Lcd.print(sec3);
  M5.Lcd.setCursor( x + 2 * d, y); M5.Lcd.print(sec2);
  M5.Lcd.setCursor( x + 3 * d, y); M5.Lcd.print(sec1);
  //  M5.Lcd.setCursor( x+4*d, y); M5.Lcd.print(dec1);
  //  M5.Lcd.setCursor( x+5*d, y); M5.Lcd.print(dec2);
}

void countdown(int cd) {
  float lasttimecheck = millis();
  float timeinterval = 1000;
  int timecd = 0;
  int dl = 0;

  while (cd > timecd) {
    if (millis() > lasttimecheck + timeinterval) {
      lasttimecheck = millis();
      timecd++;
      dl = cd - timecd;
      M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
      M5.Lcd.setTextFont(1); M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor( 115, 215); M5.Lcd.print("Delay:"); M5.Lcd.print(dl / 10 % 10); M5.Lcd.print(dl % 10);
    }
  }
  M5.Lcd.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Lcd.setTextFont(1); M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor( 115, 215); M5.Lcd.print("Delay:"); M5.Lcd.print(dl / 10 % 10); M5.Lcd.print(dl % 10);
}
