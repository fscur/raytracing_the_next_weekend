#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../common/types.h"

class guid
{
private:
    std::vector<byte> _bytes;

private:
    friend std::ostream &operator<<(std::ostream &s, const guid &guid);

public:
    guid(const std::vector<byte> &bytes);
    guid(const byte* bytes);
    guid(const std::string &fromString);
    guid();
    guid(const guid &other);
    guid &operator=(const guid &other);
    bool operator==(const guid &other) const;
    bool operator!=(const guid &other) const;
};

class guidGenerator
{
public:
    static guid newGuid();
};