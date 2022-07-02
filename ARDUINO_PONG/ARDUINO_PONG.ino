#define RACKET_WIDTH 2
#define RACKET_HIGH 10
#define RACKET_MOVE_SPEED 1
#define RACKET_START_PONT_X 15
#define RACKET_START_PONT_Y 20

#define BALL_RADIUS 2
#define BALL_START_POINT_X 64
#define BALL_START_POINT_Y 32
#define BALL_SPEED_MODULE_X 3
#define BALL_SPEED_MODULE_Y 2


#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define FPS 30

// Библиотека дисплея
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

int xStartPlayer, yStartPlayer, xEndPlayer, yEndPlayer, ballSpeedX, ballSpeedY = 0;
int yPlayerNow = RACKET_START_PONT_Y;
uint64_t gameTimer = 0;

void setup() {
  oled.init();        // инициализация
  oled.clear();       // очистка
  oled.rect(RACKET_START_PONT_X, RACKET_START_PONT_Y, RACKET_START_PONT_X + RACKET_WIDTH, RACKET_START_PONT_Y + RACKET_HIGH, OLED_FILL);
  
  ballSpeedX = BALL_SPEED_MODULE_X;
  ballSpeedY = BALL_SPEED_MODULE_Y;
  oled.circle(BALL_START_POINT_X, BALL_START_POINT_Y, BALL_RADIUS, OLED_FILL);
  
  gameTimer = millis();
}



void loop() {

  // Ограничение частоты кадров
  if (millis() - gameTimer >= 1000 / FPS) {
    gameTimer = millis();

    // Управление ракеткой
    if (digitalRead(BUTTON_UP) && yPlayerNow > 0) {
      
      xStartPlayer = RACKET_START_PONT_X;
      yStartPlayer = yPlayerNow ;
      xEndPlayer = RACKET_START_PONT_X + RACKET_WIDTH;
      yEndPlayer = yPlayerNow + RACKET_HIGH;
      
      oled.rect(xStartPlayer, yStartPlayer, xEndPlayer, yEndPlayer, OLED_CLEAR);
      yPlayerNow -= RACKET_MOVE_SPEED;
      xStartPlayer = RACKET_START_PONT_X;
      yStartPlayer = yPlayerNow ;
      xEndPlayer = RACKET_START_PONT_X + RACKET_WIDTH;
      yEndPlayer = yPlayerNow + RACKET_HIGH;      
      
      oled.rect(xStartPlayer, yStartPlayer, xEndPlayer, yEndPlayer, OLED_FILL);

    } else if (digitalRead(BUTTON_DOWN) && yPlayerNow < 63 - RACKET_HIGH) {

      xStartPlayer = RACKET_START_PONT_X;
      yStartPlayer = yPlayerNow ;
      xEndPlayer = RACKET_START_PONT_X + RACKET_WIDTH;
      yEndPlayer = yPlayerNow + RACKET_HIGH;
      
      oled.rect(xStartPlayer, yStartPlayer, xEndPlayer, yEndPlayer, OLED_CLEAR);
      yPlayerNow += RACKET_MOVE_SPEED;
      xStartPlayer = RACKET_START_PONT_X;
      yStartPlayer = yPlayerNow ;
      xEndPlayer = RACKET_START_PONT_X + RACKET_WIDTH;
      yEndPlayer = yPlayerNow + RACKET_HIGH;      
      
      oled.rect(xStartPlayer, yStartPlayer, xEndPlayer, yEndPlayer, OLED_FILL);

    }
    // Расчёт физики полёта мяча
    
  }
}
