/*

*/
#ifndef menuItemManager_h
#define menuItemManager_h

#include "Arduino.h"
#include "menuItem.h"

class menuItemManager
{
  public:
    menuItemManager() { _first = 0; _last = 0; } ;
    void addMenuItem(menuItem *mi);
    menuItem *getFirst() { return _first; }; 

  private:
    menuItem *_first;
    menuItem *_last;
};

#endif
