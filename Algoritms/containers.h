#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <iostream>
#include <iterator>


const int MINcapacity = 0;
const int INCREMENTION_MULTIPLIE = 2;
const int LIST_CHUNKsize = 8;


template<typename T>
class Array
{
public:
	T* storagePtr;
	int capacity;
	int size;

public:
	class Iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	private:
		Array<T>& array;
		int itPos;
	public:
		Iterator(Array<T>& array) : array(array), itPos(0) {}

		const T& get() const
		{
			return this->array[this->itPos];
		}

		void set(const T& value)
		{
			this->array[this->itPos] = value;
		}

		void insert(const T& value)
		{
			this->array.insert(this->itPos, value);
		}

		void remove()
		{
			this->array.remove(this->itPos);
		}

		void next()
		{
			if (this->itPos >= this->array.returnSize() - 1)
				throw std::runtime_error("Unable to set iterator index to that position");
			this->itPos++;
		}

		void prev()
		{
			if (this->itPos <= 0)
				throw std::runtime_error("Unable to set iterator index to that position");
			this->itPos--;
		}

		void toIndex(int index)
		{
			if ((index > this->array.size) || (index < -1))
				throw std::runtime_error("Unable to set iterator index to that position");
			this->itPos = index;
		}

		bool hasNext() const
		{
			return (this->itPos < this->array.size - 1);
		}

		bool hasPrev() const
		{
			return (this->itPos > 0);
		}
	};

	Array(int capacity) :
		capacity(capacity),
		storagePtr(nullptr),
		size(0)
	{
		if (capacity < MINcapacity)
			throw std::runtime_error("Invalid array capacity");
		if (this->capacity != 0)
			this->storagePtr = new T[capacity];
		else
			this->storagePtr = nullptr;
	}

	~Array() {
		delete[] this->storagePtr;
	}

	// Copy constructor
	Array(const Array& other)
	{
		this->storagePtr = new T[other.capacity];
		std::copy(other.storagePtr,
			other.storagePtr + other.capacity,
			this->storagePtr);

		capacity = other.capacity;
		size = other.size;
	}

	// Copy assignment operator
	Array& operator =(const Array& other)
	{
		if (&other == this)
			return *this;

		delete[] this->storagePtr;
		this->storagePtr = new T[other.capacity];

		std::copy(other.storagePtr,
			other.storagePtr + other.capacity,
			this->storagePtr);

		capacity = other.capacity;
		size = other.size;

		return *this;
	}

	// Move constructor
	Array(Array&& other)
	{
		this->storagePtr = new T[other.capacity];
		std::move(other.storagePtr,
			other.storagePtr + other.capacity,
			this->storagePtr);

		capacity = other.capacity;
		size = other.size;

		other.storagePtr = nullptr;
		other.size = 0;
	}

	// Move assignment operator
	Array& operator=(Array&& other)
	{
		if (this != &other)
		{
			delete[] this->storagePtr;
			this->storagePtr = new T[other.capacity];

			std::move(other.storagePtr,
				other.storagePtr + other.capacity,
				this->storagePtr);

			capacity = other.capacity;
			size = other.size;

			other.storagePtr = nullptr;
			other.size = 0;
		}
		return *this;
	}

	void expandStorage()
	{
		T* newChunkPtr;
		if (this->returnCapacity() == 0)
			this->capacity++;
		this->capacity = this->capacity * INCREMENTION_MULTIPLIE;

		newChunkPtr = new T[this->capacity];

		for (int i = 0; i != this->size; i++)
			newChunkPtr[i] = std::move(this->storagePtr[i]);

		this->storagePtr = newChunkPtr;
	}

	int const returnCapacity()
	{
		return capacity;
	}

	; T& operator[](int index)
	{
		if ((index > this->returnSize()) || (index < -1))
			throw std::runtime_error("Reference to invalid item, index is out of bounds");
		return this->storagePtr[index];
	}

	const T& operator[](int index) const
	{
		if ((index > this->size()) || (index < -1))
			throw std::runtime_error("Reference to invalid item, index is out of bounds");
		return std::move(this->storagePtr[index]);
	}

	int const returnSize()
	{
		return this->size;
	}

	void insert(const T& value)
	{
		this->insert(this->returnSize(), value);
	}

	void insert(int index, const T& value)
	{
		if ((index > this->returnSize()) || (index < 0))
			throw std::runtime_error("Unable to insert, index is out of bounds");

		if (this->capacity == this->returnSize())
			this->expandStorage();

		for (int i = this->returnSize() - 1; i >= index; i--)
			this->storagePtr[i + 1] = std::move(this->storagePtr[i]);

		this->storagePtr[index] = std::move(value);

		this->size++;
	}

	void remove(int index)
	{
		if ((index >= this->returnSize()) || (index < -1))
			throw std::runtime_error("Unable to remove, index is out of bounds");

		for (int i = index; i < this->returnSize(); i++)
			this->storagePtr[i] = std::move(this->storagePtr[i + 1]);

		this->size--;
	}

	Iterator iterator()
	{
		return Iterator(*this);
	}

	Iterator begin()
	{
		Iterator* it = new Iterator(*this);
		it->toIndex(-1);
		return *it;
	}

	Iterator end()
	{
		Iterator* it = new Iterator(*this);
		it->toIndex(this->returnSize());
		return *it;
	}
};



