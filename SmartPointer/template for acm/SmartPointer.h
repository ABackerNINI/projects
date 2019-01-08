//
//	Create by ABacker on 3/31/2016
//

#ifndef SMART_POINTER_H
#define SMART_POINTER_H

#include <iostream>
//#include <memory>

#define DEBUG_POINTER		1

template<typename DataType>
class _Ptr {
private:
	template<class DataType>friend class SmartPointer;
	_Ptr(DataType *ptr) :ptr(ptr), ref(1) {}

	~_Ptr() {
#if(DEBUG_POINTER)
		std::cout << "delete value:" << *ptr << std::endl;
#endif;
		delete ptr;
	}
	size_t ref;
	DataType *ptr;
};

template<typename DataType>class SmartPointer {
public:
	SmartPointer() :ptr(NULL) {}
	SmartPointer(const SmartPointer<DataType> &pointer) {
		if (pointer.ptr) ++(pointer.ptr->ref);

		ptr = pointer.ptr;
	}
	SmartPointer(SmartPointer<DataType> &&pointer) {
		ptr = pointer.ptr;
		pointer.ptr = NULL;
	}
	SmartPointer(const DataType &value) :ptr(new _Ptr<DataType>(new DataType(value))) {
#if(DEBUG_POINTER)
		std::cout << "new _Ptr" << std::endl;
		std::cout << "new value:" << **this << std::endl;
		++newPtr; ++newVal;
#endif;
	}

	//valPtr must point to a block of memory on heap
	explicit SmartPointer(DataType *valPtr) :ptr(new _Ptr<DataType>(valPtr)) {
#if(DEBUG_POINTER)
		std::cout << "new _Ptr" << std::endl;
		++newPtr;
#endif;
	}

	SmartPointer &operator=(const SmartPointer<DataType> &pointer) {
		if (ptr&&--(ptr->ref) == 0) {
			delete ptr;
#if(DEBUG_POINTER)
			std::cout << "delete _Ptr" << std::endl;
			++deletePtr; ++deleteVal;
#endif
		}
		if (pointer.ptr)++(pointer.ptr->ref);

		ptr = pointer.ptr;

		return *this;
	}
	SmartPointer &operator=(SmartPointer<DataType> &&pointer) {
		if (ptr&&--(ptr->ref) == 0) {
			delete ptr;
#if(DEBUG_POINTER)
			std::cout << "delete _Ptr" << std::endl;
			++deletePtr; ++deleteVal;
#endif
		}
		ptr = pointer.ptr;
		pointer.ptr = NULL;

		return *this;
	}

	//SmartPointer &operator=(const DataType &value) {
	//	this->assign(value);
	//
	//	return *this;
	//}
	//	SmartPointer &operator=(DataType *valPtr) {
//		if (ptr&&--(ptr->ref) == 0) {
//			//delete ptr;
//#if(DEBUG_POINTER)
//			std::cout << "delete value:" << *(ptr->ptr) << std::endl;
//			++deleteVal;
//#endif
//			delete ptr->ptr;
//
//			ptr->ptr = valPtr;
//			++ptr->ref;
//		}
//		else {
//			ptr = new _Ptr<DataType>(valPtr);
//#if(DEBUG_POINTER)
//			std::cout << "new _Ptr" << std::endl;
//			++newPtr;
//#endif
//		}
//
//		return *this;
//	}

	void assign(const DataType &value) {
		if (ptr&&--(ptr->ref) == 0) {
			//delete ptr;
#if(DEBUG_POINTER)
			std::cout << "delete value:" << *(ptr->ptr) << std::endl;
			++deleteVal;
#endif;
			delete ptr->ptr;

			ptr->ptr = new DataType(value);
			++ptr->ref;
#if(DEBUG_POINTER)
			std::cout << "new value:" << *(ptr->ptr) << std::endl;
			++newVal;
#endif;
		}
		else {
			ptr = new _Ptr<DataType>(new DataType(value));
#if(DEBUG_POINTER)
			std::cout << "new value:" << **this << std::endl;
			std::cout << "new _Ptr" << std::endl;
			++newVal; ++newPtr;
#endif;
		}
	}

	//valPtr must point to a block of memory on heap
	void assign(DataType *valPtr) {
		if (ptr&&--(ptr->ref) == 0) {
			//delete ptr;
#if(DEBUG_POINTER)
			std::cout << "delete value:" << *(ptr->ptr) << std::endl;
			++deleteVal;
#endif
			delete ptr->ptr;

			ptr->ptr = valPtr;
			++ptr->ref;
		}
		else {
			ptr = new _Ptr<DataType>(valPtr);
#if(DEBUG_POINTER)
			std::cout << "new _Ptr" << std::endl;
			++newPtr;
#endif
		}
	}

	//SmartPointer<DataType> clone() {
	//	return SmartPointer<DataType>(**this);
	//}
	//
	//const DataType &operator*() const {
	//	return *ptr->ptr;
	//}

	//Do NOT refer out and do NOT delete it
	const DataType *operator->() const {
		return ptr->ptr;
	}

	~SmartPointer() {
		if (ptr&&--ptr->ref == 0) {
			delete ptr;
#if(DEBUG_POINTER)
			std::cout << "delete _Ptr" << std::endl;
			++deletePtr; ++deleteVal;
#endif;
		}
#if(DEBUG_POINTER)
		std::cout << "newPtr:" << newPtr << "   " << "deletePtr:" << deletePtr << std::endl;
		std::cout << "newVal:" << newVal << "   " << "deleteVal:" << deleteVal << std::endl;
#endif;
	}

private:
	_Ptr<DataType>*ptr;
#if(DEBUG_POINTER)
	int newPtr = 0, deletePtr = 0;
	int newVal = 0, deleteVal = 0;
#endif
};

template<typename DataType>using SPtr = SmartPointer<DataType>;

#endif