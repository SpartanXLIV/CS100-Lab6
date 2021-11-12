#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <string>	//added
#include <cstring>
#include "spreadsheet.hpp"

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.

class Select_Construct_Helper : public Select						//added
{
public:
	virtual bool select(const Spreadsheet* sheet, int row) const
	{
		return 1;							//stops an empty from just being null or garbage
	}
};

class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;		//the s is the (row, column) from the above select
};

class Select_Contains: public Select_Column			//extend Select_Column rather than Select_Contains
{
protected:
	std::string search;		//using to compare
public:
	Select_Contains(const Spreadsheet* sheet, const std::string& col, const std::string& s) :Select_Column(sheet, col), search(s) {} //extend Select_Column
	
	virtual bool select(const std::string& s) const			//bool select will be used alot in other classes
	{
		if (s.find(search) != std::string::npos) return 1;	//checks if string is contained
		return 0;						//by checking with parameter
	}
};

class Select_Not: public Select						//DEclared Select_Not
{									//basically the oposite of Select_Contains
protected:
	Select* x;
public:
	Select_Not(Select* input) :x(input) {}

	~Select_Not()
	{
		delete x;
	}
	virtual bool select(const Spreadsheet* sheet, int row) const
	{
		return !x->select(sheet, row);
	}
};

class Select_And: public Select
{
protected:
	Select* x;
	Select* y;
public:
	~Select_And()
	{
		delete x;
		delete y;
	}
	Select_And(Select* input1, Select* input2) :x(input1), y(input2) {}

	virtual bool select(const Spreadsheet* sheet, int row) const
	{
		return x->select(sheet, row) && y->select(sheet,row);		//and &&
	}
};

class Select_Or: public Select						//DEclared Select_Or
{									//SAME AS Select_And
protected:
	Select* x;
	Select* y;
public:
	~Select_Or()							//deconstructor
	{
		delete x;
		delete y;
	}
	Select_Or(Select* input1, Select* input2) :x(input1), y(input2) {}

	virtual bool select(const Spreadsheet* sheet, int row) const
	{
		return x->select(sheet, row) || y->select(sheet, row);		//or ||
	}
};









#endif //__SELECT_HPP__
