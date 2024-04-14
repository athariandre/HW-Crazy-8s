#include <iostream>

#include "Card.h"

using std::string;

Card::Card(string rank, string suit) /* TODO: initialize */ {

    if(rank == "" || suit == ""){
      throw std::invalid_argument("rank and/or suit is empty!");
    }

    for(char c: rank){
      if(!std::isalnum(c)){
        throw std::invalid_argument("rank is not alphanumeric!");
      }
    }
    for(char c: suit){
      if(!std::isalnum(c)){
        throw std::invalid_argument("suit is not alphanumeric!");
      }
    }
  }


string Card::getRank() {
  return rank;
}

string Card::getSuit() {
  return suit;
}

int Card::getTimesPlayed() {
  return timesPlayed;
}

bool Card::canBePlayed(string currentRank, string currentSuit) {
  if(currentRank == "8"){
    return true;
  }
  else if(currentRank == rank || currentSuit == suit){
    return true;
  }
  return false;
}

void Card::play() {
  timesPlayed++;
}
