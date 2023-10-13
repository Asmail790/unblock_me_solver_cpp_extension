
#include <set>
#include <vector>
#include <stdexcept>
#include <tuple>
#include "block.hpp"

namespace UnblockMe::Utils::Block {
    // use std::move for xHeadPos.value ?
     
    Block::Block(
        BlockType type,
        X xHeadPos,
        Y yHeadPos
     ) : type{type}, xHeadPos{xHeadPos.value}, yHeadPos{yHeadPos.value} {}

    auto Block::operator==(const Block& otherBlock) const ->bool  {
        if (this->type != otherBlock.type) {
            return false;
        }

        if (this->xHeadPos != otherBlock.xHeadPos){
            return false;
        }

        if (this->yHeadPos != otherBlock.yHeadPos){
            return false;
        }
        return true;
    }

    Block::Block(const Block& other) : 
    type{other.type},
    xHeadPos{other.xHeadPos},
    yHeadPos{other.yHeadPos} {};

    
    Block::Block(Block&& other) noexcept : 
    type{other.type},
    xHeadPos{other.xHeadPos},
    yHeadPos{other.yHeadPos} {};

   

    auto  Block::operator<(const Block& otherBlock)const -> bool {
       const auto t1 = std::tuple(this->type, this->xHeadPos,this->yHeadPos);
       const auto t2 = std::tuple(otherBlock.type, otherBlock.xHeadPos,otherBlock.yHeadPos);
       return t1 < t2;
    }



    std::size_t hashOfBlock(const Block &block) {
        using std::size_t;

        size_t hash = block.xHeadPos*1 +block.yHeadPos*10 + static_cast<int>(block.type)*100; 
        return hash;
    }
    bool equalsOfBlock(const Block& lhs, const Block& rhs){
          return lhs == rhs;
    }

    auto getOccupiedPositions(const Block& block)->std::vector<std::pair<unsigned char,unsigned char>> {
        using std::vector;
        using std::pair;
        using output = std::vector<pair<unsigned char,unsigned char>>;
        

        if (block.type == BlockType::FIXED_BLOCK) {
            return output{pair{block.xHeadPos,block.yHeadPos}};
        }

        if (block.type == BlockType::MOVABLE_BLOCK_2XH ||  block.type == BlockType::MAIN_BLOCK) {
            unsigned char xStart = block.xHeadPos;
            unsigned char y = block.yHeadPos;
            return output{
                pair{xStart,y},
                pair{xStart+1,y},
            };
        }

        if (block.type == BlockType::MOVABLE_BLOCK_3XH) {
            unsigned char xStart = block.xHeadPos;
            unsigned char y = block.yHeadPos;
            return output{
                pair{xStart,y},
                pair{xStart+1,y},
                pair{xStart+2,y},
            };
        }

        if (block.type == BlockType::MOVABLE_BLOCK_2XV){
            unsigned char x = block.xHeadPos;
            unsigned char yStart = block.yHeadPos;
            return output{
                pair{x,yStart},
                pair{x,yStart +1},
            };
        }

        
        if (block.type == BlockType::MOVABLE_BLOCK_3XV){
            unsigned char x = block.xHeadPos;
            unsigned char yStart = block.yHeadPos;

          return output{
                pair{x,yStart},
                pair{x,yStart +1},
                pair{x,yStart +2},
            };
        }

        // Todo set up variable for deplovment and if true throw error
        // improve message
        //asdasd
        throw std::invalid_argument{"illegal blocktype"};
    }

}