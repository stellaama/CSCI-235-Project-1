#include <iostream>
#include <vector>
#include "Game.h"
using namespace std;

//default constructor 
Tractor :: Tractor(){
  x=0;
  y=0;
  size=0;
  activity= IDLE;
}

//parameterized constructor
Tractor :: Tractor (int x_val, int y_val, unsigned short size_val, Activity activity_val){
  x=x_val;
  y=y_val;
  size=size_val;
  activity=activity_val;
}

//Mutator method set_xcoord
void Tractor :: set_xcoord(const int new_x){
  x=new_x;
}

//Accessor method get_xcoord
int Tractor :: get_xcoord() const{
  return x;
}

//Mutator method set_ycoord
void Tractor :: set_ycoord(const int new_y){
  y=new_y;
}

//Accessor method set_ycoord
int Tractor ::get_ycoord() const{
  return y;
}  

//Mutator method setSize
void Tractor ::  setSize(const unsigned short newSize){
  size= newSize;
}

//Accessor method getSize
int Tractor :: getSize() const{
  return size;
}

//Mutator method setActivity
void Tractor :: setActivity(const Activity newActivity){
  activity = newActivity;
}

//Accessor method getActivity
int Tractor :: getActivity() const{
  return activity;
}

//Contructor to set the size of the map
Game :: Game(unsigned int new_size){
  map_size= new_size;
}

//Retrieves tractor at coordinate (x,y)
int Game :: GetTractor( int x, int y ) const{
  //Gets the tractor if the coordinate (x,y) is in the square unit 
  for (int i=0; i < all.size(); i++){
    if ((x >= (all[i].get_xcoord() - all[i].getSize()/ 2.0))
	&& (x <= (all[i].get_xcoord() + all[i].getSize()/ 2.0))
	&& (y >= (all[i].get_ycoord() - all[i].getSize()/2.0))
	&& (y <= (all[i].get_ycoord() + all[i].getSize()/2.0)))
      return i;
  }
  return -1;
}

//Empties the vector selected and adds a tractor to the vector if "clicked"
void Game :: SelectTractor(int x, int y ){
  if (GetTractor(x,y) == -1){
    while (!(selected.empty()))
      selected.pop_back();
  }
  else{
    while (!(selected.empty()))
      selected.pop_back();
    selected.push_back(GetTractor(x,y));
  }
}

//Empties the vector selected and adds tractors to the vector inside the rectangle created by the (x1,y1) and (x2,y2) coordinates
void Game :: SelectTractors( int x1, int y1, int x2, int y2){
  //Checks if the selected coordinates for the rectangle are inside the map
  if ((x1 > map_size) || (x1 < 0) || (y1 > map_size)|| (y1 < 0) || (x2 > map_size) || (x2 < 0) || (y2 > map_size) || (y2 < 0))
    cout << "The selected coordinates are out of map bounds." << endl;
  while (!selected.empty())
    selected.pop_back();

  //When (x1,y1) is at bottom left and (x2,y2) is at top right and if the box is partially inside the rectangle, it is added to the vector selected
  if ((x1 < x2) && (y1 < y2))
    for (int i=0; i < all.size(); i++){
      if ((x1 <= (all[i].get_xcoord() + all[i].getSize()/ 2.0))
	  && (x2 >= (all[i].get_xcoord() - all[i].getSize()/ 2.0))
	  && (y1 <= (all[i].get_ycoord() + all[i].getSize()/2.0))
	  && (y2 >= (all[i].get_ycoord() - all[i].getSize()/2.0)))
	selected.push_back(i);
    }

  //When (x1,y1) is at top left and (x2,y2) is at bottom right and if the box is partially inside the rectangle, it is added to the vector selected
  if ((x1 < x2) && (y1 > y2))
    for (int i=0; i < all.size(); i++){
      if ((x1 <= (all[i].get_xcoord() + all[i].getSize()/ 2.0))
	  && (x2 >= (all[i].get_xcoord() - all[i].getSize()/ 2.0))
	  && (y1 >= (all[i].get_ycoord() - all[i].getSize()/2.0))
	  && (y2 <= (all[i].get_ycoord() + all[i].getSize()/2.0)))
	selected.push_back(i);
    }

  //When (x1,y1) is at top right and (x2,y2) is at bottom left and if the box is partially inside the rectangle, it is added to the vector selected
  if ((x1 > x2) && (y1 > y2))
    for (int i=0; i < all.size(); i++){
      if ((x1 >= (all[i].get_xcoord() - all[i].getSize()/ 2.0))
	  && (x2 <= (all[i].get_xcoord() + all[i].getSize()/ 2.0))
	  && (y1 >= (all[i].get_ycoord() - all[i].getSize()/2.0))
	  && (y2 <= (all[i].get_ycoord() + all[i].getSize()/2.0)))
	selected.push_back(i);
    }

  //When (x1,y1) is at bottom right and (x2,y2) is at top left and if the box is partially inside the rectangle, it is added to the vector selected
  if ((x1 > x2) && (y1 < y2))
    for (int i=0; i < all.size(); i++){
      if ((x1 >= (all[i].get_xcoord() - all[i].getSize()/ 2.0))
	  && (x2 <= (all[i].get_xcoord() + all[i].getSize()/ 2.0))
	  && (y1 <= (all[i].get_ycoord() + all[i].getSize()/2.0))
	  && (y2 >= (all[i].get_ycoord() - all[i].getSize()/2.0)))
	selected.push_back(i);
    }
}

