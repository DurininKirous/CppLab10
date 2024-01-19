#include <stdarg.h>
#include <iostream>
#include <string>
template <typename T>
class MyPriorityQueue {
	T *Queue;
	size_t NumberOfElements;
	//----------------------
	void UpdatePriority()
	{
		bool ChangeStatus=true;
		T tmp;
		while ( ChangeStatus )
		{
			ChangeStatus=false;
			for ( size_t i=1; i<NumberOfElements; ++i )
			{
				if ( Queue[i-1] > Queue[i] )
				{
					tmp=Queue[i-1];
					Queue[i-1]=Queue[i];
					Queue[i]=tmp;
					ChangeStatus=true;
				}
			}
		}
	}

public:
	friend std::ostream &operator <<(std::ostream &out, MyPriorityQueue& NewQueue)
	{
		for (  size_t i=0; i<NewQueue.NumberOfElements; ++i)
		{
			out << NewQueue.Queue[i] << " ";
		}
		out << std::endl;
		return out;
	}
	
	MyPriorityQueue( size_t N, T Element, ... ): Queue(NULL), NumberOfElements(N)
	{
		if ( N==0 )
		{
			Queue = new T [1];
		}
		else if ( N > 0 )
		{	
			Queue=new T [N];
			va_list ptr;
			va_start( ptr, Element );
			for ( size_t i=0; i<N; ++i )
			{
				Queue[i]=Element;
				if (sizeof(T)<4)
				{
					Element=va_arg(ptr, int);
				}
				else Element=va_arg(ptr, T);
			}
			va_end(ptr);
			(*this).UpdatePriority();
		}
		else 
		{
			std::cerr << "Error! Choose another Number.";
		}
	}
	MyPriorityQueue(): Queue(NULL), NumberOfElements(0)
	{
		Queue=new T [1];
	}
	void push(T item)
	{
		T *Queue_new=new T [NumberOfElements+1];
		for ( size_t i=0; i<NumberOfElements; ++i )
		{
			Queue_new[i]=Queue[i];
		}
		Queue_new[NumberOfElements]=item;
		delete[] Queue;
		Queue=Queue_new;
		NumberOfElements+=1;
		(*this).UpdatePriority();
	}

	T peek()
	{
		return Queue[NumberOfElements-1];
	}

	T pop()
	{	
		T *Queue_new=new T [NumberOfElements-1];
		T ReturnElement=Queue[NumberOfElements-1];
		for ( size_t i=0; i<NumberOfElements-1; ++i )
		{
			Queue_new[i]=Queue[i];
		}
		delete[] Queue;
		Queue=Queue_new;
		NumberOfElements-=1;
		return ReturnElement;
	}

	size_t size()
	{
		return NumberOfElements;
	}

};

int main()
{
	MyPriorityQueue<char> First;
	std::cout <<"Current queue: " <<First; //Empty
	First.push('i');
	First.push('d');
	std::cout <<"Current queue: "<<First;
	std::cout <<"First element of queue (pop): " <<First.pop()<<std::endl;
	std::cout << "Current queue: " << First;
	First.push('m');
	std::cout <<"Current queue: "<<First;
	std::cout <<"First element of queue: "<<First.peek()<<std::endl;
	std::cout <<"Size of queue: "<<First.size()<<std::endl;
	std::cout <<"----------------------------------------------\n";
	MyPriorityQueue Second(5, 5.1, 7.2, 3.9, 3.1, 5.0);
	std::cout <<"Current queue: " <<Second;
	First.push(10.1);
	First.push(1.5);
	std::cout <<"Current queue: "<<Second;
	std::cout <<"First element of queue (pop): " <<Second.pop()<<std::endl;
	std::cout << "Current queue: " << Second;
	Second.push(6.3);
	std::cout <<"Current queue: "<<Second;
	std::cout <<"First element of queue: "<<Second.peek()<<std::endl;
	std::cout <<"Size of queue: "<<Second.size()<<std::endl;
	std::cout <<"----------------------------------------------\n";
	MyPriorityQueue<int> Third;
	std::cout <<"Current queue: " <<Third; //Empty
	Third.push(15);
	Third.push(10);
	std::cout <<"Current queue: "<<Third;
	std::cout <<"First element of queue (pop): " <<Third.pop()<<std::endl;
	std::cout << "Current queue: " << Third;
	Third.push(12);
	std::cout <<"Current queue: "<<Third;
	std::cout <<"First element of queue: "<<Third.peek()<<std::endl;
	std::cout <<"Size of queue: "<<Third.size()<<std::endl;
	std::cout <<"----------------------------------------------\n";
	MyPriorityQueue<std::string> Fourth;
	std::cout <<"Current queue: " <<Fourth; //Empty
	Fourth.push("World");
	Fourth.push("Alexey");
	std::cout <<"Current queue: "<<Fourth;
	std::cout <<"First element of queue (pop): " <<Fourth.pop()<<std::endl;
	std::cout << "Current queue: " << Fourth;
	std::cout <<"Current queue: "<<Fourth;
	Fourth.push("Success");
	std::cout <<"First element of queue: "<<Fourth.peek()<<std::endl;
	std::cout <<"Size of queue: "<<Fourth.size()<<std::endl;
	return 0;
}
