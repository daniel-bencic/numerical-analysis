#ifndef ITERATIVE_METHOD_HH
#define ITERATIVE_METHOD_HH

namespace num {
	template<typename T>
	class IterativeMethod {
	public:
		IterativeMethod();
		IterativeMethod(double tolerance, int max_iterations);
		virtual ~IterativeMethod() = 0;
		
	protected:
		double _tol;
		int _its;
	};

	template<typename T>
	IterativeMethod<T>::IterativeMethod()
		: _tol(0.0), _its(0)
	{ }

	template<typename T>
	IterativeMethod<T>::IterativeMethod(double tolerance, int max_iterations)
		: _tol(tolerance), _its(max_iterations)
	{ }

	template<typename T>
	IterativeMethod<T>::~IterativeMethod<T>()
	{ }
}

#endif /* ITERATIVE_METHOD_HH */
