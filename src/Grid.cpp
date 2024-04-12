#include "Grid.hpp"
#include "Tumbuhan.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <typeinfo>

template <typename T>
Grid<T>::Grid(size_t rows, size_t cols) : rows(rows), cols(cols) {
    T* initial = new T;
    this->data.resize(rows, std::vector<T*>(cols, initial));
}

template <typename T>
Grid<T>::~Grid() {
    // INI MASIH ERROR, segfault. belum ketemu alasannya
    for (int i=0; i < this->rows; i++) {
        for (int j=0; j < this->cols; j++) {
            delete this->data[i][j];
            this->data[i][j] = nullptr;
        }
    }
}

template <typename T>
T*& Grid<T>::get(size_t row, size_t col) {
    //T* value = dynamic_cast<T*>(this->data[row][col])
    return this->data[row][col];
}

template <typename T>
void Grid<T>::set(size_t row, size_t col, T& value) {
    T* temp = new T(value);
    this->data[row][col] = temp;
}

template <typename T>
void Grid<T>::set_first_empty(T& value) {
    bool set = false;
    int i=0;
    int j=0;
    while (i < this->rows && !set) {
        while (j<this->cols && !set) {
            if (this->data[i][j]->getKodeHuruf() == "   ") {
                T* temp = new T(value);
                this->data[i][j] = temp;
                set = true;
            }
            j++;
        }
        i++;
    }
}

template <typename T>
void Grid<T>::unset(size_t row, size_t col) {
    T* a = new T;
    this->data[row][col] = a;
}

template <typename T>
bool Grid<T>::is_empty(size_t row, size_t col) {
    return (this->data[row][col]->getKodeHuruf() == "-");
}
template <typename T>
size_t Grid<T>::numRows() const {
    return this->rows;
}

template <typename T>
size_t Grid<T>::numCols() const {
    return this->cols;
}

template <typename T>
bool Grid<T>::is_full() {
    bool full = true;
    int i = 0;
    int j = 0;
    while (i<this->rows && full) {
        while (j<this->cols && full) {
            if (this->data[i][j].getKodeHuruf != "   ") full = false;
            j++;
        }
        i++;
    }
    return full;
}

template <typename T>
bool Grid<T>::has_type(T& value) {
    bool exists = false;
    int i = 0;
    int j = 0;
    while (i<this->rows && !exists) {
        while (j<this->cols && !exists) {
            if (this->data[i][j]->getType().compare(value.getType()) == 0) exists=true;
            j++;
        }
        i++;
    }
    return exists;
}

void printLexicalOrder(ostream& st, int n) {
    char current = 'A'; // Start from 'A' (uppercase)
    int count = 0;

    while (count < n) {
        for(int i = 0; i < 5; i++){
            st << " ";
        }
        
        st << current;
        count++;
        current++;

        // If current character reaches 'Z', reset it to 'A'
        if (current > 'Z') {
            current = 'A';
        }
    }
    st << std::endl;
}

void printBorder(ostream& st, int n) {
    st << "   ";
    for(int i = 0; i < n; i++) {
        st << "+-----";
    }
    st << "+" << std::endl;
}

template <typename T>
ostream& operator<<(ostream& st, Grid<T> &grid) {
    st << " ";
    printLexicalOrder(st, grid.numCols());
    for (int i = 0; i < grid.numRows(); ++i){
        printBorder(st, grid.numCols());
        st << std::setw(2) << std::setfill('0') << i+1;

        st << " | " ;
        for (int j = 0; j < grid.numCols(); ++j) {
            if (grid.is_empty(i,j)) st << "   " << " | ";
            else st << std::setw(3) << std::setfill(' ') << grid.get(i,j)->getKodeHuruf() << " | ";
        }
        st << "  " << endl;
    }
    printBorder(st, grid.numCols());
    return st;
}

int main() {
    // Create a 3x3 grid of integers
    Grid<Tumbuhan> grid(6, 6);

    cout << grid;
    // Set values in the grid
    FruitPlant a(1, "AAA", "jambu", "froot", 3, 3, 0);
    FruitPlant b(2, "AAC", "apel", "froot", 3, 3, 0);
    MaterialPlant c(3, "BBB", "JATI", "mat", 3, 3, 0);
    grid.set(2,2,a);
    grid.set(0,0,b);
    grid.set_first_empty(c);

    // Print the grid
    cout << grid;

    // Test the get method
    cout << "Value at position (1, 1): " << grid.get(0, 0)->getNamaTumbuhan() << endl;

    //FruitPlant d(grid.get(2,2));
    FruitPlant d;
    //grid.get2(2,2,&d);
    d = grid.get(2,2);
    cout << d.getNamaTumbuhan() << endl;
    cout << typeid(d).name() << endl;
    FruitPlant e(a);
    if (grid.has_type(a)) cout<<" has FruitPlant "<<endl;
    if (grid.has_type(c)) cout << "has MaterialPlant" << endl;
    grid.unset(0,1);
    cout << grid << endl;
    if (grid.has_type(c)) cout << "has MaterialPlant" << endl; 
    return 0;
}

