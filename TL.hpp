#pragma once
#include <initializer_list>
#include <vector>
#include <memory>

namespace TL
{
    template<class T>
    class SinglyLinkedList
    {
    private:
        struct Node
        {
            T data;
            Node *next;

            Node(T data)
                : data(data), next(nullptr) {}
        };

        Node *head_;
        Node *tail_;

    public:
        class Iterator
        {
        private:
            Node *cur_;
        public:
            Iterator(Node *node)
                : cur_(node) { }
            
            bool operator!=(const Iterator& other)
            {
                return !(cur_==other.cur_);
            }

            T& operator*()
            {
                return cur_->data;
            }

            Iterator operator++()
            {
                cur_=cur_->next;
                return *this;
            }

        };

        Iterator begin() const
        {
            return Iterator(head_);
        }

        Iterator end() const
        {
            return Iterator(nullptr);
        }


    public:
        bool IsEmpty()
        {
            return head_==nullptr;
        }

        Node *Append(T data)
        {
            Node *new_node = new Node(data);

            if(IsEmpty())
            {
                head_ = tail_ = new_node;
            }
            else 
            {
                tail_->next = new_node;
                tail_ = new_node;
            }

            return new_node;
        }   

        Node *Prepend(T data)
        {
            Node *new_node = new Node(data);

            if(IsEmpty())
            {
                head_ = tail_ = new_node;
            }
            else
            {
                new_node->next = head_;
                head_ = new_node;
            }

            return new_node;
            
        }   

        Node *InsertAt(Node *dst, T data)
        {
            Node *new_node = new Node(data);

            Node *cur;

            for(cur = head_; cur->next != dst; cur=cur->next){}
            new_node->next = dst;
            cur->next = new_node;

            return new_node;
            
        }
        Node *InserAt(T dst, T data)
        {
            Node *new_node = new Node(data);

            Node *cur;

            for(cur = head_; cur->next->data != dst; cur=cur->next){}
            new_node->next = cur->next;
            cur->next = new_node;

            return new_node;
        }

        std::vector<T> GetData() const
        {
            std::vector<T> data_vec;

            for(auto data: *this)
            {  
                data_vec.push_back(data);
            }

            return data_vec;

        }

        void Clear()
        {
            Node *cur = head_;
            Node *next;

            while(cur != nullptr)
            {
                next=cur->next;
                delete cur;
                cur = next;
            }

            head_ = nullptr;
            tail_ = nullptr;
        }
    public:
        SinglyLinkedList()
            :head_(nullptr), tail_(nullptr) {}

        SinglyLinkedList(std::initializer_list<T> list)
            :head_(nullptr), tail_(nullptr)
        {
            for(auto data: list)
                Append(data);
        }

        SinglyLinkedList(const SinglyLinkedList<T>& other)
            :head_(nullptr), tail_(nullptr)
        {
            std::vector<T> data_list = std::move(other.GetData());

            for(auto data: data_list)
            {
                Append(data);    
            }

        }
        
        SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other)
        {
            Clear();
            std::vector<T> data_list = std::move(other.GetData());

            for(auto data: data_list)
            {
                Append(data);    
            }
            return *this;
        }



        ~SinglyLinkedList()
        {
            Node *cur = head_;
            Node *next;

            while(cur != nullptr)
            {
                next=cur->next;
                delete cur;
                cur = next;
            }

            head_ = nullptr;
            tail_ = nullptr;
        }

    };

}