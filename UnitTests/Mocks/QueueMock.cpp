#include "QueueMock.h"

bool FakeQueue::enter(const HumanInteraction* interaction, IQueue::Callback callback)
{
    queueCallback = callback;
    return false;
}

void FakeQueue::leave(const HumanInteraction* interaction)
{

}

size_t FakeQueue::getPosition(const HumanInteraction* interaction)
{
    return 0;
}

void FakeQueue::callNext()
{

}

QueueMock::QueueMock()
{
    ON_CALL(*this, enter(_, _)).WillByDefault(Invoke(&fakeQueue, &FakeQueue::enter));
}