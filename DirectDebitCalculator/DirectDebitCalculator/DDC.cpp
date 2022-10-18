#include <iostream>
#include <string>

float mVol = 1.02264;
float calorific = 39.4;
float j_kW = 3.6;
float metricConversion = 0.0283168;

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
		kWhGas = m_kWh(ft_m(gasIn));
	}
	else
	{
		cout << "Input not valid" << endl;
		cout << "" << endl;
		goto invalidInput;
	}

	cout << "Please input electricity use (kWh): ";
	cin >> kWhElec;
	cout << "" << endl;

	float gasStandingCharge;
	float gasUnitRate;
	cout << "Please input gas standing charge: ";
	cin >> gasStandingCharge;
	cout << "" << endl;
	cout << "Please input gas unit rate: ";
	cin >> gasUnitRate;
	cout << "" << endl;
	cout << "" << endl;

	float elecStandingCharge;
	float elecUnitRate;
	cout << "Please input electric standing charge: ";
	cin >> elecStandingCharge;
	cout << "" << endl;
	cout << "Please input electric unit rate: ";
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
	float EAC = EDD * 12.f;

	cout << "EAC ~= " + to_string(EAC) << endl;
	cout << "Recomended DD ~= " + to_string(EDD) << endl;

	string a;
	cin >> a;

	return 0;
}