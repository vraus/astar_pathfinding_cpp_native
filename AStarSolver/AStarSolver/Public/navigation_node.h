#pragma once

#include "../global_var.h"

// std
#include <vector>

class navigation_node
{
public:
    navigation_node();
    explicit navigation_node(glb::world::vector2d location);
    
    ~navigation_node();

    // setters
    void set_gcost(const int gcost);
    void set_hcost(const int hcost);
    void set_type(const glb::node::node_type type);
    void set_parent(navigation_node* parent);
    void add_neighbor(navigation_node* const neighbor);

    // getters
    glb::world::location location() const { return location_; }
    int fcost() const { return nav_node_.fcost(); }
    int gcost() const { return nav_node_.gcost; }
    int hcost() const { return nav_node_.hcost; }
    int get_distance_to(const navigation_node* target) const { return location_.get_distance_to(target->location()); }
    std::vector<navigation_node*> neighbors() const { return neighbors_; }
    navigation_node* parent() const { return nav_node_.parent; }
    
    // debug
    void print_node() const;
private:
    // connections
    std::vector<navigation_node*> neighbors_;

    // node struct
    glb::node::s_navigation_node nav_node_;
    glb::world::location location_;
};
