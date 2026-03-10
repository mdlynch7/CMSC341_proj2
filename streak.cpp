// UMBC - CMSC 341 - Spring 2026 - Proj2
#include "streak.h"

Streak::Streak(){
    // default constructor, performs required initializations
    m_root = nullptr;
    m_gridID = DEFAULT_ID;
}

Streak::Streak(int grid, Tiger tigers[], int population){
    // constructor performs required initializations, inserts all objects in tigers array
    // population is the size of the array, function assumes the population is of correct size
    m_root = nullptr;
    m_gridID = grid;

    for (int i = 0; i < population; i++) {
        // calls insert to handle new memory and AVL balancing
        insert(tigers[i]);
    }
}

Streak::~Streak(){
    // destructor, performs required clearnup including memory deallocation and re-initializing
    clear();
}
void Streak::insert(const Tiger& tiger){
    // inserts a tiger object into the tree in proper position
    // Tiger::m_id used as the key to traverse Streak tree and abide by BST traversal rules
    // Tiger id is a unique number in range MINID - MAXID. No duplicate ids or objects with invalid ids
    // REMEMBER: after insertion, update height of each node

    // checks for valid m_id (within MINID and MAXID) and checks for existence
    if (tiger.m_id < MINID || tiger.m_id > MAXID) return;
    if (findTiger(tiger.m_id)) return;

    // recursive case, calls helper function to perform everything needed :)
    m_root = insert(m_root, tiger);
}

void Streak::clear(){
    // deallocates all memory in tree and makes it empty tree
    clearHelper(m_root);
    m_root = nullptr;
}

void Streak::remove(int id){
    // traverses tree to find a node with the id and removes it from the tree
    // after removal, update height of each node on the path traversed
    // also, check for an imbalance at each node
    m_root = remove(m_root, id);
}

void Streak::listTigers() const {
    // prints a list of all tigers in tree to the standard output in ascending order of IDs
    // driver.txt has output format
    listTigers(m_root);
}

bool Streak::setState(int id, STATE state){
    // tries to change the state of the tiger, if successful returns true
    Tiger* node = m_root;
    while (node != nullptr) {
        if (id == node->m_id) {
            node->m_state = state;
            return true;
        } else if (id < node->m_id) {
            node = node->m_left;
        } else { // assumes it's not equal to (should already be checked for)
            node = node->m_right;
        }
    }
    return false;
}

void Streak::removeDead(){
    // traverses the tree, finds all tigers with DEAD state and removes them from tree
    // final tree must be a balanced AVL tree
    Tiger* deadTiger = findDead(m_root);
    while (deadTiger != nullptr) {
        remove(deadTiger->m_id);
        deadTiger = findDead(m_root);
    }
}

bool Streak::findTiger(int id) const {
    // returns true if it finds the node with id in tree
    Tiger* tiger = m_root;
    while (tiger != nullptr) {
        if (id == tiger->m_id) {
            return true;
        } else if (id < tiger->m_id) {
            tiger = tiger->m_left;
        } else if (id > tiger->m_id) {
            tiger = tiger->m_right;
        } 
    }
    return false;
}

int Streak::count(AGE age) const{
    // function finds all tigers with specific age and returns total number of them
    return countHelper(m_root, age);
}

