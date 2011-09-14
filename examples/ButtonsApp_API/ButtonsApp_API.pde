
#include <ButtonsApp.h>

ButtonsApp buttons;

int pin(0), val(0), type(0);

void setup() {
  buttons.begin();
}

void loop() {
  
  buttons.refresh();
  buttons.lastButton(pin, val, type);
  
  digitalWrite(pin, !digitalRead(pin));
  delay(50);
  
}

