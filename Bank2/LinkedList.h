#pragma once
#include "Node.h"
#include <iostream>
using namespace std;


template <class T> class LinkedList
{
public:
    LinkedList()
    {
        head = tail = NULL;
    }


    Node<T>* head, * tail;
    int index = 0;


    void Add(T c)
    {
        Node<T>* node = new Node <T>(c);

        if (head == NULL)
        {
            head = tail = node;
            node->index = index;
            index++;
        }
        else
        {
            tail->Next = node;
            node->Prev = tail;
            tail = node;
            node->index = index;
            index++;
        }
    }


    void Remove(T c)
    {
        Node<T>* node = GetNodeByData(c);
        Node<T>* nodeCopy = node;

        if (node == NULL)
            return;

        if (node == head)
        {
            if (node == tail)
            {
                head = tail = NULL;
            }
            else
            {
                head = head->Next;
                head->Prev = NULL;
            }
        }

        else if (node == tail)
        {
            tail = tail->Prev;
            tail->Next = NULL;
        }
        else
        {
            node->Prev->Next = node->Next;
            node->Next->Prev = node->Prev;
        }
        while (node->Next != NULL)
        {

            node->Next->index -= 1;
            node = node->Next;
        }
        node = nodeCopy;
        delete node;                 
    }
 
    void Swap(Node<T>* n1, Node<T>* n2)
    {
        T temp = n1->c;              
        n1->c = n2->c;
        n2->c = temp;
    }


    int bubbleSort()
    {
        int iterations = 0;
        if (head == NULL)
        {
            return 0;
        }

        int sorted = 0;
        for (int counter = 0; counter < index - 1 && sorted == 0; counter++)
        {

            sorted = 1;
            Node<T>* swappedItem = head;
            for (int i = 0; i < index - 1 - counter; i++)
            {
                if (swappedItem->c > swappedItem->Next->c)
                {
                    Swap(swappedItem, swappedItem->Next);
                    sorted = 0;
                }
                swappedItem = swappedItem->Next;
                iterations++;
            }
        }
    }



protected:

private:

    Node<T>* GetNodeByData(T c)
    {
        Node<T>* current = head;

        while (current != NULL)
        {
            if (c == current->c)
                return current;

            current = current->Next;
        }

        return NULL;
    }
};

