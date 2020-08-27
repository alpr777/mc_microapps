#ifndef OPENER_H
#define OPENER_H

#include <Arduino.h>

class OpenerExc
{
private:
    typedef class
    {
    public:
        uint8_t pin;
        unsigned long timestamp;

    public:
        void write(bool cmd)
        {
            digitalWrite(pin, cmd);
        };

        void on()
        {
            digitalWrite(pin, 0x1);
        };

        void off()
        {
            digitalWrite(pin, 0x0);
        };

        void active(unsigned long &currentMillisecTime)
        {
            timestamp = currentMillisecTime;
            on();
        };
        void process(unsigned long &currentMillisecTime)
        {
            if (currentMillisecTime - timestamp < 1000)
            {
                return;
            }
            off();
        };
        void init(uint8_t pinNumb)
        {
            pin = pinNumb;
            pinMode(pin, 0x1);
            off();
        };

    } OutputExc;

    typedef class
    {
    public:
        uint8_t pin;
        bool state;
        bool previous;
        unsigned long timestamp;

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

        void init(uint8_t pinNumb)
        {
            pin = pinNumb;
            pinMode(pin, 0x0);
        };
        bool pressing(unsigned long &currentMillisecTime)
        {
            read();
            if (state != previous && state == true && currentMillisecTime - timestamp > 200)
            {
                timestamp = currentMillisecTime;
                update();
                return true;
            }
            return false;
        };

    } InputExc;

public:
    OutputExc relay;
    InputExc button;

public:
    OpenerExc(const unsigned int relayPin, const unsigned int buttonPin)
    {
        relay.init(relayPin);
        button.init(buttonPin);
    };
    void pressingOpen(unsigned long &currentMillisecTime)
    {
        button.read();
        if (button.state == button.previous)
        {
            return;
        }
        if (button.state == true && currentMillisecTime - button.timestamp > 200)
        {
            relay.active(currentMillisecTime);
        }
        button.timestamp = currentMillisecTime;
        button.update();
    };
};

#endif