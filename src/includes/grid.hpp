#ifndef UnblockMe_Utils_Grid
#define UnblockMe_Utils_Grid


#include <unordered_set>
#include "block.hpp"
#include <vector>
#include <set>
#include <cstdio>



namespace UnblockMe::Utils::Grid {
    using UnblockMe::Utils::Block::Block;
    using UnblockMe::Utils::Block::hashOfBlock;


    // implement std::equal_to and std::hash  for block to skip decltype(&hashOfBlock)?
    using Grid = std::set<Block>;
    using ExperimentalGrid = std::unordered_set<const Block*,decltype(&hashOfBlock)>;
    auto getOccupiedPositions(const Grid& grid)->std::array<std::array<bool,6>,6>;
    auto getAvailablePositionsForBlock(const Block& block, const std::array<std::array<bool,6>,6>& occupied)->std::vector<std::pair<unsigned char,unsigned char>>;
    auto getAdjacentGrids(const Grid& grid)->std::set<Grid>;
    auto isValidGrid(const Grid& grid)->bool;

    

}
#endif