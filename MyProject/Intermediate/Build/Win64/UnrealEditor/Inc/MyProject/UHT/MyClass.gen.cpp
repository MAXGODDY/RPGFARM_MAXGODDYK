// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MyClass.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMyClass() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor();
MYPROJECT_API UClass* Z_Construct_UClass_AMyClass();
MYPROJECT_API UClass* Z_Construct_UClass_AMyClass_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AMyClass *****************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AMyClass;
UClass* AMyClass::GetPrivateStaticClass()
{
	using TClass = AMyClass;
	if (!Z_Registration_Info_UClass_AMyClass.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MyClass"),
			Z_Registration_Info_UClass_AMyClass.InnerSingleton,
			StaticRegisterNativesAMyClass,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_AMyClass.InnerSingleton;
}
UClass* Z_Construct_UClass_AMyClass_NoRegister()
{
	return AMyClass::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AMyClass_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MyClass.h" },
		{ "ModuleRelativePath", "Public/MyClass.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AMyClass constinit property declarations *********************************
// ********** End Class AMyClass constinit property declarations ***********************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyClass>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AMyClass_Statics
UObject* (*const Z_Construct_UClass_AMyClass_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AMyClass_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AMyClass_Statics::ClassParams = {
	&AMyClass::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AMyClass_Statics::Class_MetaDataParams), Z_Construct_UClass_AMyClass_Statics::Class_MetaDataParams)
};
void AMyClass::StaticRegisterNativesAMyClass()
{
}
UClass* Z_Construct_UClass_AMyClass()
{
	if (!Z_Registration_Info_UClass_AMyClass.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AMyClass.OuterSingleton, Z_Construct_UClass_AMyClass_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AMyClass.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AMyClass);
AMyClass::~AMyClass() {}
// ********** End Class AMyClass *******************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h__Script_MyProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AMyClass, AMyClass::StaticClass, TEXT("AMyClass"), &Z_Registration_Info_UClass_AMyClass, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AMyClass), 2824322681U) },
	};
}; // Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h__Script_MyProject_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h__Script_MyProject_2070491771{
	TEXT("/Script/MyProject"),
	Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h__Script_MyProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_MyClass_h__Script_MyProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
