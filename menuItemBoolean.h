#ifndef menuItemBoolean_h
#define menuItemBoolean_h

#include "Arduino.h"
#include "menuItem.h"

class menuItemBoolean : public menuItem
{
  public:
    menuItemBoolean(String name, int addr, int relay);
    String getValue();
    void incValue();
    void decValue();

  protected:
};

#endif
