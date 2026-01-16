#pragma once

#include "chart.hpp"
#include "types.hpp"

#include <optional>
#include <string>
#include <vector>

namespace chartlib {

class TPlotter final {
public:
    explicit TPlotter(const std::string& filename);

    void SetXValues(const std::vector<int>& values);

    template <typename T>
    void EmplaceChart(const std::vector<T>& data, const std::string& title);

    void Plot() const;

    void SetDimensions(unsigned int width, unsigned int height);

private:
    void SaveDataToFile() const;

    std::string GenerateGnuplotCommands() const;

    void SaveGnuplotCommandsToFile() const;

private:
    unsigned int Width_;
    unsigned int Height_;
    std::string ImageName_;
    std::string DataFile_;
    std::string CommandFile_;
    std::optional<int> DataSize_;
    std::vector<int> XValues_;
    std::vector<TChart> Charts_;
};

template <typename T>
void TPlotter::EmplaceChart(
    const std::vector<T>& data, const std::string& title
) {
    Charts_.emplace_back(data, title);
}

} // namespace chartlib
