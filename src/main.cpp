//
//  main.cpp
//  Text Adventure
//
//  Created by Megaminxception on 12/13/21.
//

#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

#include "Room.hpp"

// Prototypes
void mapShuffle2D();
void actionManager();
void showMap();
void gameplay();
void calculateScore();
void init();

// Global vars
int movesLeft;
// posRow and posCol hold the position of the user in the map
int posRow;
int posCol;
// Character details
bool knight = false;
bool mage = false;
bool cat = false;
bool dog = false;
int backpackSize;
std::string name;
std::string petName;

// Other important things (map, etc.)
std::string instructions = "Instructions:"
"\nThis game works by presenting you with a room, then giving you the option to go"
"\n\nup (goes forward)\ndown (goes backward)\nleft\nright\n(all case sensitive)\n"
"\nOnce in a room, you will also have the option to SEARCH using the command"
"\n\nsearch (case sensitive)\n"
"\nWhen you SEARCH a room, you will be told if there is an ITEM or not."
"\nExample: (user enters room)"
"\nUser: search"
"\nConsole: You found... "
"\nsword"
"\nAt this point, you have the option to TAKE the ITEM from the room using the command"
"\n\ntake (case sensitive)\n"
"\nOnce you use the command to TAKE an ITEM, the item will be added to your inventory,"
"\nand to the total that you accumulate at the end of the game."
"\nThe objective of this game is to make as much money as possible from selling items,"
"\nso you might find that sometimes it's better to leave an ITEM behind, since you only have"
"\nFIVE INVENTORY SLOTS."
"\nOnce your inventory is full, the game automatically ends and totals up your profit."
"\nTo see how many inventory slots you have left, use the command"
"\n\n inven or inventory (case sensitive)\n"
"\nFinally,you have a default move limit of 15 moves. This makes it interesting to see what the maximum"
"\nprofit you can make is when limited like this. Do note that, depending on your character"
"\nchoices, you may have a higher move limit. "
"\nTo see how many moves you have left, use the command"
"\n\nmoves (case sensitive)\n"
"\nThe board will have a rooms connected in a random"
"\norder, so have fun with the good (or bad) luck you may recieve!";

