// Created by David Zashkolny on 05.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>

// TODO tasks

struct node{
    int key_value;
    node *p_left;
    node *p_right;
};


node *insert(node* p_tree, int key);

node *search(node* p_tree, int key);

node *remove(node* p_tree, int key);

void destroyTree(node* p_tree);


int main(){

}


node *insert(node* p_tree, int key){
    if (p_tree == NULL){
        node* p_new_tree = new node;
        p_new_tree->p_left = NULL;
        p_new_tree->p_right = NULL;
        p_new_tree->key_value = key;
        return p_new_tree;
    }
    if (key < p_tree->key_value) {
        p_tree->p_left = insert(p_tree->p_left, key);
    } else {
        p_tree->p_right = insert(p_tree->p_right, key);
    }
    return p_tree;
}


node *search(node* p_tree, int key){
    if (p_tree == NULL){
        return NULL;
    }
    if (key == p_tree->key_value){
        return p_tree;
    } else if (key < p_tree->key_value){
        return search(p_tree->p_left, key);
    } else {
        return search(p_tree->p_right, key);
    }
}


void destroyTree(node* p_tree){
    if (p_tree != NULL){
        destroyTree(p_tree->p_right);
        destroyTree(p_tree->p_left);
        delete p_tree;
    }
}



node *find_max(node* p_tree){
    if (p_tree == NULL){
        return NULL;
    } else if (p_tree->p_right == NULL){
        return p_tree;
    } else {
        return find_max(p_tree->p_right);
    }
}


node *remove_max_node(node* p_tree, node* p_max_node){
    if (p_tree == NULL){
        return NULL;
    }
    if (p_tree == p_max_node){
        return p_max_node->p_left;
    }

    p_tree->p_right = remove_max_node(p_tree->p_right, p_max_node);
    return p_tree;
}


node *remove(node* p_tree, int key){
    if (p_tree == NULL){
        return NULL;
    } else if (p_tree->key_value == key){
        if (p_tree->p_left == NULL){
            node* right_subtree = p_tree->p_right;
            delete p_tree;
            return right_subtree;
        } else if (p_tree->p_right == NULL){
            node* left_subtree = p_tree->p_left;
            delete p_tree;
            return left_subtree;
        }
        node *p_max_node = find_max(p_tree->p_left);
        p_max_node->p_left = remove_max_node(p_tree->p_left, p_max_node);
        p_max_node->p_right = p_tree->p_right;
        return p_max_node;
    } else if (key < p_tree->key_value){
        p_tree->p_left = remove(p_tree->p_left, key);
    } else {
        p_tree->p_right = remove(p_tree->p_right, key);
    }
    return p_tree;
}


