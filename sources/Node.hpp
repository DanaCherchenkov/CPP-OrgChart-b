#include <iostream>
#include <vector>

using namespace std;

namespace ariel{
    class Node{
        public:
            string node_value;
            Node* next_node;
            vector<Node*> leaves;
            bool is_visited;

        Node(string new_node){
            this->node_value = move(new_node);
            this->next_node = nullptr;
            this->leaves = vector<Node*>(); 
            this->is_visited = false;
        }
    };
}