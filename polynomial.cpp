#include "polynomial.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cfloat>

using std::istream;
using std::ostream;
using std::string;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::showpos;

Polynomial::Polynomial(size_t degree) : _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = 0.0;
	}
}
Polynomial::Polynomial(size_t degree, const float* coefficients): _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = coefficients[i];
	}
}
Polynomial::Polynomial(const Polynomial& polynomial): _degree(polynomial._degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = polynomial._coefficients[i];
	}
}
Polynomial::~Polynomial(){
	delete[] _coefficients;
	_coefficients = nullptr;
	// DO THIS FIRST TO PREVENT MEMORY LEAKS!
}
const Polynomial Polynomial::Sum(const Polynomial& rhs)const{
	/*if the degree of rhs is greater than the degree of the particular
	polynomial, only add up to the maximum degree of the particular polynomial*/
	//Polynomial sumArr(*this);
	if (rhs._degree > _degree)
	{
		// Create a new Polynomial, with degrees = rhs
		Polynomial sumArr(rhs);
		// put rhs into the new array
		for (size_t i = 0; i < sumArr._degree + 1; i++)
		{
			sumArr._coefficients[i] = rhs._coefficients[i];
			std::cout << sumArr._coefficients[i] << std::endl;
		}
		std::cout << "cut" << std::endl;
		// add polynomial to the rhs coefficents in the new array
		for (size_t j = 0; j < _degree + 1; j++)
		{
			sumArr._coefficients[j] += _coefficients[j];
			std::cout << sumArr._coefficients[j] << std::endl;
		}
	}
	// Redo but with the rhs degrees being less
	else
	{
		Polynomial sumArr(*this);
		for (size_t i = 0; i < sumArr._degree + 1; i++)
		{
			sumArr._coefficients[i] = _coefficients[i];
		}
		for (size_t j = 0; j < rhs._degree + 1; j++)
		{
			sumArr._coefficients[j] += rhs._coefficients[j];
			std::cout << "hello";
			std::cout << sumArr._coefficients[j] << std::endl;
		}

	}
	std::cout << "rhs array" << std::endl;
	for (size_t q = 0; q < rhs._degree + 1; q++)
	{
		std::cout << rhs._coefficients[q] << std::endl;
	}

	std::cout << "poly array" << std::endl;
	for (size_t w = 0; w < _degree + 1; w++)
	{
		std::cout << _coefficients[w] << std::endl;
	}

	return 1;
}
const Polynomial Polynomial::Subtract(const Polynomial& rhs)const{
	return Polynomial(0);
}
const Polynomial Polynomial::Minus()const{
	Polynomial retVal(*this);
	for (size_t i = 0; i < _degree + 1; i++) {
		retVal._coefficients[i] *= -1;
	}
	return retVal;
}
const Polynomial Polynomial::Multiply(const Polynomial& rhs)const{
	return Polynomial(0);
}
const Polynomial Polynomial::Divide(const Polynomial& rhs)const{
	return Polynomial(0);
}
const Polynomial Polynomial::Derive()const{
	return Polynomial(0);
}
float Polynomial::Evaluate(float x)const{
	return FLT_MAX;
}
float Polynomial::Integrate(float start, float end)const{
	return FLT_MAX;
}
const Polynomial& Polynomial::operator=(const Polynomial& rhs){
	if (&rhs == this){
		return *this;
	}
	if (_degree != rhs._degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = rhs._degree;
		_coefficients = new float[_degree + 1];
	}
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = rhs._coefficients[i];
	}
	return *this;
}
bool Polynomial::Equals(const Polynomial& rhs)const{
	if (_degree != rhs._degree){
		return false;
	}
	for (size_t i=0; i < _degree; i++){
		if (abs(_coefficients[i] - rhs._coefficients[i]) > 0.0001){
			return false;
		}
	}
	return true;
}
string Polynomial::ToString()const{
	stringstream ss;
	for (size_t i = _degree; i > 0; i--) {
		ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
	}
	ss << showpos << fixed << setprecision(2) << _coefficients[0];
	return ss.str();
}
ostream& Polynomial::Write(ostream& output)const{
	output << _degree << " ";
	for (size_t i = 0; i < _degree + 1; i++) {
		output << _coefficients[i] << " ";
	}
	return output;
}
istream& Polynomial::Read(istream& input){
	size_t degree;
	input >> degree;
	if (input.fail()){
		return input;
	}
	float* coefficients = new float[degree + 1];
	for (size_t i = 0; i < degree + 1; i++) {
		input >> coefficients[i];
		if (input.fail()){
			delete[] coefficients;
			return input;
		}
	}

	if (degree != _degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = degree;
		_coefficients = coefficients;
	}else{
		for (size_t i = 0; i < _degree + 1; i++) {
			_coefficients[i] = coefficients[i];
		}
		delete[] coefficients;
	}
	return input;
}
