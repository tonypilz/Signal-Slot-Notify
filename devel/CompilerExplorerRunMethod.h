#include <include/signal_slot.h>

//remove prgram once


int run(int i)
{
    if (i<0) return 0;
    sisl::Signal<int(int)> s;
    s.connect(run);
    sisl::detail::ReturnValueAggregateContainerType<int>::type res = s.emit(i-1); //recursive call
    return i + res.front();
}
