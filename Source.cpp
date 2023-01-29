//#include <iostream>
//
//class ElectroFuel {
//public:
//	ElectroFuel() {
//		std::cout << "ElectroFuel()" << std::endl;
//	}
//	const std::string &getInfo() const {
//
//		return _info;
//	}
//private:
//	std::string _info = "ElectroFuel";
//};
//
//template <class T>
//class Vehicle {
//public:
//	Vehicle() {
//		std::cout << "Vehicle()" << std::endl;
//	}
//	void printInfo() {
//		std::cout << _fuel.getInfo() << std::endl;
//	}
//private:
//	T _fuel;
//};
//
//class ElectricBicycle : public Vehicle<ElectroFuel> {
//public:
//	ElectricBicycle(const std::string& name) : _name(name) {
//		std::cout << "Parametrized ElectricBicycle()" << std::endl;
//	}
//	void printName() {
//		std::cout << _name << std::endl;
//	}
//private:
//	std::string _name;
// };
//
//int main() {
//	ElectricBicycle eb("Kawasaki");
//
//}

#include <iostream>

class Parent {
public:
	virtual void sleep() {
		std::cout << "sleep()" << std::endl;
	}
	virtual ~Parent() {}
};

class Child : public Parent {
public:
	void sleep() override {
		std::cout << "child sleep()" << std::endl;
	}
	void gotoSchool() {
		std::cout << "gotoSchool()" << std::endl;
	}
};

void func(Parent derived_obj) {

}

int main() {
	Parent parent;
	Child child;

	// upcast (неявное преобразование типов разрешено)
	Parent *pParent = & child; // стэк
	Parent *pParent2 = new Child(); // куча
	// downcast 
	Child *pChild = (Child *)pParent;
	// C-style каст выполняет первый успешный каст
	// в порядке:
	// 
	// const_cast
	// static_cast
	// static_cast -> const_cast
	// reinterpret_cast
	// reinterpret_cast -> const_cast
	// 
	// Если классы в иерархии наследования не виртуальные
	// то можно кастовать (upcast/downcast) через static_cast
	Child *pChild2 = static_cast<Child *>(pParent);


	// downcast UB - так делать нельзя
	// Child *pChild2 = (Child *)&parent;

	pParent->sleep(); // sleep() non-virtual // child sleep() virtual
	pChild->sleep(); // child sleep()
	//pChild2->sleep(); // UB
	
	delete pParent2;


	// static_cast<new_type>(expression)
	int a = 5;
	std::cout << "a: " << a << std::endl;
	double b = static_cast<double>(a); // Раньше: double(a)
									   // или (double)a
	std::cout << "b: " << b << std::endl;

	int c = 6;
	const int *pC = &c;
	int *ppC = const_cast<int *>(pC);
	std::cout << "============\n";
	std::cout << *ppC << std::endl;
	*ppC = 4;
	std::cout << *ppC << " " << c << std::endl;

	// dynamic_cast<new-type>(expression)
	Child *pChild3 = dynamic_cast<Child *>(&parent);
	if (pChild3 == nullptr) {
		std::cout << "pChild3 is nullptr" << std::endl;
	}
	//Parent *pParent3 = new Child();
	//Child *pChild4 = dynamic_cast<Child *>(pParent3);
	//delete pParent3;

	try {
		Child &pChild5 = dynamic_cast<Child &>(parent);
	}
	catch (std::bad_cast& e) {
		std::cout << 
			"cast parent to child results in bad_cast" << std::endl;
		std::cout << e.what() << std::endl;
	}

}