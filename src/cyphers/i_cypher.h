#pragma once

#include <string>

using namespace std;

// Общий интерфейс для методов шифрования.
// Кроме шифрования занимается разбором строки, что нехорошо.
struct ICypher
{
    virtual ~ICypher() = default;

    virtual void Configure(string const& config) = 0;

    virtual string Encrypt(string const& input) = 0;

    virtual string Decrypt(string const& input) = 0;
};
