#include "drawer.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace chartlib {

constexpr double EdgeThicknessMultiplier = 5.0;
constexpr double NodeSizeMultiplier = 20.0;

void TDrawer::GenerateAndDrawGraph(
    const TMatrix& adjacency_matrix,
    const std::string& filename,
    const std::vector<Type>& node_weights
) {
    GenerateDotFile(adjacency_matrix, filename, node_weights);
    GenerateImage(filename);
}

void TDrawer::GenerateDotFile(
    const TMatrix& adjacency_matrix,
    const std::string& filename,
    const std::vector<Type>& node_weights
) {
    if (adjacency_matrix.empty()) {
        throw std::invalid_argument("Adjacency matrix is empty");
    }

    size_t n = adjacency_matrix.size();

    // Validate matrix is square
    for (const auto& row : adjacency_matrix) {
        if (row.size() != n) {
            throw std::invalid_argument("Adjacency matrix must be square");
        }
    }

    std::ofstream dotFile(filename + ".dot");
    if (!dotFile.is_open()) {
        throw std::runtime_error("Failed to create DOT file: " + filename);
    }

    dotFile << "digraph G {\n";
    dotFile << "    rankdir=LR;\n";
    dotFile << "    node [shape=circle];\n";

    dotFile << GenerateNodesCommand(adjacency_matrix, node_weights);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            Type weight = adjacency_matrix[i][j];
            if (weight > 0) {
                Type thickness = weight * EdgeThicknessMultiplier;
                dotFile << GenerateEdge(i, j, weight, thickness);
            }
        }
    }

    dotFile << "}\n";
}

std::string
TDrawer::GenerateEdge(int from, int to, Type weight, Type thickness) {
    std::stringstream command;
    command << "    "
            << "N" << from << " -> N" << to << " [label=\"" << std::fixed
            << std::setprecision(2) << weight << "\", "
            << "penwidth=" << thickness << "];\n";
    return command.str();
}

std::string TDrawer::GenerateNodesCommand(
    const TMatrix& adjacency_matrix, const std::vector<Type>& node_weights
) {
    if (node_weights.empty()) {
        return {};
    }

    if (node_weights.size() != adjacency_matrix.size()) {
        throw std::invalid_argument(
            "Node weights vector size must match matrix size"
        );
    }

    std::stringstream command;
    for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
        command << "    N" << i << "[label=\"N" << i << "\", penwidth="
                << std::max(0.1, node_weights[i] * NodeSizeMultiplier)
                << "];\n";
    }
    return command.str();
}

void TDrawer::GenerateImage(const std::string& filename) {
    try {
        std::string command =
            "dot -Tpng " + filename + ".dot -o " + filename + ".png";
        if (system(command.c_str()) != 0) {
            throw std::runtime_error("Failed to generate PNG image");
        }

        std::cout << "Graph image created: " << filename << ".png\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

} // namespace chartlib
