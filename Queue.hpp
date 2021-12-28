// Queue.hpp
//
// ICS 46 Spring 2021
// Project #2: Time Waits for No One
//
// This is the complete implementation of a Queue<ValueType> class template,
// which implements a queue of objects.  It may seem a little bit odd that
// there's so little code, but it's because the class inherits all of its
// implementation details from the DoublyLinkedList<ValueType> class
// template that you'll be building.  Effectively, a queue is really just
// a more limited version of a linear data structure like an array or a
// linked list -- it's *some* things that an array or linked list is,
// but not everything.  The way we express a relationship like that in C++
// is to use private inheritance (i.e., inheritance that our Queue class
// template is aware of, but that no code elsewhere in the program is
// permitted to use).  Our implementation, then, is a set of member
// functions that call into DoublyLinkedList member functions, along with
// some "using" declarations that take some things that are declared in
// DoublyLinkedList and make them public members of Queue.
//
// While you can add things to this class if you'd like, DO NOT MODIFY THE
// PROVIDED CODE IN ANY WAY otherwise.  We will be running unit tests
// against this class template -- mainly as a way of validating that your
// DoublyLinkedList<ValueType> makes the correct assumptions -- and these
// will neither compile nor run if the public member functions below have
// changed in any way.  As we did in Project #0, we've provide you a
// basic set of unit tests that briefly demonstrate how each of the member
// functions is required to behave; you'll find those in the "gtest"
// directory.
//
// The entire C++ Standard Library is off-limits in your implementation
// of this class.  DO NOT submit a version of this file (or any file
// that it includes) that includes any C++ Standard Library headers.
// (This includes things like adding a print() member function that
// requires <iostream>.)

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "DoublyLinkedList.hpp"



template <typename ValueType>
class Queue : private DoublyLinkedList<ValueType>
{
public:
    // Note that the constructors, destructors, and assignment
    // operators are not declared here, because the defaults
    // will do precisely what we want them to, in this case:
    // Call the versions from the base class.  The only reason
    // you would need to add those declarations is if you
    // added something to this class template that required
    // initialization, cleanup, etc., which is unlikely.


    // enqueue() adds the given value to the back of the queue, after
    // all of the ones that are already stored within.
    void enqueue(const ValueType& value);

    // dequeue() removes the front value from the queue, if there is
    // one.  If the queue is empty, it throws an EmptyException instead.
    void dequeue();

    // front() returns the front value in the queue, if there is one.
    // If the queue is empty, it throws an EmptyException instead.
    const ValueType& front() const;


    // These members of DoublyLinkedList are being made into public
    // members of Queue.  Given a Queue object, you'd now be able to
    // call the isEmpty(), size(), or constIterator() member functions,
    // as well as say something like "Queue<int>::ConstIterator".
    //
    // Note that we don't need to implement these separately; the
    // implemenations from DoublyLinkedList are now a part of Queue.
    // All we're doing is making them public.

    using DoublyLinkedList<ValueType>::isEmpty;
    using DoublyLinkedList<ValueType>::size;

    using DoublyLinkedList<ValueType>::constIterator;
    using ConstIterator = typename DoublyLinkedList<ValueType>::ConstIterator;
};



template <typename ValueType>
void Queue<ValueType>::enqueue(const ValueType& value)
{
    // Note that it's not always necessary (or even preferable) to say "this->"
    // when you access an inherited member.  addToEnd() is part of the base
    // class (DoublyLinkedList), so you would expect to be able to say this:
    //
    //     addToEnd(value);
    //
    // However, in the presence of templates, things can get more complicated.
    // For example, there are stricter rules about how names are looked up.
    // One of those rules is that names in "dependent types" (i.e., types
    // that depend on what ValueType is, in the context of this function)
    // are not looked up by the compiler.  The reason why is a long story,
    // but revolves roughly around the idea that different instantiations of
    // the same template can have wildly different details sometimes.  So
    // the compiler will refuse to find addToEnd(), though it can find it if
    // give it a little more help with where to look.  "this->" is our way of
    // doing that; we're saying "You can expect to find addToEnd as a member
    // function of the current object."

    this->addToEnd(value);
}


template <typename ValueType>
void Queue<ValueType>::dequeue()
{
    this->removeFromStart();
}


template <typename ValueType>
const ValueType& Queue<ValueType>::front() const
{
    return this->first();
}



#endif

