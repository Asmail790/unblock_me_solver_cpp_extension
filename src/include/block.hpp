#ifndef UnblockMe_Utils_Block
#define UnblockMe_Utils_Block

#include <unordered_set>
#include <utility>
namespace UnblockMe::Utils::Block {

    enum class Direction {
        VERTICAL,
        HORIZONTAL,
        NONE,
    };

    enum class BlockType {
        MAIN_BLOCK,
        MOVABLE_BLOCK_2XV,
        MOVABLE_BLOCK_3XV,
        MOVABLE_BLOCK_2XH,
        MOVABLE_BLOCK_3XH,
        FIXED_BLOCK,
    };

    struct X {
        const unsigned char value;
};

    struct Y {
        const unsigned char value;
    };

    struct Size {
        const unsigned char value;
    };

    class Block{
        public:
            Block( 
                Direction direction,
                BlockType type,
                X xHeadPos,
                Y yHeadPos,
                Size size
            );

            const Direction direction;
            const BlockType type;
            const unsigned char xHeadPos;
            const unsigned char yHeadPos;
            const unsigned char size;
            auto operator==(const Block& otherBlock)const ->bool;
    };



    std::size_t hashOfBlock(const Block &block);
    bool equalsOfBlock(const Block& lhs, const Block& rhs);
    //using Grid = std::unordered_set<Block>;
}

#endif