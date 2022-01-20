// DoublyLinkedList.hpp
// A Doubly Linked List template class.
// All of the public member functions listed with "noexcept" in their
// signature never throw exceptions.
// All of the others have no memory has leaked and the contents
// of the list/iterator will not have visibly changed in the event that
// an exception has been thrown.


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
        // Accessible to the derived classes.
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


    Node* head;
    Node* tail;
    unsigned int sz;  // Size of DLL.
    unsigned int* pSZ = &sz; // Pointer to reference for use in IteratorBase and derived classes.
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

        // Set up for next possible node or nullptr if no more nodes to link.
        listCurrentNode = listCurrentNode->next;  // Could be nullptr or filled Node.

        // IF MORE THAN ONE NODE, LINK THE NODE TOGETHER BASED ON NODE COUNT/SIZE OF LIST (OTHER DLL).
        while(listCurrentNode != nullptr)
        {
            Node* thisPreviousNode = thisCurrentNode; 
            thisCurrentNode = thisCurrentNode->next;

            thisCurrentNode = new Node
                                    {
                                        listCurrentNode->value,
                                        thisPreviousNode, // Link back.
                                        nullptr
                                    };
            thisPreviousNode->next = thisCurrentNode; // Link forward.
        
            tail = thisCurrentNode;

            // Could be another node of list OR nullptr which will break while loop.
            listCurrentNode = listCurrentNode->next;
        }
        // After exiting the while loop, the head should point to the first node.

        sz = list.sz;  
    }
    // Catch exception/error, deallocate memory (to avoid memory leak), then re-throw exception/error.
    catch(...)
    {
        // Return to being empty with size = 0 and head/tail point to nullptr.
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
    Node* thisHead = head; // Stays pointing at original head.
    head = list.head; // Make our head point to other List.head.
    list.head = thisHead; 

    Node* thisTail = tail; // Stays pointing at original head
    tail = list.tail;
    list.tail = thisTail;

    // Swaps size but since size is statically allocated here, no real need to swap.
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
}

// Assignment operator
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

            // Set up for next possible node or nullptr if no more nodes to link.
            listCurrentNode = listCurrentNode->next;  // Could be nullptr or filled Node.

            // IF MORE THAN ONE NODE, LINK THE NODE TOGETHER BASED ON NODE COUNT/SIZE OF LIST (OTHER DLL).
            while(listCurrentNode != nullptr)
            {
                Node* thisPreviousNode = thisCurrentNode; 
                thisCurrentNode = thisCurrentNode->next;

                thisCurrentNode = new Node
                                        {
                                            listCurrentNode->value,
                                            thisPreviousNode, // Link back.
                                            nullptr
                                        };
                thisPreviousNode->next = thisCurrentNode; // Link forward.
            
                newTail = thisCurrentNode;

                // Could be another node of list OR nullptr which will break while loop.
                listCurrentNode = listCurrentNode->next;
            }

            // Delete all current nodes from this DLL if any exist.
            while (head != nullptr)
            {
                Node* tempNode = head;
                head = head->next;
                delete tempNode;
            }

            head = tail = nullptr;

            // Repoint head and tail to new DLL.
            head = newHead;
            tail = newTail;
            // this size = list size
            sz = list.sz;  
        } 
        // Catch exception/error, deallocate memory (to avoid memory leak), then re-throw exception/error.
        catch(...)
        {
            // Original head, tail, size stays intact.
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

// Move assigntment operator.
template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
    if (this != &list)
    {
        // Doesn't matter if other list is empty or not since ALL private member vars should be switched anyways.
        Node* tempNode = nullptr;

        tempNode = head; // Stays pointing at original head.
        head = list.head;
        list.head = tempNode;

        tempNode = tail; // Stays pointing at original head.
        tail = list.tail;
        list.tail = tempNode;

        // Swaps size.
        unsigned int tempSize;
        tempSize = sz;
        sz = list.sz;
        list.sz = tempSize;
    }
    return *this;
}


// Adds node to the front with a particular value and repoints head.
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
            // Can anything go wrong here in this try?  If it does, catch it and no memory is leaked.
            Node* tempNode = head;
            head->prev = newNode;
            head = newNode;

            head->value = value;
            head->prev = nullptr;
            head->next = tempNode;

            sz++;  // If the try has gotten this far, size will not throw an exception.
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

// Adds node to the back with a particular value and repoints tail.
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


// Remove node from end of the DLL and repoint tail.
template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
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


// Returns the value of the head (first node) that CANNOT change or be modified.
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

// Returns the value of the head (first node) that CAN change or be modified.
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


