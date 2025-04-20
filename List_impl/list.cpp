#include <iostream>
#include <initializer_list>
#include <iterator>


template <class T>
class List {
private:   
    //NODE  STRUCTURE//
    //value//prev//next
    struct Node
    {
        T value;
        Node* prev;
        Node* next;

        Node(const T& value_ = T(),Node* prev_ = nullptr,Node* next_ = nullptr):
            value(value_),prev(prev_),next(next_) {}
    };
    ////////////////////
    Node* head = nullptr;
    Node* tail = nullptr;
    std::size_t list_size = 0;
public:
    class Iterator;
    // Создает список размера count заполненный дефолтными значениями типа T
    List(std::size_t count = 0)  {
        while (count)
        {
            push_back(T{});
            count--;
        }
    }

    List(const std::initializer_list<T>& init_list)
    {
        for (const auto& x : init_list)
        {
            push_back(x);
        }
        std::cout << "Initializer list CONSTRUCTOR !\n";
    }

    // Создает новый список, являющийся  глубокой копией списка other [O(n)]
    List(const List& other)
    {
        for (const auto& x : other)
        {
            push_back(x);
        }
        std::cout << "COPY CONSTRUCTOR!\n";
    }

    // Перезаписывает текущий список списком other
    // List l1{5}, l2{10};
    // l1 = l2;
    // std::cout << l1.size() == 10 << std::endl // True
    List& operator=(const List& other)
    {
            head = nullptr;
            tail = nullptr;
            list_size = 0;
            for (const auto& x : other)
            {
                push_back(x);
            }
        std::cout << "OPERATOR= !\n";
        return *this;
    }

    // Очищает память списка [O(n)]
    ~List()
    {
        while (list_size)
        {
            pop_back();
        }
        std::cout << "DESTRUCTOR !\n";
    }

    template <class E>
    friend std::ostream& operator<<(std::ostream& os, const List<E>& list);
    

    // Возвращает размер списка (сколько памяти уже занято)
    std::size_t size() const
    {
        return list_size;
    }

    // Проверяет является ли контейнер пустым
    bool empty()
    {
        return list_size == 0;
    }

    // Возвращает итератор на первый элемент
    // https://en.cppreference.com/w/cpp/container/list/begin
    Iterator begin() const
    {
        return Iterator{ head };
    }

    // Возвращает итератор обозначающий конец контейнера
    Iterator end() const
    {
        return Iterator{ tail->next };
    }

    // Возвращает копию элемента по индексу
    T operator[](std::size_t index) const
    {
        if (index >= list_size)
        {
            throw std::runtime_error("Your index is Invalid !\n");
        }
        int i = 0;
        for (auto it = begin(); it != end(); ++it)
        {
            if (i == index)
            {
                return *it;
            }
            i++;
        }
    }

    // Возвращает ссылку на элемент по индексу (позволяет менять элемент, типа
    // v[5] = 42;)
    T& operator[](std::size_t index)
    {
        if (index >= list_size)
        {
            throw std::runtime_error("Your index is Invalid !\n");
        }
        int i = 0;
        for (auto it = begin(); it != end(); ++it)
        {
            if (i == index)
            {
                return *it;
            }
            i++;
        }
    }

    // Добавляет элемент в конец списока.
    void push_back(const T& x)
    {
        if (tail == nullptr)
        {
            Node* new_block = new Node(x);
            tail = new_block;
            head = new_block;
        }
        else
        {
            Node* new_block = new Node(x,tail);
            tail->next = new_block;
            tail = new_block;
        }
        list_size++;
    }

    // Добавляет элемент в начало списока.
    void push_front(const T& x)
    {
        if (head == nullptr)
        {
            Node* new_block = new Node(x);
            head = new_block;
            tail = new_block;
        }
        else
        {
            Node* new_block = new Node(x, nullptr, head);
            head->prev = new_block;
            head = new_block;
        }
        list_size++;
    }

