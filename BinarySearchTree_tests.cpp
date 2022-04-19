// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"

#include "unit_test_framework.h"

using namespace std;

TEST(pretest) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    ASSERT_TRUE(tree.size() == 1);
}


TEST(test_empty_impl) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_TRUE(tree.size() == 0);
    ASSERT_TRUE(tree.height() == 0);
}

TEST(test_size_impl) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    ASSERT_TRUE(tree.size() == 1);
}

TEST(test_height_impl) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    ASSERT_TRUE(tree.height() == 1);
}

TEST(test_height_impl_skew_right) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    ASSERT_TRUE(tree.height() == 3);
}

TEST(test_height_impl_skew_left) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    ASSERT_TRUE(tree.height() == 3);
}

TEST(test_height_impl_asymmetric_right) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);
    ASSERT_TRUE(tree.height() == 3);
    ASSERT_TRUE(tree.size() == 4);
}

TEST(test_height_impl_asymmetric_left) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);
    ASSERT_TRUE(tree.height() == 3);
    ASSERT_TRUE(tree.size() == 4);
}

TEST(test_iterator) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    BinarySearchTree<int>::Iterator i = tree.begin();
    ASSERT_TRUE(tree.size() == 3);
    ASSERT_TRUE(*i == 2);
}

TEST(testfindbasic) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);

    BinarySearchTree<int>::Iterator i = tree.find(2);
    ASSERT_TRUE(*i == 2);
}

TEST(testfindfail) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    BinarySearchTree<int>::Iterator i1(tree.end());
    BinarySearchTree<int>::Iterator i2 = tree.find(5);
    bool isTrue = false;
    if (i1 == i2) {
        isTrue = true;
    }
    assert(isTrue);
}

TEST(testfindleft) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);
    
    BinarySearchTree<int>::Iterator i = tree.find(3);
    ASSERT_TRUE(*i == 3);

    i = tree.find(2);
    ASSERT_TRUE(*i == 2);

    i = tree.find(1);
    ASSERT_TRUE(*i == 1);
}

TEST(testfindright) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);

    BinarySearchTree<int>::Iterator i = tree.find(2);
    ASSERT_TRUE(*i == 2);

    i = tree.find(3);
    ASSERT_TRUE(*i == 3);

    i = tree.find(4);
    ASSERT_TRUE(*i == 4);
}

TEST(testmaxminone) {
    BinarySearchTree<int> tree;
    tree.insert(3);

    BinarySearchTree<int>::Iterator i = tree.max_element();
    ASSERT_TRUE(*i = 3);

    i = tree.min_element();
    ASSERT_TRUE(*i = 3);
}

TEST(testbasictree) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);

    BinarySearchTree<int>::Iterator i = tree.max_element();
    ASSERT_TRUE(*i == 4);

    i = tree.min_element();
    ASSERT_TRUE(*i == 2);

    tree.insert(1);

    i = tree.min_element();
    ASSERT_TRUE(*i == 1);
}

// testtraverseinorder
// test traverse in order one element
TEST(test1) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "3 ");
}

// test traverse in order basic tree
TEST(test2) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(1);

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "1 2 3 ");
    
    cout << endl;

    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "2 1 3 ");
}

// test traverse skew left
TEST(test3) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "1 2 3 4 ");
    
    cout << endl;

    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "3 2 1 4 ");
}

// test traverse skew right
TEST(test4) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    ASSERT_TRUE(oss_inorder.str() == "1 2 3 4 ");
    
    cout << endl;

    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "2 1 3 4 ");
}

// large test case
/*
TEST(test5) {
    BinarySearchTree<int> tree;
    tree.insert(100);
    tree.insert(80);
    tree.insert(110);
    tree.insert(81);
    tree.insert(4);
    tree.insert(1);
    tree.insert(78);
    tree.insert(79);
    tree.insert(68);
    tree.insert(75);
    tree.insert(20);
    tree.insert(24);
    tree.insert(22);
    tree.insert(107);
    tree.insert(120);
    tree.insert(109);
    tree.insert(105);

    ostringstream oss_inorder;
    tree.traverse_inorder(oss_inorder);
    cout << "inorder" << endl;
    cout << oss_inorder.str() << endl << endl;
    string s = "1 4 20 22 24 68 75 78 79 80 81 100 105 107 109 110 120 ";
    ASSERT_TRUE(oss_inorder.str() == s);
    
    cout << endl;

    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    string s = "100 80 4 1 78 68 20 24 22 75 79 81 110 107 105 109 120 ";
    ASSERT_TRUE(oss_preorder.str() == s);

    BinarySearchTree<int>::Iterator i = tree.max_element();
    ASSERT_TRUE(*i == 120);

    i = tree.min_element();
    ASSERT_TRUE(*i == 1);
}
*/

