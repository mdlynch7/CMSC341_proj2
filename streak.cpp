// UMBC - CMSC 341 - Spring 2026 - Proj2
#include "streak.h"

Streak::Streak(){
    
}
Streak::Streak(int grid, Tiger tigers[], int population){
    
}
Streak::~Streak(){
    
}
void Streak::insert(const Tiger& tiger){
    
}

void Streak::clear(){
    
}

void Streak::remove(int id){
    
}

void Streak::listTigers() const {
    
}

bool Streak::setState(int id, STATE state){
    
}

void Streak::removeDead(){
    
}

bool Streak::findTiger(int id) const {
    
}

int Streak::count(AGE age) const{
    
}

int Streak::count(STATE state) const{
    
}

void Streak::dumpTree() const {dump(m_root);}
void Streak::dump(Tiger* aTiger) const{
    if (aTiger != nullptr){
        cout << "(";
        dump(aTiger->m_left);//first visit the left child
        cout << aTiger->m_id << ":" << aTiger->m_height;//second visit the node itself
        dump(aTiger->m_right);//third visit the right child
        cout << ")";
    }
}

//////////////////////////////////////////////////////////////////////
Grid::Grid(){
    
}

Grid::~Grid(){
    
}

bool Grid::insert(int grid, Tiger tigers[], int population){
    
}

int Grid::count(int grid, STATE state){
    
}
int Grid::count(int grid, AGE age){
    
}
bool Grid::removeTiger(int grid, int tiger, bool all){
    
}
int Grid::getGridHeight(int grid){
    
}
bool Grid::setState(int grid, int tiger, STATE state){
    
}
void Grid::dump(bool verbose) const{
	dumpHelper(m_root, verbose);
    cout << endl;
}

void Grid::dumpHelper(Streak* root, bool verbose) const{
    if (root != nullptr){
        {
            cout << "(";
            dumpHelper( root->m_left, verbose );
            if (verbose)
                cout << root->m_gridID << ":" << root->m_root->m_id;
            else
                cout << root->m_gridID;
            dumpHelper( root->m_right, verbose );
            cout << ")";
        }
    }
}