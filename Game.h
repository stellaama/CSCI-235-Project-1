#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <vector>
using namespace std;

enum Activity {SEEDING, HARVESTING, MOVING, IDLE};

class Tractor{
 public:
  Tractor();
  Tractor(int x_val, int y_val, unsigned short size_val, Activity activity_val);
  //Mutator and accessor for x-coordinate
  void set_xcoord(const int new_x);
  int get_xcoord() const;

  //Mutator and accessor for y-coordinate
  void set_ycoord(const int new_y);
  int get_ycoord() const;

  //Mutator and accessor for size
  void setSize(const unsigned short newSize);
  int getSize() const;

  //Mutator and accessor for acitivity
  void setActivity(const Activity newActivity);
  int getActivity() const;
  
 private:
  int x;
  int y;
  unsigned short size;
  Activity activity;
};

class Game{
 public:
  Game(unsigned int new_size);
  int GetTractor(int x, int y) const;
  void SelectTractor(int x, int y );
  void SelectTractors( int x1, int y1, int x2, int y2 );
  void AddTractor(const Tractor& new_unit);
  bool MoveTractor(int i, int new_x, int new_y );
  void AssignTractorsActivity(Activity new_activity);
  void PrintTractor(int i) const;
  void PrintSelectedTractors() const;
  void PrintAllTractors() const;
  
 private:
  unsigned int map_size;
  vector<Tractor> all;
  vector<int> selected;
};

#endif