std::vector<Room> roomItemList;
// using this set to take advantage of O(1) contains method
std::unordered_set<std::string> roomSet;
std::vector<Room> mapList = {
  Room("You enter a large room. It's dark, and the only source of light is a"
       "\nsingle sword in the middle of the room, sticking out of the ground."
       "\nThe sword gleams with runes and old spells; no doubt a powerful weapon.",
       "Ancient Rune-Inlaid Sword", 570),
  
  Room("You enter a small room that features a single desk."
       "\nOn top of the desk is a blank piece of paper.", "Dixon Pencil", 2),
  
  Room("You enter a medium-sized room with a single desk"
       "\nand chair inside it. On the desk is a piece of paper with only"
       "\none word written on it – 'THE'.", "Dixcon Ticonderoga Pencil", 20),
  
  Room("You enter a dark room lit by a single lightbulb. The lightbulb"
       "\nflickers unsteadily. It makes you uneasy."),
  
  Room("You enter a dark cavern lit to the sides by bubbling magma."
       "\nYou note that you should be careful not to get burnt.",
       "Precious Rock", 250),
  
  Room("You enter a room with a small hot spring in the middle of it."
       "\nYou briefly consider taking a break to soak in it, "
       "but decide otherwise."),
  
  Room("You enter a brightly lit room. It reminds you of the light they"
       "\nshine in your eyes at the dentist's office. It smells faintly of mint"
       "\nand mouthwash.", "Toothbrush", 1),
  
  Room("You enter what appears to be a kitchen, complete with a"
       "\npie baking in the oven. You wonder where the family who must"
       "\nlive here is."),
  
  Room("You enter an empty classroom. Lit by stark white lights, it's almost "
       "eerie how quiet it is. The pain of past students radiates into "
       "your soul.", "Cheat sheet for the final", 250),
  
  Room("You enter a nearly empty room. In the distance you hear someone"
       "\ntyping furiously on a keyboard. You look up and see a portrait"
       "\nof TechLead (as a millionaire)."),
  
  Room("You enter a room and find you have no weight. It looks like the set"
       "\nfor a movie, but you can see a lot of dust on the ground."
       "\nA piece of paper floats by – the script for what's being filmed."
       "\nYou catch a glimpse of what it says before it floats away:"
       "\nOne small step for man, one gi-.", "Minature Spaceship", 100),
  
  Room("You enter a vault. You open your phone and try to find your location,"
       "\nbut Siri can't help you here. Around you is thousands of discs,"
       "and the door to the vault is engraved with three numbers: 999.",
       "Go Hard, an Unreleased Song By Juice WRLD", 999),
  
  Room("You enter a room and discover a clumsy mage looking for her magical"
       "\nstaff. She seems to have misplaced it in this labrynth, and you hear"
       "\nher muttering things about explosions. You decide it would be best"
       "\nfor you to leave this room before she does something dangerous."),
  
  Room("You enter a pristine room, filled with figures of unknown origins."
       "\nOn a computer monitor you can see a show playing."
       "\nYou notice something locked in a safe, but the password is"
       "\nwritten on the wall.", "The Lost Episode for a Popular Show", 1000),

  Room("You enter a graveyard, late at night. Light shines on a single gravestone,"
       "\nBut you can't make out the name. However, there's a note left on the"
       "\ngrave that reads: I love you 3000. You don't dare disturb this site –"
       "\nit feels too important."),
  
  Room("You enter the back room of a Walmart. In the distance, you hear people"
       "\ncomplaining about their cancelled orders. You see a box poking out from"
       "\nunderneath a bench, obviously hid by a worker who wanted to"
       "\nclaim it for themselves.", "PlayStation 5", 499),
  
  Room("You enter a room that smells of skeletons. You can't"
       "\nexplain it, but you feel you sins crawling on your back."
       "\nA single blue light glows in the corner – it looks like"
       "\nan eye. You want to leave this room as soon as possible."),
  
  Room("You enter an extremely dark room, yet somehow you can see"
       "Everything in the room. On the wall seems to be an old spell written"
       "\nout. It begins 'Darkness darker than dark, blacker than black'.",
       "Unidentified magical staff", 780),
  
  Room("You enter a room with only two planks covering a pitfall."
       "\nYou note that you can't see the bottom of the pit, and when you're"
       "\nquiet, you swear you can hear voices coming from the pit. It makes"
       "\nyou feel like following them."),
  
  Room("You enter a room where the main attraction is a Tesla Cybertruck,"
       "\nthe window shattered and a steel ball on the floor. You hear faint voices,"
       "\nlikely someone being fired.", "A Scrap of Paper that Elon Musk Once "
       "Touched", 69),
  
  Room("You enter a room that features a desert. The temperature is well"
       "\nabove 120 degrees Farenheight, and you're parched instantly."
       "\nUnfortunately, you didn't bring any water with you, and nothing there"
       "\nis good enough to drink.", "A Bottle of Dasani Water", 0),
  
  Room("You enter a room lit from an unknown source. You see the"
       "\nMilky Way Galaxy off in the distance, and wonder where you are."
       "\nYou miss home, and want to get out of there."),
  
  Room("You enter a basement, lit by a flashing screen with two words"
       "\non it: Victory Royale. Upstairs you can hear a kid yelling at"
       "\ntheir mother, and shudder thinking of the beating you would've"
       "\ngotten for speaking like that when you were a child.",
       "Xbox Series X controller", 36),
  
  Room("But nobody came."),
  
  Room("You enter a room that smells of nostalgia. The scents of candy shops,"
       "\npizza, and cake fill the room. You see a selection of games"
       "\nin the corner, all for the Nintendo 3DS, and remember your"
       "\nchildhood.", "Super Smash Bros. For the Nintendo 3DS", 175)
};
// 2d vector representing the "map" for the user to explore
std::vector<std::vector<Room>> map;



int main() {
  init();
  gameplay();
  calculateScore();
  return 0;
}

