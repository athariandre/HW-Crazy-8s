#include <iostream>
#include <sstream>

#include "Player.h"

using std::vector, std::string, std::size_t, std::cout, std::endl, std::cin;

Player::Player(bool isAI) /* TODO: initialize */ {
  this->isAI = isAI;
}

void Player::addToHand(Card* c) {
  hand.push_back(c);
}

size_t Player::getHandSize() {
  return(hand.size());
}

std::string Player::getHandString() { //THIS IS THE ISSUE
  string handString = "";
  for(int i = 0; i < hand.size(); i++){
    if(i < hand.size()-1){
      handString += (hand[i]->getRank() + " " + hand[i]->getSuit() + ", ");
    }
    else{
      handString += (hand[i]->getRank() + " " + hand[i]->getSuit());
    }
  }
  handString += (hand[hand.size()-1]->getRank() + " " + hand[hand.size()-1]->getSuit());
  return(handString);
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
  // if(isAI){
  //   for(int i = 0; i < hand.size(); i++){
  //     if(hand[i]->canBePlayed(currentRank, currentSuit)){
  //       hand[i]->play();
  //       currentRank = hand[i]->getRank();
  //       currentSuit = hand[i]->getSuit();
  //       hand.erase(hand.begin() + i);
  //       return hand[i];
  //     }
  //   }
  //   return nullptr;
  // }
  // else{
  //   cout << "Your hand contains: " << getHandString() << endl;
  //   cout << "The next card played must be a " << currentRank << " or " << currentSuit << endl;
  //   cout << "What would you like to play? (enter \"draw card\" to draw a card)" << endl;

  //   string newRank, newSuit;
  //   while(false){
  //     cin >> newRank >> newSuit;
  //     if(newRank + newSuit == "drawcard"){
  //      return nullptr;
  //     }

  //     int i = 0;
  //     for(Card *c: hand){
  //       if(c->getRank() == newRank && c->getSuit() == newSuit){
  //         if(c->canBePlayed(currentRank, currentSuit)){  
  //           if(c->getRank() == "8"){
  //             cout << "What suit would you like to declare?" << endl;
  //             while(true){
  //               cin >> newSuit;
  //               for(string suit: suits){
  //                 if(suit == newSuit){
  //                   break;
  //                 }
  //               }
  //               cout << "That's not a suit in this deck. Try again." << endl;
  //             }
  //           }
  //           c->play();
  //           currentRank = newRank;
  //           currentSuit = newSuit;
  //           hand.erase(hand.begin() + i);
  //           return c;
  //         }
  //         cout << "You can't play that card. Try again." << endl;
  //         continue;
  //       }
  //       i++;
  //     }
  //     cout << "That's not a card you have. Try again." << endl;
  //   }
  // }
  
}