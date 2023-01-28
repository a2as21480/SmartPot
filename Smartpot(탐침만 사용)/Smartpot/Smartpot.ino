#include "src\SmartPot.h"
#include "src\Soil_Moisture.h" //cpp파일에서도 헤더를 include해야하는데, 아두이노 컴파일러는 상대 경로를 못 읽는 듯,(아두이노는 gui 레벨에서 못 건드리게 막아둠) 
Soil_Moisture Moi(A0);

#include "DHT.h"
DHT dht(A1, DHT11);

#include <SoftwareSerial.h>
#define RXD 11 //RXD에 연결(모듈의 수신부)
#define TXD 10 //TXD에 연결(모듈의 송신부)
SoftwareSerial BT(TXD,RXD);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define pump 8
int n = 0;

enum LED {
    LED_R = 5,
    LED_G,
    LED_B
};


void setup() {
    Serial.begin(9600);
    BT.begin(9600);
    dht.begin();

    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Hello, Arduino");
    lcd.setCursor(0,1);
    lcd.print("Smart Pot");
    delay(3000);
    lcd.clear();

    //핀 준비
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(pump, OUTPUT);
}

void loop() {
    //센서값 읽기
    int moisture = Moi.read();
    int humi = dht.readHumidity();
    int temper = dht.readTemperature();
    
    String info = "Soil Moisture:" + String(moisture) + ", H:" + String(humi) + " ,T:" + String(temper) + "  ";
    int len = info.length();

    //센서값 안내
    Serial.println(info);
    BT.println(info);

    lcd.home();
    lcd.print("Arduino SmartPot");
    lcd.setCursor(0,1);
    for(int i=0; i<16; i++) {
        lcd.print(info.charAt( (i+n)%len) );
    }
    n+=1; //num을 하나 증가
    n%=len; //num을 문자열의 길이로 나눈 나머지를 num에 대입
    delay(500);


    //화분 건조 상태 판단
    if(moisture < 50) {
        //화분이 건조한 경우
        led(LED_R); //LED RED
        lcd.clear();
        Serial.println("Drying");
        BT.println("Drying");
        lcd.home();
        lcd.print("Drying          ");
        delay(1500);

        //펌프 작동
        led(LED_B);
        Serial.println("Pumping");
        BT.println("Pumping");
        lcd.home();
        lcd.print("Pumping         ");
        digitalWrite(pump, HIGH);
        delay(3000);
        digitalWrite(pump, LOW);
    }
    else led(LED_G);

    //그냥 안내만 하는거면 LCD 스크롤은 while 부분을 뺀다음 함수로 만들어서 넣으면, 물론 n은 전역으로 선언해서
    //시리얼로 센서값 안내, LCD 첫 줄은 스마트 팟, 둘째줄은 LCD 스크롤 안내
    //평소에는 LED 그린
    //물 부족 감지하면 LED 레드
    //모터 작동하는 동안은 LED 블루
}
