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
pp(std::ostream& out, Tree_node<K, T>*& node)
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
    if(branch.rchild != nullptr
       && branch.rchild->lchild != nullptr) {
        // branch->lchild and rchild's rchild are kept in place
        std::cout << "Begin optimization: lsmt" << std::endl;
        if(branch.parent != nullptr) {
            // grand parent's stuff --ROFL--
            //// if branch is lchild of parent then
            //// change l parent's pointer
            //// else
            //// change the right one

            if(branch.parent->lchild == branch) {
                // std::cout << "Thread #" << std::this_thread::get_id();
                std::cout << " setting parent's pointer" << std::endl;
                branch.parent->lchild = branch.rchild;
            } else {
                // std::cout << "Thread #" << std::this_thread::get_id();
                std::cout << " setting parent's pointer" << std::endl;
                branch.parent->rchild = branch.rchild;
            }
        }
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BRP pointer" << std::endl;
        branch.rchild->parent = branch.parent;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BRP pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BP pointer" << std::endl;
        branch.parent = branch.rchild;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BP pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BRLP pointer" << std::endl;
        branch.rchild->lchild->parent = branch;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BRLP pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BR pointer" << std::endl;
        branch.rchild = branch.rchild->lchild;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BR pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BPL pointer" << std::endl;
        branch.parent->lchild = branch;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BPL pointer" << std::endl;
        std::cout << "End optimization: lsmt" << std::endl;
    }
}

template<typename K, typename T>
void
right_small_turn(Tree_node<K, T>& branch)
{
    if(branch.lchild != nullptr && branch.lchild->rchild != nullptr) {
        std::cout << "Begin optimization: rsmt" << std::endl;
        //std::cout << "Current status B" << std::endl;
        //pp(std::cout, branch);

        std::cout << "Current status BL" << std::endl;
        pp(std::cout, branch.lchild);

        std::cout << "Current status BLR" << std::endl;
        pp(std::cout, branch.lchild->rchild);

        if(branch.parent != nullptr) {
            std::cout << "Current status BP" << std::endl;
            pp(std::cout, branch.parent);
            if(branch.parent->lchild == &branch) {
                // std::cout << "Thread #" << std::this_thread::get_id();
                std::cout << " setting parent's pointer" << std::endl;
                branch.parent->lchild = branch.lchild;
            } else {
                // std::cout << "Thread #" << std::this_thread::get_id();
                std::cout << " setting parent's pointer" << std::endl;
                branch.parent->rchild = branch.rchild;
            }
        }

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BLP pointer" << std::endl;
        branch.lchild->parent = branch.parent;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BLP pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BP pointer" << std::endl;
        branch.parent = branch.lchild;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BP pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BLRP pointer" << std::endl;
        branch.lchild->rchild->parent = &branch;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BLRP pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BL pointer" << std::endl;
        branch.lchild = branch.lchild->rchild;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BL pointer" << std::endl;

        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " setting BPR pointer" << std::endl;
        branch.parent->rchild = &branch;
        // std::cout << "Thread #" << std::this_thread::get_id();
        std::cout << " set BPR pointer" << std::endl;

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
    std::srand(0);
    int a;
    Tree<int, int> tester;
    constructor(tester);
    for(int i = 0; i < 30; ++i) {
        a = std::rand() % 1000;
        add(tester, a, a);
    }

    /*add(tester, 5, std::string("5"));
    add(tester, 3, std::string("3"));
    add(tester, 2, std::string("2"));
    add(tester, 4, std::string("4"));
    add(tester, 1, std::string("1"));
    add(tester, 6, std::string("6"));
    add(tester, 8, std::string("8"));
    add(tester, 7, std::string("7"));
    add(tester, 234, std::string("234"));
    add(tester, 2347, std::string("2347"));*/
    print(tester);
    right_small_turn(*tester.rootptr->lchild);
    left_small_turn(*tester.rootptr->lchild);
    print(tester);
    return 0;
}
