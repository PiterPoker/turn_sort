#include <iostream>

using namespace std;

int j = 50;


struct NumberSeries
{
	int index;                                

	void Input(NumberSeries &numberSeries);         
	NumberSeries *Right = NULL, *Left = NULL;                         
};

class List
{
	
public:
	int variant;
	NumberSeries *Head, *Last;                          
	List() :Head(NULL) {};
	~List();
	int DeleteLastItem(NumberSeries &numberSeries);
	void Add(NumberSeries &numberSeries);            
	void Show(NumberSeries &numberSeries);                           
	NumberSeries DeleteFirstItem(int index);
};


void NumberSeries::Input(NumberSeries &numberSeries)
{
	j = 50;
	j = (rand() % j)*pow(-1, rand() % 2 + 1);
	index = j;
}

List::~List()                              
{
	while (Head != NULL)                
	{
		NumberSeries *temp = Head->Right;    
		delete Head;                   
		Head = temp;                  
	}
}


void List::Add(NumberSeries &numberSeries)
{
	NumberSeries *temp = new NumberSeries;
	temp->Right = Head;
	temp->index = numberSeries.index;
	Head = temp;
	if (temp->Right == NULL)
		Last = temp;
	if (temp->Right != NULL)
		temp->Right->Left = temp;
}

int List::DeleteLastItem(NumberSeries &numberSeries)
{
	NumberSeries *tempR = &numberSeries;
	NumberSeries *tempL = tempR;
	int min = tempR->index;
	while (tempR->Right != NULL)
	{
		if (tempR->index>tempR->Right->index)
		{
			int index = tempR->index;
			tempR->index = tempR->Right->index;
			tempR->Right->index = index;
			DeleteLastItem(*tempR);
		}
		tempR = tempR->Right;
		if (min>tempR->index)
			min = tempR->index;
		if (11 == tempR->index)
			variant = tempR->index;
	}
	return min;
}


void List::Show(NumberSeries &numberSeries)
{
	NumberSeries *temp = &numberSeries;
	while (Head->Left != NULL)
	{
		Head = Head->Left;
		if (Head->Left == NULL)
			Show(*Head);
	}
	while (temp != NULL)
	{
		cout << temp->index << "\t";
		temp = temp->Right;
	}
}

NumberSeries List::DeleteFirstItem(int index)
{
	while (Head != NULL)
	{
		NumberSeries *temp = Head->Right;
		if (Head->index == index)
		{
			temp->Left = Head->Left;
			if (Head->Left != NULL)
				temp->Left->Right = Head->Right;
			delete Head;
			Head = temp;
			break;
		}
		Head = Head->Right;
	}
	return *Head;
}

int main()
{
	NumberSeries numberSeries;
	int N = 100, min;
	List lst;

	for (int i = 0; i <= N; i++)
	{
		numberSeries.Input(numberSeries);
		lst.Add(numberSeries);
	}

	cout << "Initial data:" << endl;
	lst.Show(*lst.Head);
	do
	{
		min = lst.DeleteLastItem(*lst.Head);
	} while (lst.Head->index > min);

	numberSeries = *lst.Head;
	while (numberSeries.Right != NULL)
	{
		if (numberSeries.index == numberSeries.Right->index)
		{
			numberSeries = lst.DeleteFirstItem(numberSeries.index);
			continue;
		}
		numberSeries = *numberSeries.Right;
	}
	cout << endl << "Result: variant " << lst.variant << endl;
	lst.Show(*lst.Head);
	cout << endl;
	system("pause");
	return 0;
}