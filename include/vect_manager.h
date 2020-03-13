#ifndef VECTMANAGER_H
#define VECTMANAGER_H

#include <vector>
#include "SingleEvent.h"



class SingleEvent_Manager {
 public:
  SingleEvent_Manager();
  ~SingleEvent_Manager();
 public:

  static SingleEvent_Manager* APointer;
  vector<SingleEvent*> SingleEvent_list;
};

#endif //VECTMANAGER_H
