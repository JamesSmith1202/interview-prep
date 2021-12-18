#include <bits/stdc++.h>

using namespace std;

template <class T> struct DataNode {
    T payload;
    DataNode<T>* next;
    DataNode<T>* prev;

    DataNode(T i, DataNode<T>* p, DataNode<T>* n) : payload(i), next(n), prev(p) {};
    DataNode(T i) : DataNode(i, nullptr, nullptr) {};
};

template <class T> struct Iterator {
    using iterator_category = forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    Iterator(DataNode<T> * p = (DataNode<T>*)nullptr) {
        this->p = p;
    }

    Iterator(const Iterator& other) = default;

    ~Iterator() = default;

    T& operator*() const {
        return p->payload;
    }

    T* operator->() {
        return &p->payload;
    }

    // prefix
    Iterator& operator++() {
        this->p = p->next;
        return *this;
    }

    // postfix
    Iterator operator++(int) {
        Iterator tmp = *this;
        p = p->next;
        return tmp;
    }

    // prefix
    Iterator& operator--() {
        this->p = p->prev;
        return *this;
    }

    // postfix
    Iterator operator--(int) {
        Iterator tmp = *this;
        p = p->prev;
        return tmp;
    }

    friend bool operator==(const Iterator& l, const Iterator& r) {
        return l.p == r.p;
    }

    friend bool operator!=(const Iterator& l, const Iterator& r) {
        return l.p != r.p;
    }

    Iterator& operator=(Iterator other) { swap(p, other.p); return *this; }

    DataNode<T> * p;
};

template <class T> class PrepList {
    public:
        PrepList(): head(nullptr), tail(nullptr), _size(0) {};
        PrepList(size_t init_size);
        PrepList(PrepList& other);
        ~PrepList();

        void push_back(T i);
        Iterator<T> insert(Iterator<T>& pos, T i);

        void erase(Iterator<T>& pos);
        void erase(Iterator<T>& start, Iterator<T>& end);
        void clear();
        void pop_back();
        void pop_front();

        T& front();
        T& back();

        Iterator<T> begin();
        Iterator<T> end();

        size_t size() const;

        string to_string();

    private:
        DataNode<T> * head;
        DataNode<T> * tail;
        size_t _size;
};

template <class T> PrepList<T>::PrepList(size_t init_size) : PrepList() {
    for (int i = 0; i < init_size; i++) {
        this->push_back(T());
    }
}

template <class T> PrepList<T>::PrepList(PrepList& other) : PrepList() {
    Iterator tmp = other.begin();
    Iterator end = other.end();
    while (tmp != end) {
        this->push_back(*tmp);
        tmp++;
    }
}

template <class T> PrepList<T>::~PrepList() {
    this->clear();
}

template <class T> void PrepList<T>::push_back(T i) {
    if (this->head == nullptr) {
        this->head = new DataNode(i);
        this->tail = this->head;
    } else {
        this->tail->next = new DataNode(i);
        this->tail->next->prev = this->tail;
        this->tail = tail->next;
    }
    _size++;
}

template <class T> Iterator<T> PrepList<T>::insert(Iterator<T>& pos, T i) {
    DataNode<T> * ahead = pos.p;
    if (ahead == nullptr) {
        this->push_back(i);
        return this->begin();
    }

    DataNode<T> * before = ahead->prev;

    if (before == nullptr) {
        // ahead = head
        this->head->prev = new DataNode(i, (DataNode<T>*)nullptr, this->head);
        this->head = this->head->prev;
    } else {
        before->next = new DataNode(i, before, before->next);
        ahead->prev = before->next;
    }

    this->_size++;

    return Iterator(before->next);
}

template <class T> void PrepList<T>::erase(Iterator<T>& pos) {
    DataNode<T> * r = pos.p;

    if (this->_size == 1) {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else if (this->tail == r) {
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
    }
    else if (r == this->head) {
        this->head = this->head->next;
        this->head->prev = nullptr;
    } else {
        r->prev->next = r->next;
        r->next->prev = r->prev;
    }

    delete r;
    this->_size--;
}
template <class T> void PrepList<T>::erase(Iterator<T>& start, Iterator<T>& end) {
    Iterator<T> tmp = start;
    while (tmp != end) {
        Iterator<T> n = tmp++;
        this->erase(n);
    }
}

template <class T> void PrepList<T>::clear() {
    Iterator<T> begin = this->begin();
    Iterator<T> end = this->end();

    this->erase(begin, end);
}

template <class T> T& PrepList<T>::back() {
    if (this->_size == 0) {
        throw out_of_range("no elements");
    }

    return this->tail->payload;
}

template <class T> T& PrepList<T>::front() {
    if (this->_size == 0) {
        throw out_of_range("no elements");
    }

    return this->head->payload;
}

template <class T> void PrepList<T>::pop_back() {
    Iterator<T> back(this->tail);
    this->erase(back);
}

template <class T> void PrepList<T>::pop_front() {
    Iterator<T> front = this->begin();
    this->erase(front);
}

template <class T> Iterator<T> PrepList<T>::begin() {
    return Iterator(this->head);
}

template <class T> Iterator<T> PrepList<T>::end() {
    return Iterator<T>();
}

template <class T> size_t PrepList<T>::size() const {
    return this->_size;
}

template <class T> string PrepList<T>::to_string() {
    stringstream ss;

    ss << "[";

    Iterator<T> it = this->begin();
    Iterator<T> end = Iterator(this->tail);
    while(it != end) {
        ss << *it << ",";
        it++;
    }

    if (this->tail != nullptr) {
        ss << *end;
    }

    ss << "]";

    return ss.str();
}

int main() {
    PrepList<int> pl;

    cout << pl.to_string() << endl;

    pl.push_back(1);

    cout << pl.to_string() << endl;

    pl.push_back(2);
    pl.push_back(3);
    pl.push_back(4);

    cout << pl.to_string() << endl;

    pl.pop_back();

    cout << pl.to_string() << endl;

    pl.pop_front();

    cout << pl.to_string() << endl;

    pl.clear();

    cout << pl.to_string() << endl;

    PrepList<int> original;
    for (int i = 0; i < 10; i++) {
        original.push_back(i);
    }

    
    cout << "Original: " << original.to_string() << endl;
    
    PrepList copy_list(original);

    cout << "Copy Constructor: " << copy_list.to_string() << endl;

    PrepList<int> copy_algo(original.size());
    copy(original.begin(), original.end(), copy_algo.begin());
    cout << "Copy Algo: " << copy_list.to_string() << endl;

    PrepList<string> strlst;

    strlst.push_back("hello");
    strlst.push_back("world");
    strlst.push_back("!");

    cout << strlst.to_string() << endl;
    cout << strlst.size() << endl;
}