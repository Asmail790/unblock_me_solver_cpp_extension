#ifndef UnblockMe_Utils_Grid
#define UnblockMe_Utils_Grid

#include <unordered_set>
#include <utility>
namespace UnblockMe::Utils::Grid {

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

    class Block{
        public:
            Block( 
                Direction direction,
                BlockType type,
                unsigned char xHeadPos,
                unsigned char yHeadPos,
                unsigned char size
            );

            const Direction direction;
            const BlockType type;
            const unsigned char xHeadPos;
            const unsigned char yHeadPos;
            const unsigned char size;
            auto operator==(const Block& otherBlock)->bool const;
    };

    // or function/lambda instead or std::hash operator overloading?
    class BlockHash{
        public:
          auto operator()(const Block &block)->std::size_t const;
    };

    class BlockEquals{
        public:
          constexpr auto operator()(const Block& lhs, const Block& rhs)->bool const;
    };
    using Grid = std::unordered_set<Block>;
}

#endif