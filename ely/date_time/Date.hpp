#ifndef DATE_H
#define DATE_H

#include <boost/date_time/gregorian/gregorian.hpp>

#include <string>

namespace ely
{
namespace date
{

class Date
{
private:
    /**
     * @brief La date
     *
     * La date dans son type réel.
     */
    boost::gregorian::date the_date;
    /**
     * @brief Format de la date
     *
     * Format de la date sous forme de chaîne de caractères.\n
     * Le format sera utilisé pour la création de date à partir d'une chaîne de caractères et
     * pour la transformation d'une date en chaîne de caratères.
     * Le format par défaut est : %d/%m/%Y
     */
    std::string date_format;

public:
    /**
     * Le type représentant un jour
     */
    typedef unsigned short day;
    /**
     * Le type représentant un mois
     */
    typedef unsigned short month;
    /**
     * Le type représentant une année
     */
    typedef unsigned short year;

    /**
     * @brief Constructeur
     *
     * Si le paramètre <em>date_string_</em> est fournit et que la chaîne de caractères
     * représente une date au format valide, la date construite est celle de <em>date_string_</em>.\n
     * Sinon la date du jour est utilisée pour initialiser l'objet.
     *
     * @param date_string_ Paramètre optionnel représentant une date sous forme de chaîne de caractères au format C
     *
     * @see from_string(std::string const &)
     * @see Date(std::string const &)
     * @see Date(year, month, day)
     * @see Date(Date const &)
     * @see operator=(Date)
     */
    Date( char const * date_string_ = "" );

    /**
     * @brief Constructeur
     *
     * Constructeur par défaut\n
     *  Si le paramètre <em>date_string_</em> est fournit et que la chaîne de caractères
     *  représente une date au format valide, la date construite est celle de <em>date_string_</em>.\n
     *  Sinon la date du jour est utilisée pour initialiser l'objet.
     *
     * @param date_string_ Paramètre optionnel représentant une date sous forme de chaîne de caractères
     *
     * @see from_string(std::string const &)
     * @see Date(char const *)
     * @see Date(year, month, day)
     * @see Date(Date const &)
     * @see operator=(Date)
     */
    Date( std::string const & date_string_ = std::string() );

    /**
     * @brief Constructeur
     *
     * Construit un objet Date depuis le numéro de l'année, du mois et du jour
     *
     * @param year_ Numéro de l'année
     * @param month_    Numéro du mois
     * @param day_  Numéro du jour
     *
     * @see Date(char const *)
     * @see Date(std::string const &)
     * @see Date(Date const &)
     * @see operator=(Date)
     */
    Date( year const & year_, month const & month_, day const & day_ );

    /**
     * @brief Constructeur
     *
     * Constructeur par copie
     *
     * @param date_ la date à copier
     *
     * @see Date(char const *)
     * @see Date(std::string const &)
     * @see Date(year, month, day)
     * @see operator=(Date)
     */
    Date( Date const & date_ );

    /**
     * @brief Opérateur d'affectation
     *
     * Initialise la date depuis une autre date
     *
     * @param date_ la date à copier
     *
     * @return Une référence sur la date initialisée
     *
     * @see Date(char const *)
     * @see Date(std::string const &)
     * @see Date(year, month, day)
     * @see Date(Date const &)
     */
    Date & operator =( Date date_ );

    /**
     * @brief Définit le format utilisé pour les traitements sous forme de chaîne de caractères
     *
     * @param date_format_ Le nouveau format à utiliser
     *
     * @see from_string(std::string const &)
     * @see to_string() const
     */
    void set_format( std::string const & date_format_ );

    /**
     * @brief Change la date depuis une chaîne de caractères
     *
     * Change la date actuelle par celle contenue dans <em>date_string_</em> si son format est valide.\n
     * Si le format de <em>date_string_</em> est invalide, la date conserve son ancienne valeure.
     *
     * @param date_string_ La nouvelle date
     *
     * @return Une référence sur la date modifiée
     *
     * @see Date(char const &)
     * @see Date(std::string const &)
     * @see set_format(std::string const &)
     */
    Date & from_string( std::string const & date_string_ );

