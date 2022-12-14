#ifndef ITASK
#define ITASK

class ITask {

    protected:
        int myPeriod;
        int timeElapsed;

    public:    
        virtual void init(int period) {
            this->myPeriod = period;
            timeElapsed = 0;
        }

        virtual void tick() = 0;

        bool updateAndCheckTime(int basePeriod) {
            timeElapsed += basePeriod;
            if (timeElapsed >= myPeriod) {
                timeElapsed = 0;
                return true;
            } else {
                return false;
            }
        }

        virtual void reset() = 0;
};

#endif