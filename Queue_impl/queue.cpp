#include <iostream>
#include <list>
#include <initializer_list>

template <class T>
class Queue {
private:
	std::list<T> data_list;
public:
	// Создает пустую очередь
	Queue() = default;

	// Создает новую очередь, являющююся глубокой копией очереди other [O(n)]
	Queue(const Queue& other) = default;

	Queue(const std::initializer_list<T>& init_list) :data_list{ init_list }
	{
		std::cout << "Initializer list Constructor !\n";
	}

	// Перезаписывает текущую очередь очередью other
	Queue& operator=(const Queue& other) = default;

	// Создает новую очередь перемещая существующую
	Queue(Queue&& other) :data_list(std::move(other.data_list)) {}

	// Перезаписывает текущую очередь очередью other
	Queue& operator=(Queue&& other)
	{
		data_list = std::move(other.data_list);
		return *this;
	}


	// Очищает память очереди
	~Queue() = default;

	// Возвращает размер очереди (сколько памяти уже занято)
	std::size_t size() const
	{
		return data_list.size();
	}

	// Проверяет является ли контейнер пустым
	bool empty()
	{
		return data_list.empty();
	}

	// Получает ссылку на первый элемент очереди
	T& front()
	{
		return data_list.front();
	}

	// Получает ссылку на последний элемент очереди
	T& back()
	{
		return data_list.back();
	}

	// Добавляет элемент в конец очереди.
	void push(const T& x)
	{
		data_list.push_back(x);
	}

	// Удаляет элемент из начала очереди. Возвращает удаленный элемент.
	T pop()
	{
		T value = front();
		data_list.pop_front();
		return value;
	}

	// Меняет содержимое с другой очередью. q1.swap(q2);
	void swap(Queue& other)
	{
		data_list.swap(other.data_list);
	}

	void print()const
	{
		for (auto it = data_list.begin(); it != data_list.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	template <class E>
	friend Queue<E>& merge(Queue<E>& first, Queue<E>& second);

	template <class C>
	friend std::ostream& operator<<(std::ostream& os, const Queue<C>& que);
};

template <class S>
std::ostream& operator<<(std::ostream& os, const Queue<S>& que)
{
	for (const auto& x : que.data_list)
	{
		os << x << " ";
	}
	os << std::endl;
	os << "Operator << successfully finished! \n";
	return os;
}


template <class Q>
Queue<Q> merge_t(Queue<Q>& first, Queue<Q>& second)
{
	Queue<Q> result;
	while (first.size() != 0 || second.size() != 0)
	{
		if (!first.empty())
		{
			result.push(first.pop());
		}
		if (!second.empty())
		{
			result.push(second.pop());
		}
	}
	std::cout << "MERGE end! \n";
	return result;
}

int main() {
	/*
	Queue<int> first;
	std::cout << "Empty first queue:   Expec: 1    Res: " << first.empty() <<"\n";
	std::cout << "Size of first:       Expec: 0    Res: " << first.size() <<"\n";
	for (int i = 1; i < 5; i++)
	{
		first.push(i);
		first.push(i * 2 +1);
	}
	std::cout << "first looks: ";
	first.print();
	std::cout << "Size of first:       Expec: 8    Res: " << first.size() << "\n";
	std::cout << "first.front():       Expec: 1    Res: " << first.front() << "\n";
	std::cout << "first.back():        Expec: 9    Res: " << first.back() << "\n";

	Queue<int> second(first);
	std::cout << "\nCopy Constructor !\n";
	std::cout << "second looks: ";
	second.print();
	std::cout << std::endl;

	first.back() = 63;
	std::cout << "back() = 63:         Expec: 63   Res: " << first.back() << "\n";
	first.front() = 111;
	std::cout << "front() = 111:       Expec: 111  Res: " << first.back() << "\n";

	std::cout << "first looks: ";
	first.print();

	std::cout << "pop():               Expec: 111  Res: " << first.pop() << "\n";

	std::cout << "first looks: ";
	first.print();

	std::cout << "pop():               Expec: 3    Res: " << first.pop() << "\n";

	std::cout << "first looks: ";
	first.print();
	std::cout << "second looks: ";
	second.print();

	std::cout << "\nSwaping first and second !\n";
	first.swap(second);

	std::cout << "first looks: ";
	first.print();
	std::cout << "second looks: ";
	second.print();

	std::cout << "\nMove Constructor !\n";

	Queue<int> third(std::move(first));
	std::cout << "Empty first queue:   Expec: 1    Res: " << first.empty() << "\n";
	std::cout << "Size of first:       Expec: 0    Res: " << first.size() << "\n";
	std::cout << "third looks: ";
	third.print();

	std::cout << "\nOperator= !\n";

	first = second;
	std::cout << "first looks: ";
	first.print();
	std::cout << "second looks: ";
	second.print(); */

	Queue<int> q0{ 1,2,3 };
	Queue<int> q1{ 4,5,6,7,8 };
	Queue<int> empt;
	std::cout << "q0 looks: " << q0 << std::endl;
	std::cout << "q1 looks: " << q1 << std::endl;
	Queue<int> q3 = merge_t(q0, q1);
	std::cout << "OUTPUT of merge be like:  1 4 2 5 3 6 7 8 \n";
	std::cout << "q3 looks: " << q3 << std::endl; // 1 4 2 5 3 6 7 8

	return 0;
}