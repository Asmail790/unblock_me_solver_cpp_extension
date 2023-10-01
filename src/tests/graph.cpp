#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "graph.hpp"
#include <list>
#include <stdexcept>

#include <iostream>
#include <string>
using UnblockMe::Utils::Block::Block;
using UnblockMe::Utils::Block::BlockType;
using UnblockMe::Utils::Block::Direction;
using UnblockMe::Utils::Block::Size;
using UnblockMe::Utils::Block::X;
using UnblockMe::Utils::Block::Y;
using UnblockMe::Utils::Graph::Graph;
using UnblockMe::Utils::Graph::Node;
using UnblockMe::Utils::Graph::StepDescription;
using UnblockMe::Utils::Graph::findShortestPath;
using UnblockMe::Utils::Graph::isTerminalNode;
TEST_CASE("Graph Basic", "[Graph][Basic]")
{
    Node n1 = Node{
        Block{
            Direction::HORIZONTAL,
            BlockType::MOVABLE_BLOCK_2XH,
            X{0},
            Y{0},
            Size{2}
        }
    };

    Node n2 = Node{};

    Node n3 = Node{
          Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{0},
            Y{0},
            Size{2}
        }
    };

    Node n4 = Node{
          Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{2},
            Y{0},
            Size{2}
        }
    };

    Graph graph{};
        SECTION("Test add node","Test adding old node returns same id") {
        REQUIRE(graph.add(n1) == 0);
        REQUIRE(graph.add(n1) == 0);
        REQUIRE(graph.add(n2) == 1);
        REQUIRE(graph.add(n2) == 1);
    }

    // TODO fixa beskrivingnen och namn, istället för add
    // bör make n1 predesscor of n2
    // och själv klart kan n2 bara ha en predesscor och 
    // därmed REQUIRE_FALSE sant
    SECTION("Test add edge","Test adding old edge node returns id") {
        REQUIRE(graph.add(n1,n2));
        REQUIRE(graph.add(n1,n3));
        REQUIRE_FALSE(graph.add(n2,n3));
    }
    
    SECTION("Test exist") {
        graph.add(n1);
        REQUIRE(graph.exist(n1));

        graph.add(n2,n3);
        REQUIRE(graph.exist(n2));
        REQUIRE(graph.exist(n3));
    }

    // TODO ändra namn getPath
    SECTION("Test getPath") {
        graph.add(n1,n2);
        graph.add(n2,n3);
        graph.getPath(n3);
        REQUIRE(graph.getPath(n3) == std::list<Node>{n1,n2,n3});
    }
   //findShortestPath(initalNode);

}

TEST_CASE("Graph describeAction describePath", "[Graph][describePath]")
{
    Block b1 =    
        Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{0},
            Y{0},
            Size{2}
        };

    Block b2 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{1},
            Y{0},
            Size{2}
    };

    Block b3 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{2},
            Y{0},
            Size{2}
    };

    Block b4 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{3},
            Y{0},
            Size{2}
    };

    Block b5 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{4},
            Y{0},
            Size{2}
    };
    Node n1 = Node{b1};


    Node n2 = Node{b2};


    Node n3 = Node{b3};


    Node n4 = Node{b4};

    Node n5 = Node{b5};

    Graph g{};
    StepDescription desc = g.describeAction(n1,n2);
    REQUIRE( desc == StepDescription {
        b1, 
        X{1},
        Y{0}
    });

    StepDescription desc2 = g.describeAction(n2,n3);
    REQUIRE( desc2 == StepDescription {
        b2, 
        X{2},
        Y{0}
    });


    StepDescription desc3 = g.describeAction(n3,n4);
    REQUIRE( desc3 == StepDescription {
        b3, 
        X{3},
        Y{0}
    });

    StepDescription desc4 = g.describeAction(n4,n5);
    REQUIRE( desc4 == StepDescription {
        b4, 
        X{4},
        Y{0}
    });




    REQUIRE( g.add(n1,n2) == true);
    REQUIRE( g.add(n2,n3) == true);
    REQUIRE( g.add(n3,n4) == true);
    REQUIRE( g.add(n4,n5) == true);
    
    std::list<Node> path = g.getPath(n5);
    REQUIRE( path == std::list<Node>{n1,n2,n3,n4,n5});
    
    const auto edges = g.describePath(path);
    REQUIRE( edges == std::vector<StepDescription>{
        StepDescription {
            b1, 
            X{1},
            Y{0}
        },
        StepDescription {
            b2, 
            X{2},
            Y{0}
        },
        StepDescription {
            b3, 
            X{3},
            Y{0}
        },
        StepDescription {
            b4, 
            X{4},
            Y{0}
        }
        }
    );
}

