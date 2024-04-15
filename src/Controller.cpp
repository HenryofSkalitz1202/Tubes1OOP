#include "Controller.hpp"
#include "Muat.hpp"
#include "Simpan.hpp"

Controller::Controller()
{
    this->current_player_index = 0;
    this->turn_number = 0;
    this->game_over = true;
}

Controller::~Controller()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        delete this->players[i];
    }
}

vector<string> Controller::stringToArrayEnter(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, '\n')) {
        result.push_back(token);
    }
    return result;
}

vector<string> Controller::stringToArraySpace(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

void Controller::printVector(const vector<string>& vec) {
    std::cout << "<";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ">" << endl;
}

void Controller::populateConfigProduk(string filePathProduk){
    FileReader fileReader(filePathProduk);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, ProductMaterial*> mp_material;
    map<string, ProductFruit*> mp_fruit;
    map<string, ProductHewan*> mp_hewan;
    map<string, int> mp_bahan;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        ProductMaterial* produkMaterialPtr = nullptr;
        ProductFruit* produkFruitPtr = nullptr;
        ProductHewan* produkHewanPtr = nullptr;
        if(str_arr[3] == "PRODUCT_MATERIAL_PLANT"){
            produkMaterialPtr = new ProductMaterial(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_material.insert({str_arr[2], produkMaterialPtr});
        }else if(str_arr[3] == "PRODUCT_FRUIT_PLANT"){
            produkFruitPtr = new ProductFruit(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_fruit.insert({str_arr[1], produkFruitPtr});
        }else if(str_arr[3] == "PRODUCT_ANIMAL"){
            produkHewanPtr = new ProductHewan(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], str_arr[4], std::stoi(str_arr[5]), std::stoi(str_arr[6]));
            mp_hewan.insert({str_arr[1], produkHewanPtr});
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownProductTypeException();
        }
    }

    ProductMaterial::configProdukMaterial.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp_material) {
        ProductMaterial::configProdukMaterial.insert({pair.first, pair.second});
    }

    ProductFruit::configProdukFruit.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp_fruit) {
        ProductFruit::configProdukFruit.insert({pair.first, pair.second});
    }

    ProductHewan::configProdukHewan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp_hewan) {
        ProductHewan::configProdukHewan.insert({pair.first, pair.second});
    }

    std::cout << "Map content Material:" << std::endl;
    for (const auto& pair : ProductMaterial::configProdukMaterial) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Map content Plant:" << std::endl;
    for (const auto& pair : ProductFruit::configProdukFruit) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Map content Hewan:" << std::endl;
    for (const auto& pair : ProductHewan::configProdukHewan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    }
}

void Controller::populateConfigHewan(string filePathHewan){
    FileReader fileReader(filePathHewan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Hewan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        Hewan* hewanPtr = nullptr;
        if(str_arr[3] == "HERBIVORE"){
            hewanPtr = new Herbivore(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]));
        }else if(str_arr[3] == "CARNIVORE"){
            hewanPtr = new Carnivore(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]));
        }else if(str_arr[3] == "OMNIVORE"){
            hewanPtr = new Omnivore(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]));
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownAnimalTypeException();
        }
        mp.insert({str_arr[1], hewanPtr});
    }

    Hewan::configHewan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp) {
        Hewan::configHewan.insert({pair.first, pair.second});
    }

    std::cout << "Map content:" << std::endl;
    for (const auto& pair : Hewan::configHewan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    }
}

void Controller::populateConfigTumbuhan(string filePathTumbuhan){
    FileReader fileReader(filePathTumbuhan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Tumbuhan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        Tumbuhan* tumbuhanPtr = nullptr;
        if(str_arr[3] == "MATERIAL_PLANT"){
            tumbuhanPtr = new MaterialPlant(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]), Tumbuhan::current_turn);
        }else if(str_arr[3] == "FRUIT_PLANT"){
            tumbuhanPtr = new FruitPlant(std::stoi(str_arr[0]), str_arr[1], str_arr[2], str_arr[3], std::stoi(str_arr[4]), std::stoi(str_arr[5]), Tumbuhan::current_turn);
        }else{
            cout << "Type " << str_arr[3];
            throw UnknownPlantTypeException();
        }
        mp.insert({str_arr[1], tumbuhanPtr});
    }

    Tumbuhan::configTumbuhan.clear(); // Clear the existing configProduk map if needed
    for (const auto& pair : mp) {
        Tumbuhan::configTumbuhan.insert({pair.first, pair.second});
    }

    std::cout << "Map content:" << std::endl;
    for (const auto& pair : Tumbuhan::configTumbuhan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    }
}

