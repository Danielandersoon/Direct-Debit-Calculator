/*
*	This is a prototype open source project made by Daniel Anderson
*	The aim is to make a calculator to find an aprox. DD for your energy
*	bills based on prior usage and the prices of your current tariff.
*
*	Please do not use this for financial advice, I am in NO WAY qualified
*	to speak on such matters. 
*	Any harm caused by use of this program is soley the fault of the user.
*/

#include <iostream>
#include <string>

// Const declairations
float mVol = 1.02264;
float calorific = 39.4;
float j_kW = 3.6;
float metricConversion = 0.0283168;

// variables used in runtime
int NoMonths;
int NoDays;
bool m3;

float ft_m(float ft)
{
	// converts from ft^3 to m^3
	return (ft * metricConversion);
}

float m_kWh(float m)
{
	// converts from m^3 to kW
	return (m * mVol * calorific / j_kW);
}


float calculateDailyFuelCost(float fuelUsage, float unitPrice)
{
	// finds avg cost per day based on pervious usage (in gbp)
	return ((fuelUsage / (((NoMonths * 30.f) + NoDays)) * unitPrice));
}

float calculateMonthlyFuelCost(float fuelUsage, float standingCharge, float unitPrice)
{
	// uses aprox daily cost to find aprox yearly cost (in gbp)
	float cost = calculateDailyFuelCost(fuelUsage, unitPrice);

	// times daily cost of units by days in month
	cost *= 30.f;
	cost += standingCharge * 30.f;
	return cost;
}

using namespace std;
int main()
{
	float kWhElec;
	float kWhGas;

invalidInput:
	cout << "Is the gas in m3? Y/N: ";
	char ism;
	cin >> ism;

	float gasIn;
	cout << "Please input gas in what ever unit you have selected: ";
	cin >> gasIn;

	if (ism == 'Y' || ism == 'y')
	{
		kWhGas = m_kWh(gasIn);
	}
	else if (ism == 'N' || ism == 'n')
	{
		// First must convert from ft3 to m3
		kWhGas = m_kWh(ft_m(gasIn));
	}
	else
	{
		// non valid input
		cout << "Input not valid" << endl;
		cout << "" << endl;
		goto invalidInput;
	}

	cout << "Please input electricity use (kWh): ";
	cin >> kWhElec;
	cout << "" << endl;

	float gasStandingCharge;
	float gasUnitRate;
	cout << "Please input gas standing charge in GBP: ";
	cin >> gasStandingCharge;
	cout << "" << endl;
	cout << "Please input gas unit rate in GBP: ";
	cin >> gasUnitRate;
	cout << "" << endl;
	cout << "" << endl;

	float elecStandingCharge;
	float elecUnitRate;
	cout << "Please input electric standing charge in GBP: ";
	cin >> elecStandingCharge;
	cout << "" << endl;
	cout << "Please input electric unit rate in GBP: ";
	cin >> elecUnitRate;
	cout << "" << endl;
	cout << "" << endl;

	cout << "Please input the number of FULL months this is over: ";
	cin >> NoMonths;
	cout << "Please input the number of days remaining: ";
	cin >> NoDays;

	cout << "" << endl;
	cout << "" << endl;

	float EDD = calculateMonthlyFuelCost(kWhGas, gasStandingCharge, gasUnitRate) + calculateMonthlyFuelCost(kWhElec, elecStandingCharge, elecUnitRate);
	float EAC = EDD * 12.f; // ~12 months 

	char accountForBall;
	cout << "Would you like to take into account the acount ballance?: ";
	cin >> accountForBall;

	if (accountForBall == 'Y' || accountForBall == 'y')
	{
		float Ballance;
		cout << "Please input ballance on account in GBP: "
		cin >> Ballance;

		Ballance /= 6; // assumes use over 6 months
		cout << "EAC ~= " + to_string(EAC) << endl;
		EDD -= Ballance;
		cout << "Recomended DD ~= " + to_string(EDD) << endl;
	}
	else if (accountForBall == 'N' || accountForBall == 'n')
	{
		cout << "EAC ~= " + to_string(EAC) << endl;
		cout << "Recomended DD ~= " + to_string(EDD) << endl;
	}
	else
	{
		cout << "Input not valid" << endl;
		cout << "" << endl;
		goto invalidInput2;
	}

	string a;
	cin >> a;

	return 0;
}
