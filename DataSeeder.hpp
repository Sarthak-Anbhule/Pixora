#ifndef PIXORA_DATA_SEEDER_HPP
#define PIXORA_DATA_SEEDER_HPP

#include <vector>
#include "Pin.hpp"
#include "Board.hpp"
#include "Profile.hpp"

namespace Pixora {

class DataSeeder {
public:
    static std::vector<Pin> getInitialPins();
    static std::vector<Board> getInitialBoards();
    static Profile getInitialProfile();
};

} // namespace Pixora

#endif // PIXORA_DATA_SEEDER_HPP
