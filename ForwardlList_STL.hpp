//
//  ForwardlList_STL.hpp
//  MYSTL
//
//  Created by K on 2020/9/22.
//  Copyright © 2020 K. All rights reserved.
//

#ifndef Forward_list_hpp
#define Forward_list_hpp

#include <string>
#include <iostream>
#include <stdlib.h>

template<class T>
class _List_node
{
    typedef _List_node* self;
    T data;
    self next;
    
};


template<class T>
struct forward_list_iterator
{
    
    //无const
    //前五行是必须的
    typedef std::forward_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ptrdiff_t difference_type;
    
    typedef forward_list_iterator<T> iterator;
    typedef forward_list_iterator<T> self;
    typedef _List_node<T>* link_type;
    typedef _List_node<T> list_node;
    
    
    forward_list_iterator(){};
    forward_list_iterator(list_node x):node(x){};
    
    
    reference operator*(){
        return (*node).data;//我 node->data
    }
    
     pointer operator->(){
        return &(operator*());//我&(this->operator*());
    }
    
    self& operator++(){
        
        node = (link_type)node->next;
        return *this;
        
    };
    
    //标准库返回值是喜欢使用self，本代码与iterator定义相同
    iterator operator++(int){
        iterator it = *this;
        node = (link_type)node->next;//标准库++*this
        return it;//返回应该是迭代器
    }
    
    
      bool operator==(iterator x){
          return node==x.node;
        }
    
    bool operator!=(iterator x){
          return node!=x.node;
        }
    
    link_type node;
    
};




template<class T>
struct ForwardlList_STL
{

    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef ptrdiff_t difference_type;
    
    typedef const value_type& const_reference;
    typedef const value_type* const_pointer;
    
    typedef _List_node<T> list_node;
    typedef list_node* link_type;
    typedef size_t size_type;
    
    typedef forward_list_iterator<T> iterator;
    typedef forward_list_iterator<T> self;
    
    list_node node;
//   我想存的是头指针 link_type node;
    size_t size;

    
    iterator begin(){return iterator(node.next);};
    iterator end(){return iterator(0);};
    
    
    
    ForwardlList_STL(){node=creat_node();};
    
    
    ~ForwardlList_STL();


    link_type creat_node(){
        link_type _node = new list_node;
        _node->date=0;
        _node->node=_node;
        return _node;
    }

    list_node* _reverse(link_type head)
    {
        if(head==NULL||head->pre==NULL)
            return head;
        list_node *newhead = _reverse(head->pre);
        head->pre->pre=head;
        head->pre=NULL;
        return newhead;
    };

    void reverse()
    {
        node->pre=_reverse(node->pre);
    }


    
    iterator push_front(value_type t){
        list_node* newnode = creat_node();
        newnode->data=t;
        newnode->next=node->next;
        node->next=newnode;
    };
        
};









#endif /* Forward_list_hpp */
