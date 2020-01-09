#ifndef DICTONARY_H
#define DICTONARY_H

#include <iostream>
#include <string>
#include <stack>

template<typename K, typename V>
class Dictonary final
{
private:
	struct Node
	{
	public:
		Node* left;
		Node* right;
		int height;
		K key;
		V value;
		Node(K key, V value)
		{
			this->key = key;
			this->value = value;
			this->left = nullptr;
			this->right = nullptr;
			this->height = 1;
		}

		int returnHeight()
		{
			return this->height;
		}

		int BalanceFactor()
		{
			if (this->left == nullptr && this->right == nullptr)
				return 0;
			else if (this->left == nullptr)
				return this->right->returnHeight();
			else if (this->right == nullptr)
				return -this->left->returnHeight();
			else
				return this->right->returnHeight() - this->left->returnHeight();
		}

		int IsBalanced()
		{
			return this->BalanceFactor <= 1;
		}

		int ElementsCount()
		{
			int leftCnt = 0;
			int righCnt = 0;
			if (this->left == nullptr)
				leftCnt = 0;
			else
				leftCnt = this->left->ElementsCount();
			if (this->right == nullptr)
				righCnt = 0;
			else
				righCnt = this->right->ElementsCount();
			return righCnt + leftCnt + 1;
		}

		Node* findMinimal(Node* p)
		{
			if (p->left != nullptr)
				return findMinimal(p->left);
			else
				return p;
		}

		Node* findMax(Node* p)
		{
			if (p->right != nullptr)
				return findMax(p->right);
			else
				return p;
		}

		Node* removeMinimal(Node* p)
		{
			if (p->left == nullptr)
				return p->right;
			p->left = this->removeMinimal(p->left);
			return balance(p);
		}

		Node* remove(Node* p, const K k)
		{
			if (p == nullptr)
				return 0;
			if (k < p->key)
				p->left = this->remove(p->left, k);
			else if (k > p->key)
				p->right = this->remove(p->right, k);
			else
			{
				Node* l = p->left;
				Node* r = p->right;
				delete p;
				if (r == nullptr)
					return l;
				Node* min = findMinimal(r);
				min->right = removeMinimal(r);
				min->left = l;
				return this->balance(min);
			}
			return this->balance(p);
		}

		Node* get(const K& key)
		{
			if (this->key == key)
				return this;
			else if (this->key > key)
			{
				if (this->left == nullptr)
					return nullptr;
				return this->left->get(key);
			}
			else
			{
				if (this->right == nullptr)
					return nullptr;
				return this->right->get(key);
			}
		}

		void recalculateheight()
		{
			if (this->left == nullptr && this->right == nullptr)
				this->height = 1;
			else if (this->left == nullptr)
				this->height = this->right->returnHeight() + 1;
			else if (this->right == nullptr)
				this->height = this->left->returnHeight() + 1;
			else if (this->left->returnHeight() > this->right->returnHeight())
				this->height = this->left->returnHeight() + 1;
			else
				this->height = this->right->returnHeight() + 1;
		}

		Node* insert(const K& key, const V& value)
		{
			if (key == this->key)
				this->value = value;
			else if (key < this->key)
				this->insertLeft(key, value);
			else
				this->insertRight(key, value);
			return balance(this);
		}

		void insertLeft(const K& key, const V& value)
		{
			if (!this->left)
				this->left = new Node(key, value);
			else
				this->left = this->left->insert(key, value);
		}

		void insertRight(const K& key, const V& value)
		{
			if (!this->right)
				this->right = new Node(key, value);
			else
				this->right = this->right->insert(key, value);
		}


		Node* rotateRight(Node* p)
		{
			Node* q = p->left;
			p->left = q->right;
			q->right = p;
			q->recalculateheight();
			p->recalculateheight();
			return q;
		}

		Node* rotateLeft(Node* q)
		{
			Node* p = q->right;
			q->right = p->left;
			p->left = q;
			p->recalculateheight();
			q->recalculateheight();
			return p;
		}

		Node* balance(Node* p)
		{
			p->recalculateheight();
			if (p->BalanceFactor() == 2)
			{
				if (p->right->BalanceFactor() < 0)
					p->right = this->rotateRight(p->right);
				return this->rotateLeft(p);
			}
			if (p->BalanceFactor() == -2)
			{
				if (p->left->BalanceFactor() > 0)
					p->left = this->rotateLeft(p->left);
				return this->rotateRight(p);
			}
			return p;
		}
	};
	Node* rootNode;
public:
	class Iterator
	{
		friend class Dictonary;
	private:
		Dictonary <K, V> dict;
		int itPos;
		Node* currentNode;
		Node* minNode;
		Node* maxNode;
		std::stack<Node*> forwardStack;
		std::stack<Node*> backwardStack;
	public:
		Iterator(Dictonary<K, V>& dict, bool begin) :
			dict(dict),
			itPos(0)
		{
			Node* tmp;
			this->setupFakeCurrentNode();
			if (begin) {
				tmp = findMin(this->dict.rootNode);
				this->forwardStack.push(tmp);
			}
			else {
				tmp = findMax(this->dict.rootNode);
				this->backwardStack.push(tmp);
			}
		}