TEST(test6) {
    BinarySearchTree<int> tree;
    tree.insert(3);

    ostringstream oss_preorder;
    tree.traverse_preorder(oss_preorder);
    cout << "preorder" << endl;
    cout << oss_preorder.str() << endl << endl;
    ASSERT_TRUE(oss_preorder.str() == "3 ");
}

TEST(test7) {
    BinarySearchTree<int> tree;
    assert(tree.check_sorting_invariant());
}

TEST(test8) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    assert(tree.check_sorting_invariant());
}

// tests if max/min works for empty trees
TEST(test9) {
    BinarySearchTree<int> tree;
    bool maxIsTrue = false;
    bool minIsTrue = false;
    BinarySearchTree<int>::Iterator i(tree.end());
    if (i == tree.max_element()) {
        maxIsTrue = true;
    }
    if (i == tree.min_element()) {
        minIsTrue = true;
    }
    assert(maxIsTrue);
    assert(minIsTrue);
}

// tests max/min for one element
TEST(test10) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    ASSERT_TRUE(*(tree.max_element()) == 3);
    ASSERT_TRUE(*(tree.min_element()) == 3);
}

// max/min test tree skew left
TEST(test11) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(3);
    tree.insert(5);
    tree.insert(2);
    
    BinarySearchTree<int>::Iterator i = tree.max_element();
    ASSERT_TRUE(*i == 5);

    i = tree.min_element();
    ASSERT_TRUE(*i == 2);

    tree.insert(1);

    BinarySearchTree<int>::Iterator i2 = tree.min_element();
    ASSERT_TRUE(*i2 == 1);
}

TEST(test12) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(2);
    
    BinarySearchTree<int>::Iterator i = tree.max_element();
    ASSERT_TRUE(*i == 5);

    i = tree.min_element();
    ASSERT_TRUE(*i == 2);

    tree.insert(1);

    BinarySearchTree<int>::Iterator i2 = tree.min_element();
    ASSERT_TRUE(*i2 == 1);
}

TEST(test13) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(1);

    BinarySearchTree<int>::Iterator i = tree.find(2);
    ASSERT_TRUE(*i == 2);

    i = tree.find(3);
    ASSERT_TRUE(*i == 3);

    i = tree.find(4);
    ASSERT_TRUE(*i == 4);
}

TEST(test14) {
    BinarySearchTree<int> tree1;
    tree1.insert(3);
    tree1.insert(2);
    tree1.insert(4);
    tree1.insert(1);
    ASSERT_TRUE(tree1.height() == 3);
    ASSERT_TRUE(tree1.size() == 4);

    BinarySearchTree<int> tree2 = tree1;

    BinarySearchTree<int>::Iterator i1;
    BinarySearchTree<int>::Iterator i2 = tree2.begin();
    BinarySearchTree<int>::Iterator i3 = tree1.end();

    for (i1 = tree1.begin(); i1 == i3; i1++) {
        ASSERT_TRUE(*i1 == *i2);
        i2++;
    }
    ASSERT_TRUE(tree2.size() == 4);
}

TEST(test15) {
    BinarySearchTree<int> tree;
    bool isTrue = false;
    isTrue = tree.check_sorting_invariant();
    assert(isTrue);
}

TEST(test16) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    bool isTrue = false;
    isTrue = tree.check_sorting_invariant();
    assert(isTrue);
}

TEST(test17) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    bool isTrue = false;
    isTrue = tree.check_sorting_invariant();
    assert(isTrue);
}

TEST(test18) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    bool isTrue = false;
    isTrue = tree.check_sorting_invariant();
    assert(isTrue);
}

TEST(test19) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    bool isTrue = false;
    isTrue = tree.check_sorting_invariant();
    assert(isTrue);
}

TEST(test20) {
    BinarySearchTree<int> tree;
    tree.insert(101);
    tree.insert(81);
    tree.insert(111);
    tree.insert(82);
    tree.insert(5);
    tree.insert(2);
    tree.insert(79);
    tree.insert(80);
    tree.insert(69);
    tree.insert(76);
    tree.insert(21);
    tree.insert(25);
    tree.insert(23);
    tree.insert(108);
    tree.insert(121);
    tree.insert(110);
    tree.insert(106);

    ASSERT_EQUAL(76, *tree.min_greater_than(69));
    ASSERT_EQUAL(76, *tree.min_greater_than(73));
    ASSERT_EQUAL(23, *tree.min_greater_than(22));
    ASSERT_EQUAL(82, *tree.min_greater_than(81));
    ASSERT_EQUAL(110, *tree.min_greater_than(109));
    ASSERT_EQUAL(108, *tree.min_greater_than(107));
    ASSERT_EQUAL(101, *tree.min_greater_than(100));
    ASSERT_EQUAL(2, *tree.min_greater_than(1));
    ASSERT_EQUAL(21, *tree.min_greater_than(20));
    ASSERT_EQUAL(79, *tree.min_greater_than(78));
}

