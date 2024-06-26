#include "Game.h"

#include <iostream>
#include <sstream>
#include <fstream>


using std::string, std::vector, std::ifstream, std::istringstream, std::cout, std::cin, std::endl;

Game::Game() : players({}), suits({}), ranks({}), deck({}), drawPile({}), discardPile({}) {}

void Game::loadDeckFromFile(string filename) {
  ifstream infs(filename);
  if(!infs.is_open()){
    throw std::invalid_argument("bad file name!");
  }

  string line, suit, rank;
  getline(infs, line);

  if(line != ""){
    istringstream inss(line);
    while(inss.good()){
      inss >> suit;
      suits.push_back(suit);
    }
  }

  getline(infs, line);

  if(line != ""){
    istringstream inss(line);
    while(inss.good()){
      inss >> rank;
      ranks.push_back(rank);
    }
  }
  
  while(getline(infs, line)){
    line+=" ";
    if(line != ""){
      istringstream inss(line);
      inss >> rank >> suit;
      if(!inss.good()){
        throw std::runtime_error("bad card input!");
      }
      string temp;
      inss >> temp;
      if(!inss.eof()){
        throw std::runtime_error("bad card input! (extra text in line)");
      }
      bool rankvalid = false;
      for(int i = 0; i < (int)ranks.size(); i++){
        if(ranks[i] == rank){
          rankvalid = true;
          break;
        }
      }
      if(!rankvalid){
        throw std::runtime_error("bad rank!");
      }

      bool suitvalid = false;
      for(int i = 0; i < (int)suits.size(); i++){
        if(suits[i] == suit){
          suitvalid = true;
          break;
        }
      }
      if(!suitvalid){
        throw std::runtime_error("bad suit!");
      }

      try{
        Card *c = new Card(rank, suit);
        deck.push_back(c);
        drawPile.insert(drawPile.begin(), c);
      }
      catch(std::exception &e){
        throw std::runtime_error("card could not be created!");
      }
    }
  }
}


void Game::addPlayer(bool isAI){
  Player* p = new Player(isAI);
  players.push_back(p);
}

void Game::drawCard(Player* p) {
  // TODO: Move the top card of the draw pile to Player p's hand
  // If the draw pile is empty, flip the discard pile to create a new one
  
  if(!drawPile.empty()){
    p->addToHand(drawPile.back());
    drawPile.pop_back();
  }
  else{
    cout << "Draw pile, empty, flipping the discard pile." << endl;
    if(discardPile.empty()){
      throw std::runtime_error("both piles empty!");
    }

    while(!discardPile.empty()){
      drawPile.push_back(discardPile.back());
      discardPile.pop_back();
    }

    p->addToHand(drawPile.back());
    drawPile.pop_back();
  }
}

// deals numCards cards to each player
Card* Game::deal(int numCards) {
  Card * initialCard = drawPile.back();
  drawPile.pop_back();
  discardPile.push_back(initialCard);

  for(int i = 0; i < (int)numCards*players.size(); i++){
    drawCard(players.at(i%players.size()));
  }

  return initialCard;
}

string Game::mostPlayedSuit() {
  vector<int> suitCount(suits.size(), 0);
  for(Card* card: deck){ //looping thru every card
    for(int j = 0; j < (int)suits.size(); j++){ //looping thru suit
      if(card->getSuit() == suits[j]){ //only 
        suitCount[j]+=card->getTimesPlayed();
      }
    }
  }

  int max = suitCount[0];
  string maxSuit = suits[0];

  for(int i = 0; i < (int)suits.size(); i++){
    if(suitCount[i] > max){
      max = suitCount[i];
      maxSuit = suits[i];
    }
  }
  return maxSuit;
}

int Game::runGame() {

  string currRank = deck[0]->getRank();
  string currSuit = deck[0]->getSuit();
  int i = 0;
  while(true){
    cout << "Player " << i << "'s turn!" << endl;
    Card* playedCard = players[i]->playCard(suits, currRank, currSuit);
    if(playedCard != nullptr){ //if played did not draw
      if(playedCard->getRank() != "8"){
        cout << "Player " << i << " plays " << playedCard->getRank() << " " << playedCard->getSuit() << "." << endl;
      }
      else{
        cout << "Player " << i << " plays " << playedCard->getRank() << " " << playedCard->getSuit() << " and changes the suit to " << currSuit << "." << endl;
      }
      discardPile.push_back(playedCard);
    }
    else{
      try{
        drawCard(players[i]);
        cout << "Player " << i << " draws a card." << endl;
      }
      catch(std::exception &e){
        cout << "Player " << i << " cannot draw a card." << endl;
        return -1;
      }
    }

    if(players[i]->getHandSize() == 0){
      return i;
    }
    i++;
    i%=players.size();
  }
  cout << "exit??" << endl;
  return -2;
}

// Destructor--Deallocates all the dynamic memory we allocated
Game::~Game() {
  for (unsigned int i = 0; i < deck.size(); i++) {
    delete deck.at(i);
  }
  for (unsigned int i = 0; i < players.size(); i++) {
    delete players.at(i);
  }
}
