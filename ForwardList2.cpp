// LinkedListInherit21.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string.h>
#include <ostream>

using namespace std;

class Exception: public exception
{
protected:
	//сообщение об ошибке
	char* str;
public:
	Exception(const char* s)
	{
		str = new char[strlen(s) + 1];
		strlcpy(str, s, strlen(s) + 1);
	}
	Exception(char* s)
	{
		str = new char[strlen(s) + 1];
		strlcpy(str, s, strlen(s) + 1);
	}
	Exception()
	{
		str = NULL;
	}
	Exception(const Exception& e)
	{
		str = new char[strlen(e.str) + 1];
		strlcpy(str, e.str,strlen(e.str) + 1);
	}
	virtual ~Exception() _NOEXCEPT
	{
		delete[] str;
	}

	//функцию вывода можно будет переопределить в производных классах, когда будет ясна конкретика
	virtual void print()
	{
		cout << "Exception: " << str<< "; "<<what();
	}
};

template<class T>
class Element
{
protected:
	Element* next;
	T info;
public:
	Element(T data)
	{
		next = NULL;
		info = data;
	}

	Element(Element* Next, T data)
	{
		next = Next;
		info = data;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, Element<T1>& el);

	Element* getNext() { return next; }
	void setNext(Element* value) { next = value; }

	T getData() { return info; }
	void setData(T value) { info = value; }
};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}

template<class T>
class ForwardList
{
protected:
	Element<T>* head;
public:

	ForwardList()
	{
		head = NULL;
	}

    virtual Element<T>* pop()
	{
		if (head->next == NULL) 
		    return NULL;
		Element<T>* res=head;
		while (head!=res->next->next){
			res=res->next;
		}		
		Element<T>* p=res->next;
		res->next=head;
		delete p;
		return res;
	}
	virtual Element<T>* push(T value)
	{
		Element<T>* res=head;
		while (head!=res->next->next){
			res=res->next;
		}		
		Element<T>* p;
		p->info=value;
		p->next=head;
		res->next->next=p;
		return res;
	}

	T& operator[](int index) = 0;

	template<class T1>
	friend ostream& operator<<(ostream& s, ForwardList<T1>& el)
	{
		Element<T1>* res=el.head;
		while (el.head!=res->next){
            s << res->info << "; ";
			res=res->next;
		}
		return s;
	}
	virtual ~ForwardList()
	{
       
		if (head!=NULL){
		    Element<T>* alfa=head;
		    while (head!=alfa->next){
			    alfa=alfa->next;
		    }
			Element<T>* res = head;
			Element<T>* tmp = head->next;
			while (alfa!=tmp){
				delete res;
				res=tmp;
				tmp=tmp->next;
			}
			delete res;
			delete alfa;
		}
	}
};

/*В наследнике нужно доработать
template<class T>
class Myclass:public ForwardList
{
protected:
	Element<T>* head;
public:

	Myclass()
	{
		head = NULL;
	}

	virtual Element<T>* pop() = 0;
	virtual Element<T>* push(T value) = 0;

	T& operator[](int index) = 0;

	template<class T1>
	friend ostream& operator<<(ostream& s, Myclass<T1>& el);

	virtual ~Myclass()
	{
		
	}
};

int main()
{
	
	char c; cin >> c;
	return 0;
}
*/
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
