#include <iostream>
#include <cstdlib> // For system()
using namespace std;

template<typename T>
class DoublyLinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
    };
    Node* head;

public:
    DoublyLinkedList()
        : head(nullptr) {}

    void sortedInsert(T value)
    {
        Node* newNode = new Node{ value, nullptr, nullptr };

        if (!head)
        {
            head = newNode;
            return;
        }

        if (value < head->data)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next && temp->next->data < value)
        {
            temp = temp->next;
        }

        newNode->next = temp->next;
        if (temp->next)
        {
            temp->next->prev = newNode;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    void deleteNode(T value)
    {
        if (!head)
            return;

        Node* temp = head;

        if (head->data == value)
        {
            head = head->next;
            if (head)
            {
                head->prev = nullptr;
            }
            delete temp;
            return;
        }

        while (temp && temp->data != value)
        {
            temp = temp->next;
        }
        if (!temp)
            return;

        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        delete temp;
    }

    void displayForward() const
    {
        Node* temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void displayBackward() const
    {
        if (!head)
            return;

        Node* temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }

        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    bool search(T value) const
    {
        Node* temp = head;
        int pos = 1;
        while (temp)
        {
            if (temp->data == value)
            {
                cout << "Value " << value << " found at position " << pos << endl;
                return true;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Value " << value << " not found." << endl;
        return false;
    }

    void deleteAll()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~DoublyLinkedList()
    {
        deleteAll();
    }
};


int main()
{
    DoublyLinkedList<int> list;
    int choice, value;

    do
    {
        
        cout << "Implementation of Doubly Linked List\n";
        cout << "\n1. Insert (Sorted)"
            << "\n2. Delete"
            << "\n3. Display (Forward)"
            << "\n4. Display (Backward)"
            << "\n5. Search"
            << "\n6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            list.sortedInsert(value);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            list.deleteNode(value);
            break;
        case 3:
            cout << "List (Forward): ";
            list.displayForward();
            break;
        case 4:
            cout << "List (Backward): ";
            list.displayBackward();
            break;
        case 5:
            cout << "Enter value to search: ";
            cin >> value;
            list.search(value);
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