void Controller::populateConfigBangunan(string filePathBangunan){
    FileReader fileReader(filePathBangunan);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    map<string, Bangunan*> mp;

    for (const auto& str : fileContentarr) {
        vector<string> str_arr = stringToArraySpace(str);
        Bangunan* bangunanPtr = nullptr;
        map<string, int> mp_bahan;

        try{
            for(size_t i = 4; i < str_arr.size(); i+=2){
                auto it = ProductMaterial::configProdukMaterial.find(str_arr[i]);
                if (it == ProductMaterial::configProdukMaterial.end()) {
                    cout << "Material " << str_arr[i];
                    throw MaterialBangunanNotProductMaterialException();
                }

                mp_bahan.insert({str_arr[i], std::stoi(str_arr[i+1])});
            }

            bangunanPtr = new Bangunan(std::stoi(str_arr[0]), str_arr[1], str_arr[2], std::stoi(str_arr[3]), mp_bahan);
            mp.insert({str_arr[1], bangunanPtr});

            std::cout << "ListBahan:" << std::endl;
            for (const auto& pair : mp_bahan) {
                std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
            }
            std::cout << "=====================" << std::endl;
        }catch(MaterialBangunanNotProductMaterialException& e){
            cout << e.what() << endl;
        }catch(exception& e){
            cout << e.what() << endl;
        }
    }

    Bangunan::resepBangunan.clear();
    for (const auto& pair : mp) {
        Bangunan::resepBangunan.insert({pair.first, pair.second});
    }

    std::cout << "Map content:" << std::endl;
    for (const auto& pair : Bangunan::resepBangunan) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second->getNamaAsset() << std::endl;
    }
}

void Controller::GameConfig(string filePathMisc){
    FileReader fileReader(filePathMisc);
    std::string fileContent = fileReader.readText();

    vector<string> fileContentarr = stringToArrayEnter(fileContent);
    //vector<string> str_arr = stringToArraySpace(str);

    Pemain::uangWin = std::stoi(fileContentarr[0]);
    Pemain::beratWin = std::stoi(fileContentarr[1]);

    vector<string> str_arr_inv = stringToArraySpace(fileContentarr[2]);
    Inventory::inventoryRowSize = std::stoi(str_arr_inv[0]);
    Inventory::inventoryColumnSize = std::stoi(str_arr_inv[1]);

    vector<string> str_arr_lhn = stringToArraySpace(fileContentarr[3]);
    Ladang::lahanRowSize = std::stoi(str_arr_lhn[0]);
    Ladang::lahanColumnSize = std::stoi(str_arr_lhn[1]);

    vector<string> str_arr_pet = stringToArraySpace(fileContentarr[4]);
    Peternakan::peternakanRowSize = std::stoi(str_arr_pet[0]);
    Peternakan::peternakanColumnSize = std::stoi(str_arr_pet[1]);
}

void Controller::set_current_player(Pemain* player)
{
    this->current_player = player;
}

Pemain* Controller::get_current_player()
{
    return this->current_player;
}

void Controller::print_current_player()
{
    cout << this->current_player->getUsername() << endl;
}

void Controller::sort_players() {
    sort(players.begin(), players.end(), [](Pemain* a, Pemain* b) {
        return a->getUsername() < b->getUsername();
    });
}

void Controller::add_player(Pemain* player)
{
    this->players.push_back(player);
    this->sort_players();
}

Pemain* Controller::get_first_player()
{
    return this->players[0];
}

void Controller::print_players()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        cout << this->players[i]->getUsername() << endl;
    }
}

bool Controller::is_game_over()
{
    return this->game_over;
}

