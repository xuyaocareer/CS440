#ifndef MAP_H
#define MAP_H

#include <utility>
#include <initializer_list>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>

namespace cs540 {
    
#define MAX_LEVEL 32
    
    template <class Key, class Value>
    class Node {
    public:
        int node_height;
        std::pair<const Key, Value> data;
        Node* forward[MAX_LEVEL];
        Node* backward[MAX_LEVEL];
    public:
        Node(const std::pair<Key,Value> && vt, int h) : data(vt) {
            node_height = h;
            for (int i=0; i<MAX_LEVEL; i++) {
                forward[i] = nullptr;
                backward[i] = nullptr;
            }
        }
	Node(const std::pair<Key,Value> vt) : data(vt) {
            node_height = MAX_LEVEL;
            for (int i=0; i<MAX_LEVEL; i++) {
                forward[i] = nullptr;
                backward[i] = nullptr;
            }
        }
        ~Node() {
            //delete data.first;
            //delete data.second;
        }
    };
    
    template <class Key, class Value>
    class Map {
    public:
        class Iterator;
        class ConstIterator;
        class ReverseIterator;
    public:
        int list_size;
        int map_height;
        Node<Key,Value>* head;
        Node<Key,Value>* tail;
    public:
        // Constructors
        Map();
        Map(const Map &);
        Map& operator=(const Map&);
        Map(Map&&);
        Map& operator=(Map&&);
        Map(std::initializer_list<std::pair<const Key, Value>>);
        ~Map();
        // Modifiers
        Iterator insert(const std::pair<const Key, Value>&);
        Iterator insert(std::pair<const Key, Value>&&);
        void erase(Iterator);
        void remove(const Key&);
        void clear();
        // Lookup
        Iterator find(const Key&);
        ConstIterator find(const Key&) const;
        Value& at(const Key&);
        const Value& at(const Key&) const;
        Value& operator[](const Key&);
        // Size
        std::size_t size() const;
        bool empty() const;
        // Comparison Operators
        bool operator==(const Map&) const;
        bool operator!=(const Map&) const;
        // Iterators
        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        ReverseIterator rbegin();
        ReverseIterator rend();
        // Others
        int randomLevel();
        void print_map();
        // Iterator comparisons
        friend bool operator==(const Map<Key,Value>::Iterator& it1, const Map<Key,Value>::Iterator& it2) {
	    if (it1.node_ptr==nullptr && it2.node_ptr == nullptr) {
		return true;
	    }
	    else if (it1.node_ptr==nullptr || it2.node_ptr == nullptr) {
		if (it1.node_ptr==nullptr) {
			if (it2.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
		if (it2.node_ptr == nullptr) {
			if (it1.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
	    }
            return (it1.node_ptr==it2.node_ptr);
        }
        friend bool operator!=(const Map<Key,Value>::Iterator& it1, const Map<Key,Value>::Iterator& it2) {
            return !(it1.node_ptr==it2.node_ptr);
        }
        friend bool operator==(const Map<Key,Value>::ConstIterator& it1, const Map<Key,Value>::ConstIterator& it2) {
	    if (it1.node_ptr==nullptr && it2.node_ptr == nullptr) {
		return true;
	    }
	    else if (it1.node_ptr==nullptr || it2.node_ptr == nullptr) {
		if (it1.node_ptr==nullptr) {
			if (it2.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
		if (it2.node_ptr == nullptr) {
			if (it1.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
	    }
            return (it1.node_ptr==it2.node_ptr);
        }
        friend bool operator!=(const Map<Key,Value>::ConstIterator& it1, const Map<Key,Value>::ConstIterator& it2) {
            return !(it1.node_ptr==it2.node_ptr);
        }
        friend bool operator==(const Map<Key,Value>::ReverseIterator& it1, const Map<Key,Value>::ReverseIterator& it2) {
	    if (it1.node_ptr==nullptr && it2.node_ptr == nullptr) {
		return true;
	    }
	    else if (it1.node_ptr==nullptr || it2.node_ptr == nullptr) {
		if (it1.node_ptr==nullptr) {
			if (it2.node_ptr->backward[0]==nullptr)
				return true;
		else
			return false;
		}
		if (it2.node_ptr == nullptr) {
			if (it1.node_ptr->backward[0]==nullptr)
				return true;
		else
			return false;
		}
	    }
            return (it1.node_ptr==it2.node_ptr);
        }
        friend bool operator!=(const Map<Key,Value>::ReverseIterator& it1, const Map<Key,Value>::ReverseIterator& it2) {
            return !(it1.node_ptr==it2.node_ptr);
        }
        friend bool operator==(const Map<Key,Value>::ConstIterator& it1, const Map<Key,Value>::Iterator& it2) {
	    if (it1.node_ptr==nullptr && it2.node_ptr == nullptr) {
		return true;
	    }
	    else if (it1.node_ptr==nullptr || it2.node_ptr == nullptr) {
		if (it1.node_ptr==nullptr) {
			if (it2.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
		if (it2.node_ptr == nullptr) {
			if (it1.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
	    }
            return (it1.node_ptr==it2.node_ptr);
        }
        friend bool operator!=(const Map<Key,Value>::ConstIterator& it1, const Map<Key,Value>::Iterator& it2) {
            return !(it1.node_ptr==it2.node_ptr);
        }
        friend bool operator==(const Map<Key,Value>::Iterator& it1, const Map<Key,Value>::ConstIterator& it2) {
	    if (it1.node_ptr==nullptr && it2.node_ptr == nullptr) {
		return true;
	    }
	    else if (it1.node_ptr==nullptr || it2.node_ptr == nullptr) {
		if (it1.node_ptr==nullptr) {
			if (it2.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
		if (it2.node_ptr == nullptr) {
			if (it1.node_ptr->forward[0]==nullptr)
				return true;
		else
			return false;
		}
	    }
            return (it1.node_ptr==it2.node_ptr);
        }
        friend bool operator!=(const Map<Key,Value>::Iterator& it1, const Map<Key,Value>::ConstIterator& it2) {
            return !(it1.node_ptr==it2.node_ptr);
        }
    };
    
    
    // Iterator
    template <class Key, class Value>
    class Map<Key,Value>::Iterator {
    public:
        Iterator() : node_ptr(nullptr) {}
        Iterator(const Iterator&);
        Iterator& operator=(const Iterator&);
        Iterator(Iterator&&);
        Iterator& operator=(Iterator&&);
        ~Iterator();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        std::pair<const Key, Value>& operator*() const;
    public:
        Node<Key,Value>* node_ptr;
    };
    
    // Iterator member functions
    template <class Key, class Value>
    Map<Key,Value>::Iterator::Iterator(const Map<Key,Value>::Iterator& it_in) {
        node_ptr = it_in.node_ptr;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator& Map<Key,Value>::Iterator::operator=(const Map<Key,Value>::Iterator& it_in) {
        if (this==&it_in)
            return *this;
        node_ptr = it_in.node_ptr;
        //it_in.node_ptr = nullptr;
        return *this;
    }
    template <class Key, class Value>
    Map<Key,Value>::Iterator::Iterator(Map<Key,Value>::Iterator&& it_in) {
        node_ptr = it_in.node_ptr;
        it_in.node_ptr = nullptr;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator& Map<Key,Value>::Iterator::operator=(Map<Key,Value>::Iterator&& it_in) {
        if (this==&it_in)
            return *this;
        node_ptr = it_in.node_ptr;
        //it_in.node_ptr = nullptr;
        return *this;
    }
    template <class Key, class Value>
    Map<Key,Value>::Iterator::~Iterator() {
    }
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator& Map<Key,Value>::Iterator::operator++() {
        node_ptr = node_ptr->forward[0];
        return *this;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator Map<Key,Value>::Iterator::operator++(int) {
        Node<Key,Value>* temp = node_ptr;
        node_ptr = node_ptr->forward[0];
        Iterator it;
        it.node_ptr = temp;
        return it;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator& Map<Key,Value>::Iterator::operator--() {
        node_ptr = node_ptr->backward[0];
        return *this;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator Map<Key,Value>::Iterator::operator--(int) {
        Node<Key,Value>* temp = node_ptr;
        node_ptr = node_ptr->backward[0];
        Iterator it;
        it.node_ptr = temp;
        return it;
    }
    template <class Key, class Value>
    std::pair<const Key, Value>& Map<Key,Value>::Iterator::operator*() const {
        //std::pair<const Key, Value>* ptr = const_cast<std::pair<const Key, Value>*>(&node_ptr->data);
        //return *ptr;
        return node_ptr->data;
    }
    
    // ConstInterator
    template <class Key, class Value>
    class Map<Key,Value>::ConstIterator {
    public:
        ConstIterator() : node_ptr(nullptr) {}
        ConstIterator(const ConstIterator&);
        ConstIterator& operator=(const ConstIterator&);
        ConstIterator(ConstIterator&&);
        ConstIterator& operator=(ConstIterator&&);
        ~ConstIterator();
        ConstIterator(const Iterator&);
        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        const std::pair<const Key, Value>& operator*() const;
    public:
        Node<Key,Value>* node_ptr;
    };
    
    // ConstIterator member functions
    template <class Key, class Value>
    Map<Key,Value>::ConstIterator::ConstIterator(const Map<Key,Value>::ConstIterator& it_in) {
        node_ptr = it_in.node_ptr;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator& Map<Key,Value>::ConstIterator::operator=(const Map<Key,Value>::ConstIterator& it_in) {
        if (this==&it_in)
            return *this;
        node_ptr = it_in.node_ptr;
        //it_in.node_ptr = nullptr;
        return *this;
    }
    template <class Key, class Value>
    Map<Key,Value>::ConstIterator::ConstIterator(Map<Key,Value>::ConstIterator&& it_in) {
        node_ptr = it_in.node_ptr;
        it_in.node_ptr = nullptr;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator& Map<Key,Value>::ConstIterator::operator=(Map<Key,Value>::ConstIterator&& it_in) {
        if (this==&it_in)
            return *this;
        node_ptr = it_in.node_ptr;
        //it_in.node_ptr = nullptr;
        return *this;
    }
    template <class Key, class Value>
    Map<Key,Value>::ConstIterator::~ConstIterator() {
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator& Map<Key,Value>::ConstIterator::operator++() {
        node_ptr = node_ptr->forward[0];
        return *this;
    }
    template <class Key, class Value>
    Map<Key,Value>::ConstIterator::ConstIterator(const Iterator& it_in) {
        node_ptr = it_in.node_ptr;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator Map<Key,Value>::ConstIterator::operator++(int) {
        Node<Key,Value>* temp = node_ptr;
        node_ptr = node_ptr->forward[0];
        ConstIterator it;
        it.node_ptr = temp;
        return it;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator& Map<Key,Value>::ConstIterator::operator--() {
        node_ptr = node_ptr->backward[0];
        return *this;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator Map<Key,Value>::ConstIterator::operator--(int) {
        Node<Key,Value>* temp = node_ptr;
        node_ptr = node_ptr->backward[0];
        Iterator it;
        it.node_ptr = temp;
        return it;
    }
    template <class Key, class Value>
    const std::pair<const Key, Value>& Map<Key,Value>::ConstIterator::operator*() const {
        //std::pair<const Key, Value>* ptr = const_cast<std::pair<const Key, Value>*>(&node_ptr->data);
        //return *ptr;
        return node_ptr->data;
    }
    
    
    // ReverseIterator
    template <class Key, class Value>
    class Map<Key,Value>::ReverseIterator {
    public:
        ReverseIterator() : node_ptr(nullptr) {}
        ReverseIterator(const ReverseIterator&);
        ReverseIterator& operator=(const ReverseIterator&);
        ReverseIterator(ReverseIterator&&);
        ReverseIterator& operator=(ReverseIterator&&);
        ~ReverseIterator();
        ReverseIterator& operator++();
        ReverseIterator operator++(int);
        ReverseIterator& operator--();
        ReverseIterator operator--(int);
        std::pair<const Key, Value>& operator*() const;
    public:
        Node<Key,Value>* node_ptr;
    };
    
    // ReverseIterator member functions
    template <class Key, class Value>
    Map<Key,Value>::ReverseIterator::ReverseIterator(const Map<Key,Value>::ReverseIterator& it_in) {
        node_ptr = it_in.node_ptr;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator& Map<Key,Value>::ReverseIterator::operator=(const Map<Key,Value>::ReverseIterator& it_in) {
        if (this==&it_in)
            return *this;
        node_ptr = it_in.node_ptr;
        //it_in.node_ptr = nullptr;
        return *this;
    }
    template <class Key, class Value>
    Map<Key,Value>::ReverseIterator::ReverseIterator(Map<Key,Value>::ReverseIterator&& it_in) {
        node_ptr = it_in.node_ptr;
        it_in.node_ptr = nullptr;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator& Map<Key,Value>::ReverseIterator::operator=(Map<Key,Value>::ReverseIterator&& it_in) {
        if (this==&it_in)
            return *this;
        node_ptr = it_in.node_ptr;
        //it_in.node_ptr = nullptr;
        return *this;
    }
    template <class Key, class Value>
    Map<Key,Value>::ReverseIterator::~ReverseIterator() {
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator& Map<Key,Value>::ReverseIterator::operator++() {
        node_ptr = node_ptr->backward[0];
        return *this;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator Map<Key,Value>::ReverseIterator::operator++(int) {
        Node<Key,Value>* temp = node_ptr;
        node_ptr = node_ptr->backward[0];
        ReverseIterator it;
        it.node_ptr = temp;
        return it;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator& Map<Key,Value>::ReverseIterator::operator--() {
        node_ptr = node_ptr->forward[0];
        return *this;
    }
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator Map<Key,Value>::ReverseIterator::operator--(int) {
        Node<Key,Value>* temp = node_ptr;
        node_ptr = node_ptr->forward[0];
        ReverseIterator it;
        it.node_ptr = temp;
        return it;
    }
    template <class Key, class Value>
    std::pair<const Key, Value>& Map<Key,Value>::ReverseIterator::operator*() const {
        //std::pair<const Key, Value>* ptr = const_cast<std::pair<const Key, Value>*>(&node_ptr->data);
        //return *ptr;
        return node_ptr->data;
    }
    
    
    // Constructors
    template <class Key, class Value>
    Map<Key,Value>::Map() {
        map_height = 0;
        list_size = 0;
        head = nullptr;
        tail = nullptr;
    }
    
    template <class Key, class Value>
    Map<Key,Value>::Map(const Map & map_in) {
        map_height = 0;
        list_size = 0;
        head = nullptr;
        tail = nullptr;
        for (ConstIterator it=map_in.begin(); it!=map_in.end(); ++it) {
            insert(it.node_ptr->data);
        }
    }
    
    template <class Key, class Value>
    Map<Key,Value>& Map<Key,Value>::operator=(const Map & map_in) {
        if (this==&map_in)
            return *this;
        if (this!=&map_in) {
            if (list_size>0)
                clear();
            if (head!=nullptr)
                delete head;
            if (tail!=nullptr)
                delete tail;
        }
        map_height = 0;
        list_size = 0;
        head = nullptr;
        tail = nullptr;
        for (ConstIterator it=map_in.begin(); it!=map_in.end(); ++it) {
            insert(it.node_ptr->data);
        }
        return *this;
    }
    
    template <class Key, class Value>
    Map<Key,Value>::Map(Map&& map_in) {
        /*
         map_height = map_in.map_height;
         list_size = map_in.list_size;
         head = map_in.head;
         tail = map_in.tail;
         map_in.head = nullptr;
         map_in.tail = nullptr;
         map_in.list_size = 0;
         */
        map_height = 0;
        list_size = 0;
        head = nullptr;
        tail = nullptr;
        for (Iterator it=map_in.begin(); it!=map_in.end(); ++it) {
            insert(it.node_ptr->data);
        }
        
    }
    
    template <class Key, class Value>
    Map<Key,Value>& Map<Key,Value>::operator=(Map&& map_in) {
        if (this==&map_in)
            return *this;
        if (this!=&map_in) {
            if (list_size>0)
            	clear();
            if (head!=nullptr)
            	delete head;
            if (tail!=nullptr)
            	delete tail;
        }
        /*
         map_height = map_in.map_height;
         list_size = map_in.list_size;
         head = map_in.head;
         tail = map_in.tail;
         map_in.head = nullptr;
         map_in.tail = nullptr;
         map_in.list_size = 0;
         return *this;
         */
        map_height = 0;
        list_size = 0;
        head = nullptr;
        tail = nullptr;
        for (Iterator it=map_in.begin(); it!=map_in.end(); ++it) {
            insert(it.node_ptr->data);
        }
        return *this;
    }
    
    template <class Key, class Value>
    Map<Key,Value>::Map(std::initializer_list<std::pair<const Key, Value>> list_in) {
        map_height = 0;
        list_size = 0;
        head = nullptr;
        tail = nullptr;
        for (auto it=list_in.begin(); it!=list_in.end(); ++it) {
            insert(*it);
        }
    }
    
    template <class Key, class Value>
    Map<Key,Value>::~Map() {
        if (list_size>0)
            clear();
        if (head!=nullptr)
            delete head;
        if (tail!=nullptr)
            delete tail;
    }
    
    // Modifiers
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator Map<Key,Value>::insert(const std::pair<const Key, Value>& data_in) {
        if (list_size==0 && head==nullptr && tail==nullptr) {
            Node<Key,Value>* insert_head = new Node<Key,Value>(data_in);
            Node<Key,Value>* insert_tail = new Node<Key,Value>(data_in);
            head = insert_head;
            tail = insert_tail;
            for (int i=0; i<MAX_LEVEL; i++) {
                head->forward[i] = tail;
                head->backward[i] = nullptr;
                tail->forward[i] = nullptr;
                tail->backward[i] = head;
            }
        }
        
        Iterator it_insert;
        
        Node<Key,Value>* update[MAX_LEVEL];
        for (int i=0; i<MAX_LEVEL; i++) {
            update[i] = head;
        }
        Node<Key,Value>* p = nullptr;
        Node<Key,Value>* q = nullptr;
        p = head;
        
        // find all nodes needed to be update
        for (int i=map_height-1; i>=0; i--) {
            while ((q=p->forward[i]) != tail && (q->data.first < data_in.first)) {
                p = q;
            }
            update[i] = p;
        }
        
        // if node with same key exist, do not update the value
        if(q!=nullptr && (q!=tail && q->data.first == data_in.first)) {
            //q->data.second = data_in.second; // update the value
            it_insert.node_ptr = q;
            return it_insert;
        }
        
        // random level given to node inserted
        int level_insert = randomLevel();
        if (level_insert > map_height) {
            map_height = level_insert;
        }
        
        // update the map
        Node<Key,Value>* insert_node = new Node<Key,Value>(std::move(data_in), level_insert);
        for (int i=0; i<level_insert; i++) {
            insert_node->backward[i] = update[i];
            update[i]->forward[i]->backward[i] = insert_node;
            insert_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = insert_node;
        }
        list_size++;
        it_insert.node_ptr = insert_node;
        return it_insert;
    }
    
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator Map<Key,Value>::insert(std::pair<const Key, Value>&& data_in) {
        if (list_size==0 && head==nullptr && tail==nullptr) {
            Node<Key,Value>* insert_head = new Node<Key,Value>(data_in);
            Node<Key,Value>* insert_tail = new Node<Key,Value>(data_in);
            head = insert_head;
            tail = insert_tail;
            for (int i=0; i<MAX_LEVEL; i++) {
                head->forward[i] = tail;
                head->backward[i] = nullptr;
                tail->forward[i] = nullptr;
                tail->backward[i] = head;
            }
        }
        
        Iterator it_insert;
        
        Node<Key,Value>* update[MAX_LEVEL];
        for (int i=0; i<MAX_LEVEL; i++) {
            update[i] = head;
        }
        Node<Key,Value>* p = nullptr;
        Node<Key,Value>* q = nullptr;
        p = head;
        
        // find all nodes needed to be update
        for (int i=map_height-1; i>=0; i--) {
            while ((q=p->forward[i]) != tail && (q->data.first < data_in.first)) {
                p = q;
            }
            update[i] = p;
        }
        
        // if node with same key exist, do not update the value
        if(q!=nullptr && (q!=tail && q->data.first == data_in.first)) {
            //q->data.second = data_in.second; // update the value
            it_insert.node_ptr = q;
            return it_insert;
        }
        
        // random level given to node inserted
        int level_insert = randomLevel();
        if (level_insert > map_height) {
            map_height = level_insert;
        }
        
        // update the map
        Node<Key,Value>* insert_node = new Node<Key,Value>(std::move(data_in), level_insert);
        for (int i=0; i<level_insert; i++) {
            insert_node->backward[i] = update[i];
            update[i]->forward[i]->backward[i] = insert_node;
            insert_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = insert_node;
        }
        list_size++;
        it_insert.node_ptr = insert_node;
        return it_insert;
    }
    
    template <class Key, class Value>
    void Map<Key,Value>::erase(Iterator it_erase) {
        if (it_erase.node_ptr==nullptr || it_erase.node_ptr==tail)
            return;
        if (list_size==0)
            return;
        for (int i=0; i<(it_erase.node_ptr->node_height); i++) {
            it_erase.node_ptr->backward[i]->forward[i] = it_erase.node_ptr->forward[i];
            it_erase.node_ptr->forward[i]->backward[i] = it_erase.node_ptr->backward[i];
        }
        list_size--;
        //for (int i=0; i<it_erase.node_ptr->node_height; i++) {
        //    it_erase.node_ptr->forward[i] = nullptr;
        //    it_erase.node_ptr->backward[i] = nullptr;
        //}
        delete it_erase.node_ptr;
    }
    
    template <class Key, class Value>
    void Map<Key,Value>::remove(const Key& key_in) {
        auto it_remove = find(key_in);
        erase(it_remove);
    }
    
    template <class Key, class Value>
    void Map<Key,Value>::clear() {
        if (list_size==0)
            return;
        Iterator it = begin();
        while (it!=end()) {
            erase(it++);
        }
        if (list_size!=0)
            throw std::out_of_range("list_size is not correct");
    }
    
    // Lookup
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator Map<Key,Value>::find(const Key& key_in) {
        Iterator it_find;
        
        Node<Key,Value>* p = nullptr;
        Node<Key,Value>* q = nullptr;
        p = head;
        
        for (int i=map_height-1; i>=0; i--) {
            while ((q=p->forward[i]) != tail && (q->data.first < key_in)) {
                p = q;
            }
            if (q!=tail && q->data.first == key_in) {
                it_find.node_ptr = q;
                return it_find;
            }
        }
        
        it_find.node_ptr = tail;
        return it_find;
    }
    
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator Map<Key,Value>::find(const Key& key_in) const {
        ConstIterator it_find;
        
        Node<Key,Value>* p = nullptr;
        Node<Key,Value>* q = nullptr;
        p = head;
        
        for (int i=map_height-1; i>=0; i--) {
            while ((q=p->forward[i]) != tail && (q->data.first < key_in)) {
                p = q;
            }
            if (q!=tail && q->data.first == key_in) {
                it_find.node_ptr = q;
                return it_find;
            }
        }
        
        it_find.node_ptr = tail;
        return it_find;
        
    }
    
    template <class Key, class Value>
    Value& Map<Key,Value>::at(const Key& key_in) {
        Node<Key,Value>* p = nullptr;
        Node<Key,Value>* q = nullptr;
        p = head;
        
        for (int i=map_height-1; i>=0; i--) {
            while ((q=p->forward[i]) != tail && (q->data.first < key_in)) {
                p = q;
            }
            if (q!=tail && q->data.first == key_in) {
                return q->data.second;
            }
        }
        throw std::out_of_range("out_of_range");
    }
    
    template <class Key, class Value>
    const Value& Map<Key,Value>::at(const Key& key_in) const {
        Node<Key,Value>* p = nullptr;
        Node<Key,Value>* q = nullptr;
        p = head;
        
        for (int i=map_height-1; i>=0; i--) {
            while ((q=p->forward[i]) != tail && (q->data.first < key_in)) {
                p = q;
            }
            if (q!=tail && q->data.first == key_in) {
                return q->data.second;
            }
        }
        throw std::out_of_range("out_of_range");
    }
    
    template <class Key, class Value>
    Value& Map<Key,Value>::operator[](const Key& key_in) {
        /*
         Node<Key,Value>* p = nullptr;
         Node<Key,Value>* q = nullptr;
         p = head;
         
         for (int i=map_height-1; i>=0; i--) {
         while ((q=p->forward[i]) != tail && (q->data.first < key_in)) {
         p = q;
         }
         if (q->data.first == key_in) {
         return q->data.second;
         }
         }
         //Value value_in;
         //const std::pair<const Key, Value> temp = std::make_pair(key_in, value_in);
         //Iterator it = insert(temp);
         */
        Iterator it_at = find(key_in);
        if (it_at.node_ptr==tail) {
            std::pair<const Key, Value> temp {key_in, {}};
            Iterator it = insert(temp);
            //Iterator it = insert({key_in,{}});
            return it.node_ptr->data.second;
        }
        else
            return it_at.node_ptr->data.second;
    }
    
    // Size
    template <class Key, class Value>
    std::size_t Map<Key,Value>::size() const {
        return list_size;
    }
    
    template <class Key, class Value>
    bool Map<Key,Value>::empty() const {
        return (list_size==0);
    }
    
    
    // Iterators
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator Map<Key,Value>::begin() {
        Iterator it;
        if (head!=nullptr)
            it.node_ptr = head->forward[0];
        return it;
    }
    
    template <class Key, class Value>
    typename Map<Key,Value>::Iterator Map<Key,Value>::end() {
        Iterator it;
        it.node_ptr = tail;
        return it;
    }
    
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator Map<Key,Value>::begin() const {
        ConstIterator it;
        if (head!=nullptr)
            it.node_ptr = head->forward[0];
        return it;
    }
    
    template <class Key, class Value>
    typename Map<Key,Value>::ConstIterator Map<Key,Value>::end() const {
        ConstIterator it;
        it.node_ptr = tail;
        return it;
    }
    
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator Map<Key,Value>::rbegin() {
        ReverseIterator it;
        if (tail!=nullptr)
            it.node_ptr = tail->backward[0];
        return it;
    }
    
    template <class Key, class Value>
    typename Map<Key,Value>::ReverseIterator Map<Key,Value>::rend() {
        ReverseIterator it;
        it.node_ptr = head;
        return it;
    }
    
    // Comparison Operators
    template <class Key, class Value>
    bool Map<Key,Value>::operator==(const Map& map2) const {
        if (list_size != map2.list_size)
            return false;
        ConstIterator it1 = begin();
        ConstIterator it2 = map2.begin();
        while (it1!=end() && it2!=map2.end()) {
            if ((it1.node_ptr->data) != (it2.node_ptr->data))
                return false;
            ++it1;
            ++it2;
        }
        return true;
    }
    
    template <class Key, class Value>
    bool Map<Key,Value>::operator!=(const Map& map2) const {
        if (list_size != map2.list_size)
            return true;
        ConstIterator it1 = begin();
        ConstIterator it2 = map2.begin();
        while (it1!=end() && it2!=map2.end()) {
            if ((it1.node_ptr->data) != (it2.node_ptr->data))
                return true;
            ++it1;
            ++it2;
        }
        return false;
    }
    
    // Others
    template <class Key, class Value>
    int Map<Key,Value>::randomLevel() {
        int k = 1;
        while(rand()%2)
            k++;
        k = (k<MAX_LEVEL) ? k:MAX_LEVEL;
        return k;
    }
    template <class Key, class Value>
    void Map<Key,Value>::print_map() {
        for (Iterator it=begin(); it!=end(); ++it) {
            std::cout<< it.node_ptr->data.first << " " << it.node_ptr->data.second << std::endl;
        }
    }
    
}


#endif

