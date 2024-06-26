#include <iostream>
#include <sstream>

#include "Player.h"

using std::vector, std::string, std::size_t, std::cout, std::endl, std::cin;

Player::Player(bool isAI) /* TODO: initialize */ {
  this->isAI = isAI;
  this->hand = {};
}

void Player::addToHand(Card* c) {
  hand.push_back(c);
}

size_t Player::getHandSize() {
  return(hand.size());
}

std::string Player::getHandString() { 
  string handString = "";
  for(int i = 0; i < hand.size(); i++){
    if(i < hand.size()-1){
      handString += (hand[i]->getRank() + " " + hand[i]->getSuit() + ", ");
    }
    else{
      handString += (hand[i]->getRank() + " " + hand[i]->getSuit());
    }
  }
  return(handString);
}

Card* Player::playCard(vector<string> const& suits, string& currentRank, string& currentSuit) {
  if(isAI){
    for(int i = 0; i < hand.size(); i++){
      if(hand[i]->canBePlayed(currentRank, currentSuit)){
        hand[i]->play();
        currentRank = hand[i]->getRank();
        currentSuit = hand[i]->getSuit();
        Card* temp = hand[i];
        hand.erase(hand.begin() + i);
        return temp;
      }
    }
    return nullptr;
  }
  else{
    cout << "Your hand contains: " << getHandString() << endl;
    cout << "The next card played must be a " << currentRank << " or " << currentSuit << endl;
    cout << "What would you like to play? (enter \"draw card\" to draw a card)" << endl;

    string newRank, newSuit;
    while(true){
      cin >> newRank >> newSuit;

      if(newRank + newSuit == "drawcard"){
       return nullptr;
      }
      bool cardunplayable = false;
      for(int i = 0; i < hand.size(); i++){ //checking for match within hand
        if(hand[i]->getRank() == newRank && hand[i]->getSuit() == newSuit){ //if card exists in hand
          if(hand[i]->canBePlayed(currentRank, currentSuit)){   //if card exists and can be played
            if(hand[i]->getRank() == "8"){ //if card is eight, pick new suit first
              cout << "What suit would you like to declare?" << endl;
              bool suitChanged = false;
              while(!suitChanged){
                cin >> newSuit;
                for(int i = 0; i < suits.size(); i++){
                  if(suits[i] == newSuit){
                    suitChanged = true;
                    break;
                  }
                }
                if(suitChanged){
                  break;
                }
                cout << "That's not a suit in this deck. Try again." << endl;
              }
            }
            hand[i]->play();
            currentRank = newRank;
            currentSuit = newSuit;
            Card* temp = hand[i];
            hand.erase(hand.begin() + i);
            return temp;
          }
          else{ //if card exists but cannot be played
            cardunplayable = true;
            cout << "You can't play that card. Try again." << endl;
            break;
          }
        }
      }
      if(!cardunplayable){
        cout << "That's not a card you have. Try again." << endl;
      }
    }
  }
  
}