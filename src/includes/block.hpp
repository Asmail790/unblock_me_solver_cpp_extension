#ifndef UnblockMe_Utils_Block
#define UnblockMe_Utils_Block

#include <unordered_set>
#include <utility>
#include <vector>
#include <array>
#include <stdexcept>
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

        Block(const Block& other);
        Block(Block&& other) noexcept;

        auto operator=(const Block& other)->Block& = delete;
        auto operator=(Block&& other) noexcept->Block& = delete;

            
        public:
            const Direction direction;
            const BlockType type;
            const unsigned char xHeadPos;
            const unsigned char yHeadPos;
            const unsigned char size;
            auto operator==(const Block& otherBlock)const ->bool;
            auto operator<(const Block& otherBlock)const ->bool;
    };


    auto hashOfBlock(const Block &block)->std::size_t;
    auto equalsOfBlock(const Block& lhs, const Block& rhs)->bool;

    inline Direction getDirection(const Block &block) {
        BlockType type = block.type;
        if (type == BlockType::FIXED_BLOCK) {
            return Direction::NONE;
        }

         if (type == BlockType::MAIN_BLOCK || type == BlockType::MOVABLE_BLOCK_2XH ||type == BlockType::MOVABLE_BLOCK_3XH ) {
            return Direction::HORIZONTAL;
        }

         if (type == BlockType::MOVABLE_BLOCK_2XV ||type == BlockType::MOVABLE_BLOCK_3XV) {
             return Direction::VERTICAL;
        }

        throw std::invalid_argument("NO BlockType match");
    }

    inline unsigned char getSize(const Block &block) {
        BlockType type = block.type;
        if (type == BlockType::FIXED_BLOCK) {
            return 1;
        }

         if (type == BlockType::MAIN_BLOCK || type == BlockType::MOVABLE_BLOCK_2XH || type == BlockType::MOVABLE_BLOCK_2XV ) {
            return 2;
        }

         if (type == BlockType::MOVABLE_BLOCK_3XH  ||type == BlockType::MOVABLE_BLOCK_3XV) {
             return 3;
        }

        throw std::invalid_argument("NO BlockType match");
    }

    // reuse vector or create it each time ?
    // use array since at most 6 positions occupied ?
     auto getOccupiedPositions(const Block& block)->std::vector<std::pair<unsigned char,unsigned char>>;

}

#endif