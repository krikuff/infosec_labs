#include <cyphers/magic_square_cypher.h>

#include <algorithm>
#include <cmath>
#include <numeric>
#include <sstream>
#include <stdexcept>

namespace {

const size_t DefaultSquareSize = 16;

} // namespace anonymous

void MagicSquareCypher::Configure(string const& config)
{
    auto square = ParseSquare(config);
    CheckSquareForMagic(square);

    decryptionSquare_ = move( square );
    for(auto& number : decryptionSquare_)
    {
        --number;
    }

    // меняем местами индексы и значения, чтобы ускорить шифрование
    encryptionSquare_.resize( decryptionSquare_.size() );
    for(size_t i = 0; i < encryptionSquare_.size(); ++i)
    {
        encryptionSquare_[ decryptionSquare_[i] ] = i;
    }
}

string MagicSquareCypher::Pass(vector<int> const& square, string const& input)
{
    const size_t inputSize = input.size();
    const size_t squareSize = square.size();
    size_t blockCount = inputSize / squareSize; // количество квадратов, нужное для шифрования текста
    if( inputSize % squareSize != 0 )
    {
        ++blockCount;
    }

    string output( blockCount * squareSize, ' ' );

    for( size_t i = 0; i < inputSize; ++i )
    {
        const size_t currentBlock = i / squareSize;
        const size_t offset = currentBlock * squareSize;
        const size_t outputIdx = offset + square[ i % squareSize ];

        output[ outputIdx ] = input[i];
    }

    return output;
}

string MagicSquareCypher::Encrypt(string const& input)
{
    return Pass(encryptionSquare_, input);
}
string MagicSquareCypher::Decrypt(string const& input)
{
    return Pass(decryptionSquare_, input);
}

vector<int> MagicSquareCypher::ParseSquare(string const& str)
{
    vector<int> square;
    square.reserve( DefaultSquareSize );
    stringstream ss(str);
    int number;
    while(ss >> number)
    {
        square.emplace_back(number);
    }
    if(square.size() == 0)
    {
        throw invalid_argument("Couldn't parse any numbers from config");
    }

    // Проверка на квадратность
    const size_t squareSize = square.size();
    const size_t sideLen = sqrt( squareSize );
    if( sideLen * sideLen != squareSize && squareSize != 1 )
    {
        throw invalid_argument("Incorrect square size");
    }

    return square;
}

void MagicSquareCypher::CheckSquareForMagic(vector<int> const& square)
{
    const size_t squareSize = square.size();
    const size_t sideLen = sqrt( squareSize );

    // За эталон берется сумма первой строки
    const int sampleSum = accumulate(square.begin(), square.begin() + sideLen, 0);

    // Проверка равенства сумм строк
    for(auto begin = square.begin() + sideLen; begin != square.end(); begin += sideLen)
    {
        const int sum = accumulate(begin, begin + sideLen, 0);
        if(sum != sampleSum)
        {
            throw invalid_argument("Row sums are not equal");
        }
    }

    // Проверка равенства сумм столбцов
    for(int i = 0; i < sideLen; ++i)
    {
        int sum = square.at(i);
        for(int j = i + sideLen; j < squareSize; j += sideLen)
        {
            sum += square.at(j);
        }

        if(sum != sampleSum)
        {
            throw invalid_argument("Column sums are not equal");
        }
    }

    // Проверка равенства сумм диагоналей
    int diagonalSum = square.at(0);
    for(int i = sideLen + 1; i < squareSize; i += sideLen + 1)
    {
        diagonalSum += square.at(i);
    }
    if(diagonalSum != sampleSum)
    {
        throw invalid_argument("Primary diagonal sum doesn't fit");
    }

    diagonalSum = square.at(sideLen - 1);
    for(int i = 2; i <= sideLen; ++i)
    {
        diagonalSum += square.at( sideLen * i - i );
    }
    if(diagonalSum != sampleSum)
    {
        throw invalid_argument("Secondary diagonal sum doesn't fit");
    }
}
