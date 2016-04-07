#include "Timer.h"
#include <iostream>
#include <stdexcept>

Timer::Timer(int fps) : _fps(fps) {
   if ((_timer = al_create_timer(1.0 / _fps)) == NULL) {
      throw std::runtime_error("cannot initialize timer\n");
   }   
}

Timer::~Timer() {
   if (_timer != NULL) {
      al_destroy_timer(_timer);
   }
   std::cout << "timer deleted\n";      
}

void Timer::startTimer() {
   al_start_timer(_timer);
}

void Timer::stopTimer() {
   al_stop_timer(_timer);
}

void Timer::resetTimer() {
   al_set_timer_count(_timer, 0);
   al_start_timer(_timer);
}

void Timer::resetTimerAndStop() {
   al_set_timer_count(_timer, 0);
}

int Timer::getCount() const {
   return al_get_timer_count(_timer);
}

bool Timer::isRunning() const {
   return al_get_timer_started(_timer);
}

