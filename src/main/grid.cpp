#include "grid.hpp"
#include "block.hpp"
#include <stdexcept>
#include <string>
#include <set>
#include <deque>
#include <tuple>
namespace UnblockMe::Utils::Grid {





auto getOccupiedPositions(const Grid& grid)->std::array<std::array<bool,6>,6>{
    using UnblockMe::Utils::Block::getOccupiedPositions;
    using OccupiedPositionsGrid = std::array<std::array<bool,6>,6>;

    OccupiedPositionsGrid occupiedPositions{};// false array
    occupiedPositions.fill(std::array<bool,6>{});
    for(auto block:grid) {
        auto occupied = getOccupiedPositions(block);
        for(auto pair: occupied) {

            const auto x = pair.first;
            const auto y = pair.second;


            occupiedPositions.at(x).at(y) = true;
        }
    }
    return occupiedPositions;
}

auto getAvailablePositionsForBlock(const Block& block, const std::array<std::array<bool,6>,6>& occupied)->std::vector<std::pair<unsigned char,unsigned char>>{
    using UnblockMe::Utils::Block::BlockType;
    using Position = std::pair<unsigned char,unsigned char>;
    using Positions = std::vector<Position>;




    Positions available{};
    if (block.type == BlockType::MAIN_BLOCK || block.type == BlockType::MOVABLE_BLOCK_2XH || block.type == BlockType::MOVABLE_BLOCK_3XH) {
        auto xStart = block.xHeadPos;
        const auto yStart = block.yHeadPos;
        const auto blockSize = (block.type == BlockType::MAIN_BLOCK || block.type == BlockType::MOVABLE_BLOCK_2XH)?2:3; // Todo use inline getSizeFunction

        for(int x = xStart-1; 0<=x;x--) {
            const auto isBlockedOff = occupied.at(x).at(yStart);
            
            if (isBlockedOff) break;
            available.emplace_back(x,yStart);
        }


        for (int x = xStart+1;x<=6-blockSize;x++) {
            const auto newXEnd = x + (blockSize-1);
            const auto isBlockedOff = occupied.at(newXEnd).at(yStart);

            
            if (isBlockedOff) break;
            available.emplace_back(x,yStart);
        }
    }

    else if(block.type == BlockType::MOVABLE_BLOCK_2XV || block.type == BlockType::MOVABLE_BLOCK_3XV) {
        const auto xStart = block.xHeadPos;
        const auto yStart = block.yHeadPos;
        const auto blockSize = block.type == BlockType::MOVABLE_BLOCK_2XV ?2:3; 

        for(int y = yStart-1; 0 <=y;y--) {
            const auto isBlockedOff = occupied.at(xStart).at(y);
            
            if (isBlockedOff) break;
            available.emplace_back(xStart,y);
        }

        for(int y = yStart +1;y <=6-blockSize;y++){
            const auto newYEnd = y + (blockSize-1);
            const auto isBlockedOff = occupied.at(xStart).at(newYEnd);
            
            if (isBlockedOff) break;
            available.emplace_back(xStart,y);
        }

    }

    
    else if(block.type == BlockType::FIXED_BLOCK) {
        // can't replace since fixed
    }

    // todo make else a debug variable
    else {
        throw std::invalid_argument("invalid blocktype!!");
    }

    return available;
}

    auto getAdjacentGrids(const Grid& grid)->std::set<Grid> {
        using UnblockMe::Utils::Grid::getOccupiedPositions;
        using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
        using UnblockMe::Utils::Block::Y;
        using UnblockMe::Utils::Block::X;
        using UnblockMe::Utils::Block::Size;
        using std::set;


        const auto occupiedPositions = getOccupiedPositions(grid);
        auto grids = std::set<Grid>{};
        std::set<Block>::iterator it;
        for (const auto& block:grid) {
            for (const auto& pos: getAvailablePositionsForBlock(block,occupiedPositions)) {
                auto copyOfGrid =  Grid{ grid.begin(),grid.end()}; 
                copyOfGrid.erase(block);
                
              
                
                copyOfGrid.emplace(
                    block.direction,
                    block.type,
                    X{pos.first},
                    Y{pos.second},
                    Size{block.size}
                );

                grids.insert(copyOfGrid);   
            }
        }
        return grids;
    }
}