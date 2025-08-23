#include "musicbrainz_client.h"

#include <iostream>
#include <string>

void PrintUsage() {
    std::cout << "Usage: explorer [options]\n";
    std::cout << "Options:\n";
    std::cout << "  --test-connection           Test MusicBrainz API connection\n";
    std::cout << "  --help                      Show this help message\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        PrintUsage();
        return 1;
    }

    std::string command = argv[1];
    MusicBrainzClient client;

    if (command == "--test-connection") {
        std::cout << "Testing MusicBrainz API connection...\n";
        if (client.TestConnection()) {
            std::cout << "✓ Connection successful!\n";
            return 0;
        } else {
            std::cout << "✗ Connection failed!\n";
            return 1;
        }
    } else if (command == "--help") {
        PrintUsage();
        return 0;
    } else {
        std::cout << "Invalid command or missing arguments.\n";
        PrintUsage();
        return 1;
    }

    return 0;
}
