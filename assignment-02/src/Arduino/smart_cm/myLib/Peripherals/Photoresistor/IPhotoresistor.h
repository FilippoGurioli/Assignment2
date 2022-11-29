#ifndef IPHOTORESISTOR
#define IPHOTORESISTOR

class IPhotoresistor {

    public:
        virtual int getLightLevel() = 0;
        
};

#endif