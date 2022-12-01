#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <map>
#include <numeric>
#include <bitset>

#include "string_utils.h"

namespace fs = std::filesystem;

namespace puzzleInput
{
  constexpr std::string_view input1 = "9C0141080250320F1802104A08";
  constexpr std::string_view input = "E0529D18025800ABCA6996534CB22E4C00FB48E233BAEC947A8AA010CE1249DB51A02CC7DB67EF33D4002AE6ACDC40101CF0449AE4D9E4C071802D400F84BD21CAF3C8F2C35295EF3E0A600848F77893360066C200F476841040401C88908A19B001FD35CCF0B40012992AC81E3B980553659366736653A931018027C87332011E2771FFC3CEEC0630A80126007B0152E2005280186004101060C03C0200DA66006B8018200538012C01F3300660401433801A6007380132DD993100A4DC01AB0803B1FE2343500042E24C338B33F5852C3E002749803B0422EC782004221A41A8CE600EC2F8F11FD0037196CF19A67AA926892D2C643675A0C013C00CC0401F82F1BA168803510E3942E969C389C40193CFD27C32E005F271CE4B95906C151003A7BD229300362D1802727056C00556769101921F200AC74015960E97EC3F2D03C2430046C0119A3E9A3F95FD3AFE40132CEC52F4017995D9993A90060729EFCA52D3168021223F2236600ECC874E10CC1F9802F3A71C00964EC46E6580402291FE59E0FCF2B4EC31C9C7A6860094B2C4D2E880592F1AD7782992D204A82C954EA5A52E8030064D02A6C1E4EA852FE83D49CB4AE4020CD80272D3B4AA552D3B4AA5B356F77BF1630056C0119FF16C5192901CEDFB77A200E9E65EAC01693C0BCA76FEBE73487CC64DEC804659274A00CDC401F8B51CE3F8803B05217C2E40041A72E2516A663F119AC72250A00F44A98893C453005E57415A00BCD5F1DD66F3448D2600AC66F005246500C9194039C01986B317CDB10890C94BF68E6DF950C0802B09496E8A3600BCB15CA44425279539B089EB7774DDA33642012DA6B1E15B005C0010C8C917A2B880391160944D30074401D845172180803D1AA3045F00042630C5B866200CC2A9A5091C43BBD964D7F5D8914B46F040";
}

enum TypeId : uint8_t
{
  SUM = 0x00,
  PRODUCT = 0x01,
  MINIMUM = 0x02,
  MAXIMUM = 0x03,
  LITERAL = 0x04,
  GREATER_THAN = 0x05,
  LESS_THAN = 0x06,
  EQUAL_TO = 0x07
};

struct Packet
{
  uint8_t version;
  uint8_t typeID;
  int value;
};

class Parser
{
public:
  Parser(const std::string &input) : size(input.size() * bitsPerSet)
  {
    for (size_t i = 0; i < input.size(); i++)
    {
      data.push_back(std::bitset<bitsPerSet>(stoi(input.substr(i, 1), NULL, 16)));
    }
    std::cout << "calc " << size << " data.size():" << data.size() << std::endl;
  }

  void parse()
  {
    // while (cursor < size)
    // {
    auto p = readPacket();
    packets.insert(packets.end(), p.begin(), p.end());
    // }
  }

  int sumVersionNumbers()
  {
    int ret{0};
    for (auto packet : packets)
    {
      ret += packet.version;
    }
    return ret;
  }

  void exB()
  {
    for (auto packet : packets)
    {
      std::cout << packet.value << std::endl;
    }
  }

private:
  static constexpr std::size_t alignment{8u};
  static constexpr std::size_t bitsPerSet{4u};
  std::vector<Packet> packets;
  std::vector<std::bitset<bitsPerSet>> data;
  std::size_t cursor{0U};
  std::size_t size{0U};

  std::vector<Packet> readPacket(bool subpacket = false)
  {

    std::vector<Packet> ret;
    ret.emplace_back();
    ret.back().version = read<uint8_t>(3u);
    ret.back().typeID = read<uint8_t>(3u);
    if (ret.back().typeID == TypeId::LITERAL)
    {
      ret.back().value = 0;
      uint32_t value = 0;
      uint8_t last{0u};
      do
      {
        value = value << 4;
        last = read<uint8_t>(1u);
        value |= last;
      } while (last != 0u);

      std::cout << value;
      // create package

      // realign cursor
      if (!subpacket)
      {
        std::size_t padding = cursor % alignment;
        cursor += alignment - padding;
      }
    }
    else
    {
      std::size_t lengthTypeID = (read<int>(1u) == 0 ? 15u : 11u);
      uint16_t subpacketLength = read<uint16_t>(lengthTypeID);
      std::size_t tempCursor = cursor + subpacketLength;
      std::vector<Packet> p;
      while (cursor < tempCursor)
      {
        p = readPacket(true);
      }

      int value = 0;
      switch (ret.back().typeID)
      {
      case TypeId::SUM:

        std::cout << " + (";
        std::for_each(p.begin(), p.end(), [&value](Packet &p)
                      {
                        value += p.value;
                        std::cout << p.value << " ";
                      });
        std::cout << ")=" << value << " ";
        break;

      case TypeId::PRODUCT:
        value = 1;
        std::cout << " * (";
        std::for_each(p.begin(), p.end(), [&value](Packet &p)
                      {
                        value *= p.value;
                        std::cout << p.value << " ";
                      });
        std::cout << ")=" << value << " ";
        break;

      case TypeId::MINIMUM:
        value = std::numeric_limits<int>::max();
        std::cout << " MIN(";
        for (auto subPackage : p)
        {
          std::cout << subPackage.value << " ";
          value = std::min(value, subPackage.value);
        }
        std::cout << ")=" << value << " ";

        break;

      case TypeId::MAXIMUM:
        value = std::numeric_limits<int>::min();
        std::cout << " MAX(";
        for (auto subPackage : p)
        {
          std::cout << subPackage.value << " ";
          value = std::max(value, subPackage.value);
        }
        std::cout << ")=" << value << " ";
        break;

      case TypeId::GREATER_THAN:
        value = (p[0].value > p[1].value ? 1 : 0);
        std::cout << " GT(" << p[0].value << ", " << p[1].value << ")=" << value;
        break;

      case TypeId::LESS_THAN:
        value = (p[0].value < p[1].value ? 1 : 0);
        std::cout << " LT(" << p[0].value << ", " << p[1].value << ")=" << value;
        break;

      case TypeId::EQUAL_TO:
        value = (p[0].value == p[1].value ? 1 : 0);
        std::cout << " EQ(" << p[0].value << ", " << p[1].value << ")=" << value;
        break;
      }
      std::cout << std::endl;
      ret.back().value = value;

      if (cursor != tempCursor)
      {
        std::cerr << "PARSER ERROR" << std::endl;
      }
    }
    return ret;
  }

  template <typename T>
  T read(std::size_t nBits)
  {
    T retVal{0};
    for (auto i = 0u; i < nBits; ++i)
    {
      retVal = retVal << 1;

      auto element = cursor / bitsPerSet;
      auto subElement = (bitsPerSet - 1) - (cursor % bitsPerSet);

      retVal |= data[element][subElement];
      ++cursor;
    }
    return retVal;
  }
};

int main(int, char *[])
{
  constexpr bool readFile = false;

  std::string inString{readFile ? puzzleInput::input : puzzleInput::input1};

  Parser parser(inString);

  parser.parse();

  std::cout << "---------------------" << std::endl;
  std::cout << "sumVersion: " << parser.sumVersionNumbers() << std::endl;
  return 0;
}