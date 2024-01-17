#include "pch.h"
#include "config/appconfig.h"

#include "config/staticconfig.h"
#include "util/json.h"

template<>
bool AppConfig::VariableBase::LoadValueFromJson(const nlohmann::json& jsonObject, const char* name)
{
	bool value = false;
	return jsonObject.at(name).get_to(value);
	return value;
}

AppConfig::AppConfig()
{
	LoadConfig();
}

#if defined(USE_DEBUG)
void AppConfig::PrintConfig()
{
	std::cout << "AppConfig:" << std::endl;

	for (const VariableBase* variable : _allVariables)
	{
		std::cout << "  " << variable->Name << ": " << variable->GetValueAsString() << std::endl;
	}
}
#endif //defined(USE_DEBUG)

void AppConfig::LoadConfig()
{
	std::ifstream file(StaticConfig::PATH_CONFIGFILE);
	if (!file.is_open())
	{
		// todo - error
		return;
	}

	nlohmann::json configData = nlohmann::json::parse(file);
	for (VariableBase* variable : _allVariables)
	{
		variable->LoadFromJson(configData);
	}
}

AppConfigProxy::AppConfigProxy() = default;