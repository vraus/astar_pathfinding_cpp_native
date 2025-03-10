#pragma once

// std
#include <algorithm>
#include <vector>

#include "navigation_node.h"

class map
{
public:
    map();
    
    ~map() = default;

    // initialisation
    void generate_map(const glb::map::map map_size);
    void init_target(const glb::world::location start_coord, const glb::world::location end_coord);

    //solve
    bool find_path();

    // getters
    std::vector<navigation_node*> get_map() const { return map_; }

    //debug
    void print_map() const;
    void print_path() const;
    
private:
    // initialisation
    void init_start(const glb::world::location start_coord);
    void init_end(const glb::world::location end_coord);
    void set_targets_values() const;

    // neighboring
    void find_neighbors() const;
    void find_adjacents(const int map_index) const;

    // path
    size_t find_smallest_fcost() const;
    void reconstruct_path(navigation_node* from_node);
    std::vector<navigation_node*> path_;
    
    // map
    std::vector<navigation_node*> map_;
    int map_size_;

    // targets
    navigation_node* start_node_;
    navigation_node* end_node_;

    // queues
    std::vector<navigation_node*> open_queue_;
    std::vector<navigation_node*> closed_queue_;
};