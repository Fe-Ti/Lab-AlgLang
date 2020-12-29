// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// AVL tree
//
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
 * |_size
 *
 * tree_node:
 * |_pointer to parent (if is main root, then nullptr)
 * |_2 pointers to children (if is leaf, then nullptr)
 * |_subtree size (amount of nodes)
 * |_data
 *
 *
 */

#include <iostream>
#include <utility>

template<typename K, typename T> struct Tree_node {
    K key;
    Tree_node<K, T>* parent;
    Tree_node<K, T>* lchild;
    Tree_node<K, T>* rchild;
    unsigned int tsize;
    unsigned int theight;
    T data;
};

template<typename K, typename T> struct Tree {
    Tree_node<K, T>* rootptr;
    unsigned int tsize;
    unsigned int theight;
};

template<typename K, typename T>
Tree_node<K, T>*
init_node(K key,
          T data,
          Tree_node<K, T>* parent = nullptr,
          Tree_node<K, T>* lchild = nullptr,
          Tree_node<K, T>* rchild = nullptr,
          unsigned int tsize = 1,
          unsigned int theight = 1)
{
    return new Tree_node<K, T>
    {
        key,
        parent,
        lchild,
        rchild,
        tsize,
        theight,
        data
    }
}

template<typename K, typename T>
void
constructor(Tree<K, T>& birch) // birch is a tree so why not?
{
    birch.rootptr = nullptr;
    birch.theight = 0;
    birch.tsize = 0;
}

template<typename K, typename T>
void
leftsmall_turn()
{
}

template<typename K, typename T>
void
rightsmall_turn()
{
}

template<typename K, typename T>
void
leftbig_turn()
{
}

template<typename K, typename T>
void
rightbig_turn()
{
}
template<typename K, typename T>
void
add(Tree_node<R, T>& branch, K key, T data, bool check_enable = true)
{
}

template<typename K, typename T>
void
add(Tree<K, T>& birch, K key, T data, bool check_enable = true)
{
    if(birch.rootptr != nullptr) {

    } else {
        birch.rootptr = init_node(key, data);
    }
}

template<typename K, typename T>
void
add(Tree<K, T>& birch, pair<K, T> tuple) // an overload for pairs
{
    add(birch, tuple.first, tuple.second); // simply parse the pair
}

template<typename K, typename T>
void
remove()
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
    return 0;
}
