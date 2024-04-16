#include "Controller.cpp"

// ANSI color codes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int Pemain::defaultBerat = 40;
int Pemain::defaultUang = 50;

int main(){
    //Start Menu
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

        //Set Mode
        cout << ANSI_COLOR_BLUE << "All config has been set successfully" << ANSI_COLOR_RESET << endl;
        cout << "Press any key to continue..." << endl;
        cin.get();

        cout << "==========================" << endl;
        cout << "WELCOME TO KINGDOM MANAGER" << endl;
        cout << "==========================" << endl;
        cout << "1. New Game" << endl;
        cout << "2. Load Game" << endl;

        string gameMode;
        bool validGameMode = false;
        
        while(!validGameMode){
            gameMode = "";
            cout << "Select game mode: ";
            cin >> gameMode;

            if(gameMode != "1" && gameMode != "2"){
                cout << ANSI_COLOR_YELLOW << "Invalid game mode!\n" << ANSI_COLOR_RESET << endl;
            }else{
                validGameMode = true;
            }
        }

        //READ AND EXECUTE COMMAND
        if(gameMode == "1"){
            cout << ANSI_COLOR_BLUE << "\nStarting new game...." << ANSI_COLOR_RESET << endl;
            Controller mainPage;

            while(!mainPage.is_game_over()){
                cout << ANSI_COLOR_CYAN << "\nTurn: " << mainPage.getTurnNumber() << ANSI_COLOR_RESET << endl; 
                cout << ANSI_COLOR_MAGENTA << "Current player: " << mainPage.get_current_player()->getUsername() << ANSI_COLOR_RESET << endl;
                mainPage.readCommand(mainPage.get_current_player());
            }

            cout << GREEN << "Selamat kamu menang!" << NORMAL << endl;
        }else if(gameMode == "2"){
            //COMING SOON
        }
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
