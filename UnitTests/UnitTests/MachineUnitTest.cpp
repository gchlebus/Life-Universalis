#include <gtest/gtest.h>
#include "Machine.h"

TEST(MachineTest, Constructor)
{
    Machine m;
}

TEST(MachineTest, GetService)
{
    Machine machine;
    machine.getService();
}

TEST(MachineTest, GetQueue)
{
    Machine machine;
    machine.getQueue();
}


TEST(MachineTest, GetWorkplaces)
{
    Machine machine;
    machine.getWorkplaces();
}


TEST(MachineTest, GetParent)
{
    Machine machine;
    machine.getParent();
}

TEST(MachineTest, AddNullptrAsWorkplace_NothingIsAdded)
{
    Machine machine;
    machine.addWorkplace(nullptr);
    ASSERT_EQ(0, machine.getWorkplaces().size());
}


TEST(MachineTest, AddWorkplace_WorkplaceIsAdded)
{
    Machine machine;
    machine.addWorkplace(new Workplace());
    ASSERT_EQ(1, machine.getWorkplaces().size());
}

TEST(MachineTest, AddSameWorkplaceTwice_WorkplaceIsAddedOnlyOnce)
{
    Machine machine;
    Workplace* workplace = new Workplace();
    machine.addWorkplace(workplace);
    machine.addWorkplace(workplace);
    ASSERT_EQ(1, machine.getWorkplaces().size());
}
