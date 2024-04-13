#include <iostream>
#include "Server.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <level file>" << std::endl;
        return 1;
    }

    Server server;
    if (!server.loadLevel(argv[1])) {
        std::cerr << "Failed to load level file." << std::endl;
        return 1;
    }

    server.run();
    return 0;
}
