#pragma once

#include "Arduino.h"

struct state_t {
    char  tag[3];
};

typedef void (*example_f_ptr)(void);

class Example {

private:
    state_t state;

public:

    static example_f_ptr funcArray[2];
    static state_t* stateArray[2];

    Example() {
        init_nested(this);
    }

    ~Example() {
    }

    static void IRAM_ATTR some(state_t* arg) {
        Serial.println(__FUNCTION__);
        Serial.println(arg->tag);
    }

    void tag(char a, char b) {
        state.tag[0] = a;
        state.tag[1] = b;
        state.tag[2] = '\0';
    }

    void other() {
        Serial.println(__FUNCTION__);
    }

    static void init_nested(Example* ptr) {
        stateArray[0] = &(ptr->state);
        stateArray[1] = &(ptr->state);
        funcArray[0] = &nested0;
        funcArray[1] = &nested1;
    }

    static void IRAM_ATTR nested0(void) {
        some(stateArray[0]);
    }

    static void IRAM_ATTR nested1(void) {
        some(stateArray[1]);
    }

    void test() {
        some(stateArray[0]);
        some(stateArray[1]);
    }

};
