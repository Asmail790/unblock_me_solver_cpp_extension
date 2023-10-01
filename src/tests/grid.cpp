#define CATCH_CONFIG_MAIN
#include <set>
#include "catch2/catch_test_macros.hpp"
#include "block.hpp"
#include "grid.hpp"


using UnblockMe::Utils::Block::Block;
using UnblockMe::Utils::Block::Direction;
using UnblockMe::Utils::Block::BlockType;
using UnblockMe::Utils::Block::X;
using UnblockMe::Utils::Block::Y;
using UnblockMe::Utils::Block::Size;
using UnblockMe::Utils::Grid::Grid;
using UnblockMe::Utils::Block::hashOfBlock;

TEST_CASE("Grid Add duplicates","[Grid][Duplicates]") {

    const Direction direction = Direction::HORIZONTAL;
    const BlockType blockType = BlockType::MAIN_BLOCK;
    const auto xHeadPos = X{1};
    const auto yHeadPos = Y{2}; 
    const auto size = Size{3};
    
    const auto block =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto duplicateBlock =  Block(direction,blockType,xHeadPos,yHeadPos,size);
    const auto nonDuplicateBlock = Block( Direction::NONE,BlockType::FIXED_BLOCK,X{0},Y{0},Size{0});


    Grid grid{};
    grid.insert(block);

    REQUIRE( grid.count(duplicateBlock) == 1);
    REQUIRE( grid.count(nonDuplicateBlock) == 0);
    
}

TEST_CASE("getOccupiedPositions", "[Occupied][Positions]") {
    using UnblockMe::Utils::Grid::getOccupiedPositions;

    Grid grid{
        {
            Block{
                Direction::NONE,
                BlockType::FIXED_BLOCK,
                X{0},
                Y{0},
                Size{1}
            },

            Block{
                Direction::NONE,
                BlockType::FIXED_BLOCK,
                X{5},
                Y{0},
                Size{1}
            },

            Block{
                Direction::NONE,
                BlockType::FIXED_BLOCK,
                X{5},
                Y{5},
                Size{1}
            },

            Block{
                Direction::NONE,
                BlockType::FIXED_BLOCK,
                X{0},
                Y{5},
                Size{1}
            },
        }
    };

    const auto occupiedPositions = getOccupiedPositions(grid);

    for(int x = 0; x < occupiedPositions.size();x++) {
        for(int y=0; y< occupiedPositions[0].size();y++) {


        const auto isTopLeft = x == 0  && y == 0;
        const auto isTopRight = x==5 && y==0;
        const auto isBottomRight = x == 5 && y == 5;
        const auto isBottomLeft = x == 0 && y == 5;
        const auto isAtACorner = isTopLeft || isTopRight || isBottomRight||isBottomLeft;

            if (isAtACorner) {
                REQUIRE(occupiedPositions[x][y]  == true);
            } else {
                REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }
    
}

// TODO parametrize all getAvailablePositionsForBlock simple cases and advanced cases tests 

TEST_CASE("getAvailablePositionsForBlock for Simple Case MOVABLE_BLOCK_2XH","[Available][Positions][For][Block][Simple][Case][MOVABLE_BLOCK_2XH]") {
    using  UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto block = Block{
            Direction::HORIZONTAL,
            BlockType::MOVABLE_BLOCK_2XH,
            X{2},
            Y{2},
            Size{2}
    };

    const auto grid = Grid{
        {block}
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = y == 2 && 2<=x && x<=3; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{{0,2},{1,2},{3,2},{4,2}};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}

TEST_CASE("getAvailablePositionsForBlock for Simple Case MAIN_BLOCK","[Available][Positions][For][Block][Simple][Case][MAIN_BLOCK]") {
    using  UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto block = Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{2},
            Y{2},
            Size{2}
    };

    const auto grid = Grid{
        {block}
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = y == 2 && 2<=x && x<=3; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{{0,2},{1,2},{3,2},{4,2}};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}



TEST_CASE("getAvailablePositionsForBlock for Simple Case MOVABLE_BLOCK_3XH","[Available][Positions][For][Block][Simple][Case][MOVABLE_BLOCK_3XH]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto block = Block{
            Direction::HORIZONTAL,
            BlockType::MOVABLE_BLOCK_3XH,
            X{2},
            Y{2},
            Size{3}
    };

    const auto grid = Grid{
        {block}
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied =  y == 2 && 2<=x && x<=4; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{{0,2},{1,2},{3,2}};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}


TEST_CASE("getAvailablePositionsForBlock for Simple Case MOVABLE_BLOCK_2XV","[Available][Positions][For][Block][Simple][Case][MOVABLE_BLOCK_2XV]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto block = Block{
            Direction::VERTICAL,
            BlockType::MOVABLE_BLOCK_2XV,
            X{2},
            Y{2},
            Size{2}
    };

    const auto grid = Grid{
        {block}
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = x == 2 && 2<=y && y<=3; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{{2,0},{2,1},{2,3},{2,4}};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}


TEST_CASE("getAvailablePositionsForBlock for Simple Case MOVABLE_BLOCK_3XV","[Available][Positions][For][Block][Simple][Case][MOVABLE_BLOCK_3XV]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto block = Block{
            Direction::VERTICAL,
            BlockType::MOVABLE_BLOCK_3XV,
            X{2},
            Y{2},
            Size{3}
    };

    const auto grid = Grid{
        {block},
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = x == 2 && 2<=y && y<=4; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{{2,0},{2,1},{2,3}};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}

TEST_CASE("getAvailablePositionsForBlock for Simple Case FIXED_BLOCK","[Available][Positions][For][Block][Simple][Case][FIXED_BLOCK]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto block = Block{
            Direction::NONE,
            BlockType::FIXED_BLOCK,
            X{2},
            Y{2},
            Size{1}
    };

    const auto grid = Grid{
        {block},
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = x == 2 && y == 2; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}

// TODO refactor code getAvailablePositionsForBlock for Advanced Cases
TEST_CASE("getAvailablePositionsForBlock for Advanced Case MOVABLE_BLOCK_2XH","[Available][Positions][For][Block][Advanced][Case][MOVABLE_BLOCK_2XH]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto fixed1 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{1},
        Y{0},
        Size{1}
    };

    const auto block = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_2XH,
        X{2},
        Y{0},
        Size{2}
    };

    const auto fixed2 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{4},
        Y{0},
        Size{1}
    };



    const auto grid = Grid{
        {fixed1,block,fixed2}  
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = 1<=x && x<=4 && y == 0; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}

TEST_CASE("getAvailablePositionsForBlock for Advanced Case MAIN_BLOCK","[Available][Positions][For][Block][Advanced][Case][MAIN_BLOCK]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto fixed1 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{1},
        Y{0},
        Size{1}
    };

    const auto block = Block{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{2},
        Y{0},
        Size{2}
    };

    const auto fixed2 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{4},
        Y{0},
        Size{1}
    };



    const auto grid = Grid{
        {fixed1,block,fixed2}  
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = 1<=x && x<=4 && y == 0; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}



