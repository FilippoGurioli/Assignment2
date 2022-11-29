#ifndef DISPLAYY
#define DISPLAYY

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "IDisplay.h"

#define MAX_VALUE_COORDS 5
LiquidCrystal_I2C display(0x27, 20, 4);

class Display: public IDisplay {

    private:
        int cursors[MAX_VALUE_COORDS];
        int head;
        int val;
    
    public:

        Display() {
            this->val = 0;
            this->head = 0;
            display.init();
            display.noBacklight();
            display.clear();
        }

        void printTitle(String string) {
            display.display();
            display.backlight();
            display.setCursor(4, 0);
            display.print(string);
            display.setCursor(0, 1);
        }

        void printStatString(String stat) {
            this->val += display.print(stat);
            display.print(0);
            display.print("   ");
            this->cursors[head++] = val;
            this->val += 4;
        }

        bool updateStatValue(int pos, int value) {
            if (pos <= 0 || pos > head) {
                return false;
            }
            pos--;
            display.setCursor(this->cursors[pos], 1);
            display.print("   ");
            display.setCursor(this->cursors[pos], 1);
            display.print(value);
            return true;
        }

        void clear() {
            display.clear();
            this->head = 0;
            this->val = 0;
            display.noBacklight();
        }
};

#endif