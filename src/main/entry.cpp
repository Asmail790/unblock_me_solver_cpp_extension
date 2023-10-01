#include <utility>
#include <vector>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <map>
#include "grid.hpp"
#include "graph.hpp"
#include "entry.hpp"


namespace UnblockMe::Utils::Entry {

            
    auto BoundingBox::width()const->float{
        return this->right - this->left;
    }

    auto BoundingBox::height()const->float{
        return this->bottom - this->top;
    }

    auto BoundingBox::topLeft()const->std::pair<float,float> {
        return std::pair<float,float>{this->left,this->top};
    }

    auto BoundingBox::operator==(const BoundingBox& other)const->bool{
        return left == other.left && top == other.top && right == other.right && bottom == other.bottom && class_ == other.class_;
    }

    auto findClosetMatch(float stepSize, float gridStart,float coordinate)->unsigned short{
        unsigned char closestXMatchIndex = -1;
        float closestXMatchValue = std::numeric_limits<float>::infinity();


        for(unsigned char i=0; i < GRID_SIZE; i++) {
            float curentStep = gridStart + i*stepSize;

            if ( std::abs(curentStep-coordinate) < closestXMatchValue){
                closestXMatchIndex = i;
                closestXMatchValue = std::abs(curentStep-coordinate);
            }
        }

        return closestXMatchIndex;

    }

    auto convertToBlockCoordinate(const std::pair<int,int>& coordinate, const GridProperties& gridProperties_)->std::pair<unsigned char,unsigned char>{
        int x = std::get<0>(coordinate);
        int y = std::get<1>(coordinate);

        float gridXStart = gridProperties_.left;
        float gridYStart = gridProperties_.top;

        float stepSizeX = gridProperties_.stepSizeX;
        float stepSizeY = gridProperties_.stepSizeY;

        unsigned char logicalXCoordinate = findClosetMatch(stepSizeX,gridXStart,x);
        unsigned char logicalYCoordinate = findClosetMatch(stepSizeY,gridYStart,y);


        return std::pair<unsigned char,unsigned char>(logicalXCoordinate,logicalYCoordinate );
    }

    auto  mlClassIdToBlockType( const BoundingBox& box,const MLClassIds mlClassIds_)->UnblockMe::Utils::Block::BlockType{
        const auto id = mlClassIds_;
        
        using UnblockMe::Utils::Block::BlockType;
        if (box.class_ == id.fixedBlock){
            return BlockType::FIXED_BLOCK;
        }

        else if (box.class_ == id.mainBlock){
            return BlockType::MAIN_BLOCK;
        }

        else if (box.class_ == id.horizontal2XBlock){
            return BlockType::MOVABLE_BLOCK_2XH;
        }

        else if (box.class_ == id.horizontal3XBlock){
            return BlockType::MOVABLE_BLOCK_3XH;
        }
        
        else if (box.class_ == id.vertical2XBlock){
            return BlockType::MOVABLE_BLOCK_2XV;
        }

        else if (box.class_ == id.vertical3XBlock){
            return BlockType::MOVABLE_BLOCK_3XV;
        }
    
        throw std::invalid_argument("no ML BLOCK ID class match.");
    }

    auto  BlockTypeToMLlClassId(const Block& block,const MLClassIds mlClassIds_)->unsigned char{
        const auto type = block.type;
        const auto id = mlClassIds_;
        
        
        using UnblockMe::Utils::Block::BlockType;
        if (type == BlockType::FIXED_BLOCK){
            return id.fixedBlock;
        }

        else if (type == BlockType::MAIN_BLOCK){
            return  id.mainBlock;
        }

        else if (type == BlockType::MOVABLE_BLOCK_2XH){
            return  id.horizontal2XBlock;
        }

        else if (type == BlockType::MOVABLE_BLOCK_3XH){
            return id.horizontal3XBlock;
        }
        
        else if (type ==BlockType::MOVABLE_BLOCK_2XV){
            return id.vertical2XBlock;
        }

        else if (type == BlockType::MOVABLE_BLOCK_3XV){
            return id.vertical3XBlock;;
        }
    
        throw std::invalid_argument("no Block Type  match ML class Id");
    }

