#pragma once

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <memory>
using namespace std;

template<class Base>
class IocContainer
{
public:
    static IocContainer& GetInstance() {
        static IocContainer instance;
        return instance;
    }

	template<class Derived>
	void Register(const char* key) {
		if (m_map.find(key) != m_map.end()) {
			// throw std::invalid_argument("this key has exist");
		}
		m_map.emplace(key, static_cast<std::shared_ptr<Base>>(std::make_shared<Derived>(key)));
	}

    std::shared_ptr<Base> GetInstanceByKey(const char* key) {
        if (m_map.find(key) == m_map.end()) {
			return nullptr;
		}
		return m_map[key];
    }
private:
	std::map<string, std::shared_ptr<Base>> m_map;
};

template<class Base, class Derived>
class RegisterInstance {
public:
    RegisterInstance(const char* name) {
        IocContainer<Base>::GetInstance().template Register<Derived>(name);
    }
};

#define REGISTER(name) \
    static class RegisterInstance<DbcInterface, Dbc<name##_record, name##_record_count, name##_string_block_size>> name##Instance_(#name);

#define GetInstance(name) IocContainer<DbcInterface>::GetInstance().GetInstanceByKey(name)