// Returns the value of the last (last node) that CANNOT change or be modified.
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


// Returns the value of the last (last node) that CAN change or be modified.
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

// Returns the size of the DLL that is modified in the DLL class and IteratorBase with its derived iterator classes.
template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
    return sz;
}


// Returns true of list is empty, false if not empty.
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


//
// Iterator member functions //
//


// Construct modifiable iterator.
template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
    return Iterator{*this};
}


// Construct constant iterator.
template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
    return ConstIterator{*this};
}


// Class that Iterator and ConstIterator derives from using the DLL.
template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
{
    itHead = list.head;
    itTail = list.tail;
    itSize = list.pSZ;

    // If list is empty.
    if (itHead == nullptr && itTail == nullptr)
    {
        itSize = 0;
        currentNode = nullptr;
        pastStart = true;
        pastEnd = true;
    }
    // If list is NOT empty.
    else // itHead will refer to the first value in the list.
    {
        pastStart = false;
        pastEnd = false;

        currentNode = itHead;
    }
}


// Current position moves to next node towards tail.
template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
    // If current position is nullptr after tail.
    if (currentNode == nullptr && pastStart == false && pastEnd == true) // CurrentNode is pastStart.
    {
        throw IteratorException{};
    }
    // If current position is nullptr before head, move to head.
    else if (currentNode == nullptr && pastStart == true && pastEnd == false)
    {
        currentNode = itHead;

        pastStart = false;
        pastEnd = false;
    }
    // If current position is node before tail, set to tail.
    else if (currentNode->next == itTail)
    {
        currentNode = itTail;

        pastStart = false;
        pastEnd = false;
    }
    // Current position from head to tail - 1
    else
    {
        currentNode = currentNode->next;

        // If current position IS the tail, it is now nullptr and pastEnd.
        if (currentNode == nullptr)
        {
            pastStart = false;
            pastEnd = true;
        }
    }
}


// Current position moves to next node towards head.
template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
    // If current position is nullptr before head.
    if (currentNode == nullptr && pastStart == true && pastEnd == false) // CurrentNode is pastStart.
    {
        throw IteratorException{};
    }
    // If current position is nullptr after tail, move to tail.
    else if (currentNode == nullptr && pastStart == false && pastEnd == true)
    {
        currentNode = itTail;
    
        pastStart = false;
        pastEnd = false;
    }
    // If current position is node BEFORE head, set head to this node.
    else if (currentNode->prev == itHead)
    {
        currentNode = itHead;

        pastStart = false;
        pastEnd = false;
    }
    // Current position from head + 1 to tail.
    else
    {
        currentNode = currentNode->prev;

        // If current position IS the head, it is now nullptr and pastStart.
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


// ConstIterator constructor taking in the DLL.
template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
}


// Returns the value of the current position in the ConstIterator.
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


// Iterator constructor taking in the DLL.
template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
}


// Returns the value of the current position of Iterator.
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


// Inserts new node before current position.
// Increases size of DLL by 1.
// DOES NOT move current position / currentNode .
template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
    // If current position is nullptr before head.
    if (this->pastStart == true && this->currentNode == nullptr)
    {
        throw IteratorException{};
    }
    // If current position IS head.
    else if (this->currentNode == this->itHead)
    {
        Node* insertedNode = new Node{value, nullptr, this->itHead};
        this->itHead->prev = insertedNode;

        // Repoint head to insertedNode.
        this->itHead = insertedNode;
    }
    // If current position is nullptr after tail.
    else if (this->pastEnd == true && this->currentNode == nullptr)
    {
        Node* insertedNode = new Node{value, this->itTail, nullptr};
        this->itTail->next = insertedNode;

        // Repoint tail to insertedNode.
        this->itTail = insertedNode;

        // PastEnd remains true.
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


// Inserts new node after current position.
// Increases size of DLL by 1.
// DOES NOT move current position / currentNode.
template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
    // If current position is nullptr after tail.
    if (this->pastEnd == true && this->currentNode == nullptr)
    {
        throw IteratorException{};
    }
    // If current position IS tail, insertedNode becomes new tail.
    else if (this->currentNode == this->itTail && this->pastEnd == false)
    {
        Node* insertedNode = new Node{value, this->itTail, nullptr};
        this->itTail->next = insertedNode;

        // Repoint tail to insertedNode.
        this->itTail = insertedNode;

        // // No longer necessary since size counts the nodes when
        // // the member function .size() is called.
        // //update size
        // itSize++;
    }
    // If current position is nullptr before head.
    else if (this->pastStart == true && this->currentNode == nullptr)
    {
        Node* insertedNode = new Node{value, nullptr, this->itHead};
        this->itHead->prev = insertedNode;

        // Repoint tail to insertedNode.
        this->itHead = insertedNode;

        // PastStart remains true.
    }
    else
    {
        Node* insertedNode = new Node{value, this->currentNode, this->currentNode->next};

        Node* nodeAfterInsert = this->currentNode->next;
        nodeAfterInsert->prev = insertedNode;

        this->currentNode->next = insertedNode;
    }
    this->itSize++;
}


