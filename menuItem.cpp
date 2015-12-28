#include "Arduino.h"
#include "menuItem.h"

menuItem::menuItem(String name, int addr, int relay, int minValue, int maxValue)
{
    _name=name;
    _addr=addr;
    _minValue = minValue;
    _maxValue = maxValue;
    _value = readValue();
    _relay = relay;
}


void menuItem::setNext(menuItem *mi)
{
   _next = mi;
}

int  menuItem::getRelay() 
{ 
    return _relay; 
}

void menuItem::setPrev(menuItem *mi)
{
  _prev = mi;
}

menuItem* menuItem::getNext()
{
  return _next;
}

menuItem* menuItem::getPrev()
{
  return _prev;
}

String menuItem::getName()
{
    return(_name); 
}

String menuItem::getValue()
{
  return String(_value);
}

void menuItem::incValue()
{
  _value++;
  if(_value > _maxValue) _value = _maxValue;
  saveValue();
}

void menuItem::decValue()
{
  _value--;
  if(_value < _minValue) _value = _minValue;
  saveValue();
}


int menuItem::getInteger()
{
  return _value;
}


void menuItem::setMin(int minValue)
{
  _minValue = minValue;
}


void menuItem::setMax(int maxValue)
{
  _maxValue = maxValue;
}


