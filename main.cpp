#include <iostream>
#include <string>

#include "Card.h"
#include "Game.h"
#include "Player.h"

using std::string, std::cout, std::endl, std::cin, std::vector;

bool loadDeck(Game& g) {
  string filename;
  std::cout << "Choose a file to load the deck from:" << std::endl;
  std::cin >> filename;
  try {
    g.loadDeckFromFile(filename);
  } catch (std::invalid_argument const&) {
    std::cout << "The file was invalid. Aborting." << std::endl;
    return false;
  }
  return true;
}

int getPlayerCount() {
  std::cout << "Enter number of players:" << std::endl;
  int numPlayers;
  while (true) {
    if ((!(std::cin >> numPlayers)) || numPlayers <= 0) {
      if (std::cin.fail()) {
        // Clear the fail flag
        std::cin.clear();
        // Remove the non-integer data from the stream
        string garbage;
        std::cin >> garbage;
      }
      std::cout << "Please enter a positive number" << std::endl;
    } else {
      // break out of the loop once we've read a valid number
      break;
    }
  }
  return numPlayers;
}

void setupPlayers(Game& g, int numPlayers) {
  // TODO: Determine whether each player is a human or an AI
  // and add them to the game
}

void setupGame(Game& g) {
  // TODO: Determine how many cards to deal, deal the cards, and
  // print the initial discard
}

int main() {
  // Game g;
  // if (!loadDeck(g)) {
  //   return 1;
  // }
  // int numPlayers = getPlayerCount();
  // setupPlayers(g, numPlayers);
  // setupGame(g);
  // int winner = g.runGame();
  // if (winner != -1) {
  //   std::cout << "Player " << winner << " wins!" << std::endl;
  // } else {
  //   std::cout << "The game is a draw!" << std::endl;
  // }
  // std::cout << "The most played suit was " << g.mostPlayedSuit() << std::endl;


    Player p = Player(false);
    for(int i = 1; i < 11; i++){
      Card *c = new Card(std::to_string(i), "Hearts");
      p.addToHand(c);
    }
    Card *c = new Card("8", "Spades");
    p.addToHand(c);
    c = new Card("2", "Spades");
    p.addToHand(c);


    const vector<string> suits = {"Hearts", "Spades"};
    string rank1 = "3";
    string suit1 = "Hearts";
    while(true){
      p.playCard(suits, rank1, suit1);
    }
    return 0;
}