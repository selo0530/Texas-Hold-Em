#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <assert.h>
#include "Dealer.h"
#include "Player.h"
#include "User.h"
#include "Computer.h"
#include "Move.h"

using std::cout;
using std::cin;
using std::endl;

Dealer::Dealer(){
  numPlayers = 6;
  User* user = new User(500);
  players.push_back(user);
  for(int i = 1; i < numPlayers; i++){
    players.push_back(new Computer(500));
  }

  std::vector<Player*>::iterator pitr;


  int pointerOffset = 0;
  smallBlindHolderIndex = 0;
  //Game loop
  /*
  while(userStillAlive(*user)){
    //Fill and shuffle the deck before each hand
    deck.fill();
    deck.shuffle();

    //Kill all the players that can't make large blind
    for(pitr = players.begin(); pitr != players.end(); ++pitr){
      if((**pitr).wallet < largeBlind){
        (*pitr) = NULL; //GET NULLIFIED
        numPlayers--;
      }
    }

    if(numPlayers == 1){
      //Game Over, you win
    }

    //Clear out each user's hand, then deal them a new one
    for(pitr = players.begin(); pitr != players.end(); ++pitr){
      if((*pitr) != NULL){
        (**pitr).hand.clear();
      }
    }

    for(int i = 0; i < 2; i++){
      for(pitr = players.begin(); pitr != players.end(); ++pitr){
        if((*pitr) != NULL){
          (**pitr).hand.push_back(deck.dealCard());
        }
      }
    }

    //Resetting things between rounds
    betValue = largeBlind;
    pot = 0;
    smallBlindHolderIndex = (smallBlindHolderIndex + 1) % numPlayers;

    if(players[smallBlindHolderIndex]->wallet > smallBlind){
      players[smallBlindHolderIndex]->wallet -= smallBlind;
    }else{
    }
    roundOfBetting(2);

    dealFlop();

    roundOfBetting(0);

    dealTurn();

    roundOfBetting(0);
    dealRiver();

    roundOfBetting(0);
    determineWinner();
  }
  */
  cout << "User has left/lost the game." << endl;

}

void Dealer::dealFlop(){
  cout << "Dealing the flop." << endl;
  for(int i = 0; i < 3; i++){
    community.push_back(deck.dealCard());
  }
  cout << "Community cards: " << Deck::displayHand(community) << endl;
}

void Dealer::dealTurn(){
  cout << "Dealing the turn." << endl;
  community.push_back(deck.dealCard());
  cout << "Community cards: " << Deck::displayHand(community) << endl;
}

void Dealer::dealRiver(){
  cout << "Dealing the river." << endl;
  community.push_back(deck.dealCard());
  cout << "Community cards: " << Deck::displayHand(community) << endl;
}

void Dealer::roundOfBetting(int handOffset){
  cout << "Commence betting." << endl;
  //All set if nobody has raised, means everyone has folded or checked
  bool allSet;
  int playerPos;
  //Start by setting everyone's contribution to the pot to zero
  std::vector<Player*>::iterator pitr;
  for(pitr = players.begin(); pitr != players.end(); ++pitr){
    (**pitr).currentContribution = 0;
  }

  while(!allSet){
    cout << "Pot: $" << pot << " Bet: " << betValue << endl;
    allSet = true;
    for(int i = ((smallBlindHolderIndex + handOffset) % players.size()); i != ((smallBlindHolderIndex+handOffset-1) % players.size()); i = ((i + 1) % players.size())){
      if(players[i] != NULL){
        Player* player = players[i];
        Move move = player->getMove(this);
        if(move == RAISE){
          //The amount they spend is the amount they need to add to match the current bet, plus their raise
          int raise = player->getAmountForMove(this);
          int amount = (betValue - player->currentContribution) + raise;
          if(amount <= player->wallet){ //If they have enough money to do this
            betValue += raise;
            player->wallet -= amount;
            pot += amount;
          }
          allSet = false;
        }else if(move == CALL){
          int amount = betValue - player->currentContribution;
          if(amount < player->wallet){
            player->wallet -= amount;
            pot += amount;
          }
        }else if(move == FOLD){
          //Kick them out of this round
        }else if(move == ALLIN){
          int amount = player->wallet;

        }else{
          assert(false);
        }

      }
    }
  }
}