TEST_CASE("isTerminalNode","[isTerminalNode]"){
        Block b1 =    
        Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{0},
            Y{2},
            Size{2}
    };

    const auto  simple_puzzle = Node{b1};
    Block b2 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{1},
            Y{2},
            Size{2}
    };

    Block b3 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{2},
            Y{2},
            Size{2}
    };

    Block b4 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{3},
            Y{2},
            Size{2}
    };

    Block b5 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{4},
            Y{2},
            Size{2}
    };

  
    Node n1 = Node{b1};
    Node n2 = Node{b2};
    Node n3 = Node{b3};
    Node n4 = Node{b4};
    Node n5 = Node{b5};
    REQUIRE_FALSE(isTerminalNode(n1));
    REQUIRE_FALSE(isTerminalNode(n2));
    REQUIRE_FALSE(isTerminalNode(n3));
    REQUIRE_FALSE(isTerminalNode(n4));
    REQUIRE(isTerminalNode(n5));




}

TEST_CASE("findShortestPath SimpleCase 1", "[findShortestPath][SimpleCase][1]"){

    Block b1 =    
        Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{0},
            Y{2},
            Size{2}
    };

    const auto  n1 = Node{b1};
    Block b2 =    
            Block{
            Direction::HORIZONTAL,
            BlockType::MAIN_BLOCK,
            X{4},
            Y{2},
            Size{2}
    };
    const auto n2 = Node{b2};

    const auto edges = std::vector<StepDescription>{
        StepDescription {
            b1, 
            X{4},
            Y{2}
        }
    };



    const auto pair = findShortestPath(n1);

 
    
    const auto path = std::list<Node>{n1,n2};
    REQUIRE(pair.first == edges);
    REQUIRE(pair.second == path);
    

}

TEST_CASE("findShortestPath SimpleCase 2", "[findShortestPath][SimpleCase][2]"){

    Block b1 =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{0},
        Y{2},
        Size{2}
    };


    Block b2 =    
        Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{2},
        Y{2},
        Size{2}
    };

    Block b3 =    
        Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{2},
        Y{0},
        Size{2}
    };

    Block b4 =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{4},
        Y{2},
        Size{2}
    };

    const auto n1 = Node{b1,b2};
    
    const auto n2 = Node{b1,b3};

    const auto n3 = Node{b4,b3};

    const auto edges = std::vector<StepDescription>{
        StepDescription {
            b2, 
            X{2},
            Y{0}
        },
        StepDescription {
            b1, 
            X{4},
            Y{2}
        }
    };


    const auto pair = findShortestPath(n1);   
    const auto path = std::list<Node>{n1,n2,n3};
    REQUIRE(pair.first == edges);
    REQUIRE(pair.second == path);
}

