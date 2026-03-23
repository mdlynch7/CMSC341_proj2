// UMBC - CMSC 341 - Spring 2026 - Proj2
#include "streak.h"
#include <vector>
#include <random>
using namespace std;
enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};
class Tester{ // Tester class to implement test functions
    public:
    //// HELPER FUNCTIONS
    bool isBalanced(Tiger* node) {
        if (node == nullptr) return true;
        int leftHeight = (node->m_left != nullptr) ? node->m_left->m_height : -1;
        int rightHeight = (node->m_right != nullptr) ? node->m_right->m_height : -1;
        if (abs(leftHeight - rightHeight) > 1) return false;
        return isBalanced(node->m_left) && isBalanced(node->m_right);
    }

    bool isBST(Tiger* node, int min, int max) {
        if (node == nullptr) return true;
        if (node->m_id <= min || node->m_id >= max) return false;
        return isBST(node->m_left, min, node->m_id) && isBST(node->m_right, node->m_id, max);
    }

    bool isGridBST(Streak* node, int min, int max) {
        if (node == nullptr) return true;
        if (node->m_gridID <= min || node->m_gridID >= max) return false;
        return isGridBST(node->m_left, min, node->m_gridID) && isGridBST(node->m_right, node->m_gridID, max);
    }

    // testing functions
    // AVL testing functions
    bool testAVLInsertBalance();
    bool testDuplicateID();

    // AVL remove
    bool testAVLRemoveBalance(); // normal multiple removal, ensures balance is good
    bool testAVLRemoveEmpty(); // tests removing from empty tree
    bool testAVLRemoveError(); // tests removing when id DNE


    // searching test functions
    bool testSearchLarge();
    bool testSearchEmpty();
    bool testSearchError();

    // Grid Testing Functions
    bool testGridSplayLarge();
    bool testGridCount(); // tests count function for a specific state
    bool testGridCountAge();
    bool testGridSetState();
};
int main(){
    Tester tester;

    cout << "************* AVL Tree Testing *************" << endl;
    cout << endl << "Testing AVL Insert Balance with 300 tigers" << endl;
    if (tester.testAVLInsertBalance()) cout << "AVL Insert Balance Test Successful!" << endl;
    else cout << "AVL Insert Balance Test failed..." << endl;

    cout << endl << "Testing Inserting Duplicate ID" << endl;
    // successful means it was not inserted, as it should
    if (tester.testDuplicateID()) cout << "Inserting Duplicate ID Test Successful!" << endl;
    else cout << "Inserting Duplicate ID Test failed..." << endl;

    cout << endl << "Testing AVL Remove Balance" << endl;
    if (tester.testAVLRemoveBalance()) cout << "AVL Remove Balance Test Successful!" << endl;
    else cout << "AVL Remove Balance Test failed..." << endl;

    cout << endl << "Testing AVL Remove Empty" << endl;
    if (tester.testAVLRemoveEmpty()) cout << "AVL Remove Empty Test Successful!" << endl;
    else cout << "AVL Remove Empty Test failed..." << endl;

    cout << endl << "Testing AVL Remove Error" << endl;
    if (tester.testAVLRemoveError()) cout << "AVL Remove Error Test Successful!" << endl;
    else cout << "AVL Remove Error Test failed..." << endl;


    cout << endl << "************* Search Functions Tests *************" << endl;
    cout << endl << "Search Normal Test" << endl;
    if (tester.testSearchLarge()) cout << "Normal Search Test Successful!" << endl;
    else cout << "Normal Search Test failed..." << endl;
    
    cout << endl << "Search Empty Test" << endl;
    if (tester.testSearchEmpty()) cout << "Empty Search Test Successful!" << endl;
    else cout << "Empty Search Test failed..." << endl;
    
    cout << endl << "Search Error Test" << endl;
    if (tester.testSearchError()) cout << "Error Search Test Successful!" << endl;
    else cout << "Error Search Test failed..." << endl;


    cout << endl << "************* Splay Tree Testing *************" << endl;
    cout << endl << "Testing Grid Splay" << endl;
    if (tester.testGridSplayLarge()) cout << "Grid Splay Test Successful!" << endl;
    else cout << "Grid Splay Test failed..." << endl;

    cout << endl << "Testing Grid Count" << endl;
    if (tester.testGridCount()) cout << "Grid Count Test Successful!" << endl;
    else cout << "Grid Count Test failed..." << endl;

    cout << endl << "Testing Count for Age" << endl;
    if (tester.testGridCountAge()) cout << "Count for Age Test Successful!" << endl;
    else cout << "Count for Age Test failed..." << endl;

    cout << endl << "Testing Set State" << endl;
    if (tester.testGridSetState()) cout << "Set State Test Successful!" << endl;
    else cout << "Set State Test failed..." << endl;

    return 0;
}

