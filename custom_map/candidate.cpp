#include "candidate.h"

candidate::candidate()
{
	this->surname = "";
	this->name = "";
	this->CNP = "";
	this->grade = 0;
	this->rank = 0;
}

candidate::candidate(std::string surname, std::string name, std::string CNP, float grade, unsigned int rank)
{
	this->surname = surname;
	this->name = name;
	this->CNP = CNP;
	this->grade = grade;
	this->rank = rank;
}

void candidate::setSurname(std::string surname)
{
	this->surname = surname;
}

std::string candidate::getSurname() const
{
	return surname;
}

void candidate::setName(std::string name)
{
	this->name = name;
}

std::string candidate::getName() const
{
	return name;
}

void candidate::setCNP(std::string CNP)
{
	this->CNP = CNP;
}

std::string candidate::getCNP() const
{
	return CNP;
}

void candidate::setGrade(float grade)
{
	this->grade = grade;
}

float candidate::getGrade() const
{
	return grade;
}

void candidate::setRank(unsigned int rank)
{
	this->rank = rank;
}

unsigned int candidate::getRank() const
{
	return rank;
}

bool candidate::verifyCNP()
{
	long long constant = 972853641972;
	long long safetyNumber = 0;

	for (int index = 0; index < 12; index++)
	{
		safetyNumber += ((CNP[index] - '0') * (constant % 10));
		constant /= 10;
	}

	if (safetyNumber % 11 % 10 == (CNP[12] - '0'))
		return true;
	else 
		return false;
}

bool candidate::operator <(const candidate &student) const
{
	if (this->grade < student.grade)
		return true;
	if (this->grade > student.grade)
		return false;

	if (this->surname < student.surname)
		return true;
	if (this->surname > student.surname)
		return false;

	if (this->name < student.name)
		return true;
	if (this->name > student.name)
		return false;

	if (this->CNP < student.CNP)
		return true;

	return false;
}

bool candidate::operator >(const candidate &student) const
{
	return student < *this;
}

bool candidate::operator ==(const candidate & student) const
{
	return this->grade == student.grade && this->name == student.name && this->surname == student.surname && this->CNP == student.CNP;
}

bool candidate::operator!=(const candidate& student) const
{
	return !(*this == student);
}

std::ostream& operator<<(std::ostream& output, const candidate& candidate)
{
	output << candidate.getName() << " " << candidate.getSurname() << " " << candidate.getGrade();
	return output;
}