TEST(test21) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    bool isTrue = false;
    isTrue = tree.check_sorting_invariant();
    assert(isTrue);
}

// test traverse skew right
TEST(test22) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    assert(tree.check_sorting_invariant());
}

// test traverse skew left
TEST(test23) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);
    assert(tree.check_sorting_invariant());
}

TEST(test24) {
    BinarySearchTree<int> tree;
    tree.insert(2);
    ASSERT_TRUE(tree.size() == 1);
}

TEST(test_copy_subtree) {
    BinarySearchTree<int> tree1;
    tree1.insert(100);
    tree1.insert(90);
    tree1.insert(101);
    tree1.insert(80);
    tree1.insert(99);
    tree1.insert(98);
    tree1.insert(97);
    tree1.insert(102);
    tree1.insert(103);
    ASSERT_TRUE(tree1.height() == 5);
    ASSERT_TRUE(tree1.size() == 9);

    BinarySearchTree<int>::Iterator i1 = tree1.begin();
    ++i1;
    ++i1;
}

TEST(test25) {
    BinarySearchTree<int> tree;
    bool isTrue = false;
    BinarySearchTree<int>::Iterator i = tree.end();
    if (tree.min_greater_than(9) == i) {
        isTrue = true;
    }
    assert(isTrue);
}

TEST(test26) {
    BinarySearchTree<int> tree;
    tree.insert(3);
    BinarySearchTree<int>::Iterator i = tree.end();
    bool isTrue = false;
    if (tree.min_greater_than(9) == i) {
        isTrue = true;
    }
    assert(isTrue);
    ASSERT_EQUAL(*tree.min_greater_than(2), 3);
}

TEST(test27){
    BinarySearchTree<int> tree;
    tree.insert(7);
    tree.insert(5);
    tree.insert(9);
    BinarySearchTree<int>::Iterator i = tree.begin();
    *i = 7;
    ASSERT_FALSE(tree.check_sorting_invariant());
}


TEST(test28){
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(4);
    tree.insert(10);
    BinarySearchTree<int>::Iterator i = tree.begin();
    ++i;
    ++i;
    *i = 7;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test29){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    tree.insert(8);
    BinarySearchTree<int>::Iterator i = tree.begin();
    ++i;
    ++i;
    *i = 7;
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test30){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(7);
    tree.insert(9);
    BinarySearchTree<int>::Iterator i = tree.begin();
    ++i;
    ++i;
    *i = 4;
}

TEST(test31) {
    BinarySearchTree<int> tree1;
    tree1.insert(3);
    BinarySearchTree<int> tree2 = tree1;
    BinarySearchTree<int>::Iterator i = tree2.begin();
    ASSERT_TRUE(tree2.size() == 1);
    ASSERT_TRUE(*i == 3);
}

TEST(test32) {
    BinarySearchTree<int> tree1;
    tree1.insert(3);
    tree1.insert(4);
    BinarySearchTree<int> tree2 = tree1;
    BinarySearchTree<int>::Iterator i = tree2.begin();
    ASSERT_TRUE(tree2.size() == 2);
    ++i;
    ASSERT_TRUE(*i == 4);
}

TEST(test33) {
    BinarySearchTree<int> tree1;
    tree1.insert(3);
    tree1.insert(2);
    tree1.insert(4);
    BinarySearchTree<int> tree2 = tree1;
    BinarySearchTree<int>::Iterator i = tree2.begin();
    ASSERT_TRUE(tree2.size() == 3);
    ++i;
    ASSERT_TRUE(*i == 3);
}

TEST(bst_public_test) {
  BinarySearchTree<int> tree;

  tree.insert(5);

  ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);

  ASSERT_TRUE(tree.find(5) != tree.end());

  tree.insert(7);
  tree.insert(3);

  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_TRUE(*tree.max_element() == 7);
  ASSERT_TRUE(*tree.min_element() == 3);
  ASSERT_TRUE(*tree.min_greater_than(5) == 7);

  cout << "cout << tree.to_string()" << endl;
  cout << tree.to_string() << endl << endl;

  cout << "cout << tree" << endl << "(uses iterators)" << endl;
  cout << tree << endl << endl;

  ostringstream oss_preorder;
  tree.traverse_preorder(oss_preorder);
  cout << "preorder" << endl;
  cout << oss_preorder.str() << endl << endl;
  ASSERT_TRUE(oss_preorder.str() == "5 3 7 ");

  ostringstream oss_inorder;
  tree.traverse_inorder(oss_inorder);
  cout << "inorder" << endl;
  cout << oss_inorder.str() << endl << endl;
  ASSERT_TRUE(oss_inorder.str() == "3 5 7 ");
}


TEST_MAIN()


