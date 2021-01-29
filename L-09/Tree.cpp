// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// AVL tree
// Some information was obtained at https://habr.com/ru/post/150732/
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
    uint16_t height = 1; // this is more than enough for an average desktop PC
    AVLTNode<K, T>* left_st = nullptr;
    AVLTNode<K, T>* right_st = nullptr;
};

template<typename K, typename T> struct AVLTree {
    AVLTNode<K, T>* root_pointer = nullptr;
};

template<typename K, typename T>
void
constructor()
{
    
}

template<typename K, typename T>
void
destructor()
{
    
}

int
main()
{
    
}
