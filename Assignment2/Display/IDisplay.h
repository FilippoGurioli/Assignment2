#ifndef IDISPLAY
#define IDISPLAY

class IDisplay {

    public:

        virtual void printTitle(String string) = 0;
        virtual void printStatString(String stat) = 0;
        virtual bool updateStatValue(int row, int value) = 0;
        virtual void clear() = 0;
        
};

#endif