#include <iostream>
#include <vector>
#include <random>

template <class T>
class Stack
{
private:
	std::vector<T> data{};
	
public:
	Stack() = default;
	~Stack() = default;
	
	Stack(const std::vector<T>& vect):data(vect)
	{
    std::cout << "Stack initialized by vector\n";
	}

	Stack(const Stack& other) = default;

	Stack& operator=(const Stack& other) = default;

	T& top()
	{
		if (size() == 0)
		{
			throw std::runtime_error("Your stack is empty,there is no elem in top()\n");
		}
		return data[size() - 1];
	}

	std::size_t size() const
	{
		return data.size();
	}

	void push(const T& value)
	{
		data.push_back(value);
	}

	T pop()
	{
		if (size() == 0)
		{
			throw std::runtime_error("Your stack is empty,nothing to pop()");
		}
		T x = data[size() - 1];
		data.pop_back();
		return x;
	}


	bool empty()
	{
		return data.empty();
	}


	void swap(Stack& other)
	{
		data.swap(other.data);
		/*std::vector<T> tmp(stack);
		stack = other;
		other = tmp;*/
	}

	void print_stack()
	{
		for (T& x : data)
		{
			std::cout << x << " ";
		}
		std::cout << std::endl;
	}

};



int main()
{
	Stack<int> stack1;
	std::cout << "stack is empty: " << stack1.empty() << std::endl;
	for (int i = 0; i < 6; i++)
	{
		stack1.push(rand() % 10 + i);
	}
	std::cout << "stack1 looks: ";
	stack1.print_stack();
	std::cout << std::endl;
	std::cout << "top()    " << stack1.top() << std::endl;
	std::cout << "size->   " << stack1.size() << std::endl;
	std::cout << "pop()    " << stack1.pop() << std::endl;
	std::cout << "size->   " << stack1.size() << std::endl;
	std::cout << "top()    " << stack1.top() << std::endl << std::endl;

	Stack<int> other;
	std::cout << "other looks: ";
	other.print_stack();


	other = stack1;
	std::cout << "other looks: ";
	other.print_stack();
	std::cout << "other.pop():  " << other.pop() << "\n";

	Stack<int> any(other);
	std::cout << "any looks: ";
	any.print_stack();

	Stack<int> st;
	st = stack1;
	std::cout << "st looks: ";
	st.print_stack();
	st.push(63);
	st.push(45);
	std::cout << "st.push(63)\n" << "st.push(45)\n";
	std::cout << "st looks: ";
	st.print_stack();

	Stack<int> st1(st);
	std::cout << "st1 looks: ";
	st1.print_stack();
	std::cout << "st1.pop():  " << st1.pop() << "\n";
	std::cout << "st1.pop():  " << st1.pop() << "\n";
	std::cout << "st1.pop():  " << st1.pop() << "\n";
	std::cout << "st1 looks: ";
	st1.print_stack();

	Stack<int> st2;
	st2 = st1;
	std::cout << "st2 looks: ";
	st2.print_stack();
	st2.push(314);
	st2.push(53);
	std::cout << "st2 looks: ";
	st2.print_stack();

	std::cout << "\n\n";

	st2.swap(st1);
	std::cout << "st2 looks: ";
	st2.print_stack();
	std::cout << "st1 looks: ";
	st1.print_stack();

	std::cout << "\n\n";

	//Написать конструктор стэка, который получает вектор, и из него конструирует стэк
	std::cout << "Write stack constructor, which recieve vector, and from it copies stack\n";
	std::vector<int> x{ 1, 2, 3, 4, 5 };
	Stack<int> s{x};
	std::cout << "s{x} looks: ";
	s.print_stack();
	std::cout << "Expected: 5   Res: " << s.top() << "\n\n"; // expected: 5 

}