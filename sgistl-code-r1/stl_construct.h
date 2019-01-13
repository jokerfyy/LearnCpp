
#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new.h> 		//placement new

__STL_BEGIN_NAMESPACE   //namespace std {		


//��ָ��p��ָ����ڴ�ռ��У���valueΪ��ֵ���ÿ������캯��
template <class T1, class T2>
inline void construct(T1* p, const T2& value) {
  new (p) T1(value);	//placement new
}


template <class T>
inline void destroy(T* pointer) 
{
	//����ָ��pointerָ������������������û���ͷ��ڴ�
    pointer->~T();
}

//�Ѱ뿪�������[first, last)�ڵ�����Ԫ��������
//�����Ԫ�ص�����������trivial�ģ���ʲôҲ����
//�����Ԫ�ص�����������non-trivial�ģ��������������������
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

//��Ԫ�ص�����������trivial�ģ���ʲôҲ����
template <class ForwardIterator> 
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) 
{
  //no-op
}

//��Ԫ�ص�����������non-trivial�ģ��������������������
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) 
{
  for ( ; first < last; ++first)
    destroy(&*first);
}


//��������ڵ�Ԫ������Ϊchar��wchar_t����destroyʲôҲ����
inline void destroy(char*, char*) {  }
inline void destroy(wchar_t*, wchar_t*) {  }

__STL_END_NAMESPACE		// }

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
