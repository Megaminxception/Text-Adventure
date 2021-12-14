//
//  Room.cpp
//  Text Adventure
//
//  Created by Megaminxception on 12/13/21.
//

#include "Room.hpp"

Room::Room(std::string contents) {
  this->contents = contents;
  this->item = "nothing";
  this->itemPrice = 0;
}

Room::Room(std::string contents, std::string item, int itemPrice) {
  this->contents = contents;
  this->item = item;
  this->itemPrice = itemPrice;
}

// Idek if I need this but whatever lol
Room::Room() {
  
}

std::string Room::getContents() {
  return this->contents;
}

std::string Room::getItem() {
  return this->item;
}

int Room::getItemPrice() {
  return this->itemPrice;
}
