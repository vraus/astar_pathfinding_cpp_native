#include "../Public/navigation_node.h"

// std
#include <iostream>
#include <cmath>

navigation_node::navigation_node(): location_(glb::world::location(0, 0))
{
    nav_node_.parent = nullptr;
    nav_node_.gcost = _HUGE_ENUF;
    nav_node_.hcost = _HUGE_ENUF;
    nav_node_.type = glb::node::path_node;
}

navigation_node::navigation_node(const glb::world::vector2d location): location_(&location)
{
    nav_node_.parent = nullptr;
    nav_node_.gcost = _HUGE_ENUF;
    nav_node_.hcost = _HUGE_ENUF;
    nav_node_.type = glb::node::path_node;
}

navigation_node::~navigation_node() = default;

void navigation_node::set_gcost(const int gcost)
{
    nav_node_.gcost = gcost;
}

void navigation_node::set_hcost(const int hcost)
{
    nav_node_.hcost = hcost;
}

void navigation_node::set_type(const glb::node::node_type type)
{
    nav_node_.type = type;
}

void navigation_node::set_parent(navigation_node* parent)
{
    nav_node_.parent = parent;
}

void navigation_node::add_neighbor(navigation_node* const neighbor)
{
    neighbors_.push_back(neighbor);
}

void navigation_node::print_node() const
{    
    std::cout << "(" << location_ <<
        ", t:" << nav_node_.type <<
        ", n:" << neighbors_.size() <<
        ", c:" << nav_node_.gcost << ", " << nav_node_.hcost << ", " << nav_node_.fcost() << ")";
}
