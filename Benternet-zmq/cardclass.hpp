#ifndef CARDCLASS_HPP
#define CARDCLASS_HPP
#include <string>

enum class CardSuit
{
    Hearts,
    Diamonds,
    Clubs,
    Spades
};

class CardClass
{
public:
    //CardClass();
    CardClass(int seed);
    CardSuit getSuit();
    int getValue();
    std::string outputCardString();
    std::string outputsuitString();
    static CardSuit getRandomSuit(int seed);
    static int getRandomValue(int seed);
private:
    CardSuit suit;
    int value;
};

#endif // CARDCLASS_HPP
