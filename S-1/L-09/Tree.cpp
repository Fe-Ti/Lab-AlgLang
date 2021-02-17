// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// AVL tree
// Some ideas were obtained at
// https://habr.com/ru/post/150732/
//
// Notes:
// 1) My structures are very similar to ones in the tutorial
// 2) The same is applicable to several functions like left and right small
// turns 3) The stuff mentioned above was done in the way:
//      - reading the article
//      - closing the browser
//      - grasping what is needed to do
//      - writing the code
//      - if got stuck then repeating these steps

/*                                        .--------------->|subsub...
 *##################               -----------------
 *#principle scheme#    .-------->|subtree root node|
 *##################    |          -----------------
 *                      |                 *--------------->|subsub...
 *  ----       --------------
 * |tree|~~~~>|tree root node|
 *  ----       --------------
 *                      |                 .--------------->|subsub...
 *                      |          -----------------
 *                      *-------->|subtree root node|
 *                                 -----------------
 *                                        *--------------->|subsub...
 *##############
 *# Structures #
 *##############
 *
 * tree:
 * |_pointer to the root
 *
 * tree_node:
 * |_key
 * |_left subtree pointer
 * |_right subtree pointer
 * |_height
 * |_data
 *
 *
 */

#include <iostream>
#include <string>

template<typename K, typename T>
struct AVLTNode {
    K key;
    T data;
    int16_t height = 1; // this is more than enough for an average desktop PC
    AVLTNode<K, T>* left_st = nullptr;
    AVLTNode<K, T>* right_st = nullptr;
};

template<typename K, typename T>
struct AVLTree {
    AVLTNode<K, T>* root_pointer;
};

template<typename K, typename T>
void
constructor(AVLTree<K, T>& atree)
{
    atree.root_pointer = nullptr;
}

template<typename K, typename T>
int16_t
get_height(AVLTNode<K, T>* tnode) // Returns a value > 0 if the tree exists
{
    if(tnode == nullptr) {
        return 0;
    }
    return tnode->height;
}

template<typename K, typename T>
int16_t
get_balance_factor(
  AVLTNode<K, T>* tnode) // the function is used to figure out if the subtree
                         // should be turned and what type of rotation is needed
{
    return get_height(tnode->left_st) - get_height(tnode->right_st);
}

template<typename K, typename T>
void
reset_height(AVLTNode<K, T>* tnode) // correcting the height of the node
{
    int16_t ls_height = get_height(tnode->left_st);
    int16_t rs_height = get_height(tnode->right_st);
    if(ls_height > rs_height) {
        tnode->height = ls_height;
    } else {
        tnode->height = rs_height;
    }
    ++tnode->height; // increasing node's height by 1
                     // because it was equal either left subtree height
                     // or to the right one
}

template<typename K, typename T>
AVLTNode<K, T>*
left_small_turn(AVLTNode<K, T>* tnode)
{
    AVLTNode<K, T>* tmp_ptr = tnode->right_st;
    tnode->right_st = tmp_ptr->left_st;
    tmp_ptr->left_st = tnode;
    reset_height(tnode);
    reset_height(tmp_ptr);
    return tmp_ptr;
}

template<typename K, typename T>
AVLTNode<K, T>*
right_small_turn(AVLTNode<K, T>* tnode)
{
    AVLTNode<K, T>* tmp_ptr = tnode->left_st;
    tnode->left_st = tmp_ptr->right_st;
    tmp_ptr->right_st = tnode;
    reset_height(tnode);
    reset_height(tmp_ptr);
    return tmp_ptr;
}

template<typename K, typename T>
AVLTNode<K, T>*
left_great_turn(AVLTNode<K, T>* tnode)
{
    tnode->right_st = right_small_turn(tnode->right_st);
    AVLTNode<K, T>* tmp_ptr = left_small_turn(tnode);
    return tmp_ptr;
}

template<typename K, typename T>
AVLTNode<K, T>*
right_great_turn(AVLTNode<K, T>* tnode)
{
    tnode->left_st = left_small_turn(tnode->left_st);
    AVLTNode<K, T>* tmp_ptr = right_small_turn(tnode);
    return tmp_ptr;
}

template<typename K, typename T>
AVLTNode<K, T>*
rebalance_subtree(AVLTNode<K, T>* tnode)
{
    reset_height(tnode);
    if(get_balance_factor(tnode) == -2) { // left turns (lsth - rsth == -2)
        std::cout << "YES! " << std::endl;
        if(get_balance_factor(tnode->right_st) > 0) {
            return left_great_turn(tnode);
        }
        return left_small_turn(tnode);
    } else if(get_balance_factor(tnode) == 2) { // right turns
        std::cout << "YES! " << std::endl;
        if(get_balance_factor(tnode->left_st) < 0) {
            return right_great_turn(tnode);
        }
        return right_small_turn(tnode);
    }
    std::cout << "NO! " << std::endl;
    return tnode;
}

