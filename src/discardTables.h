#ifndef CSDISCARD_TABLES_H
#define CSDISCARD_TABLES_H

#include <vector>
#include <string>
#include <sstream>

namespace cribslvr {

class RunningAverage{
public:

	int count;
	double average;

	RunningAverage()
	{
		count = 0; 
		average = 0;
	}
	void newValue(double value)
	{
		int newCount = count + 1;
		average = (average*count + value)/newCount;
		count = newCount;
	}
};	 

class DiscardTables {

public:
	static DiscardTables* getTables();
	DiscardTables(std::string file);
	static bool doTablesExist();

	double getExpectedValue(bool dealer, int first_card, int second_card);
	void publishResult(bool dealer, int first_card, int second_card, int value);

	std::string print();

	void saveTables();
		~DiscardTables();

private:
	DiscardTables();
	std::vector<std::vector<RunningAverage> > *dealer_table;
	std::vector<std::vector<RunningAverage> > *pone_table;
	static bool tables_exist;
	static bool instance_flag;
	static DiscardTables* tables;

};

}
#endif