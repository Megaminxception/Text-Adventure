//
//  Room.hpp
//  Text Adventure
//
//  Created by Megaminxception on 12/13/21.
//

#ifndef Room_hpp
#define Room_hpp

#include <stdio.h>
#include <string>

class Room {
private:
  std::string contents;
  std::string item;
  int itemPrice;
  
  Room();
public:
  Room(std::string contents);
  Room(std::string contents, std::string item, int itemPrice);
  std::string getContents();
  std::string getItem();
  int getItemPrice();
};

#endif /* Room_hpp */