/// Sets up all the important game details
void init() {
  srand((unsigned int) time(0)); // sets up the rng seed
  
  std::string input;
  std::cout << "Before we get into the adventure, we will need to create"
  " a character for you!\nThe only thing that really matters is your class"
  " and pet, but feel free to\ncustomize however you would like!\n"
  "To get started, please enter your name: ";
  std::getline(std::cin, name);
  
  if (name == "Megumin") {
    std::cout << "Ah, a true individual of culture... (2 moves added"
    " to move limit)\n";
    movesLeft += 2;
  } else {
    std::cout << name << "... Sounds kinda funny, but it'll do!\n";
  }
  
  std::cout << "Alright! Now it's time to choose your class.\n";
  
  while (true) {
    std::cout << "You can choose from:\n"
    "Knight (can tell the value of found items)\n"
    "Mage (add 3 moves to move limit)\n"
    "Enter your choice: ";
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if (input == "knight") {
      knight = true;
      break;
    } else if (input == "mage") {
      movesLeft += 3;
      mage = true;
      break;
    } else {
      std::cout << "That's not one of the classes, silly! "
      "Please try again...\n";
      continue;
    }
  }
  
  std::cout << "You chose to be a " << input << "!\n"
  "Now, let's choose your pet!\n";
  
  while (true) {
    std::cout << "Please from one of the following:\n"
    "Cat (searches rooms for you)\n"
    "Dog (increases backpack size by 1)\n"
    "Enter your pet choice: ";
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    if (input == "cat") {
      cat = true;
      break;
    } else if (input == "dog") {
      dog = true;
      backpackSize += 1;
      break;
    } else {
      std::cout << "That's not one of the pet options, silly! "
      "Please try again...\n";
      continue;
    }
  }
  
  std::cout << "Now, choose your pet's name: ";
  std::getline(std::cin, petName);
  if (petName == "Chomusuke" && cat) {
    std::cout << "Obviously the best cat name; +1 backpack slot!\n";
  }
  
  std::cout << "Alright, your pet " << input << " is named " <<
  petName << "!\n";
  
  // character overview
  std::cout << "Here's an overview of your details:\n"
  "Character name: " << name << std::endl;
  if (knight) {
    std::cout << "Class: Knight\n";
  }
  if (mage) {
    std::cout << "Class: Mage\n";
  }
  std::cout << "Pet name: " << petName << std::endl;
  if (cat) {
    std::cout << "Pet type: Cat\n";
  }
  if (dog) {
    std::cout << "Pet type: Dog\n";
  }
  
  // final setup
  movesLeft += 15;
  backpackSize += 5;
  mapShuffle2D();
  posRow = posCol = 2;
  
  std::cout << "Setup is complete!\n"
  "When you're ready to continue, press Enter...\n";
  std::cin.get();
}

/// Handles the gameplay loop
void gameplay() {
  std::cout << "Welcome to Dungeon Search, where the title is not final!"
  "\nIn this game, you will search rooms in a 5x5 map to find hidden treasures"
  "\nfor you to sell after a certain amount of moves (minimum of 15)." <<
  std::endl << instructions << std::endl <<
  "To see these instructions again at any time, use the command 'instructions'"
  " (case sensitive)." << std::endl << "Alright! In this game, you always start"
  " in the middle of the map (3,3)."
  "\nGood luck, and I hope you find some nice treasure!\n\n"
  "Press enter to begin." << std::endl;
  
  std::cin.get(); // should wait for the user to press enter
  
  while (movesLeft != -1) {
    if (roomItemList.size() == backpackSize) {
      std::cout << "Your backpack is full!"
      "\nLet's see what you collected...\n";
      break;
    } else {
      showMap();
      actionManager();
      movesLeft--;
    }
  }
  if (movesLeft == -1) {
    std::cout << "You're out of moves!"
    "\nLet's see what you collected...\n";
  }
}

/// Shows a visual representation of the user's position in the map.
void showMap() {
  for (int i = 0; i < map.size(); i++) {
    std::cout << std::endl;
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j].getContents() == map[posRow][posCol].getContents()) {
        std::cout << "[X]";
      } else {
        std::cout << "[ ]";
      }
    }
  }
  std::cout << std::endl;
}

