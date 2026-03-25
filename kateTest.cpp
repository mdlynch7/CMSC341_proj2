// UMBC - CMSC 341 - Spring 2026 - Proj2
#include <coroutine>

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
    // STREAK FUNCTIONS
    void results(string s, bool r);
    bool streakDefConst();
    
    bool streakConst();
    bool streakConstEdge();
    bool streakConstError();

    bool streakInsert();
    bool streakInsertEdge();
    bool streakInsertError();
    bool streakInsertMass();

    bool streakRemove();
    bool streakRemoveEdge();
    bool streakRemoveError();
    bool streakRemoveMass();

    bool streakSetState();
    bool streakSetStateError();

    bool streakRemoveDead();
    bool streakRemoveDeadEdge();
    bool streakRemoveDeadError();
    bool streakRemoveDeadMass();

    bool streakFindTigerMass();

    bool streakCountAge();
    bool streakCountAgeEdge();

    bool streakCountState();
    bool streakCountStateEdge();

    bool checkTree(Streak *s);
    bool checkTreeHelper(Tiger *t, int minID, int maxID);

    // GRID FUNCTIONS
    bool gridDefConst();

    bool gridSplay();

    bool gridInsert();
    bool gridInsertError();
    bool gridInsertMass();

    bool gridCountState();
    bool gridCountStateEdge();
    
    bool gridCountAge();
    bool gridCountAgeEdge();

    bool gridRemove();
    bool gridRemoveEdge();
    bool gridRemoveError();
    bool gridRemoveMass();

    bool gridGetHeight();
    bool gridGetHeightError();

    bool gridSetState();
    bool gridSetStateError();
    
    // reusable vars
    const int ID1 = 10001;
    const int ID2 = 10002;
    const int ID3 = 10003;
    const int ID4 = 10004;
    const int ID5 = 10005;
    const int ID6 = 10006;
    const int ID7 = 10007;
    const int ID8 = 10008;
    const int ID9 = 10009;
    const int ID10 = 10010;
    const int TOOLOWID = 100;
    const int TOOHIGHID = 100000;

    bool checkGridBST(Streak *node);
    bool checkGridBSTHelper(Streak *node, int min, int max);
};

int main() {
    Tester t;
    cout << "--- STREAK TESTS ---" << endl;
    cout << "** Streak Default Constructor **" << endl;
    t.results("Streak Default Constructor", t.streakDefConst());

    cout << "\n** Streak Constructors **" << endl;
    t.results("Streak Constructor", t.streakConst());
    t.results("Edge Streak Constructor", t.streakConstEdge());
    t.results("Error Streak Constructor", t.streakConstError());

    cout << "\n** Insert **" << endl;
    t.results("Insert", t.streakInsert());
    t.results("Edge Insert", t.streakInsertEdge());
    t.results("Error Insert", t.streakInsertError());
    t.results("Mass Insert", t.streakInsertMass());

    cout << "\n** Remove **" << endl;
    t.results("Remove", t.streakRemove());
    t.results("Edge Remove", t.streakRemoveEdge());
    t.results("Error Remove", t.streakRemoveError());
    t.results("Mass Remove", t.streakRemoveMass());

    cout << "\n** Set State **" << endl;
    t.results("Set State", t.streakSetState());
    t.results("Error Set State", t.streakSetStateError());

    cout << "\n** RemoveDead **" << endl;
    t.results("Remove Dead", t.streakRemoveDead());
    t.results("Edge Remove Dead", t.streakRemoveDeadEdge());
    t.results("Error Remove Dead", t.streakRemoveDeadError());
    t.results("Mass Remove Dead", t.streakRemoveDeadMass());

    cout << "\n** Find Tiger **" << endl;
    t.results("Find Tiger Mass", t.streakFindTigerMass());

    cout << "\n** Count Age **" << endl;
    t.results("Count Age", t.streakCountAge());
    t.results("Error Count Age", t.streakCountAgeEdge());

    cout << "\n** Count State **" << endl;
    t.results("Count State", t.streakCountState());
    t.results("Error Count State", t.streakCountStateEdge());


    cout << "\n\n--- GRID TESTS ---" << endl;
    cout << "** Default Constructor **" << endl;
    t.results("Default Constructor", t.gridDefConst());

    cout << "\n** Splay ***" << endl;
    t.results("Splay", t.gridSplay());

    cout << "\n** Insert **" << endl;
    t.results("Insert", t.gridInsert());
    t.results("Error Insert", t.gridInsertError());
    t.results("Mass Insert", t.gridInsertMass());
    
    cout << "\n** Count Age **" << endl;
    t.results("Count Age", t.gridCountAge());
    t.results("Count Age Edge", t.gridCountAgeEdge());

    cout << "\n** Count State **" << endl;
    t.results("Count State", t.gridCountState());
    t.results("Count State Edge", t.gridCountStateEdge());

    cout << "\n** Remove **" << endl;
    t.results("Remove", t.gridRemove());
    t.results("Edge Remove", t.gridRemoveEdge());
    t.results("Error Remove", t.gridRemoveError());
    t.results("Mass Remove", t.gridRemoveMass());

    cout << "\n** Get Height **" << endl;
    t.results("Get Height", t.gridGetHeight());
    t.results("Get Height Edge", t.gridGetHeightError());

    cout << "\n** Set State **" << endl;
    t.results("Set State", t.gridSetState());
    t.results("Set State Edge", t.gridSetStateError());
    
    return 0;
}
// printing results of tests
void Tester::results(string s, bool r) {
    if (r) cout << s << " has passed." << endl;
    else cout << s << " has failed." << endl;
}

