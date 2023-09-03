
#include <set>
#include "block.hpp"

namespace UnblockMe::Utils::Block {
    // use std::move for xHeadPos.value ?
     
    Block::Block(
        Direction direction,
        BlockType type,
        X xHeadPos,
        Y yHeadPos,
        Size size
     ) : 
     direction{direction},
     type{type},
     xHeadPos{xHeadPos.value},
     yHeadPos{yHeadPos.value},
     size{size.value} {

    }
    auto Block::operator==(const Block& otherBlock) const ->bool  {
        if (this->direction != otherBlock.direction) {
            return false;
        }

        if (this->type != otherBlock.type) {
            return false;
        }

        if (this->xHeadPos != otherBlock.xHeadPos){
            return false;
        }

        if (this->yHeadPos != otherBlock.yHeadPos){
            return false;
        }

        if (this->size != otherBlock.size) {
            return false;
        }
        return true;
    }


    std::size_t hashOfBlock(const Block &block) {
        using std::size_t;

        size_t hash = block.xHeadPos*10000 +block.yHeadPos*1000 +block.size*100 + static_cast<int>(block.type)*10 + static_cast<int>(block.direction); 
        return hash;
    }
    bool equalsOfBlock(const Block& lhs, const Block& rhs){
          return lhs == rhs;
    }
}