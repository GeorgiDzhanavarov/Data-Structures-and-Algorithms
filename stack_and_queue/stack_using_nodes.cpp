struct Node {
    int data;
    Node *previous = nullptr;

    Node(int data, Node *previous = nullptr) {
        this->data = data;
        this->previous = previous;
    }
};

class Stack {
private:
    Node *top = nullptr;

    void copyStackRecursive(Node *current) {
        if (current != nullptr) {
            copyStackRecursive(current->previous);
            push(current->data);
        }
    }

public:
    Stack() {}

    void copy(const Stack &source) {
        copyStackRecursive(source.top);
    }

    void clear() {
        while (top != nullptr) {
            Node *previous = top->previous;
            delete top;
            top = previous;
        }
    }

    Stack(const Stack &source) {
        copy(source);
    }

    Stack &operator=(const Stack &source) {
        if (this != &source) {
            clear();
            copy(source);
        }

        return *this;
    }

    ~Stack() {
        clear();
    }

    void push(int number) {
        if (isEmpty()) {
            top = new Node(number);
        } else {
            Node *newTop = new Node(number, top);
            top = newTop;
        }
    }

    void pop() {
        if (!isEmpty()) {
            Node *oldTop = top;
            top = top->previous;
            delete oldTop;
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }

    int peek() const {
        if (!isEmpty()) {
            return top->data;
        } else {
            throw std::underflow_error("Stack is empty");
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};
