
#include <set>
#include "grid.hpp"

namespace UnblockMe::Utils::Grid {

    Block::Block(
        Direction direction,
        BlockType type,
        unsigned char xHeadPos,
        unsigned char yHeadPos,
        unsigned char size
     ) : 
     direction{direction},
     type{type},
     xHeadPos{xHeadPos},
     yHeadPos{yHeadPos},
     size{size} {

    }
    auto Block::operator==(const Block& otherBlock)->bool const {
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

    auto BlockHash::operator()(const Block& block)->std::size_t const{
        using std::size_t;

        size_t hash = block.xHeadPos*10000 +block.yHeadPos*1000 +block.size*100 + static_cast<int>(block.type)*10 + static_cast<int>(block.direction); 
        return hash;
    };

    constexpr auto BlockEquals::operator()(const Block& lhs, const Block& rhs)->bool const{
        return lhs.size== rhs.size;
    };

    
}