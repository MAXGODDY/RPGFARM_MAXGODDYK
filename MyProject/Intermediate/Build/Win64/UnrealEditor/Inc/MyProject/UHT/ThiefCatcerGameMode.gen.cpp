// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThiefCatcerGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeThiefCatcerGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
MYPROJECT_API UClass* Z_Construct_UClass_AThiefCatcerGameMode();
MYPROJECT_API UClass* Z_Construct_UClass_AThiefCatcerGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AThiefCatcerGameMode *****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AThiefCatcerGameMode;
UClass* AThiefCatcerGameMode::GetPrivateStaticClass()
{
	using TClass = AThiefCatcerGameMode;
	if (!Z_Registration_Info_UClass_AThiefCatcerGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ThiefCatcerGameMode"),
			Z_Registration_Info_UClass_AThiefCatcerGameMode.InnerSingleton,
			StaticRegisterNativesAThiefCatcerGameMode,
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
	return Z_Registration_Info_UClass_AThiefCatcerGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_AThiefCatcerGameMode_NoRegister()
{
	return AThiefCatcerGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AThiefCatcerGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ThiefCatcerGameMode.h" },
		{ "ModuleRelativePath", "Public/ThiefCatcerGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA

// ********** Begin Class AThiefCatcerGameMode constinit property declarations *********************
// ********** End Class AThiefCatcerGameMode constinit property declarations ***********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AThiefCatcerGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AThiefCatcerGameMode_Statics
UObject* (*const Z_Construct_UClass_AThiefCatcerGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AThiefCatcerGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AThiefCatcerGameMode_Statics::ClassParams = {
	&AThiefCatcerGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AThiefCatcerGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AThiefCatcerGameMode_Statics::Class_MetaDataParams)
};
void AThiefCatcerGameMode::StaticRegisterNativesAThiefCatcerGameMode()
{
}
UClass* Z_Construct_UClass_AThiefCatcerGameMode()
{
	if (!Z_Registration_Info_UClass_AThiefCatcerGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AThiefCatcerGameMode.OuterSingleton, Z_Construct_UClass_AThiefCatcerGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AThiefCatcerGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AThiefCatcerGameMode);
AThiefCatcerGameMode::~AThiefCatcerGameMode() {}
// ********** End Class AThiefCatcerGameMode *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThiefCatcerGameMode_h__Script_MyProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AThiefCatcerGameMode, AThiefCatcerGameMode::StaticClass, TEXT("AThiefCatcerGameMode"), &Z_Registration_Info_UClass_AThiefCatcerGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AThiefCatcerGameMode), 4245484546U) },
	};
}; // Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThiefCatcerGameMode_h__Script_MyProject_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThiefCatcerGameMode_h__Script_MyProject_1277991575{
	TEXT("/Script/MyProject"),
	Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThiefCatcerGameMode_h__Script_MyProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThiefCatcerGameMode_h__Script_MyProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