void Controller::is_won()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->getUang() >= Pemain::uangWin && this->players[i]->getBeratBadan() >= Pemain::beratWin)
        {
            cout << "_________                                     __        .__          __  .__"<< endl <<                      
"\\_   ___ \\  ____   ____    ________________ _/  |_ __ __|  | _____ _/  |_|__| ____   ____   ______" << endl <<
"/    \\  \\/ /  _ \\ /    \\  / ___\\_  __ \\__  \\\\   __\\  |  \\  | \\__  \\\\   __\\  |/  _ \\ /    \\ /  ___/" << endl <<
"\\     \\___(  <_> )   |  \\/ /_/  >  | \\// __ \\|  | |  |  /  |__/ __ \\|  | |  (  <_> )   |  \\___ \\" << endl <<
" \\______  /\\____/|___|  /\\___  /|__|  (____  /__| |____/|____(____  /__| |__|\\____/|___|  /____  >" << endl <<
"        \\/            \\//_____/            \\/                     \\/                    \\/     \\/" << endl;
            cout << this->players[i]->getUsername() << " wins!" << endl << endl << "Thank you for playing!";
            this->game_over = true;
            break;
        }
    }
}

void Controller::start_option()
{
    int option;

    cout << "Choose an option to start the game" << endl;
    cout << "1. Default" << endl;
    cout << "2. Load" << endl;
    
    do {
        cout << "Choose option: ";
        cin >> option;
        cin.ignore();
    } while (option != 1 && option != 2);

    if (option == 1) {
        this->start_default();
    } else if (option == 2) {
        string filePathState;
        cout << "Masukkan path file penyimpanan!" << endl;
        cin >> filePathState;
        this->muat(filePathState);
    }
}

void Controller::start_default()
{
    Petani* p1 = new Petani("Petani1", 50, 40);
    Peternak* p2 = new Peternak("Peternak1", 50, 40);
    Walikota* w1 = new Walikota("Walikota", 50, 40);
    this->add_player(w1);
    this->add_player(p1);
    this->add_player(p2);
    this->set_current_player(this->get_first_player());
    this->game_over = false;
}

bool Controller::is_petani(Pemain* player)
{
    return dynamic_cast<Petani*>(player) != nullptr;
}

bool Controller::is_peternak(Pemain* player)
{
    return dynamic_cast<Peternak*>(player) != nullptr;
}

bool Controller::is_walikota(Pemain* player)
{
    return dynamic_cast<Walikota*>(player) != nullptr;
}

vector<Pemain*> Controller::getPlayers() {
    return this->players;
}

Toko Controller::getToko() {
    return this->toko;
}

int Controller::getTurnNumber() {
    return this->turn_number;
}

void Controller::readCommand() {
    cout << "Apa yang ingin kamu lakukan?" << endl;
    string choice;
    cin >> choice;
    for (auto& x : choice) x = tolower(x); // mengubah string input menjadi lowercase untuk pengecekan
    try {
    if (choice.compare("next") == 0) {
        this->next();
    }
    else if (choice.compare("cetak_penyimpanan") == 0) {
        this->cetak_penyimpanan();
    } 
    else if (choice.compare("pungut_pajak") == 0) {
        this->pungut_pajak();;
    } 
    else if (choice.compare("cetak_ladang") == 0) {
        this->cetak_ladang();
    } 
    else if (choice.compare("cetak_peternakan") == 0) {
        this->cetak_peternakan();
    } 
    else if (choice.compare("tanam") == 0) {
        this->tanam();
    } 
    else if (choice.compare("ternak") == 0) {
        this->ternak();
    } 
    else if (choice.compare("bangun") == 0) {
        this->bangun();
    } 
    else if (choice.compare("makan") == 0) {
        this->makan();
    } 
    else if (choice.compare("kasih_makan") == 0) {
        this->kasih_makan();
    } 
    else if (choice.compare("beli") == 0) {
        this->beli();
    } 
    else if (choice.compare("jual") == 0) {
        this->jual();
    } 
    else if (choice.compare("panen") == 0) {
        this->panen();
    } 
    else if (choice.compare("simpan") == 0) {
        this->simpan();
    } 
    else if (choice.compare("tambah_pemain") == 0) {
        this->tambah_pemain();
    }
    else throw commandNotFoundException();
    }
    catch (exception& e) {
        throw e;
    }
}