    auto convertToGrid(const std::vector<BoundingBox>&  blocks, const MLClassIds& mlClassIds_, const GridProperties& gridProperties)->Grid{
        using UnblockMe::Utils::Block::BlockType;
        using UnblockMe::Utils::Block::Direction;
        using UnblockMe::Utils::Block::X;
        using UnblockMe::Utils::Block::Y;
        using UnblockMe::Utils::Block::Size;
        using UnblockMe::Utils::Block::Block;
        Grid grid{};
        const auto id = mlClassIds_;

        for(auto& box:blocks ){
            auto coordinate = convertToBlockCoordinate(box.topLeft(),gridProperties);
            
            if (box.class_ == id.fixedBlock){
                grid.emplace(Direction::NONE,BlockType::FIXED_BLOCK,X{coordinate.first},Y{coordinate.second},Size{1});
            }

            else if (box.class_ == id.mainBlock){
                 grid.emplace(Direction::HORIZONTAL,BlockType::MAIN_BLOCK,X{coordinate.first},Y{coordinate.second},Size{2});
            }

            else if (box.class_ == id.horizontal2XBlock){
                grid.emplace(Direction::HORIZONTAL,BlockType::MOVABLE_BLOCK_2XH,X{coordinate.first},Y{coordinate.second},Size{2});
            }

            else if (box.class_ == id.horizontal3XBlock){
                grid.emplace(Direction::HORIZONTAL,BlockType::MOVABLE_BLOCK_3XH,X{coordinate.first},Y{coordinate.second},Size{3});
            }
            
            else if (box.class_ == id.vertical2XBlock){
                grid.emplace(Direction::VERTICAL,BlockType::MOVABLE_BLOCK_2XV,X{coordinate.first},Y{coordinate.second},Size{2});
            }

            else if (box.class_ == id.vertical3XBlock){
                grid.emplace(Direction::VERTICAL,BlockType::MOVABLE_BLOCK_3XV,X{coordinate.first},Y{coordinate.second},Size{3});
            }
        }


        return grid;

    }

    auto convertToImageCoordinate(unsigned char logicalX,unsigned char logicalY, const GridProperties& gridProperties_)->std::pair<float,float>{

        auto  x = (float) logicalX;
        auto  y =  (float) logicalY;
        float gridXStart = gridProperties_.left;
        float gridYStart = gridProperties_.top;

        float stepSizeX = gridProperties_.stepSizeX;
        float stepSizeY = gridProperties_.stepSizeY;

        float xImageCoordinate = gridXStart + stepSizeX*x;
        float yImageCoordinate = gridYStart + stepSizeY*y;

        return std::pair(xImageCoordinate,yImageCoordinate);

    }

