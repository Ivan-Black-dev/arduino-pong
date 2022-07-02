#define RACKET_WIDTH 2
#define RACKET_HIGH 10
#define RACKET_MOVE_SPEED 1
#define RACKET_START_PONT_X 15
#define RACKET_START_PONT_Y 20

#define BALL_RADIUS 2
#define BALL_START_POINT_X 64
#define BALL_START_POINT_Y 32
#define BALL_SPEED_MODULE_X 3
#define BALL_SPEED_MODULE_yRacketNow 2


#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define FPS 30

// Библиотека дисплея
#include <GyRacketNowverOLED.h>
GyRacketNowverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

int xRacketStart,  yRacketNowRacketStart, xEnd, yRacketNowEnd, ballSpeedX, ballSpeedY = 0;
int yRacketNowNow = RACKET_START_PONT_Y;
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
    if (digitalRead(BUTTON_UP) && yRacketNowNow > 0) {

      xRacketStart = RACKET_START_PONT_X;
      yRacketNowRacketStart = yRacketNowNow;
      xEnd = RACKET_START_PONT_X + RACKET_WIDTH;
      yRacketNowEnd = yRacketNowNow + RACKET_HIGH;
      oled.rect(xRacketStart, yRacketNowRacketStart, xEnd, yRacketNowEnd, OLED_CLEAR);
      yRacketNow -= RACKET_MOVE_SPEED;
      xRacketStart = RACKET_START_PONT_X;
      yRacketNowRacketStart = yRacketNow;
      xEnd = RACKET_START_PONT_X + RACKET_WIDTH;
      yRacketNowEnd = yRacketNow + RACKET_HIGH;
      oled.rect(xRacketStart, yRacketNowRacketStart, xEnd, yRacketNowEnd, OLED_FILL);

    } else if (digitalRead(BUTTON_DOWN) && yRacketNow < 63 - RACKET_HIGH) {

      xRacketStart = RACKET_START_PONT_X;
      yRacketNowRacketStart = yRacketNow;
      xEnd = RACKET_START_PONT_X + RACKET_WIDTH;
      yRacketNowEnd = yRacketNow + RACKET_HIGH;
      oled.rect(xRacketStart, yRacketNowRacketStart, xEnd, yRacketNowEnd, OLED_CLEAR);
      yRacketNow += RACKET_MOVE_SPEED;
      xRacketStart = RACKET_START_PONT_X;
      yRacketNowRacketStart = yRacketNow;
      xEnd = RACKET_START_PONT_X + RACKET_WIDTH;
      yRacketNowEnd = yRacketNow + RACKET_HIGH;
      oled.rect(xRacketStart, yRacketNowRacketStart, xEnd, yRacketNowEnd, OLED_FILL);

    }
    // Расчёт физики полёта мяча
    
  }
}
