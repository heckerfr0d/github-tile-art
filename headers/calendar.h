#ifndef CALENDAR_H
#define CALENDAR_H
#include <chrono>
#include <vector>
#include <tuple>


//  holds the repo and auth details
struct Config{
    char url[100], cname[50], cmail[80], path[50], auth[50];
};


//  holds the graffiti as a matrix
struct Art{
    int nc, year;
    bool a[7][52];
};


//  comparison function to sort Arts by year
bool cmp(Art a, Art b)
{
    return a.year<b.year;
}

// Returns day of week in civil calendar [0, 6] -> [Sun, Sat]
// Preconditions:  z is number of days since 1970-01-01 and is in the range:
//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-4].
template <class Int>
constexpr unsigned
weekday_from_days(Int z) noexcept
{
    return static_cast<unsigned>(z >= -4 ? (z + 4) % 7 : (z + 5) % 7 + 6);
}

// Preconditions: x <= 6 && y <= 6
// Returns: The number of days from the weekday y to the weekday x.
// The result is always in the range [0, 6].
constexpr unsigned
weekday_difference(unsigned x, unsigned y) noexcept
{
    x -= y;
    return x <= 6 ? x : x + 7;
}

// Returns number of days since civil 1970-01-01.  Negative values indicate
//    days prior to 1970-01-01.
// Preconditions:  y-m-d represents a date in the civil (Gregorian) calendar
//                 m is in [1, 12]
//                 d is in [1, last_day_of_month(y, m)]
//                 y is "approximately" in
//                   [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
//                 Exact range of validity is:
//                 [civil_from_days(numeric_limits<Int>::min()),
//                  civil_from_days(numeric_limits<Int>::max()-719468)]
template <class Int>
constexpr Int
days_from_civil(Int y, unsigned m, unsigned d) noexcept
{
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
                  "This algorithm has not been ported to a 16 bit unsigned integer");
    static_assert(std::numeric_limits<Int>::digits >= 20,
                  "This algorithm has not been ported to a 16 bit signed integer");
    y -= m <= 2;
    const Int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);           // [0, 399]
    const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;          // [0, 146096]
    return era * 146097 + static_cast<Int>(doe) - 719468;
}

// Returns year/month/day triple in civil calendar
// Preconditions:  z is number of days since 1970-01-01 and is in the range:
//                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
template <class Int>
constexpr std::tuple<Int, unsigned, unsigned>
civil_from_days(Int z) noexcept
{
    static_assert(std::numeric_limits<unsigned>::digits >= 18,
                  "This algorithm has not been ported to a 16 bit unsigned integer");
    static_assert(std::numeric_limits<Int>::digits >= 20,
                  "This algorithm has not been ported to a 16 bit signed integer");
    z += 719468;
    const Int era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = static_cast<unsigned>(z - era * 146097);               // [0, 146096]
    const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365; // [0, 399]
    const Int y = static_cast<Int>(yoe) + era * 400;
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100); // [0, 365]
    const unsigned mp = (5 * doy + 2) / 153;                      // [0, 11]
    const unsigned d = doy - (153 * mp + 2) / 5 + 1;              // [1, 31]
    const unsigned m = mp + (mp < 10 ? 3 : -9);                   // [1, 12]
    return std::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
}


//  get the nth day of the week given month and year
std::chrono::system_clock::time_point
get_nth_dow_month_year(unsigned n, unsigned wd, unsigned month, int year)
{
    using namespace std;
    using namespace std::chrono;
    typedef duration<int, ratio_multiply<hours::period, ratio<24>>> days;
    int d = days_from_civil(year, month, 1);
    const unsigned wd_1st = weekday_from_days(d);
    d += weekday_difference(wd, wd_1st) + (n - 1) * 7;
    return system_clock::time_point(days(d));
}


//  get a matrix of dates by weekday given year
std::vector<std::vector<std::chrono::system_clock::time_point>>
dates_by_weekday(int year)
{
    using namespace std;
    using namespace std::chrono;
    std::vector<std::vector<std::chrono::system_clock::time_point>> dates;
    std::chrono::system_clock::time_point sun1 = get_nth_dow_month_year(1, 0, 1, year);
    dates.resize(7 * sizeof(std::vector<std::chrono::system_clock::time_point>));
    for (int x = 0; x < 52 * 7; x++)
        dates[x % 7].push_back(sun1 + hours(x * 24));
    return dates;
}


//  get a matrix of dates by weekday of the last 52 weeks
std::vector<std::vector<std::chrono::system_clock::time_point>>
dates_by_weekday()
{
    using namespace std;
    using namespace std::chrono;
    std::vector<std::vector<std::chrono::system_clock::time_point>> dates;
    unsigned long long d = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())/(24*60*60)-367;
    const unsigned wd_1st = weekday_from_days(d);
    d += weekday_difference(0, wd_1st);
    typedef duration<int, ratio_multiply<hours::period, ratio<24>>> days;
    std::chrono::system_clock::time_point sun1 = std::chrono::system_clock::time_point(days(d));
    dates.resize(7 * sizeof(std::vector<std::chrono::system_clock::time_point>));
    for (int x = 0; x < 52 * 7; x++)
        dates[x % 7].push_back(sun1 + hours(x * 24));
    return dates;
}



#endif // CALENDAR_H