		void setupFakeCurrentNode()
		{
			currentNode = this->dict.rootNode;
			currentNode = new Node(currentNode->key, currentNode->value);
		}

		Node* findMin(Node* p)
		{
			if (p->left != nullptr) {
				this->forwardStack.push(p);
				return findMin(p->left);
			}
			else
				return p;
		}

		Node* findMax(Node* p)
		{
			if (p->right != nullptr) {
				this->backwardStack.push(p);
				return findMax(p->right);
			}
			else
				return p;
		}


		Node* moveForward(Node* p)
		{
			if (p->right) {
				if (this->backwardStack.size())
					this->backwardStack.pop();
				this->backwardStack.push(p);
				return this->findMin(p->right);
			}
			else
				if (!this->forwardStack.empty()) {
					Node* tmp = this->forwardStack.top();
					this->forwardStack.pop();
					return tmp;
				}
				else
					std::runtime_error("Forward stack is empty, stop iteration");
			return p;
		}

		Node* moveBackward(Node* p)
		{
			if (p->left) {
				if (this->forwardStack.size())
					this->forwardStack.pop();
				this->forwardStack.push(p);
				return this->findMax(p->left);
			}
			else
				if (!this->backwardStack.empty()) {
					Node* tmp = this->backwardStack.top();
					this->backwardStack.pop();
					return tmp;
				}
				else
					std::runtime_error("Backward stack is empty, stop iteration");
			return p;
		}

		const K& key() const
		{
			return this->currentNode->key;
		}

		const V& get() const
		{
			return this->currentNode->value;
		}

		void set(const V& value)
		{
			this->currentNode->insert(this->currentNode->key, value);
		}

		void next()
		{
			this->currentNode = this->moveForward(currentNode);
		}

		void prev()
		{
			this->currentNode = this->moveBackward(currentNode);
		}

		bool hasNext() const
		{
			if (this->currentNode->right)
				return true;
			return !this->forwardStack.empty();
		}

		bool hasPrev() const
		{
			if (this->currentNode->left)
				return true;
			return !this->backwardStack.empty();
		}
	};
	Dictonary()
	{
		this->rootNode = nullptr;
	}

	~Dictonary()
	{}

	void put(const K& key, const V& value)
	{
		if (!this->rootNode)
			this->rootNode = new Node(key, value);
		else
			this->rootNode = this->rootNode->insert(key, value);
	}

	void remove(const K& key)
	{
		if (!this->rootNode)
			throw std::runtime_error("Key error");
		this->rootNode = this->rootNode->remove(this->rootNode, key);
	}

	bool contains(const K& key)
	{
		if (!this->rootNode)
			return false;
		return this->rootNode->get(key) != nullptr;
	}

	V& operator[](const K& key)
	{
		if (!this->rootNode)
			throw std::runtime_error("Key error");
		Node* tmp = this->rootNode->get(key);
		if (tmp == nullptr)
			throw std::runtime_error("Key error");
		return this->rootNode->get(key)->value;
	}

	const V& operator[](const K& key) const
	{
		if (!this->rootNode)
			throw std::runtime_error("Key error");
		Node* tmp = this->rootNode->get(key);
		if (tmp == nullptr)
			throw std::runtime_error("Key error");
		return this->rootNode->get(key)->value;
	}

	int const size()
	{
		if (!this->rootNode)
			return 0;
		return this->rootNode->ElementsCount();
	}

	Iterator begin()
	{
		return Iterator(*this, true);
	}

	Iterator end()
	{
		return Iterator(*this, false);
	}

	std::string pformat()
	{
		std::string dictPformat;
		this->Pformat(this->rootNode, 0, dictPformat);
		dictPformat.append("\n");
		return dictPformat;
	}

	void Pformat(Node* to_print, int tabulate, std::string& dictPformat)
	{
		int i;
		if (to_print != nullptr)
		{
			this->Pformat(to_print->right, tabulate + 1, dictPformat);
			for (i = 0; i < tabulate; i++)
			dictPformat.append("    ");
			dictPformat.append(std::to_string(to_print->key));
			dictPformat.append("    \n");
			this->Pformat(to_print->left, tabulate + 1, dictPformat);
		}
	}
 };


#endif // DICTONARY_H
