#ifndef UnblockMe_Utils_Graph
#define UnblockMe_Utils_Graph

#include <map>
#include <set>
#include <vector>
#include <tuple>
#include <list>
#include "grid.hpp"
#include <tuple>
namespace UnblockMe::Utils::Graph {
    using Node = UnblockMe::Utils::Grid::Grid;
    using UnblockMe::Utils::Block::Block;
    using UnblockMe::Utils::Block::X;
    using UnblockMe::Utils::Block::Y;

    struct StepDescription {
        const Block oldBlock;
        const X newXpos;
        const Y newYPos;

        bool operator==(const StepDescription& other)const {
            return (
                newXpos.value == other.newXpos.value
                 &&
                 newYPos.value == other.newYPos.value
                 && 
                 oldBlock == other.oldBlock
                 );
        }
    };





    auto isTerminalNode(const Node& grid)->bool; // Todo move to graph and call it isTerminalNode

   
    // TODO  remove private member in Graph.hpp by using pimpl idiom
    // remove also nodeIDComparator,Cost and NodeID of 
    // check link https://www.youtube.com/watch?v=KOMl2p49rvo
    // check item 22 in effective modern c++

    //ReName to path builder
    class Graph{
        using NodetoIsTerminalNode = bool;
    
    private:
        int counter =0;
        std::map<int,Node> mapping{}; // TODO make capacity at least 1000
        std::map<Node,int> reverseMapping{}; // TODO make capacity at least 1000
        std::set<int> nodesIds{};
        std::set<Node> nodes{};
        std::vector<int> backwards{};  // TODO make capacity at least 1000
        
        // represents graph point to inital node
    
    
    public:
        Graph();
            auto add(const Node& node)->int; 
            auto add(const Node& from, const Node& to)->bool; 
            auto exist(const Node& node) const ->bool; 
            auto getPath(const Node& node) const ->  std::list<Node>;
            auto describePath(const std::list<Node>& path) const ->std::vector<StepDescription>;
            auto describeAction(const Node& after,const Node& before) const -> StepDescription; // make static
            


        // add new edge return node ide,node ide
        // node exist
        // add new node returns node ide
        // 

    };  


    auto findShortestPath(const Node& grid)->std::pair<std::vector<StepDescription>,std::list<Node>>;
}

#endif