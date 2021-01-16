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
//#include <thread>
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
std::ostream&
pp(std::ostream& out, Tree_node<K, T>*& node) // superinternal func
                                              // prints info about a given node
{
    out << "Node   : " << node->key << std::endl;
    out << " data  : " << node->data << std::endl;
    out << " parent: " << node->parent << std::endl;
    out << " lchild: " << node->lchild << std::endl;
    out << " rchild: " << node->rchild << std::endl;
    out << " rstmh : " << node->rst_max_height << std::endl;
    out << " lstmh : " << node->lst_max_height << std::endl;
    out << " th    : " << node->t_height << std::endl;
    out << " own pt: " << node << std::endl;
    return out;
}
template<typename K, typename T>
Tree_node<K, T>*
get_pointer() // superinternal function //TODO!
{
    Tree_node<K, T>* node;
    return node;
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
exists(Tree_node<K, T>*& branch)
{
    if(branch != nullptr)
        return true;
    return false;
}
template<typename K, typename T>
bool
wants_lsmt(Tree_node<K, T>*& branch)
{
    return false;
}

template<typename K, typename T>
bool
wants_rsmt(Tree_node<K, T>*& branch)
{
    return false;
}

template<typename K, typename T>
bool
wants_lbt(Tree_node<K, T>*& branch)
{
    return false;
}

template<typename K, typename T>
bool
wants_rbt(Tree_node<K, T>*& branch)
{
    return false;
}

template<typename K, typename T>
void
left_small_turn(Tree_node<K, T>& branch)
{
    if(branch.rchild != nullptr && branch.rchild->lchild != nullptr) {
        // branch->lchild and rchild's rchild are kept in place
        std::cout << "Begin optimization: lsmt" << std::endl;
        if(branch.parent != nullptr) {
            // grand parent's stuff --ROFL--
            //// if branch is lchild of parent then
            //// change l parent's pointer
            //// else
            //// change the right one

            if(branch.parent->lchild == &branch) {
                // std::cout << "Thread #" << std::this_thread::get_id();
                std::cout << " setting parent's pointer" << std::endl;
                branch.parent->lchild = branch.rchild;
            } else {
                // std::cout << "Thread #" << std::this_thread::get_id();
                std::cout << " setting parent's pointer" << std::endl;
                branch.parent->rchild = branch.rchild;
            }
        }
        branch.rchild->parent = branch.parent;
        branch.parent = branch.rchild;
        branch.rchild->lchild->parent = &branch;
        branch.rchild = branch.rchild->lchild;
        branch.parent->lchild = &branch;
        std::cout << "End optimization: lsmt" << std::endl;
    }
}

template<typename K, typename T>
void
right_small_turn(Tree_node<K, T>& branch) // the same as lsmt
{
    if(branch.lchild != nullptr && branch.lchild->rchild != nullptr) {
        std::cout << "Begin optimization: rsmt" << std::endl;
        if(branch.parent != nullptr) {
            if(branch.parent->lchild == &branch) {
                branch.parent->lchild = branch.lchild;
            } else {
                branch.parent->rchild = branch.rchild;
            }
        }
        branch.lchild->parent = branch.parent;
        branch.parent = branch.lchild;
        branch.lchild->rchild->parent = &branch;
        branch.lchild = branch.lchild->rchild;
        branch.parent->rchild = &branch;
        std::cout << "Begin optimization: rsmt" << std::endl;
    }
}

template<typename K, typename T>
void
left_big_turn(Tree_node<K, T>*& branch)
{
}

template<typename K, typename T>
void
right_big_turn(Tree_node<K, T>*& branch)
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
check_tree(Tree_node<K, T>*& branch)
{
    if(wants_lsmt(branch)) {
        left_small_turn(*branch);
    }
    if(wants_rsmt(branch)) {
        right_small_turn(*branch);
    }
    if(wants_lbt(branch)) {
        left_big_turn(branch);
    }
    if(wants_rbt(branch)) {
        right_big_turn(branch);
    }
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
            check_tree(branch);
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
    ++birch.t_size;
    std::cout << "Added " << data << " with key " << key << std::endl;
}

template<typename K, typename T>
void
add(Tree<K, T>& birch, std::pair<K, T> tuple) // an overload for pairs
{
    add(birch, tuple.first, tuple.second); // simply parse the pair
}

template<typename K, typename T>
bool
is_root(Tree_node<K, T>* branch)
{
    if(branch->parent != nullptr) {
        return false;
    }
    return true;
}

template<typename K, typename T>
bool
has_lchild(Tree_node<K, T>* branch)
{
    if(branch->lchild == nullptr) {
        return false;
    }
    return true;
}
template<typename K, typename T>
bool
has_rchild(Tree_node<K, T>* branch)
{
    if(branch->rchild == nullptr) {
        return false;
    }
    return true;
}

template<typename K, typename T>
void
set_parents_child_ptr(Tree_node<K, T>* successor, Tree_node<K, T>* child)
{
    if(successor->parent->rchild == successor) {
        successor->parent->rchild = child;
    } else {
        successor->parent->lchild = child;
    }
}

template<typename K, typename T>
void
eject_successor(Tree_node<K, T>* successor)
{
    if(has_lchild(successor)) {
        successor->lchild->parent = successor->parent;
        set_parents_child_ptr(successor, successor->lchild);
    } else if(has_rchild(successor)) {
        successor->rchild->parent = successor->parent;
        set_parents_child_ptr(successor, successor->rchild);
    } else {
        if(successor->parent->rchild == successor) {
            successor->parent->rchild = nullptr;
        } else {
            successor->parent->lchild = nullptr;
        }
    }
}

template<typename K, typename T>
void
update_successor(Tree_node<K, T>* successor, Tree_node<K, T>* branch)
{
    successor->parent = branch->parent;
    successor->lchild = branch->lchild;
    successor->rchild = branch->rchild;
}

template<typename K, typename T>
void
inject_successor(Tree_node<K, T>* successor, Tree_node<K, T>* branch)
{
    if(exists(successor->parent)) {
        if(successor->parent->rchild == branch) {
            successor->parent->rchild = successor;
        } else {
            successor->parent->lchild = successor;
        }
    }
    if(exists(successor->lchild))
        successor->lchild->parent = successor;

    if(exists(successor->rchild))
        successor->rchild->parent = successor;
}

template<typename K, typename T>
void
coronate(Tree_node<K, T>* successor, Tree_node<K, T>* branch)
{
    if(successor != nullptr) {
        eject_successor(successor);
        update_successor(successor, branch);
        inject_successor(successor, branch);
    } else {
        if(exists(branch->parent)) {
            if(branch->parent->rchild == branch) {
                branch->parent->rchild = successor;
            } else {
                branch->parent->lchild = successor;
            }
        }
    }
    delete branch;
}

template<typename K, typename T>
Tree_node<K, T>*
find_succssessor(Tree_node<K, T>* branch)
{
    Tree_node<K, T>* successor;
    if(has_lchild(branch)) { // looking for left child
        successor = branch->lchild;
        if(successor != nullptr) {
            while(successor->rchild != nullptr) {
                successor = successor->rchild;
            }
        }
    } else {
        successor = branch->rchild;
        if(successor != nullptr) {
            while(successor->lchild != nullptr) {
                successor = successor->lchild;
            }
        }
    }
    return successor;
}

template<typename K, typename T>
void
cut(Tree<K, T>& birch,
    Tree_node<K, T>* branch,
    T& key,
    bool check_enable = true)
{
    if(branch->key != key) {
        if(branch->key < key) {
            if(branch->rchild != nullptr) {
                cut(birch, branch->rchild, key, check_enable);
            } else {
                check_enable = false;
                // if not found we do not need to check the tree
            }
        } else {
            if(branch->lchild != nullptr) {
                cut(birch, branch->lchild, key, check_enable);
            } else {
                check_enable = false;
            }
        }

    } else {
        check_enable = false;
        Tree_node<K, T>* successor = find_succssessor(branch);
        coronate(successor, branch); // replacing branch with its successor
        if(exists(successor)) {
            if(is_root(successor)) {
                birch.rootptr = successor;
            }
        }
        --birch.t_size;
    }
    if(check_enable) {
        check_tree(branch);
    }
}

template<typename K, typename T>
void
remove(Tree<K, T>& birch, K key, bool check_enable = true)
{
    if(birch.rootptr != nullptr) {
        cut(birch, birch.rootptr, key, check_enable);
    }
    std::cout << birch.t_size << std::endl;
    if(birch.t_size == 0) {
        birch.rootptr = nullptr;
    }
}

template<typename K, typename T>
void
recuprint(Tree_node<K, T>*& branch, std::string& recuheader)
{
    if(recuheader.size() < 35) {
        std::cout << recuheader << branch->data << std::endl;
        recuheader.push_back('|');
        if(branch->lchild != nullptr) {
            std::cout << "going left" << std::endl;

            recuprint(branch->lchild, recuheader);
        }
        if(branch->rchild != nullptr) {
            std::cout << "going right" << std::endl;

            recuprint(branch->rchild, recuheader);
        }
        recuheader.pop_back();
    } else {
        std::cout << "fck u" << std::endl;
    }
}

template<typename K, typename T>
void
print(Tree<K, T>& birch)
{
    std::string recustr;
    std::cout << "AVeryLittle Tree:" << std::endl;
    if(birch.rootptr != nullptr) {
        recuprint(birch.rootptr, recustr);
    } else {
        std::cout << "NULL" << std::endl;
    }
}

template<typename K, typename T>
void
destructor()
{
}

int
main()
{
    std::srand(0);
    Tree<int, int> tester;
    constructor(tester);
    for(int i = 15; i < 20; ++i) {
        add(tester, i, i);
    }
    for(int i = 0; i < 5; ++i) {
        add(tester, i, i);
    }
    for(int i = 5; i < 15; ++i) {
        add(tester, i, i);
    }
    print(tester);

    for(int i = 10; i < 15; ++i) {
        remove(tester, i);
    }
    print(tester);
    return 0;
}
