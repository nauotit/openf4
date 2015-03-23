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
  * \file critical-pair.inl
  * \brief Definition of CriticalPair methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_AVL_INL
#define F4_AVL_INL

using namespace std;

namespace F4
{
    // Class Node
    
    // Constructor
    
    template <typename keyType>
    Node<keyType>::Node()
    { 
        _key = -1; 
        _parent = 0;
        _left = 0;
        _right = 0; 
        _height = 0; 
    }
    
    template <typename keyType>
    Node<keyType>::Node(keyType k)
    { 
        _key = k; 
        _parent = 0;
        _left = 0;
        _right = 0; 
        _height = 1; 
    }
    
    template <typename keyType>
    Node<keyType>::Node(keyType k, Node<keyType> * parent)
    { 
        _key = k; 
        _parent = parent;
        _left = 0;
        _right = 0; 
        _height = 1; 
    }
    
    
    // Get / Set 
    
    template <typename keyType>
    void
    Node<keyType>::setNode(keyType k)
    { 
        _key = k; 
        _parent = 0;
        _left = 0;
        _right = 0; 
        _height = 1; 
    }
    
    template <typename keyType>
    void
    Node<keyType>::setNode(keyType k, Node<keyType> * parent)
    { 
        _key = k; 
        _parent = parent;
        _left = 0;
        _right = 0; 
        _height = 1; 
    }
    
    
    // Tools
    
    template <typename keyType>
    unsigned char 
    getHeight(Node<keyType>* p)
    {
        return p?p->_height:0;
    }
    
    template <typename keyType>
    int 
    getBalanceFactor(Node<keyType>* p)
    {
        return getHeight(p->_right)-getHeight(p->_left);
    }
    
    template <typename keyType>
    void 
    fixHeight(Node<keyType>* p)
    {
        unsigned char hl = getHeight(p->_left);
        unsigned char hr = getHeight(p->_right);
        p->_height = (hl>hr?hl:hr)+1;
    }
    
    template <typename keyType>
    void 
    printNode(Node<keyType>* p, int indent)
    {
        if(p) 
        {
            if(p->_right) 
            {
                printNode(p->_right, indent+4);
            }
            if (indent) 
            {
                cout << setw(indent) << ' ';
            }
            if (p->_right) 
            {
                cout<<" /\n" << setw(indent) << ' ';
            }
            if(p->_parent)
            {
                cout<< p->_key << ", p: " << p->_parent->_key << "\n ";
            }
            else
            {
                cout<< p->_key << "\n ";
            }
            if(p->_left) 
            {
                cout << setw(indent) << ' ' << " \\\n";
                printNode(p->_left, indent+4);
            }
        }
    }
        
    
    // Rotations

    template <typename keyType>
    Node<keyType> * 
    rotateRight(Node<keyType>* p)
    {
        Node<keyType>* q = p->_left;
        p->_left = q->_right;
        // update parent
        if(p->_left)
        {
            (p->_left)->_parent=p;
        }
        q->_right = p;
        // update parent
        q->_parent=p->_parent;
        // update parent
        p->_parent=q;
        fixHeight(p);
        fixHeight(q);
        return q;
    }

    template <typename keyType>
    Node<keyType> * 
    rotateLeft(Node<keyType>* q)
    {
        Node<keyType>* p = q->_right;
        q->_right = p->_left;
        // update parent
        if(q->_right)
        {
            (q->_right)->_parent=q;
        }
        // update parent
        p->_parent=q->_parent;
        p->_left = q;
        // update parent
        q->_parent=p;
        fixHeight(q);
        fixHeight(p);
        return p;
    }

    template <typename keyType>
    Node<keyType> * 
    balance(Node<keyType>* p) // balancing the p Node
    {
        fixHeight(p);
        if( getBalanceFactor(p)==2 )
        {
            //cout << "double rotation right left" << endl;
            if( getBalanceFactor(p->_right) < 0 )
            {
                p->_right = rotateRight(p->_right);
            }
            return rotateLeft(p);
        }
        if( getBalanceFactor(p)==-2 )
        {
            //cout << "double rotation left right" << endl;
            if( getBalanceFactor(p->_left) > 0  )
            {
                p->_left = rotateLeft(p->_left);
            }
            return rotateRight(p);
        }
        return p; // balancing is not required
    }
    
    // Insertion

    template <typename keyType>
    Node<keyType> * 
    insert(Node<keyType>* p, keyType k, Node<keyType>* parent) // insert k key in a tree with p root
    {
        if( !p ) 
        {   
            // update parent
            return new Node<keyType>(k, parent);
            //nodeArray[numNode].setNode(k,parent);
            //p=nodeArray+numNode;
            //numNode++;
        }
        if( k < p->_key )
        {
            p->_left = insert(p->_left, k, p);
        }
        if( k > p->_key )
        {
            p->_right = insert(p->_right, k, p);
        }
        return balance(p);
    }
    
    
    // Search

    template <typename keyType>
    Node<keyType> * 
    findSmallest(Node<keyType>* p) // find a Node with minimal _key in a p tree 
    {
        return p->_left?findSmallest(p->_left):p;
    }
    
    template <typename keyType>
    Node<keyType> * 
    findNextSmallest(Node<keyType>* p)
    {
        if (!p)
        {
            /* Pointer null */
            return p;
        }
        if (p->_right)
        {
            /* p has a right son */
            p = p->_right;
            while (p->_left)
            {
                p = p->_left;
            }
            return p;
        }
        else
        {
            /* p has not a right son */
            while (p->_parent)
            {
                if (p->_parent->_left == p)
                {
                    return p->_parent;
                }
                p = p->_parent;
            }
        }
        // last element
        return 0;
    }
    
    
    // Delete

    template <typename keyType>
    Node<keyType> * 
    removeSmallest(Node<keyType>* p) // deleting a Node with minimal _key from a p tree
    {
        if( p->_left==0 )
        {
            return p->_right;
        }
        p->_left = removeSmallest(p->_left);
        return balance(p);
    }

    template <typename keyType>
    Node<keyType> * 
    remove(Node<keyType>* p, keyType k) // deleting k _key from p tree
    {
        if( !p ) 
        {
            return 0;
        }
        if( k < p->_key )
        {
            p->_left = remove(p->_left,k);
        }
        else if( k > p->_key )
        {
            p->_right = remove(p->_right,k);
        }
        else //  k == p->_key 
        {
            Node<keyType>* q = p->_left;
            Node<keyType>* r = p->_right;
            delete p;
            if( !r ) 
            {
                return q;
            }
            Node<keyType>* min = findSmallest(r);
            min->_right = removeSmallest(r);
            min->_left = q;
            return balance(min);
        }
        return balance(p);
    }
    
    template <typename keyType>
    void
    clear(Node<keyType> * & p)
    {
        if(p)
        {
            if(p->_left)
            {
                clear(p->_left);
            }
            if(p->_right)
            {
                clear(p->_right);
            }
            delete p;
            p=0;
        }
    }
}

#endif // F4_AVL_INL
