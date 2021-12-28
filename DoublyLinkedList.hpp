// DoublyLinkedList.hpp
//
// ICS 46 Spring 2021
// Project #2: Time Waits for No One
//
// DoublyLinkedList<ValueType> is a class template that implements a
// doubly-linked list with head and tail pointers, including two kinds
// of iterators: One of them allows viewing and modifying the list's
// contents, while the other allows only viewing them.
//
// Your goal is to implement the entire public interface *exactly* as
// specified below.  Do not modify the signatures of any of the public
// member functions (including the public member functions of the various
// iterator classes) in any way.  We will be running extensive unit
// tests against your implementation, which will not compile unless
// things remain completely unchanged.  As we did in Project #0, we've
// provided you a basic set of unit tests that briefly demonstrate how
// each of the member functions is required to behave; you'll find
// those in the "gtest" directory.
//
// All of the public member functions listed with "noexcept" in their
// signature must be implemented in a way that they never throw exceptions.
// All of the others are expected to make the "strong" exception guarantee,
// which means two things: (1) no memory has leaked, and (2) the contents
// of the list/iterator will not have visibly changed in the event that
// an exception has been thrown.
//
// The entire C++ Standard Library is off-limits in your implementation
// of this class.  DO NOT submit a version of this file (or any file
// that it includes) that includes any C++ Standard Library headers.
// (This includes things like adding a print() member function that
// requires <iostream>.)
//
// As is good custom in class templates, keep the interface separate
// from the implementation.  This means the bodies of member functions
// should not be written in the class declaration, but should appear
// below it.  I've placed "dummy" implementations of every public
// member function, though, of course, most of them don't do the
// right thing; but they will save you some typing and demonstrate
// the structure of what you should be writing.

#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "EmptyException.hpp"
#include "IteratorException.hpp"



template <typename ValueType>
class DoublyLinkedList
{
    // The forward declarations of these classes allows us to establish
    // that they exist, but delay displaying all of the details until
    // later in the file.
    //
    // (This is generally a good style, with the most important details
    // appearing earlier in the class declaration.  That's the same
    // reason why we're implementing the bodies of the member functions
    // outside of the class declaration.)
public:
    class Iterator;
    class ConstIterator;


private:
    struct Node;


public:
    // Initializes this list to be empty.
    DoublyLinkedList() noexcept;

    // Initializes this list as a copy of an existing one.
    DoublyLinkedList(const DoublyLinkedList& list);

    // Initializes this list from an expiring one.
    DoublyLinkedList(DoublyLinkedList&& list) noexcept;


    // Destroys the contents of this list.
    virtual ~DoublyLinkedList() noexcept;


    // Replaces the contents of this list with a copy of the contents
    // of an existing one.
    DoublyLinkedList& operator=(const DoublyLinkedList& list);

    // Replaces the contents of this list with the contents of an
    // expiring one.
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;


    // addToStart() adds a value to the start of the list, meaning that
    // it will now be the first value, with all subsequent elements still
    // being in the list (after the new value) in the same order.
    void addToStart(const ValueType& value);

    // addToEnd() adds a value to the end of the list, meaning that
    // it will now be the last value, with all subsequent elements still
    // being in the list (before the new value) in the same order.
    void addToEnd(const ValueType& value);


    // removeFromStart() removes a value from the start of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the first one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromStart();

    // removeFromEnd() removes a value from the end of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the last one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromEnd();


    // first() returns the value at the start of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& first() const;
    ValueType& first();


    // last() returns the value at the end of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& last() const;
    ValueType& last();


    // isEmpty() returns true if the list has no values in it, false
    // otherwise.
    bool isEmpty() const noexcept;


    // size() returns the number of values in the list.
    unsigned int size() const noexcept;



    // There are two kinds of iterators supported: Iterators and
    // ConstIterators.  They have similar characteristics; they both
    // allow you to see what values are in the list and move back and
    // forth between them.  The difference is that ConstIterators allow
    // you to see the elements but not modify them, while Iterators also
    // support modification of the list (both by modifying the elements
    // directly, and also by inserting or removing values at arbitrary
    // locations).
    //
    // At any given time, an iterator refers to a value in the list.
    // There are also two additional places it can refer: "past start"
    // and "past end", which are the positions directly before the
    // first value and directly after the last one, respectively.
    // Except with respect to those boundaries, they can be moved
    // both forward and backward.
    //
    // Note, too, that the reason we have a ConstIterator class instead
    // of just saying "const Iterator" is because a "const Iterator"
    // is something different: It's an Iterator object that you can't
    // modify (i.e., you can't move it around).  What a ConstIterator
    // holds constant isn't the iterator; it's the list that's protected
    // by it.


