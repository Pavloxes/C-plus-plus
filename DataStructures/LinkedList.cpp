#include <iostream>
#include <vector>

using namespace std;

typedef int my_type;

template <typename Type>
class linked_list
{
private:
	struct Node
	{
		Type data;
		struct Node* prev, * next;

		Node() {};
		Node(Type const& data) : data(data), prev(nullptr), next(nullptr) {};

		friend ostream& operator<<(ostream& out, Node& node)
		{
			return out << node.data;
		}
	};

	Node* head = nullptr, * cur_ptr = nullptr;
	int size = 0, cur_ind = 0;

	//вставляет элемент перед головой списка
	void push_front(Type val)
	{
		Node* new_node = new Node(val);

		if (head == nullptr)
		{
			new_node->prev = new_node;
			new_node->next = new_node;
		}
		else
		{
			new_node->next = head;
			new_node->prev = head->prev;
			head->prev->next = new_node;
			head->prev = new_node;
		}

		head = new_node;
		cur_ptr = head;
		cur_ind = 0;

		size++;
	}

	int through_mid(int ind)
	{
		return abs(cur_ind - ind);
	}

	//возвращает элемент с индексом ind (идёт по кратчайшему пути в циклическом списке)
	Node* go_to(int ind)
	{
		int m = through_mid(ind), h = size - m;
		if (ind < cur_ind)//если запрашиваемый индекс левее, чем текущий индекс
		{
			if (m < h)//если через центр идти быстрее чем через голову
			{
				for (int i = 0; i < m; ++i)//идём влево
				{
					cur_ptr = cur_ptr->prev;
				}
			}
			else
			{
				for (int i = 0; i < h; ++i)//иначе идём вправо
				{
					cur_ptr = cur_ptr->next;
				}
			}
		}
		else//если правее
		{
			if (m < h)//если через центр идти быстрее чем через голову
			{
				for (int i = 0; i < m; ++i)//идём вправо
				{
					cur_ptr = cur_ptr->next;
				}
			}
			else
			{
				for (int i = 0; i < h; ++i)//иначе идём влево
				{
					cur_ptr = cur_ptr->prev;
				}
			}
		}

		return cur_ptr;
	}

public:

	//вставляет в список на позицию ind элемент val
	void push_at(int ind, Type val)
	{
		ind %= size + 1;
		head = go_to(ind);
		push_front(val);
		cur_ind = ind;
	}

	//удаляет элемент на позиции ind
	void erase_at(int ind)
	{
		ind %= size + 1;
		Node* to_erase = go_to(ind);
		head = to_erase->next;

		to_erase->next->prev = to_erase->prev;
		to_erase->prev->next = to_erase->next;
		to_erase->prev = nullptr;
		to_erase->next = nullptr;

		cur_ptr = head;
		cur_ind = ind;
		size--;
	}

	//возвращает значение на позиции ind
	Type get(int ind)
	{
		ind %= size + 1;
		Type ans = go_to(ind)->data;
		cur_ind = ind;
		return ans;
	}

	//выводит список начиная с 0 позиции
	void print()
	{
		cur_ptr = go_to(0);
		cur_ind = 0;
		for (int i = 0; i < size; ++i)
		{
			cout << cur_ptr->data << ' ';
			cur_ptr = cur_ptr->next;
		}
		cout << '\n';
	}
};

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	linked_list<int>my_linked_list;
	int n = 5;
	//Вставим в начало списка элемент {5, 4, 3, 2, 1}
	for (int i = 0; i < n; ++i)
	{
		my_linked_list.push_at(0, i + 1);
	}
	my_linked_list.print();
	//Вставим элемент 17 на позицию 2
	my_linked_list.push_at(2, 17);
	my_linked_list.print();
	//Удалим элемент на 3 позиции
	my_linked_list.erase_at(3);
	my_linked_list.print();

	cout << "You want to try my linked_list?\n[y/N]\n";
	char ans;
	cin >> ans;
	if (ans == 'y')
	{
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			string query;
			cin >> query;
			if (query == "c")
			{
				my_linked_list.print();
			}
			if (query == "p")
			{
				int val, ind;
				cin >> ind >> val;
				my_linked_list.push_at(ind, val);
			}
			if (query == "g")
			{
				int ind;
				cin >> ind;
				cout << my_linked_list.get(ind) << '\n';
			}
			if (query == "e")
			{
				int ind;
				cin >> ind;
				my_linked_list.erase_at(ind);
			}
		}
	}

	return 0;
}