void Controller::next()
{
    this->is_won();
    if (!this->is_game_over()) {
        std::cout << current_player->getUsername() << " mengakhiri gilirannya" << endl;
        this->current_player_index = (this->current_player_index + 1) % this->players.size();
        this->current_player = this->players[this->current_player_index];
        this->turn_number++;
        std::cout << "Giliran " << current_player->getUsername() << " untuk bermain" << endl;
    }
}

void Controller::cetak_penyimpanan() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        current_player->printInventory();
    }
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }
}
void Controller::pungut_pajak() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        if (!this->is_walikota(current_player)) {
            throw wrongPlayerTypeException();
        }
        else {
            Walikota temp;
            temp = current_player;
            temp.tagihPajak();
        }
    }
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }
}

void Controller::cetak_ladang() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        if (!this->is_petani(current_player)) {
            throw wrongPlayerTypeException();
        }
        else {
            Petani temp;
            temp = current_player;
            temp.printLadang();
        }
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }
}

void Controller::cetak_peternakan() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        if (!this->is_peternak(current_player)) {
            throw wrongPlayerTypeException();
        }
        else {
            Peternak temp;
            temp = current_player;
            temp.printPeternakan();
        }
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }
}

void Controller::tanam() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        if (!this->is_petani(current_player)) {
            throw wrongPlayerTypeException();
        }
        else {
            Petani temp;
            temp = current_player;
            temp.tanamTanaman();
        }
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }    
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }
}

void Controller::ternak() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }    
        if (!this->is_petani(current_player)) {
            throw wrongPlayerTypeException();
        }
        else {
            Peternak temp;
            temp = current_player;
            temp.taruhHewan();
        }
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }    
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }
}

void Controller::bangun() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        if (!this->is_walikota(current_player)) {
            throw wrongPlayerTypeException();
        }
        else {
            Walikota temp;
            temp = current_player;
            temp.bangunBangunan();
        }
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }  
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }  
}

void Controller::makan() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        current_player->makan();
    }
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }
}

void Controller::kasih_makan() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        if (!this->is_peternak(current_player)) {
            throw wrongPlayerTypeException();
        }
        else {
            Peternak temp;
            temp = current_player;
            temp.beriMakan();
        }
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }   
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    } 
}

void Controller::panen() {
    // TODO
}

void Controller::tambah_pemain() {
    try {
        if (this->is_game_over()) {
            throw gameNotStartedException();
        }
        if (!this->is_walikota(current_player)) {
            throw wrongPlayerTypeException();
        }
        if (current_player->getUang() < 50) {
            throw notEnoughMoneyException();
        }
        string type;
        string usn;
        std::cout << "Masukkan jenis pemain: ";
        std::cin >> type;
        for (auto& x : type) x = tolower(x); // mengubah string input menjadi lowercase untuk pengecekan
        if (type.compare("peternak") && type.compare("petani")) {
            throw pemainFalseTypeException();
        }
        std::cout << "Masukkan nama pemain: ";
        std::cin >> usn;
        for (auto x : players) {
            if (!usn.compare(x->getUsername())) {
                throw usernameNotUniqueException();
            }
        }

        Pemain* newPlayerPoint;
        if (type.compare("peternak")==0) {
            Peternak newPlayer(usn, 50, 0);
            Pemain* newPlayerPoint = &newPlayer;
        }
        else {
            Petani newPlayer(usn, 50, 0);
            Pemain* newPlayerPoint = &newPlayer;
        }
        players.push_back(newPlayerPoint);
        this->sort_players();
        // update current index
        if (current_player->getUsername().compare(usn) > 0) this->current_player_index  = (this->current_player_index + 1) % this->players.size();
        std::cout << "Pemain ditambahkan!" << endl;
        std::cout << "Selamat datang \"" << usn << "\" di kota ini!" << endl;
    }
    catch (wrongPlayerTypeException& e) {
        std::cout << e.what();
    }   
    catch (gameNotStartedException& e) {
        std::cout << e.what();
    }   
    catch (notEnoughMoneyException& e) {
        std::cout << e.what();
    }   
    catch (pemainFalseTypeException& e) {
        std::cout << e.what();
    }   
    catch (usernameNotUniqueException& e) {
        std::cout << e.what();
    }   
}


