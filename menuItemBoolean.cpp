#include "Arduino.h"
#include "menuItemBoolean.h"

menuItemBoolean::menuItemBoolean(String name, int addr, int relay) : menuItem(name, addr, relay)
{
}

String menuItemBoolean::getValue()
{
  if(_value == 0) {
    return "Av";
  } else {
    return "P\1";
  }
}

void menuItemBoolean::incValue()
{
  if(_value == 0) {
    _value = 1;
  } else {
    _value = 0;
  }

  saveValue();
}

void menuItemBoolean::decValue()
{

  if(_value == 0) {
    _value = 1;
  } else {
    _value = 0;
  }

  saveValue();
}


