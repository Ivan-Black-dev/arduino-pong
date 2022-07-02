#define RACKET_WIDTH 2
#define RACKET_HIGH 15
#define RACKET_MOVE_SPEED 1
#define RACKET_START_PONT_X 15
#define RACKET_START_PONT_Y 20

#define ENEMY_WIDTH 2
#define ENEMY_HIGH 15
#define ENEMY_MOVE_SPEED 1
#define ENEMY_START_PONT_X 110
#define ENEMY_START_PONT_Y 20

#define BALL_RADIUS 2
#define BALL_START_POINT_X 64
#define BALL_START_POINT_Y 32
#define BALL_SPEED_MODULE_X 1
#define BALL_SPEED_MODULE_Y 1



#define BUTTON_UP 2
#define BUTTON_DOWN 3

#define FPS 30
#define GOAL_DELAY 1000

// Библиотека дисплея
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

byte playerScore = 0, enemyScore = 0;

byte xStartPlayer = 0, yStartPlayer = 0, xEndPlayer = 0, yEndPlayer = 0;
byte yPlayerNow = RACKET_START_PONT_Y;

byte xStartEnemy = 0, yStartEnemy = 0, xEndEnemy = 0, yEndEnemy = 0;
byte yEnemyNow = ENEMY_START_PONT_Y;

byte ballSpeedX, ballSpeedY, ballNowX, ballNowY = 0;
uint64_t gameTimer = 0;
int fps = FPS;


void updateScore() {
  if (playerScore > 5 || enemyScore > 5){
      ballSpeedX = 2;
    }else if (playerScore > 15 || enemyScore > 15){
      ballSpeedX = 3;
    }
  oled.home();
  oled.print(playerScore);
  oled.setCursor(115, 0);
  oled.print(enemyScore);
}


void resetBall() {
  oled.rect(ballNowX - BALL_RADIUS, ballNowY + BALL_RADIUS, ballNowX + BALL_RADIUS, ballNowY - BALL_RADIUS, OLED_CLEAR);
  ballNowX = BALL_START_POINT_X;
  ballNowY = BALL_START_POINT_Y;
  delay(GOAL_DELAY);
}

void enemyMoveUp() {
  if (yEnemyNow > 0) {
    xStartEnemy = ENEMY_START_PONT_X;
    yStartEnemy = yEnemyNow;
    xEndEnemy = ENEMY_START_PONT_X + ENEMY_WIDTH;
    yEndPlayer = yEnemyNow + ENEMY_HIGH;

    oled.rect(xStartEnemy, yStartEnemy, xEndEnemy, yEndEnemy, OLED_CLEAR);

    yEnemyNow -= ENEMY_MOVE_SPEED;
    xStartEnemy = ENEMY_START_PONT_X;
    yStartEnemy = yEnemyNow;
    xEndEnemy = ENEMY_START_PONT_X + ENEMY_WIDTH;
    yEndEnemy = yEnemyNow + ENEMY_HIGH;

    oled.rect(xStartEnemy, yStartEnemy, xEndEnemy, yEndEnemy, OLED_FILL);
  }
}

void enemyMoveDown() {
  if (yEnemyNow < 63 - ENEMY_HIGH) {
    xStartEnemy = ENEMY_START_PONT_X;
    yStartEnemy = yEnemyNow;
    xEndEnemy = ENEMY_START_PONT_X + ENEMY_WIDTH;
    yEndPlayer = yEnemyNow + ENEMY_HIGH;

    oled.rect(xStartEnemy, yStartEnemy, xEndEnemy, yEndEnemy, OLED_CLEAR);

    yEnemyNow += ENEMY_MOVE_SPEED;
    xStartEnemy = ENEMY_START_PONT_X;
    yStartEnemy = yEnemyNow;
    xEndEnemy = ENEMY_START_PONT_X + ENEMY_WIDTH;
    yEndEnemy = yEnemyNow + ENEMY_HIGH;

    oled.rect(xStartEnemy, yStartEnemy, xEndEnemy, yEndEnemy, OLED_FILL);
  }
}

void setup() {
  oled.init();
  oled.clear();

  // Иницилизация счёта
  updateScore();

  // Иницилизация игрока
  oled.rect(RACKET_START_PONT_X, RACKET_START_PONT_Y, RACKET_START_PONT_X + RACKET_WIDTH, RACKET_START_PONT_Y + RACKET_HIGH, OLED_FILL);

  // Иницилизация противника
  oled.rect(ENEMY_START_PONT_X, ENEMY_START_PONT_Y, ENEMY_START_PONT_X + ENEMY_WIDTH, ENEMY_START_PONT_Y + ENEMY_HIGH, OLED_FILL);

  // Иницилизация мячика
  ballSpeedX = BALL_SPEED_MODULE_X;
  ballSpeedY = BALL_SPEED_MODULE_Y;
  ballNowX = BALL_START_POINT_X;
  ballNowY = BALL_START_POINT_Y;
  oled.circle(ballNowX, ballNowY, BALL_RADIUS, OLED_FILL);

  gameTimer = millis();
}


void loop() {

  // Ограничение частоты кадров
  if (millis() - gameTimer >= 1000 / fps) {
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
    if (ballNowY >= 63) {
      ballSpeedY = -ballSpeedY;
    }
    if (ballNowY <= 0) {
      ballSpeedY = -ballSpeedY;
    }
    if (ballNowX >= ENEMY_START_PONT_X - BALL_RADIUS - 4) {
      // Проверка на забитие гола
      if ((ballNowY + BALL_RADIUS > yEnemyNow + ENEMY_HIGH - 2) || (ballNowY < yEnemyNow - 2)) {
        playerScore++;
        updateScore();
        resetBall();
      }
      ballSpeedX = -ballSpeedX;
    }
    if (ballNowX <= RACKET_START_PONT_X + RACKET_WIDTH + BALL_RADIUS + 4) {
      // Проверка на забитие гола
      if ( (ballNowY > yPlayerNow + RACKET_HIGH + 2) || (ballNowY < yPlayerNow - 2)) {
        enemyScore++;
        updateScore();
        resetBall();
      }
      ballSpeedX = -ballSpeedX;
    }

    // Вычесления противника
    if (ballNowY < yEnemyNow) {
      enemyMoveUp();
    }
    if (ballNowY > yEnemyNow + ENEMY_HIGH/2) {
      enemyMoveDown();
    }



    // Отрисовка мячика
    oled.rect(ballNowX - BALL_RADIUS, ballNowY + BALL_RADIUS, ballNowX + BALL_RADIUS, ballNowY - BALL_RADIUS, OLED_CLEAR);
    ballNowX += ballSpeedX;
    ballNowY += ballSpeedY;
    oled.circle(ballNowX, ballNowY, BALL_RADIUS, OLED_FILL);




  }
}
