#ifndef __UNIT_TEST_HPP__
#define __UNIT_TEST_HPP__

#include "select.hpp"
#include "spreadsheet.hpp"
#include "gtest/gtest.h"

Spreadsheet* sheet = new Spreadsheet();

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
//        sheet->set_column_names(("First","Last", "Age", "Major"));
//        sheet->add_row(("Amanda","Andrews","22","business"));
//        Select* select = new Select_Contains(sheet,"Last", "Andrews");
//        ASSERT_TRUE(select->select(sheet,0));
//        delete select;
//}
//
#endif
