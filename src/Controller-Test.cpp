#include "Controller.hpp"

int main() {
    Controller test;
    std::string filePathProduk = "produk.txt";
    std::string filePathHewan = "animal.txt";
    std::string filePathTumbuhan = "plant.txt";
    std::string filePathBangunan = "recipe.txt";
    std::string filePathMisc = "misc.txt";

    try {
        std::ifstream fileProduk(filePathProduk);
        if (!fileProduk.is_open()) {
            cout << "File config produk '" << filePathProduk;
            throw FilePathProdukNotFoundException();
        }

        test.populateConfigProduk(filePathProduk);
        fileProduk.close();

        std::ifstream fileHewan(filePathHewan);
        if (!fileHewan.is_open()) {
            cout << "File config hewan '" << filePathHewan;
            throw FilePathHewanNotFoundException();
        }

        cout << endl;
        test.populateConfigHewan(filePathHewan);
        fileHewan.close();

        std::ifstream fileTumbuhan(filePathTumbuhan);
        if (!fileTumbuhan.is_open()) {
            cout << "File config tumbuhan '" << filePathTumbuhan;
            throw FilePathTumbuhanNotFoundException();
        }

        cout << endl;
        test.populateConfigTumbuhan(filePathTumbuhan);
        fileTumbuhan.close();

        std::ifstream fileMisc(filePathMisc);
        if (!fileMisc.is_open()) {
            cout << "File config bangunan '" << filePathBangunan;
            throw FilePathBangunanNotFoundException();
        }

        cout << endl;
        test.GameConfig(filePathMisc);
        fileMisc.close();

        test.start_option();
        cout << "Giliran " << test.get_current_player()->getUsername() << " untuk bermain!" << endl;
        while (!test.is_game_over()) {
            test.readCommand();
        }
    }
    catch(const std::exception& e) {
        cerr << e.what() << endl; // Print any error message
        return 1;
    }
    return 0;
}