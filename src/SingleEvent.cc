//Information of single hit
#include "SingleEvent.h"

SingleEvent *SingleEvent::SiPointer;

SingleEvent::SingleEvent() {
SiPointer = this;  
}

SingleEvent::~SingleEvent()
{
}
