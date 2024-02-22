#pragma once
template <class T> class Node
{
public:
    T c;
    int index;        
    Node* Prev, * Next;
    Node(T c)
    {
        this->c = c;
        Prev = Next = NULL;
    }

protected:

private:
};

