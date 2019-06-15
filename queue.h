#include <cstdint>
#include <stdexcept>

namespace structures {

    //! Fila encadeada
    template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

      //! limpar
    void clear();

      //! enfilerar
    void enqueue(const T& data);

      //! desenfilerar
    T dequeue();

      //! primeiro dado
    T& front() const;

      //! último dado
    T& back() const;

      //! fila vazia
    bool empty() const;

      //! tamanho
    std::size_t size() const;

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

        T& data() {  // getter: info
            return data_;
        }
        const T& data() const {  // getter-constante: info
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }
        const Node* next() const {  // getter-constante: próximo
            return next_;
        }

        void next(Node* next) {  // setter: próximo
            next_ = next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* head = nullptr;  //! nodo-cabeça
    Node* tail = nullptr;  //! nodo-fim
    std::size_t size_{0u};  //! tamanho
};

template<typename T>
LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}
template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    if (!empty())
        clear();
}
template<typename T>
void LinkedQueue<T>::clear() {
    if (!empty()) {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }
}
template<typename T>
void LinkedQueue<T>::enqueue(const T& data) {
    Node *elemento = new Node(data, nullptr);
    if (elemento == NULL)
        throw std::out_of_range("não há espaço");

    if (empty()) {
        head = elemento;
        tail = elemento;
    } else {
        tail->next(elemento);
        tail = tail->next();
    }
    size_++;
}
template<typename T>
T LinkedQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("lista vazia");
    Node *saiu;
    T valor;
    saiu = head;
    valor = head->data();
    head = head->next();
    if (size_ == 1)
        tail = nullptr;
    delete saiu;  // deleta só o ponteiro ou o elemento apontado também?
    size_--;
    return valor;
}
template<typename T>
T& LinkedQueue<T>::front() const {
    if (empty())
        throw std::out_of_range("lista vazia");
    return head->data();
}
template<typename T>
T& LinkedQueue<T>::back() const {
    if (empty())
        throw std::out_of_range("lista vazia");
    return tail->data();
}
template<typename T>
bool LinkedQueue<T>::empty() const {
    return !size_;
}
template<typename T>
std::size_t LinkedQueue<T>::size() const {
    return size_;
}
}  // namespace structures