template<typename T>
class LinkedList
{
private:
	struct Chunk
	{
		Array<T>* container;
		int size;
		int capacity;
		Chunk* next;
		Chunk* prev;

		Chunk(const int capacity, Chunk* prev_chunk, Chunk* next_chunk) :
			size(0),
			capacity(capacity),
			next(next_chunk),
			prev(prev_chunk)
		{
			container = new Array<T>(capacity);
		}

		~Chunk()
		{}

		void insertToStart(const T& value)
		{
			this->container->insert(0, value);
			this->size++;
		}

		void insertToEnd(const T& value)
		{
			this->container->insert(value);
			this->size++;
		}

		int const returnSize()
		{
			return this->size;
		}

		bool const filled()
		{
			return this->capacity == this->size;

		}

		void removeFirst()
		{
			this->container->remove(0);
			this->size--;
		}

		void removeLast()
		{
			int cntsize;
			cntsize = this->container->returnSize() - 1;
			this->container->remove(cntsize);
			this->size--;
		}

		const T& first()
		{
			auto it = this->container->begin();
			it.next();
			return it.get();
		}

		const T& last()
		{
			auto it = this->container->end();
			it.prev();
			return it.get();
		}
	};

	Chunk* storagePtr;
	Chunk* headChunkPtr;
	Chunk* tailChunkPtr;
	int size;
public:
	LinkedList() :
		storagePtr(nullptr),
		size(0)
	{
		this->tailChunkPtr = new Chunk(LIST_CHUNKsize, nullptr, nullptr);
		this->headChunkPtr = this->tailChunkPtr;
	}

	void insertHead(const T& value)
	{
		if (this->headChunkPtr->filled())
		{
			this->headChunkPtr->prev = new Chunk(LIST_CHUNKsize, nullptr, this->storagePtr);
			this->headChunkPtr = this->headChunkPtr->prev;
		}
		this->headChunkPtr->insertToStart(value);
		this->size++;
	}

	void insertTail(const T& value)
	{
		if (this->tailChunkPtr->filled())
		{
			this->tailChunkPtr->next = new Chunk(LIST_CHUNKsize, this->tailChunkPtr, nullptr);
			this->tailPtr = this->tailChunkPtr->next;
		}
		this->tailChunkPtr->insertToEnd(value);
		this->size++;
	}

	void removeHead()
	{
		if (this->returnSize() == 0)
			return;

		this->headChunkPtr->removeFirst();
		this->size--;

		// get rid of empty chunks
		if (this->headChunkPtr->next == nullptr)  // keep chunk if it's last
			return;

		if (this->headChunkPtr->returnSize() == 0)  // and remove if it's not
		{
			this->headChunkPtr = this->headChunkPtr->next;
			this->headChunkPtr->prev->~Chunk();
			this->headChunkPtr->prev = nullptr;
		}
	}

	void removeTail()
	{
		if (this->returnSize() == 0)
			return;

		this->tailChunkPtr->removeLast();
		this->size--;

		// get rid of empty chunks
		if (this->tailChunkPtr->prev == nullptr)  // keep chunk if it's last
			return;

		if (this->tailChunkPtr->returnSize() == 0)  // and remove if it's not
		{
			this->tailChunkPtr = this->tailChunkPtr->prev;
			this->tailChunkPtr->next->~Chunk();
			this->tailChunkPtr->next = nullptr;
		}
	}

	const T& head()
	{
		if (this->returnSize() == 0)
			throw std::runtime_error("Unable to read head, List is empty");
		return this->headChunkPtr->first();
	}

	const T& tail()
	{
		if (this->returnSize() == 0)
			throw std::runtime_error("Unable to read head, List is empty");
		return this->tailChunkPtr->last();
	}

	int returnSize() const
	{
		return this->size;
	};
};

#endif // CONTAINERS_H
