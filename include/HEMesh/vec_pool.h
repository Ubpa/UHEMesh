#pragma once
#ifndef _BASIC_HEADER_VECPOOL_H_
#define _BASIC_HEADER_VECPOOL_H_

#include <vector>
#include <unordered_set>

namespace Ubpa {
	template<typename T>
	class vec_pool {
	public:
		vec_pool() : buffer((T*)malloc(32 * sizeof(T))), capacity(32), size(0) { }
		~vec_pool() {
			for (size_t i = 0; i < size; i++) {
				if (emptyIndices.find(i) == emptyIndices.end())
					buffer[i].~T();
			}
			if (buffer)
				free(buffer);
		}

	public:
		template<typename ... Args>
		size_t request(Args&& ... args) {
			size_t idx;

			if (emptyIndices.empty()) {
				assert(size <= capacity);
				if (size == capacity) {
					emptyIndices.reserve(2 * capacity);
					buffer = (T*)realloc(buffer, 2 * capacity * sizeof(T));
					capacity *= 2;
				}
				idx = size++;
			}
			else {
				auto iter = emptyIndices.begin();
				idx = *iter;
				emptyIndices.erase(idx);
			}

			new (buffer + idx) T(std::forward<Args>(args)...);
			return idx;
		}

		void recycle(size_t idx) {
			assert(idx < size);
			buffer[idx].~T();
			emptyIndices.insert(idx);
		}

		void reserve(size_t n) {
			if (n < capacity)
				return;

			buffer = (T*)realloc(buffer, n * sizeof(T));
			emptyIndices.reserve(n);
			capacity = n;
		}

		void clear() {
			for (size_t i = 0; i < size; i++) {
				if (emptyIndices.find(i) == emptyIndices.end())
					buffer[i].~T();
			}
			emptyIndices.clear();
		}

		T& at(size_t n) {
			assert(n < capacity && emptyIndices.find(n) == emptyIndices.end());
			return buffer[n];
		}
		const T& at(size_t n) const { const_cast<vec_pool*>(this)->at(n); }
		T& operator[](size_t n) { return at(n); }
		const T& operator[](size_t n) const { return at(n); }

	private:
		T* buffer;
		size_t size;
		size_t capacity;
		std::unordered_set<size_t> emptyIndices;
	};
}

#endif // !_BASIC_HEADER_VECPOOL_H_