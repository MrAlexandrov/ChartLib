#pragma once

#include "types.hpp"

#include <string>
#include <vector>

namespace chartlib {

class TDrawer {
private:
    TDrawer() = delete;

public:
    static void GenerateAndDrawGraph(
        const TMatrix& adjacency_matrix,
        const std::string& filename,
        const std::vector<Type>& node_weights = {}
    );

private:
    static void GenerateDotFile(
        const TMatrix& adjacency_matrix,
        const std::string& filename,
        const std::vector<Type>& node_weights
    );

    static std::string GenerateNodesCommand(
        const TMatrix& adjacency_matrix, const std::vector<Type>& node_weights
    );

    static std::string
    GenerateEdge(int from, int to, Type weight, Type thickness);

    static void GenerateImage(const std::string& filename);
};

} // namespace chartlib
