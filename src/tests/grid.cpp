#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "block.hpp"
#include "grid.hpp"


using UnblockMe::Utils::Block::Block;
using UnblockMe::Utils::Block::Direction;
using UnblockMe::Utils::Block::BlockType;
using UnblockMe::Utils::Block::X;
using UnblockMe::Utils::Block::Y;
using UnblockMe::Utils::Block::Size;
using UnblockMe::Utils::Grid::Grid;

TEST_CASE("Grid Add duplicates", "[Block][unordered_set]") {
    using UnblockMe::Utils::Block::equalsOfBlock;
    using UnblockMe::Utils::Block::hashOfBlock;

    const Direction direction = Direction::HORIZONTAL;
    const BlockType blockType = BlockType::MAIN_BLOCK;
    const auto xHeadPos = X{1};
    const auto yHeadPos = Y{2}; 
    const auto size = Size{3};
    
    const auto block =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto duplicateBlock =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto nonDuplicateBlock = Block( Direction::NONE,BlockType::FIXED_BLOCK,X{0},Y{0},Size{0});


    Grid grid{1,&hashOfBlock};
    grid.insert(block);

    REQUIRE( grid.count(duplicateBlock) == 1);
    REQUIRE( grid.count(nonDuplicateBlock) == 0);
    
}