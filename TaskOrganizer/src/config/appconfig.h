#pragma once

#include "util/proxy.h"
#include "external/nlohmann_json_fwd.hpp"

class AppConfig
{
#define DEFINE_CONFIG_VARIABLE(type, name, default_value) \
		Variable<type> name {_allVariables, #name, default_value};

public:
	struct VariableBase
	{
		std::string Name;

		VariableBase(std::vector<VariableBase*>& allVariables, const char* name):
			Name{ name }
		{
			allVariables.push_back(this);
		}

		virtual std::string GetValueAsString() const = 0;
		virtual void LoadFromJson(const nlohmann::json& jsonObject) = 0;

	protected:
		// Default function doesn't work, specializations must be defined bellow for supported types.
		template <typename T>
		static T LoadValueFromJson(const nlohmann::json& jsonObject, const char* name) { assert(false); return {}; }

		// Specialization for supported json config types.
		template<>
		static bool LoadValueFromJson(const nlohmann::json& jsonObject, const char* name);
	};

	template <typename T>
	struct Variable : public VariableBase
	{
		T Value;

		Variable(std::vector<VariableBase*>& allVariables, const char* name, const T& value) :
			VariableBase{ allVariables, name },
			Value{ value }
		{

		}
		operator T() { return Value; }
		Variable& operator=(const T& value) { Value = T; return *this; }

		std::string GetValueAsString() const final { return ToString(Value); }
		void LoadFromJson(const nlohmann::json& jsonObject) final { Value = VariableBase::LoadValueFromJson<T>(jsonObject, Name.c_str()); }
	};

public:
	AppConfig();

#if !defined(_RELEASE)
	void PrintConfig();
#endif //!defined(_RELEASE)

// This unfortunate private block here is ugly but this member needs to be defined before the config variables.
private:
	std::vector<VariableBase*> _allVariables;

public:
	// Config variables - currently public for simplicity.
	DEFINE_CONFIG_VARIABLE(bool, ShowWidgetBounds, false);
	DEFINE_CONFIG_VARIABLE(bool, ShowWindowDebug, false);

private:
	void LoadConfig();
};

class AppConfigProxy : public Proxy<AppConfig>
{
public:
	AppConfigProxy();
};