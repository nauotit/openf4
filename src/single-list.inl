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
  * \file single-list.inl
  * \brief Definition of SingleList methods.
  * \author Vanessa VITSE, Antoine JOUX, Titouan COLADON
  */

#ifndef F4_SINGLE_LIST_INL
#define F4_SINGLE_LIST_INL

using namespace std;

namespace F4
{
    /* Global variables */
    
    extern int VERBOSE;
    
    
    /* Constructor */
    
    template<typename Element>
    NodeList<Element>::NodeList():_term(0,-1)
    {
    }
    
    template<typename Element>
    NodeList<Element>::NodeList(Element coefficient, int numMonomial):_term(coefficient,numMonomial)
    {
    }
    
    template<typename Element>
    SingleList<Element>::SingleList():_list(0)
    {
    }
    
    template<typename Element>
    SingleList<Element>::~SingleList()
    {
        if(_list)
        {
             NodeList<Element> * node;
             while (_list->_next)
             {
                 node=_list;
                 _list=_list->_next;
                 delete node;
             }
             delete _list;
         }
    }
    
    
    /* Miscellaneous */
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::emplaceBegin(Element coefficient, int numMonomial)
    {
        NodeList<Element> * node = new NodeList<Element>(coefficient, numMonomial);
        if(!_list)
        {
            /* The list is empty */
            _list = node;
            _list->_next=0;
        }
        else
        {
            node->_next=_list->_next;
            _list = node;
        }
        return _list;
    }
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::emplaceAfter(NodeList<Element> * it, Element coefficient, int numMonomial)
    {
        NodeList<Element> * node = new NodeList<Element>(coefficient, numMonomial);
        node->_next=it->_next;
        it->_next=node;
        return node;
    }
    
    template<typename Element>
    void 
    SingleList<Element>::printList(ostream & stream) const
    {
        if(_list)
        {
            NodeList<Element> * node = _list;
            stream << node->_term << endl;
            while(node->_next)
            {
                node=node->_next;
                stream << node->_term << endl;
            }
        }
    }
}

#endif // F4_SINGLE_LIST_INL
