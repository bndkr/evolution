#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>
#include <iostream>

class Hello
{
public:
  Hello() { }
  void sayHi() { std::cout << "hi." << std::endl; }
};


BOOST_PYTHON_MODULE(pyEvolution) {
  using namespace boost::python;
  class_<Hello>("Hello", init<>()).def("sayHi", &Hello::sayHi);
}