bool Dealer::userStillAlive(User user){
  //First player is user, smallBlind*2 is large blind
  return user.wallet > smallBlind*2;
}
//A royal flush is just a straight flush from 10-ACE
bool Dealer::royalFlush(std::vector<Card> hand){
  return straightFlush(hand) && highestValue(hand) == ACE;
}

//A straight flush is just a straight and a flush
bool Dealer::straightFlush(std::vector<Card> hand){
  return straight(hand) && flush(hand); }

  bool Dealer::fourOfAKind(std::vector<Card> hand){
    //Map from Card value to the number of those cards you have
    std::map<Value, int> cardCounts;

    //Iterate over cards and initialize the map to zero at those values
    std::vector<Card>::iterator itr;
    for(itr = hand.begin(); itr != hand.end(); ++itr){
      cardCounts[(*itr).value] = 0;
    }

    //Iterate over the cards again and increment the count at that value
    for(itr = hand.begin(); itr != hand.end(); ++itr){
      cardCounts[(*itr).value]++;
    }

    //Iterate through the map and look for a count of 4
    std::map<Value,int>::iterator mitr;
    for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
      if((*mitr).second == 4){
        return true;
      }
    }
    return false;
  }

Value Dealer::valueOfFourOfAKind(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 4){
      return (*mitr).first;
    }
  }
  //Should never reach this, method only called once 4 of a kind exists
  return TWO;
}

bool Dealer::fullHouse(std::vector<Card> hand){
  return threeOfAKind(hand) && pair(hand);
}

bool Dealer::flush(std::vector<Card> hand){
  Suit target = hand.front().suit;

  //Iterate over cards and see if they all have the same sui
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    if((*itr).suit != target){
      return false;
    }
  }
  return true;
}

bool Dealer::straight(std::vector<Card> hand){
  std::sort(hand.begin(),hand.end());
  Value lowest = hand.front().value;
  Value previous = lowest;
  //Iterate starting with the second card
  std::vector<Card>::iterator itr;
  for(itr = hand.begin()+1; itr != hand.end(); ++itr){
    //Those final conditions handle ACE as a low value
    if(((*itr).value - previous) != 1 && !(previous == FIVE && (*itr).value == ACE)){
      return false;
    }else {
      previous = (*itr).value;
    }
  }
  return true;
}

bool Dealer::threeOfAKind(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 3){
      return true;
    }
  }
  return false;
}

Value Dealer::valueOfThreeOfAKind(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 3){
      return (*mitr).first;
    }
  }
  //Should never reach this, method only called once 3 of a kind exists
  return TWO;
}

bool Dealer::twoPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  int numPairs = 0;
  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2){
      numPairs++;
    }
  }
  return numPairs == 2;
}

Value Dealer::higherPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  int numPairs = 0;
  Value highestValue = TWO;
  //Iterate through the map and look for a count of 2
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2 && (*mitr).first > highestValue){
      highestValue = (*mitr).first;
    }
  }
  return highestValue;
}

Value Dealer::lowerPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  Value lowestValue = ACE;
  //Iterate through the map and look for a count of 2
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2 && (*mitr).first < lowestValue){
      lowestValue = (*mitr).first;
    }
  }
  return lowestValue;
}

bool Dealer::pair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  int numPairs = 0;
  //Iterate through the map and look for a count of 4
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2){
      numPairs++;
    }
  }
  return numPairs == 1;
}

Value Dealer::valueOfPair(std::vector<Card> hand){
  //Map from Card value to the number of those cards you have
  std::map<Value, int> cardCounts;

  //Iterate over cards and initialize the map to zero at those values
  std::vector<Card>::iterator itr;
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value] = 0;
  }

  //Iterate over the cards again and increment the count at that value
  for(itr = hand.begin(); itr != hand.end(); ++itr){
    cardCounts[(*itr).value]++;
  }

  //Iterate through the map and look for a count of 2
  std::map<Value,int>::iterator mitr;
  for(mitr = cardCounts.begin(); mitr!=cardCounts.end(); ++mitr){
    if((*mitr).second == 2){
      return (*mitr).first;
    }
  }
  //Should never reach this, method only called once 3 of a kind exists
  return TWO;
}

Value Dealer::highestValue(std::vector<Card> hand){
  std::sort(hand.begin(),hand.end());
  return hand.back().value;
}