    // iterator() creates a new Iterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    Iterator iterator();


    // constIterator() creates a new ConstIterator over this list.  It will
    // initially be referring to the first value in the list, unless the
    // list is empty, in which case it will be considered both "past start"
    // and "past end".
    ConstIterator constIterator() const;


public:
    // The IteratorBase class is the base class for our two kinds of
    // iterators.  Because there are so many similarities between them,
    // we write those similarities in a base class, then inherit from
    // that base class to specify only the differences.
    class IteratorBase
    {
    public:
        // Initializes a newly-constructed IteratorBase to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        IteratorBase(const DoublyLinkedList& list) noexcept;


        // moveToNext() moves this iterator forward to the next value in
        // the list.  If the iterator is refrering to the last value, it
        // moves to the "past end" position.  If it is already at the
        // "past end" position, an IteratorException will be thrown.
        void moveToNext();


        // moveToPrevious() moves this iterator backward to the previous
        // value in the list.  If the iterator is refrering to the first
        // value, it moves to the "past start" position.  If it is already
        // at the "past start" position, an IteratorException will be thrown.
        void moveToPrevious();


        // isPastStart() returns true if this iterator is in the "past
        // start" position, false otherwise.
        bool isPastStart() const noexcept;


        // isPastEnd() returns true if this iterator is in the "past end"
        // position, false otherwise.
        bool isPastEnd() const noexcept;
    
    protected:
        // You may want protected member variables and member functions,
        // which will be accessible to the derived classes.
        bool pastStart;
        bool pastEnd;
        unsigned int* itSize;
        Node* itHead;
        Node* itTail;
        Node* currentNode;
    };


    class ConstIterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed ConstIterator to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        ConstIterator(const DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        const ValueType& value() const;

    private:
        // You may want private member variables and member functions.
        // Node* currentNode;

    };


    class Iterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed Iterator to operate on the
        // given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        Iterator(DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        ValueType& value() const;


        // insertBefore() inserts a new value into the list before
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past start" position, an IteratorException
        // is thrown.
        void insertBefore(const ValueType& value);


        // insertAfter() inserts a new value into the list after
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past end" position, an IteratorException
        // is thrown.
        void insertAfter(const ValueType& value);


        // remove() removes the value to which this iterator refers,
        // moving the iterator to refer to either the value after it
        // (if moveToNextAfterward is true) or before it (if
        // moveToNextAfterward is false).  If the iterator is in the
        // "past start" or "past end" position, an IteratorException
        // is thrown.
        void remove(bool moveToNextAfterward = true);

    private:
        // You may want private member variables and member functions.
    };


private:
    // A structure that contains the vital parts of a Node in a
    // doubly-linked list, the value and two pointers: one pointing
    // to the previous node (or nullptr if there isn't one) and
    // one pointing to the next node (or nullptr if there isn't
    // one).
    struct Node
    {
        ValueType value;
        Node* prev;
        Node* next;
    };


    // You can feel free to add private member variables and member
    // functions here; there's a pretty good chance you'll need some.
    Node* head;
    Node* tail;
    unsigned int sz;  // size of DLL
    unsigned int* pSZ = &sz; // pointer to reference for use in IteratorBase and derived classes.
};


// Default constructor
template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList() noexcept
{
    head = tail = nullptr;
    sz = 0;
}


