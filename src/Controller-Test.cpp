#include "Controller.hpp"

int main() {
    //Controller test;
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

        Controller::populateConfigProduk(filePathProduk);
        fileProduk.close();

        std::ifstream fileHewan(filePathHewan);
        if (!fileHewan.is_open()) {
            cout << "File config hewan '" << filePathHewan;
            throw FilePathHewanNotFoundException();
        }

        cout << endl;
        Controller::populateConfigHewan(filePathHewan);
        fileHewan.close();

        std::ifstream fileTumbuhan(filePathTumbuhan);
        if (!fileTumbuhan.is_open()) {
            cout << "File config tumbuhan '" << filePathTumbuhan;
            throw FilePathTumbuhanNotFoundException();
        }

        cout << endl;
        Controller::populateConfigTumbuhan(filePathTumbuhan);
        fileTumbuhan.close();

        std::ifstream fileBangunan(filePathBangunan);
        if (!fileBangunan.is_open()) {
            cout << "File config bangunan '" << filePathBangunan;
            throw FilePathBangunanNotFoundException();
        }

        cout << endl;
        Controller::populateConfigBangunan(filePathBangunan);
        fileBangunan.close();

        std::ifstream fileMisc(filePathMisc);
        if (!fileMisc.is_open()) {
            cout << "File config misc '" << filePathMisc;
            throw FilePathBangunanNotFoundException();
        }

        cout << endl;
        Controller::GameConfig(filePathMisc);
        fileMisc.close();

        Controller test;
        test.start_option();
        cout << "Giliran " << test.get_current_player()->getUsername() << " untuk bermain!" << endl;
        while (!test.is_game_over()) {
            test.readCommand();
        }
    }
    catch(const exception& e) {
        cout << e.what() << endl; // Print any error message
        return 1;
    }
    return 0;
}