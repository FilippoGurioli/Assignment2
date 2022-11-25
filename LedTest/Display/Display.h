#ifndef DISPLAYY
#define DISPLAYY

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "IDisplay.h"

#define WIDTH 128
#define HEIGHT 64
#define MAX_VALUE_COORDS 5

Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);

class Display: public IDisplay {

    private:
        int valueCoords[MAX_VALUE_COORDS][2];
        int nValueCoords;

    public:

        Display() {
            this->nValueCoords = 0;
            display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextWrap(false);
            display.display();
        }

        void printTitle(String string) {
            display.setTextSize(2);
            display.setCursor(10, 10);
            display.println(string);
            display.println();
            display.display();
        }

        void printStatString(String stat) {
            display.setTextSize(1);
            display.print(stat);
            this->valueCoords[nValueCoords][0] = display.getCursorX();
            this->valueCoords[nValueCoords][1] = display.getCursorY();
            this->nValueCoords++;
            display.println(0);
            display.display();
        }

        bool updateStatValue(int row, int value) {
            if (row > nValueCoords || row <= 0) {
                return false;
            }
            display.fillRect(this->valueCoords[row - 1][0], this->valueCoords[row - 1][1], 16, 8, 0);
            display.setCursor(this->valueCoords[row - 1][0], this->valueCoords[row - 1][1]);
            display.print(value);
            display.display();
            return true;
        }

        void clear() {
            display.clearDisplay();
            for (nValueCoords--; nValueCoords >= 0; nValueCoords--) { //Azzera valueCoords
                this->valueCoords[nValueCoords][0] = NULL;
                this->valueCoords[nValueCoords][1] = NULL;
            }
            this->nValueCoords = 0;
            display.display();
        }
};

#endif