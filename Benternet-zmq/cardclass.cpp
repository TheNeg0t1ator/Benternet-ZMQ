#include "cardclass.hpp"
#include <cstdlib>

int CardClass::getRandomValue(int seed) {
    srand(seed);
    return rand() % 13 + 1;
}

CardSuit CardClass::getRandomSuit(int seed) {
    srand(seed);
    return static_cast<CardSuit>(rand() % 4);
}

CardClass::CardClass(int seed) {
    int seed1, seed2;
    srand(seed);
    seed1 = rand();
    seed2 = rand()+1%1000;
    suit = getRandomSuit(seed1);
    value = getRandomValue(seed2);
}

CardSuit CardClass::getSuit() {
    return suit;
}

int CardClass::getValue() {
    return value;
}

std::string CardClass::outputCardString() {
    std::string suitString =  outputsuitString();
    return suitString + " " + std::to_string(value);
}

std::string CardClass::outputsuitString() {
    std::string suitString;
    switch (suit) {
    case CardSuit::Hearts:
        suitString = "Hearts";
        break;
    case CardSuit::Diamonds:
        suitString = "Diamonds";
        break;
    case CardSuit::Clubs:
        suitString = "Clubs";
        break;
    case CardSuit::Spades:
        suitString = "Spades";
        break;
    }
    return suitString;
}
