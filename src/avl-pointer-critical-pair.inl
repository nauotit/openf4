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
  * \file avl-pointer-critical-pair.inl
  * \brief Definition of AvlPointerCriticalPair methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_AVL_POINTER_CRITICAL_PAIR_INL
#define F4_AVL_POINTER_CRITICAL_PAIR_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    /* Constructor */
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element>::NodeAvlPointerCriticalPair(): _bf(0), _parent(0), _left(0), _right(0)
    {
    } 
    
    template<typename Element>
    AvlPointerCriticalPair<Element>::AvlPointerCriticalPair(): _array(1000, 100, 1), _it(_array.getBegin()), _root(0), _size(0)
    {
    }
    
    
    /* Miscellaneous */
    
    template<typename Element>
    void 
    printNode(NodeAvlPointerCriticalPair<Element>* p, int indent)
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
                cout << " /\n" << setw(indent) << ' ';
            }
            
            cout << *(p->_cp) << "\n ";
            
            if(p->_left) 
            {
                cout << setw(indent) << ' ' << " \\\n";
                printNode(p->_left, indent+4);
            }
        }
    }
    
    template<typename Element>
    void 
    AvlPointerCriticalPair<Element>::printAvlCriticalPair(ostream & stream) const
    {
        printNode(_root);
    }
    
    template<typename Element>
    void 
    AvlPointerCriticalPair<Element>::reset()
    {
        _it=_array.getBegin();
        _root=0;
        _array.reset();
        _size=0;
    }
    
    template<typename Element>
    size_t 
    AvlPointerCriticalPair<Element>::size() const
    {
        return _size;
    }
    
    template<typename Element>
    bool 
    AvlPointerCriticalPair<Element>::isEmpty() const
    {
        return _root==0;
    }
    
    
    /* Insertion */
    
    template<typename Element>
    int
    AvlPointerCriticalPair<Element>::insert(CriticalPair<Element> * cp)
    {
        NodeAvlPointerCriticalPair<Element> *tmpnode, *tmpnode2, *tmpnode3, *tmpnode4, *tmpnode5, *tmp_parent, *node;
        int adjust, cmp;

        if (_root == 0)
        {
            node = _it;
            _it=_array.getNext(_it);
            node->_cp = cp;

            _root = node;
            
            _root->_left = 0;
            _root->_right = 0;
            _root->_parent = 0;
            _root->_bf = 0;
            
            _size++;
            return 0;
        }

        tmpnode = _root;
        while (tmpnode != 0)
        {
            tmpnode2 = tmpnode;
            if( *(tmpnode->_cp) < *cp)
            { 
                cmp=1;
                tmpnode = tmpnode->_right;
            }
            else if (*(tmpnode->_cp) > *cp)
            {
                cmp=-1;
                tmpnode = tmpnode->_left;
            }
            else
            {
                /* Polynomial found */
                return 1;
            }
        }

        /* Polynomial is not here, we create it */
        node = _it;
        _it=_array.getNext(_it);
        node->_cp=cp;

        /* Insertion */
        tmpnode = tmpnode2;
        if (cmp < 0)
        {
            tmpnode->_left = node;
            node->_parent = tmpnode;
            node->_bf = 0;
            node->_left = node->_right = 0;
            adjust = -1;
        }
        else
        {
            tmpnode->_right = node;
            node->_parent = tmpnode;
            node->_bf = 0;
            node->_left = node->_right = 0;
            adjust = 1;
        }

        while (adjust != 0)
        {
            if (tmpnode->_bf == adjust)
            {
                if (adjust == 1)
                {
                    tmpnode2 = tmpnode->_right;
                    if (tmpnode2->_bf != -adjust)
                    {
                        tmpnode3 = tmpnode->_right = tmpnode2->_left;
                        tmpnode2->_left = tmpnode;
                        tmp_parent = tmpnode2->_parent = tmpnode->_parent;
                        if (tmp_parent != 0)
                        {
                            if (tmp_parent->_left == tmpnode)
                            {
                                tmp_parent->_left = tmpnode2;
                            }
                            else
                            {
                                tmp_parent->_right = tmpnode2;
                            }
                        }
                        else
                        {
                            _root = tmpnode2;
                        }
                        tmpnode->_parent = tmpnode2;
                        if (tmpnode3 != 0)
                        {
                            tmpnode3->_parent = tmpnode;
                        }
                        tmpnode->_bf = adjust - tmpnode2->_bf;
                        tmpnode2->_bf -= adjust;
                    }
                    else
                    {
                        tmpnode3 = tmpnode2->_left;
                        tmpnode4 = tmpnode->_right = tmpnode3->_left;
                        tmpnode5 = tmpnode2->_left = tmpnode3->_right;
                        tmpnode3->_left = tmpnode;
                        tmpnode3->_right = tmpnode2;
                        tmp_parent = tmpnode3->_parent = tmpnode->_parent;
                        if (tmp_parent != 0)
                        {
                            if (tmp_parent->_left == tmpnode)
                            {
                                tmp_parent->_left = tmpnode3;
                            }
                            else
                            {
                                tmp_parent->_right = tmpnode3;
                            }
                        }
                        else
                        {
                            _root = tmpnode3;
                        }
                        tmpnode->_parent = tmpnode3;
                        tmpnode2->_parent = tmpnode3;
                        if (tmpnode4 != 0)
                        {
                            tmpnode4->_parent = tmpnode;
                        }
                        if (tmpnode5 != 0)
                        {
                            tmpnode5->_parent = tmpnode2;
                        }
                        if (tmpnode3->_bf <= 0)
                        {
                            tmpnode->_bf = 0;
                        }
                        else
                        {
                            tmpnode->_bf = -1;
                        }
                        if (tmpnode3->_bf >= 0)
                        {
                            tmpnode2->_bf = 0;
                        }
                        else
                        {
                            tmpnode2->_bf = 1;
                        }
                        tmpnode3->_bf = 0;
                    }
                }
                else
                {
                    node = tmpnode->_right;
                    tmpnode2 = tmpnode->_left;
                    if (tmpnode2->_bf != -adjust)
                    {
                        tmpnode3 = tmpnode->_left = tmpnode2->_right;
                        tmpnode2->_right = tmpnode;
                        tmp_parent = tmpnode2->_parent = tmpnode->_parent;
                        if (tmp_parent != 0)
                        {
                            if (tmp_parent->_left == tmpnode)
                            {
                                tmp_parent->_left = tmpnode2;
                            }
                            else
                            {
                                tmp_parent->_right = tmpnode2;
                            }
                        }
                        else
                        {
                            _root = tmpnode2;
                        }
                        tmpnode->_parent = tmpnode2;
                        if (tmpnode3 != 0)
                        {
                            tmpnode3->_parent = tmpnode;
                        }
                        tmpnode->_bf = adjust - tmpnode2->_bf;
                        tmpnode2->_bf -= adjust;
                    }
                    else
                    {
                        tmpnode3 = tmpnode2->_right;
                        tmpnode4 = tmpnode->_left = tmpnode3->_right;
                        tmpnode5 = tmpnode2->_right = tmpnode3->_left;
                        tmpnode3->_left = tmpnode2;
                        tmpnode3->_right = tmpnode;
                        tmp_parent = tmpnode3->_parent = tmpnode->_parent;
                        if (tmp_parent != 0)
                        {
                            if (tmp_parent->_left == tmpnode)
                            {
                                tmp_parent->_left = tmpnode3;
                            }
                            else
                            {
                                tmp_parent->_right = tmpnode3;
                            }
                        }
                        else
                        {
                            _root = tmpnode3;
                        }
                        tmpnode->_parent = tmpnode3;
                        tmpnode2->_parent = tmpnode3;
                        if (tmpnode4 != 0)
                        {
                            tmpnode4->_parent = tmpnode;
                        }
                        if (tmpnode5 != 0)
                        {
                            tmpnode5->_parent = tmpnode2;
                        }
                        if (tmpnode3->_bf >= 0)
                        {
                            tmpnode->_bf = 0;
                        }
                        else
                        {
                            tmpnode->_bf = 1;
                        }
                        if (tmpnode3->_bf <= 0)
                        {
                            tmpnode2->_bf = 0;
                        }
                        else
                        {
                            tmpnode2->_bf = -1;
                        }
                        tmpnode3->_bf = 0;
                    }
                }
                adjust = 0;
            }
            else
            {
                tmpnode->_bf += adjust;
                if (tmpnode->_bf != 0)
                {
                    tmpnode2 = tmpnode->_parent;
                    if (tmpnode2 == 0)
                    {
                        adjust = 0;
                    }
                    else
                    {
                        if (tmpnode == tmpnode2->_left)
                        {
                            adjust = -1;
                        }
                        else
                        {
                            adjust = 1;
                        }
                        tmpnode = tmpnode2;
                    }
                }
                else
                {
                    adjust = 0;
                }
            }
        }
        
        _size++;
        return 0;
    }
    
    
    /* Check */
    
    template<typename Element>
    void testNode(NodeAvlPointerCriticalPair<Element> * node)
    {
        if(node)
        {
            testNode(node->_left);
            testNode(node->_right);
            
            if(node->_parent)
            {
                if((node->_parent->_left != node) && (node->_parent->_right != node))
                {
                    cout << endl << "!!!!!!!!!!!!!!!!!!!!    AVL INCONSISTENCY   !!!!!!!!!!!!!!!!!!" << endl;
                }
                else
                {
                    cout << " testNode: Node consistent !!!" << endl;
                }
            }
        }
    }
    
    template<typename Element>
    void 
    AvlPointerCriticalPair<Element>::testAVL()
    {
        if(_root)
        {
            cout << " Test the AVL ...." << endl;
            testNode(_root);
        }
        else
        {
            cout << "_root is nil" << endl;
        }
    }
    
    
    /* Search */
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> *
    AvlPointerCriticalPair<Element>::findBiggest ()
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlPointerCriticalPair<Element> * tmp = _root;
        while (tmp->_right != 0)
        {
            tmp = tmp->_right;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> const *
    AvlPointerCriticalPair<Element>::findBiggest () const
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlPointerCriticalPair<Element> * tmp = _root;
        while (tmp->_right != 0)
        {
            tmp = tmp->_right;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> *
    AvlPointerCriticalPair<Element>::findNextBiggest(NodeAvlPointerCriticalPair<Element> * node)
    {
        if (node == 0)
        {
            return 0;
        }
        if (node->_left != 0)
        {
            node = node->_left;
            while (node->_right != 0)
            {
                node = node->_right;
            }
            return node;
        }
        else
        {
            /* No left child */
            while (node->_parent != 0)
            {
                if (node->_parent->_right == node)
                {
                    return node->_parent;
                }
                node = node->_parent;
            }
        }
        return 0;
    }
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> const *
    AvlPointerCriticalPair<Element>::findNextBiggest(NodeAvlPointerCriticalPair<Element> const * node) const
    {
        if (node == 0)
        {
            return 0;
        }
        if (node->_left != 0)
        {
            node = node->_left;
            while (node->_right != 0)
            {
                node = node->_right;
            }
            return node;
        }
        else
        {
            /* No left child */
            while (node->_parent != 0)
            {
                if (node->_parent->_right == node)
                {
                    return node->_parent;
                }
                node = node->_parent;
            }
        }
        return 0;
    }
    
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> *
    AvlPointerCriticalPair<Element>::findSmallest ()
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlPointerCriticalPair<Element> * tmp = _root;
        while (tmp->_left != 0)
        {
            tmp = tmp->_left;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> const *
    AvlPointerCriticalPair<Element>::findSmallest () const
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlPointerCriticalPair<Element> * tmp = _root;
        while (tmp->_left != 0)
        {
            tmp = tmp->_left;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> *
    AvlPointerCriticalPair<Element>::findNextSmallest(NodeAvlPointerCriticalPair<Element> * node)
    {
        if (node == 0)
        {
            return 0;
        }
        if (node->_right != 0)
        {
            node = node->_right;
            while (node->_left != 0)
            {
                node = node->_left;
            }
            return node;
        }
        else
        {
            /* No right child */
            while (node->_parent != 0)
            {
                if (node->_parent->_left == node)
                {
                    return node->_parent;
                }
                node = node->_parent;
            }
        }
        return 0;
    }
    
    template<typename Element>
    NodeAvlPointerCriticalPair<Element> const *
    AvlPointerCriticalPair<Element>::findNextSmallest(NodeAvlPointerCriticalPair<Element> const * node) const
    {
        if (node == 0)
        {
            return 0;
        }
        if (node->_right != 0)
        {
            node = node->_right;
            while (node->_left != 0)
            {
                node = node->_left;
            }
            return node;
        }
        else
        {
            /* No right child */
            while (node->_parent != 0)
            {
                if (node->_parent->_left == node)
                {
                    return node->_parent;
                }
                node = node->_parent;
            }
        }
        return 0;
    }
    
    
    /* Operator overload */
    
    template<typename Element>
    std::ostream & operator<<(std::ostream & stream, AvlPointerCriticalPair<Element> const & avlCriticalPair)
    {
        avlCriticalPair.printAvlCriticalPair(stream);
        return stream;
    }
    
}

#endif // F4_AVL_POINTER_CRITICAL_PAIR_INL
