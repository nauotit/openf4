/* 
 * Copyright (C) 2015 Antoine Joux, Vanessa Vitse and Titouan Coladon
 * 
 * This file is part of F4.
 * 
 * F4 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * F4 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with F4.  If not, see <http://www.gnu.org/licenses/>.
 */

  /**
  * \file list-pointer-critical-pair.inl
  * \brief Definition of ListPointerCriticalPair methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_LIST_POINTER_CRITICAL_PAIR_INL
#define F4_LIST_POINTER_CRITICAL_PAIR_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    /* Constructor */
    
    template<typename Element>
    NodeListPointerCriticalPair<Element>::NodeListPointerCriticalPair(): _next(0)
    {
    } 
    
    template<typename Element>
    ListPointerCriticalPair<Element>::ListPointerCriticalPair(): _array(1000, 100, 1), _it(_array.getBegin()), _root(0)
    {
    }
    
    
    /* Miscellaneous */
    
    template<typename Element>
    void 
    ListPointerCriticalPair<Element>::printListCriticalPair(ostream & stream) const
    {
        NodeListPointerCriticalPair<Element> * tmp = _root;
        while(tmp)
        {
            stream << *tmp->_cp << endl;
            tmp=tmp->_next;
        } 
    }
    
    template<typename Element>
    void 
    ListPointerCriticalPair<Element>::reset()
    {
        _it=_array.getBegin();
        _root=0;
        _array.reset();
    }
    
    template<typename Element>
    NodeListPointerCriticalPair<Element> const * 
    ListPointerCriticalPair<Element>::getRoot() const
    {
        return _root;
    }
    
    /* Insertion */
    
    template<typename Element>
    void
    ListPointerCriticalPair<Element>::insert(CriticalPair<Element> * cp)
    {
        if(_root)
        {
            _it->_cp = cp;
            _it->_next=_root;
            _root=_it;
            _it=_array.getNext(_it);
        }
        else
        {
            _root=_it;
            _root->_cp=cp;
            _root->_next=0;
            _it=_array.getNext(_it);
        }
    }
    
    
    /* Access */
    
    template<typename Element>
    NodeListPointerCriticalPair<Element> const *
    ListPointerCriticalPair<Element>::getNext(NodeListPointerCriticalPair<Element> const * node) const
    {
        if (node == 0)
        {
            return 0;
        }
        else
        {
            return node->_next;
        }
    }
    
    
    /* Operator overload */
    
    template<typename Element>
    std::ostream & operator<<(std::ostream & stream, ListPointerCriticalPair<Element> const & avlCriticalPair)
    {
        avlCriticalPair.printListCriticalPair(stream);
        return stream;
    }
    
}

#endif // F4_LIST_POINTER_CRITICAL_PAIR_INL
