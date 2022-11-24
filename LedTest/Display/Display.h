#ifndef DISPLAYY
#define DISPLAYY

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "IDisplay.h"

#define WIDTH 128
#define HEIGHT 64

Adafruit_SSD1306 display(WIDTH, HEIGHT);

class Display: public IDisplay {

    private:
        int line;

    public:
        Display() {
            display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
            display.setTextColor(WHITE);
            this->line = 10;
        }

        void print(String string, int size, int x, int y) {
            display.setTextSize(size);
            display.setCursor(x,y);
            display.println(string);
            display.display();
        }

        void printLine(String string, bool big){

            if(big) {
                this->print(string, 1, 10, line);
                line += 10;
            } else {
                this->print(string, 2, 10, line);
                line += 20;
            }
            display.display();
            
        }

        void clear() {
            display.clearDisplay();
            display.display();
            this->line = 0;
        }

};

#endif