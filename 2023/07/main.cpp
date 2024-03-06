#include <algorithm>
#include <array>
#include <cmath>
#include <istream>
#include <sstream>
#include <vector>

#include "input_helpers.h"
#include "string_utils.h"

struct Card
{
    enum class Value
    {
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King,
        Ace
    } value;

    auto operator<=>(const Card &other) const = default;
};

std::istream &operator>>(std::istream &s, Card &card)
{
    while (std::isspace(s.peek()))
        s.ignore();
    switch (s.get()) {
        case '2':
            card.value = Card::Value::Two;
            break;
        case '3':
            card.value = Card::Value::Three;
            break;
        case '4':
            card.value = Card::Value::Four;
            break;
        case '5':
            card.value = Card::Value::Five;
            break;
        case '6':
            card.value = Card::Value::Six;
            break;
        case '7':
            card.value = Card::Value::Seven;
            break;
        case '8':
            card.value = Card::Value::Eight;
            break;
        case '9':
            card.value = Card::Value::Nine;
            break;
        case 'T':
            card.value = Card::Value::Ten;
            break;
        case 'J':
            card.value = Card::Value::Jack;
            break;
        case 'Q':
            card.value = Card::Value::Queen;
            break;
        case 'K':
            card.value = Card::Value::King;
            break;
        case 'A':
            card.value = Card::Value::Ace;
            break;
        default:
            s.setstate(std::ios_base::failbit);
            return s;
    }
    return s;
}

struct Hand
{
    static constexpr std::size_t nCards = 5;
    std::array<Card, nCards> cards;
    uint64_t bid{0};

    enum class Type
    {
        HighCard,
        OnePair,
        TwoPair,
        ThreeOfKind,
        FullHouse,
        FourOfKind,
        FiveOfKind
    } type;

    Type analyzeHand()
    {
        std::array<Card, nCards> sorted_cards = cards;
        std::ranges::sort(sorted_cards, std::greater<>{});
        std::array<int64_t, nCards> freq = {1, 0, 0, 0, 0};
        auto it = freq.begin();
        for (int i = 1; i < 5; ++i) {
            if (sorted_cards[i - 1] != sorted_cards[i])
                ++it;
            ++*it;
        }
        std::ranges::sort(freq, std::greater<>{});

        Type value;
        // Map the frequencies to the hand type
        if (freq[0] == 5)
            value = Type::FiveOfKind;
        else if (freq[0] == 4)
            value = Type::FourOfKind;
        else if (freq[0] == 3 && freq[1] == 2)
            value = Type::FullHouse;
        else if (freq[0] == 3 && freq[1] != 2)
            value = Type::ThreeOfKind;
        else if (freq[0] == 2 && freq[1] == 2)
            value = Type::TwoPair;
        else if (freq[0] == 2 && freq[1] != 2)
            value = Type::OnePair;
        else
            value = Type::HighCard;
        return value;
    }

    auto operator<=>(const Hand &other) const
    {
        // First compare by the hand value
        auto cmp = type <=> other.type;
        if (std::is_neq(cmp))
            return cmp;
        // If the hands are the same, lexicographically compare the cards
        return cards <=> other.cards;
    }
};

std::istream &operator>>(std::istream &s, Hand &hand)
{
    for (auto i = 0u; i < Hand::nCards; ++i) {
        if (!(s >> hand.cards[i])) {
            return s;
        }
    }
    if (!(s >> hand.bid)) {
        return s;
    }
    hand.type = hand.analyzeHand();

    return s;
}

int main()
{
    int64_t part1 = 0;
    int64_t part2 = 0;

    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    std::vector<std::string> input = utils::getInput(file);
    std::vector<Hand> hands;
    for (auto line : input) {
        Hand hand;
        std::stringstream ss(line);
        ss >> hand;
        hands.emplace_back(hand);
    }

    {
        // part 1
        std::ranges::sort(hands, std::less<>{});
        
        for(auto idx = 0u; idx < hands.size(); ++idx) {
            part1 += (idx+1) * hands[idx].bid;
        }
    }

    {
        // part 2
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
}
