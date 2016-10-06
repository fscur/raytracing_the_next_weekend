#include "guid.h"
#include <iomanip>

using namespace std;

guid::guid(const vector<byte> &bytes)
{
    _bytes = bytes;
}

guid::guid(const byte* bytes)
{
    _bytes.assign(bytes, bytes + 16);
}

byte hexDigitToChar(char ch)
{
    if (ch > 47 && ch < 58)
        return ch - 48;

    if (ch > 96 && ch < 103)
        return ch - 87;

    if (ch > 64 && ch < 71)
        return ch - 55;

    return 0;
}

byte hexPairToChar(char a, char b)
{
    return hexDigitToChar(a) * 16 + hexDigitToChar(b);
}

guid::guid(const string &fromString)
{
    _bytes.clear();

    char charOne = 0;
    char charTwo = 0;

    bool lookingForFirstChar = true;

    for (const char &ch : fromString)
    {
        if (ch == '-')
            continue;

        if (lookingForFirstChar)
        {
            charOne = ch;
            lookingForFirstChar = false;
        }
        else
        {
            charTwo = ch;
            auto byte = hexPairToChar(charOne, charTwo);
            _bytes.push_back(byte);
            lookingForFirstChar = true;
        }
    }
}

guid::guid()
{
    _bytes = std::vector<byte>(16, 0);
}

guid::guid(const guid &other)
{
    _bytes = other._bytes;
}

guid &guid::operator=(const guid &other)
{
    _bytes = other._bytes;
    return *this;
}

bool guid::operator==(const guid &other) const
{
    return _bytes == other._bytes;
}

bool guid::operator!=(const guid &other) const
{
    return !((*this) == other);
}

ostream &operator<<(ostream &s, const guid &guid)
{
    return s << hex << setfill('0')
        << setw(2) << (int)guid._bytes[0]
        << setw(2) << (int)guid._bytes[1]
        << setw(2) << (int)guid._bytes[2]
        << setw(2) << (int)guid._bytes[3]
        << "-"
        << setw(2) << (int)guid._bytes[4]
        << setw(2) << (int)guid._bytes[5]
        << "-"
        << setw(2) << (int)guid._bytes[6]
        << setw(2) << (int)guid._bytes[7]
        << "-"
        << setw(2) << (int)guid._bytes[8]
        << setw(2) << (int)guid._bytes[9]
        << "-"
        << setw(2) << (int)guid._bytes[10]
        << setw(2) << (int)guid._bytes[11]
        << setw(2) << (int)guid._bytes[12]
        << setw(2) << (int)guid._bytes[13]
        << setw(2) << (int)guid._bytes[14]
        << setw(2) << (int)guid._bytes[15];
}