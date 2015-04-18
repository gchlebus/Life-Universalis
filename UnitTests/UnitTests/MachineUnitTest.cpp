#include <gtest/gtest.h>
#include "Machine.h"


class MachineTest
    : public ::testing::Test
{
protected:
    Machine machine;
};

TEST_F(MachineTest, AddNullptrAsWorkplace_NothingIsAdded)
{
    machine.addWorkplace(nullptr);
    ASSERT_EQ(0, machine.getWorkplaces().size());
}

TEST_F(MachineTest, AddWorkplace_WorkplaceIsAdded)
{
    machine.addWorkplace(new Workplace());
    ASSERT_EQ(1, machine.getWorkplaces().size());
}

TEST_F(MachineTest, AddSameWorkplaceTwice_WorkplaceIsAddedOnlyOnce)
{
    Workplace* workplace = new Workplace();
    machine.addWorkplace(workplace);
    machine.addWorkplace(workplace);
    ASSERT_EQ(1, machine.getWorkplaces().size());
}
