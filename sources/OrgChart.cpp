#include <iostream>
#include "OrgChart.hpp"
#include <queue>
#include <stack>

using namespace std;

namespace ariel{
    OrgChart::OrgChart(){
        this->root = NULL;
        this->node_queue_for_preorder = vector<Node*>();
    }

    OrgChart::~OrgChart() {}

    OrgChart& OrgChart::add_root(string const & new_root){
        if(this->root != nullptr){
            this->root->node_value = new_root;
        }else{
            //there is no root, we create a new node with the root data.
            this->root = new Node(new_root);
            this->all_chart.push_back(root);
        }
        return *this;
    }

    OrgChart& OrgChart::add_sub(string const & parent, string child){
        if(this->all_chart.empty()){
            throw invalid_argument("The chart is empty");
        }
        if(parent.empty()){
            throw invalid_argument("The value of the node cannot be NULL");
        }
        Node* tmp = search_node(this->root, parent);
        if(tmp == nullptr){
            throw invalid_argument("There is no node with this name parent");
        }
        Node* child_node = new Node(move(child));
        tmp->leaves.push_back(child_node);
        return *this;
    }

    Node* OrgChart::search_node(Node* node, string const & new_node){
        if(node->node_value == new_node){
            return node;
        }
        if(this->root == nullptr){
            throw invalid_argument("The root cannot be null");
        }
        for(size_t i = 0; i < node->leaves.size(); i++){
            Node* tmp = this->search_node(node->leaves.at(i), new_node);
            if(tmp != nullptr){
                return tmp;
            }
        }
        return nullptr;
    }
    
    //The node that start with
    OrgChart::Iterator_chart OrgChart::begin(){
        return this->begin_level_order();
    }

    //Allways be null because when we get to a node whose data is equal to NULL we will know that we have gone through the whole chart.
    OrgChart::Iterator_chart OrgChart::end(){
        return this->end_level_order();
    }

    OrgChart::Iterator_chart OrgChart::begin_level_order(){
        if(this->all_chart.empty()){
            throw invalid_argument("The chart is empty");
        }
        for(size_t i = 0; i < this->all_chart.size(); ++i){
            this->all_chart.at(i)->is_visited = false;
        }
        if(this->root == NULL){
            throw invalid_argument("There is no root");
        }
        this->root->is_visited = true; //starting with the root
        vector<Node*> node_queue;
        node_queue.push_back(root);
        for(size_t i = 0; i < node_queue.size(); i++){
            for(size_t j = 0; j < node_queue.at(i)->leaves.size(); j++){
                node_queue.push_back(node_queue.at(i)->leaves.at(j));
                node_queue.at(i)->is_visited = true;
            }
        }
        return Iterator_chart{node_queue};
    }

    OrgChart::Iterator_chart OrgChart::end_level_order(){
        if(this->all_chart.empty()){
            throw invalid_argument("The chart is empty");
        }
        vector<Node*> node_queue;
        node_queue.push_back(nullptr);
        return Iterator_chart{node_queue}; 
        //When the pointer points to null we know that we have gone through the whole chart.
    }

    OrgChart::Iterator_chart OrgChart::begin_reverse_order(){
        if(this->all_chart.empty()){
            throw invalid_argument("The chart is empty");
        }
        if(this->root == NULL){
            throw invalid_argument("The root cannot be null");
        }
        this->root->is_visited = true; //starting with the root
        vector<Node*> iter_ans;
        queue<Node*> node_queue;
        stack<Node*> node_stack;
        node_queue.push(root);
        while(!node_queue.empty()){
            Node* curr = node_queue.front();
            node_queue.pop();
            node_stack.push(curr);
            for(int j = curr->leaves.size(); j > 0; j--){
                node_queue.push(curr->leaves.at((unsigned int)(j-1)));
            }
        }
        while(!node_stack.empty()){
            Node* temp = node_stack.top();
            node_stack.pop();
            iter_ans.push_back(temp);
        }
        return Iterator_chart{iter_ans};
    }

    OrgChart::Iterator_chart OrgChart::reverse_order(){
        if(this->all_chart.empty()){
            throw invalid_argument("The chart is empty");
        }
        vector<Node*> node_queue;
        node_queue.push_back(NULL);
        return Iterator_chart{node_queue}; 
    }

    OrgChart::Iterator_chart OrgChart::begin_preorder(){
        node_queue_for_preorder.clear();
        if(this->all_chart.empty()){
            throw invalid_argument("The chart is empty");
        }
        this->preorder_func();
        size_t last = this->node_queue_for_preorder.size()-1;
        this->node_queue_for_preorder.at(last)->next_node = NULL;

        for(size_t i = 0; i < this->node_queue_for_preorder.size()-1; i++){
            node_queue_for_preorder.at(i)->next_node = this->node_queue_for_preorder.at(i+1);
        }
        return Iterator_chart{node_queue_for_preorder};
    }

    OrgChart::Iterator_chart OrgChart::end_preorder(){
        if(this->all_chart.empty()){
            throw invalid_argument("The chart is empty");
        }
        vector<Node*> node_queue;
        node_queue.push_back(nullptr);
        return Iterator_chart{node_queue}; 
    }

    ostream& operator<<(ostream& out, const OrgChart& chart){return out;}
   

    void OrgChart::preorder_func(){
        for(size_t i = 0; i < this->all_chart.size(); ++i){
            this->all_chart.at(i)->is_visited = false; //Resetting the treatment state of the nodes, no treatment is done at any node
        }
        if(this->root == NULL){
            throw invalid_argument("There is no root");
        }
        init_preorder_func(root);
        
    }

    void OrgChart::init_preorder_func(Node* curr_node){
        this->node_queue_for_preorder.push_back(curr_node);
        for(size_t i = 0; i < curr_node->leaves.size(); i++){
                init_preorder_func(curr_node->leaves.at(i));
        }
    }
}