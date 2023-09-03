#ifndef UnblockMe_Utils_Grid
#define UnblockMe_Utils_Grid


#include <unordered_set>
#include "block.hpp"



namespace UnblockMe::Utils::Grid {
    using UnblockMe::Utils::Block::Block;
    using UnblockMe::Utils::Block::hashOfBlock;


    // implement std::equal_to and std::hash  for block to skip decltype(&hashOfBlock)?
    using Grid = std::unordered_set<Block,decltype(&hashOfBlock)>;
    
}
#endif