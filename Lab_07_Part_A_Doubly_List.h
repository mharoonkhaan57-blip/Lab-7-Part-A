#ifndef LAB07_PART_A_DOUBLY_LIST_H
#define LAB07_PART_A_DOUBLY_LIST_H

/* Name: M.Haroon-Ur-Rasheed Khan | Reg. No: Ai-9 | Subject: DSA | Sec: A */
// Lab 07 Part A: Menu-driven doubly linked list

#include <iostream>
#include <string>

using namespace std;

struct dNode
{
    int id;
    string title;
    dNode* left;
    dNode* right;

    dNode(int bookID, const string& bookTitle)
        : id(bookID), title(bookTitle), left(nullptr), right(nullptr) {}
};

class DoublyLinkedList
{
private:
    dNode* head;
    dNode* tail;
    dNode* current;

    void clear()
    {
        while (head != nullptr)
        {
            dNode* removed = RemoveCurrent();
            delete removed;
        }
    }

    void copyFrom(const DoublyLinkedList& other)
    {
        for (dNode* node = other.head; node != nullptr; node = node->right)
            InsertRight(new dNode(node->id, node->title));
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    DoublyLinkedList(const DoublyLinkedList& other)
        : head(nullptr), tail(nullptr), current(nullptr)
    {
        copyFrom(other);
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other)
    {
        if (this != &other)
        {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    ~DoublyLinkedList() { clear(); }

    bool IsEmpty() const { return head == nullptr; }
    bool IsNotEmpty() const { return head != nullptr; }

    void InsertRight(dNode* node)
    {
        if (node == nullptr)
            return;

        node->left = tail;
        node->right = nullptr;

        if (tail != nullptr)
            tail->right = node;
        else
            head = node;

        tail = node;
        if (current == nullptr)
            current = node;
    }

    void Next()
    {
        if (current != nullptr && current->right != nullptr)
            current = current->right;
        else
            cout << "No next book.\n";
    }

    void Previous()
    {
        if (current != nullptr && current->left != nullptr)
            current = current->left;
        else
            cout << "No previous book.\n";
    }

    void PrintCurrent() const
    {
        if (current == nullptr)
            cout << "Borrowing session is empty.\n";
        else
            cout << "Current book: " << current->id
                 << " - " << current->title << '\n';
    }

    void InsertAfterCurrent(dNode* node)
    {
        if (node == nullptr)
            return;

        if (current == nullptr)
        {
            InsertRight(node);
            return;
        }

        node->left = current;
        node->right = current->right;

        if (current->right != nullptr)
            current->right->left = node;
        else
            tail = node;

        current->right = node;
    }

    dNode* RemoveCurrent()
    {
        if (current == nullptr)
            return nullptr;

        dNode* removed = current;
        dNode* previous = removed->left;
        dNode* next = removed->right;

        if (previous != nullptr)
            previous->right = next;
        else
            head = next;

        if (next != nullptr)
            next->left = previous;
        else
            tail = previous;

        current = (next != nullptr) ? next : previous;
        removed->left = nullptr;
        removed->right = nullptr;
        return removed;
    }

    void PrintForward() const
    {
        cout << "\nBorrowing Session (First to Last):\n";
        for (dNode* node = head; node != nullptr; node = node->right)
        {
            cout << node->id << " - " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << '\n';
        }
    }

    void PrintBackward() const
    {
        cout << "\nBorrowing Session (Last to First):\n";
        for (dNode* node = tail; node != nullptr; node = node->left)
        {
            cout << node->id << " - " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << '\n';
        }
    }
};

#endif