// Copy Constructor
template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& list)
{
    try
    {
        Node* listCurrentNode = list.head; // Keeps track of nodes in other list without modifying any nodes.

        head = new Node
                    {
                        listCurrentNode->value,
                        nullptr,
                        nullptr
                    };
        
        Node* thisCurrentNode = head;  // Only do this once so head points to correct first created node.

        // Set up for next possible node or nullptr if no more nodes to link
        listCurrentNode = listCurrentNode->next;  // could be nullptr or filled Node

        // IF MORE THAN ONE NODE, LINK THE NODE TOGETHER BASED ON NODE COUNT/SIZE OF LIST (OTHER DLL).
        while(listCurrentNode != nullptr)
        {
            Node* thisPreviousNode = thisCurrentNode; 
            thisCurrentNode = thisCurrentNode->next;

            thisCurrentNode = new Node
                                    {
                                        listCurrentNode->value,
                                        thisPreviousNode, // link back
                                        nullptr
                                    };
            thisPreviousNode->next = thisCurrentNode; // link forward
        
            tail = thisCurrentNode;

            // // Could be another node of list OR nullptr which will break while loop
            listCurrentNode = listCurrentNode->next;
        }
        // After exiting the while loop, the head should point to the first node and

        sz = list.sz;  
    }
    // Catch exception/error, deallocate memory (to avoid memory leak), then re-throw exception/error.
    catch(...)
    {
        // Return to being empty with size = 0 and head/tail point to nullptr
        while (head != nullptr)
        {
            Node* tempNode = head;
            head = head->next;
            delete tempNode;
        }
        head = tail = nullptr;
        sz = 0;

        throw;
    }
}


// move copy constructor
template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& list) noexcept
    : head{nullptr}, tail{nullptr}, sz{0}
{
    Node* thisHead = head; // stays pointing at original head
    head = list.head; // make our head point to other List.head
    list.head = thisHead;  // 

    Node* thisTail = tail; // stays pointing at original head
    tail = list.tail;
    list.tail = thisTail;

    // swaps size but since size is statically allocated here, no real need to swap
    unsigned int tempSize;
    tempSize = sz;
    sz = list.sz;
    list.sz = tempSize;
}

// Deconstructor
template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList() noexcept
{
    while (head != nullptr)
    {
        Node* currentNode = head;
        head = head->next;
        delete currentNode;
    }
    // Ensure these member variables die.
    head = tail = nullptr;
    //delete pSZ;
}

// assignment operator
template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(const DoublyLinkedList& list)
{
    Node* newHead = nullptr;
    Node* newTail = nullptr;

    if (this != &list)
    {
        try
        {
            Node* listCurrentNode = list.head; // Keeps track of nodes in other list without modifying any nodes.

            newHead = new Node
                        {
                            listCurrentNode->value,
                            nullptr,
                            nullptr
                        };
            
            Node* thisCurrentNode = newHead;  // Only do this once so head points to correct first created node.

            // Set up for next possible node or nullptr if no more nodes to link
            listCurrentNode = listCurrentNode->next;  // could be nullptr or filled Node

            // IF MORE THAN ONE NODE, LINK THE NODE TOGETHER BASED ON NODE COUNT/SIZE OF LIST (OTHER DLL).
            while(listCurrentNode != nullptr)
            {
                Node* thisPreviousNode = thisCurrentNode; 
                thisCurrentNode = thisCurrentNode->next;

                thisCurrentNode = new Node
                                        {
                                            listCurrentNode->value,
                                            thisPreviousNode, // link back
                                            nullptr
                                        };
                thisPreviousNode->next = thisCurrentNode; // link forward
            
                newTail = thisCurrentNode;

                // // Could be another node of list OR nullptr which will break while loop
                listCurrentNode = listCurrentNode->next;
            }

            // delete all current nodes from this DLL if any exist
            while (head != nullptr)
            {
                Node* tempNode = head;
                head = head->next;
                delete tempNode;
            }

            head = tail = nullptr;

            // repoint head and tail to new DLL
            head = newHead;
            tail = newTail;
            // this size = list size
            sz = list.sz;  
        } 
        // Catch exception/error, deallocate memory (to avoid memory leak), then re-throw exception/error.
        catch(...)
        {
            // original head, tail, size stay intact
            while (newHead != nullptr)
            {
                Node* tempNode = newHead;
                newHead = newHead->next;
                delete tempNode;
            }
            throw;
        }    
    }
    return *this;
}

// move assigntment operator
template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
    if (this != &list)
    {
        // Doesn't matter if other list is empty or not since ALL private member vars should be switched anyways
        Node* tempNode = nullptr;

        tempNode = head; // stays pointing at original head
        head = list.head;
        list.head = tempNode;

        tempNode = tail; // stays pointing at original head
        tail = list.tail;
        list.tail = tempNode;

        // swaps size
        unsigned int tempSize;
        tempSize = sz;
        sz = list.sz;
        list.sz = tempSize;
    }
    return *this;
}


