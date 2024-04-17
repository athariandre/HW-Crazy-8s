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
      if(inss.eof()){
        throw std::invalid_argument("bad card input!");
      }
      string temp;
      inss >> temp;
      if(!inss.eof()){
        throw std::invalid_argument("bad card input! (extra text in line)");
      }
      bool rankvalid = false;
      for(int i = 0; i < ranks.size(); i++){
        if(ranks[i] == rank){
          rankvalid = true;
          break;
        }
      }
      if(!rankvalid){
        throw std::invalid_argument("bad rank!");
      }

      bool suitvalid = false;
      for(int i = 0; i < suits.size(); i++){
        if(suits[i] == suit){
          suitvalid = true;
          break;
        }
      }
      if(!suitvalid){
        throw std::invalid_argument("bad suit!");
      }

      try{
        Card *c = new Card(rank, suit);
        deck.push_back(c);
        drawPile.insert(drawPile.begin(), c);
      }
      catch(std::exception &e){
        throw e;
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
    if(discardPile.empty()){
      throw std::invalid_argument("both piles empty!");
    }
    cout << "Draw pile, empty, flipping the discard pile." << endl;
    for(int i = discardPile.size()-1; i >= 0; i--){
      drawPile.push_back(discardPile[i]);
      discardPile.pop_back();
    }

  }
}

// deals numCards cards to each player
Card* Game::deal(int numCards) {
  // TODO: Flip the top card of the draw pile to be the initial discard
  // then deal numCards many cards to each player
  return nullptr;
}

string Game::mostPlayedSuit() {
  // TODO: Return the suit which has been played the most times
  // if there is a tie, choose any of the tied suits
  return "";
}

int Game::runGame() {
  // TODO: Run the game and return the number of the winning player
  return 1;
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
