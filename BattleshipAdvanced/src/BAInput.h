#ifndef BAINPUT_H
#define BAINPUT_H
#include <Arduboy.h>

#define BA_INPUT_NEVER_REFIRE ULONG_MAX

// used only internally
class BAButton{
  public:
    BAButton();
    uint8_t arduboyButton;
    bool pressed;
    bool hold;
    unsigned long pressedTimestamp;
    unsigned long lastPollTimestamp;

    void reset();
};

class BAInput{
  public:
    BAInput(Arduboy *arduboy);

    // Should be called an each new screen.
    void reset();

    // Should be calle after every frame refresh
    void updateInput();

    // Should the buttons refire each frame even when not released.
    // Default = false. If true it's the same effect when polling Arduboy::pressed();
    bool fireContinuous;

    // milliseconds after a button should refire. Default = 500. Works only if fireContinuous = false.
    // if set to BA_INPUT_NEVER_REFIRE than it won't refire.
    unsigned long refireAfterMillis;

    // Getters
    bool pressed(uint8_t button);

    // True if the button is pressed for at least milliseconds or longer
    bool pressedForMillis(uint8_t button, unsigned long milliseconds);

    // True if the button is pressed for 1 sek or longer - Convinience method
    bool longPressed(uint8_t button);

  private:
    BAButton buttons[6];
    Arduboy *arduboy;
};

#endif
