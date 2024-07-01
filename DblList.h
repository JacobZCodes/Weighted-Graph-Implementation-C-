// Jacob Zamore
// Header file for doubly linked list implementation
#ifndef DBL_LIST_H
#define DBL_LIST_H

#include "ListNode.h"

template <typename T>
class DblList{
    public:
        DblList();
        virtual ~DblList();
        void addFront(T data);
        void addBack(T data);
        void add(int pos, T data);
        T removeFront();
        T removeBack();
        T remove(int pos);
        bool isEmpty();
        int getSize();
        T get(int pos);
        ListNode<T>* getFront();
        void printInfo();
        bool removeByValue(int value);
        bool contains(T value);


    private:
        ListNode<T>* m_front;
        ListNode<T>* m_back;
        int m_size;
};

template <typename T>
DblList<T>::DblList(){
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}

template <typename T>
DblList<T>::~DblList(){
    m_front = NULL;
    m_back = NULL;
    m_size = 0;
}


template <typename T>
bool DblList<T>::removeByValue(int value) {
// CHATGPT 
    // Case: Empty list
    if (isEmpty()) {
        return false;
    }

    ListNode<T>* current = m_front;

    // Searching for the node with the given integer value
    while (current != NULL && current->m_data != value) {
        current = current->m_next;
    }

    // Case: Value not found
    if (current == NULL) {
        return false;
    }

    // Case: Node is the only element in the list
    if (m_size == 1) {
        delete m_front;
        m_front = NULL;
        m_back = NULL;
    }
    // Case: Node is the front element
    else if (current == m_front) {
        m_front = m_front->m_next;
        m_front->m_prev = NULL;
        delete current;
    }
    // Case: Node is the back element
    else if (current == m_back) {
        m_back = m_back->m_prev;
        m_back->m_next = NULL;
        delete current;
    }
    // Case: Node is in the middle
    else {
        current->m_prev->m_next = current->m_next;
        current->m_next->m_prev = current->m_prev;
        delete current;
    }

    --m_size;
    return true; // Successful removal
}

template <typename T>
void DblList<T>::printInfo() {
    ListNode<T>* current = m_front;
    while (current != NULL) {
        // Print the data in the current node
        // If T is a simple data type:
        cout << current->m_data << endl;

        // If T is a complex type and has a print or toString method:
        // current->m_data.print(); // or
        // cout << current->m_data.toString() << endl;

        // Move to the next node
        current = current->m_next;
    }
}

template <typename T>
bool DblList<T>::contains(T value) {
    // CHATGPT
    ListNode<T>* currentNode = m_front;
    while (currentNode != NULL) {
        if (currentNode->m_data == value) {
            return true; // Found the ListNode with the specified value
        }
        currentNode = currentNode->m_next; // Move to the next node in the list
    }
    return false; // Value not found in the list
}


template <typename T>
ListNode<T>* DblList<T>::getFront(){
    return m_front;
}
template <typename T>
int DblList<T>::getSize(){ //constant - O(1)
    return m_size;
}

template <typename T>
bool DblList<T>::isEmpty(){ //constant - O(1)
    return (m_size == 0);
}

template <typename T>
void DblList<T>::addFront(T data){ //Constant
    ListNode<T>* newNode = new ListNode<T>(data);
    if(!isEmpty()){
        m_front->m_prev = newNode;
        newNode->m_next = m_front;
    }else{ //the list is empty
        m_back = newNode;
    }
    m_front = newNode;
    ++m_size;
}

template <typename T>
void DblList<T>::addBack(T data){ //Constant
    ListNode<T>* newNode = new ListNode<T>(data);
    if(!isEmpty()){
        m_back->m_next = newNode;
        newNode->m_prev = m_back;
    }else{ //list is empty
        m_front = newNode;
    }
    m_back = newNode;
    ++m_size;
}

template<typename T>
void DblList<T>::add(int pos, T data){ //linear 
    if(isEmpty()){
        addFront(data);
    }else if(pos == 0){
        addFront(data);
    }else if(pos >= m_size){
        addBack(data);
    }else{
        ListNode<T>* current = m_front;
        int cPos = 0;
        while(cPos != pos){
            current = current->m_next;
            ++cPos;
        }
        ListNode<T>* newNode = new ListNode<T>(data);
        current->m_prev->m_next = newNode;
        newNode->m_prev = current->m_prev;
        current->m_prev = newNode;
        newNode->m_next = current;
        ++m_size;
    }

}

template<typename T>
T DblList<T>::removeFront(){ //constant
    T data;
    data = m_front->m_data;
    //make sure not empty
    if(m_size == 1){
        delete m_front;
        m_front = NULL;
        m_back = NULL;
    }else{
        ListNode<T>* currFront = m_front;
        m_front = m_front->m_next;
        m_front->m_prev = NULL;
        delete currFront;
    }
    --m_size;
    return data;
}

template<typename T>
T DblList<T>::removeBack(){ //constant
    T data;
    data = m_back->m_data;
    //make sure not empty
    if(m_size == 1){
        delete m_back; //could also use m_front, since m_back and m_front point to the same place
        m_front = NULL;
        m_back = NULL;
    }else{
        ListNode<T>* currBack = m_back;
        m_back = m_back->m_prev;
        m_back->m_next = NULL;
        delete currBack;
    }
    --m_size;
    return data;
}

template<typename T>
T DblList<T>::remove(int pos){ //linear
    //make sure not empty
    T data;
    if(pos == 0){
        data = removeFront();
    }else if(pos >= m_size){
        data = removeBack();
    }else{

        ListNode<T>* current = m_front;
        int cPos = 0;
        while(cPos != pos){
            current = current->m_next;
            ++cPos;
        }
        data = current->m_data;
        current->m_prev->m_next = current->m_next;
        current->m_next->m_prev = current->m_prev;
        delete current;
        --m_size;
    }    return data;
} 

template<typename T>
T DblList<T>::get(int pos){ //linear
    //todo - make sure position is in range
    ListNode<T>* current = m_front;
    int cPos = 0;
    while(cPos != pos){
        current = current->m_next;
        ++cPos;
    }
    return current->m_data;
}


#endif