    // Удаляет последний элемент списока.
    T pop_back()
    {
        if (list_size == 0)
        {
            throw std::runtime_error("Your list is empty.Nothing to pop_back\n");
        }
        T poped = tail->value;
        Node* temp = tail;

        if (list_size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        list_size--;

        return poped;
    }

    // Удаляет первый элемент списока.
    T pop_front()
    {
        if (list_size == 0)
        {
            throw std::runtime_error("Your list is empty.Nothing to pop_front\n");
        }
        T poped = head->value;
        Node* temp = head;

        if (list_size == 1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        list_size--;

        return poped;
    }

    // Вставляет новый элемент value перед элементом, на который указывает it.
    //     it
    //     v
    // [1, 2, 3].insert(it, 42) -> [1, 42, 2, 3]
    void insert(Iterator it, T value)
    {
        if (it.current == nullptr)
        {
            throw std::runtime_error("Your itertor is invalid!\n");
        }
        else if (it.current == head)
        {
            push_front(value);
        }
        else if (it.current == tail->next)
        {
            push_back(value);
        }
        
        Node* temp = new Node{ value,it.current->prev,it.current };
        it.current->prev->next = temp;
        it.current->prev = temp;

    }

    //     it
    //     v
    // [1, 2, 3].erase(it) -> [1, 3] (return 2)
    T erase(Iterator it)
    {
        if (it.current == nullptr)
        {
            throw std::runtime_error("Your iterator is invalid!\n");
        }
        else if (it.current == head)
        {
            return pop_front();
        }
        else if (it.current == tail)
        {
            return pop_back();
        }
        T erased_elem = it.current->value;
        it.current->next->prev = it.current->prev;
        it.current->prev->next = it.current->next;

        delete it.current;
        list_size--;

        return erased_elem;
    }

    
    void erase(const Iterator& start_it,const Iterator& end_it)
    {
      std::cout << "Overloaded erase begining! \n";
        for (auto it = start_it; it != end_it; ++it)
        {
            erase(it);
        }
      std::cout << "Overloaded erase successfully finished! \n";
      
    }


    void print() const
    {
        Node* current = head;
        while (current != nullptr)
        {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
      delete current;
    }

    // Класс, который позволяет итерироваться по контейнеру.
    // Я указал минимальный набор операций
    class Iterator {
    public:
        Node* current;

        // Инкремент. Движение к следующему элементу. ++it
        Iterator& operator++()
        {
            if (current == nullptr)
            {
                throw std::runtime_error("++ : Your iterator is out of list\n");
            }
            current = current->next;
            return *this;
        }

        // Декремент. Движение к предыдущему элементу. --it
        Iterator& operator--()
        {
            if (current == nullptr)
            {
                throw std::runtime_error("-- : Your iterator is out of list\n");
            }
            current = current->prev;
            return *this;
        }

        // Проверка на неравенство двух итераторов. Обычно используется it !=
        // container.end().
        bool operator!=(const Iterator& other)
        {
            return current != other.current;
        }

        // разыменование (как с указателями): *it = 42; или std::cout << *it;
        T& operator*()
        {
            if (current == nullptr)
            {
                throw std::runtime_error("Invalid iterator,you haven't element here\n");
            }
            return current->value;
        }
    };
};


template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list)
{
    //os << "operator<< BEGIN !\n";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        os << *it << " ";
    }
    os << "\n";
    os << "operator<< Succesfully END !\n";
    return os;
}


int main() 
{
  /*  List<int> l1(5);
    std::cout << "Empty list l1 looks: ";
    l1.print();

    std::cout << "Empty():   Expec: 0  Res: " << l1.empty() << '\n';

    std::cout << "Size of l1:     Expec: 5   Res: " << l1.size() << '\n';
    l1.push_back(5);
    std::cout << "List l1 looks:push_back(5) ";
    l1.print();

    l1[3] = 63;
    std::cout << "List l1 looks:l1[3] =_63_ ";
    l1.print();

    l1.push_front(77);
    std::cout << "List l1 looks:push_front(77) ";
    l1.print();


    std::cout << "Size of l1:     Expec: 7   Res: " << l1.size() << '\n';
   
    std::cout << "Print list with iterators: ";
    for (auto it = l1.begin(); it != l1.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    auto start = l1.begin();

    l1.pop_back();
    std::cout << "List l1 looks:pop_back() ";
    l1.print();

    l1.insert(++start, 8);
    std::cout << "List l1 looks:insert(++start, 8) ";
    l1.print();

    l1[3] = 13;
    std::cout << "List l1 looks:l1[3] =_13_ ";
    l1.print();

    l1.pop_front();
    std::cout << "List l1 looks:pop_front() ";
    l1.print();

    
    l1.erase(++start);
    std::cout << "List l1 looks:erase(++start) ";
    l1.print();

    std::cout << "\n\n\n";

    std::cout << "List l1 looks: ";
    l1.print();

    List<int> first(l1);
    std::cout << " List<int> first(l1) looks: ";
    first.print();

    first.push_back(23);
    first.push_front(1);

    l1 = first;
    std::cout << "l1 = first looks: \n";
    std::cout << "l1: ";
    l1.print();
    std::cout << "first: ";
    first.print();*/
    List<int> l0{1,2,3,4,5};
    l0.print();
    auto start_it = l0.begin();
    //std::advance(start_it, 1); // на 2ку
    ++start_it;
    std::cout << "Show on _2_:   Res: " << * start_it << std::endl;
    auto end_it = l0.begin();
    //std::advance(end_it, 3); // на 4ку
    ++++++end_it;
    std::cout << "Show on _4_:   Res: " << *end_it << std::endl;

    l0.erase(start_it, end_it);
    std::cout << "Expec: 1 4 5   Res: "<< l0 << std::endl; // 1 4 5 


    return 0;
}