TEST_CASE("findShortestPath SimpleCase 3", "[findShortestPath][SimpleCase][3]"){

    Block b1 =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{0},
        Y{2},
        Size{2}
    };


    Block b2 =    
        Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_3XV,
        X{2},
        Y{0},
        Size{3}
    };

    Block b3 =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_3XH,
        X{2},
        Y{3},
        Size{3}
    };

    Block b4 =    
        Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{5},
        Y{3},
        Size{2}
    };


    Block b4_2 =    
        Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{5},
        Y{0},
        Size{2}
    };

    Block b3_3 =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_3XH,
        X{3},
        Y{3},
        Size{3}
    };

    Block b2_4 =    
        Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_3XV,
        X{2},
        Y{3},
        Size{3}
    };

    Block b1_5 =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{4},
        Y{2},
        Size{2}
    };



    const auto n1 = Node{b1,b2,b3,b4};
    
    const auto n2 = Node{b1,b2,b3,b4_2};

    const auto n3 = Node{b1,b2,b3_3,b4_2};

    const auto n4 = Node{b1,b2_4,b3_3,b4_2};

    const auto n5 = Node{b1_5,b2_4,b3_3,b4_2};

    const auto edges = std::vector<StepDescription>{
        StepDescription {
            b4, 
            X{5},
            Y{0},
        },
        StepDescription {
            b3, 
            X{3},
            Y{3},
        },
        StepDescription {
            b2, 
            X{2},
            Y{3},
        },
        StepDescription {
            b1, 
            X{4},
            Y{2},
        },

    };

    const auto pair = findShortestPath(n1);
    for (const auto grid:pair.second) {
         for (const auto block:grid) {
            std::string s ="None";
            if (block.direction==Direction::HORIZONTAL) {
                s = "HORIZONTAL";
            } else if (block.direction==Direction::VERTICAL){
                s = "VERTICAL";
            }
            std::string k = "Fixed";
            if (block.type==BlockType::MAIN_BLOCK) {
                k = "MAIN_BLOCK";
            } else if (block.type==BlockType::MOVABLE_BLOCK_2XH){
                k = "MOVABLE_BLOCK_2XH";
            } else if (block.type==BlockType::MOVABLE_BLOCK_3XH) {
                k = "MOVABLE_BLOCK_3XH";
            } else if(block.type == BlockType::MOVABLE_BLOCK_2XV){
                k = "MOVABLE_BLOCK_2XV";
            } else if (block.type == BlockType::MOVABLE_BLOCK_3XV) {
                k = "MOVABLE_BLOCK_3XV";
            }
            
        }
    }
    const auto path = std::list<Node>{n1,n2,n3,n4,n5};
    REQUIRE(pair.first == edges);
    REQUIRE(pair.second == path);
}

TEST_CASE("findShortestPath No Path Found", "[findShortestPath][No][Path][Found]"){

    Block b1 =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{0},
        Y{3},
        Size{2}
    };

    const auto invalidNode = Node{b1};
    REQUIRE_THROWS_AS(findShortestPath(invalidNode),std::logic_error);
}

TEST_CASE("findShortestPath Hard Puzzle", "[findShortestPath][Hard][puzzle]"){
 //Taken from Expert>Original>Puzzle 1
     Block b1 = Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_3XV,
        X{0},
        Y{0},
        Size{3}
    };


    Block b2 = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_2XH,
        X{0},
        Y{3},
        Size{2}
    };

    Block b3 = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_2XH,
        X{2},
        Y{3},
        Size{2}
    };

    Block b4 = Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{2},
        Y{0},
        Size{2}
    };

    Block b5 = Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_2XV,
        X{3},
        Y{1},
        Size{2}
    };

    Block b6 = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_3XH,
        X{3},
        Y{0},
        Size{3}
    };


    Block b7 = Block{
        Direction::VERTICAL,
        BlockType::MOVABLE_BLOCK_3XV,
        X{5},
        Y{2},
        Size{3}
    };

    Block b8 = Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_2XH,
        X{0},
        Y{4},
        Size{2}
    };

    Block b9 =  Block{
        Direction::HORIZONTAL,
        BlockType::MOVABLE_BLOCK_2XH,
        X{2},
        Y{4},
        Size{2}
    };

    Block main =    
        Block{
        Direction::HORIZONTAL,
        BlockType::MAIN_BLOCK,
        X{1},
        Y{2},
        Size{2}
    };
    const auto start = Node{b1,b2,b3,b4,b5,b6,b7,b8,b9,main};
    REQUIRE_NOTHROW(findShortestPath(start));
}