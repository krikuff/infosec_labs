#pragma once

#include <string>
#include <vector>

///@brief Magic square cypher
class MagicSquareCypher final
{
public:
    ///@brief
    ///@param square Magic square as plain string, rows are separated with newline
    explicit MagicSquareCypher( std::string const& square );

    ///@brief Set up magic square
    ///@param square Magic square as plain string, rows are separated with newline
    void Configure( std::string const& square );

    std::string Encrypt( std::string const& input );

    std::string Decrypt( std::string const& input );

private:
    /// Encryption/decryption algorithm pass
    std::string Pass( std::vector<int> const& square, std::string const& input );

    std::vector<int> ParseSquare( std::string const& str );

    void CheckSquareForMagic( std::vector<int> const& square );

private:
    std::vector<int> decryptionSquare_; //< Magic square stored linearly
    std::vector<int> encryptionSquare_; //< Same square but values became indices and vice versa
};
