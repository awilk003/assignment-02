#include "semicolon.hpp"

Semicolon::Semicolon(bool Left, Cmdline* Right)
{
	Lchild = Left;
	Rchild = Right;
}

void Semicolon::execute(string cmd)
{
	Rchild->execute(cmd);	
}

bool Semicolon::isValid()
{
	return true;
}

//class operations : public Base
//{
//	public:
//		operations(Base* num1, Base* num2) {this->num1 = num1; this->num2 = num2;};		
//	protected:
//		Base* num1;
//		Base* num2;		
//};

//class Mult : public operations
//{
//	public:
//		Mult(Base* num1, Base* num2):operations(num1, num2) {};
//		double evaluate() { return num1->evaluate()*num2->evaluate();};
//	private:
//		Base* left;
//		Base* right;
//};

