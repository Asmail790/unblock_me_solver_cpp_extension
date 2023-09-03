#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "block.hpp"


using UnblockMe::Utils::Block::Block;
using UnblockMe::Utils::Block::Direction;
using UnblockMe::Utils::Block::BlockType;
using UnblockMe::Utils::Block::X;
using UnblockMe::Utils::Block::Y;
using UnblockMe::Utils::Block::Size;



TEST_CASE("Block Equals", "[Block][Equals]") {
    using UnblockMe::Utils::Block::equalsOfBlock;
    
    const Direction direction = Direction::HORIZONTAL;
    const BlockType blockType = BlockType::MAIN_BLOCK;
    const auto xHeadPos = X{1};
    const auto yHeadPos = Y{2}; 
    const auto size = Size{3};
    
    const auto block =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto duplicateBlock =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto nonDuplicateBlock = Block( Direction::NONE,BlockType::FIXED_BLOCK,X{0},Y{0},Size{0});

    REQUIRE(equalsOfBlock(block,duplicateBlock));
    REQUIRE(block == duplicateBlock);
    REQUIRE((block == nonDuplicateBlock) == false);
    REQUIRE(!equalsOfBlock(block,nonDuplicateBlock));
}


TEST_CASE("Block Hash", "[Block][Hash]") {
    using UnblockMe::Utils::Block::hashOfBlock;

    const Direction direction = Direction::HORIZONTAL;
    const BlockType blockType = BlockType::MAIN_BLOCK;
    const auto xHeadPos = X{1};
    const auto yHeadPos = Y{2}; 
    const auto size = Size{3};
    
    const Block block =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto duplicateBlock =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto nonDuplicateBlock = Block( Direction::NONE,BlockType::FIXED_BLOCK,X{0},Y{0},Size{0});

    std::size_t correct = block.xHeadPos*10000 +block.yHeadPos*1000 +block.size*100 + static_cast<int>(block.type)*10 + static_cast<int>(block.direction);
    REQUIRE( hashOfBlock(block)== correct);
    REQUIRE( hashOfBlock(block)== hashOfBlock(duplicateBlock));
    REQUIRE( hashOfBlock(block)!= hashOfBlock(nonDuplicateBlock));
}


