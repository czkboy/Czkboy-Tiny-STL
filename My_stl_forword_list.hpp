//
//  My_stl_forword_list.hpp
//  MYSTL
//
//  Created by K on 2020/12/26.
//  Copyright © 2020 K. All rights reserved.
//

#ifndef My_stl_forword_list_hpp
#define My_stl_forword_list_hpp
#include "ForwordList_NGX.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>

template <typename T>
struct remove_all_pointer
{
typedef T type;
};


template <typename T>
struct remove_all_pointer<T*>
{
typedef typename remove_all_pointer<T>::type type;
};
//---------------偏特化递归-----------------------


template<typename T>
class NgxWrapper
{
public:
    typedef typename remove_all_pointer<T>::type   wrapper_type;
    typedef wrapper_type*   wrapper_pointer;
    typedef wrapper_type&   wrapper_reference;
private:
    wrapper_pointer m_ptr = nullptr;
protected:
    NgxWrapper(wrapper_pointer p):m_ptr(p){}
    NgxWrapper(wrapper_reference x):m_ptr(&x){}
    ~NgxWrapper()=default;
public:
    wrapper_pointer get() const{
        return m_ptr;
    }
    
    operator bool () const{
        return get();
    }
    
    operator wrapper_pointer() const{
        return get();
    }
};

//--------------简单包装类-----------




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
    
    typedef FList_node list_node;
    typedef list_node* link_type;
public:
    

    
    
    forward_list_iterator(Forward_List* l):m_part(l->part),m_data(static_cast<T*>(m_part->data)){};
    forward_list_iterator()= default;
    ~forward_list_iterator()=default;
    
    
    
private:
    link_type m_part = nullptr;
    pointer m_data = nullptr;
    unsigned m_count=0;
    
public:
    reference operator*(){
        return m_data[m_count];//我 node->data
    }
    
     pointer operator->(){
        return &(operator*());//我&(this->operator*());
    }
    
    self& operator++(){
        
        if(!m_part || !m_data)
        {
            throw std::out_of_range(" we get the outofrange error");
        }
        ++m_count;
        if(m_count>=m_part->ndata)
        {
            m_count=0;
            m_part = m_part->pre;
            m_data = m_part? static_cast<T*>(m_part->data):nullptr;
        }

        return *this;
        
    };
    
    //标准库返回值是喜欢使用self，本代码与iterator定义相同
    iterator operator++(int){
        iterator it = *this;
        ++*this;
        return it;//返回应该是迭代器
    }
    
    
      bool operator==(iterator x){
          return m_part == x.m_part && m_data== x.m_data && m_count == x.m_count;
        }
    
    bool operator!=(iterator x){
          return !(*this == x);
        }
    
    
    
};


template<typename T>
class my_stl_FList final : public NgxWrapper<Forward_List>
{
    

    typedef ptrdiff_t difference_type;
    typedef T   value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef const value_type* const_pointer;
    

    typedef size_t size_type;
    
    typedef forward_list_iterator<T> iterator;
    typedef forward_list_iterator<T> self;
    
    
public:
    typedef NgxWrapper<Forward_List> super_type;
    typedef my_stl_FList this_type;
    
    
    
public:
    my_stl_FList(Forward_List* l):super_type(l){}
    my_stl_FList(Forward_List& l):super_type(&l){}
    ~my_stl_FList() = default;
public:
    reference prepare()const{
        auto tmp = Flist_push_back(get());
        //检测空指针
        return *reinterpret_cast<T*>(tmp);
    }
    void push(const_reference x) const{
        prepare() = x;
    }


    
    void pop(){
        Flist_pop_back(get());
    };
    //-------------------------------------------------
    reference back(){*Flist_getlast(get());};
    reference front(){*Flist_getpart(get());};
    
    
    
    iterator begin(){return iterator(get());};
    iterator end(){return iterator(0);};
};




#endif /* My_stl_forword_list_hpp */
