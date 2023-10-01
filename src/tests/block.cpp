#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
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

TEST_CASE("Block less than", "[Block][Operator][Less than]") {
    const auto block1 =  Block(Direction::VERTICAL,BlockType::MAIN_BLOCK,X{1},Y{2},Size{3});

    const auto block2 =  Block(Direction::HORIZONTAL,BlockType::MAIN_BLOCK,X{1},Y{2},Size{3});
    
    const auto block3 =  Block(Direction::HORIZONTAL,BlockType::MOVABLE_BLOCK_2XV,X{1},Y{2},Size{3});
    
    const auto block4 =  Block(Direction::HORIZONTAL,BlockType::MOVABLE_BLOCK_2XV,X{2},Y{2},Size{3});
    
    const auto block5 =  Block(Direction::HORIZONTAL,BlockType::MOVABLE_BLOCK_2XV,X{2},Y{3},Size{3});
    
    const auto block6 =  Block(Direction::HORIZONTAL,BlockType::MOVABLE_BLOCK_2XV,X{2},Y{3},Size{4});

    const auto block7 =  Block(Direction::NONE,BlockType::FIXED_BLOCK,X{1},Y{1},Size{1});

    REQUIRE(block1 < block2);
    REQUIRE(block2 < block3);
    REQUIRE(block3 < block4);
    REQUIRE(block4 < block5);
    REQUIRE(block5 < block6);
    REQUIRE(block5 < block6);
    REQUIRE(block6 < block7);
 
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




TEST_CASE("getOccupiedPositions", "[Block][Occupied][Positions]") {
    using UnblockMe::Utils::Block::hashOfBlock;
    using std::pair;
    using output = std::vector<pair<unsigned char,unsigned char>>;
    using UnblockMe::Utils::Block::getOccupiedPositions;


    const Block mainBlock{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{1},
        Y{1},
        Size{2}
    };


    REQUIRE(getOccupiedPositions(mainBlock) == output{{1,1},{2,1}});
    

    const Block horizontalal2Xblock{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_2XH,
        X{0},
        Y{0},
        Size{2}
    };

    REQUIRE(getOccupiedPositions(horizontalal2Xblock) == output{{0,0},{1,0}});

    const Block horizontalal3XBlock{
    Direction::HORIZONTAL,
    BlockType::MOVABLE_BLOCK_3XH,
    X{1},
    Y{1},
    Size{3}
    };

    REQUIRE(getOccupiedPositions(horizontalal3XBlock) == output{{1,1},{2,1},{3,1}});

    const Block vertical2XBlock{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{1},
        Y{1},
        Size{2}
    };

    REQUIRE(getOccupiedPositions(vertical2XBlock) == output{{1,1},{1,2}});

    const Block vertical3XBlock{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_3XV,
        X{1},
        Y{1},
        Size{3}
    };

    REQUIRE(getOccupiedPositions(vertical3XBlock) == output{{1,1},{1,2},{1,3}});

    const Block fixedBlock{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{1},
        Y{1},
        Size{1}
    };

    REQUIRE(getOccupiedPositions(fixedBlock) == output{{1,1}});
}



