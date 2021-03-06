#include <SFML/Graphics.hpp>

using namespace sf;

const int H = 17;  //Задаем высоту карты
const int W = 150; //Задаем ширину карты

String TileMap[H] = {
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "00",
    "0                                                                         "
    "                                                                          "
    " 0",
    "0                                                                         "
    "           w                                                              "
    " 0",
    "0                   w                                                     "
    "                                         w                                "
    " 0",
    "0                                      w                                  "
    "                                                                          "
    " 0",
    "0                                                                         "
    "                                                                          "
    " 0",
    "0                                                                         "
    "        w                                                                 "
    " 0",
    "0                                                                       r "
    "                                                                          "
    " 0",
    "0                                                                      rr "
    "                                                         w                "
    " 0",
    "0                                                                     rrr "
    "                                                                          "
    " 0",
    "0                   kckck                                            rrrr "
    "                                                                          "
    " 0",
    "0                                      t0                           rrrrr "
    "                                                                          "
    " 0",
    "0G                                     00              t0          rrrrrr "
    "           G                                                              "
    " 0",
    "0           d    g       d             00              00         rrrrrrr "
    "                                                            G             "
    " 0",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
    "PP",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
    "PP",
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
    "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP"
    "PP",
};

float offsetX = 0;

float offsetY = 0;
class OBJECTS {
public:
  float dx, dy;
  FloatRect rect;
  bool onGround;
  Sprite sprite;
  float currentFrame;
  bool life;

  static bool Collision(const FloatRect& rect, const String& chars) // Проверка возможности дальнейшего движения. Проверка
                          // столкновения с текстурой.
                          // O(H*W), где H - высота персонажа, W - ширина персонажа
  {

    for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++) {
      for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++) {
        for (char c : chars) {
          if (TileMap[i][j] == c) {
            return true;
          }
        }
      }
    }
    return false;
  }
};
class PLAYER : public OBJECTS
//Создаем класс игрока. Описываем его координаты.
{

public:
  PLAYER(Texture &image)
  //Объявляем игрока. Создаем для него sprite.
  {
    sprite.setTexture(image);
    rect = FloatRect(100, 180, 16, 16);

    dx = dy = 0.1;
    currentFrame = 0;
  }

  void update(float time) // Описываем движения игрока во время прыжка.
  {

    rect.left += dx * time;
    while (Collision(rect, "Pk0rt")) {
      rect.left -= dx * rect.width;
    }

    if (!onGround)
      dy = dy + 0.0005 * time;
    rect.top += dy * time;
    onGround = false;
    if (Collision(rect, "Pk0rt")) {
      while (Collision(rect, "Pk0rt")) {
        rect.top -= dy * rect.height;
      }
      if (dy > 0) {
        onGround = true;
      }
      dy = 0;
    }
    currentFrame += time * 0.005;
    if (currentFrame > 3)
      currentFrame -= 3;

    if (dx > 0)
      sprite.setTextureRect(IntRect(112 + 31 * int(currentFrame), 144, 16, 16));
    if (dx < 0)
      sprite.setTextureRect(
          IntRect(112 + 31 * int(currentFrame) + 16, 144, -16, 16));

    sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

    dx = 0;
  }

};

class ENEMY : public OBJECTS
//Создаем класс врага. Описываем его координаты.
{

public:
  void set(Texture &image, int x, int y) // Создание текстуры врага.
  {
    sprite.setTexture(image);
    rect = FloatRect(x, y, 16, 16);

    dx = 0.05;
    currentFrame = 0;
    life = true;
  }

  void update(float time) // Описываем движения врага.
  {
    rect.left += dx * time;

    if (Collision(rect, "P0")) {
      dx *= -1;
      while (Collision(rect, "P0")) {
        rect.left += dx * rect.width;
      }
    }

    currentFrame += time * 0.005;
    if (currentFrame > 2)
      currentFrame -= 2;

    sprite.setTextureRect(IntRect(18 * int(currentFrame), 0, 16, 16));
    if (!life)
      sprite.setTextureRect(IntRect(58, 0, 16, 16));

    sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
  }
};

void game() {
  RenderWindow window(VideoMode(500, 300), "Game"); // Создание окна.

  Texture tileSet;
  tileSet.loadFromFile("Mario_Tileset.png"); // Загрузка текстуры.

  PLAYER Mario(tileSet);
  ENEMY enemy;
  enemy.set(tileSet, 48 * 16, 13 * 16);

  Sprite tile(tileSet);

  Clock clock;

  while (window.isOpen()) {

    float time =
        clock.getElapsedTime().asMicroseconds(); // Высчитываем прошедшее время.
    clock.restart(); // Обнуляем счетчик времени.

    time = time / 500;

    if (time > 20)
      time = 20;

    Event event;
    while (window.pollEvent(event))

    {
      if (event.type == Event::Closed)
        window.close(); // Закрываем окно.
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) // Движение вправо.
      Mario.dx = 0.1;

    if (Keyboard::isKeyPressed(Keyboard::Left)) // Движение влево.
      Mario.dx = -0.1;

    if (Keyboard::isKeyPressed(Keyboard::Up)) // Движение вверх.
      if (Mario.onGround) {
        Mario.dy = -0.27;
        Mario.onGround = false;
      }

    Mario.update(time);
    enemy.update(time);

    if (Mario.rect.intersects(enemy.rect)) {
      if (enemy.life) {
        if (Mario.dy > 0) {
          enemy.dx = 0;
          Mario.dy = -0.2;
          enemy.life = false;
        } else
          Mario.sprite.setColor(Color::Red); // При проигрыше игрока игрок
                                             // окрашивается в красный цвет.
      }
    }

    if (Mario.rect.left > 200)
      offsetX = Mario.rect.left - 200;

    window.clear(Color(107, 140, 255));

    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) {
        if (TileMap[i][j] == 'P')
          tile.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

        if (TileMap[i][j] == 'k')
          tile.setTextureRect(IntRect(143, 112, 16, 16));

        if (TileMap[i][j] == 't')
          tile.setTextureRect(IntRect(0, 47, 32, 95 - 47));

        if (TileMap[i][j] == 'g')
          tile.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

        if (TileMap[i][j] == 'G')
          tile.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

        if (TileMap[i][j] == 'd')
          tile.setTextureRect(IntRect(0, 106, 74, 127 - 106));

        if (TileMap[i][j] == 'w')
          tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

        if (TileMap[i][j] == 'r')
          tile.setTextureRect(IntRect(143 - 32, 112, 16, 16));

        if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0'))
          continue;

        tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);
        window.draw(tile);
      }

    window.draw(Mario.sprite);
    window.draw(enemy.sprite);

    window.display();
  }
}