    /**
     * @brief Retourne une représentation de l'objet sous forme de chaîne de caractères
     *
     * @return Une chaîne de caractères représentant l'objet.
     *
     * @see set_format(std::string const &)
     */
    std::string to_string() const;

    /**
     * @brief Retourne le numéro du jour
     *
     * @return Le numéro du jour
     */
    day get_day() const;
    /**
     * @brief Retourne le numéro du mois
     *
     * @return Le numéro du mois
     */
    month get_month() const;
    /**
     * @brief Retourne l'année
     *
     * @return L'année
     */
    year get_year() const;

    /**
     * @brief Définit le jour
     *
     * Si le numéro du jour est plus grand que le dernier jour du mois de l'année de la date actuelle, la date ne change pas.
     *
     * @param day_ Le nouveau jour
     */
    void set_day( day day_ );
    /**
     * @brief Définit le mois
     *
     * Si le mois n'est pas valide la date ne change pas.
     *
     * @param month_ Le nouveau mois
     */
    void set_month( month month_ );
    /**
     * @brief Définit l'année
     *
     * @param year_ La nouvelle année
     */
    void set_year( year year_ );

    /**
     * @brief Opérateur de comparaison
     *
     * Compare deux dates pour savoir si se sont les mêmes
     *
     * @param date_ La date à comparer
     *
     * @return true si les dates sont les mêmes, sinon false
     *
     * @see operator!=(Date const &) const
     * @see operator<(Date const &) const
     * @see operator<=(Date const &) const
     * @see operator>(Date const &) const
     * @see operator>=(Date const &) const
     */
    bool operator ==( Date const & date_ ) const;

    /**
     * @brief Opérateur de comparaison
     *
     * Compare deux dates pour savoir si elles sont différentes
     *
     * @param date_ La date à comparer
     *
     * @return true si les dates sont différentes, sinon false
     *
     * @see operator==(Date const &) const
     * @see operator<(Date const &) const
     * @see operator<=(Date const &) const
     * @see operator>(Date const &) const
     * @see operator>=(Date const &) const
     */
    bool operator !=( Date const & date_ );

    /**
     * @brief Opérateur de comparaison
     *
     * Compare deux dates pour savoir la qu'elle est la plus ancienne
     *
     * @param date_ La date à comparer
     *
     * @return true si la date actuelle est plus récente que <em>date_</em>, sinon false
     *
     * @see operator==(Date const &) const
     * @see operator!=(Date const &) const
     * @see operator<=(Date const &) const
     * @see operator>(Date const &) const
     * @see operator>=(Date const &) const
     */
    bool operator <( Date const & date_ );

    /**
     * @brief Opérateur de comparaison
     *
     * Compare deux dates pour savoir la qu'elle est la plus ancienne
     *
     * @param date_ La date à comparer
     *
     * @return true si la date actuelle est plus récente ou égale à <em>date_</em>, sinon false
     *
     * @see operator==(Date const &) const
     * @see operator!=(Date const &) const
     * @see operator<(Date const &) const
     * @see operator>(Date const &) const
     * @see operator>=(Date const &) const
     */
    bool operator <=( Date const & date_ );

    /**
     * @brief Opérateur de comparaison
     *
     * Compare deux dates pour savoir la qu'elle est la plus ancienne
     *
     * @param date_ La date à comparer
     *
     * @return true si la date actuelle est plus ancienne que <em>date_</em>, sinon false
     *
     * @see operator==(Date const &) const
     * @see operator!=(Date const &) const
     * @see operator<(Date const &) const
     * @see operator<=(Date const &) const
     * @see operator>=(Date const &) const
     */
    bool operator >( Date const & date_ );

    /**
     * @brief Opérateur de comparaison
     *
     * Compare deux dates pour savoir la qu'elle est la plus ancienne
     *
     * @param date_ La date à comparer
     *
     * @return true si la date actuelle est plus ancienne ou égale à <em>date_</em>, sinon false
     *
     * @see operator==(Date const &) const
     * @see operator!=(Date const &) const
     * @see operator<(Date const &) const
     * @see operator<=(Date const &) const
     * @see operator>(Date const &) const
     */
    bool operator >=( Date const & date_ );
};

} // namespace ::ely::date
} // namespace ::ely

std::ostream & operator <<( std::ostream & out_, ely::date::Date const & date_ );

#endif // DATE_H