bool Tester::testAVLInsertBalance() {
    // tests that after insertion the AVL tree is still balanced
    Streak streak;
    Random idGen(MINID, MAXID);
    // creates 300 element tiger array and populates it with random ids
    for (int i = 0; i < 300; i++) {
        Tiger tiger(idGen.getRandNum());
        streak.insert(tiger);
    }

    // calls helper function that ensures AVL tree is still balanced
    return isBalanced(streak.m_root) && isBST(streak.m_root, MINID - 1, MAXID + 1);
}

bool Tester::testAVLRemoveBalance() {
    // tests that after removal, AVL tree is still balanced
    Streak streak;
    Random idGen(MINID, MAXID);
    // initializes array with 50 elements 
    int ids[50];
    // creates tigers and populates with random numbers
    for (int i = 0; i < 50; i++) {
        ids[i] = idGen.getRandNum();
        Tiger tiger(ids[i]);
        streak.insert(tiger);
    }

    // removes half of them
    for (int i = 0; i < 25; i++) {
        streak.remove(ids[i]);
    }

    // ensures tree is still balanced and is a BST using helper functions
    return isBalanced(streak.m_root) && isBST(streak.m_root, MINID, MAXID);
}

bool Tester::testDuplicateID() {
    Streak streak;
    // test ID between MIN and MAX
    int testID = 12345;
    Tiger t1(testID);
    Tiger t2(testID);
    // tries to insert tiger with same id
    streak.insert(t1);
    streak.insert(t2);
    // returns true if only one was added and it is still a BST
    return (streak.count(ALIVE) == 1) && isBST(streak.m_root, MINID - 1, MAXID + 1);

}

bool Tester::testAVLRemoveEmpty() {
    Streak streak;
    streak.remove(12345);
    // returns true if m_root is nullptr (program didn't crash and didn't remove anything)
    return (streak.m_root == nullptr);
}

bool Tester::testAVLRemoveError() {
    Streak streak;
    // creates two tiger objects with valid ID
    Tiger t1(12345);
    Tiger t2(23456);
    // inserts two tigers
    streak.insert(t1);
    streak.insert(t2);
    // tries to remove an invalid id (not in AVL tree)
    streak.remove(10001);
    return isBalanced(streak.m_root) && isBST(streak.m_root, MINID - 1, MAXID - 1);

}


bool Tester::testSearchLarge() {
    Streak streak;
    Random idGen(MINID, MAXID);
    vector<int> ids;

    int searches = 50;
    int maxTigers = 500;
    Random findGen(0, 500);

    for (int i = 0; i < maxTigers; i++) {
        int id = idGen.getRandNum();
        Tiger tiger(id);
        streak.insert(tiger);
        ids.push_back(id);
    }

    for (int i = 0; i < searches; i++) {
        int currentID = ids[i];
        if (!streak.findTiger(currentID)) return false;
    }

    return true;
}

bool Tester::testSearchEmpty() {
    Streak streak;
    streak.findTiger(12345);
    return streak.m_root == nullptr;
}

bool Tester::testSearchError() {
    Streak streak;
    Tiger t1(12345);
    Tiger t2(23456);
    streak.insert(t1);
    streak.insert(t2);

    // attempts to find tiger not in AVL tree, returns false if it finds it
    return (streak.findTiger(10001) == false);

}