//Adds tractor to all vector
void Game :: AddTractor(const Tractor& new_unit){
  all.push_back(new_unit);
}

//Assigns the same activity to all selected tractors
void Game :: AssignTractorsActivity(Activity new_activity){
  for (int i=0; i < selected.size(); i++){
    all[selected[i]].setActivity(new_activity);
  }
}

//Moves a tractor to another point on the map
bool Game :: MoveTractor(int i, int new_x, int new_y){
  //Doesn't allow the new position to be out of map bounds
  if ((new_x > map_size) || (new_x < 0) || (new_y > map_size) || (new_y < 0))
    return 0;
  
  //Doesn't allow for the tractor to be partially out of map bounds
  if (((new_x + all[i].getSize()/2.0) > map_size)
      || ((new_x - all[i].getSize()/2.0) < 0)
      || ((new_y - all[i].getSize()/2.0) < 0)
      || ((new_y + all[i].getSize()/2.0) > map_size))
    return 0;
  //Doesn't allow the tractor to overlap with other tractors

  for (int k=0; k < all.size(); k++){
    if (((new_x + all[i].getSize()/2.0) >= (all[k].get_xcoord() - all[k].getSize()/2.0))
	&& ((new_x - all[i].getSize()/2.0) <= (all[k].get_xcoord() +  all[k].getSize()/2.0))
	&& ((new_y - all[i].getSize()/2.0) <= (all[k].get_xcoord() + all[k].getSize()/2.0))
	&& ((new_y + all[i].getSize()/2.0) >= (all[k].get_xcoord() - all[k].getSize()/2.0))){
      return 0;
    }
  }
  all[i].set_xcoord(new_x);
  all[i].set_ycoord(new_y);
  return 1;
}

//Prints the x-coordinate, y-coordinate, size, and activity of a tractor
void Game :: PrintTractor(int i) const{
  cout << "The coordinates of tractor " << i << " are (" << all[i].get_xcoord() << "," << all[i].get_ycoord() << "). The size is " << all[i].getSize() << " and its activity is " << all[i].getActivity() << "." << endl;
}

//Prints the units of all the tractors (from the vector all) that is in the selected vector
void Game :: PrintSelectedTractors() const{
  for (int i=0; i < selected.size(); i++){
    cout << "For tractor " << selected[i] << ", its coordinates are (" << all[selected[i]].get_xcoord() << "," << all[selected[i]].get_ycoord() << "). Its size is " << all[selected[i]].getSize() << " and its activity is " << all[selected[i]].getActivity() << "." << endl;
  }
}

//Prints the units of all the tractors from all vector
void Game :: PrintAllTractors() const{
  for (int i=0; i < all.size(); i++)
    PrintTractor(i);
}

