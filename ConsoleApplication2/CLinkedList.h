#pragma once

template <typename T>
class CLinkedList
{
public:
	struct Node
	{
		T _data;
		Node *_Prev = nullptr;
		Node *_Next = nullptr;
	};

	class Iterator
	{
	private:
		Node *_node = nullptr;
	public:
		// �ȿ��� ����ó�� X
		Iterator(Node *node = nullptr)
		{
			//���ڷ� ���� Node �����͸� ����
			_node = node;
		}

		Node* GetNode() // ����� ������
		{
			return _node;
		}

		const Iterator operator ++(int) // �̰� ����
		{
			//���� ��带 ���� ���� �̵�
			Iterator temp = *this;
			_node = _node->_Next;
			return temp;
		}

		const Iterator operator --(int)
		{
			//���� ��带 ���� ���� �̵�
			Iterator temp = *this;
			_node = _node->_Prev;
			return temp;
		}

		Iterator& operator ++() // �̰� ����
		{
			//���� ��带 ���� ���� �̵�
			_node = _node->_Next;
			return *this;
		}

		Iterator& operator --()
		{
			//���� ��带 ���� ���� �̵�
			_node = _node->_Prev;
			return *this;
		}

		T& operator *()
		{
			//���� ����� �����͸� ����
			return _node->_data;
		}

		T& operator =(T& rhs)
		{
			_node->_data = rhs->_data;

			return *this;
		}

		// ���ͷ����Ͱ� ����Ű�� ��� ��
		bool operator ==(Iterator& rhs)const
		{
			if (_node == rhs.GetNode())
			{
				return true;
			}

			return false;
		}

		bool operator !=(Iterator& rhs)const
		{
			if (_node != rhs.GetNode())
			{
				return true;
			}

			return false;
		}
	};

public:
	CLinkedList()
	{
		_head._Prev = nullptr;
		_head._Next = &_tail;
		_tail._Prev = &_head;
		_tail._Next = nullptr;
	}

	~CLinkedList()
	{
		Clear(); // Clear �������� ������ ���
	}

	Iterator begin()
	{
		// �ȿ��� ����
		// ù��° ���(������)�� ����Ű�� ���ͷ����� ����

		Iterator newIter(_head._Next);
		return newIter;
	}

	Iterator end()
	{
		//Tail ���(����)�� ����Ű�� ���ͷ����͸� ����

		Iterator newIter(&_tail);
		return newIter;
	}

	void push_front(T data) // headInsert
	{
		Node* newNode = new Node;
		newNode->_data = data;

		newNode->_Next = _head._Next;
		newNode->_Prev = _head;
		_head._Next->_Prev = newNode;
		_head._Next = newNode;

		_size++;
	}

	void push_back(T data) // tailInsert
	{
		Node* newNode = new Node;
		newNode->_data = data;

		newNode->_Next = &_tail;
		newNode->_Prev = _tail._Prev;
		_tail._Prev->_Next = newNode;
		_tail._Prev = newNode;

		_size++;
	}

	void pop_front(T* data)
	{
		Node* popData = _head._Next;

		_head._Next->_Next->_Prev = _head;
		_head._Next = popData->_Next;

		*data = popData->_data;

		_size--;
	}

	void pop_back(T* data)
	{
		Node* popData = _tail._Prev;

		_tail._Prev->_Prev->_Next = _tail;
		_tail._Prev = popData->_Prev;

		*data = popData->_data;

		_size--;
	}

	void Insert(Iterator iter, T data)
	{
		// ���ͷ����Ϳ� ������ �ֱ�
		*iter = data;
	}

	// ��ũ�� ����Ʈ ����
	void Clear()
	{
		Node* delData = _head._Next;
		if (delData == nullptr)
		{
			return;
		}

		for (int i = 0; i < _size; i++)
		{
			Node* delDataNext = delData->_Next;
			delete delData;
			delData = delDataNext;
		}

		_head._Prev = nullptr;
		_head._Next = &_tail;
		_tail._Prev = &_head;
		_head._Next = nullptr;

		_size = 0;
	}

	int size()
	{
		return _size;
	}

	bool IsEmpty()
	{
		if (_size == 0)
		{
			return true;
		}

		return false;
	}

	Iterator erase(Iterator iter)
	{
		//- ���ͷ������� �� ��带 ����.(���ͷ����Ͱ� ����Ű�� ������)
		//- �׸��� ���� ����� ���� ��带 ī��Ű�� ���ͷ����� ����
		if (_head._Next == &_tail)
		{
			return iter;
		}

		Node* delNode = iter.GetNode();

		Iterator returnIter(delNode->_Next);

		delNode->_Next->_Prev = delNode->_Prev;
		delNode->_Prev->_Next = delNode->_Next;

		delete delNode;
		_size--;

		return returnIter;
	}

private:
	int _size = 0;
	Node _head;
	Node _tail;
};
