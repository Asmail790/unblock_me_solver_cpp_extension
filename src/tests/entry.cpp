
#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "entry.hpp"


using UnblockMe::Utils::Entry::Top;
using UnblockMe::Utils::Entry::Left;
using UnblockMe::Utils::Entry::Right;
using UnblockMe::Utils::Entry::Bottom;
using UnblockMe::Utils::Entry::StepSizeX;
using UnblockMe::Utils::Entry::StepSizeY;

using UnblockMe::Utils::Entry::MainBlockLabel;
using UnblockMe::Utils::Entry::Vertical2XBlockLabel;
using UnblockMe::Utils::Entry::Vertical3XBlockLabel;
using UnblockMe::Utils::Entry::Horizontal2XBlockLabel;
using UnblockMe::Utils::Entry::Horizontal3XBlockLabel;
using UnblockMe::Utils::Entry::FixedBlockLabel;
using UnblockMe::Utils::Entry::GridLabel;
using UnblockMe::Utils::Entry::Class_;


TEST_CASE("convertToImageCoordinate","[convertToImageCoordinate]"){
    using UnblockMe::Utils::Entry::GridProperties;


    GridProperties properties {
        Top{100},
        Left{100},
        StepSizeX {50.5},
        StepSizeY {25.5},    
    };



    SECTION("case 1"){
        unsigned char logicalX = 0;
        unsigned char logicalY = 0;
        auto point = convertToImageCoordinate(logicalX,logicalY,properties);
        REQUIRE( std::pair{100.f,100.f} == point);
    }

    SECTION("case 2"){
        unsigned char logicalX = 1;
        unsigned char logicalY = 1;
        auto point = convertToImageCoordinate(logicalX,logicalY,properties);
        REQUIRE( std::pair{150.5f,125.5f} == point);
    }

    SECTION("case 3"){
        unsigned char logicalX = 5;
        unsigned char logicalY = 5;
        auto point = convertToImageCoordinate(logicalX,logicalY,properties);
        REQUIRE( std::pair{100.f + 5*50.5f,100.f + 5*25.5f } == point);
    }

}

TEST_CASE("convertToBlockCoordinate","[convertToBlockCoordinate]"){
    using UnblockMe::Utils::Entry::GridProperties;
      GridProperties properties {
        Top{100},
        Left{100},
        StepSizeX{50},
        StepSizeY{25},    
    };


    SECTION("case 1 close to gridsTopLeftCoroner=(100,100)") {
        const auto imageCoordinate = std::pair(110,110);
        const auto point = convertToBlockCoordinate(imageCoordinate, properties);
        REQUIRE(point == std::pair<unsigned char,unsigned char>(0,0));
    };

    SECTION("case 2 below gridsTopLeftCoroner=(100,100)") {
        const auto imageCoordinate = std::pair(0,0);
        const auto point = convertToBlockCoordinate(imageCoordinate, properties);
        REQUIRE(point == std::pair<unsigned char,unsigned char>(0,0));
    };

    SECTION("case 2 above gridsBottomRightCoroner(100+50*5,100+25*5)") {
        const auto imageCoordinate = std::pair(1000,1000);
        const auto point = convertToBlockCoordinate(imageCoordinate, properties);
        REQUIRE(point == std::pair<unsigned char,unsigned char>(5,5));
    };

    SECTION("case 3 close to (150,125)") {
        const auto imageCoordinate = std::pair(100 + 49,100 + 24);
        const auto point = convertToBlockCoordinate(imageCoordinate, properties);
        REQUIRE(point == std::pair<unsigned char,unsigned char>(1,1));
    };

    SECTION("case 4 close to (150,125)") {
        const auto imageCoordinate = std::pair(100 + 50 +1,100 + 25 + 1);
        const auto point = convertToBlockCoordinate(imageCoordinate, properties);
        REQUIRE(point == std::pair<unsigned char,unsigned char>(1,1));
    };

    SECTION("case 5 close to center point of (100 to 150,100 to 125) ie. (125,112.5) but below") {
        const auto imageCoordinate = std::pair(100 + 25-1,100 + ((int)12.5) - 1);
        const auto point = convertToBlockCoordinate(imageCoordinate, properties);
        REQUIRE(point == std::pair<unsigned char,unsigned char>(0,0));
    };

    SECTION("case 6 close to center point of (100 to 150,100 to 125) ie. (125,112.5) but above") {
        const auto imageCoordinate = std::pair(100 + 25+1,100 + ((int)12.5) + 1);
        const auto point = convertToBlockCoordinate(imageCoordinate, properties);
        REQUIRE(point == std::pair<unsigned char,unsigned char>(1,1));
    };
}

