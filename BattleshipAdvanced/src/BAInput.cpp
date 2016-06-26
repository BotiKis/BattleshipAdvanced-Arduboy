#include "BAInput.h"

#define MILLIS_SINCE(MILLIS) (millis() - MILLIS)

// ------------------------------------------------
// BAInput
BAButton::BAButton(){
  reset();
}

void BAButton::reset(){
  pressed = false;
  pressedTimestamp = lastPollTimestamp = 0;
  hold = false;
}

// ------------------------------------------------
// BAInput

BAInput::BAInput(Arduboy *arduboy){
  fireContinuous = false;
  refireAfterMillis = BA_INPUT_REFIRERATE_DEFAULT;
  this->arduboy = arduboy;
  reset();
}

void BAInput::reset(){
  uint8_t btns[6] = {LEFT_BUTTON, RIGHT_BUTTON, UP_BUTTON, DOWN_BUTTON, A_BUTTON, B_BUTTON};
  // init buttons with arduboy buttons
  for (uint8_t i = 0; i < 6; i++) {
    buttons[i].reset();
    buttons[i].arduboyButton = btns[i];
  }
}

void BAInput::updateInput(){

  // all buttons
  for (uint8_t i = 0; i < 6; i++) {
    if (this->arduboy->pressed(buttons[i].arduboyButton)) {
        if (buttons[i].pressed) {
          buttons[i].hold = true;
        }
        else{
          buttons[i].pressedTimestamp = millis();
          buttons[i].pressed = true;
          buttons[i].hold = false;
        }
    }
    else{
      if (buttons[i].pressed) {
        buttons[i].reset();
      }
    }
  }

}


bool BAInput::pressed(uint8_t button){

  for (uint8_t i = 0; i < 6; i++){
    if(buttons[i].arduboyButton == button && buttons[i].pressed){
      if(fireContinuous)
        return true;
      else{
        if ( buttons[i].lastPollTimestamp == 0 || (MILLIS_SINCE(buttons[i].lastPollTimestamp) > refireAfterMillis)) {
          buttons[i].lastPollTimestamp = millis();
          return true;
        }
      }
    }
  }
  return false;
}

bool BAInput::pressedForMillis(uint8_t button, unsigned long milliseconds){
  for (uint8_t i = 0; i < 6; i++){
    if(buttons[i].arduboyButton == button && buttons[i].hold){
      return (MILLIS_SINCE(buttons[i].pressedTimestamp) > milliseconds);
    }
  }
  return false;
}

bool BAInput::longPressed(uint8_t button){
  return pressedForMillis(button, 1000);
}