bool Tester::testGridSplayLarge() {
    // tests splay function of grid works correctly when multi-inserting
    Grid grid;
    Tiger tigers[100];

    Random idGen(MINID, MAXID);
    
    for (int i = 0; i < 500; i++) {
        int currentID = idGen.getRandNum();

        if (grid.insert(currentID, tigers, 10)) {
            if (grid.m_root == nullptr || grid.m_root->m_gridID != currentID) return false;

            if (!isGridBST(grid.m_root, MINID - 1, MAXID + 1)) return false;
        }

    }

    return true;
}

bool Tester::testGridCount() {
    Grid grid;
    Random idGen(MINID, MAXID);

    // creates random grids so one to insert is not the root initially
    Tiger ranTigers[5];
    grid.insert(12345, ranTigers, 0);
    grid.insert(54321, ranTigers, 0);

    // tigers for testing
    int numTigers = 20;
    Tiger tigers[20];

    // testing numbers, 15 wanted ALIVE so 5 DEAD
    int wantedAlive = 15;

    // initializing the tigers and their states
    for (int i = 0; i < numTigers; i++) {
        // if i less than 15 make tiger alive, otherwise dead
        STATE s = (i < wantedAlive) ? ALIVE : DEAD;
        // creates tiger with wanted state
        tigers[i] = Tiger(idGen.getRandNum(), CUB, UNKNOWN, s);
    }
    
    int targetGrid = 23456;

    grid.insert(targetGrid, tigers, numTigers);

    // moves another grid to top (forces splay)
    grid.getGridHeight(12345);

    int result = grid.count(targetGrid, ALIVE);

    if (result != wantedAlive) return false;

    if (grid.m_root == nullptr || grid.m_root->m_gridID != targetGrid) return false;

    return true;
}

bool Tester::testGridCountAge() {
    // tests to see if correct value returned and splay operation performed (AGE)
    Grid grid;
    Random idGen(MINID, MAXID);

    // creates random grids so one to insert is not the root initially
    Tiger ranTigers[10];

    grid.insert(12345, ranTigers, 0);
    grid.insert(54321, ranTigers, 0);

    int targetID = 23456;

    int numTigers = 15;
    Tiger tigers[15];

    // number of expected young tigers
    int wantedYoung = 5;

    // initializes tigers, setting them to desired state
    for (int i = 0; i < numTigers; i++) {
        if (i < 5) {
            tigers[i] = Tiger(idGen.getRandNum(), CUB);
        } else if (i < 10) {
            tigers[i] = Tiger(idGen.getRandNum(), YOUNG);
        } else if (i < 15) {
            tigers[i] = Tiger(idGen.getRandNum(), OLD);
        }

    }

    grid.insert(targetID, tigers, numTigers);

    // moves root to another grid, forces splay
    grid.getGridHeight(12345);

    if (grid.count(targetID, YOUNG) != wantedYoung) return false;

    // makes sure splay happened
    if (grid.m_root == nullptr || grid.m_root->m_gridID != targetID) return false;

    return true;
}

bool Tester::testGridSetState() {
    // tests for correct value returned and splay operation performed (STATE)
    Grid grid;
    Random idGen(MINID, MAXID);

    // creates random grids so one to insert is not the root initially
    Tiger ranTigers[10];

    grid.insert(12345, ranTigers, 0);
    grid.insert(54321, ranTigers, 0);

    // sets default state (ALIVE) for all tigers
    int numTigers = 20;
    Tiger tigers[20];

    int targetID = idGen.getRandNum();
    int targetTigerID = idGen.getRandNum();

    // initializes all tigers
    for (int i = 0; i < numTigers; i++) {
        if (i == 0) {
            tigers[i] = Tiger(targetTigerID);
        } else {
            tigers[i] = Tiger(idGen.getRandNum());
        }
    }

    grid.insert(targetID, tigers, numTigers);

    // calls another grid, forcing splay
    grid.getGridHeight(12345);

    if (!grid.setState(targetID, targetTigerID, DEAD)) return false;

    // ensures splay worked as intended
    if (grid.m_root == nullptr || grid.m_root->m_gridID != targetID) return false;

    return true;
}