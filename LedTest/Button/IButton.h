#ifndef IBUTTON
#define IBUTTON

class IButton {

    public:
        virtual void listen() = 0;
        virtual bool isOn() = 0;
};

#endif