// Removes a node and redetermines/updates head and tail pointers if neccesary.
// Decrease size of DLL by -1.
// Possible for currentNode to enter the pastStart or pastEnd position (aka nullptr).
template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
    if (this->pastStart == true || this->pastEnd == true)
    {
        throw IteratorException{};
    }
    else if (moveToNextAfterward == true) // So move after.
    {
        if (this->currentNode == this->itHead)
        {
            Node* tempNode = this->currentNode; // Point to original head position to delete later.
            this->currentNode = this->currentNode->next; // Repoint to node after head.
            this->currentNode->prev = nullptr; // Update for prev to point at pastStart / nullptr.
            this->itHead = this->currentNode; // Repoint to "new" head node.

            delete tempNode; // Delete the original head   .
        }
        else if (this->currentNode == this->itTail) // Will delete tail node and point to nullptr.
        {
            this->currentNode = this->currentNode->prev; // Go backwards to delete current / tail node.
            delete this->currentNode->next; // Delete original tail node.
            this->itTail = this->currentNode; // Tail now refers to "new" tail.
            this->currentNode->next = nullptr; // Update the next pointer of new tail node.
            this->currentNode = nullptr; // Current position is now pastEnd / correct position.
            
            this->pastEnd = true; // Update pastEnd to true because currentNode now points to nullptr after tail.
        }
        // node is right before tail
        else if (this->currentNode->next == this->itTail) 
        {
            this->currentNode = this->currentNode->prev; // Go backwards to delete current.
            delete this->currentNode->next; // Delete original tail node.
            this->currentNode->next = this->itTail;  // Tail should still have same value and same next (nullptr).
            this->itTail->prev = this->currentNode;

            this->currentNode = this->itTail;  
        }
        // If currentNode is the last node in the DLL.
        else if (this->currentNode->prev == nullptr && this->currentNode->next == nullptr)
        {
            delete this->currentNode;
            this->currentNode = this->itHead = this->itTail = nullptr;
            this->pastStart = true;
            this->pastEnd = true;

            //update size?
        }
        else // Remove a body node if size > 1 since size == 1 is taken care of.
        {
            Node* nodeBefore = this->currentNode->prev;
            Node* nodeAfter = this->currentNode->next;
            
            delete this->currentNode;
            nodeBefore->next = nodeAfter;
            nodeAfter->prev = nodeBefore;

            this->currentNode = nodeAfter;
        }
    }
    else if (moveToNextAfterward == false) // So move before.
    {
        if (this->currentNode == this->itHead)
        {
            this->currentNode = this->currentNode->next; 
            delete this->currentNode->prev; // Same as delete itHead.
            this->currentNode->prev = nullptr; // prev now points to nullptr.
            this->currentNode = this->currentNode->prev; // Same as nullptr.
            this->itHead = this->currentNode; // Repoint head node.

            this->pastStart = true;
            this->pastEnd = false;
        }
        else if (this->currentNode == this->itTail) // Will delete tail node and point to node before original tail.
        {
            this->currentNode = this->currentNode->prev; // Go backwards to delete current / tail node.
            delete this->currentNode->next; // Delete original tail node.
            this->currentNode->next = nullptr; 
            this->itTail = this->currentNode; // Tail now refers to "new" tail.
            
            this->pastEnd = false; // Update pastEnd to true because currentNode now points to nullptr after tail.
        }
        // Node is right before head.
        else if (this->currentNode->prev == this->itHead) 
        {
            this->currentNode = this->currentNode->next; 
            delete this->currentNode->prev;
            this->currentNode->prev = this->itHead;
            this->itHead->next = this->currentNode;

            this->currentNode = this->itHead; 
        }
        // If currentNode is the last node in the DLL.
        else if (this->currentNode->prev == nullptr && this->currentNode->next == nullptr)
        {
            delete this->currentNode;
            this->currentNode = this->itHead = this->itTail = nullptr;
            this->pastStart = true;
            this->pastEnd = true;
        }
        else // Remove a body node if size > 1 since size == 1 is taken care of.
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

