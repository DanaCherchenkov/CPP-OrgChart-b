#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "Node.hpp"

#pragma once

using namespace std;

namespace ariel{
    class OrgChart{
        private:
            Node* root;
            vector<Node*> all_chart;
            vector<Node*> node_queue_for_preorder;
        public:
            
            //-----------------------------------------------------------------
            // inner class and methods that return instances of it
            //-------------------------------------------------------------------
            class Iterator_chart{
                private:
                    size_t counter = 1;
                    Node* ptr_curr_node;
                    vector<Node*> iter_vec;

                public:
                    Iterator_chart(Node* curr = nullptr): ptr_curr_node(curr) {} //constructor

                    Iterator_chart(std::vector<Node*> vec) : ptr_curr_node(vec.at(0)){
                        iter_vec = vec;
                    }
            
                    string& operator*() const{
                       return this->ptr_curr_node->node_value;
                    }    

                    string* operator->() const{
                       return &(this->ptr_curr_node->node_value);
                    }

                    Node* operator&(){
                        return this->ptr_curr_node;
                    }

                    Iterator_chart& operator++() {
                        if(counter >= iter_vec.size()){
                            ptr_curr_node = nullptr;
                        }else{
                            ptr_curr_node = iter_vec.at(counter);
                            counter++;
                        }   
                        return *this;
                    }

                    bool operator==(const Iterator_chart& chart) const {
                        return this->ptr_curr_node == chart.ptr_curr_node;
                    }

                    bool operator!=(const Iterator_chart& chart) const {
                        return this->ptr_curr_node != chart.ptr_curr_node;
                    }
            };
            //-------------------------------------------------------------------
            // inner class Iterator_chart closed
            //-------------------------------------------------------------------


            OrgChart();
            OrgChart(OrgChart &new_org);
            OrgChart(OrgChart &&new_org) = default;
            OrgChart& operator=(OrgChart&& new_org) = default;
            OrgChart& operator=(const OrgChart &new_org);
            ~OrgChart();

            OrgChart& add_root(string const & root);
            OrgChart& add_sub(string const & parent, string child);
            Node* search_node(Node* node, string const & new_node);

            Iterator_chart end();
            Iterator_chart begin();
            Iterator_chart begin_level_order();
            Iterator_chart end_level_order();
            Iterator_chart begin_reverse_order();
            Iterator_chart reverse_order();
            Iterator_chart begin_preorder();
            Iterator_chart end_preorder();
            friend ostream& operator<<(ostream& out, const OrgChart& chart);

            //Auxiliary functions
            void preorder_func();
            void init_preorder_func(Node* node);
    };
}

