#include "custom_vector.hpp"

int main()
{
	/*
	Vector<int> v1(7);
	std::cout << "size of v1 :         Expec:7  Res: " << v1.size() << std::endl;
	std::cout << "capacity of v1 :     Expec:15 Res: " << v1.capacity() << std::endl;
	std::cout << "v1 is empty :        Expec:0  Res: " << v1.empty() << std::endl;
	std::cout << "v1[0] :              Expec:0  Res: " << v1[0] << std::endl;
	v1.print();

	Vector<int> vector;
	vector.push_back(7);
	vector.push_back(12);
	vector.push_back(4);
	vector.push_back(66);
	vector.push_back(912);
	std::cout << "size of vector :     Expec: 5    Res: " << vector.size() << std::endl;
	std::cout << "capacity of vector : Expec: 7    Res: " << vector.capacity() << std::endl;
	std::cout << "vector is empty :    Expec: 0    Res: " << vector.empty() << std::endl;
	std::cout << "v[0],v[3] :          Expec: 7 66 Res: " << vector[0] << " " << vector[3] << std::endl;

	vector.print();
	std::cout << "pop_back 1 :         Expec: 912  Res: " << vector.pop_back() << std::endl;
	std::cout << "pop_back 2 :         Expec: 66   Res: " << vector.pop_back() << std::endl;
	vector.print();
	vector.insert(2, 42);
	std::cout << "insert(2,42) :       Expec: 42   Res: " << vector[2] << std::endl;
	vector.print();

	std::cout << "erase(1) :           Expec: 12   Res: " << vector.erase(1) << std::endl;
	std::cout << "size of vector :     Expec: 3    Res: " << vector.size() << std::endl;
	std::cout << "capacity of vector : Expec: 7    Res: " << vector.capacity() << std::endl;
	vector.print();

	for (int i = 0; i < 6; i++)
	{
		vector.push_back(rand() % 20);
	}
	std::cout << "capacity of vector : Expec: 15    Res: " << vector.capacity() << std::endl;
	std::cout << "size of vector  :    Expec: 9     Res: " << vector.size() << std::endl;
	std::cout << "v[0],v[1] :          Expec: 7 42  Res: " << vector[0] << " " << vector[1] << std::endl;

	std::cout << "\n\n";
	Vector<int> copy(vector);
	std::cout << "New Vector __copy__" << std::endl;
	std::cout << "Copy vector's :    ";
	copy.size_cap_info();
	std::cout << "copy vector looks: ";
	copy.print();
	std::cout << "copy.erase(1)      " << copy.erase(1) <<std::endl;
	std::cout << "copy.pop_back()    " << copy.pop_back() << std::endl;
	std::cout << "copy vector looks: ";
	copy.print();
	std::cout << "Copy vector's :    ";
	copy.size_cap_info();
	copy.push_back(314);
	std::cout << "push_back(314)     ";
	copy.print();
	copy.insert(4, 423);
	std::cout << "insert(4, 423)     ";
	copy.print();
	copy.insert(0, 241);
	std::cout << "insert(0,241)      ";
	copy.print();
	std::cout << "copy.erase(4)      " << copy.erase(4) << std::endl;
	std::cout << "copy vector looks: ";
	copy.print();
	std::cout << "Copy vector's :    ";
	copy.size_cap_info();

	std::cout << "\n\n";

	vector.print();
	vector.clear();
	std::cout << "Vector after clear!\n";
	std::cout << "Empty ? Expec: 1   Res: " <<vector.empty() << std::endl;
	std::cout << "Vector CLEARED" << std::endl;

	std::cout << "\n\n";

	Vector<int> x = copy;
	x.print();
	v1 = x;
	v1.print();
	v1 = vector;
	v1.print();
	std::cout <<"V1 became empty Expec:1 Res: "<< v1.empty() << std::endl;
	std::cout << "V1 vector's :    ";
	v1.size_cap_info();
	v1.resize(10);
	std::cout << "V1 vector's :    ";
	v1.size_cap_info();
	v1.resize(10);
	std::cout << "V1 vector's :    ";
	v1.size_cap_info();
	v1.resize(9);
	std::cout << "V1 vector's :    ";
	v1.size_cap_info();
	for (int i = 0; i < 14; i++)
	{
		v1.push_back(rand()%20);
	}
	v1.print();
	std::cout << "V1 vector's :    ";
	v1.size_cap_info();
	v1.resize(13);
	std::cout << "V1 vector's :    ";
	v1.size_cap_info();
	for (int i = 0; i < 4; i++)
	{
		v1.push_back(rand() % 20);
	}
	v1.print();
	std::cout << "V1 vector's :    ";
	v1.size_cap_info();*/

/*
	Vector<char> name;
	name.push_back('a');
	name.push_back('a');
	name.push_back('a');
	name.push_back('a');
	name.push_back('a');
	name.size_cap_info();
	name.print();
	Vector<char> another{ 5 };
	another.print(); // empty line , beacause "\0\0\0\0\0"
	another.size_cap_info();
	std::cout << "Equalation of 2 vectors: " << (name == another) << std::endl;
	another = name;
	std::cout << "Name-->";
	name.size_cap_info();
	name.print();
	std::cout << "Another-->";
	another.size_cap_info();
	another.print();
	std::cout << "Operator== Expec: 1  Res: " << (name == another) << std::endl;

	std::cout << "\n\n";

	Vector<char> symbols(name);
	std::cout << "Symbols-->";
	symbols.size_cap_info();
	std::cout << "Symbols looks: ";
	symbols.print();
	std::cout << "insert(3, 'c')" << std::endl;
	symbols.insert(3, 'c');
	std::cout << "Symbols looks: ";
	symbols.print();
	std::cout << "insert(3, 'd')" << std::endl;
	symbols.insert(3, 'd');
	std::cout << "Symbols looks: ";
	symbols.print();
	std::cout << "push_back('A') 5 times " << std::endl;
	symbols.push_back('A');
	symbols.push_back('A');
	symbols.push_back('A');
	symbols.push_back('A');
	symbols.push_back('A');
	std::cout << "Symbols looks: ";
	symbols.print();
	std::cout << "Symbols-->";
	symbols.size_cap_info();
	symbols.erase(3);
	std::cout << "erase(3)\n";
	std::cout << "Symbols looks: ";
	symbols.print();
	symbols.pop_back();
	std::cout << "pop_back()\n";
	std::cout << "Symbols looks: ";
	symbols.print();
	std::cout << "Symbols-->";
	symbols.size_cap_info();
	std::cout << "Symbols looks: ";
	symbols.print();
	symbols.resize(20);
	std::cout << "Symbols-->";
	symbols.size_cap_info();
	std::cout << "Symbols looks: ";
	symbols.print();
	symbols.resize(8);
	std::cout << "Symbols-->";
	symbols.size_cap_info();
	std::cout << "Symbols looks: ";
	symbols.print();

	

	std::cout << "\n\n";*/




	Vector<double> v0{0.0, 1.0, 2.0, 3.0, 4.0 ,5.5} ;
	std::cout << "New Vector<double>\n";
	v0.print();
	std::cout << "Double vector's-->";
	v0.size_cap_info();

	std::cout << "push_back(3.14)\n";
	v0.push_back(3.14);
	std::cout << "Vector looks: ";
	v0.print();

	std::cout << "push_back(6.6)\n";
	v0.push_back(6.6);
	std::cout << "Vector looks: ";
	v0.print();

	std::cout << "insert(v0.size()-1, 7.62)\n";
	v0.insert(v0.size()-1, 7.62);
	std::cout << "Vector looks: ";
	v0.print();

	std::cout << "pop_back()\n";
	v0.pop_back();
	std::cout << "Vector looks: ";
	v0.print();

	std::cout << "erase(3)\n";
	v0.erase(3);
	std::cout << "Vector looks: ";
	v0.print();

	std::cout << "Vector's : ";
	v0.size_cap_info();

	v0.resize(10);

	std::cout << "Vector's : ";
	v0.size_cap_info();

	std::cout << "Vector looks: ";
	v0.print();

	v0.resize(5);

	std::cout << "Vector's : ";
	v0.size_cap_info();

	std::cout << "Vector looks: ";
	v0.print();

	
	for (size_t i = 0; i < 10; i++)
	{
		v0.push_back(rand() % 30 + 0.5);
	}

	std::cout << "Vector's : ";
	v0.size_cap_info();

	std::cout << "Vector looks: ";
	v0.print();

	return 0;
}
