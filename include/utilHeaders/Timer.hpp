#include "main.h"
#include "chrono"

#ifndef CLASS_NAME_H
#define CLASS_NAME_H

class Timer{
    public:
        Timer();
        ~Timer();

        void start();

        void stop();

        double getElapsedTime();

        void clear();

    private:
};


#endif