TEST_CASE("getAvailablePositionsForBlock for Advanced Case MOVABLE_BLOCK_3XH","[Available][Positions][For][Block][Advanced][Case][MOVABLE_BLOCK_3XH]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto fixed1 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{1},
        Y{0},
        Size{1}
    };

    const auto block = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_3XH,
        X{2},
        Y{0},
        Size{3}
    };

    const auto fixed2 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{5},
        Y{0},
        Size{1}
    };



    const auto grid = Grid{
        {fixed1,block,fixed2}  
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = 1<=x && x<=5 && y == 0; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}

TEST_CASE("getAvailablePositionsForBlock for Advanced Case MOVABLE_BLOCK_2XV","[Available][Positions][For][Block][Advanced][Case][MOVABLE_BLOCK_2XV]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto fixed1 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{0},
        Y{1},
        Size{1}
    };

    const auto block = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{0},
        Y{2},
        Size{2}
    };

    const auto fixed2 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{0},
        Y{4},
        Size{1}
    };



    const auto grid = Grid{
        {fixed1,block,fixed2}  
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = x == 0 && 1<=y && y<=4; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}

TEST_CASE("getAvailablePositionsForBlock for Advanced Case MOVABLE_BLOCK_3XV","[Available][Positions][For][Block][Advanced][Case][MOVABLE_BLOCK_3XV]") {
    using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
    using UnblockMe::Utils::Grid::getOccupiedPositions;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::set<Position>;
  
    const auto fixed1 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{0},
        Y{1},
        Size{1}
    };

    const auto block = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_3XV,
        X{0},
        Y{2},
        Size{3}
    };

    const auto fixed2 = Block{
        Direction::NONE,
        BlockType::FIXED_BLOCK,
        X{0},
        Y{5},
        Size{1}
    };



    const auto grid = Grid{
        {fixed1,block,fixed2},
    }; 

    const auto occupiedPositions = getOccupiedPositions(grid);

       for(int x = 0;x<occupiedPositions.size();x++) {
        for(int y = 0;y<occupiedPositions[0].size();y++) {
            
            const auto isOccupied = x == 0 && 1<=y && y<=5; 
            if (isOccupied) {
                  REQUIRE(occupiedPositions[x][y]  == true);
            }
            else {
                  REQUIRE(occupiedPositions[x][y]  == false);
            }
        }
    }

    const auto correctPlacements = Positions{};
    const auto placements = getAvailablePositionsForBlock(block,occupiedPositions);
    const auto placementsSet=Positions(placements.begin(),placements.end());
    REQUIRE(placementsSet == correctPlacements);
}

