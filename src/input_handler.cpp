#include "input_handler.h"

bool KEYS[322];  // 322 is the number of SDLK_DOWN events


void SetupInputHandler(){
    for(int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }
}

void KeyboardHandler(){

}
