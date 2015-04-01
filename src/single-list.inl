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
    
    
    /* Class NodeList */
    
    /* Constructor */
    
    template<typename Element>
    NodeList<Element>::NodeList():_term(0,-1), _next(0)
    {
    }
    
    template<typename Element>
    NodeList<Element>::NodeList(Element coefficient, int numMonomial):_term(coefficient,numMonomial), _next(0)
    {
    }
    
    template<typename Element>
    NodeList<Element>::NodeList(Term<Element> const & term):_term(term), _next(0)
    {
    }
    
    
    /* Get / Set */
        
    template<typename Element>
    Term<Element> const & 
    NodeList<Element>::getTerm() const
    {
        return _term;
    }
        
    template<typename Element>
    int 
    NodeList<Element>::getNumMonomial() const
    {
        return _term.getNumMonomial();
    }
    
    template<typename Element>
    Element 
    NodeList<Element>::getCoefficient() const
    {
        return _term.getCoefficient();
    }
    
    template<typename Element>
    void 
    NodeList<Element>::setCoefficient(Element element)
    {
        _term.setCoefficient(element);
    }
    
    template<typename Element>
    void 
    NodeList<Element>::setNumMonomial(int numMonomial)
    {
        _term.setNumMonomial(numMonomial);
    }
    
    
    /* Class SingleList */
    
    /* Constructor */
    
    template<typename Element>
    SingleList<Element>::SingleList():_list(0)
    {
    }
    
    template<typename Element>
    SingleList<Element>::SingleList(SingleList const & toCopy)
    {
        if(toCopy._list)
        {
            NodeList<Element> * it1 = toCopy._list;
            _list = new NodeList<Element>(it1->getTerm());
            NodeList<Element> * it2 = _list;
            it1=it1->_next;
            while(it1)
            {
                it2->_next = new NodeList<Element>(it1->getTerm());
                it1=it1->_next;
                it2=it2->_next;
            }
            it2->_next=0;
        }
        else
        {
            _list=0;
        }
    }
    
    template<typename Element>
    SingleList<Element>::SingleList(SingleList && toCopy)
    {
        _list=toCopy._list;
        toCopy._list=0;
    }
    
    
    /* Destructor */
    
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
                 node=0;
             }
             delete _list;
             _list=0;
         }
    }
    
    template<typename Element>
    void
    SingleList<Element>::clear()
    {
        if(_list)
        {
             NodeList<Element> * node;
             while (_list->_next)
             {
                 node=_list;
                 _list=_list->_next;
                 delete node;
                 node=0;
             }
             delete _list;
             _list=0;
         }
    }
    
    template<typename Element>
    void
    SingleList<Element>::deleteAfter(NodeList<Element> * it)
    {
        if(it)
        {
             NodeList<Element> * node;
             if(it->_next)
             {
                 node=it->_next;
                 it->_next=0;
                 it=node->_next;
                 delete node;
                 node=0;
                 if(it)
                 {
                     while (it->_next)
                     {
                         node=it;
                         it=it->_next;
                         delete node;
                         node=0;
                     }
                     delete it;
                     it=0;
                 }
             }
         }
    }
    
    
    /* Miscellaneous */
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::getBegin() const
    {
        return _list;
    }
    
    template<typename Element>
    bool 
    SingleList<Element>::empty() const
    {
        return _list==0;
    }
    
    template<typename Element>
    Term<Element> const & 
    SingleList<Element>::front() const
    {
        assert(_list);
        return _list->_term;
    }
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::emplaceBegin(Element coefficient, int numMonomial)
    {
        NodeList<Element> * node = new NodeList<Element>(coefficient, numMonomial);
        if(_list)
        {
            node->_next=_list;
            _list = node;
        }
        else
        {
            /* The list is empty */
            _list = node;
            _list->_next=0;
        }
        return _list;
    }
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::emplaceAfter(NodeList<Element> * it, Element coefficient, int numMonomial)
    {
        NodeList<Element> * node = new NodeList<Element>(coefficient, numMonomial);
        if(it)
        {
            node->_next=it->_next;
            it->_next=node;
        }
        else
        {
            /* The list is empty */
            _list = node;
            _list->_next=0;
        }
        return node;
    }
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::emplaceOn(NodeList<Element> * it, Element coefficient, int numMonomial)
    {
        if(it)
        {
            it->setCoefficient(coefficient);
            it->setNumMonomial(numMonomial);
        }
        else
        {
            it = new NodeList<Element>(coefficient, numMonomial);
        }
        return it;
    }
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::insertBegin(Term<Element> const & term)
    {
        NodeList<Element> * node = new NodeList<Element>(term);
        if(_list)
        {
             node->_next=_list;
            _list = node;
        }
        else
        {
            /* The list is empty */
            _list = node;
            _list->_next=0;
        }
        return _list;
    }
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::insertAfter(NodeList<Element> * it, Term<Element> const & term)
    {
        NodeList<Element> * node = new NodeList<Element>(term);
        if(_list)
        {
            node->_next=it->_next;
            it->_next=node;
        }
        else
        {
            /* The list is empty */
            _list = node;
            _list->_next=0;
        }
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
    
    template<typename Element>
    NodeList<Element> * 
    SingleList<Element>::popFront()
    {
        if(_list)
        {
            NodeList<Element> * front = _list;
            _list=_list->_next;
            delete front;
        }
        return _list;
    }
    
    
    /* Operator overload */
    
    template<typename Element>
    SingleList<Element> &
    SingleList<Element>::operator=(SingleList const & toCopy)
    {
        if(toCopy._list)
        {
            NodeList<Element> * it1 = toCopy._list;
            if(_list)
            {
                _list->_term=it1->getTerm();
            }
            else
            {
                _list = new NodeList<Element>(it1->getTerm());
                _list->_next=0;
            }
            NodeList<Element> * it2 = _list;
            it1=it1->_next;
            while(it1)
            {
                if(it2->_next)
                {
                    (it2->_next)->_term = it1->getTerm();
                }
                else
                {
                    it2->_next = new NodeList<Element>(it1->getTerm());
                }
                it1=it1->_next;
                it2=it2->_next;
            }
            if(it2->_next)
            {
                /* Free the end of the current list */
                NodeList<Element> * node;
                while (it2->_next)
                {
                    node=it2->_next;
                    it2->_next=it2->_next->_next;
                    delete node;
                }
            }
        }
        else
        {
            /* Free the list */
            NodeList<Element> * node;
            while (_list->_next)
            {
                node=_list;
                _list=_list->_next;
                delete node;
            }
            delete _list;
            _list=0;
        }
        return * this;
    }
    
    template<typename Element>
    SingleList<Element> &
    SingleList<Element>::operator=(SingleList && toCopy)
    {
        if(*this != toCopy)
        {
            /* Delete the current list */
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
            _list=toCopy._list;
            toCopy._list=0;
        }
        return * this;
    }
    
    template<typename Element>
    std::ostream & operator<<(std::ostream & stream, SingleList<Element> const & list)
    {
        list.printList(stream);
        return stream;
    }
}

#endif // F4_SINGLE_LIST_INL
