#include <bitset>
#include <range/v3/view.hpp>
#include <aoc/Exercise.h>

namespace aoc
{

namespace
{

class Image
{
public:
    Image(std::vector<std::string> data, std::size_t boundary, char boundaryValue = '.')
        : _boundaryValue(boundaryValue)
    {
        const auto rows = data.size() + 2 * boundary;
        const auto cols = data.front().size() + 2 * boundary;

        _data.reserve(rows);
        for (std::size_t i = 0; i < boundary; ++i)
        {
            _data.emplace_back(cols, boundaryValue);
        }
        for (auto& row : data)
        {
            _data.emplace_back(std::string(boundary, boundaryValue) + row + std::string(boundary, boundaryValue));
        }
        for (std::size_t i = 0; i < boundary; ++i)
        {
            _data.emplace_back(cols, boundaryValue);
        }
    }

    std::size_t cols() const
    {
        return _data.front().size();
    }

    std::size_t rows() const
    {
        return _data.size();
    }

    const char& at(std::size_t row, std::size_t col) const
    {
        return _data[row][col];
    }

    char& at(std::size_t row, std::size_t col)
    {
        return _data[row][col];
    }

    char boundaryValue() const
    {
        return _boundaryValue;
    }

    void setBoundaryValue(char value)
    {
        _boundaryValue = value;
    }

    std::size_t lightPixelCount() const
    {
        return ranges::distance
        (
            _data
                | ranges::views::join
                | ranges::views::filter(ranges::bind_back(ranges::equal_to{}, '#'))
        );
    }

private:
    std::vector<std::string> _data;
    char _boundaryValue;
};

std::size_t index(const Image& img, std::size_t row, std::size_t col)
{
    auto result = std::bitset<9>{};
    auto idx = std::size_t{8};
    for (const auto dr : ranges::views::closed_iota(-1, 1))
    {
        for (const auto dc : ranges::views::closed_iota(-1, 1))
        {
            if ((row > 0 || dr > -1) && (col > 0 || dc > -1) && (row + dr < img.rows() - 1) && (col + dc < img.cols() - 1))
            {
                result[idx] = (img.at(row + dr, col + dc) == '#');
            }
            else
            {
                result[idx] = (img.boundaryValue() == '#');
            }
            --idx;
        }
    }
    return result.to_ulong();
}

Image enhance(const Image& image, const std::string& enhancementAlgorithm)
{
    auto result = image;
    for (const auto row : ranges::views::iota(std::size_t{0}, image.rows()))
    {
        for (const auto col : ranges::views::iota(std::size_t{0}, image.cols()))
        {
            result.at(row, col) = enhancementAlgorithm[index(image, row, col)];
        }
    }
    result.setBoundaryValue((image.boundaryValue() == '.') ? enhancementAlgorithm[0] : enhancementAlgorithm[511]);
    return result;
}

std::size_t exercise(std::istream& stream, std::size_t iterations)
{
    auto lines = ranges::getlines(stream);

    const auto enhancementAlgorithm = *lines.begin();

    auto image = Image{lines | ranges::views::drop(2) | ranges::to_vector, iterations};
    for (std::size_t iteration = 0; iteration < iterations; ++iteration)
    {
        image = enhance(image, enhancementAlgorithm);
    }

    return image.lightPixelCount();
}

}

template <>
Result exercise<2021, 20, 1>(std::istream& stream)
{
    return exercise(stream, 2);
}

template <>
Result exercise<2021, 20, 2>(std::istream& stream)
{
    return exercise(stream, 50);
}

}
