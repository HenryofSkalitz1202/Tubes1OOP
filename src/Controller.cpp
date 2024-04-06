#include "Controller.hpp"

Controller::Controller()
{
    this->current_player_index = 0;
    this->turn_number = 0;
    this->game_over = false;
}

Controller::~Controller()
{
    for (size_t i = 0; i < this->players.size(); i++)
    {
        delete this->players[i];
    }
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
    sort(players.begin(), players.end(), [](const Pemain* a, const Pemain* b) {
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
            cout << this->players[i]->getUsername() << " wins!" << endl;
            this->game_over = true;
            break;
        }
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
}

void Controller::next()
{
    this->is_won();
    this->current_player_index = (this->current_player_index + 1) % this->players.size();
    this->current_player = this->players[this->current_player_index];
    this->turn_number++;
}