    auto convertToNextStep(const StepDescription& step, const GridProperties& gridProperties,const MLClassIds& mlClassIds)->NextStep{
        const auto oldXStart = step.oldBlock.xHeadPos;
        const auto oldYStart = step.oldBlock.yHeadPos;
        const auto newXStart = step.newXpos.value;
        const auto newYStart = step.newYPos.value;

        auto size = UnblockMe::Utils::Block::getSize(step.oldBlock); 
        auto direction = UnblockMe::Utils::Block::getDirection(step.oldBlock);

        unsigned char oldXEnd = oldXStart + 1;
        unsigned char oldYEnd = oldYStart + 1;
        unsigned char newXEnd = oldXStart + 1;
        unsigned char newYEnd = oldYStart + 1;


        if (direction == UnblockMe::Utils::Block::Direction::HORIZONTAL){
            oldXEnd = oldXStart + size; 
            newXEnd = newXStart + size;
        } 
        else if (direction == UnblockMe::Utils::Block::Direction::VERTICAL){
            oldYEnd = oldYStart + size;
            newYEnd = newYStart + size;
        } 
        // Cmake debug variable
        else {
           // throw error
           // no fixed Box should be find
        }


        auto message = std::string("");
        message.append("move block positioned at");
        message.append(" ");
        message.append("(" + std::to_string((int)oldXStart) + "," + std::to_string((int)oldYStart) + ")");
        message.append(" ");
        message.append("to ");
        message.append("(" + std::to_string((int)newXStart) + "," + std::to_string((int)newYStart) + ").");
        auto oldTopLeft = convertToImageCoordinate(oldXStart,oldYStart,gridProperties);
        auto oldBottomRight = convertToImageCoordinate(oldXEnd,oldYEnd,gridProperties);


        auto newTopLeft = convertToImageCoordinate(newXStart,newYStart,gridProperties);
        auto newBottomRight = convertToImageCoordinate(newXEnd,newYEnd,gridProperties);
        auto class_id = BlockTypeToMLlClassId(step.oldBlock,mlClassIds);

        const auto oldBoundingBox = BoundingBox{
           Left {oldTopLeft.first},
           Top {oldTopLeft.second},
           Right {oldBottomRight.first},
           Bottom {oldBottomRight.second},
           Class_{class_id}
        };

        const auto newBoundingBox = BoundingBox{
           Left {newTopLeft.first},
           Top {newTopLeft.second},
           Right {newBottomRight.first},
           Bottom {newBottomRight.second},
           Class_{class_id}
        };

        const auto nextStep =  NextStep{
            oldBoundingBox,
            newBoundingBox,
            message
        };

        return nextStep;
    }

    auto SimpleGuider::setGridProperties(const BoundingBox& grid)->void{

                float left = grid.left;
                float right =  grid.right;
                float top = grid.top; 
                float bottom = grid.bottom;

                float stepSizeX = (right - left) / GRID_SIZE;
                float stepSizeY = (bottom - top) / GRID_SIZE;
                gridProperties= GridProperties{
                    Top{ top},
                    Left{ left},
                    StepSizeX{ stepSizeX},
                    StepSizeY{ stepSizeY}
                };
            }

    auto SimpleGuider::setBlockImageProperties(std::vector<BoundingBox> blockBoundingBoxes, MLClassIds mlClassIds_)->void{

                BlockImageProperies properties{};
                for(auto& box: blockBoundingBoxes){
                    BlockType type = mlClassIdToBlockType(box,mlClassIds_);
                    properties.insert({  type, { box.width(),box.height()}});
                }
                blockImageProperties = properties;
            }

    auto SimpleGuider::setUpGobals(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox)->void{
            setGridProperties(gridBoudingBox);
            setBlockImageProperties(boundingBoxes,mlClassIds.value());
        }
    
    auto SimpleGuider::setMLClassIds(MLClassIds& ids)->void{
            mlClassIds= ids;
    }

    std::vector<NextStep> SimpleGuider::inferAllSteps(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox)   {
        using UnblockMe::Utils::Graph::findShortestPath;
            setUpGobals(boundingBoxes,gridBoudingBox);
            
            auto grid = convertToGrid(boundingBoxes,mlClassIds.value(),gridProperties.value());
            auto path = findShortestPath(grid);
            auto edges = path.first;
            auto nodes = path.second;
            std::vector<NextStep> result{};
            
            for(auto& edge: edges){
                result.push_back( convertToNextStep(edge, gridProperties.value(),mlClassIds.value())); 
            }

            return result;
    }

    NextStep SimpleGuider::inferOneStep(const std::vector<BoundingBox>& boundingBoxes, const BoundingBox& gridBoudingBox) {
        using UnblockMe::Utils::Graph::findShortestPath;
        setUpGobals(boundingBoxes,gridBoudingBox);
        
        auto grid = convertToGrid(boundingBoxes,mlClassIds.value(),gridProperties.value());
        auto path = findShortestPath(grid);
        auto edges = path.first;
        auto nodes = path.second;
        return convertToNextStep(edges.at(0),gridProperties.value(),mlClassIds.value());
    }

}
