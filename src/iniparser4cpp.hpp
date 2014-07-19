#ifndef INIPARSER4CPP_HPP_INCLUDED
#define INIPARSER4CPP_HPP_INCLUDED

#include "iniparser.h"
#include <cassert>

namespace
{
    // boost
    class noncopyable
    {
    protected:
        noncopyable() {}
        ~noncopyable() {}
    private:  // emphasize the following members are private
        noncopyable( const noncopyable& );
        const noncopyable& operator=( const noncopyable& );
    };
}

class iniparser4cpp : public noncopyable
{
public:
    iniparser4cpp(const std::string& inifile)
    {
        assert(!inifile.empty());
        ini = iniparser_load(inifile.c_str());
    }
    ~iniparser4cpp()
    {
        iniparser_freedict(ini);
    }

    int getnsec(void)
    {
        return iniparser_getnsec(ini);
    }

    std::string iniparser_getsecname(int n)
    {
        return std::string(iniparser_getsecname(ini, n));
    }

    std::string getstring(const char * key, char * def=nullptr)
    {
        return std::string(iniparser_getstring(ini, key, def));
    }

    int getint(const char * key, int notfound=0)
    {
        return iniparser_getint(ini, key, notfound);
    }

    double getdouble(const char * key, double notfound=0.0)
    {
        return iniparser_getdouble(ini, key, notfound);
    }

    bool getboolean(const char * key, bool notfound=false)
    {
        return iniparser_getboolean(ini, key, notfound);
    }

    bool set(const char * entry, const char * val)
    {
        return 0==iniparser_set(ini, entry, val);
    }

    void unset(dictionary * ini, const char * entry)
    {
        iniparser_unset(ini, entry);
    }

    bool find_entry(const char * entry)
    {
        return 1==iniparser_find_entry(ini, entry);
    }

private:
    dictionary* ini;
};

#endif // INIPARSER4CPP_HPP_INCLUDED
