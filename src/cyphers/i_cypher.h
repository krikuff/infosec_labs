#pragma once

#include <string>

// Общий интерфейс для методов шифрования.
// Кроме шифрования занимается разбором строки, что нехорошо.
struct ICypher
{
    virtual ~ICypher() = default;

    virtual void Configure(std::string const& config) = 0;

    virtual std::string Encrypt(std::string const& input) = 0;

    virtual std::string Decrypt(std::string const& input) = 0;
};