int Streak::count(STATE state) const{
    // finds all tigers with specific state and returns total number of them
    return countHelper(m_root, state);
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
/**
 * Each node within grid is a streak object (AVL tree)
 * Every node in AVL tree is a tiger
 */
Grid::Grid(){
    // constructor creates an empty object
}

Grid::~Grid(){
    // destructor, deallocates all dynamically created memory
}

bool Grid::insert(int grid, Tiger tigers[], int population){
    // inserts the tigers into tree
    // Splay tree: required reorganization after insertion
    // duplicate key is not allowed
    // invalid ID returns false
    if (grid < MINID || grid > MAXID) return false;

    // if tree empty, adds new Streak (AVL)
    if (m_root == nullptr) {
        m_root = new Streak(grid, tigers, population);
        return true;
    }

    // splay tree for gridID
    m_root = splay(m_root, grid);

    // check if duplicate
    if (m_root->m_gridID == grid) return false;
}

int Grid::count(int grid, STATE state){
    // finds all tigers with specific state and returns total number of them
}
int Grid::count(int grid, AGE age){
    // finds all tigers with specific age and returns total number of them
}
bool Grid::removeTiger(int grid, int tiger, bool all){
    // removes tiger if all flag is false, if true it removes all dead tigers
}
int Grid::getGridHeight(int grid){
    // returns the height of the tree
    // if error case, returns -1
}
bool Grid::setState(int grid, int tiger, STATE state){
    // tries to change the current state of the tiger
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


//////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////

Tiger* Streak::insert(Tiger* node, const Tiger& tiger) {
    // if the tree is empty, returns a new node
    if (node == nullptr) return new Tiger(tiger.m_id, tiger.m_age, tiger.m_gender, tiger.m_state);

    // otherwise, recurrs down the tree
    if (tiger.m_id < node->m_id) {
        node->m_left = insert(node->m_left, tiger);
    } else if (tiger.m_id > node->m_id){
        node->m_right = insert(node->m_right, tiger);
    } else {
        // if equal, do nothing
        return node;
    }

    // calls helper function to update height
    updateHeight(node);
    // when it gets to here, it goes back through recursive calls
    return rebalance(node);
}

Tiger* Streak::rebalance(Tiger* node) {
    // rebalances AVL tree
    // if left-right or left-left
    int balance = checkBalance(node);
    // if > 1, left heavy
    if (balance > 1) {
        if (checkBalance(node->m_left) < 0) {
            node->m_left = leftRotate(node->m_left);
        }
        return rightRotate(node);
    }

    if (balance < -1) {
        if (checkBalance(node->m_right) > 0) {
            node->m_right = rightRotate(node->m_right);
        }
        return leftRotate(node);
    }
    return node;
}

int Streak::checkBalance(Tiger* node) {
    // if node is nullptr, returns 0. Bottom of the tree
    if (node == nullptr) return 0;

    // left height. returns height if there is one, if not sets to -1
    int leftHeight = (node->m_left) ? node->m_left->m_height : -1;
    // same thing with right height
    int rightHeight = (node->m_right) ? node->m_right->m_height : -1;
    // returns difference between left and right height
    // > 1, means left is heavier than right and needs to be rebalanced
    // < -1, means right is heavier than left and needs to be rebalanced
    return (leftHeight - rightHeight);
}

void Streak::updateHeight(Tiger* node) {
    if (node == nullptr) return;
    int leftHeight = (node->m_left) ? node->m_left->m_height : -1;
    int rightHeight = (node->m_right) ? node->m_right->m_height : -1;
    node->m_height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

Tiger* Streak::rightRotate(Tiger* y) {
    Tiger* x = y->m_left;
    Tiger* T2 = x->m_right;

    // performs rotation
    x->m_right = y;
    y->m_left = T2;

    // updates heights
    updateHeight(y);
    updateHeight(x);

    // returns new root
    return x;
}

Tiger* Streak::leftRotate(Tiger* x) {
    Tiger* y = x->m_right;
    Tiger* T2 = y->m_left;

    // performs rotation
    y->m_left = x;
    x->m_right = T2;

    // updates heights
    updateHeight(x);
    updateHeight(y);

    // returns new root
    return y;
}

bool Streak::search(Tiger* tiger, int id) {

}

void Streak::clearHelper(Tiger* node) {
    // Base case, returns if node is nullptr
    if (node == nullptr) return;
    // recursive case, recursively deletes nodes
    clearHelper(node->m_left);
    clearHelper(node->m_right);
    // deletes the node after both children are gone
    delete node;
}

Tiger* Streak::remove(Tiger* root, int id) {
    if (root == nullptr) return root;
    
    // performs standard BST delete
    if (id < root->m_id) {
        root->m_left = remove(root->m_left, id);
    } else if (id > root->m_id) {
        root->m_right = remove(root->m_right, id);
    } else {
        if ((root->m_left == nullptr) || (root->m_right == nullptr)) {
            Tiger* temp = root->m_left ? root->m_left : root->m_right;

        if (temp == nullptr) {
            delete root;
            return nullptr;
        } else {
            Tiger* old = root;
            root = temp;
            delete old;
        }
    
        } else {
            Tiger* temp = root->m_right;
            while (temp->m_left != nullptr) temp = temp->m_left;

            root->m_id = temp->m_id;
            root->m_age = temp->m_age;
            root->m_gender = temp->m_gender;
            root->m_state = temp->m_state;

            root->m_right = remove(root->m_right, temp->m_id);
        }
    }

    if (root == nullptr) return nullptr;

    updateHeight(root);
    return rebalance(root);
}

Tiger* Streak::findDead(Tiger* toDelete) {
    if (toDelete == nullptr) return nullptr;
    if (toDelete->m_state == DEAD) return toDelete;

    Tiger* leftSib = findDead(toDelete->m_left);
    if (leftSib != nullptr) return leftSib;

    return findDead(toDelete->m_right);
}

void Streak::listTigers(Tiger* node) const {
    if (node == nullptr) return;

    listTigers(node->m_left);

    cout << node->m_id << ":" << node->getAgeStr() << ":" << node->getGenderStr() << ":" << node->getStateStr() << endl;
    listTigers(node->m_right);
}

int Streak::countHelper(Tiger* node, AGE age) const{
    // if the node is null, return 0 (no tigers with wanted age)
    if (node == nullptr) return 0;

    // equals one iff node->m_age is wanted age
    int match = (node->m_age == age) ? 1 : 0;

    // returns the count (ultimately) and calls recursive function
    // checks both of nodes children, if either one is nullptr (no children) doesn't add one
    return match + countHelper(node->m_left, age) + countHelper(node->m_right, age);
}

int Streak::countHelper(Tiger* node, STATE state) const{
    // works much like countHelper for age but with state
    // if current node is null, returns 0 (tiger does not have wanted STATE)
    if (node == nullptr) return 0;

    // equals one iff node->m_state is wanted state
    int match = (node->m_state == state) ? 1 : 0;

    // returns count after recursing through current nodes children (their children, etc.) until nullptr
    return match + countHelper(node->m_left, state) + countHelper(node->m_right, state);
}


/**
 *          GRID HELPER FUNCTIONS (YIPPEEEEEEE)
 */

Streak* Grid::splay(Streak* root, int gridID) {
    // if root is nullptr (traversed through tree) or target found, return root
    if (root == nullptr || root->m_gridID == gridID) return root;

    if (gridID < root->m_gridID) {
        if (root->m_left == nullptr) return root;
    }
}