void Controller::beli() {
    try {
        toko.displayToko();
        int uang = current_player->getUang();
        int available_slot = current_player->getInventory().countAvailableCapacity();
        cout << "Uang Anda: " << uang << endl;
        cout << "Slot penyimpanan tersedia: " << available_slot << endl;

        int pilihan, jumlah;
        cout << "\nNomor barang yang ingin dibeli: ";
        cin >> pilihan;
        cout << "Kuantitas: ";
        cin >> jumlah;

        if (is_walikota(current_player) && pilihan <= toko.getJumlahBangunan()) {
            // throw walikota cant buy
        }

        if (jumlah > current_player->getInventory().countAvailableCapacity()) {
            throw NotEnoughInventoryException();
        }

        Asset* item = toko.beli(pilihan, jumlah, uang);
        current_player->setUang(uang);

        cout << "Selamat Anda berhasil membeli " << jumlah << " " << item->getNamaAsset() << ". Uang Anda tersisa " << uang << " gulden." << endl;
        cout << "Pilih slot untuk menyimpan barang yang Anda beli!" << endl;
        cetak_penyimpanan();
        string str_petak, petak;
        vector<string> v_petak;
        cin >> str_petak;
        stringstream ss(str_petak);
        while(!ss.eof()) {
            getline(ss, petak, ',');
            if (petak[0] == ' ') {
                petak.erase(petak.begin());
            }
            v_petak.push_back(petak);
        }
        if (v_petak.size() != jumlah) {
            // throw invalid input
        }
        for (auto const& p: v_petak) {
            current_player->addToInventory(item, petak);
        }
        cout << item->getNamaAsset() << " berhasil disimpan dalam penyimpanan!" << endl;
    } catch (NotEnoughInventoryException& e) {
        cout << e.what() << endl;
    }
}

void Controller::jual() {
    try {
        string str_petak, petak;
        vector<Asset*> itemJual;
        if (current_player->getInventory().isEmpty()) {
            throw inventoryEmptyException();
        }
        cout << "Berikut merupakan penyimpanan Anda" << endl;
        cetak_penyimpanan();
        cout << "Silahkan pilih petak yang ingin Anda jual!" << endl;
        cout << "Petak: ";
        cin >> str_petak;
        stringstream ss(str_petak);
        while (!ss.eof()) {
            getline(ss, petak, ',');
            if (petak[0] == ' ') {
                petak.erase(petak.begin());
            }
            if (current_player->getFromInventory(petak)->getAssetType() == "BANGUNAN") {
                if (is_petani(current_player) || is_peternak(current_player)) {
                    // throw wrong player
                }
            }
            itemJual.push_back(current_player->getFromInventory(petak));
            //belum remove item
        }
        int hasilJual = toko.jual(itemJual);
        current_player->setUang(current_player->getUang() + hasilJual);
        cout << "Barang Anda berhasil dijual! Uang Anda bertambah " << hasilJual << " gulden!" << endl;
    } catch (inventoryEmptyException& e) {
        cout << e.what() << endl;
    }
}

void Controller::muat(string filePathState)
{
    try {
        ifstream fileState(filePathState);
        if (!fileState) {
            throw FilePathStateNotFoundException();
        }

        Muat Muat(filePathState, *this);
        Muat.read();

    } catch (FilePathStateNotFoundException& e) {
        cout << e.what() << endl;
    }
}

void Controller::simpan() {
    string filepath;
    cout << "Masukkan lokasi berkas state:";
    cin >> filepath;
    try {
        ofstream SaveFile(filepath);
        if (!SaveFile) {
            throw SavePathNotFoundException();
        }
        SaveFile.close();
        Simpan simpan(filepath, *this);
        simpan.write();
        cout << "State berhasil disimpan" << endl;
    } catch (SavePathNotFoundException& e) {
        cout << e.what() << endl;
    }
}