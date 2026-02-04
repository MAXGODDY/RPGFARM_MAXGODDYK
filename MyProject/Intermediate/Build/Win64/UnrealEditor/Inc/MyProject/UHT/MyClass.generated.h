// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MyClass.h"

#ifdef MYPROJECT_MyClass_generated_h
#error "MyClass.generated.h already included, missing '#pragma once' in MyClass.h"
#endif
#define MYPROJECT_MyClass_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class AMyClass *****************************************************************
struct Z_Construct_UClass_AMyClass_Statics;
MYPROJECT_API UClass* Z_Construct_UClass_AMyClass_NoRegister();

#define FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h_11_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAMyClass(); \
	friend struct ::Z_Construct_UClass_AMyClass_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MYPROJECT_API UClass* ::Z_Construct_UClass_AMyClass_NoRegister(); \
public: \
	DECLARE_CLASS2(AMyClass, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/MyProject"), Z_Construct_UClass_AMyClass_NoRegister) \
	DECLARE_SERIALIZER(AMyClass)


#define FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h_11_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	AMyClass(AMyClass&&) = delete; \
	AMyClass(const AMyClass&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AMyClass); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AMyClass); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AMyClass) \
	NO_API virtual ~AMyClass();


#define FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h_8_PROLOG
#define FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h_11_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h_11_INCLASS_NO_PURE_DECLS \
	FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h_11_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class AMyClass;

// ********** End Class AMyClass *******************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
