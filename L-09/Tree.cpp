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
#include <string>
#include <utility>

template<typename K, typename T> struct Tree_node {
    K key;
    Tree_node<K, T>* parent;
    Tree_node<K, T>* lchild;
    Tree_node<K, T>* rchild;
    unsigned int t_height;
    unsigned int lst_max_height;
    unsigned int rst_max_height;
    T data;
};

template<typename K, typename T> struct Tree {
    Tree_node<K, T>* rootptr;
    unsigned int t_size;
    // unsigned int t_height;
};

template<typename K, typename T>
Tree_node<K, T>*
init_node(K key,
          T data,
          Tree_node<K, T>* parent = nullptr,
          Tree_node<K, T>* lchild = nullptr,
          Tree_node<K, T>* rchild = nullptr,
          unsigned int rst_max_height = 0,
          unsigned int lst_max_height = 0,
          unsigned int t_height = 1)
{
    return new Tree_node<K, T>{
        key,      parent,         lchild,         rchild,
        t_height, lst_max_height, rst_max_height, data
    };
}

template<typename K, typename T>
void
constructor(Tree<K, T>& birch) // birch is a tree so why not?
{
    birch.rootptr = nullptr;
    birch.t_size = 0;
}

template<typename K, typename T>
bool
wants_lsmt(Tree_node<K, T>*& branch)
{
}

template<typename K, typename T>
bool
wants_rsmt(Tree_node<K, T>*& branch)
{
}

template<typename K, typename T>
bool
wants_lbt(Tree_node<K, T>*& branch)
{
}

template<typename K, typename T>
bool
wants_rbt(Tree_node<K, T>*& branch)
{
}

template<typename K, typename T>
void // prototyping
left_small_turn(Tree_node<K, T>*& branch)
{
    Tree_node<K, T>*;
    if(branch->parent->lchild == branch) // if branch is lchild of parent then
        branch->parent->lchild = branch->rchild; // change l parent's pointer
    else                                         // else
        branch->parent->rchild = branch->rchild; // change right one

    // branch->lchild is kept in place
    branch->rchild->parent = branch->parent;
    branch->parent = branch->rchild;
    branch->rchild->lchild->parent = branch;
}

template<typename K, typename T>
void
right_small_turn()
{
}

template<typename K, typename T>
void
left_big_turn()
{
}

template<typename K, typename T>
void
right_big_turn()
{
}

// internal functions
template<typename K, typename T>
void
update_lstmh(Tree_node<K, T>*& branch, Tree_node<K, T>*& new_node)
{
    if(new_node->t_height > branch->lst_max_height)
        branch->lst_max_height = new_node->t_height;
}
template<typename K, typename T>
void
update_rstmh(Tree_node<K, T>*& branch, Tree_node<K, T>*& new_node)
{
    if(new_node->t_height > branch->rst_max_height)
        branch->rst_max_height = new_node->t_height;
}

template<typename K, typename T>
void
grow(Tree_node<K, T>*& branch,
     Tree_node<K, T>*& new_node,
     bool check_enable = true)
{
    if(branch == nullptr) {
        branch = new_node;
    } else {
        new_node->parent = branch;
        ++new_node->t_height;
        if(branch->key > new_node->key) {
            grow(branch->lchild, new_node, check_enable);
            update_lstmh(branch, new_node);
        } else {
            grow(branch->rchild, new_node, check_enable);
            update_rstmh(branch, new_node);
        }
        if(check_enable) {
            if(wants_lsmt(branch)) {
                left_small_turn();
            }
            if(wants_rsmt(branch)) {
                right_small_turn();
            }
            if(wants_lbt(branch)) {
                left_big_turn();
            }
            if(wants_rbt(branch)) {
                right_big_turn();
            }
        }
    }
}

template<typename K, typename T>
void
add(Tree<K, T>& birch, K key, T data, bool check_enable = true)
{
    Tree_node<K, T>* new_node = init_node(key, data);
    if(birch.rootptr != nullptr) {
        grow(birch.rootptr, new_node, check_enable);
    } else {
        birch.rootptr = new_node;
    }
    std::cout << "Added " << data << " with key " << key << std::endl;
}

template<typename K, typename T>
void
add(Tree<K, T>& birch, std::pair<K, T> tuple) // an overload for pairs
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
recuprint(Tree_node<K, T>*& branch, std::string& recuheader)
{
    std::cout << recuheader << branch->data << std::endl;
    if(!recuheader.empty())
        recuheader.erase(recuheader.size() - 7, 7);
    recuheader.push_back('|');
    if(branch->lchild != nullptr) {
        recuheader += "LChild ";
        recuprint(branch->lchild, recuheader);
    }
    if(branch->rchild != nullptr) {
        recuheader += "RChild ";
        recuprint(branch->rchild, recuheader);
    }
    recuheader.pop_back();
}

template<typename K, typename T>
void
print(Tree<K, T>& birch)
{
    std::string recuheader;
    std::cout << "AVeryLittle Tree:" << std::endl << "Root ";
    recuprint(birch.rootptr, recuheader);
}

template<typename K, typename T>
void
destructor()
{
}

int
main()
{
    Tree<int, std::string> tester;
    constructor(tester);
    add(tester, 5, std::string("5"));
    add(tester, 4, std::string("4"));
    add(tester, 2, std::string("2"));
    add(tester, 3, std::string("3"));
    add(tester, 1, std::string("1"));
    add(tester, 6, std::string("6"));
    add(tester, 8, std::string("8"));
    add(tester, 7, std::string("7"));
    add(tester, 234, std::string("234"));
    add(tester, 2347, std::string("2347"));
    print(tester);
    return 0;
}
