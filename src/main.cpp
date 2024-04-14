#include "Controller.cpp"

// ANSI color codes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int Pemain::defaultBerat;
int Pemain::defaultUang;

int main(){
    std::cout << ".------..------..------..------..------..------." << endl;
    std::cout << "|W.--. ||H.--. ||O.--. ||O.--. ||P.--. ||S.--. |" << endl;
    std::cout << "| :" << ANSI_COLOR_RED << "/\\" << ANSI_COLOR_RESET <<  ": || :" << ANSI_COLOR_RED << "/\\" << ANSI_COLOR_RESET <<  ": || :" << ANSI_COLOR_RED << "/\\" << ANSI_COLOR_RESET <<  ": || :" << ANSI_COLOR_RED << "/\\" << ANSI_COLOR_RESET <<  ": || :" << ANSI_COLOR_RED << "/\\" << ANSI_COLOR_RESET <<  ": || :" << ANSI_COLOR_RED << "/\\" << ANSI_COLOR_RESET <<  ": |" << endl;
    std::cout << "| :" << ANSI_COLOR_RED << "\\/" << ANSI_COLOR_RESET <<  ": || " << ANSI_COLOR_RED << "(__)" << ANSI_COLOR_RESET << " || :" << ANSI_COLOR_RED << "\\/" << ANSI_COLOR_RESET <<  ": || :" << ANSI_COLOR_RED << "\\/" << ANSI_COLOR_RESET <<  ": || " << ANSI_COLOR_RED << "(__)" << ANSI_COLOR_RESET << " || :" << ANSI_COLOR_RED << "\\/" << ANSI_COLOR_RESET <<  ": |" << endl;
    std::cout << "| '--'W|| '--'H|| '--'O|| '--'O|| '--'P|| '--'S|" << endl;
    std::cout << "`------'`------'`------'`------'`------'`------'" << endl;
    std::cout << "================================================" << endl;
    std::cout << ANSI_COLOR_GREEN << "10023634 Yudi Kurniawan" << ANSI_COLOR_RESET << endl;
    std::cout << ANSI_COLOR_GREEN << "13522010 Maria Flora Renata S" << ANSI_COLOR_RESET << endl;
    std::cout << ANSI_COLOR_GREEN << "13522010 Kayla Namira Mariadi" << ANSI_COLOR_RESET << endl;
    std::cout << ANSI_COLOR_GREEN << "13522062 Salsabiila" << ANSI_COLOR_RESET << endl;
    std::cout << ANSI_COLOR_GREEN << "13522097 Ellijah Darrellshane Suryanegara" << ANSI_COLOR_RESET << endl;
    std::cout << ANSI_COLOR_GREEN << "13522102 Hayya Zuhailii Kinasih" << ANSI_COLOR_RESET << endl;
    std::cout << "================================================" << endl;

    std::cout << " _  _____ _  _  ___ ___   ___  __  __   __  __   _   _  _   _   ___ ___ ___ "<< endl;
    std::cout << "| |/ /_ _| \\| |/ __|   \\ / _ \\|  \\/  | |  \\/  | /_\\ | \\| | /_\\ / __| __| _ \\" << endl;
    std::cout <<"| ' < | || .` | (_ | |) | (_) | |\\/| | | |\\/| |/ _ \\| .` |/ _ \\ (_ | _||   /" << endl;
    std::cout << "|_|\\_\\___|_|\\_|\\___|___/ \\___/|_|  |_| |_|  |_/_/ \\_\\_|\\_/_/ \\_\\___|___|_|_\\" << endl;
    std::cout << "\n" << endl;

    try {
        std::string filePathHewan;
        bool validPathHewan = false;
        while(!validPathHewan){
            filePathHewan = "";

            cout << "Masukkan file path hewan: " << endl;
            cin >> filePathHewan;

            std::ifstream fileHewan(filePathHewan);
            cout << "\nOpening " << filePathHewan << "....." << endl;

            if(Controller::stringToArrayDot(filePathHewan)[1] != "txt"){
                cout << ANSI_COLOR_YELLOW << "File config must be a txt file!\n" << ANSI_COLOR_RESET << endl;
            }else if (!fileHewan.is_open()) {
                cout << ANSI_COLOR_YELLOW << "File config hewan '" << filePathHewan << "' is not found\n" << ANSI_COLOR_RESET << endl;
            }else{
                cout << ANSI_COLOR_GREEN << "Success! File '" << filePathHewan << "' is found" << ANSI_COLOR_RESET << endl;
                std::cin.get();
                std::cout << "Press any key to continue..." << endl;
                std::cin.get();
                validPathHewan = true;
            }
        }
        Controller::populateConfigHewan(filePathHewan);

        std::string filePathTumbuhan;
        bool validPathTumbuhan = false;
        while(!validPathTumbuhan){
            filePathTumbuhan = "";

            cout << "Masukkan file path tumbuhan: " << endl;
            cin >> filePathTumbuhan;

            std::ifstream fileTumbuhan(filePathTumbuhan);
            cout << "\nOpening " << filePathTumbuhan << "....." << endl;

            if(Controller::stringToArrayDot(filePathTumbuhan)[1] != "txt"){
                cout << ANSI_COLOR_YELLOW << "File config must be a txt file!\n" << ANSI_COLOR_RESET << endl;
            }else if (!fileTumbuhan.is_open()) {
                cout << ANSI_COLOR_YELLOW << "File config tumbuhan '" << filePathTumbuhan << "' is not found\n" << ANSI_COLOR_RESET << endl;
            }else{
                cout << ANSI_COLOR_GREEN << "Success! File '" << filePathTumbuhan << "' is found" << ANSI_COLOR_RESET << endl;
                std::cin.get();
                std::cout << "Press any key to continue..." << endl;
                std::cin.get();
                validPathTumbuhan = true;
            }
        }
        Controller::populateConfigTumbuhan(filePathTumbuhan);

        string filePathProduk;
        bool validPathProduk = false;
        while(!validPathProduk){
            filePathProduk = "";

            cout << "Masukkan file path produk: " << endl;
            cin >> filePathProduk;                                                

            std::ifstream fileProduk(filePathProduk);
            cout << "\nOpening " << filePathProduk << "....." << endl;

            if(Controller::stringToArrayDot(filePathProduk)[1] != "txt"){
                cout << ANSI_COLOR_YELLOW << "File config must be a txt file!\n" << ANSI_COLOR_RESET << endl;
            }else if(!fileProduk.is_open()) {
                cout << ANSI_COLOR_YELLOW << "File config produk '" << filePathProduk << "' is not found\n" << ANSI_COLOR_RESET << endl;
            }else{
                cout << ANSI_COLOR_GREEN << "Success! File '" << filePathProduk << "' is found" << ANSI_COLOR_RESET << endl;
                std::cin.get();
                std::cout << "Press any key to continue..." << endl;
                std::cin.get();
                validPathProduk = true;
            }
        }
        Controller::populateConfigProduk(filePathProduk);

        std::string filePathBangunan;
        bool validPathBangunan = false;

        while(!validPathBangunan){
            filePathBangunan = "";

            cout << "Masukkan file path bangunan: " << endl;
            cin >> filePathBangunan;

            std::ifstream fileBangunan(filePathBangunan);
            cout << "\nOpening " << filePathBangunan << "....." << endl;

            if(Controller::stringToArrayDot(filePathBangunan)[1] != "txt"){
                cout << ANSI_COLOR_YELLOW << "File config must be a txt file!\n" << ANSI_COLOR_RESET << endl;
            }else if (!fileBangunan.is_open()) {
                cout << ANSI_COLOR_YELLOW << "File config bangunan '" << filePathBangunan << "' is not found\n" << ANSI_COLOR_RESET << endl;
            }else{
                cout << ANSI_COLOR_GREEN << "Success! File '" << filePathBangunan << "' is found" << ANSI_COLOR_RESET << endl;
                std::cin.get();
                std::cout << "Press any key to continue..." << endl;
                std::cin.get();
                validPathBangunan = true;
            }
        }
        Controller::populateConfigBangunan(filePathBangunan);

        std::string filePathMisc;
        bool validPathMisc = false;
        while(!validPathMisc){
            filePathMisc = "";

            cout << "Masukkan file path misc: " << endl;
            cin >> filePathMisc;

            std::ifstream fileMisc(filePathMisc);
            cout << "\nOpening " << filePathMisc << "....." << endl;

            if(Controller::stringToArrayDot(filePathMisc)[1] != "txt"){
                cout << ANSI_COLOR_YELLOW << "File config must be a txt file!\n" << ANSI_COLOR_RESET << endl;
            }else if (!fileMisc.is_open()) {
                cout << ANSI_COLOR_YELLOW << "File config misc '" << filePathMisc << "' is not found\n" << ANSI_COLOR_RESET << endl;
            }else{
                cout << ANSI_COLOR_GREEN << "Success! File '" << filePathMisc << "' is found" << ANSI_COLOR_RESET << endl;
                std::cin.get();
                std::cout << "Press any key to continue..." << endl;
                std::cin.get();
                validPathMisc = true;
            }
        }
        Controller::GameConfig(filePathMisc);

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
    } catch(invalidKodeHurufException& e){
        cout << e.what() << endl;
    } catch(invalidPriceException& e){
        cout << e.what() << endl;
    } catch(invalidWeightToHarvestException& e){
        cout << e.what() << endl;
    } catch(invalidDurationToHarvestException& e){
        cout << e.what() << endl;
    } catch(invalidMaterialQuantityException& e){
        cout << e.what() << endl;
    } catch(productMaterialNotFromMaterialPlantException& e){
        cout << e.what() << endl;
    } catch(productMaterialFalseAddedWeightException& e){
        cout << e.what() << endl;
    } catch(productFruitNotFromFruitPlantException& e){
        cout << e.what() << endl;
    } catch(productFruitFalseAddedWeightException& e){
        cout << e.what() << endl;
    } catch(productHewanNotFromHewanException& e){
        cout << e.what() << endl;
    } catch(productHewanFalseAddedWeightException& e){
        cout << e.what() << endl;
    } catch(MaterialBangunanNotProductMaterialException& e){
        cout << e.what() << endl;
    } catch(invalidStoiException& e){
        cout << e.what() << endl;
    } catch(duplicateKeyException& e){
        cout << e.what() << endl;
    } catch(const std::exception& e) {
        cerr << e.what() << endl; // Print any error message
        return 1;
    }

    return 0;
}
