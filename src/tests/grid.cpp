#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "grid.hpp"



TEST_CASE( "Block Hash", "[Block][Hash]" ) {
    using UnblockMe::Utils::Grid::Block;
    using UnblockMe::Utils::Grid::Direction;
    using UnblockMe::Utils::Grid::BlockType;
    using UnblockMe::Utils::Grid::BlockHash;

    Direction direction = Direction::HORIZONTAL;
    BlockType blockType = BlockType::MAIN_BLOCK;
    int xHeadPos = 1;
    int yHeadPos = 2; 
    int size = 3;
    
    Block block =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    auto hasher = BlockHash();
    std::size_t correct = block.xHeadPos*10000 +block.yHeadPos*1000 +block.size*100 + static_cast<int>(block.type)*10 + static_cast<int>(block.direction);
    REQUIRE( hasher(block)== correct);
}

TEST_CASE( "Grid Add duplicates", "[Block][unordered_set]" ) {
    using UnblockMe::Utils::Grid::Block;
    using UnblockMe::Utils::Grid::Direction;
    using UnblockMe::Utils::Grid::BlockType;
    using UnblockMe::Utils::Grid::BlockHash;
    using UnblockMe::Utils::Grid::BlockEquals;

    Direction direction = Direction::HORIZONTAL;
    BlockType blockType = BlockType::MAIN_BLOCK;
    int xHeadPos = 1;
    int yHeadPos = 2; 
    int size = 3;
    
    auto hasher = BlockHash();
    auto equals = BlockEquals();
    auto block1 =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    auto block2 =  Block(direction,blockType,xHeadPos,yHeadPos,size);

    std::unordered_set<Block,BlockHash,BlockEquals> set{1,hasher,equals};
    set.insert(block1);

}