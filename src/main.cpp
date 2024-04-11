#include "Controller.cpp"

int Pemain::defaultBerat;
int Pemain::defaultUang;

int main() {
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

        // Create a MaterialPlant object
        int tumbuhanID = 1; // Assign a suitable ID
        string kodeHuruf = "ALT"; // Assign a suitable code
        string namaTumbuhan = "ALOE_TREE"; // Assign a suitable name
        string type = "MATERIAL_PLANT"; // Assign the type (assuming Material)
        size_t durationToHarvest = 5; // Assign the duration to harvest
        int price = 10; // Assign the price
        size_t turnInstantiated = 0; // Assign the turn instantiated (assuming starting from turn 0)

        MaterialPlant materialPlant(tumbuhanID, kodeHuruf, namaTumbuhan, type, durationToHarvest, price, turnInstantiated);

        // Harvest materials
        vector<Produk*> harvestedMaterials = materialPlant.harvest();

        // Display harvested materials
        cout << "Harvested Materials:" << endl;
        for (Produk* material : harvestedMaterials) {
            cout << "Name: " << material->getNamaAsset() << ", Origin: " << material->getOrigin() << endl;
        }

        return 0;

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
