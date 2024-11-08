#include <algorithm>
#include <array>
#include <cmath>
#include <istream>
#include <sstream>
#include <vector>

#include "utils/input_helpers.h"
#include "utils/string_utils.h"
#include "utils/fileinput.h"

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

struct Card_b
{
    enum class Value
    {
        Jack,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Queen,
        King,
        Ace
    } value;

    auto operator<=>(const Card_b &other) const = default;
};

template <typename C>
std::istream &operator>>(std::istream &s, C &card)
{
    while (std::isspace(s.peek()))
        s.ignore();
    switch (s.get()) {
        case '2':
            card.value = C::Value::Two;
            break;
        case '3':
            card.value = C::Value::Three;
            break;
        case '4':
            card.value = C::Value::Four;
            break;
        case '5':
            card.value = C::Value::Five;
            break;
        case '6':
            card.value = C::Value::Six;
            break;
        case '7':
            card.value = C::Value::Seven;
            break;
        case '8':
            card.value = C::Value::Eight;
            break;
        case '9':
            card.value = C::Value::Nine;
            break;
        case 'T':
            card.value = C::Value::Ten;
            break;
        case 'J':
            card.value = C::Value::Jack;
            break;
        case 'Q':
            card.value = C::Value::Queen;
            break;
        case 'K':
            card.value = C::Value::King;
            break;
        case 'A':
            card.value = C::Value::Ace;
            break;
        default:
            s.setstate(std::ios_base::failbit);
            return s;
    }
    return s;
}

template <typename C>
struct Hand
{
    static constexpr std::size_t nCards = 5;
    std::array<C, nCards> cards;
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
        std::array<C, nCards> sorted_cards = cards;
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

    Type analyzeHand_b()
    {
        std::array<C, nCards> sorted_cards = cards;
        std::ranges::sort(sorted_cards, std::greater<>{});
        std::array<int64_t, nCards> freq = {1, 0, 0, 0, 0};
        auto it = freq.begin();
        auto jokers = (sorted_cards[0].value == C::Value::Jack ? 1 : 0);
        for (int i = 1; i < 5; ++i) {
            if (sorted_cards[i].value == C::Value::Jack) {
                jokers++;
                continue;
            }
            if (sorted_cards[i - 1] != sorted_cards[i])
                ++it;
            ++*it;
        }
        std::ranges::sort(freq, std::greater<>{});

        Type value = Type::FiveOfKind;
        // Map the frequencies to the hand type
        if (freq[0] == 5) {
            value = Type::FiveOfKind;
        } else if (freq[0] == 4) {
            if (jokers == 1)
                value = Type::FiveOfKind;
            else if (jokers == 0)
                value = Type::FourOfKind;

        } else if (freq[0] == 3 && freq[1] == 2) {
            value = Type::FullHouse;
        } else if (freq[0] == 3 && freq[1] != 2) {
            if (jokers == 2)
                value = Type::FiveOfKind;
            else if (jokers == 1)
                value = Type::FourOfKind;
            else if (jokers == 0)
                value = Type::ThreeOfKind;

        } else if (freq[0] == 2 && freq[1] == 2) {
            if (jokers == 1)
                value = Type::FullHouse;
            else if (jokers == 0)
                value = Type::TwoPair;

        } else if (freq[0] == 2 && freq[1] != 2) {
            if (jokers == 3)
                value = Type::FiveOfKind;
            else if (jokers == 2)
                value = Type::FourOfKind;
            else if (jokers == 1)
                value = Type::ThreeOfKind;
            else if (jokers == 0)
                value = Type::OnePair;

        } else {
            if (jokers >= 4)
                value = Type::FiveOfKind;
            else if (jokers == 3)
                value = Type::FourOfKind;
            else if (jokers == 2)
                value = Type::ThreeOfKind;
            else if (jokers == 1)
                value = Type::OnePair;
            else if (jokers == 0)
                value = Type::HighCard;
        }
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

template <typename C>
std::istream &operator>>(std::istream &s, Hand<C> &hand)
{
    for (auto i = 0u; i < Hand<C>::nCards; ++i) {
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

int main(int /*argc*/, char* argv[])
{
    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    std::string file_path = utils::getInputFilePath(argv[0], file);
    if (file_path.empty()) {
        std::cerr << "Error: Could not determine the input file path for " << file_path << ".\n";
        return 1;
    }

    int64_t part1 = 0;
    int64_t part2 = 0;
    std::vector<std::string> input = utils::getInput(file_path);

    {
        // part 1
        std::vector<Hand<Card>> hands;
        for (auto line : input) {
            Hand<Card> hand;
            std::stringstream ss(line);
            ss >> hand;
            hands.emplace_back(hand);
        }

        std::ranges::sort(hands, std::less<>{});

        for (auto idx = 0u; idx < hands.size(); ++idx) {
            part1 += (idx + 1) * hands[idx].bid;
        }
    }

    {
        // part 2
        std::vector<Hand<Card_b>> hands;
        for (auto line : input) {
            Hand<Card_b> hand;
            std::stringstream ss(line);
            ss >> hand;
            hands.emplace_back(hand);
        }

        auto update = [](Hand<Card_b> &hand) { hand.type = hand.analyzeHand_b(); };
        std::ranges::for_each(hands, update);
        std::ranges::sort(hands, std::less<>{});

        for (auto idx = 0u; idx < hands.size(); ++idx) {
            part2 += (idx + 1) * hands[idx].bid;
        }
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
}
