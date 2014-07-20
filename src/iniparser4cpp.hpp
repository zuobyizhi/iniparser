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
    : ini(nullptr)
    {
        reset(inifile);
    }
    ~iniparser4cpp()
    {
        iniparser_freedict(ini);
    }

    inline bool invalid(void) const
    {
        return nullptr==ini;
    }

    void reset(const std::string& inifile)
    {
        assert(!inifile.empty());
        if (!invalid())
        {
            iniparser_freedict(ini);
            assert(invalid());
        }
        ini = iniparser_load(inifile.c_str());
    }

    inline int getnsec(void)
    {
        return iniparser_getnsec(ini);
    }

    inline std::string getsecname(int n)
    {
        return std::string(iniparser_getsecname(ini, n));
    }

    inline std::string getstring(const char * key, char * def=nullptr)
    {
        return std::string(iniparser_getstring(ini, key, def));
    }

    inline int getint(const char * key, int notfound=0)
    {
        return iniparser_getint(ini, key, notfound);
    }

    inline double getdouble(const char * key, double notfound=0.0)
    {
        return iniparser_getdouble(ini, key, notfound);
    }

    inline bool getboolean(const char * key, bool notfound=false)
    {
        return iniparser_getboolean(ini, key, notfound);
    }

    inline bool set(const char * entry, const char * val)
    {
        return 0==iniparser_set(ini, entry, val);
    }

    inline void unset(dictionary * ini, const char * entry)
    {
        iniparser_unset(ini, entry);
    }

    inline bool find_entry(const char * entry)
    {
        return 1==iniparser_find_entry(ini, entry);
    }

private:
    dictionary* ini;
};

#endif // INIPARSER4CPP_HPP_INCLUDED
