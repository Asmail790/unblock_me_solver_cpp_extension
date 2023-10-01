#define CATCH_CONFIG_MAIN

#include <stdexcept>
#include <list>

#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
#include "graph.hpp"
#include <tuple>
#include <iostream>
#include <string>
#include<cstdlib>


#include <tuple>
#include <array>

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

auto SolveSimplePuzzle() {
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

    const auto start = Node{b1,b2,b3,b4};
    return findShortestPath(start);
}


auto prepare() {
    srand((unsigned) time(NULL));
    auto grids = std::vector<std::vector<std::tuple<char,char,char,char>>>{};

    for (int i=0; i < 20; i++) {
        auto grid = std::vector<std::tuple<char,char,char,char>>{}; 

        for(int j=0; j < 10; j++){
            char xStart = rand() % 6;
            char yStart = rand() % 6;
            char xSize = 1 + (rand() % 2);
            char ySize = 1 + (rand() % 2);
            char xEnd = xStart + xSize;
            char yEnd = yStart + ySize;  
            grid.emplace_back(xStart,xEnd,yStart,yEnd);
        }

        grids.push_back(grid);
    }
    return grids;
}

auto do_overlap(const std::tuple<char,char,char,char>& rec1, const std::tuple<char,char,char,char>& rec2)->bool{
    bool horizantalSpaceExist = std::get<1>(rec1)  <= std::get<0>(rec2) || std::get<1>(rec2) <= std::get<0>(rec1);   
    bool verticalSpaceExist =   std::get<3>(rec1)  <= std::get<2>(rec2) || std::get<3>(rec2) <= std::get<2>(rec1);
    return !(horizantalSpaceExist || verticalSpaceExist); 

}

auto fakeSolvePuzzle(const std::vector<std::vector<std::tuple<char,char,char,char> >>& grids) {
    auto res = std::vector<bool>{};

    for(const auto& grid: grids){
        for ( size_t i =0; i < grid.size();i++) {
            for(size_t j  = 0; j < grid.size();j++) {
                for(char x = 0; x < 6;x++){
                    for (char y = 0; y < 6; y++) {
                        auto rectangle_i = grid[i];
                        auto rectangle_j = grid[j];
                        char xStart  = std::get<0>(rectangle_i);
                        char xEnd = std::get<1>(rectangle_i);
                        char yStart = std::get<2>(rectangle_i);
                        char yEnd = std::get<3>(rectangle_i);

                        char newXStart = x;
                        char newYStart = y;
                        char newXEnd =  x + (xEnd-xStart);
                        char newYEnd =  y + (yEnd - yStart);
                        auto new_rec = std::tuple{newXStart,newXEnd,newYStart,newYEnd};
                        
                        bool insideGrid =newXEnd < 6 && newYEnd < 6;
                        bool same_rectangle = i == j; 
                    
                        bool xStartSame = x == xStart;
                        bool yStartSame = y == yStart;
                        bool samePostion = xStartSame && yStartSame;


                        bool overlap = do_overlap(new_rec,rectangle_j);
                        bool add_to_list = overlap && (! same_rectangle) && insideGrid && (! samePostion);
                        res.push_back(add_to_list);
                     
                    }
                }
            }
        }
    } 

    return res;
}

auto prepareSumOfTwo(){
    srand((unsigned) time(NULL));
    auto a = std::array<int,1000>{};
    auto b = std::array<int,1000>{};

    for (int i=0; i < 1000; i++) {
        a[i] = rand() % 10000;
        b[i] = rand() % 10000; 
    }
    return std::pair<std::array<int,1000>,std::array<int,1000>>{a,b};
}

auto sumOfTwo(const std::array<int,1000>& a,const std::array<int,1000>& b ) {
    auto res = std::array<int,1000>{};

    for(int i = 0; i < a.size(); i++) {
        res[i] = a[i] + b[i];
    }

    return res;
}


auto SolveAdvancedPuzzle() {
    
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
    return findShortestPath(start);
}


TEST_CASE("BenchMark") {

    // TODO BENCHMARK_ADVANCED and setUpSimplePuzzleFunction
    //BENCHMARK("SimplePuzzle") {
    //    return SolveSimplePuzzle();
    //};

    // TODO BENCHMARK_ADVANCED and setUpAdvancedPuzzle
    //BENCHMARK("AdvancedPuzzle") {
    //    return SolveAdvancedPuzzle();
    //};

    BENCHMARK("AdvancedPuzzle") {
        const auto data = prepare();
        return fakeSolvePuzzle(data);
    };

    //BENCHMARK("AdvancedPuzzle") {
    //    const auto data = prepareSumOfTwo();
    //    return sumOfTwo(data.first,data.second);
    //};
}