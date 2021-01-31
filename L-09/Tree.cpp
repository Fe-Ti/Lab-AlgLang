// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// AVL tree
// Partially was obtained at
// https://habr.com/ru/post/150732/

/*                                        .--------------->|subsub...
 *##################               -------v---------
 *#principle scheme#    .-------->|subtree root node|
 *##################    |          -------^---------
 *                      |                 *--------------->|subsub...
 *  ----       ---------v----
 * |tree|~~~~>|tree root node|
 *  ----       ---------^----
 *                      |                 .--------------->|subsub...
 *                      |          -------v---------
 *                      *-------->|subtree root node|
 *                                 -------^---------
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

template<typename K, typename T> struct AVLTNode {
    K key;
    T data;
    int16_t height = 1; // this is more than enough for an average desktop PC
    AVLTNode<K, T>* left_st = nullptr;
    AVLTNode<K, T>* right_st = nullptr;
};

template<typename K, typename T> struct AVLTree {
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
get_height(AVLTNode<K, T>* tnode)
{
    if(tnode == nullptr) {
        return 0;
    }
    return tnode->height;
}

template<typename K, typename T>
int16_t
get_balance_factor(AVLTNode<K, T>* tnode)
{
    return get_height(tnode->left_st) - get_height(tnode->right_st);
}

template<typename K, typename T>
void
reset_height(AVLTNode<K, T>* tnode)
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
    if(get_balance_factor(tnode) == -2) { // left turns (lsth - rsth == -2)
        if(get_balance_factor(tnode->right_st) > 0) {
            return left_great_turn(tnode);
        }
        return left_small_turn(tnode);
    } else if(get_balance_factor(tnode) == 2) { // right turns
        if(get_balance_factor(tnode->left_st) < 0) {
            return right_great_turn(tnode);
        }
        return right_small_turn(tnode);
    }
    return tnode;
}

template<typename K, typename T>
AVLTNode<K, T>*
add_node(AVLTNode<K, T>* tnode, K& key, T& data)
{
    if(tnode == nullptr) {
        return new AVLTNode<K, T>{ key, data };
    }
    if(tnode->key > key) { // going deeper
        tnode->left_st = add_node(tnode->left_st, key, data);
    } else {
        tnode->right_st = add_node(tnode->right_st, key, data);
    }
    reset_height(tnode);
    return rebalance_subtree(tnode);
}

template<typename K, typename T>
void
add(AVLTree<K, T>& atree, K& key, T& data)
{
    add_node(atree.root_pointer, key, data);
}

template<typename K, typename T>
void
destructor()
{
}

template<typename K, typename T>
void
lprint(AVLTNode<K, T>* tnode, std::string& level)
{
    if(tnode != nullptr) {
        std::cout << level << "⊦" << tnode->data << std::endl;
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
        std::cout << level << "⎿" << tnode->data << std::endl;
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

int
main()
{
    AVLTree<int, int> tester;
    for(int i = 0; i < 10; ++i)
        add(tester, i, i);
    print(tester);
}
