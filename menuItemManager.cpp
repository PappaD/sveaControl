#include "menuItemManager.h"

void menuItemManager::addMenuItem(menuItem *mi)
{
  if(_first == 0)
  {
    _first = mi;
    _last = mi;
  } 
  else
  {
    _last->setNext(mi);
    _first->setPrev(mi);
    mi->setPrev(_last);
    mi->setNext(_first);
    _last = mi;
  }
}

