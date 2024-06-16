# Optimal BST that uses threads to fasten the process of building it.

---

## The unit tests are performed on an example of one tree with 100 nodes. OBST class is made using singleton pattern.

---

This project implements an Optimal Binary Search Tree (BST) using Rational 
numbers, which are represented by a custom Rational class. The optimal BST minimizes 
the expected search cost by arranging keys based on their frequencies.
It has: 3 classes: Node, Rational and OptimalBST. To build a test tree with a bunch of nodes, we use input.txt document, where we have entered around 100 key/frequency pairs.
After constructing each tree with 2 different methods, we can see time in which the tree had been created.

---

The time difference:

![image](https://github.com/qwfm/oop-lab-work-2.3-a-/assets/146103678/4fcd4750-5ef6-4f2e-9442-e03607fcfffc)

and 

![image](https://github.com/qwfm/oop-lab-work-2.3-a-/assets/146103678/5259f98f-33cb-432d-864a-93138d7d5151)

From this comperison, we can see that using threads to build a tree is faster, than sequential method.

---
Documentation was written in doxygen and for unit tests I used Google Tests.