TEST_CASE("convertToNextStep","[convertToNextStep]"){
    using UnblockMe::Utils::Entry::GridProperties;
    using UnblockMe::Utils::Entry::MLClassIds;
    using UnblockMe::Utils::Graph::StepDescription;
    using UnblockMe::Utils::Entry::BoundingBox;
    

    using UnblockMe::Utils::Block::Block;
    using UnblockMe::Utils::Block::Direction;
    using UnblockMe::Utils::Block::BlockType;
    using UnblockMe::Utils::Block::X;
    using UnblockMe::Utils::Block::Y;

    GridProperties properties {
        Top{0},
        Left{0},
        StepSizeX{100},
        StepSizeY{100},    
    };

    MLClassIds mlClassIds{
        MainBlockLabel{0},
        Vertical2XBlockLabel{1},
        Vertical3XBlockLabel{2},
        Horizontal2XBlockLabel{3},
        Horizontal3XBlockLabel{4},
        FixedBlockLabel{5},
        GridLabel{6}
    };

    const auto step = StepDescription{
        .oldBlock = Block{
            BlockType::MAIN_BLOCK,
            X{0},
            Y{2}
        },
        X{4},
        Y{2}
    };


    const auto mlClassId = BlockTypeToMLlClassId(step.oldBlock, mlClassIds);
    REQUIRE(mlClassId == mlClassIds.mainBlock);

    const auto originalBoundingBox= BoundingBox{
        Left{ 0},
        Top{200},
        Right{200},
        Bottom{300},
        Class_{mlClassId}
    }; 


    const auto newBoundingBox= BoundingBox{
        Left{400},
        Top{200},
        Right{600},
        Bottom{ 300},
        Class_{mlClassId}
    }; 

    const auto instruction = convertToNextStep(step, properties, mlClassIds );
    REQUIRE(instruction.from == originalBoundingBox);
    REQUIRE(instruction.to == newBoundingBox);
}

TEST_CASE("SimpleGuider","[SimpleGuider]") {
    using UnblockMe::Utils::Entry::SimpleGuider;
    using UnblockMe::Utils::Entry::MLClassIds;
    using UnblockMe::Utils::Entry::BoundingBox;
    using UnblockMe::Utils::Entry::NextStep;
    
    MLClassIds mlClassIds{
        MainBlockLabel{0},
        Vertical2XBlockLabel{1},
        Vertical3XBlockLabel{2},
        Horizontal2XBlockLabel{3},
        Horizontal3XBlockLabel{4},
        FixedBlockLabel{5},
        GridLabel{6}
    };
    SimpleGuider guider{};
    guider.setMLClassIds(mlClassIds);
    
    SECTION("Simple Case") {
        BoundingBox gridBoundingBox = BoundingBox{
            Left{0},
            Top {0},
            Right{600},
            Bottom{600},
            Class_{mlClassIds.grid}
        };

        BoundingBox mainBlockBoundingBox = BoundingBox{
            Left{0},
            Top {200},
            Right{200},
            Bottom{300},
            Class_{mlClassIds.mainBlock}
        };

        std::vector<BoundingBox> blocksBoundingBoxes{mainBlockBoundingBox};
        const auto instruction = guider.inferOneStep(blocksBoundingBoxes,gridBoundingBox );
        const auto allInstructions = guider.inferAllSteps(blocksBoundingBoxes,gridBoundingBox );



        const auto newBoundingBox =  BoundingBox{
            Left{400},
            Top{200},
            Right{600},
            Bottom{300},
            Class_{mlClassIds.mainBlock}
       };

        REQUIRE(instruction.from == mainBlockBoundingBox);
        REQUIRE(instruction.to == newBoundingBox);
        REQUIRE((allInstructions.size() == 1 && allInstructions[0].from ==mainBlockBoundingBox && allInstructions[0].to == newBoundingBox));

    }

    SECTION("Simple Case 2") {
        BoundingBox gridBoundingBox = BoundingBox{
            Left{ 0},
            Top{ 0},
            Right{ 600},
            Bottom{ 600},
            Class_{ mlClassIds.grid}
        };

        BoundingBox mainBlockBoundingBox = BoundingBox{
            Left{0},
            Top{200},
            Right{200},
            Bottom{300},
            Class_{mlClassIds.mainBlock}
        };

        const auto mainBlockAtExitBoundingBox =  BoundingBox{
            Left{400},
            Top{200},
            Right{600},
            Bottom{300},
            Class_{mlClassIds.mainBlock}
       };

        BoundingBox verticalBlockBoundingBox = BoundingBox{
            Left{200},
            Top{100},
            Right{300},
            Bottom{300},
            Class_{mlClassIds.vertical2XBlock}
        };

        const auto verticalBlockPushedUpBoundingBox =  BoundingBox{
            Left{200},
            Top{0},
            Right{300},
            Bottom{200},
            Class_{mlClassIds.vertical2XBlock}
       };

  
        std::vector<BoundingBox> blocksBoundingBoxes{mainBlockBoundingBox,verticalBlockBoundingBox};
        const auto instruction = guider.inferOneStep(blocksBoundingBoxes,gridBoundingBox);
        const auto allInstructions = guider.inferAllSteps(blocksBoundingBoxes,gridBoundingBox);



        REQUIRE(instruction.from == verticalBlockBoundingBox);
        REQUIRE(instruction.to == verticalBlockPushedUpBoundingBox);
        
        REQUIRE(allInstructions.size() == 2);

        REQUIRE(allInstructions[0].from == verticalBlockBoundingBox);
        REQUIRE(allInstructions[0].to == verticalBlockPushedUpBoundingBox);

        REQUIRE(allInstructions[1].from == mainBlockBoundingBox);
        REQUIRE(allInstructions[1].to == mainBlockAtExitBoundingBox);

    }

    SECTION("Simple Case 3") {
        // TODO
    };

    SECTION("Simple Case 4") {
        // TODO
    };

}