template<typename K, typename T>
AVLTNode<K, T>*
add_node(AVLTNode<K, T>* tnode, K& key, T& data)
{
    if(tnode == nullptr) {
        std::cout << "Inserted" << data << std::endl;
        return new AVLTNode<K, T>{ key, data };
    } else {
        if(tnode->key > key) { // going deeper
            std::cout << "Going left" << std::endl;
            tnode->left_st = add_node(tnode->left_st, key, data);
        } else {
            std::cout << "Going right" << std::endl;
            tnode->right_st = add_node(tnode->right_st, key, data);
        }
        std::cout << "Rebalance? " << std::endl;
        return rebalance_subtree(tnode);
    }
}

template<typename K, typename T>
void
add(AVLTree<K, T>& atree, K& key, T& data)
{
    atree.root_pointer = add_node(atree.root_pointer, key, data);
}

template<typename K, typename T>
AVLTNode<K, T>*
find_max(AVLTNode<K, T>* tnode, AVLTNode<K, T>*& maxkey_node)
{
    if(tnode->right_st != nullptr) {
        tnode->right_st = find_max(tnode->right_st, maxkey_node);
        return rebalance_subtree(tnode);
    } else {
        maxkey_node = tnode;
        return tnode->left_st;
    }
}

template<typename K, typename T>
AVLTNode<K, T>*
remove_node(AVLTNode<K, T>* tnode, K& key)
{
    if(tnode != nullptr) {
        if(tnode->key == key) {
            std::cout << "Data at the given key is " << tnode->data
                      << std::endl;
            AVLTNode<K, T>* sub_ptr;
            if(tnode->left_st != nullptr) {
                tnode->left_st = find_max(tnode->left_st, sub_ptr);
                sub_ptr->left_st = tnode->left_st;
                sub_ptr->right_st = tnode->right_st;
            } else {
                sub_ptr = tnode->right_st;
            }
            delete tnode;
            return sub_ptr;
        } else {
            if(tnode->key > key) { // going deeper
                std::cout << "Going left" << std::endl;
                tnode->left_st = remove_node(tnode->left_st, key);
            } else {
                std::cout << "Going right" << std::endl;
                tnode->right_st = remove_node(tnode->right_st, key);
            }
            std::cout << "Rebalance?" << std::endl;
            return rebalance_subtree(tnode);
        }
    } else {
        return tnode;
    }
}

template<typename K, typename T>
void
remove(AVLTree<K, T>& atree, K& key)
{
    atree.root_pointer = remove_node(atree.root_pointer, key);
}

template<typename K, typename T>
void
erase_tree(AVLTNode<K, T>* tnode)
{
    if(tnode->left_st != nullptr) {
        erase_tree(tnode->left_st);
    }
    if(tnode->right_st != nullptr) {
        erase_tree(tnode->right_st);
    }
    delete tnode;
}

template<typename K, typename T>
void
destructor(AVLTree<K, T>& atree)
{
    std::cout << "Destructing!... ";
    erase_tree(atree.root_pointer);
    std::cout << "[ DONE ]" << std::endl;
}

template<typename K, typename T>
void
lprint(AVLTNode<K, T>* tnode, std::string& level)
{
    if(tnode != nullptr) {
        std::cout << level << "├" << tnode->data << std::endl;
        level.push_back('|');
        lprint(tnode->left_st, level);
        rprint(tnode->right_st, level);
        level.pop_back();
    }
}

template<typename K, typename T>
void
rprint(AVLTNode<K, T>* tnode, std::string& level)
{
    if(tnode != nullptr) {
        std::cout << level << "└" << tnode->data << std::endl;
        level.push_back(' ');
        lprint(tnode->left_st, level);
        rprint(tnode->right_st, level);
        level.pop_back();
    }
}

template<typename K, typename T>
void
print(AVLTree<K, T> atree)
{
    std::string level;
    std::cout << atree.root_pointer->data << std::endl;
    lprint(atree.root_pointer->left_st, level);
    rprint(atree.root_pointer->right_st, level);
}

template<typename K, typename T>
void
find_node(AVLTNode<K, T>* tnode, K key, T& data)
{
    if(tnode != nullptr) {
        if(tnode->key == key) {
            data = tnode->data;
        } else {
            if(tnode->key > key) {
                find_node(tnode->left_st, key, data);
            } else {
                find_node(tnode->right_st, key, data);
            }
        }
    }
}

template<typename K, typename T>
T
find(AVLTree<K, T> atree, K key)
{
    T data;
    find_node(atree.root_pointer, key, data);
    return data;
}

int
main()
{
    int lim = 0;
    std::cout << "Enter the limit (int value)" << std::endl;
    std::cin >> lim;
    AVLTree<int, int> tester;
    constructor(tester);
    for(int i = 0; i < lim; ++i) {
        add(tester, i, i);
        print(tester);
        std::cout << "Added " << i << std::endl;
    }
    print(tester);
    while(lim != -1) {
        print(tester);
        std::cout << "Enter the the key to remove (-1 to skip)" << std::endl;
        std::cin >> lim;
        if(lim != -1)
            remove(tester, lim);
    }
    while(lim != -2) {
        print(tester);
        std::cout << "Enter the the key to remove (-2 to skip)" << std::endl;
        std::cin >> lim;
        if(lim != -2)
            std::cout << find(tester, lim) << std::endl;
    }
    print(tester);
    destructor(tester);
    return 0;
}
