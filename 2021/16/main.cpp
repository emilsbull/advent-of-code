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
  constexpr std::string_view input1 = "C0015000016115A2E0802F182340";
  constexpr std::string_view input = "E0529D18025800ABCA6996534CB22E4C00FB48E233BAEC947A8AA010CE1249DB51A02CC7DB67EF33D4002AE6ACDC40101CF0449AE4D9E4C071802D400F84BD21CAF3C8F2C35295EF3E0A600848F77893360066C200F476841040401C88908A19B001FD35CCF0B40012992AC81E3B980553659366736653A931018027C87332011E2771FFC3CEEC0630A80126007B0152E2005280186004101060C03C0200DA66006B8018200538012C01F3300660401433801A6007380132DD993100A4DC01AB0803B1FE2343500042E24C338B33F5852C3E002749803B0422EC782004221A41A8CE600EC2F8F11FD0037196CF19A67AA926892D2C643675A0C013C00CC0401F82F1BA168803510E3942E969C389C40193CFD27C32E005F271CE4B95906C151003A7BD229300362D1802727056C00556769101921F200AC74015960E97EC3F2D03C2430046C0119A3E9A3F95FD3AFE40132CEC52F4017995D9993A90060729EFCA52D3168021223F2236600ECC874E10CC1F9802F3A71C00964EC46E6580402291FE59E0FCF2B4EC31C9C7A6860094B2C4D2E880592F1AD7782992D204A82C954EA5A52E8030064D02A6C1E4EA852FE83D49CB4AE4020CD80272D3B4AA552D3B4AA5B356F77BF1630056C0119FF16C5192901CEDFB77A200E9E65EAC01693C0BCA76FEBE73487CC64DEC804659274A00CDC401F8B51CE3F8803B05217C2E40041A72E2516A663F119AC72250A00F44A98893C453005E57415A00BCD5F1DD66F3448D2600AC66F005246500C9194039C01986B317CDB10890C94BF68E6DF950C0802B09496E8A3600BCB15CA44425279539B089EB7774DDA33642012DA6B1E15B005C0010C8C917A2B880391160944D30074401D845172180803D1AA3045F00042630C5B866200CC2A9A5091C43BBD964D7F5D8914B46F040";
}

enum TypeId : uint8_t
{
  LITERAL = 0b100,
  OPERATOR = 0xFF
};

struct Packet
{
  uint8_t version;
  uint8_t typeID;
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
  }

  void parse()
  {
    while (cursor < size)
    {
      auto p = readPacket();
      packets.insert(packets.end(), p.begin(), p.end());
    }
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
      std::vector<uint8_t> literals;
      uint8_t last{0u};
      do
      {
        last = read<uint8_t>(1u);
        literals.push_back(read<uint8_t>(4u));
      } while (last != 0u);

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
      while (cursor < tempCursor)
      {
        auto p = readPacket(true);
        packets.insert(packets.end(), p.begin(), p.end());
      }
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
  constexpr bool readFile = true;

  std::string inString{readFile ? puzzleInput::input : puzzleInput::input1};

  Parser parser(inString);

  parser.parse();

  std::cout << "---------------------" << std::endl;
  std::cout << "sumVersion: " << parser.sumVersionNumbers() << std::endl;
  return 0;
}