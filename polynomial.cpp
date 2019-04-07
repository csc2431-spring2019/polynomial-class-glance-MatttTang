// Class 2431 Spring 2019, Data Structures 2
//
// Professor: Carlos Arias
//
// Author: Matthew Tang



#include "polynomial.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include <cmath>

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
// Sum returns a new polynomial that is the addition of the rhs polynomial, and
// The polynomial started with
const Polynomial Polynomial::Sum(const Polynomial& rhs)const{
	Polynomial sumArr(rhs);
	// Make sure the new sum array has enough space to fit the highest degree
	// polynomial
	if (_degree > rhs._degree)
		sumArr._degree = _degree;

	for (size_t i = 0; i < sumArr._degree + 1; i++)
	{
		sumArr._coefficients[i] = rhs._coefficients[i];
	}

	for (size_t j = 0; j < _degree + 1; j++)
	{
		sumArr._coefficients[j] += _coefficients[j];
	}

	return sumArr;
}
// Subtract is the polynnomial we started with minus the rhs polynomial
const Polynomial Polynomial::Subtract(const Polynomial& rhs)const{

	Polynomial subArr(*this);
	for (size_t i = 0; i < subArr._degree + 1; i++)
	{
		subArr._coefficients[i] = _coefficients[i];
	}

	for (size_t j = 0; j < _degree + 1; j++)
	{
		subArr._coefficients[j] -= rhs._coefficients[j];
	}

	return subArr;

}

const Polynomial Polynomial::Minus()const{
	Polynomial retVal(*this);
	for (size_t i = 0; i < _degree + 1; i++) {
		retVal._coefficients[i] *= -1;
	}
	return retVal;
}

// Multiply multiplies the 2 polynomials by eachother
const Polynomial Polynomial::Multiply(const Polynomial& rhs)const{
	Polynomial multArr(*this);

	// the new polynomial's degree is the first 2 added together
	multArr._degree = rhs._degree + _degree;

	// Initialize the new polynomial to 0 at first
	for (size_t q = 0; q < multArr._degree + 1; q++)
	{
		multArr._coefficients[q] = 0;
	}

	// Using a for-loop, iterate through one polynomial, multiplying by each of
	// of the other polynomials terms, nested for-loop
	for (size_t i = 0; i < _degree + 1; i ++)
	{
		for (size_t j = 0; j < rhs._degree + 1; j++)
		{
			multArr._coefficients[i + j] = _coefficients[i] * rhs._coefficients[j] + multArr._coefficients[i + j];
		}
	}
	return multArr;
}
const Polynomial Polynomial::Divide(const Polynomial& rhs)const{
	return Polynomial(0);
}

// Derive take the derivative of the polynomial, multiplying by its power, and
// reducing the power by 1 for each term
const Polynomial Polynomial::Derive()const{
	Polynomial deriveArr(*this);

	// Create a new polynomial, with the same terms as the one given
	for (size_t i = 0; i < _degree + 1; i++)
	{
		deriveArr._coefficients[i] = _coefficients[i];
	}

	// Multiply the terms by their degree
	for (size_t j = 0; j < deriveArr._degree + 1; j++)
	{
		deriveArr._coefficients[j] = deriveArr._coefficients[j] * j;
	}

	// Shift the array to account for the 0 degree term to go to 0
	for (size_t z = 0; z < deriveArr._degree; z++)
	{
		deriveArr._coefficients[z] = deriveArr._coefficients[z + 1];
	}

	// subtract the degree by 1
	deriveArr._degree -= 1;
	return deriveArr;
}

// Evaluate plugs in a number for x in the polynomial, and realizes the value
// of the polynomial
float Polynomial::Evaluate(float x)const{

	float retVal = 0;

	Polynomial evalArr(*this);
	// plug in the value of float x into the polynomial with cmath
	for (size_t i = 0; i < _degree + 1; i++)
	{
		evalArr._coefficients[i] = pow(x, i) * _coefficients[i];
		retVal = evalArr._coefficients[i] + retVal;
	}
	return retVal;
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
