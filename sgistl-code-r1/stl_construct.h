
#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new.h> 		//placement new

__STL_BEGIN_NAMESPACE   //namespace std {		


//在指针p所指向的内存空间中，以value为初值调用拷贝构造函数
template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
  new (p) T1(value);	//placement new
}


template <class T>
inline void destroy(T* pointer) 
{
	//调用指针pointer指向对象的析构函数，并没有释放内存
    pointer->~T();
}

//把半开半闭区间[first, last)内的所有元素析构掉
//如果该元素的析构函数是trivial的，则什么也不做
//如果该元素的析构函数是non-trivial的，则依序调用其析构函数
template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
  __destroy(first, last, value_type(first));
}


template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*) 
{
  typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
  
  __destroy_aux(first, last, trivial_destructor());
}

//该元素的析构函数是trivial的，则什么也不做
template <class ForwardIterator> 
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) 
{
  //no-op
}

//该元素的析构函数是non-trivial的，则依序调用其析构函数
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) 
{
  for ( ; first < last; ++first)
    destroy(&*first);
}


//如果区间内的元素类型为char或wchar_t，则destroy什么也不做
inline void destroy(char*, char*) {  }
inline void destroy(wchar_t*, wchar_t*) {  }

__STL_END_NAMESPACE		// }

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
