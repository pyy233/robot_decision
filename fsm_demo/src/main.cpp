#include <iostream>
#include <string>
#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/state_machine/StateNode.hpp"
#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/condition/condition_type.h"
//#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/state_machine/StateNode.hpp"
int main(){
    StateNode all("all",true);
    StateNode wait_base("wait_base",false);
    StateNode outpost_safe("outpost_safe",true);
    StateNode defence("defense",false);
    StateNode energy("energy",false);
    all.addNode(&wait_base);
    all.addNode(&outpost_safe);
    outpost_safe.addNode(&defence);
    outpost_safe.addNode(&energy);
    all.setDefaultNode("wait_base");
    outpost_safe.setDefaultNode("defense");
    StateEdge edge1;
    StateEdge edge2;
    StateEdge edge3;
    StateEdge edge4;
    edge1.src_node_name="wait_base";
    edge1.dst_node_name="outpost_safe";
    edge1.condition=ConditionType::game_start;
    edge2.src_node_name="outpost_safe";
    edge2.dst_node_name="wait_base";
    edge2.condition=ConditionType::game_end;
    edge3.src_node_name="defense";
    edge3.dst_node_name="energy";
    edge3.condition=ConditionType::in_small_energy;
    edge4.src_node_name="energy";
    edge4.dst_node_name="defense";
    edge4.condition=ConditionType::small_energy_complete;
    all.addEdge(&edge1);
    all.addEdge(&edge2);
    outpost_safe.addEdge(&edge3);
    outpost_safe.addEdge(&edge4);

    all.get_in_state();
    std::cout<<"GAMESTART!"<<std::endl;
    all.update_machine(ConditionType::game_start);
    std::cout<<"SMALLENERGY!"<<std::endl;
    all.update_machine(ConditionType::in_small_energy);
    std::cout<<"SMALLENERGYCOMPLETE!"<<std::endl;
    all.update_machine(ConditionType::small_energy_complete);
    std::cout<<"WIN!"<<std::endl;
    all.update_machine(ConditionType::game_end);
}