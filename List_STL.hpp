//
//  mylist.h
//  Mystl
//
//  Created by WH-JS on 2019/8/14.
//  Copyright © 2019 陈. All rights reserved.
//

#ifndef mylist_h
#define mylist_h


template <class T>
struct _list_node
{
public:
    typedef _list_node * self;
    self prev;
    self next;
    T date;
    
    
private:
    
};

template <class T>
struct _list_iterator
{
public:
    typedef _list_iterator<T> iterator;
    typedef _list_iterator<T> self;
    
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ptrdiff_t difference_type;
    
    
    typedef _list_node<T>* link_type;
    typedef size_t size_type;
    
    _list_iterator(){};
    _list_iterator(link_type x) :node(x) {}
    _list_iterator(const iterator& x) : node(x.node) {}//const

    
    reference operator*()const{return (*node).date;}
    pointer operator->()const{return &(operator*());}
    
    self& operator++(){
        node = (link_type)node->next;
        return *this;
        
    };
    self operator++(int){
        auto itm = *this;
        ++*this;
        return itm;
    };
    self& operator--(){
        node = (link_type)node->prev;
        return *this;
    };
    self operator--(int){
        auto itm = *this;
        --*this;
        return itm;
    };
    bool operator==(const self& x) const { return node == x.node; }
    bool operator!=(const self& x) const { return node != x.node; }//const
    
    link_type node;
    
    
protected:
    
private:
    
};

template <class T>
class mylist
{
    
protected:
    typedef void* void_pointer;
    typedef _list_node<T> list_node;
    //typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_node* link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    
public:
    typedef _list_iterator<T>             iterator;
    typedef _list_iterator<const T> const_iterator;
    
protected:
    link_type node;

    
    
    
    
public:
    link_type creat_node();
    mylist(){node = creat_node();};
    ~mylist(){
        if (!empty())
        {
            earse(begin());
        }
    }
    
    size_type size()const{
        size_type result = 0;
        distance(begin(), end(), result);
        return result;
    }
    bool empty(){
        if ( end()==begin() )
            return true;
        return false;
    };
    iterator end(){return node;}
    iterator begin(){return node->next;}
    
    //
    //const 版本
    //
    //
    
    
    
    
    
    
    void insert(iterator, T y);
    void push_back(T y);
    void push_front(T y);
    void earse(iterator x);

};
template <class T>
typename mylist<T>::link_type mylist<T>::creat_node()
{
    auto _node = new _list_node<T>;
    _node->date = 0;
    _node->next = _node;
    _node->prev = _node;
    return _node;
}




template<class T>
inline void mylist<T>::insert(mylist<T>::iterator x, T y)
{
    link_type node = creat_node();
    node->next = x.node;
    node->prev = x.node->prev;
    x.node->prev->next = node;
    x.node->prev = node;
    node->date = y;
    
}

template<class T>
inline void mylist<T>::push_back(T y)
{
    insert(end(), y);
}

template<class T>
inline void mylist<T>::push_front(T y)
{
    insert(begin(), y);
}

template<class T>
inline void mylist<T>::earse(mylist<T>::iterator x)
{
    x.node->prev->next = x.node->next;
    x.node->next->prev = x.node->prev;
    delete x.node;
}



#endif /* mylist_h */
