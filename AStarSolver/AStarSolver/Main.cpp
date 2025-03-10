#include "global_var.h"
#include "Public/map.h"

// std
#include <iostream>

int main()
{
    const auto main_map = new map();

    main_map->generate_map(glb::map::mega_map_size);
    main_map->init_target(glb::world::location(0,0), glb::world::location(99,104));
    
    if (main_map->find_path())
    {
        std::cout << "Path found !\n";
        main_map->print_path();
    }
    else
        std::cout << "No possible path !\n";
    
    return 0;
}