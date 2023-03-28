#include <algorithm>
#include <iostream>
#include <string>
#include <memory>

using namespace std;

// Клієнт
class ChemicalElement {
protected:
	string name;
	double density;
	int    position;
public:
	ChemicalElement(string);
	virtual void Show()
	{
		cout << "\nChemical Element: " << name << endl;
	}
};

ChemicalElement::ChemicalElement(string pName) {
	name = pName;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
}

// Адаптований клієнт
class ChemicalElementsInformation {
public:
	double GetDensity(string) const;
	int    GetPositionFromPeriodicTable(string) const;
};

double ChemicalElementsInformation::GetDensity(string pName) const {
	transform(pName.begin(), pName.end(), pName.begin(), ::tolower);
	if (pName == "silicon")
	{
		return 2.33;
	}
	else if (pName == "aluminum")
	{
		return 2.7;
	}
	else if (pName == "barium")
	{
		return 3.76;
	}
	return 0;

}

int ChemicalElementsInformation::GetPositionFromPeriodicTable(string pName) const {
	transform(pName.begin(), pName.end(), pName.begin(), ::tolower);
	if (pName == "silicon")
	{
		return 14;
	}
	else if (pName == "aluminum")
	{
		return 13;
	}
	else if (pName == "barium")
	{
		return 56;
	}
	return -1;
}

// Адаптер
class ExtendedChemicalElement : public ChemicalElement {
private:
	std::unique_ptr <ChemicalElementsInformation> pInformation;
public:
	ExtendedChemicalElement(string);
	void Show();
};

ExtendedChemicalElement::ExtendedChemicalElement(string pName) :ChemicalElement(pName) {
	pInformation = std::make_unique <ChemicalElementsInformation>();
}

void ExtendedChemicalElement::Show() {
	cout << "\n============================\n";
	ChemicalElement::Show();
	density = pInformation->GetDensity(name);
	position = pInformation->GetPositionFromPeriodicTable(name);
	cout << "\nDensity of Element: " << density << endl;
	cout << "\nPosition in Periodic Table: " << position << endl;
	cout << "\n============================\n";
}

int main() {
	std::unique_ptr <ChemicalElement> ptr = std::make_unique<ExtendedChemicalElement>("silicon");
	ptr->Show();

	ptr = std::make_unique<ExtendedChemicalElement>("aluminum");
	ptr->Show();


	ptr = std::make_unique<ExtendedChemicalElement>("barium");
	ptr->Show();

	return 0;
}

/*
* На основі приклада паттерна проектування “Адаптер” створіть:
1) програму, яка замість звичайних вказівників використовуватиме розумні вказівники
*/
