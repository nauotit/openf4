/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of openf4.
 * 
 * openf4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * openf4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with openf4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file avl-monomial.inl
  * \brief Definition of AvlMonomial methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef OPENF4_AVL_MONOMIAL_INL
#define OPENF4_AVL_MONOMIAL_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Constructor */
    
    NodeAvlMonomial::NodeAvlMonomial():_numMonomial(-1), _lt(false), _bf(0), _parent(0), _left(0), _right(0)
    {
    } 
    
    AvlMonomial::AvlMonomial(): _array(1000, 1000, 1), _it(_array.getBegin()), _root(0), _size(0)
    {
    }
    
    
    /* Miscellaneous */
    
    void 
    printNode(NodeAvlMonomial* p, int indent)
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
            cout << p->_numMonomial << ", lt=" << p->_lt << "\n ";
            if(p->_left) 
            {
                cout << setw(indent) << ' ' << " \\\n";
                printNode(p->_left, indent+4);
            }
        }
    }
    
    void 
    AvlMonomial::printAvlMonomial(ostream & stream) const
    {
        printNode(_root);
    }
    
    void 
    AvlMonomial::reset()
    {
        _it=_array.getBegin();
        _root=0;
        _array.reset();
        _size=0;
    }
    
    size_t 
    AvlMonomial::size() const
    {
        return _size;
    }
    
    
    /* Insertion */
    
    int
    AvlMonomial::insert(int numMon, bool lt)
    {
        NodeAvlMonomial *tmpnode, *tmpnode2, *tmpnode3, *tmpnode4, *tmpnode5, *tmp_parent, *node;
        int adjust, cmp;

        if (_root == 0)
        {
            node = _it;
            _it=_array.getNext(_it);
            node->_numMonomial = numMon;
            node->_lt = lt;

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
            if ((tmpnode->_numMonomial) < numMon)
            {
                cmp = 1;
                tmpnode = tmpnode->_right;
            }
            else if ((tmpnode->_numMonomial) > numMon)
            {
                cmp = -1;
                tmpnode = tmpnode->_left;
            }
            else
            {
                /* Monomial found */
                if (lt == true && tmpnode->_lt == false)
                {
                    tmpnode->_lt = true;
                    return 2;
                }
                else
                {
                    return 1;
                }
            }
        }

        /* Monomial is not here, we create it */
        node = _it;
        _it=_array.getNext(_it);
        node->_numMonomial = numMon;
        node->_lt = lt;

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
    
    
    /* Search */
    
    NodeAvlMonomial *
    AvlMonomial::findBiggest ()
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlMonomial * tmp = _root;
        while (tmp->_right != 0)
        {
            tmp = tmp->_right;
        }
        return tmp;
    }
    
    NodeAvlMonomial const *
    AvlMonomial::findBiggest () const
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlMonomial * tmp = _root;
        while (tmp->_right != 0)
        {
            tmp = tmp->_right;
        }
        return tmp;
    }
    

    NodeAvlMonomial *
    AvlMonomial::findNextBiggest(NodeAvlMonomial * node)
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
    
    NodeAvlMonomial const *
    AvlMonomial::findNextBiggest(NodeAvlMonomial const * node) const
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
    
    
    /* Operator overload */
    
    std::ostream & operator<<(std::ostream & stream, AvlMonomial const & avlMonomial)
    {
        avlMonomial.printAvlMonomial(stream);
        return stream;
    }
    
}

#endif // OPENF4_AVL_MONOMIAL_INL
