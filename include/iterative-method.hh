#ifndef ITERATIVE_METHOD_HH
#define ITERATIVE_METHOD_HH

namespace num {
	template<typename T>
	class IterativeMethod {
	public:
		IterativeMethod();
		IterativeMethod(T tolerance, int max_iterations);
		virtual ~IterativeMethod() = 0;
		
	protected:
		T _tol;
		int _its;
	};

	template<typename T>
	IterativeMethod<T>::IterativeMethod()
		: _tol(static_cast<T>(0)), _its(0)
	{ }

	template<typename T>
	IterativeMethod<T>::IterativeMethod(T tolerance, int max_iterations)
		: _tol(tolerance), _its(max_iterations)
	{ }

	template<typename T>
	IterativeMethod<T>::~IterativeMethod<T>()
	{ }
}

#endif /* ITERATIVE_METHOD_HH */
