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
		// 안에서 오류처리 X
		Iterator(Node *node = nullptr)
		{
			//인자로 들어온 Node 포인터를 저장
			_node = node;
		}

		Node* GetNode() // 노드의 포인터
		{
			return _node;
		}

		const Iterator operator ++(int) // 이건 후위
		{
			//현재 노드를 다음 노드로 이동
			Iterator temp = *this;
			_node = _node->_Next;
			return temp;
		}

		const Iterator operator --(int)
		{
			//현재 노드를 이전 노드로 이동
			Iterator temp = *this;
			_node = _node->_Prev;
			return temp;
		}

		Iterator& operator ++() // 이건 전위
		{
			//현재 노드를 다음 노드로 이동
			_node = _node->_Next;
			return *this;
		}

		Iterator& operator --()
		{
			//현재 노드를 이전 노드로 이동
			_node = _node->_Prev;
			return *this;
		}

		T& operator *()
		{
			//현재 노드의 데이터를 뽑음
			return _node->_data;
		}

		T& operator =(T& rhs)
		{
			_node->_data = rhs->_data;

			return *this;
		}

		// 이터레이터가 가리키는 노드 비교
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
		Clear(); // Clear 수동으로 못했을 경우
	}

	Iterator begin()
	{
		// 안에서 생성
		// 첫번째 노드(실제값)를 가리키는 이터레이터 리턴

		Iterator newIter(_head._Next);
		return newIter;
	}

	Iterator end()
	{
		//Tail 노드(더미)를 가리키는 이터레이터를 리턴

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
		// 이터레이터에 데이터 넣기
		*iter = data;
	}

	// 링크드 리스트 정리
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
		//- 이터레이터의 그 노드를 지움.(이터레이터가 가리키는 데이터)
		//- 그리고 지운 노드의 다음 노드를 카리키는 이터레이터 리턴
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
