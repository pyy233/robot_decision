#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/xml/pugixml.hpp"
#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/state_machine/StateNode.hpp"
#include "/home/sjtu-rm/new_decision_ws/src/fsm_demo/include/condition/condition_type.h"
#include <iostream>
#include <string>
#include <unordered_map>

void trim(std::string &s)
{
	int index = 0;
	if(!s.empty())
	{
		while( (index = s.find(' ',index)) != std::string::npos)
		{
			s.erase(index,1);
		}
        index=0;
         
        while( (index = s.find('\n',index)) != std::string::npos)
		{
			s.erase(index,1);
		}
	}
}
std::string XmlNodeName(const pugi::xml_node & xml_node){
    std::string res;
    res=xml_node.name();
    trim(res);
    return res;
}
std::string XmlNodeText(const pugi::xml_node & xml_node){
    std::string res;
    res=xml_node.child_value();
    trim(res);
    return res;
}
bool IfDefaultNode(const pugi::xml_node & xml_node){
    std::string if_default=xml_node.attribute("default").as_string();
    if(if_default=="true"){
        std::cout<<"default node detected"<<std::endl;
        return true;
    }
    else{
        return false;
    } 
}
void build_state_machine(const pugi::xml_node & xml_state_node, StateNode * root_state_node){
    std::cout<<"Now build machine : "<<root_state_node->getName()<<std::endl;
    if(XmlNodeText(xml_state_node)!="root_state_node"){
        if(XmlNodeName(xml_state_node.first_child().next_sibling())!="state_machine"){
            StateNode * new_state_node=new StateNode(XmlNodeText(xml_state_node),false);
            std::cout<<"new state_node:"<<new_state_node->getName()<<" created"<<std::endl;
            std::cout<<"add common node "<<XmlNodeText(xml_state_node)<<" to machine "<<root_state_node->getName()<<std::endl;
            root_state_node->addNode(new_state_node);
            if(IfDefaultNode(xml_state_node)){
                root_state_node->setDefaultNode(XmlNodeText(xml_state_node));
            }
            return;
        }
        else{
            StateNode * new_state_node=new StateNode(XmlNodeText(xml_state_node),true);
            std::cout<<"new state_node:"<<new_state_node->getName()<<" created"<<std::endl;
            std::cout<<"add machine node "<<XmlNodeText(xml_state_node)<<" to machine "<<root_state_node->getName()<<std::endl;
            root_state_node->addNode(new_state_node);
            if(IfDefaultNode(xml_state_node)){
                root_state_node->setDefaultNode(XmlNodeText(xml_state_node));
            }
            for(pugi::xml_node point_node = xml_state_node.first_child().next_sibling().first_child().first_child(); point_node != NULL; point_node = point_node.next_sibling()){
                //std::cout<<"build2:"<<XmlNodeText(point_node)<<std::endl;
                build_state_machine(point_node,new_state_node);
            }
            for(pugi::xml_node point_node = xml_state_node.first_child().next_sibling().first_child().next_sibling().first_child(); point_node != NULL; point_node = point_node.next_sibling()){
                StateEdge * new_state_edge=new StateEdge;

                new_state_edge->src_node_name=XmlNodeText(point_node.first_child());
                new_state_edge->dst_node_name=XmlNodeText(point_node.first_child().next_sibling());
                std::string condition=XmlNodeText(point_node.first_child().next_sibling().next_sibling());
                new_state_edge->condition=condition_map.at(condition);
                std::cout<<"Edge Created: src: "<<new_state_edge->src_node_name<<", dst: "<<new_state_edge->dst_node_name<<", condition:"<<new_state_edge->condition<<std::endl;
                new_state_node->addEdge(new_state_edge);
            }
        }
    }
    else{
        for(pugi::xml_node point_node = xml_state_node.first_child().next_sibling().first_child().first_child(); point_node != NULL; point_node = point_node.next_sibling()){
                //std::cout<<"build1:"<<XmlNodeText(point_node)<<std::endl;
                build_state_machine(point_node,root_state_node);
            }
        for(pugi::xml_node point_node = xml_state_node.first_child().next_sibling().first_child().next_sibling().first_child(); point_node != NULL; point_node = point_node.next_sibling()){
            StateEdge * new_state_edge=new StateEdge;
            new_state_edge->src_node_name=XmlNodeText(point_node.first_child());
            new_state_edge->dst_node_name=XmlNodeText(point_node.first_child().next_sibling());
            std::string condition=XmlNodeText(point_node.first_child().next_sibling().next_sibling());
            new_state_edge->condition=condition_map.at(condition);
            std::cout<<"Edge Created: src: "<<new_state_edge->src_node_name<<", dst: "<<new_state_edge->dst_node_name<<", condition:"<<new_state_edge->condition<<std::endl;
            root_state_node->addEdge(new_state_edge);
        }
    }
}


int main(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("/home/sjtu-rm/new_decision_ws/src/fsm_demo/config/fsm.xml");
    if(!result){
        std::cout<<"parse failed";
    }
    pugi::xml_node root_node;
    StateNode all("all",true);
    root_node=doc.first_child();
    build_state_machine(root_node,&all);
    all.get_in_state();
    std::cout<<"GAMESTART!"<<std::endl;
    all.update_machine(ConditionType::game_start);
    std::cout<<"SMALLENERGY!"<<std::endl;
    all.update_machine(ConditionType::in_small_energy);
    std::cout<<"SMALLENERGYCOMPLETE!"<<std::endl;
    all.update_machine(ConditionType::small_energy_complete);
    std::cout<<"WIN!"<<std::endl;
    all.update_machine(ConditionType::game_end);
    //std::cout<<XmlNodeName(root_node);
    //trim(a);
    //if(XmlNodeName(root_node)=="state_node"){
    //    std::cout<<1<<std::endl;
    //}

    
    return 0;
}