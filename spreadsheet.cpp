#include "spreadsheet.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>

Spreadsheet::Spreadsheet()			//Declared a constructor
{
	select = new Select_Construct_Helper();
}

Spreadsheet::~Spreadsheet()
{
    delete select;
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::clear()
{
    column_names.clear();
    data.clear();
    delete select;
    select = nullptr;
}

void Spreadsheet::set_column_names(const std::vector<std::string>& names)
{
    column_names=names;
}

void Spreadsheet::add_row(const std::vector<std::string>& row_data)
{
    data.push_back(row_data);
}

void Spreadsheet::print_selection(std::ostream& out) const			//DEFINED PRINT_SELECTION
{	

	for(int i = 0; i < this->data.size(); i++)			//Version like 38 of this,
	{								//I dont know lol
		if(select->select(this,i))				
		{
			for(auto j : data.at(i))
				out << j << " ";
			out << std::endl;
		}
	}


									//IS THIS RIGHT??
	//for(int i = 0; i < this->data.size(); i++)
	//{
	//	for(int j = 0; j < data.size(); j++)
	//	{
	//		out << data.at(j).at(i) << " " << std::endl;
	//	}
	//}
}

int Spreadsheet::get_column_by_name(const std::string& name) const
{
    for(int i=0; i<column_names.size(); i++)
        if(column_names.at(i) == name)
            return i;
    return -1;
}