// Adds node to the front with a particular value and repoints head
template <typename ValueType>
void DoublyLinkedList<ValueType>::addToStart(const ValueType& value)
{
    Node* newNode = new Node{value, nullptr, nullptr};

    Node* originalHeadNode = head;

    if (sz == 0) // DLL is empty
    {
        head = tail = newNode;
        sz++;
    }
    else // (size is > 0)
    {
        try
        {
            // can anything go wrong here in this try??
            Node* tempNode = head;
            head->prev = newNode;
            head = newNode;

            head->value = value;
            head->prev = nullptr;
            head->next = tempNode;

            sz++;  // if the try has gotten this far, size will not throw an exception.
        }
        catch(...)
        {
            delete newNode;

            // head = nodeBeforeHead->prev;
            head = originalHeadNode;      

            throw;
        }
    }
}

// Adds node to the back with a particular value and repoints tail
template <typename ValueType>
void DoublyLinkedList<ValueType>::addToEnd(const ValueType& value)
{
    Node* newNode = new Node{value, nullptr, nullptr};

    Node* originalTail = tail;

    if (sz == 0)
    {
        head = tail = newNode;
        sz++;
    }
    else
    {
        try
        {
            Node* tempNode = tail;
            tail->next = newNode;
            tail = newNode;

            tail->value = value;
            tail->prev = tempNode;
            tail->next = nullptr;

            sz++;
        }
        catch(...)
        {
            delete newNode;
            tail = originalTail;

            throw;
        }
    }
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromStart()
{
    if (sz == 0)
    {
        throw EmptyException{};
    }
    else if (sz == 1)
    {
        delete head;
        head = tail = nullptr;
        sz--;
    }
    else // sz >= 2
    {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        sz--;
    }    
}


// Remove node from end of the DLL and repoint tail
template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
    // don't need a try and catch here????

    if (sz == 0)
    {
        throw EmptyException{};
    }
    else if (sz == 1)
    {
        delete tail;
        head = tail = nullptr;
        sz--;
    }
    else
    {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        sz--;
    } 
}


// Returns the value of the head (first node) that CANNOT change or be modified
template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::first() const
{
    if (sz == 0)
    {
        throw EmptyException{};
    }
    else
    {
        return head->value;
    } 
}

// Returns the value of the head (first node) that CAN change or be modified
template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::first()
{
    if (sz == 0)
    {
        throw EmptyException{};
    }
    else
    {
        return head->value;
    } 
}


// Returns the value of the last (last node) that CANNOT change or be modified
template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::last() const
{
    if (sz == 0)
    {
        throw EmptyException{};
    }
    else
    {
        return tail->value;
    } 
}


// Returns the value of the last (last node) that CAN change or be modified
template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::last()
{
    if (sz == 0)
    {
        throw EmptyException{};
    }
    else
    {
        return tail->value;
    } 
}

// Returns the size of the DLL that is modified in the DLL class and IteratorBase with its derived iterator classes
template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
    return sz;
}


// Returns true of list is empty, false if not empty
template <typename ValueType>
bool DoublyLinkedList<ValueType>::isEmpty() const noexcept
{
    if (head == nullptr && tail == nullptr && sz == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}



// Iterator member functions //



// Construct modifiable iterator
template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
    return Iterator{*this};
}


// Construct constant iterator
template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
    return ConstIterator{*this};
}


// Class that Iterator and ConstIterator derives from using the DLL
template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
{
    itHead = list.head;
    itTail = list.tail;
    itSize = list.pSZ;

    // if list is empty
    if (itHead == nullptr && itTail == nullptr)
    {
        itSize = 0;
        currentNode = nullptr;
        pastStart = true;
        pastEnd = true;
    }
    // if list is NOT empty
    else // itHead will refer to the first value in the list;
    {
        pastStart = false;
        pastEnd = false;

        currentNode = itHead;
    }
}


// Current position moves to next node towards tail
template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
    // if current position is nullptr after tail
    if (currentNode == nullptr && pastStart == false && pastEnd == true) // currentNode is pastStart
    {
        throw IteratorException{};
    }
    // if current position is nullptr before head, move to head
    else if (currentNode == nullptr && pastStart == true && pastEnd == false)
    {
        currentNode = itHead;

        pastStart = false;
        pastEnd = false;
    }
    // if current position is node before tail, set to tail
    else if (currentNode->next == itTail)
    {
        currentNode = itTail;

        pastStart = false;
        pastEnd = false;
    }
    // current position from head to tail - 1
    else
    {
        currentNode = currentNode->next;

        // if current position IS the tail, it is now nullptr and pastEnd
        if (currentNode == nullptr)
        {
            pastStart = false;
            pastEnd = true;
        }
    }
}


