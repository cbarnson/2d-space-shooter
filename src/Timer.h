#ifndef TIMER_H
#define TIMER_H

#include <allegro5/allegro.h>

class Timer {

  public:
   Timer(int fps);
   ~Timer();

   void startTimer();
   void stopTimer();
   void resetTimer();
   void resetTimerAndStop();
   
   int getCount() const;
   bool isRunning() const;

  private:
   ALLEGRO_TIMER* _timer;
   int _fps;
   
};

#endif
