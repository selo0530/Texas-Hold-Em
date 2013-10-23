#include <algorithm>
#include "Deck.h"
#include "Card.h"
#include "SuitValue.h"

using namespace std;

Deck::Deck(){
  for(int i = 0; i < 52; i++){
    Suit s = Card::suitFromInt(i/4);
    Value v = Card::valueFromInt(i % 14);
    cards.push_back(Card(s,v));
  }
}

Deck::~Deck(){}

void Deck::shuffle(){
  random_shuffle(cards.begin(),cards.end());
}

