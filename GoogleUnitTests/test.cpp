#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "C:\Users\chasl\OneDrive\Desktop\OptimalBST\OptimalBST\Rational.h"   // Assuming Rational class is defined elsewhere
#include "C:\Users\chasl\OneDrive\Desktop\OptimalBST\OptimalBST\OptimalBST.cpp" // Assuming OptimalBST class is defined elsewhere
#include <gtest/gtest.h> 

using namespace std;
using namespace std::chrono;

// Function to read input from file and parse into keys and frequencies
void readInput(const string& filename, vector<Rational>& keys, vector<Rational>& freq) {
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Failed to open input file: " << filename << endl;
        return;
    }

    Rational key, frequency;
    while (input >> key >> frequency) {
        keys.push_back(key);
        freq.push_back(frequency);
    }

    input.close();
}

//// Function to print BST level by level
//void printLevelOrder(Node* root) {
//    if (root == nullptr)
//        return;
//
//    queue<Node*> q;
//    q.push(root);
//
//    while (!q.empty()) {
//        int levelSize = q.size();
//        for (int i = 0; i < levelSize; ++i) {
//            Node* node = q.front();
//            q.pop();
//            cout << node->key << " ";
//            if (node->left)
//                q.push(node->left);
//            if (node->right)
//                q.push(node->right);
//        }
//        cout << endl;
//    }
//}

// Unit test for sequential construction of Optimal BST
TEST(OptimalBSTTest, SequentialConstruction) {
    vector<Rational> keys;
    vector<Rational> freq;
    readInput("input.txt", keys, freq);  // Adjust path here
    int n = keys.size();

    // Create OptimalBST instance (using Singleton pattern)
    OptimalBST* obst = OptimalBST::getInstance(keys.data(), freq.data(), n);

    auto start = high_resolution_clock::now();
    obst->constructOptimalBST(1);  // Sequential construction
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Sequential construction time: " << duration.count() << " milliseconds" << endl;
    //Part to output the tree if needed
    //cout << "Sequential BST:" << endl;
    //obst->printLevelOrder(obst->getRoot());

    // Destroy the Singleton instance (if needed)
    OptimalBST::destroyInstance();
}

// Unit test for parallel construction of Optimal BST
TEST(OptimalBSTTest, ParallelConstruction) {
    vector<Rational> keys;
    vector<Rational> freq;
    readInput("input.txt", keys, freq);  // Adjust path here
    int n = keys.size();

    // Create OptimalBST instance (using Singleton pattern)
    OptimalBST* obst = OptimalBST::getInstance(keys.data(), freq.data(), n);

    auto start = high_resolution_clock::now();
    obst->constructOptimalBST(2);  // Parallel construction with 2 threads
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Parallel construction time: " << duration.count() << " milliseconds" << endl;
    //Part to output the tree if needed
    //cout << "Parallel BST:" << endl;
    //obst->printLevelOrder(obst->getRoot());

    // Destroy the Singleton instance (if needed)
    OptimalBST::destroyInstance();
}

// Main function to run all tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}