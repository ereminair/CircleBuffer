#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H
#define CIRCULARBUFFER_CIRCULARBUFFER_H

#include <iterator>

namespace CircularBuffer {

    template<typename T>
    class CircularBuffer {
    private:
        T* _buffer;
        bool* _isCellOccupied;
        size_t _size = 0;
        int32_t _head = 0;
        int32_t _tail = 0;
        size_t _capacity;
    public:
        class iterator
        {
        private:
            CircularBuffer<T> *_buffer;
            size_t _index;
        public:
            iterator(CircularBuffer<T> *buffer, size_t index)
            {
                _buffer = buffer;
                _index = index;
            }

            size_t GetIndex()
            {
                return _index;
            }

            iterator& operator++()
            {
                _index = (_index + 1) % _buffer->GetCapacity();
                return *this;
            }

            iterator& operator+(const int& other)
            {

                size_t newIndex = (this->_index + other) % _buffer->GetCapacity();
                auto tmp = new iterator(this->_buffer, newIndex);
                return *tmp;
            }

            iterator& operator<(const iterator& other)
            {
                return this->GetIndex() < other.GetIndex();
            }

            T operator *()
            {
                return this->_buffer->_buffer[_index];
            }

            bool operator==(const iterator& other)
            {
                return this->_index == other._index && this->_buffer == other._buffer;
            }

            bool operator!=(const iterator& other)
            {
                return !operator==(other);
            }
        };

        CircularBuffer(size_t capacity)
        {
            _buffer = new T[capacity];
            _isCellOccupied = new bool[capacity];
            for(int i = 0; i < capacity; i++) _isCellOccupied[i] = false;
            _capacity = capacity;
        }

        CircularBuffer(size_t capacity, T permanent)
        {
            _buffer = new T[capacity];
            _isCellOccupied = new bool[capacity];
            for(int i = 0; i < capacity; i++) _isCellOccupied[i] = true;
            for(int i = 0; i < capacity; i++) _buffer[i] = permanent;
            _capacity = capacity;
        }


        ~CircularBuffer()
        {
            delete[] _buffer;
        }

        size_t GetCapacity()
        {
            return _capacity;
        }

        void PushBack(T value)
        {
            if(_isCellOccupied[_tail])
                _tail++;
            if(_tail >= _capacity)
            {
                _tail = 0;
            }
            _isCellOccupied[_tail] = true;
            _buffer[_tail] = value;
            _size++;
        }

        void PushFront(T value)
        {
            if(_isCellOccupied[_head])
                _head -= 1;
            if(_head < 0)
            {
                _head = _capacity - 1;
            }
            _isCellOccupied[_head] = true;
            _buffer[_head] = value;
            _size++;
        }

        void PopeBack()
        {
            if(_isCellOccupied[_tail] == false)
            {
                throw std::exception();
            }// TODO ff
            _isCellOccupied[_tail] = false;
            _size--;
            _tail -= 1;
            if(_tail < 0)
            {
                _tail = _capacity - 1;
            }
        }

        void PopFront()
        {
            if(_isCellOccupied[_head] == false)
            {
                throw std::range_error("out of range");
            }// TODO
            _isCellOccupied[_head] = false;
            _size--;
            if(_head >= _capacity)
            {
                _head = 0;
            }
        }

        void Emplace(T value, iterator iterator)
        {
            int index = iterator.GetIndex();
            _buffer[index] = value;
            _isCellOccupied[index] = true;
        }

        void PopIter(iterator iterator)
        {
            int index = iterator.GetIndex();
            if(_isCellOccupied[index] == false)
            {
                throw std::range_error("out of range");
            }
            _isCellOccupied[index] = false;
        }

        T GetIter(iterator &iterator)
        {
            int index = iterator.GetIndex();
            if(_isCellOccupied[index] == false)
            {
                throw std::range_error("out of range");
            }
            return _buffer[index];
        }

        void IncreaseCapacity()
        {
            T* tempBuffer = new T[_capacity];
            for(size_t i = 0; i < _capacity; i++) tempBuffer[i] = _buffer[i];
            delete _buffer;
            size_t newSizeBuffer = (int) 1.4 * _capacity;
            _buffer = new T[newSizeBuffer];
            for(size_t i = 0; i < _capacity; i++) _buffer[i] = tempBuffer[i];
            _capacity = newSizeBuffer;
        }

        iterator begin()
        {
            return iterator(this, _head);
        }

        iterator end()
        {
            return iterator(this, _tail);
        }

        T operator[](size_t index)
        {
            return _buffer[index];
        }
    };

} // CircularBuffer

#endif