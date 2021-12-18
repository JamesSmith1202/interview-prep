# interview_prep

Random C++ preparation for interviews

# Random Questions

* `explicit` - Specifies that a constructor or conversion function (since C++11) or deduction guide (since C++17) is explicit, that is, it cannot be used for implicit conversions and copy-initialization.
* `virtual` -  (when used on a method and used in inheritance)
* `mutable` -  allows modification of the member that it is declared on even when in a const class. It is effectively a promise that it doesn't affect the visible state of the object.
* `const` - restricts modification of the variable/object
* `volatile` - restricts the compiler from optimizing instructions regarding the variable or object -- ex. instruction reordering 
* `sealed` - microsoft specific, but it restricts users from inheriting from a class declared as sealed.
* `inline` - an indicator to the compiler to copy the function code inline as opposed to performing a function call. results in a faster runtime, but larger executable. because this is an indicator, the compiler has the choice to ignore it or make functions not declared inline to be inline. Additionally it provides variables with external linkage to multiple files

What’s the difference between struct and a class? 
* struct has public members and base structs/classes by default. a class has private members and base structs/classes by default.

public inheritance = base class's public fields are also public in derived class
protected inheritance = base class's public and protected fields are protected in derived class
private inheritance = base class's public and protected fields are private in derived class

**Multiple inheritance**
