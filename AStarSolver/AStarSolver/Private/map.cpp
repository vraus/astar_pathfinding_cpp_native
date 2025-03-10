#include "../Public/map.h"

// std
#include <iostream>
#include <ostream>

map::map()
{
    start_node_ = nullptr;
    end_node_ = nullptr;
    map_size_ = -1;
}

void map::generate_map(const glb::map::map map_size)
{
    map_size_ = map_size;
    for (int i = 0; i < map_size; i++)
    {
        for (int j = 0; j < map_size; j++)
        {
            map_.push_back(new navigation_node(glb::world::vector2d(i, j)));
        }
    }
}

void map::init_target(const glb::world::location start_coord, const glb::world::location end_coord)
{
    std::cout << "---- Init Targets ----\n";
    std::cout << "----\n";
    std::cout << "Map Size: " << map_size_ << ", Total: " << map_size_ * map_size_ <<  "\n";
    std::cout << "Map Data Size: " << map_.size() << "\n";
    init_start(start_coord);
    init_end(end_coord);
    set_targets_values();
    find_neighbors();
}

bool map::find_path()
{
    // Start with the starting point
    open_queue_.push_back(start_node_);

    // Search path as long as there are neighbors
    while (!open_queue_.empty())
    {
        // Start path finding from the lowest cost (greedy algo)
        const auto q_index = find_smallest_fcost();
        auto q = open_queue_[q_index];

        // Remove the current node from the open list
        open_queue_.erase(open_queue_.begin() + q_index);
        closed_queue_.push_back(q);

        // Look at every neighbor from the current node
        for (const auto i : q->neighbors())
        {
            // If we already looked at this neighbor, ignore it
            if (glb::find(closed_queue_, i))
                continue;

            // Hurray, we found the target node
            if (i == end_node_)
            {
                i->set_parent(q);
                reconstruct_path(i);   
                return true;
            }

            // Calculate if the path to get to this node is better than the one previously calculated
            const auto new_gcost = q->gcost() + i->get_distance_to(q);

            // Record better path for this neighbor
            if (new_gcost < i->gcost())
            {
                i->set_parent(q);
                i->set_gcost(new_gcost);
                i->set_hcost(i->get_distance_to(end_node_));

                if (!glb::find(open_queue_, i))
                    open_queue_.push_back(i);
            }
        }
    }
    
    return false;
}

void map::print_map() const
{
    for (int i = 0; i < map_size_; ++i)
    {
        for (int j = 0; j < map_size_; ++j)
        {
            map_[map_size_ * i + j]->print_node();
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void map::print_path() const
{
    std::cout << "======================\n";
    std::cout << "======== PATH ========\n";
    std::cout << "======================\n";
    for (const auto i : path_)
    {
        std::cout << "\t * ";
        i->print_node();
        std::cout << '\n';
    }
    std::cout << "\n======================\n";
}

void map::init_start(const glb::world::location start_coord)
{
    const auto c = start_coord.v.x * map_size_ + start_coord.v.y;
    start_node_ = map_.at(c);
}

void map::init_end(const glb::world::location end_coord)
{
    const long c = end_coord.v.x * map_size_ + end_coord.v.y ;
    end_node_ = map_.at(c);
}

void map::set_targets_values() const
{
    start_node_->set_gcost(0);
    start_node_->set_hcost(start_node_->get_distance_to(end_node_));
    start_node_->set_type(glb::node::start_node);

    end_node_->set_hcost(0);
    end_node_->set_type(glb::node::end_node);
}

void map::find_neighbors() const
{
    for (int i = 0; i < map_size_; i++)
    {
        for (int j = 0; j < map_size_; j++)
        {
            find_adjacents(map_size_ * i + j);
        }
    }
}

void map::find_adjacents(const int map_index) const
{
    int found_neighbors = 0;
    const auto curr = map_[map_index];

    const auto map_i = map_index / map_size_;
    const auto map_j = map_index % map_size_;

    for (int i = std::max(map_i - 1, 0); i < map_size_; ++i)
    {
        for (int j = std::max(map_j - 1, 0); j < map_size_; ++j)
        {
            const auto dist = curr->get_distance_to(map_[map_size_ * i + j]); 
            if (dist > 0 && dist <= 2)
            {
                curr->add_neighbor(map_[map_size_ * i + j]);
                ++found_neighbors;
            }

            if (found_neighbors == 8)
                return;
        }
    }
}

size_t map::find_smallest_fcost() const
{
    size_t smallest_fcost = 0;

    for (size_t i = 0; i < open_queue_.size(); ++i)
    {
        if (open_queue_[i]->fcost() < open_queue_[smallest_fcost]->fcost())
            smallest_fcost = i;
    }
    
    return smallest_fcost;
}

void map::reconstruct_path(navigation_node* from_node)
{
    path_.clear();

    auto current = from_node;
    
    while (current)
    {
        path_.push_back(current);
        current = current->parent();
    }
    
}