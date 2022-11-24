#ifndef IDISPLAY
#define IDISPLAY

class IDisplay {

    public:
        virtual void print(String string, int size, int x, int y) = 0;
        virtual void printLine(String string, bool big) = 0;
        virtual void clear() = 0;
        
};

#endif