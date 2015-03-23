/* 
 * Copyright (C) 2010 Antoine Joux and Vanessa Vitse 

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 */

  /**
  * \file avl.h
  * \brief Declaration of class Avl.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON 
  */

#ifndef F4_AVL_H
#define F4_AVL_H

#include <iostream>
#include <iomanip>

/** \namespace F4 
 * Group all the required tools used by the F4 algorithm.
 */
namespace F4
{
    /**
     * \class Node
     * Represent a node of an AVL tree.
     */
    template <typename keyType>
    struct Node
    {        
        public:
            
            // Constructor
            
            Node();
            Node(keyType k);
            Node(keyType k, Node * parent);
            
            // Set / Get
            
            void setNode(keyType k);
            void setNode(keyType k, Node * parent);
            
            // Attributes
        
            keyType _key;
            unsigned char _height;
            Node* _parent;
            Node* _left;
            Node* _right;
    };
    
    // Memory gestion
    
    //Node<int> * nodeArray = new Node<int>[100000];
    //int numNode=0;
    
    
    // Tools
    
    /**
     * \brief Compute the height of the AVL of root p.
     * \param p: Pointer on a node of an AVL.
     * \return Height of the AVL of root p.
     */
    template <typename keyType>
    unsigned char getHeight(Node<keyType>* p);

    /**
     * \brief Compute the balanced factor of the AVL of root p.
     * \param p: Pointer on a node of an AVL.
     * \return Balance factor of the AVL of root p.
     */
    template <typename keyType>
    int getBalanceFactor(Node<keyType>* p);

    /**
     * \brief Set the height of the AVL of root p using the height of its subtrees.
     * \param p: Pointer on a node of an AVL.
     */
    template <typename keyType>
    void fixHeight(Node<keyType>* p);
    
    /**
     * \brief Print the AVL of root p.
     * \param p: Pointer on a node of an AVL.
     */
    template <typename keyType>
    void printNode(Node<keyType>* p, int indent=0);
    
    
    // Rotations

    /**
     * \brief Apply right rotation.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the new root node.
     */
    template <typename keyType>
    Node<keyType>* rotateRight(Node<keyType>* p);

    /**
     * \brief Apply left rotation.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the new root node.
     */
    template <typename keyType>
    Node<keyType>* rotateLeft(Node<keyType>* q);

    /**
     * \brief Apply rotations in order to balance the AVL.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the new root node.
     */
    template <typename keyType>
    Node<keyType>* balance(Node<keyType>* p);
    
    
    // Insertion
    
    /**
     * \brief Insert a new node with key k in the AVL of root p. If the key already exist, do nothing.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the new root node.
     */
    template <typename keyType>
    Node<keyType>* insert(Node<keyType>* p, keyType k, Node<keyType>* parent=0);
    
    
    // Search
    
    /**
     * \brief Get the smallest node of an AVL of root p.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the smallest node.
     */
    template <typename keyType>
    Node<keyType>* findSmallest(Node<keyType>* p);
    
    /**
     * \brief Get the next smallest node after p node.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the next smallest node after p.
     */
    template <typename keyType>
    Node<keyType>* findNextSmallest(Node<keyType>* p);
    
    
    // Delete

    /**
     * \brief Tools used by remove. Beware, the node is not deleted in memory.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the new root node.
     */
    template <typename keyType>
    Node<keyType>* removeSmallest(Node<keyType>* p);
    
    /**
     * \brief Remove the node of key k from the AVL of root p.
     * \param p: Pointer on a node of an AVL.
     * \return Pointer on the new root node.
     */
    template <typename keyType>
    Node<keyType>* remove(Node<keyType>* p, keyType k);
    
    /**
     * \brief Clear the AVL of root p.
     * \param p: Pointer on a node of an AVL.
     */
    template <typename keyType>
    void clear(Node<keyType>* &p);
}

#include "../src/avl.inl"

#endif // F4_AVL_H
