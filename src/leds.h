#include <FastLED.h>

#define LED0 LED_BUILTIN
#define LED1 5
#define LED2 6
#define LED3 9
#define STEP 0x10

#define NUM_LEDS 50
CRGB leds[NUM_LEDS];

int iled1 = 0x00;
int iled2 = 0x00;
int iled3 = 0x00;

int screen[6][8] = {
    {42, 43, 44, 45, 46, 47, 48, 49},
    {41, 40, 39, 38, 37, 36, 35, 34},
    {25, 26, 27, 28, 29, 30, 31, 32},
    {24, 23, 22, 21, 20, 19, 18, 17},
    {8, 9, 10, 11, 12, 13, 14, 15},
    {7, 6, 5, 4, 3, 2, 1, 0}};

void ledset(int &current, pin_size_t pin, int amount)
{
  current = amount;
  analogWrite(pin, current);
}
void ledup(int &current, pin_size_t pin, int amount)
{
  current += amount;
  if (current > 255)
  {
    current = 255;
  }
  analogWrite(pin, current);
}
void leddown(int &current, pin_size_t pin, int amount)
{
  current -= amount;
  if (current < 0)
  {
    current = 0;
  }
  analogWrite(pin, current);
}

void fade(uint8_t scaledown)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].nscale8(scaledown);
  }
}

void chase()
{
  int fast;
  int slow;
  for (int i = 0; i < NUM_LEDS * 4; i++)
  {
    fast = (i / 4) % 50;
    slow = (i / 2) % 50;
    leds[fast] = CRGB::Green;
    leds[NUM_LEDS - 1 - slow] = CRGB::Yellow;

    FastLED.show();
    delay(50);

    fade(170);
    leds[fast] = CRGB::Red;
    leds[NUM_LEDS - 1 - slow] = CRGB::Purple;
  }
}

void downaccross()
{
  for (int x = 0; x < 6; x++)
  {
    for (int y = 0; y < 8; y++)
    {
      leds[screen[x][y]] = CRGB::Red;
      FastLED.show();
      delay(100);
      leds[screen[x][y]] = CRGB::Black;
    }
  }
}
void accrossdown()
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 6; x++)
    {
      leds[screen[x][y]] = CRGB::Red;
      FastLED.show();
      delay(100);
      leds[screen[x][y]] = CRGB::Black;
    }
  }
}
void colourfade(CRGB crgb)
{
  for (int y = 0; y < 8; y++)
  {
    for (int x = 0; x < 6; x++)
    {
      leds[screen[x][y]] = crgb;
    }
  }
  for (int i = 0; i < 50; i++)
  {
    FastLED.show();
    delay(25);
    fade(240);
  }
}

void xloop()
{
  accrossdown();
  downaccross();
  chase();
  colourfade(CRGB::Red);
  colourfade(CRGB::Yellow);
  colourfade(CRGB::Purple);
  colourfade(CRGB::Green);
  colourfade(CRGB::Pink);
}
