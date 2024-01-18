#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/xml/pugixml.hpp"
#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/state_machine/StateNode.hpp"
#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/condition/condition_type.h"
#include <iostream>
#include <string>
#include <unordered_map>
int main(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("/home/sjtu-rm/new_decision_ws/src/fsm_demo/config/fsm.xml");
    if(!result){
        std::cout<<"parse failed";
    }
    pugi::xml_node root_node=doc.first_child().first_child().next_sibling().first_child().first_child();
    
    std::string res=root_node.attribute("default").as_string();
    std::cout<<res<<std::endl;
    if(res=="true"){
        std::cout<<"yes"<<std::endl;
    }


}