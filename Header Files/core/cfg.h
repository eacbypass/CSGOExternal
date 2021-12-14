#pragma once
// used: std::any
#include <any>
// used: std::filesystem
#include <filesystem>
// used: std::deque
#include <deque>
// used: std::vector
#include <vector>
// used: fnv1a hashing for variables
#include "fnv1a.h"

#pragma region config_definitions
#define C_ADD_VARIABLE( Type, szName, pDefault ) const std::uint32_t szName = C::AddVariable<Type>(FNV1A::HashConst(#szName), FNV1A::HashConst(#Type), pDefault);
#define C_ADD_VARIABLE_VECTOR( Type, uSize, szName, pDefault ) const std::uint32_t szName = C::AddVariable<std::vector<Type>>(FNV1A::HashConst(#szName), FNV1A::HashConst("std::vector<" #Type ">"), MEM::GetFilledVector<Type, uSize>(pDefault));
#define C_INVALID_VARIABLE (std::size_t)(-1)
#pragma endregion
struct VariableObject_t
{
	VariableObject_t(const FNV1A_t uNameHash, const FNV1A_t uTypeHash, std::any&& pDefault)
		: uNameHash(uNameHash), uTypeHash(uTypeHash), pValue(std::move(pDefault)) { }

	~VariableObject_t() = default;

	/* get casted variable value */
	template<typename T>
	T& Get()
	{
		return *static_cast<T*>(std::any_cast<T>(&pValue));
	}

	/* emplace casted variable value */
	template<typename T>
	void Set(T value)
	{
		pValue.emplace<T>(value);
	}

	FNV1A_t uNameHash = 0x0;
	FNV1A_t uTypeHash = 0x0;
	std::any pValue = { };
};

namespace C // @credits: ducarii & rollraw [i stole some of these namespaces from qo0 base]
{
	// Get
/* return variable index by hashed name */
	std::size_t GetVariableIndex(const FNV1A_t uNameHash);
	/* get path where output files will be saved (default: "%userprofile%\documents\.qo0") */
	std::filesystem::path GetWorkingPath();

	// Values
	/* all user config filenames */
	inline std::deque<std::string> vecFileNames = { };
	/* configuration variables */
	inline std::vector<VariableObject_t> vecVariables = { };

	template <typename T>
	T& Get(const std::uint32_t nIndex)
	{
		return vecVariables.at(nIndex).Get<T>();
	}

	/* add new configuration variable to massive, and return index of it */
	template <typename T>
	std::uint32_t AddVariable(const FNV1A_t uNameHash, const FNV1A_t uTypeHash, const T pDefault)
	{
		vecVariables.emplace_back(uNameHash, uTypeHash, std::make_any<T>(pDefault));
		return vecVariables.size() - 1U;
	}
}