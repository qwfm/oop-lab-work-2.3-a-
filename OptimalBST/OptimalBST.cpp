#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <queue>
#include "Rational.h"  // Assuming Rational class is defined elsewhere

using namespace std;
using namespace std::chrono;

// Node class for the binary search tree
class Node {
public:
    Rational key; ///< Key value stored in the node
    Node* left;   ///< Pointer to the left child node
    Node* right;  ///< Pointer to the right child node

    /**
     * @brief Constructor to initialize a Node with a Rational key.
     * @param k Rational key value for the node.
     */
    Node(Rational k) : key(k), left(nullptr), right(nullptr) {}
};

// OptimalBST class with Singleton pattern
class OptimalBST {
private:
    Rational** cost;  ///< Cost matrix for optimal BST
    Node*** root;     ///< Root matrix for optimal BST nodes
    Rational* keys;   ///< Array of keys
    Rational* freq;   ///< Array of frequencies
    int n;            ///< Number of keys

    // Static instance variable for Singleton pattern
    static OptimalBST* instance;

    /**
     * @brief Private constructor for OptimalBST class.
     * @param keys Array of Rational keys.
     * @param freq Array of frequencies corresponding to keys.
     * @param n Number of keys.
     */
    OptimalBST(Rational* keys, Rational* freq, int n) : keys(keys), freq(freq), n(n) {
        // Initialize cost and root matrices
        cost = new Rational * [n];
        root = new Node * *[n];
        for (int i = 0; i < n; ++i) {
            cost[i] = new Rational[n];
            root[i] = new Node * [n];
        }
    }

public:
    /**
     * @brief Destructor to free dynamically allocated memory.
     */
    ~OptimalBST() {
        for (int i = 0; i < n; ++i) {
            delete[] cost[i];
            delete[] root[i];
        }
        delete[] cost;
        delete[] root;
    }

    /**
     * @brief Method to access the singleton instance of OptimalBST.
     * @param keys Array of Rational keys.
     * @param freq Array of frequencies corresponding to keys.
     * @param n Number of keys.
     * @return Singleton instance of OptimalBST.
     */
    static OptimalBST* getInstance(Rational* keys, Rational* freq, int n) {
        if (instance == nullptr) {
            instance = new OptimalBST(keys, freq, n);
        }
        return instance;
    }

    /**
     * @brief Method to destroy the singleton instance of OptimalBST.
     */
    static void destroyInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }

    /**
     * @brief Method to compute optimal BST cost in a specified range.
     * @param start Starting index of the range.
     * @param end Ending index of the range.
     */
    void parallelComputeCost(int start, int end) {
        for (int length = 1; length <= n; ++length) {
            for (int i = start; i <= end && i <= n - length; ++i) {
                int j = i + length - 1;
                computeCost(i, j);
            }
        }
    }

    /**
     * @brief Helper method to compute cost and construct optimal BST for a given range.
     * @param i Starting index of the range.
     * @param j Ending index of the range.
     * @return Minimum cost of the optimal BST in the range [i, j].
     */
    Rational computeCost(int i, int j) {
        Rational totalFreq = Rational(0, 1);
        for (int k = i; k <= j; ++k) {
            totalFreq = totalFreq + freq[k];
        }

        Rational minCost = Rational::infinity();
        for (int r = i; r <= j; ++r) {
            Rational leftCost = (r > i) ? cost[i][r - 1] : Rational(0, 1);
            Rational rightCost = (r < j) ? cost[r + 1][j] : Rational(0, 1);
            Rational currentCost = leftCost + rightCost + totalFreq;

            if (currentCost < minCost) {
                minCost = currentCost;
                root[i][j] = new Node(keys[r]);
                root[i][j]->left = (r > i) ? root[i][r - 1] : nullptr;
                root[i][j]->right = (r < j) ? root[r + 1][j] : nullptr;
            }
        }

        cost[i][j] = minCost;
        return minCost;
    }

    /**
     * @brief Method to construct optimal BST using parallel threads.
     * @param numThreads Number of threads to use.
     */
    void constructOptimalBST(int numThreads) {
        vector<thread> threads;
        int chunkSize = n / numThreads;
        for (int t = 0; t < numThreads; ++t) {
            int start = chunkSize * t;
            int end = (t == numThreads - 1) ? n - 1 : chunkSize * (t + 1) - 1;
            threads.emplace_back(&OptimalBST::parallelComputeCost, this, start, end);
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }

    /**
     * @brief Method to get the root node of the constructed optimal BST.
     * @return Root node of the optimal BST.
     */
    Node* getRoot() {
        return root[0][n - 1];
    }

    /**
     * @brief Method to print the nodes of the BST level by level.
     * @param root Root node of the BST to print.
     */
    void printLevelOrder(Node* root) {
        if (!root)
            return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                Node* node = q.front();
                q.pop();
                cout << "(" << node->key.getNumerator() << "/" << node->key.getDenominator() << ") ";
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            cout << endl;
        }
    }
};

// Initialize the static instance variable
OptimalBST* OptimalBST::instance = nullptr;