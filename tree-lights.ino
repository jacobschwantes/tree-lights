#include <FastLED.h>
#define NUM_LEDS 50
#define DATA_PIN 11
#define BRIGHTNESS 255
#define SPEED 45
#define DELAY 70
#define SNAKE_SIZE 5
CRGB leds[NUM_LEDS];

// notes for v2 2024: on/off button, button to cycle animations (demo mode, cycle animations / colors, dials for speed and brightness, usb port in, dc power in (for microcontroller & led 5v), led female connector out, screen (to display brightness, x/y preset cycle progress indicator, big text in middle saying mode/preset), 3d printed chasis

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  dark();
  FastLED.show();
}

void loop()
{
  fadeSpiral();
  growRainbow();
  cyclone();
  cycle();
}

void dark()
{
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
}

void light()
{
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
  }
}

void fadeAll()
{
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    leds[i].nscale8(250);
  }
}

void cycle()
{
  for (byte i = 0; i < 255; i++)
  {
    for (byte j = 0; j < NUM_LEDS; j++)
    {
      leds[NUM_LEDS - j] = CHSV(i, 255, 255);
    }
    FastLED.delay(SPEED);
  }
  fadeAll();
}

void race()
{
  for (byte i = 1; i < 11; i++)
  {
    byte hue = 23 * i;

    if (i % 2)
    {
      for (byte j = 0; j < NUM_LEDS; j++)
      {
        FastLED.delay(SPEED);
        leds[j] = CHSV(hue, 255, 255);

        fadeAll();
      }
    }
    else
    {
      for (byte j = NUM_LEDS; j > 0; j--)
      {
        FastLED.delay(SPEED);
        leds[j] = CHSV(hue, 255, 255);

        fadeAll();
      }
    }
    FastLED.delay(DELAY);
  }
}

void cyclone()
{
  for (byte i = 0; i < 11; i++)
  {
    double hue = 25.5 * i;
    for (byte j = 0; j < NUM_LEDS; j++)
    {
      FastLED.delay(SPEED);
      leds[j] = CHSV(hue, 255, 255);
      if (i != 10)
      {
        fadeAll();
      }
    }
  }
  FastLED.delay(DELAY);
}

void growRainbow()
{

  for (byte j = 0; j < 26; j++)
  {
    byte hue = 10 * j;
    leds[24 - j] = CHSV(hue, 255, 255);
    leds[24 + j] = CHSV(hue, 255, 255);

    fadeAll();
    FastLED.delay(SPEED);
  };
  FastLED.delay(DELAY);
  for (byte j = 25; j > 0; j--)
  {
    leds[25 - j] = CRGB::Black;
    leds[24 + j] = CRGB::Black;

    FastLED.delay(SPEED);
  };
  FastLED.delay(DELAY);
};

void spread()
{
  for (byte i = 1; i < 10; i++)
  {
    byte hue = 25 * i;
    for (byte j = 1; j < (NUM_LEDS / 2); j++)
    {
      FastLED.delay(SPEED);
      leds[24 - j] = CRGB::Black;
      leds[24 + j] = CRGB::Black;
    };
    FastLED.delay(DELAY);

    for (byte j = 1; j < (NUM_LEDS / 2); j++)
    {
      FastLED.delay(SPEED);
      leds[24 - j] = CHSV(hue, 255, 255);
      leds[24 + j] = CHSV(hue, 255, 255);
    };
    FastLED.delay(DELAY);
  };
};

void snake()
{
  for (byte j = 0; j < NUM_LEDS + SNAKE_SIZE - 2; j++)
  {
    dark();
    for (byte n = 0; n < SNAKE_SIZE - 1; n++)
    {
      leds[j + n] = CHSV((5 * (j + n)), 255, 255);
    }

    FastLED.delay(SPEED);
  };
  FastLED.delay(DELAY);

  for (int k = 50; k > -5; k--)
  {
    dark();
    for (byte n = 0; n < 4; n++)
    {

      leds[k + n] = CHSV(5 * (k + n), 255, 255);
    }

    FastLED.delay(SPEED);
  };
  FastLED.delay(DELAY);
};

void snake2()
{
  byte steps = 6.0;
  double ratio = 255.0 / steps;
  for (byte i = 0; i < steps; i++)
  {
    if (i % 2 == 0)
    {
      for (byte j = 0; j < NUM_LEDS + SNAKE_SIZE - 2; j++)
      {
        byte hue = (ratio * i) + (ratio * ((j + 1.0) / (NUM_LEDS + SNAKE_SIZE - 2.0)));
        dark();
        for (byte n = 0; n < SNAKE_SIZE - 1; n++)
        {
          if (j+n < NUM_LEDS) {
          leds[j + n] = CHSV(hue, 255, 255);
          }
        }

        FastLED.delay(SPEED);
      };

    }
    else
    {
      for (int k = 50; k > -5; k--)
      {
        int hue = (ratio * i) + (ratio * ((51.0 - k)/ 55.0));
        dark();
        for (byte n = 0; n < 4; n++)
        {
          if (k+n >= 0) {
          leds[k + n] = CHSV(hue, 255, 255);
          }
        }

        FastLED.delay(SPEED);
      };
 
    }
  }
};

void snakes()
{
  byte MIDPOINT = NUM_LEDS / 2;

  for (int j = MIDPOINT; j > -SNAKE_SIZE - 2; j--)
  {
    byte hue = 10 * j;
    dark();
    for (byte n = 0; n < SNAKE_SIZE - 1; n++)
    {
      leds[min(max(NUM_LEDS - j - n, 26), NUM_LEDS)] = CHSV(hue, 255, 255);
    }
    for (byte n = 0; n < SNAKE_SIZE - 1; n++)
    {
      if (j + n >= 0)
      {
        leds[min(j + n, 26)] = CHSV(hue, 255, 255);
      }
    }

    FastLED.delay(SPEED);
  };
  FastLED.delay(DELAY);
  for (byte j = 0; j < MIDPOINT + SNAKE_SIZE + 2; j++)
  {
    byte hue = 10 * j;
    dark();
    for (byte n = 0; n < SNAKE_SIZE - 1; n++)
    {
      int i = NUM_LEDS - j - n + SNAKE_SIZE;
      if (i > MIDPOINT)
      {
        leds[min(max(i, 26), NUM_LEDS)] = CHSV(hue, 255, 255);
      }
    }
    for (byte n = 0; n < SNAKE_SIZE - 1; n++)
    {
      if (j + n < MIDPOINT)
      {
        leds[min(j + n, 26)] = CHSV(hue, 255, 255);
      }
    }

    FastLED.delay(SPEED);
  };
  FastLED.delay(DELAY);
};

void fadeSpiral()
{
  for (byte i = 1; i < NUM_LEDS; i++)
  {
    byte hue = 5 * i;
    FastLED.delay(SPEED);
    leds[i] = CHSV(hue, 255, 255);

    fadeAll();
  }
  FastLED.delay(DELAY);
  for (byte i = NUM_LEDS; i > 1; i--)
  {
    byte hue = 250 - (5 * i);
    FastLED.delay(SPEED);
    leds[i] = CHSV(hue, 255, 255);

    fadeAll();
  }
  FastLED.delay(DELAY);
}
