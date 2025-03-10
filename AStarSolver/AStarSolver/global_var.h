// ReSharper disable CppClangTidyReadabilityUseAnyofallof
#pragma once

// std
#include <cstdint>
#include <istream>
#include <vector>

class navigation_node;

namespace glb
{
    namespace map
    {
        enum map : uint16_t
        {
            little_map_size = 5,
            map_size = 10,
            large_map_size = 20,
            mega_map_size = 150,
            huge_map_size = 1500,
            mega_ultra_map_size = 15000,
        };
    };

    namespace node
    {
        enum node_type : char
        {
            undefined = '?',
            start_node = 's',
            end_node = 'e',
            path_node = '.',
            wall_node = 'x',
        };
        
        struct s_navigation_node
        {
            navigation_node* parent;
            int gcost;
            int hcost;
            node_type type;
            
            int fcost() const { return gcost + hcost; }
        };        
    }
    
    namespace world
    {        
        struct vector2d
        {
            vector2d() : x(0), y(0) {}
            vector2d(const int x, const int y) : x(x), y(y) {}

            explicit vector2d(const glb::world::vector2d *v) : x(v->x), y(v->y) {}
            
            int x;
            int y;
        };

        struct location
        {
            location(const int x, const int y) : v(x, y) {}
            explicit location(const glb::world::vector2d *v) : v(v) {}
            
            vector2d v;

            int get_distance_to(const location target) const
            {
                // return (x1-x2)^2 + (y1-y2)^2. No sqrt or pow to avoid (int <-> double) conversions
                return ((target.v.x - v.x) * (target.v.x - v.x)) + ((target.v.y - v.y) * (target.v.y - v.y));
            }

            friend std::ostream& operator<<(std::ostream& os, const location& location)
            {
                os << "(" << location.v.x << " " << location.v.y << ")";
                return os;
            }
        };
    }

    
    /**
     * @brief: Search in a list for the given node.
     * @param list: list of navigation_node to search in.
     * @param node: node to search in the list
     * @return true if the node is found
     * @return false otherwise
     */
    static auto find(const std::vector<navigation_node*>& list, const navigation_node* node) -> bool
    {
        for (const auto i : list)
        {
            if (i == node)
                return true;
        }
        return false;
    }

}