/// Handles all user actions; has input verification.
void actionManager() {
  std::string input;
  bool searched = cat;
  
  std::cout << map[posRow][posCol].getContents() << std::endl;
  if (searched) {
    std::cout << "You found...\n" << map[posRow][posCol].getItem() <<
    std::endl;
    
    if (knight) {
      std::cout << "This item is worth $" <<
      map[posRow][posCol].getItemPrice() << std::endl;
    }
  }
  
  std::getline(std::cin, input);
  while (true) {
    // directional choices
    if (input == "up") {
      if (posRow != 0) {
        posRow--;
        break;
      } else {
        std::cout << "Sorry, you can't go this way! Try another direction.\n";
      }
    } else if (input == "down") {
      if (posRow != 4) {
        posRow++;
        break;
      } else {
        std::cout << "Sorry, you can't go this way! Try another direction.\n";
      }
    } else if (input == "left") {
      if (posCol != 0) {
        posCol--;
        break;
      } else {
        std::cout << "Sorry, you can't go this way! Try another direction.\n";
      }
    } else if (input == "right") {
      if (posCol != 4) {
        posCol++;
        break;
      } else {
        std::cout << "Sorry, you can't go this way! Try another direction.\n";
      }
      // extra choices
    } else if (input == "search") {
      std::cout << "You found...\n" << map[posRow][posCol].getItem() <<
      std::endl;
      
      searched = true;
      if (knight) {
        std::cout << "This item is worth $" <<
        map[posRow][posCol].getItemPrice() << std::endl;
      }
    } else if (input == "take") {
      bool taken = false;
      if (roomSet.find(map[posRow][posCol].getItem()) != roomSet.end()) {
        taken = true;
      }
      if (taken) {
        std::cout << "You already took all the items in this room!\n";
      } else if (!searched) {
        std::cout << "You must search the room before you can take it's items!\n";
      } else if (map[posRow][posCol].getItem() == "nothing") {
        std::cout << "You can't add nothing to your backpack, silly!\n";
      } else {
        roomItemList.push_back(map[posRow][posCol]);
        roomSet.insert(map[posRow][posCol].getItem());
        std::cout << "You added " << map[posRow][posCol].getItem() <<
        " to your backpack!\n";
        
        if (roomItemList.size() == backpackSize) {
          break;
        }
      }
    } else if (input == "instructions") {
      std::cout << instructions << std::endl <<
      "Please press Enter to return to the game.\n";
      std::cin.get();
      movesLeft++;
      return;
    } else if (input == "moves") {
      std::cout << "Moves left: " << movesLeft << std::endl;
    } else if (input == "inven" || input == "inventory") {
      std::cout << "Open inventory slots: " <<
      backpackSize - roomItemList.size() << std::endl;
    } else {
      std::cout << "Sorry, I don't recognize " << input <<
      "! Please try again.\nRemember, you can use the command 'instructions'\n"
      "to see all the moves you can make!\n";
    }
    std::getline(std::cin, input);
  }
}

/// Shows the user their final resullts (items sold, total money earned,
/// highest item sold)
void calculateScore() {
  int score = 0;
  int highestPrice = 0;
  std::string highestItem;
  
  // custom case for if the user doesn't collect anything to sell...
  if (roomItemList.size() == 0) {
    std::cout << "Sooo... you didn't collect anything. You realize that this\n"
    "wasn't a museum, right..? (Press Enter to continue)";
    std::cin.get();
    return;
  }
  
  // normal score calculation (the user collected at least one item)
  std::cout << "Here's your total summary:" << std::endl;
  for (int i = 0; i < roomItemList.size(); i++) {
    if (roomItemList[i].getItemPrice() > highestPrice) {
      highestPrice = roomItemList[i].getItemPrice();
      highestItem = roomItemList[i].getItem();
    }
    score += roomItemList[i].getItemPrice();
    
    std::cout << std::left << std::setw(50) << roomItemList[i].getItem() <<
    "\t$" << roomItemList[i].getItemPrice() << std::endl;
  }
  
  // show final results
  std::cout << "\nIn total, you sold: " << roomItemList.size() << " items, "
  "for a total of $" << score << "!\n";
  
  // show highest item sold
  std::cout << "The most expensive item you sold was the " << highestItem <<
  ", which sold for $" << highestPrice << std::endl;
}

/// Shuffles items from mapList and inserts it into the map
/// (gives the map randomly generated layouts).
void mapShuffle2D() {
  std::vector<Room> subVector;
  
  int rand;
  for (int i = 0; i < mapList.size(); i++) {
    rand = std::rand() % mapList.size();
    std::swap(mapList[i], mapList[rand]);
  }
  
  // add elements from mapList (1d vector) to map (2d vector)
  int offset = 0;
  for (int i = 0; i < 5; i++) { // 5 is the size of each subvector of the map
    for (int j = 0; j < 5; j++) {
      subVector.push_back(mapList[j+offset]);
    }
    map.push_back(subVector);
    subVector.clear();
    offset += 5;
  }
}
