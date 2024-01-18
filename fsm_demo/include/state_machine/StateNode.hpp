#ifndef STATENODE_HPP
#define STATENODE_HPP
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/condition/condition_type.h"
struct StateEdge{
    std::string src_node_name, dst_node_name;
    ConditionType condition;
};
class StateNode{
    protected:
        //node
        std::string node_name;
        bool is_machine;
        std::vector<StateNode*> nodes;
        std::map<std::string, std::vector<StateEdge*>> state_graph;   //string is the name of srcnode(easier when updating the machine)
        std::map<std::string, StateNode*> map_name2node;
        StateNode *current_node;
        std::string default_node_name;
    public:
        explicit StateNode(const std::string & node_name, bool is_machine) : node_name(node_name), is_machine(is_machine){
            if (node_name.length() == 0) {
                //ROS_ERROR("empty state node name is illegal\n");
                exit(-1);
            }
        }


        std::string getName() const { return this->node_name; }
        bool getIfMachine() const { return this->is_machine; }

        void addNode(StateNode *node) {
            if(is_machine){
                // StateNode *new_node;
                // new_node=node;
                nodes.push_back(node);
                if (map_name2node.find(node->getName()) != map_name2node.end()) {
                    //ROS_ERROR("multiple nodes with the same name: %s in a state graph\n",new_node->getName().c_str());
                    exit(-1);
                }
                map_name2node.insert(std::make_pair(node->getName(), node));
                state_graph.insert(std::make_pair(node->getName(), std::vector<StateEdge*>()));
                std::cout<<this->getName()<<": node "<<node->getName()<<" added"<<std::endl;
            }
            else{
                std::cout<<"it is not a state machine"<<std::endl;
            }
        }
        void setDefaultNode(const std::string &default_name){
            this->default_node_name=default_name;
            std::cout<<"defaultnode:"<<default_name<<std::endl;
        }
        void addEdge(StateEdge *edge) {
            if(is_machine){
                state_graph[edge->src_node_name].push_back(edge);
                std::cout<<"Edge added to "<<this->getName()<<", src: "<<edge->src_node_name<<", dst: "<<edge->dst_node_name<<", condition:"<<edge->condition<<std::endl;
            }
            else{
                std::cout<<"it is not a state machine"<<std::endl;
            }
        }

        void get_in_state(){
            std::cout<<"get in state:"<<this->node_name<<std::endl;
            if(is_machine){
                current_node=map_name2node[default_node_name];
                current_node->get_in_state();
            }
            else{
                //behaviour tree
            }
        }
        void get_out_state(){
            std::cout<<"get out state:"<<node_name<<std::endl;
        };
        void update_machine(const ConditionType condition){
            if(is_machine){
                std::vector<StateEdge*> &edges = state_graph[current_node->getName()];
                for (std::vector<StateEdge*>::iterator it = edges.begin(); it != edges.end();it++){
                    if ((*it)->condition == condition) {
                        current_node->get_out_state();
                        current_node = map_name2node[(*it)->dst_node_name];
                        current_node->get_in_state();
                    }
                }
                current_node->update_machine(condition);
            }
        }
};

#endif //STATENODE