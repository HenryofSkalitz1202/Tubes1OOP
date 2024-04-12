#include "Controller.cpp"

int Pemain::defaultBerat;
int Pemain::defaultUang;

int main(){
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

        std::ifstream fileMisc(filePathMisc);
        if (!fileMisc.is_open()) {
            cout << "File config bangunan '" << filePathBangunan;
            throw FilePathBangunanNotFoundException();
        }

        cout << endl;
        Controller::GameConfig(filePathMisc);
        fileMisc.close();

        // Create an Inventory object
        Inventory inventory;

        // Create some assets
        // Define the materials list
        Asset* asset1 = new Bangunan(1, "SMH", "SMALL_HOUSE", 1000, {{"Wood", 10}, {"Brick", 20}});
        Asset* asset2 = new Bangunan(2, "MDH", "MEDIUM_HOUSE", 1000, {{"Wood", 10}, {"Brick", 20}});
        Asset* asset3 = new Bangunan(4, "HTL", "HOTEL", 1000, {{"Wood", 10}, {"Brick", 20}});

        // Add assets to the inventory
        inventory.addItemKey(asset1, "D04");
        inventory.addItem(asset2);
        inventory.addItemKey(asset3, "D04");

        // Print the inventory
        std::cout << "Inventory:" << std::endl;
        inventory.print();

        // Create a Ladang object
        Ladang ladang;

        // Create some Tumbuhan objects
        Tumbuhan* tumbuhan1 = new FruitPlant(1, "APL", "APPLE_TREE", "FRUIT_PLANT", 5, 5, 2);
        Tumbuhan* tumbuhan2 = new MaterialPlant(1, "IRN", "IRONWOOD_TREE", "MATERIAL_PLANT", 8, 8, 2);
        Tumbuhan* tumbuhan3 = new FruitPlant(1, "ORG", "ORANGE_TREE", "FRUIT_PLANT", 3, 7, 2);

        // Add Tumbuhan to the ladang
        ladang.addItem(tumbuhan1);
        ladang.addItemKey(tumbuhan2, "B03");
        ladang.addItemKey(tumbuhan3, "C02");

        // Print the ladang
        std::cout << "\nLadang:" << std::endl;
        ladang.print();

        // Create a Peternakan object
        Peternakan peternakan;

        // Create some Hewan objects
        Hewan* hewan1 = new Herbivore(1, "COW", "COW", "HERBIVORE", 10, 500);
        Hewan* hewan2 = new Omnivore(1, "CHK", "CHICKEN", "OMNIVORE", 10, 500);
        Hewan* hewan3 = new Carnivore(3, "SNK", "SNAKE", "CARNIVORE", 10, 50);

        // Add Hewan to the peternakan
        peternakan.addItem(hewan1);
        peternakan.addItemKey(hewan2, "B04");
        peternakan.addItemKey(hewan3, "E07");

        // Print the peternakan
        std::cout << "\nPeternakan:" << std::endl;
        peternakan.print();
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
