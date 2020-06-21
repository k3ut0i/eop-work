// -*- mode:c++ -*-
#ifndef TYPES_H
#define TYPES_H
#include <type_traits>
#include <array>

#define requires(T)

template<typename T> requires(FunctionalProcedure(T))
struct codomain_type;
#define Codomain(T) typename codomain_type<T>::type

template<typename T, unsigned i> requires(FunctionalProcedure(T))
struct input_type;
#define Input_Type(T, i) typename input_type<T, i>::type
#define Domain(T) Input_Type(T, 0)

template<typename T> struct arity_value;
#define Arity(T) arity_value<T>::arity

template<typename I, typename O, unsigned n>
struct homogeneousFunction{
public:
  O (*func) (std::array<I, n>);
  explicit homogeneousFunction(O (f) (std::array<I,n>)) : func(f){};
};
template<typename I, typename O, unsigned n>
struct codomain_type<homogeneousFunction<I, O, n>>{typedef O type;};
template<typename I, typename O, unsigned n, unsigned idx>
struct input_type<homogeneousFunction<I, O, n>, idx>{typedef I type;};
template<typename I, typename O, unsigned n>
struct arity_value<homogeneousFunction<I, O, n>>{unsigned arity = n;};

template<typename T, unsigned n>
struct operation : homogeneousFunction<T, T, n>{
  operation(T (f) (std::array<T, n>)) :
    homogeneousFunction<T, T, n>(f) {};
};
// How to unify homogeneousFunction and arity = 2 without introducting
// another parameter `n`? 
template<typename T>
struct binaryOperation : operation<T, 2>{
  binaryOperation(T (f) (std::array<T, 2>)) :
    operation<T, 2>(f){};
};
// {
//   T op(T v1, T v2){ // Individual parameters to array notation change
//     return func({v1, v2});
//   }};
template<typename T>
struct codomain_type<binaryOperation<T>>{typedef T type;};
template<typename T>
struct input_type<binaryOperation<T>, 0>{typedef T type;};
template<typename T>
struct unaryOperation : operation<T, 1>{};

#endif
