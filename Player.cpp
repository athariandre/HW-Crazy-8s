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
  string handString = "";
  for(int i = 0; i < hand.size()-1; i++){
    handString += (hand[i]->getRank() + " " + hand[i]->getSuit() + ", ");
  }
  handString += (hand[hand.size()-1]->getRank() + " " + hand[hand.size()-1]->getSuit());
  return(handString);
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
  if(isAI){
    for(int i = 0; i < hand.size(); i++){
      if(hand[i]->canBePlayed(currentRank, currentSuit)){
        hand[i]->play();
        currentRank = hand[i]->getRank();
        currentSuit = hand[i]->getSuit();
        hand.erase(hand.begin() + i);
        return hand[i];
      }
      return nullptr;
    }
  }
  return(nullptr);
  }