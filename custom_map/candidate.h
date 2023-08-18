#pragma once
#include <iostream>

class candidate
{
private:

	std::string surname, name, CNP;
	float grade;
	unsigned int rank;

public:

	candidate();
	candidate(std::string, std::string, std::string, float = 0, unsigned int = 0);

	void setSurname(std::string);
	std::string getSurname() const;

	void setName(std::string);
	std::string getName() const;

	void setCNP(std::string);
	std::string getCNP() const;

	void setGrade(float);
	float getGrade() const;

	void setRank(unsigned int);
	unsigned int getRank() const;

	bool verifyCNP();

	bool operator <(const candidate &) const;
	bool operator >(const candidate &) const;
	bool operator ==(const candidate &) const;
	bool operator !=(const candidate&) const;
};

std::ostream& operator <<(std::ostream&, const candidate&);