TEST_CASE("getAdjacentGrids simple case","[Get][Adjacent][Grids][1]") {
    using std::set;
    using UnblockMe::Utils::Grid::getAdjacentGrids;
    const auto dirH = Direction::HORIZONTAL;
    const auto typeM2XH =  BlockType::MOVABLE_BLOCK_2XH;
    
    Grid grid{{
        Block{
            dirH,
            typeM2XH,
            X{0},
            Y{0},
            Size{2}
        }
    }};

    const auto adjacentGrids = set<Grid>{{
       Grid{
            Block{
                dirH,
                typeM2XH,
                X{1},
                Y{0},
                Size{2}
            }
        },

        Grid{
            Block{
                dirH,
                typeM2XH,
                X{2},
                Y{0},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{3},
                Y{0},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{4},
                Y{0},
                Size{2}
            }
        }   
    }};

    REQUIRE(getAdjacentGrids(grid) == adjacentGrids);
}

TEST_CASE("getAdjacentGrids simple case 2","[Get][Adjacent][Grids][2]") {
    using std::set;
    using UnblockMe::Utils::Grid::getAdjacentGrids;
    const auto dirH = Direction::HORIZONTAL;
    const auto typeM2XH =  BlockType::MOVABLE_BLOCK_2XH;
    
    Grid grid{{
        Block{
            dirH,
            typeM2XH,
            X{0},
            Y{0},
            Size{2}
        },
        Block{
            dirH,
            typeM2XH,
            X{4},
            Y{0},
            Size{2}
        }

    }};

    const auto adjacentGrids = set<Grid>{{
       Grid{
            Block{
                dirH,
                typeM2XH,
                X{1},
                Y{0},
                Size{2}
            },
            Block{
                dirH,
                typeM2XH,
                X{4},
                Y{0},
                Size{2}
            }
        },

        Grid{
            Block{
                dirH,
                typeM2XH,
                X{2},
                Y{0},
                Size{2}
            },
            Block{
                dirH,
                typeM2XH,
                X{4},
                Y{0},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{0},
                Y{0},
                Size{2}
            },
            Block{
                dirH,
                typeM2XH,
                X{2},
                Y{0},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{0},
                Y{0},
                Size{2}
            },
            Block{
                dirH,
                typeM2XH,
                X{3},
                Y{0},
                Size{2}
            }
        }   
    }};
    REQUIRE(getAdjacentGrids(grid) == adjacentGrids);
}

TEST_CASE("getAdjacentGrids simple case 3","[Get][Adjacent][Grids][3]") {
    using std::set;
    using UnblockMe::Utils::Grid::getAdjacentGrids;
    const auto dirH = Direction::HORIZONTAL;
    const auto dirV = Direction::VERTICAL;
    const auto typeM2XH =  BlockType::MOVABLE_BLOCK_2XH;
    const auto typeM2XV =  BlockType::MOVABLE_BLOCK_2XV;
    
    Grid grid{
        Block{
            dirH,
            typeM2XH,
            X{1},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{1},
            Size{2}
        }
    };



    const auto adjacentGrids = set<Grid>{{
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{0},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{2},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{3},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{4},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{1},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{0},
            Size{2}
        }
    },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{1},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{2},
            Size{2}
        }
    },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{1},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{3},
            Size{2}
        }
    },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{1},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{4},
            Size{2}
        }
    }
      
    }};


    REQUIRE(getAdjacentGrids(grid) == adjacentGrids);
}


TEST_CASE("getAdjacentGrids simple case 4","[Get][Adjacent][Grids][4]") {
    using std::set;
    using UnblockMe::Utils::Grid::getAdjacentGrids;
    const auto dirH = Direction::HORIZONTAL;
    const auto dirV = Direction::VERTICAL;
    const auto typeM2XH =  BlockType::MOVABLE_BLOCK_2XH;
    const auto typeM2XV =  BlockType::MOVABLE_BLOCK_2XV;
    
    Grid grid{
        Block{
            dirH,
            typeM2XH,
            X{0},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{1},
            Size{2}
        }
    };



    const auto adjacentGrids = set<Grid>{{
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{1},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{2},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{3},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
        Grid{
            Block{
                dirH,
                typeM2XH,
                X{4},
                Y{0},
                Size{2}
            },
            Block{
                dirV,
                typeM2XV,
                X{0},
                Y{1},
                Size{2}
            }
        },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{0},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{2},
            Size{2}
        }
    },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{0},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{3},
            Size{2}
        }
    },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{0},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{4},
            Size{2}
        }
    },
    Grid{
        Block{
            dirH,
            typeM2XH,
            X{0},
            Y{0},
            Size{2}
        },
        Block{
            dirV,
            typeM2XV,
            X{0},
            Y{4},
            Size{2}
        }
    }
    }};


    REQUIRE(getAdjacentGrids(grid) == adjacentGrids);
}