// Current position moves to next node towards head
template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
    // if current position is nullptr before head
    if (currentNode == nullptr && pastStart == true && pastEnd == false) // currentNode is pastStart
    {
        throw IteratorException{};
    }
    // if current position is nullptr after tail, move to tail
    else if (currentNode == nullptr && pastStart == false && pastEnd == true)
    {
        currentNode = itTail;
    
        pastStart = false;
        pastEnd = false;
    }
    // if current position is node BEFORE head, set head to this node
    else if (currentNode->prev == itHead)
    {
        currentNode = itHead;

        pastStart = false;
        pastEnd = false;
    }
    // current position from head + 1 to tail
    else
    {
        currentNode = currentNode->prev;

        // if current position IS the head, it is now nullptr and pastStart
        if (currentNode == nullptr)
        {
            pastStart = true;
            pastEnd = false;
        }
    }
}


// Returns true if the current position is in the pastStart position, false otherwise.
template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastStart() const noexcept
{
    return pastStart;
}


// Returns true if the current position is in the pastEnd position, false otherwise.
template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastEnd() const noexcept
{
    return pastEnd;
}


// ConstIterator constructor taking in the DLL
template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
}


// Returns the value of the current position in the ConstIterator
template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::ConstIterator::value() const
{
    if (this->pastStart == true || this->pastEnd == true || this->currentNode == nullptr)
    {
        throw IteratorException{};
    }
    else
    {
        return this->currentNode->value;
    }
}


// Iterator constructor taking in the DLL
template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
}


// Returns the value of the current position of Iterator
template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::Iterator::value() const
{
    if (this->pastStart == true || this->pastEnd == true || this->currentNode == nullptr)
    {
        throw IteratorException{};
    }
    else
    {
        return this->currentNode->value;
    }
}


// Inserts new node before current position
// Increases size of DLL by 1
// DOES NOT move current position / currentNode 
template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
    // if current position is nullptr before head
    if (this->pastStart == true && this->currentNode == nullptr)
    {
        throw IteratorException{};
    }
    // if current position IS head
    else if (this->currentNode == this->itHead)
    {
        Node* insertedNode = new Node{value, nullptr, this->itHead};
        this->itHead->prev = insertedNode;

        // repoint head to insertedNode
        this->itHead = insertedNode;
    }
    // if current position is nullptr after tail
    else if (this->pastEnd == true && this->currentNode == nullptr)
    {
        Node* insertedNode = new Node{value, this->itTail, nullptr};
        this->itTail->next = insertedNode;

        // repoint tail to insertedNode
        this->itTail = insertedNode;

        // pastEnd remains true
    }
    else
    {
        Node* insertedNode = new Node{value, this->currentNode->prev, this->currentNode};

        Node* nodeBeforeInsert = this->currentNode->prev;
        nodeBeforeInsert->next = insertedNode;

        this->currentNode->prev = insertedNode;
    }
    this->itSize++;
}


// Inserts new node after current position
// Increases size of DLL by 1
// DOES NOT move current position / currentNode 
template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
    // if current position is nullptr after tail
    if (this->pastEnd == true && this->currentNode == nullptr)
    {
        throw IteratorException{};
    }
    // if current position IS tail, insertedNode becomes new tail
    else if (this->currentNode == this->itTail && this->pastEnd == false)
    {
        Node* insertedNode = new Node{value, this->itTail, nullptr};
        this->itTail->next = insertedNode;

        // repoint tail to insertedNode
        this->itTail = insertedNode;

        // // No longer necessary since size counts the nodes when
        // // the member function .size() is called.
        // //update size
        // itSize++;
    }
    // if current position is nullptr before head
    else if (this->pastStart == true && this->currentNode == nullptr)
    {
        Node* insertedNode = new Node{value, nullptr, this->itHead};
        this->itHead->prev = insertedNode;

        // repoint tail to insertedNode
        this->itHead = insertedNode;

        // pastStart remains true
    }
    else
    {
        Node* insertedNode = new Node{value, this->currentNode, this->currentNode->next};

        Node* nodeAfterInsert = this->currentNode->next;
        nodeAfterInsert->prev = insertedNode;

        this->currentNode->next = insertedNode;

        // use try and catch method???
        // delete insertedNode;
    }
    this->itSize++;
}


