#include "ely/date_time/Date.hpp"

using ::std::locale;
using ::std::string;
using ::std::istringstream;
using ::std::ostringstream;

using namespace ely::date;
using namespace boost::gregorian;

Date::Date( char const * date_string_ )
    :   the_date( day_clock::local_day() ),
    date_format( "%d/%m/%Y" )
{
    string date_string( date_string_ );

    if ( ! date_string.empty() )
    {
        from_string( date_string );
    }
}

Date::Date( string const & date_string_ )
    :   the_date( day_clock::local_day() ),
    date_format( "%d/%m/%Y" )
{
    if ( ! date_string_.empty() )
    {
        from_string( date_string_ );
    }
}

Date::Date( year const & year_, month const & month_, day const & day_ )
    :   the_date( year_, month_, day_ ),
    date_format( "%d/%m/%Y" )
{}

Date::Date( Date const & date_ )
    :   the_date( date_.the_date ),
    date_format( "%d/%m/%Y" )
{}

Date & Date::operator =( Date date_ )
{
    ::std::swap( the_date, date_.the_date );
    ::std::swap( date_format, date_.date_format );

    return *this;
}

void Date::set_format( const string & date_format_ )
{
    date_format = date_format_;
}

Date & Date::from_string( string const & date_string_ )
{
    date_input_facet * input_facet = new date_input_facet( date_format );

    istringstream iss;
    iss.imbue( locale( iss.getloc(), input_facet ) );

    iss.str( date_string_ );
    iss >> the_date;

    return *this;
}

string Date::to_string() const
{
    date_facet * output_facet = new date_facet( date_format.c_str() );
    ostringstream oss;
    oss.imbue( locale( locale::classic(), output_facet ) );

    oss << the_date;

    return oss.str();
}

Date::day Date::get_day() const
{
    return the_date.day();
}

Date::month Date::get_month() const
{
    return the_date.month();
}

Date::year Date::get_year() const
{
    return the_date.year();
}

void Date::set_day( day day_ )
{
    if ( day_ <= the_date.end_of_month().day() )
    {
        *this = Date( year(), month(), day_ );
    }
}

void Date::set_month( month month_ )
{
    if ( 1 <= month_ && month_ <= 12 )
    {
        *this = Date( year(), month_, day() );
    }
}

void Date::set_year( year year_ )
{
    *this = Date( year_, month(), day() );
}

bool Date::operator ==( Date const & date_ ) const
{
    return the_date == date_.the_date;
}

bool Date::operator !=( Date const & date_ )
{
    return the_date != date_.the_date;
}

bool Date::operator <( Date const & date_ )
{
    return the_date < date_.the_date;
}

bool Date::operator <=( Date const & date_ )
{
    return the_date <= date_.the_date;
}

bool Date::operator >( Date const & date_ )
{
    return the_date > date_.the_date;
}

bool Date::operator >=( Date const & date_ )
{
    return the_date >= date_.the_date;
}

std::ostream & operator <<( std::ostream & out_, Date const & date_ )
{
    return out_ << date_.to_string();
}
