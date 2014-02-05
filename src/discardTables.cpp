
#include "discardTables.h"

#include <fstream>
#include <sstream>
#include <iostream>



namespace cribslvr { 

bool DiscardTables::tables_exist = false;
bool DiscardTables::instance_flag = false;
DiscardTables* DiscardTables::tables;


DiscardTables* DiscardTables::getTables()
{
	if(instance_flag){
		return tables;
	}
	else{
		tables = new DiscardTables();
		return tables;
	}
}

DiscardTables::DiscardTables(std::string file_name)
{	
	dealer_table = new std::vector<std::vector<RunningAverage> >(13, std::vector<RunningAverage>(13, RunningAverage()));
	pone_table = new std::vector<std::vector<RunningAverage> >(13, std::vector<RunningAverage>(13, RunningAverage()));
	std::ifstream file;
	file.open(file_name.c_str());
	std::string line;
	for(std::vector<std::vector<RunningAverage> >::iterator i=dealer_table->begin(); i!=dealer_table->end();i++){
		std::getline(file, line);
		std::istringstream is(line);
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end();j++){
			is >> j->average;
			is >> j->count;
		}
	}
	std::getline(file, line);
	for(std::vector<std::vector<RunningAverage> >::iterator i=pone_table->begin(); i!=pone_table->end();i++){
		std::getline(file, line);
		std::istringstream is(line);
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end();j++){
			is >> j->average;
			is >> j->count;
		}
	}
}

DiscardTables::DiscardTables()
{
	dealer_table = new std::vector<std::vector<RunningAverage> >(13, std::vector<RunningAverage>(13, RunningAverage()));
	pone_table = new std::vector<std::vector<RunningAverage> >(13, std::vector<RunningAverage>(13, RunningAverage()));
	std::ifstream file;
	file.open("discard_tables");
	std::string line;
	for(std::vector<std::vector<RunningAverage> >::iterator i=dealer_table->begin(); i!=dealer_table->end();i++){
		std::getline(file, line);
		std::istringstream is(line);
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end();j++){
			is >> j->average;
			is >> j->count;
		}
	}
	std::getline(file, line);
	for(std::vector<std::vector<RunningAverage> >::iterator i=pone_table->begin(); i!=pone_table->end();i++){
		std::getline(file, line);
		std::istringstream is(line);
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end();j++){
			is >> j->average;
			is >> j->count;
		}
	}

	instance_flag = true;
}

DiscardTables::~DiscardTables()
{
	delete dealer_table;
	delete pone_table;
}

void DiscardTables::saveTables()
{
	std::ofstream file;
	file.open("discard_tables");
	std::string line;
	for(std::vector<std::vector<RunningAverage> >::iterator i=dealer_table->begin(); i!=dealer_table->end();i++){
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end();j++){
			file << j->average;
			file << " ";
			file << j->count;
			file << " ";
		}
		file << std::endl;
	}
	file << std::endl;
	for(std::vector<std::vector<RunningAverage> >::iterator i=pone_table->begin(); i!=pone_table->end();i++){
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end();j++){
			file << j->average;
			file << " ";
			file << j->count;
			file << " ";
		}
		file << std::endl;
	}
}


bool DiscardTables::doTablesExist(){
	return tables_exist;
}

double DiscardTables::getExpectedValue(bool dealer, int first_card, int second_card)
{
	if(dealer){
		return (*dealer_table)[first_card-1][second_card-1].average;
	}
	else{
		return (*pone_table)[first_card-1][second_card-1].average;
	}
}

void DiscardTables::publishResult(bool dealer, int first_card, int second_card, int value)
{
	if(dealer){
		(*dealer_table)[first_card-1][second_card-1].newValue(value);
	}
	else{
		(*pone_table)[first_card-1][second_card-1].newValue(value);
	}
}


std::string DiscardTables::print()
{
	std::stringstream ss;
	ss.precision(3);
	ss.setf(std::ios::fixed, std::ios::floatfield);
	ss << "Dealer values:" << std::endl;
	
	std::string card_types[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	for(int i=0; i<13; i++){
		ss << card_types[i] << "\t";
	}
	ss<<std::endl;
	int type=0;
	for(std::vector<std::vector<RunningAverage> >::iterator i=dealer_table->begin();i!=dealer_table->end();i++){
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end(); j++){
			ss << j->average;
			ss << "\t";
		}
		ss << card_types[type];
		type++;
		ss << std::endl;	}

	ss << "Non-dealer values:" << std::endl;
	for(int i=0; i<13; i++){
		ss << card_types[i] << "\t";
	}
	ss <<std::endl;
	type = 0;
	for(std::vector<std::vector<RunningAverage> >::iterator i=pone_table->begin();i!=pone_table->end();i++){
		for(std::vector<RunningAverage>::iterator j=i->begin(); j!=i->end(); j++){
			ss << j->average;
			ss << "\t";
		}
		ss << card_types[type];
		type++;
		ss << std::endl;

	}
	return ss.str();
}

}