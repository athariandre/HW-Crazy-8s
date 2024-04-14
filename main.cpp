#include <iostream>
#include <string>

#include "Card.h"
#include "Game.h"
#include "Player.h"

using std::string, std::cout, std::endl, std::cin;

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

  cout << "line 1" << endl;
  std::vector<Card*> list;
  cout << "line 2" << endl;
    string suit;
    cout << "line 3" << endl;
    suit = "Hearts";
    cout << "line 4" << endl;
    Player p = new Player(false);
    cout << "line 5" << endl;
    for(int i = 1; i > 11; i++){
        cout << "line 6" << endl;
        Card *c = new Card(std::to_string(i), suit);
        cout << "line 7" << endl;
        p.addToHand(c);
        cout << "line 8" << endl;
    }
    cout << "line 9" << endl;
    cout << p.getHandSize() << endl;
    cout << "line 10" << endl;
    cout << " " << p.getHandString() << " " << endl;


  return 0;
}