#include <iostream>
#include <sstream>

#include "Player.h"

using std::vector, std::string, std::size_t, std::cout;

Player::Player(bool isAI) /* TODO: initialize */ {
  this->isAI = isAI;
}

void Player::addToHand(Card* c) {
  hand.push_back(c);
}

size_t Player::getHandSize() {
  return(hand.size());
}

std::string Player::getHandString() {
  for(int i = 0; i < hand.size()-1; i++){
    Card c = *hand.at(i);
    cout << c.getRank() << " " << c.getSuit() << ", ";
  }
  Card c = *hand.at(hand.size()-1);
  cout << c.getRank() << " " << c.getSuit();
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
  if(isAI){
    for(int i = 0; i < hand.size(); i++){
      Card c = *hand.at(i);
      if(c.canBePlayed(currentRank, currentSuit)){
        c.play();
        currentRank = c.getRank();
        currentSuit = c.getSuit();
        
      }
    }
  }
}