#ifndef DATE_ITERATOR_H
#define DATE_ITERATOR_H

#include "ely/traits/type.hpp"

#include "Date.hpp"

#include <boost/date_time/gregorian/gregorian.hpp>

#include <iterator>

namespace ely
{
namespace date
{


template< class functor_type, class date_type >
class DateIterator : public std::iterator <  std::bidirectional_iterator_tag,
                                             date_type,
                                             void >
{
public:
    DateIterator( typename traits::Type< date_type >::ref const date_, unsigned short factor_ = 1 ) noexcept;
    DateIterator( DateIterator< functor_type, date_type > const & date_iterator_ ) noexcept;
    DateIterator( DateIterator< functor_type, date_type > && date_iterator_ ) noexcept;
    DateIterator< functor_type, date_type > & operator =( DateIterator< functor_type, date_type > const & date_iterator_ ) noexcept;
    DateIterator< functor_type, date_type > & operator =( DateIterator< functor_type, date_type > && date_iterator_ ) noexcept;
    ~DateIterator() noexcept;

    typename traits::Type< date_type >::ref operator *();
    typename traits::Type< date_type >::ptr operator ->() noexcept;

    DateIterator & operator ++( void ) noexcept;
    DateIterator & operator --( void ) noexcept;

    bool operator ==( DateIterator< functor_type, date_type > const & date_iterator_ ) const noexcept;
    bool operator !=( DateIterator< functor_type, date_type > const & date_iterator_ ) const noexcept;
    bool operator <( DateIterator< functor_type, date_type > const & date_iterator_ ) const noexcept;
    bool operator <=( DateIterator< functor_type, date_type > const & date_iterator_ ) const noexcept;
    bool operator >( DateIterator< functor_type, date_type > const & date_iterator_ ) const noexcept;
    bool operator >=( DateIterator< functor_type, date_type > const & date_iterator_ ) const noexcept;

private:
    typename boost::date_time::date_itr< functor_type, boost::gregorian::date > date_it;
    Date current_date;
    unsigned short factor;
};

typedef DateIterator < boost::date_time::day_functor< boost::gregorian::date >,
                       Date > DayIterator;
typedef DateIterator < boost::date_time::week_functor< boost::gregorian::date >,
                       Date > WeekIterator;
typedef DateIterator < boost::date_time::month_functor< boost::gregorian::date >,
                       Date > MonthIterator;
typedef DateIterator < boost::date_time::year_functor< boost::gregorian::date >,
                       Date > YearIterator;


} // namespace ::ely::date
} // namespace ::ely

#include "DateIterator.tpp"

#endif // DATE_ITERATOR_H
