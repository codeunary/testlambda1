#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

namespace cpp98style {

	// functor adder
	template <typename T>
	class adder {
	public:
		adder(const T &val, bool show=false) : add_val(val), show_result(show) {}
		adder copy(bool show){
			return adder(add_val, show);
		}
		T operator()(const T &target) const {
			T ret = target + add_val;
			if (show_result)
				cout << ret << ' ';

			return ret;
		}
	private:
		T add_val;
		bool show_result;
	};

	// generating a specialized adder functor
	template <typename T>
	adder<T> gen_adder(const T &x){
		return adder<T>(x);
	}

	// counting array elements
	template <typename T, size_t count>
	inline size_t countarr(const T (&arr)[count]){
		return count;
	}

	void test_adder(){
		adder<int> adder_5 = gen_adder(5);
		cout << adder_5(10) << endl;

		adder<double> adder_1_5 = gen_adder(1.5);
		cout << adder_1_5(10.5) << endl;

		adder<string> adder_test = gen_adder<string>("_test");
		cout << adder_test("adder") << endl;

		int ai[] = {1,2,3,4,5};
		for_each(ai, ai+countarr(ai), adder_5.copy(true));
		cout << endl;

		binder2nd<plus<int> > plus_10(plus<int>(), 10);
		cout << plus_10(20) << endl;
	}
};

namespace cpp11style {

	template <typename T>
	function<T(T)> gen_adder(T x){
		return [=](const T &n){ return n+x; };	// return a lambda expression, capture mode is by value
	}

	void test_adder(){
		auto adder_5 = gen_adder(5);
		cout << adder_5(10) << endl;

		auto adder_1_5 = gen_adder(1.5);
		cout << adder_1_5(10.5) << endl;

		auto adder_test = gen_adder<string>("_test");
		cout << adder_test("adder") << endl;

		int ai[] = {1,2,3,4,5};

		for_each(begin(ai), end(ai), 	// non-member begin/end
				[&](int x){ cout << adder_5(x) << ' ';});	// a lambda exp with "by reference" capture mode
		cout << endl;

		cout << [=](int x){ return x+10; }(20) << endl;
	}
};

int main(){
	cout << "C++98\n";
	cpp98style::test_adder();
	cout << "\nC++11\n";
	cpp11style::test_adder();
	cout << "\ndone" << endl;

	cin.get();
	return 0;
}
