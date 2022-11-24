#ifndef SERVO
#define SERVO

#include "IServo.h"

class Servo: public IServo {

    private:
        int currPos;

    public:
        Servo() {
            this->currPos = 0;
            //ruota a zero;
        }

        void rotate(int degree){
            //ruota
        }

};

#endif