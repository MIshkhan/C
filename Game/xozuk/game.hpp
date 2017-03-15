#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

class game {
public:
  void start();
private:
  struct player {
    int turn;
  };
  player current_player;
  vector<int> myCards;
  vector<int> compCards;
  
  static const char* address;
  
  void printInfo() const;
  vector<int> getShuffledCards() const;
  vector<int> getCardsFromDeck() const;
  vector<int> getCardsFromBoard() const;
  void input_card_on_page(int, int, int, vector<string>&) const;
  vector<string> get_page_with_cards(const vector<int>&) const;
  vector<int> get_hidden_cards(const vector<int>&) const;
  void updateCards(const vector<int>&, const vector<int>&, int);
  void print_page(const vector<string>&) const;
  void clean_page(vector<string>&);
  void move_card_up(vector<string>&, int, int) const;
  void move_card_down(vector<string>&,int,int) const;
  int print_moveable_page(const string&, const vector<int>&, 
                          const string&, const vector<int>&, 
                          const string&, const vector<int>&) const;
  void chooseCardForComp();
  void chooseCard();
  bool isGameOver() const;
};

#endif
