/* 
  this class will use chrono for time management / timer
*/

#include <chrono>

namespace timer {
  auto start;
  auto end;
  auto result;
  
  
  void start_timer ();
  
  void stop_timer ();
  
  void reset_timer ();
  
  int get_timer_in_miliseconds ();
  
  int get_timer_in_seconds ();
};

void timer::start_timer () {
  timer::start = std::chrono::steady_clock::now ();
}

void timer::stop_timer () {
  timer::end = std::chrono::steady_clock::end ();
}

int timer::get_timer_in_miliseconds () {
  timer::result = std::chrono::duration_cast <std::chrono::miliseconds>(timer::end - timer::start);
  
  int ms = static_cast <int> (timer::result.count ());
  
  return ms;
}

void timer::get_timer_in_seconds () {
  timer::result = std::chrono::duration_cast <std::chrono::seconds>(timer::end - timer::start);
  
  int ms = static_cast <int> (timer::result.count ());
}

void timer::reset_timer () {
  timer::start = 0;
  timer::end = 0;
  timer::result = 0;
}