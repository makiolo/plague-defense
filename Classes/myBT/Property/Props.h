#ifndef _PROPS_H_
#define _PROPS_H_

#include <string>
#include "any.hpp"

class Props
{
public:
    using PropsMap = std::unordered_map<std::string, nonstd::any>;

    explicit Props() { ; }
    ~Props() { ; }

    template <typename T>
    inline void set(const std::string& name, const T& value)
    {
        if (_props.count(name) > 0)
        {
            nonstd::any& prop = _props[name];
            prop = value;
        }
        else
        {
            nonstd::any newProperty = value;
            _props.insert(std::make_pair(name, newProperty));
        }
    }

    template <typename T>
    bool _has(const nonstd::any& prop) const
    {
        try
        {
            nonstd::any_cast<const T>(prop);
            return true;
        }
        catch (const nonstd::bad_any_cast&)
        {
            return false;
        }
    }

    template <typename T>
    bool has(const std::string& name) const
    {
        if (has_any(name))
        {
            const nonstd::any& prop = _props.at(name);
            return _has<T>(prop);
        }
        else
        {
            return false;
        }
    }

    inline bool has_any(const std::string& name) const
    {
        return _props.count(name) > 0;
    }

    template <typename T>
    inline T get(const std::string& name) const
    {
        assert(has<T>(name));

        const nonstd::any& prop = _props.at(name);
        return nonstd::any_cast<T>(prop);
    }

    // setters

    inline void set_bool(const std::string& name, bool value)
    {
        set<bool>(name, value);
    }

    inline void set_int(const std::string& name, int value)
    {
        set<int>(name, value);
    }

    inline void set_float(const std::string& name, float value)
    {
        set<float>(name, value);
    }

    inline void set_double(const std::string& name, double value)
    {
        set<double>(name, value);
    }

    inline void set_string(const std::string& name, const std::string& value)
    {
        set<std::string>(name, value);
    }

    // getters

    inline bool get_bool(const std::string& name) const
    {
        return get<bool>(name);
    }

    inline int get_int(const std::string& name) const
    {
        return get<int>(name);
    }

    inline float get_float(const std::string& name) const
    {
        return get<float>(name);
    }

    inline double get_double(const std::string& name) const
    {
        return get<double>(name);
    }

    inline std::string get_string(const std::string& name) const
    {
        return get<std::string>(name);
    }

protected:
    PropsMap _props;
};

#endif // _PROPS_H_
