#ifndef UnblockMe_Utils_Entry_Header
#define UnblockMe_Utils_Entry_Header

#include <utility>
#include <vector>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <map>
#include "grid.hpp"
#include "graph.hpp"


namespace UnblockMe::Utils::Entry {
    using UnblockMe::Utils::Grid::Grid;
    using UnblockMe::Utils::Graph::StepDescription;
    using UnblockMe::Utils::Block::Block;
    using UnblockMe::Utils::Block::BlockType;
    const unsigned char GRID_SIZE = 6;


    enum class  MainBlockLabel: unsigned char{};
    enum class  Vertical2XBlockLabel: unsigned char{};
    enum class  Vertical3XBlockLabel: unsigned char{};
    enum class  Horizontal2XBlockLabel: unsigned char{};
    enum class  Horizontal3XBlockLabel: unsigned char{};
    enum class  FixedBlockLabel: unsigned char{};
    enum class  GridLabel: unsigned char{};
  
    class MLClassIds{
        public:
            unsigned char mainBlock;
            unsigned char vertical2XBlock;
            unsigned char vertical3XBlock;
            unsigned char horizontal2XBlock;
            unsigned char horizontal3XBlock;
            unsigned char fixedBlock;
            unsigned char grid;

            MLClassIds(
                const MainBlockLabel mainBlock,
                const Vertical2XBlockLabel vertical2XBlock,
                const Vertical3XBlockLabel vertical3XBlock,
                const Horizontal2XBlockLabel horizontal2XBlock,
                const Horizontal3XBlockLabel horizontal3XBlock,
                const FixedBlockLabel fixedBlock,
                const GridLabel grid
            ){
                this->mainBlock =static_cast<unsigned char>(mainBlock); 
                this->vertical2XBlock =static_cast<unsigned char>(vertical2XBlock); 
                this->vertical3XBlock =static_cast<unsigned char>(vertical3XBlock); 
                this->horizontal2XBlock =static_cast<unsigned char>(horizontal2XBlock); 
                this->horizontal3XBlock =static_cast<unsigned char>(horizontal3XBlock); 
                this->fixedBlock =static_cast<unsigned char>(fixedBlock); 
                this->grid =static_cast<unsigned char>(grid); 
            }
    };

    struct Top{
        float value;
    };
    struct Left{
        float value;
    };

    struct Right{ 
        float value;
    };
    
    struct Bottom{ 
        float value;
    };

    struct StepSizeX{
        float value;
    };
    struct StepSizeY{
        float value;
    };

    enum class  Class_: unsigned char{};

    class  GridProperties{
        public:
            float top;
            float left;
            float stepSizeX;
            float stepSizeY;

            GridProperties(
                const Top top,
                const Left left,
                const StepSizeX stepSizeX,
                const StepSizeY stepSizeY
            ):
            top{top.value},
            left{left.value},
            stepSizeX{stepSizeX.value},
            stepSizeY{stepSizeY.value}
            {}
    };


    class BoundingBox{
        public:
            const float left;
            const float top;
            const float right;
            const float bottom;
            const unsigned char class_;

            BoundingBox(
                const Left left,
                const Top top,
                const Right right,
                const Bottom bottom,
                const Class_ class_
            ) : 
            left{left.value},
            top{top.value},
            right{right.value},
            bottom{bottom.value},
            class_{static_cast<unsigned char>(class_)}
            {}
          
            auto width()const->float;

            auto height()const->float;

            auto topLeft()const->std::pair<float,float>;

            auto operator==(const BoundingBox& other)const->bool;
    };

    class NextStep {
        public:
            NextStep(
                const BoundingBox& from,
                const BoundingBox& to,
                const std::string& message 
            ): 
            from{from},
            to{to},
            message{message} {}

            const BoundingBox from;
            const BoundingBox to;
            const std::string message;
    };


    auto convertToBlockCoordinate(const std::pair<int,int>& coordinate, const GridProperties& gridProperties_)->std::pair<unsigned char,unsigned char>;

    auto  mlClassIdToBlockType( const BoundingBox& box, MLClassIds mlClassIds_)->UnblockMe::Utils::Block::BlockType;

    auto  BlockTypeToMLlClassId(const Block& block, const MLClassIds mlClassIds_)->unsigned char;

    auto convertToGrid(const std::vector<BoundingBox>&  blocks, const MLClassIds& mlClassIds_, const GridProperties& gridProperties)->Grid;

    auto convertToImageCoordinate(unsigned char logicalX,unsigned char logicalY, const GridProperties& gridProperties_)->std::pair<float,float>;

    auto convertToNextStep(const StepDescription& step, const GridProperties& gridProperties,const MLClassIds& mlClassIds)->NextStep;





    class IGuider{
        public:
            virtual std::vector<NextStep> inferAllSteps(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox) = 0;
            virtual NextStep inferOneStep(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox) = 0;
    };

    class SimpleGuider: public IGuider{
        using width = float;
        using height = float;
        using BlockImageProperies = std::map<UnblockMe::Utils::Block::BlockType,std::pair<width,height>>;

        private:
            std::optional<GridProperties> gridProperties =  std::nullopt;
            std::optional<MLClassIds> mlClassIds =  std::nullopt;
            std::optional<BlockImageProperies> blockImageProperties =  std::nullopt;
            
            auto setGridProperties(const BoundingBox& grid)->void;
            auto setBlockImageProperties(const std::vector<BoundingBox> blockBoundingBoxes, MLClassIds mlClassIds_)->void;
            auto setUpGobals(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox)->void;
        
        public:
            auto setMLClassIds(const MLClassIds& ids)->void;
            
            std::vector<NextStep> inferAllSteps(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox) override;
            NextStep inferOneStep(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox) override;
    };
       

}

#endif