// Removes a node and redetermines/updates head and tail pointers if neccesary.
// Decrease size of DLL by -1
// Possible for currentNode to enter the pastStart or pastEnd position (aka nullptr).
template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
    if (this->pastStart == true || this->pastEnd == true)
    {
        throw IteratorException{};
    }
    else if (moveToNextAfterward == true) // so move after
    {
        if (this->currentNode == this->itHead)
        {
            Node* tempNode = this->currentNode; // Point to original head position to delete later
            this->currentNode = this->currentNode->next; // Repoint to node after head
            this->currentNode->prev = nullptr; // Update for prev to point at pastStart / nullptr
            this->itHead = this->currentNode; // Repoint to "new" head node

            delete tempNode; // Delete the original head   
        }
        else if (this->currentNode == this->itTail) // will delete tail node and point to nullptr
        {
            this->currentNode = this->currentNode->prev; // go backwards to delete current / tail node
            delete this->currentNode->next; // delete original tail node
            this->itTail = this->currentNode; // tail now refers to "new" tail
            this->currentNode->next = nullptr; // update the next pointer of new tail node
            this->currentNode = nullptr; // current position is now pastEnd / correct position
            
            this->pastEnd = true; // Update pastEnd to true because currentNode now points to nullptr after tail
        }
        // node is right before tail
        else if (this->currentNode->next == this->itTail) 
        {
            this->currentNode = this->currentNode->prev; // go backwards to delete current
            delete this->currentNode->next; // delete original tail node
            this->currentNode->next = this->itTail;  // Tail should still have same value and same next (nullptr)
            this->itTail->prev = this->currentNode;

            this->currentNode = this->itTail;  
        }
        // if currentNode is the last node in the DLL
        else if (this->currentNode->prev == nullptr && this->currentNode->next == nullptr)
        {
            delete this->currentNode;
            this->currentNode = this->itHead = this->itTail = nullptr;
            this->pastStart = true;
            this->pastEnd = true;

            //update size?
        }
        else // remove a body node if size > 1 since size == 1 is taken care of
        {
            Node* nodeBefore = this->currentNode->prev;
            Node* nodeAfter = this->currentNode->next;
            
            delete this->currentNode;
            nodeBefore->next = nodeAfter;
            nodeAfter->prev = nodeBefore;

            this->currentNode = nodeAfter;
        }
    }
    else if (moveToNextAfterward == false) // so move before
    {
        if (this->currentNode == this->itHead)
        {
            this->currentNode = this->currentNode->next; 
            delete this->currentNode->prev; // same as delete itHead;
            this->currentNode->prev = nullptr; // prev now points to nullptr
            this->currentNode = this->currentNode->prev; // same as nullptr
            this->itHead = this->currentNode; // Repoint head node

            this->pastStart = true;
            this->pastEnd = false;
        }
        else if (this->currentNode == this->itTail) // will delete tail node and point to node before original tail
        {
            this->currentNode = this->currentNode->prev; // go backwards to delete current / tail node
            delete this->currentNode->next; // delete original tail node
            this->currentNode->next = nullptr; 
            this->itTail = this->currentNode; // tail now refers to "new" tail
            
            this->pastEnd = false; // Update pastEnd to true because currentNode now points to nullptr after tail
        }
        // node is right before head
        else if (this->currentNode->prev == this->itHead) 
        {
            this->currentNode = this->currentNode->next; 
            delete this->currentNode->prev;
            this->currentNode->prev = this->itHead;
            this->itHead->next = this->currentNode;

            this->currentNode = this->itHead; 
        }
        // if currentNode is the last node in the DLL
        else if (this->currentNode->prev == nullptr && this->currentNode->next == nullptr)
        {
            delete this->currentNode;
            this->currentNode = this->itHead = this->itTail = nullptr;
            this->pastStart = true;
            this->pastEnd = true;
        }
        else // remove a body node if size > 1 since size == 1 is taken care of
        {
            Node* nodeBefore = this->currentNode->prev;
            Node* nodeAfter = this->currentNode->next;
            
            delete this->currentNode;
            nodeBefore->next = nodeAfter;
            nodeAfter->prev = nodeBefore;

            this->currentNode = nodeBefore;
        }
    }
    this->itSize--;
}

#endif

