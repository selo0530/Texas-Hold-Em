#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include <cstring>
#include "Dealer.h"
#include "Player.h"
#include "User.h"
#include "Computer.h"
#include "Move.h"

using std::cout;
using std::cin;
using std::endl;


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


std::vector<Player*> Dealer::determineWinner(){
  std::vector<Player*> winners;
  std::vector<Player*>::iterator itr;
  int highestScore = 0;
  //Find the highest score
  for(itr = currentRound.begin(); itr != currentRound.end(); ++itr){
    if((*itr) != NULL){
      int score = scoreBestHand((**itr).hand);
      if(score >= highestScore){
        highestScore = score;
      }
    }
  }

  //Add all players with those hands to winners array
  for(itr = currentRound.begin(); itr != currentRound.end(); ++itr){
    if((*itr) != NULL){
      if(scoreBestHand((**itr).hand) == highestScore){
        winners.push_back(*itr);
      }
    }
  }
  return winners;
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

int Dealer::playersStillIn(std::vector<Player*> current){
  int count = 0;
  std::vector<Player*>::iterator itr;
  for(itr = current.begin(); itr != current.end(); ++itr){
    if(*itr != NULL){
      count++;
    }
  }
  return count;
}
