using namespace std;
using namespace ely;
using namespace date;
using namespace traits;

using namespace std;

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>::DateIterator(typename Type<date_type>::ref const date_, unsigned short factor_) noexcept
    :   iterator<bidirectional_iterator_tag, date_type, void>(),
        date_it(boost::gregorian::date(date_.get_year(), date_.get_month(), date_.get_day()),
                factor_),
        current_date(date_),
        factor(factor_)
{}

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>::DateIterator(DateIterator<functor_type, date_type> const & date_iterator_) noexcept
    :   iterator<bidirectional_iterator_tag, date_type, void>(),
        date_it(*(date_iterator_.date_it), date_iterator_.factor),
        current_date(date_iterator_.current_date),
        factor(date_iterator_.factor)
{}

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>::DateIterator(DateIterator<functor_type, date_type> && date_iterator_) noexcept
    :   iterator<bidirectional_iterator_tag, date_type, void>(),
        date_it(move(*(date_iterator_.date_it)), date_iterator_.factor),
        current_date(move(date_iterator_.current_date)),
        factor(move(date_iterator_.factor))
{}

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>& DateIterator<functor_type, date_type>::operator=(DateIterator<functor_type, date_type> const & date_iterator_) noexcept
{
    date_it = date_iterator_.date_it;
    current_date = date_iterator_.current_date;
    factor = date_iterator_.factor;
    
    return *this;
}

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>& DateIterator<functor_type, date_type>::operator=(DateIterator<functor_type, date_type> && date_iterator_) noexcept
{
    date_it = move(date_iterator_.date_it);
    current_date = move(date_iterator_.current_date);
    factor = move(date_iterator_.factor);
    
    return *this;
}

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>::~DateIterator() noexcept
{}

template<class functor_type, class date_type>
typename Type<date_type>::ref DateIterator<functor_type, date_type>::operator*()
{
    current_date = Date(date_it->year(), date_it->month(), date_it->day());
    
    return current_date;
}

template<class functor_type, class date_type>
typename Type<date_type>::ptr DateIterator<functor_type, date_type>::operator->() noexcept
{
    current_date = Date(date_it->year(), date_it->month(), date_it->day());
    
    return &current_date;
}

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>& DateIterator<functor_type, date_type>::operator++(void) noexcept
{
    ++date_it;
    
    return *this;
}

template<class functor_type, class date_type>
DateIterator<functor_type, date_type>& DateIterator<functor_type, date_type>::operator--(void) noexcept
{
    --date_it;
    
    return *this;
}

template<class functor_type, class date_type>
bool DateIterator<functor_type, date_type>::operator==(DateIterator<functor_type, date_type> const & date_it_) const noexcept
{
    return date_it == date_it_.date_it;
}

template<class functor_type, class date_type>
bool DateIterator<functor_type, date_type>::operator!=(DateIterator<functor_type, date_type> const & date_it_) const noexcept
{
    return date_it != date_it_.date_it;
}

template<class functor_type, class date_type>
bool DateIterator<functor_type, date_type>::operator<(DateIterator<functor_type, date_type> const & date_it_) const noexcept
{
    return date_it < date_it_.date_it;
}

template<class functor_type, class date_type>
bool DateIterator<functor_type, date_type>::operator<=(DateIterator<functor_type, date_type> const & date_it_) const noexcept
{
    return date_it <= date_it_.date_it;
}

template<class functor_type, class date_type>
bool DateIterator<functor_type, date_type>::operator>(DateIterator<functor_type, date_type> const & date_it_) const noexcept
{
    return date_it > date_it_.date_it;
}

template<class functor_type, class date_type>
bool DateIterator<functor_type, date_type>::operator>=(DateIterator<functor_type, date_type> const & date_it_) const noexcept
{
    return date_it >= date_it_.date_it;
}
