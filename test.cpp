//#include "unit_tests.hpp"
#include "select.hpp"		//included for test
//#include "spreadsheet.hpp"
#include "gtest/gtest.h"

Spreadsheet* sheet = new Spreadsheet();

TEST(Select_Contains, check_correct_output) {
    Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
    s.set_selection(new Select_Contains(&s, "First", "John"));
    s.print_selection(ss);
    EXPECT_EQ("John Apple 22 computer science \n", ss.str());    
}

TEST(Select_Contains, InTheSheet)
{
        sheet->set_column_names({"First","Last", "Age", "Major"});
        sheet->add_row({"Amanda","Andrews","22","business"});
        Select* select = new Select_Contains(sheet,"Last", "Andrews");
        ASSERT_TRUE(select->select(sheet,0));
        delete select;
}


TEST(Select_Contains, EmptySearch)
{
	Select* select = new Select_Contains(sheet, "Last", "");
	ASSERT_TRUE(select->select(sheet,0));
	delete select;
}

TEST(Select_Contains, NotInTheSheet)
{
	Select* select = new Select_Contains(sheet,"Last", "Smith");
	ASSERT_FALSE(select->select(sheet,0));
	delete select;
}

//TEST(Select_Contains, InTheSheet)
//{
//	sheet->set_column_names(("First","Last", "Age", "Major"));
//	sheet->add_row(("Amanda","Andrews","22","business"));
//	Select* select = new Select_Contains(sheet,"Last", "Andrews");
//	ASSERT_TRUE(select->select(sheet,0));
//	delete select;
//}

TEST(Select_Not, InTheSheet)
{
	Select* select = new Select_Not(new Select_Contains(sheet, "Last", "Andrews"));
	ASSERT_FALSE(select->select(sheet, 0));
	delete select;
}

TEST(Select_Not, NotInTheSheet)
{
	Select* select = new Select_Not(new Select_Contains(sheet, "Last", "Jackson"));
	ASSERT_TRUE(select->select(sheet,0));
	delete select;
}

TEST(Select_Or, BothTrue)
{
	Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Amanda"));
	ASSERT_TRUE(select->select(sheet,0));
	delete select;
}

TEST(Select_Or, BothFalse)
{
	Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Jaskson"), new Select_Contains(sheet, "First", "Francine"));
	ASSERT_FALSE(select->select(sheet,0));
	delete select;
}

TEST(Select_Or, OneTrueOneFalse)
{
	Select* select = new Select_Or(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Francine"));
	ASSERT_TRUE(select->select(sheet,0));
	delete select;
}

TEST(Select_And, BothTrue)
{
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Amanda"));
        ASSERT_TRUE(select->select(sheet,0));
        delete select;
}

TEST(Select_And, BothFalse)
{
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Jaskson"), new Select_Contains(sheet, "First", "Francine"));
        ASSERT_FALSE(select->select(sheet,0));
        delete select;
}

TEST(Select_And, OneTrueOneFalse)
{
        Select* select = new Select_And(new Select_Contains(sheet, "Last", "Andrews"), new Select_Contains(sheet, "First", "Francine"));
        ASSERT_FALSE(select->select(sheet,0));
        delete select;
        delete sheet;
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