// STREAK TESTS
bool Tester::streakDefConst() {
    Streak *s = new Streak();
    bool pass = true;
    if (s->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (s->m_gridID != DEFAULT_ID) {cout << "m_gridID is not DEFAULT_ID." << endl; pass = false;}
    if (s->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (s->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}
    delete s;
    return pass;
}

bool Tester::streakConst() {
    Tiger tigers[] = {Tiger(ID1), Tiger(ID2), Tiger(ID3)};
    int pop = 3;
    int grid = 50;
    bool pass = true;
    Streak *s = new Streak(grid, tigers, pop);

    // grid ID
    if (s->m_gridID != grid) {
        cout << "m_grid does not match grid." << endl;
        pass = false;
    }

    // checking tree
    bool result = checkTree(s);
    delete s;
    return result && pass;
}
bool Tester::streakConstEdge() {
    int grid = 50;
    bool pass = true;

    // no tigers in list
    Tiger *tigers1 = nullptr;
    int pop1 = 0;
    Streak *s1 = new Streak(grid, tigers1, pop1);

    if (s1->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (s1->m_gridID != 50) {cout << "m_gridID is not 50." << endl; pass = false;}
    if (s1->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (s1->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}
    delete s1;
    if (!pass) return false;

    // one tiger in list
    Tiger tigers2[] = {Tiger(ID1)};
    int pop2 = 1;
    Streak *s2 = new Streak(grid, tigers2, pop2);

    // grid ID
    if (s2->m_gridID != grid) {
        cout << "m_grid does not match grid." << endl;
        pass = false;
    }

    // checking tree
    bool result = checkTree(s2);
    delete s2;
    return result && pass;
}
bool Tester::streakConstError() {
    int grid = 50;
    bool pass = true;
    
    // invalid IDs
    Tiger tigers1[] = {Tiger(1), Tiger(83757493)};
    int pop1 = 2;
    Streak *s1 = new Streak(grid, tigers1, pop1);
    if (s1->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (s1->m_gridID != grid) {cout << "m_gridID is not correct." << endl; pass = false;}
    if (s1->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (s1->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}
    delete s1;
    if (!pass) return false;

    // repeated IDs
    Tiger tigers2[] = {Tiger(ID1), Tiger(ID2), Tiger(ID3), Tiger(ID4), Tiger(ID5), Tiger(ID3)};
    int pop2 = 6;
    Streak *s2 = new Streak(grid, tigers2, pop2);

    // grid ID
    if (s2->m_gridID != grid) {
        cout << "m_grid does not match grid." << endl;
        pass = false;
    }

    // checking tree
    bool result = checkTree(s2);
    delete s2;
    return result && pass;
}

bool Tester::streakInsert() {
    bool pass = true;
    Streak *s = new Streak();
    s->insert(Tiger(ID1));
    s->insert(Tiger(ID2));
    s->insert(Tiger(ID3));

    // grid ID
    if (s->m_gridID != DEFAULT_ID) {
        cout << "m_grid does not match grid." << endl;
        pass = false;
    }

    // checking tree
    bool result = checkTree(s);
    delete s;
    return result && pass;
}
bool Tester::streakInsertEdge() {
    // one tiger
    bool pass = true;
    Streak *s = new Streak();
    s->insert(Tiger(ID1));

    if (s->m_gridID != DEFAULT_ID) {
        cout << "m_grid does not match grid." << endl;
        pass = false;
    }

    bool result = checkTree(s);
    delete s;
    return result && pass;
}
bool Tester::streakInsertError() {
    // invalid tiger ids
    bool pass = true;
    Streak *s = new Streak();
    s->insert(Tiger(TOOLOWID));
    s->insert(Tiger(TOOLOWID));

    if (s->m_gridID != DEFAULT_ID) {
        cout << "m_grid does not match grid." << endl;
        pass = false;
    }

    bool result = checkTree(s);
    delete s;
    return result && pass;
}
bool Tester::streakInsertMass() {
    bool pass = true;
    Streak *s = new Streak();

    // creating and adding random amount of Tigers with random IDs
    Random numGen(200, 500);
    int numTigers = numGen.getRandNum();
    Random idGen(MINID, MAXID);

    for (int i = 0; i < numTigers; i++) {
        int id = idGen.getRandNum();
        Tiger t(id);
        s->insert(t);
    }

    // grid ID
    if (s->m_gridID != DEFAULT_ID) {
        cout << "m_grid does not match grid." << endl;
        pass = false;
    }

    // checking tree
    bool result = checkTree(s);
    delete s;
    return result && pass;
}

bool Tester::streakRemove() {
    bool pass = true;
    Tiger tigers[] = {Tiger(ID1), Tiger(ID2), Tiger(ID3), Tiger(ID4), Tiger(ID5)};
    Streak *s = new Streak(DEFAULT_ID, tigers, 5);

    for (int i = ID1; i < ID5+1; i++) {
        s->remove(i);
    }

    if (s->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (s->m_gridID != DEFAULT_ID) {cout << "m_gridID is not DEFAULT_ID." << endl; pass = false;}
    if (s->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (s->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}
    delete s;
    return pass;
}
bool Tester::streakRemoveEdge() {
    bool pass = true;
    
    // no children
    Tiger tiger[] = {Tiger(ID1)};
    Streak *s1 = new Streak(DEFAULT_ID, tiger, 1);
    s1->remove(ID1);

    if (s1->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (s1->m_gridID != DEFAULT_ID) {cout << "m_gridID is not DEFAULT_ID." << endl; pass = false;}
    if (s1->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (s1->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}
    delete s1;
    if (!pass) return false;

    // one left child
    Tiger tigerLeft[] = {Tiger(ID2), Tiger(ID1)};
    Streak *s2 = new Streak(DEFAULT_ID, tigerLeft, 2);
    s2->remove(ID2);

    if (s2->m_root == nullptr || s2->m_root->getID() != ID1) {cout << "m_root did not update correctly after removing left child." << endl; pass = false;}
    bool result = checkTree(s2);
    delete s2;
    if (!pass || !result) return false;

    // one right child
    Tiger tigerRight[] = {Tiger(ID3), Tiger(ID4)};
    Streak *s3 = new Streak(DEFAULT_ID, tigerRight, 2);
    s3->remove(ID3);

    if (s3->m_root == nullptr || s3->m_root->getID() != ID4) {cout << "m_root did not update correctly after removing right child." << endl; pass = false;}
    result = checkTree(s3);
    delete s3;
    return pass && result;
}
bool Tester::streakRemoveError() {
    bool pass = true;
    Tiger tigers[] = {Tiger(ID1), Tiger(ID2), Tiger(ID3)};
    Streak *s = new Streak(DEFAULT_ID, tigers, 3);

    // invalid IDs
    s->remove(TOOLOWID);
    s->remove(TOOHIGHID);
    s->remove(ID5);
    if (!checkTree(s)) {cout << "Tree corrupted after attempting to remove invalid IDs." << endl; pass = false;}

    delete s;
    return pass;
}
bool Tester::streakRemoveMass() {
    bool pass = true;
    Streak *s = new Streak();
    vector<int> insertedIDs;

    // creating and adding random amount of Tigers with random IDs
    Random numGen(200, 500);
    int numTigers = numGen.getRandNum();
    Random idGen(MINID, MAXID);

    for (int i = 0; i < numTigers; i++) {
        int id = idGen.getRandNum();
        s->insert(Tiger(id));
        insertedIDs.push_back(id);
    }

    // checking it built correctly
    if (!checkTree(s)) {delete s; return false;}

    // removing all IDs, checking balance as we go
    for (int i = 0; i < insertedIDs.size(); i++) {
        if (pass) {
            s->remove(insertedIDs[i]);
            if (!checkTree(s)) {
                cout << "Error occured after deleting Node " << insertedIDs[i] << endl;
                pass = false;
            }
        }
    }

    // final check
    if (s->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (s->m_gridID != DEFAULT_ID) {cout << "m_gridID is not DEFAULT_ID." << endl; pass = false;}
    if (s->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (s->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}
    delete s;
    return pass;
}

bool Tester::streakSetState() {
    bool pass = true;
    Tiger tigers[] = {Tiger(ID1), Tiger(ID2), Tiger(ID3)};
    Streak *s = new Streak(DEFAULT_ID, tigers, 3);

    if (s->setState(ID1, DEAD) == false) {
        cout << "setState returned false." << endl;
        pass = false;
    }

    if (s->m_root != nullptr && s->m_root->getLeft() != nullptr) {
        if (s->m_root->getLeft()->getState() != DEAD) {
            cout << "Tiger's state did not change." << endl;
            pass = false;
        }
    } else {
        cout << "Tree was corrupted." << endl;
        pass = false;
    }

    delete s;
    return pass;
}
bool Tester::streakSetStateError() {
    bool pass = true;
    Tiger tigers[] = {Tiger(ID1), Tiger(ID2), Tiger(ID3)};
    Streak *s = new Streak(DEFAULT_ID, tigers, 3);

    // invalid ids
    if (s->setState(TOOLOWID, DEAD)) pass = false;
    if (s->setState(TOOHIGHID, DEAD)) pass = false;
    if (s->setState(ID4, DEAD)) pass = false;

    // checking tree stayed the same
    bool sameTree = false;
    if (s->m_root->getID() == ID2) {
        if (s->m_root->getLeft()->getID() == ID1) {
            if (s->m_root->getRight()->getID() == ID3) {
                sameTree = true;
            }
        }
    }

    bool result = checkTree(s);
    delete s;
    return pass && result && sameTree;
}

bool Tester::streakRemoveDead() {
    bool pass = true;
    Tiger tigers[] = {
        Tiger(ID1, CUB, MALE, DEAD),
        Tiger(ID2, YOUNG, FEMALE, ALIVE), // alive
        Tiger(ID3, CUB, MALE, DEAD),
        Tiger(ID4, YOUNG, FEMALE, DEAD),
        Tiger(ID5, CUB, MALE, DEAD),
        Tiger(ID6, YOUNG, FEMALE, ALIVE), // alive
        Tiger(ID7, CUB, MALE, DEAD),
        Tiger(ID8, YOUNG, FEMALE, DEAD),
        Tiger(ID9, CUB, MALE, DEAD),
        Tiger(ID10, YOUNG, FEMALE, DEAD)
    };
    Streak *s = new Streak(DEFAULT_ID, tigers, 10);
    s->removeDead();

    if (s->m_root == nullptr) {cout << "m_root is completely empty." << endl; pass = false;}
    if (s->count(DEAD) != 0) {cout << "Dead Tigers still present in list." << endl; pass = false;}
    if (s->count(ALIVE) != 2) {cout << "Alive Tiger count is inaccurate." << endl; pass = false;}

    delete s;
    return pass;
}
bool Tester::streakRemoveDeadEdge() {
    bool pass = true;
    Streak *s = new Streak();

    // no tigers
    s->removeDead();
    if (s->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (s->m_gridID != DEFAULT_ID) {cout << "m_gridID is not DEFAULT_ID." << endl; pass = false;}
    if (s->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (s->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}

    // one tiger
    s->insert(Tiger(ID1, CUB, MALE, DEAD));
    s->removeDead();

    if (pass && s->m_root != nullptr) {cout << "m_root is not nullptr." << endl; pass = false;}
    if (pass && s->m_gridID != DEFAULT_ID) {cout << "m_gridID is not DEFAULT_ID." << endl; pass = false;}
    if (pass && s->m_left != nullptr) {cout << "m_left is not nullptr." << endl; pass = false;}
    if (pass && s->m_right != nullptr) {cout << "m_right is not nullptr." << endl; pass = false;}
    delete s;
    return pass;
}
bool Tester::streakRemoveDeadError() {
    bool pass = true;
    Tiger tigers[] = {
        Tiger(ID1, CUB, MALE, ALIVE),
        Tiger(ID2, YOUNG, FEMALE, ALIVE),
        Tiger(ID3, CUB, MALE, ALIVE),
    };
    Streak *s = new Streak(DEFAULT_ID, tigers, 3);
    s->removeDead();

    // checking tree stayed the same
    bool sameTree = false;
    if (s->m_root->getID() == ID2) {
        if (s->m_root->getLeft()->getID() == ID1) {
            if (s->m_root->getRight()->getID() == ID3) {
                sameTree = true;
            }
        }
    }

    bool result = checkTree(s);
    delete s;
    return pass && result && sameTree;
}
bool Tester::streakRemoveDeadMass() {
    bool pass = true;
    Streak *s = new Streak();
    vector<int> aliveIDs;
    vector<int> deadIDs;

    Random numGen(200, 500);
    int numTigers = numGen.getRandNum();

    Random idGen(MINID, MAXID);
    Random stateGen(0, 1); // 0 for alive, 1 for dead

    for (int i = 0; i < numTigers; i++) {
        int id = idGen.getRandNum();
        STATE randomState = (stateGen.getRandNum() == 0) ? ALIVE : DEAD;

        if (!s->findTiger(id)) {
            Tiger t(id, CUB, MALE, randomState);
            s->insert(t);

            // keep track of who should live and who should die for our own records
            if (randomState == ALIVE) aliveIDs.push_back(id);
            else deadIDs.push_back(id);
        }
    }

    if (!checkTree(s)) {
        cout << "Tree balance corrupted during mass insertion." << endl;
        delete s;
        return false;
    }

    s->removeDead();

    if (!checkTree(s)) {
        cout << "Tree balance or sorting was corrupted after mass removeDead()." << endl;
        pass = false;
    }

    delete s;
    return pass;
}

bool Tester::streakFindTigerMass() {
    bool pass = true;
    Streak *s = new Streak();
    vector<int> insertedIDs;
    Random idGen(MINID, MAXID);

    // creating 50 tigers
    for (int i = 0; i < 50; i++) {
        int id = idGen.getRandNum();
        if (!s->findTiger(id)) {
            s->insert(Tiger(id));
            insertedIDs.push_back(id);
        }
    }

    // searching for tigers
    for (int i = 0; i < insertedIDs.size(); i++) {
        if (!s->findTiger(insertedIDs[i])) {cout << "findTiger failed to find existing Tiger ID: " << insertedIDs[i] << endl; pass = false;}
    }

    // searching for nonexistent tigers
    if (s->findTiger(TOOHIGHID)) {cout << "findTiger found a nonexistent Tiger." << endl; pass = false;}

    delete s;
    return pass;
}


bool Tester::streakCountAge() {
    bool pass = true;
    int cub = 4;
    int young = 3;
    int old = 3;
    Tiger tigers[] = {
        Tiger(ID1, CUB, MALE, DEAD),
        Tiger(ID2, YOUNG, FEMALE, ALIVE),
        Tiger(ID3, OLD, MALE, DEAD),
        Tiger(ID4, CUB, FEMALE, DEAD),
        Tiger(ID5, YOUNG, MALE, DEAD),
        Tiger(ID6, OLD, FEMALE, ALIVE),
        Tiger(ID7, CUB, MALE, DEAD),
        Tiger(ID8, YOUNG, FEMALE, DEAD),
        Tiger(ID9, OLD, MALE, DEAD),
        Tiger(ID10, CUB, FEMALE, DEAD)
    };
    Streak *s = new Streak(DEFAULT_ID, tigers, 10);

    if (s->count(CUB) != cub) {cout << "count did not count CUB correctly." << endl; pass = false;}
    if (s->count(YOUNG) != young) {cout << "count did not count YOUNG correctly." << endl; pass = false;}
    if (s->count(OLD) != old) {cout << "count did not count OLD correctly." << endl; pass = false;}

    delete s;
    return pass;
}
bool Tester::streakCountAgeEdge() {
    bool pass = true;

    // empty streak
    Streak *s = new Streak();
    if (s->count(CUB) != 0 || s->count(YOUNG) != 0 || s->count(OLD) != 0) {cout << "Count did not return 0 for empty Streak." << endl; pass = false;}

    // one Tiger
    s->insert(Tiger(ID1, CUB, MALE, ALIVE));
    if (s->count(CUB) != 1 || s->count(YOUNG) != 0 || s->count(OLD) != 0) {cout << "Count did not return properly for a single-node Streak." << endl; pass = false;}

    delete s;
    return pass;
}

bool Tester::streakCountState() {
    bool pass = true;
    int dead = 5;
    int alive = 5;
    Tiger tigers[] = {
        Tiger(ID1, CUB, MALE, DEAD),
        Tiger(ID2, YOUNG, FEMALE, ALIVE),
        Tiger(ID3, OLD, MALE, DEAD),
        Tiger(ID4, CUB, FEMALE, ALIVE),
        Tiger(ID5, YOUNG, MALE, DEAD),
        Tiger(ID6, OLD, FEMALE, ALIVE),
        Tiger(ID7, CUB, MALE, DEAD),
        Tiger(ID8, YOUNG, FEMALE, ALIVE),
        Tiger(ID9, OLD, MALE, DEAD),
        Tiger(ID10, CUB, FEMALE, ALIVE)
    };
    Streak *s = new Streak(DEFAULT_ID, tigers, 10);

    if (s->count(ALIVE) != alive) {cout << "count did not count ALIVE correctly." << endl; pass = false;}
    if (s->count(DEAD) != dead) {cout << "count did not count DEAD correctly." << endl; pass = false;}

    delete s;
    return pass;
}
bool Tester::streakCountStateEdge() {
    bool pass = true;

    // empty streak
    Streak *s = new Streak();
    if (s->count(ALIVE) != 0 || s->count(DEAD) != 0) {cout << "Count did not return 0 for empty Streak." << endl; pass = false;}

    // one Tiger
    s->insert(Tiger(ID1, CUB, MALE, ALIVE));
    if (s->count(ALIVE) != 1 || s->count(DEAD) != 0) {cout << "Count did not return properly for a single-node Streak." << endl; pass = false;}

    delete s;
    return pass;
}

// helper function to check if trees are correct for Streak
bool Tester::checkTree(Streak *s) {
    // empty tree
    if (s == nullptr) {
        cout << "m_root is nullptr." << endl;
        return false;
    }

    // calling helper
    return checkTreeHelper(s->m_root, MINID-1, MAXID+1);
}
bool Tester::checkTreeHelper(Tiger *t, int minID, int maxID) {
    // base case - empty
    if (t == nullptr) return true;

    // checking sorting
    if (t->getID() <= minID || t->getID() >= maxID) {
        cout << "Invalid ID found in Node " << t->getID() << endl;
        return false;
    }

    // checking balance
    int leftHeight = (t->getLeft() != nullptr) ? t->getLeft()->m_height : -1;
    int rightHeight = (t->getRight() != nullptr) ? t->getRight()->m_height : -1;
    int balance = leftHeight - rightHeight;

    if (balance < -1 || balance > 1) {
        cout << "Tree in unbalanced in Node " << t->getID() << endl;
        return false;
    }

    // ensuring height is correct
    int expectedHeight = 1 + max(leftHeight, rightHeight);
    if (t->m_height != expectedHeight) {
        cout << "Heigh is incorrect in Node " << t->getID() << endl;
        return false;
    }

    // recursive steps
    bool left = checkTreeHelper(t->m_left, minID, t->getID());
    bool right = checkTreeHelper(t->m_right, t->getID(), maxID);
    return left && right;
}



// GRID TESTS
bool Tester::gridDefConst() {
    bool pass = true;
    Grid *g = new Grid();

    if (g->m_root != nullptr) {cout << "m_root not initialized to nullptr." << endl; pass = false;}

    delete g;
    return pass;
}

bool Tester::gridSplay() {
    Grid g;
    Tiger t[] = {Tiger(ID1)};
    vector<int> gridIDs;

    // inserting grids
    for (int i = 10100; i < 10150; i++) {
        g.insert(i, t, 1);
        gridIDs.push_back(i);
    }


    //triggering various splays
    for (int i = 0; i < 50; i++) {
        g.count(gridIDs[i], ALIVE);
        if (g.m_root->m_gridID != gridIDs[i]) {cout << "m_root does not have the right ID." << endl; return false;}
    }


    // verifying
    return checkGridBST(g.m_root);
}


bool Tester::gridInsert() {
    bool pass = true;
    Grid g;
    Tiger tigers[] = {Tiger(ID1)};

    g.insert(ID1, tigers, 1);
    if (g.m_root == nullptr || g.m_root->m_gridID != ID1) {cout << "Tiger was not inserted or m_root gridID did not match." << endl; pass = false;}

    g.insert(ID2, tigers, 1);
    if (g.m_root == nullptr || g.m_root->m_gridID != ID2) {cout << "Newest insert is not at m_root or m_root is now nullptr." << endl; pass = false;}

    return checkGridBST(g.m_root) && pass;
}
bool Tester::gridInsertError() {
    Grid g;
    Tiger tigers[] = {Tiger(ID1)};

    // invalid id
    g.insert(-100, tigers, 1);
    if (g.m_root != nullptr) {cout << "Insert included Streak with negative ID." << endl; return false;}

    // duplicate
    g.insert(ID1, tigers, 1);
    if (g.insert(ID1, tigers, 1)) {cout << "Insert returned true for duplicate ID." << endl; return false;}

    return true;
}
bool Tester::gridInsertMass() {
    Grid g;
    Random idGen(0, 467351);
    Tiger tigers[] = {Tiger(ID1)};

    for (int i = 0; i < 300; i++) {
        int id = idGen.getRandNum();
        if (g.insert(id, tigers, 1)) {
            if (g.m_root->m_gridID != id) {
                cout << "Newest insert is not at m_root." << endl; return false;
            }
        } else {
            cout << "Insert did not return true." << endl;
            return false;
        }
    }

    return checkGridBST(g.m_root);
}

bool Tester::gridCountAge() {
    Grid g;
    Tiger t1[] = {Tiger(ID1, CUB), Tiger(ID2, CUB)};
    Tiger t2[] = {Tiger(ID3, YOUNG), Tiger(ID4, OLD)};

    g.insert(500, t1, 2);
    g.insert(501, t2, 2);

    int count = g.count(500, CUB);

    if (count != 2) {cout << "Age Count is incorrect." << endl; return false;}
    if (g.m_root == nullptr || g.m_root->m_gridID != 500) {cout << "m_root is nullptr or is not splaying correct node." << endl; return false;}

    return true;
}
bool Tester::gridCountAgeEdge() {
    Grid g;

    // empty grid
    if (g.count(100, CUB) != 0) return false;

    // nonexistant grid
    Tiger t[] = {Tiger(ID1, CUB), Tiger(ID2, CUB)};
    g.insert(100, t, 2);
    if (g.count(200, CUB) != 0) {cout << "Count was not 0 for nonexistent Grid ID." << endl; return false;}

    return true;
}

bool Tester::gridCountState() {
    Grid g;
    Tiger t1[] = {Tiger(ID1, CUB, FEMALE, ALIVE), Tiger(ID2, CUB, FEMALE, DEAD)};
    Tiger t2[] = {Tiger(ID3, YOUNG, MALE, DEAD), Tiger(ID4, OLD, MALE, ALIVE)};

    g.insert(500, t1, 2);
    g.insert(501, t2, 2);

    int count = g.count(500, ALIVE);

    if (count != 1) {cout << "State Count is incorrect." << endl; return false;}
    if (g.m_root == nullptr || g.m_root->m_gridID != 500) {cout << "m_root is nullptr or is not splaying correct node." << endl; return false;}

    return true;
}
bool Tester::gridCountStateEdge() {
    Grid g;

    // empty grid
    if (g.count(100, ALIVE) != 0) return false;

    // nonexistant grid
    Tiger t[] = {Tiger(ID1, CUB, FEMALE, ALIVE), Tiger(ID2, CUB, MALE, ALIVE)};
    g.insert(100, t, 2);
    if (g.count(200, ALIVE) != 0) {cout << "Count was not 0 for nonexistent Grid ID." << endl; return false;}

    return true;
}

bool Tester::gridRemove() {
    Grid g;
    Tiger t[] = {
        Tiger(ID1, CUB, MALE, DEAD),
        Tiger(ID2, YOUNG, FEMALE, ALIVE), // alive
        Tiger(ID3, CUB, MALE, DEAD),
        Tiger(ID4, YOUNG, FEMALE, DEAD),
        Tiger(ID5, CUB, MALE, DEAD),
        Tiger(ID6, YOUNG, FEMALE, ALIVE), // alive
        Tiger(ID7, CUB, MALE, DEAD),
        Tiger(ID8, YOUNG, FEMALE, DEAD),
        Tiger(ID9, CUB, MALE, DEAD),
        Tiger(ID10, YOUNG, FEMALE, DEAD)
    };
    g.insert(501, t, 10);
    g.insert(502, t, 10);
    g.insert(503, t, 10);

    if (!g.removeTiger(501, 0, true)) {cout << "Remove did not return true after removing all dead tigers." << endl; return false;}
    if (g.m_root->m_gridID != 501) {cout << "m_root is not gridID." << endl; return false;}
    if (g.m_root->count(DEAD) != 0) {cout << "All dead tigers were not removed." << endl; return false;}

    if (!g.removeTiger(502, ID2, false)) {cout << "Remove did not return true." << endl; return false;}
    if (g.m_root->m_gridID != 502) {cout << "m_root is not gridID." << endl; return false;}
    if (g.m_root->findTiger(ID2)) {cout << "Tiger was not removed properly." << endl; return false;}

    return true;
}
bool Tester::gridRemoveEdge() {
    Grid g;
    Tiger t[] = {Tiger(ID1, CUB, MALE, ALIVE)};
    g.insert(100, t, 1);

    if (!g.removeTiger(100, ID1, false)) {cout << "Remove did not return true." << endl; return false;}
    if (g.m_root == nullptr || g.m_root->m_gridID != 100) {cout << "m_root is not gridID." << endl; return false;}
    if (g.m_root->count(ALIVE) != 0) {cout << "Tiger was not removed properly." << endl; return false;}

    return true;
}
bool Tester::gridRemoveError() {
    Grid g;
    Tiger t[] = {Tiger(ID1, CUB, MALE, ALIVE)};
    g.insert(500, t, 1);

    if (g.removeTiger(999, ID1, false)) {cout << "Remove returned true for a nonexistent gridID." << endl; return false;}
    if (g.removeTiger(500, ID2, false)) {cout << "Remove returned true for a nonexistent tiger." << endl; return false;}
    if (g.removeTiger(500, ID1, true)) {cout << "Remove returned true when there were no dead tigers." << endl; return false;}

    return true;
}
bool Tester::gridRemoveMass() {
    Grid g;
    Tiger t[] = {Tiger(ID1, CUB, MALE, ALIVE)};
    vector<int> gridIDs;

    for (int i = 0; i < 100; i++) {
        int id = 1000 + i;
        if (g.insert(id, t, 1)) gridIDs.push_back(id);
    }

    for (size_t i = 0; i < gridIDs.size(); i++) {
        if (!g.removeTiger(gridIDs[i], ID1, false)) return false;
        if (!checkGridBST(g.m_root)) return false;
    }

    return true;
}

bool Tester::gridGetHeight() {
    Grid g;
    Tiger t[] = {Tiger(ID1), Tiger(ID2), Tiger(ID3)};
    g.insert(500, t, 3);

    int height = g.getGridHeight(500);

    if (height < 0) {cout << "Height returned error for valid grid." << endl;return false;}
    if (g.m_root->m_gridID != 500) {cout << "Splay did not occur during getHeight." << endl;return false;}

    return true;
}
bool Tester::gridGetHeightError() {
    Grid g;

    // empty grid
    if (g.getGridHeight(100) != -1) {cout << "getGridHeight did not return -1 for empty grid." << endl;return false;}

    // invalid id
    Tiger t[] = {Tiger(ID1)};
    g.insert(500, t, 1);
    if (g.getGridHeight(999) != -1) {cout << "getGridHeight did not return -1 for nonexistent ID." << endl;return false;}

    return true;
}

bool Tester::gridSetState() {
    Grid g;
    Tiger t[] = {Tiger(ID1, CUB, MALE, ALIVE)};
    g.insert(500, t, 1);

    if (!g.setState(500, ID1, DEAD)) {cout << "setState returned false for valid ID." << endl;return false;}
    if (g.m_root->m_gridID != 500) {cout << "setState did not splay correct tree." << endl; return false;}

    if (g.count(500, DEAD) != 1) {cout << "Tiger state was not updated in the AVL tree." << endl;return false;}

    return true;
}
bool Tester::gridSetStateError() {
    Grid g;
    Tiger t[] = {Tiger(ID1, CUB, MALE, ALIVE)};
    g.insert(500, t, 1);

    // nonexistent tiger
    if (g.setState(500, 99999, DEAD)) {cout << "setState returned true for nonexistent Tiger." << endl;return false;}

    // nonexistent grid
    if (g.setState(123, ID1, DEAD)) {cout << "setState returned true for nonexistent Grid." << endl;return false;}

    return true;
}

// grid helpers
bool Tester::checkGridBST(Streak *node) {
    return checkGridBSTHelper(node, -1, 2147483647);
}
bool Tester::checkGridBSTHelper(Streak *node, int min, int max) {
    if (node == nullptr) return true;

    // BST Property Violation
    if (node->m_gridID <= min || node->m_gridID >= max) {
        cout << "Grid BST Violation at ID: " << node->m_gridID << endl;
        return false;
    }

    // Left must be < current, Right must be > current
    return checkGridBSTHelper(node->m_left, min, node->m_gridID) &&
           checkGridBSTHelper(node->m_right, node->m_gridID, max);
}