#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include <string>
#include <sstream>
#include <iomanip>

const int nonDisplayedZeros = 4; // Количество неотображаемых нулей при выводе коэффициента полинома
								 // Кол-во символов после запятой = 6 - nonDisplayedZeros


class TPolinom : public THeadList<TMonom>
{
public:
	TPolinom();
	TPolinom(TPolinom& other);
	TPolinom(string str);
	TPolinom& operator=(TPolinom& other); // присваивание
	TPolinom& operator+(TPolinom& q); // сложение полиномов

	// дополнительно можно реализовать:
	void AddMonom(TMonom newMonom); // добавление монома
	TPolinom MultMonom(TMonom monom); // умножение мономов
	TPolinom AddPolinom(TPolinom& other); // добавление полинома
	TPolinom operator*(int coef); // умножение полинома на число
	TPolinom operator* (TPolinom& other); // умножение полиномов
	bool operator==(TPolinom& other); // сравнение полиномов на равенство
	string ToString(); // перевод в строку
};

TPolinom::TPolinom() :THeadList<TMonom>(){
	length = 0;
}


TPolinom::TPolinom(TPolinom& other) : THeadList<TMonom>() {
	if (other.pFirst == nullptr || other.pStop == nullptr) {

		return;
	}
	TNode<TMonom>* node = other.pFirst;
	while (node != other.pStop) {
		this->AddMonom(node->value);
		node = node->pNext;
	}
}


TPolinom::TPolinom(string str){
	for (int i = 0; i < str.length(); i += 4) {

		int coef = str[i] - '0';
		int degX = str[i + 1] - '0';
		int degY = str[i + 2] - '0';
		int degZ = str[i + 3] - '0';


		TMonom monom(coef, degX, degY, degZ);
		this->AddMonom(monom);
	}
}

TPolinom& TPolinom::operator=(TPolinom& other) {
	if (this != &other) {
		this->~TPolinom();
		new(this) TPolinom(other);
	}
	return *this;
}

void TPolinom::AddMonom(TMonom m) {
	TNode<TMonom>* current = this->pFirst;
	TNode<TMonom>* previous = nullptr;
	TNode<TMonom>* newNode = new TNode<TMonom>;
	newNode->value = m;

	while (current != this->pStop && current->value.index > m.index) {
		previous = current;
		current = current->pNext;
	}

	if (current != this->pStop && current->value.index == m.index) {
		current->value.coef += m.coef;
		if (current->value.coef == 0) {
			if (previous)
				previous->pNext = current->pNext;
			delete current;
		}
	}
	else {
		newNode->pNext = current;
		if (previous)
			previous->pNext = newNode;
		else
			this->pFirst = newNode;
	}
}

TPolinom TPolinom::MultMonom(TMonom monom)
{
	TPolinom result(*this);
	for (TNode<TMonom>* node = result.pFirst; node != result.pStop; node = node->pNext) {
		node->value.coef *= monom.coef;
		node->value.index += monom.index;
	}
	return result;
}

TPolinom& TPolinom::operator+(TPolinom& other)
{
	TPolinom result;
	
	TNode<TMonom>* node1 = this->pFirst;
	TNode<TMonom>* node2 = other.pFirst;

	while (node1 != this->pStop && node2 != other.pStop) {
		cout << node1->value.coef << " " << node1->value.index << " " << node2->value.coef << " " << node2->value.index << endl;
		//if (node1->value.coef != 0 && node2->value.coef != 0) {
			if (node1->value.index == node2->value.index) {
				//cout << node1->value.coef << " " << node1->value.index << " " << node2->value.coef << " " << node2->value.index << endl;
				
				int sumCoef = node1->value.coef + node2->value.coef;
				if (sumCoef != 0) {

					TMonom sumMonom(sumCoef, (node1->value.index / 100),(node1->value.index / 10) % 10, node1->value.index % 10);
					result.AddMonom(sumMonom);
					//cout << "result = " << result.ToString() << endl;
				}
				node1 = node1->pNext;
				node2 = node2->pNext;
			}
			else if (node1->value.index > node2->value.index) {
				//cout << node1->value.coef << " " << node1->value.index << " " << node2->value.coef << " " << node2->value.index << endl;
				result.AddMonom(node1->value);
				cout << "result = " << result.ToString() << endl;
				node1 = node1->pNext;
			}
			else {
				//cout << node1->value.coef << " " << node1->value.index << " " << node2->value.coef << " " << node2->value.index << endl;
				result.AddMonom(node2->value);
				cout << "result = " << result.ToString() << endl;
				node2 = node2->pNext;

			}
		//}
		//else {break;}
	}
	while (node1 != this->pStop) {
		cout << node1->value.coef << " " << node1->value.index << endl;
		if (node1->value.coef != 0) {
			//result.AddMonom(node1->value);
			cout << "result = " << result.ToString() << endl;
		}
		//else { break; }
		node1 = node1->pNext;
	}

	while (node2 != other.pStop) {
		cout << node2->value.coef << " " << node2->value.index << endl;
		if (node2->value.coef != 0) {
			//result.AddMonom(node2->value);
			cout << "result = " << result.ToString() << endl;
		}
		//else { break; }
		node2 = node2->pNext;
	}
	cout << "сумма = " << result.ToString() << endl;
	return result;
}

TPolinom TPolinom::AddPolinom(TPolinom& other)
{
	TPolinom result(*this);

	for (TNode<TMonom>* node = other.pFirst; node != other.pStop; node = node->pNext) {
		result.AddMonom(node->value);
	}

	return result;
}

TPolinom TPolinom::operator*(int coef)
{
	TPolinom result(*this);
	for (TNode<TMonom>* node = result.pFirst; node != result.pStop; node = node->pNext) {
		node->value.coef *= coef;
	}
	return result;
}

TPolinom TPolinom::operator*(TPolinom& other)
{
	TPolinom result;
	for (TNode<TMonom>* node1 = this->pFirst; node1 != this->pStop; node1 = node1->pNext) {
		for (TNode<TMonom>* node2 = other.pFirst; node2 != other.pStop; node2 = node2->pNext) {
			TMonom multMonom = node1->value;
			multMonom.coef *= node2->value.coef;
			multMonom.index += node2->value.index;
			result.AddMonom(multMonom);
		}
	}
	return result;
}

bool TPolinom::operator==(TPolinom& other)
{
	if (this->GetLength() != other.GetLength()) {
		return false;
	}

	TNode<TMonom>* node1 = this->pFirst;
	TNode<TMonom>* node2 = other.pFirst;

	while (node1 != this->pStop && node2 != other.pStop) {
		if (!(node1->value == node2->value)) {
			return false;
		}
		node1 = node1->pNext;
		node2 = node2->pNext;
	}

	return true;

}


string TPolinom::ToString() {
	stringstream ss;
	TNode<TMonom>* node = this->pFirst;
	while (node != this->pStop) {
		if (node->value.coef != 0) {
			ss << fixed << setprecision(6) << node->value.coef << "x^" << ((node->value.index / 100) % 10)
				<< "y^" << ((node->value.index / 10) % 10) << "z^" << (node->value.index % 10) << " + ";
		}
		node = node->pNext;
	}
	string result = ss.str();
	if (!result.empty()) {
		result.erase(result.size() - 3);
	}
	return result;
}

