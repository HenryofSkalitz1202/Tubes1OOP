#include "Controller.cpp"
#include "Pemain.cpp"
#include "Grid.cpp"

int Pemain::defaultBerat;
int Pemain::defaultUang;

int main() {
    std::string filePathProduk = "produk.txt"; // Replace "input.txt" with your file path
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

    } catch(UnknownProductTypeException& e){
        cout << e.what() << endl;
    } catch(FilePathProdukNotFoundException& e){
        cout << e.what() << endl;
    } catch(FilePathHewanNotFoundException& e){
        cout << e.what() << endl;
    } catch(FilePathBangunanNotFoundException& e){
        cout << e.what() << endl;
    } catch(const std::exception& e) {
        cerr << e.what() << endl; // Print any error message
        return 1;
    }

    return 0;
}
