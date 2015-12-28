#ifndef menuItem_h
#define menuItem_h

#include "Arduino.h"
#include <EEPROM.h>


class menuItem
{
  public:
    menuItem(String name, int addr, int relay=-1, int minValue=0, int maxValue=100);
    void setNext(menuItem *mi);
    void setPrev(menuItem *mi);
    menuItem *getNext();
    menuItem *getPrev();
    String getName();
    virtual String getValue();
    virtual void incValue();
    virtual void decValue();
    int getInteger();
    void setMin(int minValue);
    void setMax(int maxValue);
    int getRelay();
    
  protected:
    String _name;
    int _value;
    int _minValue;
    int _maxValue;
    int _addr;
    int _relay;
    int readValue() { return EEPROM.read(_addr); }
    void saveValue() { EEPROM.write(_addr, _value); }
    
    menuItem *_next;
    menuItem *_prev;
};

#endif
