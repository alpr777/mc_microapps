#ifndef PIN_EXC_H
#define PIN_EXC_H

#include <Arduino.h>

class OutputExc
{
private:
    uint8_t pin;

public:
    bool state;
    bool previous;
    unsigned long timestamp;

private:
    void init()
    {
        pinMode(pin, 0x1);
    };

public:
    bool read()
    {
        state = digitalRead(pin);
        return state;
    };

    void write(bool cmd)
    {
        if (read() == cmd)
        {
            return;
        }
        digitalWrite(pin, cmd);
    };

    void on()
    {
        if (read() == true)
        {
            return;
        }
        digitalWrite(pin, 0x1);
    };

    void off()
    {
        if (read() == false)
        {
            return;
        }
        digitalWrite(pin, 0x0);
    };

    void inverse()
    {
        digitalWrite(pin, !read());
    };

    void active(unsigned long &currentMillisecTime)
    {
        timestamp = currentMillisecTime;
        on();
    };

    //process(unsigned long &currentMillisecTime, unsigned long eventInterval, bool eventState)
    //
    //void process(unsigned long &currentMillisecTime, unsigned long eventInterval, void (*eventAct)())
    //
    //void process(void (*eventAct)())
    void process(unsigned long &currentMillisecTime, unsigned long eventInterval, bool eventState)
    {
        if (currentMillisecTime - timestamp < eventInterval)
        {
            return;
        }
        write(eventState);
    };

    //process(unsigned long &currentMillisecTime, unsigned long eventInterval, bool eventState)
    //
    //void process(unsigned long &currentMillisecTime, unsigned long eventInterval, void (*eventAct)())
    //
    //void process(void (*eventAct)())
    void process(unsigned long &currentMillisecTime, unsigned long eventInterval, void (*eventAct)())
    {
        if (currentMillisecTime - timestamp < eventInterval)
        {
            return;
        }
        read();
        eventAct();
    };

    //process(unsigned long &currentMillisecTime, unsigned long eventInterval, bool eventState)
    //
    //void process(unsigned long &currentMillisecTime, unsigned long eventInterval, void (*eventAct)())
    //
    //void process(void (*eventAct)())
    void process(void (*eventAct)())
    {
        read();
        eventAct();
    };

    OutputExc(uint8_t pinNumb, bool startState)
    {
        pin = pinNumb;
        init();
        write(startState);
    };
};

class InputExc
{
private:
    uint8_t pin;

public:
    bool state;
    bool previous;
    unsigned long timestamp;

private:
    void init()
    {
        pinMode(pin, 0x0);
    };

public:
    bool read()
    {
        state = digitalRead(pin);
        return state;
    };

    void update()
    {
        previous = state;
    };

    void process(unsigned long &currentMillisecTime, unsigned long eventInterval, void (*eventAct)())
    {
        read();
        if (currentMillisecTime - timestamp < eventInterval)
        {
            return;
        }
        eventAct();
    };

    void process(void (*eventAct)())
    {
        read();
        eventAct();
    };

    void pressing(unsigned long &currentMillisecTime, unsigned long triggerInterval, bool triggerState, void (*eventAct)())
    {
        read();
        if (state == previous)
        {
            return;
        }
        if (state == triggerState && currentMillisecTime - timestamp > triggerInterval)
        {
            eventAct();
        }
        timestamp = currentMillisecTime;
        update();
    };

    void switching(unsigned long &currentMillisecTime, unsigned long triggerInterval, void (*eventAct)())
    {
        read();
        if (state == previous)
        {
            return;
        }
        if (currentMillisecTime - timestamp > triggerInterval)
        {
            eventAct();
        }
        timestamp = currentMillisecTime;
        update();
    };

    void retention(unsigned long &currentMillisecTime, unsigned long triggerInterval, bool triggerState, void (*eventAct)())
    {
        read();
        if (state != triggerState)
        {
            return;
        }
        if (currentMillisecTime - timestamp > triggerInterval)
        {
            eventAct();
            timestamp = currentMillisecTime;
        }
    };

    bool pressing(unsigned long &currentMillisecTime, unsigned long triggerInterval, bool triggerState)
    {
        read();
        if (state != previous && state == triggerState && currentMillisecTime - timestamp > triggerInterval)
        {
            timestamp = currentMillisecTime;
            update();
            return true;
        }
        return false;
    };

    bool switching(unsigned long &currentMillisecTime, unsigned long triggerInterval)
    {
        read();
        if (state != previous && currentMillisecTime - timestamp > triggerInterval)
        {
            timestamp = currentMillisecTime;
            update();
            return true;
        }
        return false;
    };

    bool retention(unsigned long &currentMillisecTime, unsigned long triggerInterval, bool triggerState)
    {
        read();
        if (state == triggerState && currentMillisecTime - timestamp > triggerInterval)
        {
            timestamp = currentMillisecTime;
            update();
            return true;
        }
        return false;
    };

    InputExc(uint8_t pinNumb)
    {
        pin = pinNumb;
        init();
    };
};

#endif