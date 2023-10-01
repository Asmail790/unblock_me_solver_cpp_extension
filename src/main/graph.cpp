
#include <map>
#include <set>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <string>
#include <iterator>
#include "grid.hpp"
#include <stdexcept>
#include <iostream>
#include <deque>
#include "graph.hpp"
namespace UnblockMe::Utils::Graph  {
    using Node = UnblockMe::Utils::Grid::Grid;

    auto isTerminalNode(const Node& grid)->bool{
        using UnblockMe::Utils::Grid::getOccupiedPositions;
        using UnblockMe::Utils::Grid::getAvailablePositionsForBlock;
        using UnblockMe::Utils::Block::Block;
        using UnblockMe::Utils::Block::Direction;
        using UnblockMe::Utils::Block::BlockType;
        using UnblockMe::Utils::Block::Y;
        using UnblockMe::Utils::Block::X;
        using UnblockMe::Utils::Block::Size;
        return grid.count(Block{Direction::HORIZONTAL,BlockType::MAIN_BLOCK,X{4},Y{2},Size{2}})==1;
    }
        


    Graph::Graph(){
        int reservedSpace = 4000;
        backwards.reserve(reservedSpace);
        backwards.push_back(0); 
        //for(int i =0; i < reservedSpace;i++) {
        //    backwards.push_back(-1);
        //}
    };
    auto Graph::add(const Node& node)->int{
        
        if (nodes.count(node) == 0) {
            
            const auto id = counter;
            nodes.insert(node);
            nodesIds.insert(id);

            mapping.insert({id,node}); 
            reverseMapping.insert({node,id});
            counter++;
        }

        return reverseMapping.at(node);
    }

    
    // TODO fix linter to accept easily swappable parameters for addEdge
    auto Graph::add(const Node& from, const Node& to)->bool{

        const auto fromId = add(from);
        const auto toId = add(to);

        const auto largestId= std::max(fromId,toId);

        if (backwards.size() <= largestId) {
            for( size_t i=backwards.size(); i <= largestId; i++) {
                backwards.push_back(-1);
            }
        }
        
        const auto firstTimeArriving =  backwards.at(toId) == -1;
        if (firstTimeArriving) {
            backwards.at(toId) = fromId; 
            return true;
        } 
        
        return false;

    };

    auto Graph::exist(const Node& node) const ->bool{
        return nodes.find(node) != nodes.end();
    }

    auto Graph::getPath(const Node& node) const -> std::list<Node> {
        const auto destionationId = reverseMapping.at(node);
        std::list<Node> path{};

        for (auto i = destionationId; i!=0; i =  backwards.at(i)) {
            path.push_front(mapping.at(i));
        }

        path.push_front(mapping.at(0));

        return path;
    }


    auto Graph::describePath(const std::list<Node>& path)const->std::vector<StepDescription>{
        std::vector<StepDescription> edges{};
    
        // Todo iterator of path 1
        // Todo fix    describeAction via set ! sen klar !!!!!!!

        if (path.size() < 2) {
            throw std::logic_error("Path is less than 2 nodes.");
        } 

            
        for(auto i = path.cbegin(); i != std::prev(path.cend(), 1); i++) {
            const auto before = *i; 
            const auto after = *std::next(i, 1);
            edges.push_back(describeAction(before,after));
        }

        return edges;
    }

    auto Graph::describeAction(const Node& predecessorOfNode ,const Node& node) const -> StepDescription{
        using UnblockMe::Utils::Block::Block;
        using UnblockMe::Utils::Block::X;
        using UnblockMe::Utils::Block::Y;
        using UnblockMe::Utils::Block::Size;
        using UnblockMe::Utils::Block::Direction;
        using UnblockMe::Utils::Block::BlockType;
        
            std::set<Block> diff{};
           
            std::set_difference(
                predecessorOfNode.begin(), predecessorOfNode.end(),
                node.begin(), node.end(),
                std::inserter(diff, diff.begin())
            );

            //cmake debug variable
            if (diff.size()!=1) {
                throw std::logic_error("predecessorOfNode is not predecessor of node.");
            }

            Block before = std::vector<Block>{ diff.cbegin(),diff.cend()}.at(0);
            diff.clear();

            std::set_difference(
                node.begin(), node.end(),
                predecessorOfNode.begin(), predecessorOfNode.end(),
                std::inserter(diff, diff.begin())
            );

            //cmake debug variable
            if (diff.size()!=1) {
                throw std::logic_error("node1 is not predecessor of node2.");
            }


            Block after = std::vector<Block>{ diff.cbegin(),diff.cend()}.at(0);
            
          
            return StepDescription{
            before,
             X{after.xHeadPos},
             Y{after.yHeadPos}
            };

            



            
    }

    inline auto switchQueues(std::deque<Node>* q1,std::deque<Node>* q2) {
            return std::pair<std::deque<Node>*,std::deque<Node>*>(q2,q1);
    }

    auto findShortestPath(const Node& initalNode)->std::pair<std::vector<StepDescription>,std::list<Node> >{
        using UnblockMe::Utils::Grid::getAdjacentGrids;
                auto layer1 = std::deque<Node>{initalNode};
                auto layer2 = std::deque<Node>{};
                
                auto nodes = std::set<Node>{initalNode};
                auto graph = Graph{}; 
                auto* consumeQueue =&layer1;
                auto* produceQueue =&layer2;
                int switches = 0;

                while (0 < consumeQueue->size() + produceQueue->size()  ) {
                    if (consumeQueue->size() == 0) {
                      const auto pair = switchQueues(consumeQueue,produceQueue);
                      consumeQueue = pair.first;
                      produceQueue = pair.second;
                      switches++;
                    }


                    Node node = consumeQueue->back(); 
                    consumeQueue->pop_back();

                    for (auto& adjacentNode: getAdjacentGrids(node)) {
                        graph.add(node,adjacentNode);

                        if (isTerminalNode(adjacentNode)){
                            const auto p = graph.getPath(adjacentNode);
                            const auto d = graph.describePath(p);
                            return std::pair<std::vector<StepDescription>,std::list<Node>>(d,p); 
                        }

                        if(nodes.count(adjacentNode) == 0){
                            produceQueue->push_front(adjacentNode);
                            nodes.insert(adjacentNode);
                        }
                    }
                }
                

                throw std::logic_error(
                std::string( "FindShortestPath failed") +
                std::string(" at file") +
                std::string(__FILE__) +
                std::string(" line ")+
                std::to_string(__LINE__)
                );
            }

}
