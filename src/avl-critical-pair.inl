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
  * \file avl-critical-pair.inl
  * \brief Definition of AvlCriticalPair methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_AVL_CRITICAL_PAIR_INL
#define F4_AVL_CRITICAL_PAIR_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    /* Constructor */
    
    template<typename Element>
    NodeAvlCriticalPair<Element>::NodeAvlCriticalPair(): _bf(0), _parent(0), _left(0), _right(0)
    {
    } 
    
    template<typename Element>
    AvlCriticalPair<Element>::AvlCriticalPair(): _array(1000, 100, 1), _it(_array.getBegin()), _root(0), _size(0)
    {
    }
    
    
    /* Miscellaneous */
    
    template<typename Element>
    void 
    printNode(NodeAvlCriticalPair<Element>* p, int indent)
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
            
            cout << p->_cp << "\n ";
            
            if(p->_left) 
            {
                cout << setw(indent) << ' ' << " \\\n";
                printNode(p->_left, indent+4);
            }
        }
    }
    
    template<typename Element>
    void 
    AvlCriticalPair<Element>::printAvlCriticalPair(ostream & stream) const
    {
        printNode(_root);
    }
    
    template<typename Element>
    void 
    AvlCriticalPair<Element>::reset()
    {
        _it=_array.getBegin();
        _root=0;
        _array.reset();
        _size=0;
    }
    
    template<typename Element>
    size_t 
    AvlCriticalPair<Element>::size() const
    {
        return _size;
    }
    
    template<typename Element>
    bool 
    AvlCriticalPair<Element>::isEmpty() const
    {
        return _root==0;
    }
    
    
    /* Insertion */
    
    template<typename Element>
    int
    AvlCriticalPair<Element>::insert(CriticalPair<Element> cp)
    {
        NodeAvlCriticalPair<Element> *tmpnode, *tmpnode2, *tmpnode3, *tmpnode4, *tmpnode5, *tmp_parent, *node;
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
            if( tmpnode->_cp < cp)
            { 
                cmp=1;
                tmpnode = tmpnode->_right;
            }
            else if (tmpnode->_cp > cp)
            {
                cmp=-1;
                tmpnode = tmpnode->_left;
            }
            else
            {
                /* Critical pair found */
                return 1;
            }
        }

        /* Critical pair is not here, we create it */
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
    void testNode(NodeAvlCriticalPair<Element> * node)
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
    AvlCriticalPair<Element>::testAVL()
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
    
    /* Deletion */
    
    template<typename Element>
    NodeAvlCriticalPair<Element> *
    AvlCriticalPair<Element>::erase(NodeAvlCriticalPair<Element> * node)
    {
        if(!node)
        {
            cout << "AvlCriticalPair::erase call with null ! " << endl << endl;
            return node;
        }
        
        int adjust, adjust_parent;
        CriticalPair<Element> ptmp;
        NodeAvlCriticalPair<Element> *tmpnode, *tmpnode2, *tmpnode3, *tmpnode4, *tmpnode5, *tmpParent, *res;

        /* Effacement de node (remonte du successeur immediat et effacement) */
        tmpnode = node->_right;
        if (tmpnode != 0)
        {
            while (tmpnode->_left != 0)
            {
                tmpnode = tmpnode->_left;
            }
            ptmp = node->_cp;
            node->_cp = tmpnode->_cp;
            tmpnode->_cp = ptmp;
            /* Keep trace of the next smallest node after the deleted node */
            res=node;
        }
        else
        {
            tmpnode = node;
            /* Keep trace of the next smallest node after the deleted node */
            res=node->_parent;
        }

        node = tmpnode;
        tmpnode = node->_parent;
        
        if (tmpnode == 0)
        {
            _root = node->_left;
            if (_root != 0)
            {
                _root->_parent = 0;
            }
            adjust = 0;
        }
        else
        {
            if (node->_left == 0)
            {
                tmpnode2 = node->_right;
                if (tmpnode->_left == node)
                {
                    tmpnode->_left = tmpnode2;
                    adjust = 1;
                }
                else
                {
                    tmpnode->_right = tmpnode2;
                    adjust = -1;
                }
            }
            else
            {
                tmpnode2 = node->_left;
                if (tmpnode->_left == node)
                {
                    tmpnode->_left = tmpnode2;
                    adjust = 1;
                }
                else
                {
                    tmpnode->_right = tmpnode2;
                    adjust = -1;
                }
            }
            if (tmpnode2 != 0)
            {
                tmpnode2->_parent = tmpnode;
            }
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
                        tmpParent = tmpnode2->_parent = tmpnode->_parent;
                        if (tmpParent != 0)
                        {
                            if (tmpParent->_left == tmpnode)
                            {
                                tmpParent->_left = tmpnode2;
                            }
                            else
                            {
                                tmpParent->_right = tmpnode2;
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
                        adjust_parent = tmpnode2->_bf;
                        tmpnode2->_bf -= adjust;
                        tmpnode = tmpnode2;
                    }
                    else
                    {
                        tmpnode3 = tmpnode2->_left;
                        tmpnode4 = tmpnode->_right = tmpnode3->_left;
                        tmpnode5 = tmpnode2->_left = tmpnode3->_right;
                        tmpnode3->_left = tmpnode;
                        tmpnode3->_right = tmpnode2;
                        tmpParent = tmpnode3->_parent = tmpnode->_parent;
                        if (tmpParent != 0)
                        {
                            if (tmpParent->_left == tmpnode)
                            {
                                tmpParent->_left = tmpnode3;
                            }
                            else
                            {
                                tmpParent->_right = tmpnode3;
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
                        adjust_parent = 1;
                        tmpnode = tmpnode3;
                    }
                }
                else
                {
                    tmpnode2 = tmpnode->_left;
                    if (tmpnode2->_bf != -adjust)
                    {
                        tmpnode3 = tmpnode->_left = tmpnode2->_right;
                        tmpnode2->_right = tmpnode;
                        tmpParent = tmpnode2->_parent = tmpnode->_parent;
                        if (tmpParent != 0)
                        {
                            if (tmpParent->_left == tmpnode)
                            {
                                tmpParent->_left = tmpnode2;
                            }
                            else
                            {
                                tmpParent->_right = tmpnode2;
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
                        adjust_parent = tmpnode2->_bf;
                        tmpnode2->_bf -= adjust;
                        tmpnode = tmpnode2;
                    }
                    else
                    {
                        tmpnode3 = tmpnode2->_right;
                        tmpnode4 = tmpnode->_left = tmpnode3->_right;
                        tmpnode5 = tmpnode2->_right = tmpnode3->_left;
                        tmpnode3->_right = tmpnode;
                        tmpnode3->_left = tmpnode2;
                        tmpParent = tmpnode3->_parent = tmpnode->_parent;
                        if (tmpParent != 0)
                        {
                            if (tmpParent->_left == tmpnode)
                            {
                                tmpParent->_left = tmpnode3;
                            }
                            else
                            {
                                tmpParent->_right = tmpnode3;
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
                        adjust_parent = 1;
                        tmpnode = tmpnode3;
                    }
                }
                adjust = 0;
            }
            else
            {
                tmpnode->_bf += adjust;
                if (tmpnode->_bf == 0)
                {
                    adjust_parent = 1;
                }
                else
                {
                    adjust_parent = 0;
                }
            }
            if (adjust_parent)
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
                        adjust = 1;
                    }
                    else
                    {
                        adjust = -1;
                    }
                    tmpnode = tmpnode2;
                }
            }
            else
            {
                adjust = 0;
            }
        }
        
        _size--;
        return res;
    }
    
    
    /* Search */
    
    template<typename Element>
    NodeAvlCriticalPair<Element> *
    AvlCriticalPair<Element>::findBiggest ()
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlCriticalPair<Element> * tmp = _root;
        while (tmp->_right != 0)
        {
            tmp = tmp->_right;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlCriticalPair<Element> const *
    AvlCriticalPair<Element>::findBiggest () const
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlCriticalPair<Element> * tmp = _root;
        while (tmp->_right != 0)
        {
            tmp = tmp->_right;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlCriticalPair<Element> *
    AvlCriticalPair<Element>::findNextBiggest(NodeAvlCriticalPair<Element> * node)
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
    NodeAvlCriticalPair<Element> const *
    AvlCriticalPair<Element>::findNextBiggest(NodeAvlCriticalPair<Element> const * node) const
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
    NodeAvlCriticalPair<Element> *
    AvlCriticalPair<Element>::findSmallest ()
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlCriticalPair<Element> * tmp = _root;
        while (tmp->_left != 0)
        {
            tmp = tmp->_left;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlCriticalPair<Element> const *
    AvlCriticalPair<Element>::findSmallest () const
    {
        if (_root == 0)       
        {
            /* Empty tree */
            return 0;
        }
        NodeAvlCriticalPair<Element> * tmp = _root;
        while (tmp->_left != 0)
        {
            tmp = tmp->_left;
        }
        return tmp;
    }
    
    template<typename Element>
    NodeAvlCriticalPair<Element> *
    AvlCriticalPair<Element>::findNextSmallest(NodeAvlCriticalPair<Element> * node)
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
    NodeAvlCriticalPair<Element> const *
    AvlCriticalPair<Element>::findNextSmallest(NodeAvlCriticalPair<Element> const * node) const
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
    std::ostream & operator<<(std::ostream & stream, AvlCriticalPair<Element> const & avlCriticalPair)
    {
        avlCriticalPair.printAvlCriticalPair(stream);
        return stream;
    }
    
}

#endif // F4_AVL_CRITICAL_PAIR_INL
