#include "histogram.h"
#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_minus()
{
    double min = 0;
    double max = 0;
    find_minmax({-4,-3,-6},min,max);
    assert(min == -6 );
    assert(max == -3 );
}

void test_onex ()
{
    double min = 0;
    double max = 0;
    find_minmax({31,31,31},min,max);
    assert(min == 31);
    assert(max == 31);

}

void test_one_number()
{
    double min = 0;
    double max = 0;
    find_minmax({7},min,max);
    assert(min == 7);
    assert(max == 7);

}
void test_zero()
{
    double min = 0;
    double max = 0;
    find_minmax({},min,max);
    assert(min == 0);
    assert(max == 0);

}



int main()
{
    test_positive();
    test_minus();
    test_onex();
    test_one_number();
    test_zero();
    return 0;
}