int Dealer::scoreHand(std::vector<Card> hand){
  int primary = 0;
  int secondary = 0;
  int tertiary = 0;
  if(Dealer::royalFlush(hand)){
    primary = 9;
    secondary = 0;
    tertiary = 0;
  }
  else if(Dealer::straightFlush(hand)){
    primary = 8;
    secondary = highestValue(hand);
    tertiary = 0;
  }
  else if(Dealer::fourOfAKind(hand)){
    primary = 7;
    secondary = valueOfFourOfAKind(hand);
    tertiary = 0;  //Impossible in texas hold'em
  }
  else if(Dealer::fullHouse(hand)){
    primary = 6;
    secondary = valueOfThreeOfAKind(hand);
    tertiary = valueOfPair(hand);
  }
  else if(Dealer::flush(hand)){
    primary = 5;
    secondary = highestValue(hand);
    tertiary = 0; //Tie
  }
  else if(Dealer::straight(hand)){
    primary = 4;
    secondary = highestValue(hand);
    tertiary = 0; //Tie
  }
  else if(Dealer::threeOfAKind(hand)){
    primary = 3;
    secondary = valueOfThreeOfAKind(hand);
    tertiary = highestValue(hand);
  }
  else if(Dealer::twoPair(hand)){
    primary = 2;
    secondary = higherPair(hand);
    tertiary = lowerPair(hand);
  }
  else if(Dealer::pair(hand)){
    primary = 1;
    secondary = valueOfPair(hand);
    tertiary = highestValue(hand);
  }
  else{//High card
    primary = 0;
    secondary = highestValue(hand);
    tertiary = 0;
  }
  //Unique hand score, weighted by characteristic importance
  return primary*10000+secondary*100+tertiary;
}

int Dealer::scoreBestHand(std::vector<Card> hand){
  std::vector<Card> moreThanFiveCardHand;
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), hand.begin(), hand.end());
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), community.begin(), community.end());
  int index1 = 0;
  int index2 = 0;
  int highestScore = 0;
  if(moreThanFiveCardHand.size() == 7){
    for(int i = 0; i < 21; i++){
      int score = scoreHand(fiveCardHand(moreThanFiveCardHand,index1,index2));
      if(score > highestScore){
        highestScore = score;
      }
      if(index2 == 6){
        index1++;
        index2 = index1+1;
      }else{
        index2++;
      }
    }
  }else{  //Six card hand
    for(int i = 0; i < 6; i++){
      int score = scoreHand(fiveCardHand(moreThanFiveCardHand,i,-1));
      if(score > highestScore){
        highestScore = score;
      }
    }
  }
  return highestScore;
}

std::vector<Card> Dealer::bestHand(std::vector<Card> hand){
  std::vector<Card> moreThanFiveCardHand;
  std::vector<Card> highestHand;
  std::vector<Card> tempHand;
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), hand.begin(), hand.end());
  moreThanFiveCardHand.insert(moreThanFiveCardHand.end(), community.begin(), community.end());
  int index1 = 0;
  int index2 = 0;
  int highestScore = 0;
  if(moreThanFiveCardHand.size() == 7){
    for(int i = 0; i < 21; i++){
      tempHand = fiveCardHand(moreThanFiveCardHand,index1,index2);
      int score = scoreHand(tempHand);
      if(score > highestScore){
        highestScore = score;
        highestHand = tempHand;
      }
      if(index2 == 6){
        index1++;
        index2 = index1+1;
      }else{
        index2++;
      }
    }
  }else{  //Six card hand
    for(int i = 0; i < 6; i++){
      tempHand = fiveCardHand(moreThanFiveCardHand,i,-1);
      int score = scoreHand(tempHand);
      if(score > highestScore){
        highestScore = score;
        highestHand = tempHand;
      }
    }
  }
  return highestHand;
}


Player* Dealer::determineWinner(){
  return NULL;
}

std::vector<Card> Dealer::fiveCardHand(std::vector<Card> largeHand, int i1, int i2){
  std::vector<Card> newHand;
  int length = largeHand.size();
  for(int i = 0; i < length; i++){
    if(i != i1 && i != i2){
      newHand.push_back(largeHand[i]);
    }
  }
  return newHand;
}
