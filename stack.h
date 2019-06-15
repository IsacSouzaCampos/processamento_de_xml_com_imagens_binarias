#include <cstdint>
#include <stdexcept>

namespace structures {

typedef struct {
  int x = 0;
  int y = 0;
} coordenada_t;

//! implementacao de pilha encadeada
template<typename T>
class LinkedStack {
 public:
    //! construtor da pilha encadeada
    LinkedStack();
    //! destrutor
    ~LinkedStack();
    //! ...
    void clear();  // limpa pilha
    //! ...
    void push(const T& data);  // empilha
    //! ...
    T pop();  // desempilha
    //! ...
    T& top() const;  // dado no topo
    //! ...
    bool empty() const;  // pilha vazia
    //! ...
    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

template<typename T>
LinkedStack<T>::LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    clear();
}

template <typename T>
void LinkedStack<T>::clear() {
    while (!empty())
        pop();
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::push(const T& data) {
    Node *new_element = new Node(data, nullptr);
    if (new_element == nullptr)
        throw std::out_of_range("não há espaço");
    if (!empty())
        new_element -> next(top_);
    top_ = new_element;
    size_++;
}

template<typename T>
T LinkedStack<T>::pop() {
    if (empty())
        throw std::out_of_range("lista vazia");
    Node *elemento_saindo = top_;
    if (size_ == 1) {
        top_ = nullptr;
    } else {
        top_ = top_->next();
    }
    size_--;
    T volta = elemento_saindo->data();
    delete(elemento_saindo);
    return volta;
}


template<typename T>
T& LinkedStack<T>::top() const {
    if (empty())
        throw std::out_of_range("lista vazia");
    return top_->data();
}

template<typename T>
bool LinkedStack<T>::empty() const {
    return !size_;
}

template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

}  // namespace structures
