// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ThifCatcher.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeThifCatcher() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
MYPROJECT_API UClass* Z_Construct_UClass_AMainCheracter();
MYPROJECT_API UClass* Z_Construct_UClass_AThifCatcher();
MYPROJECT_API UClass* Z_Construct_UClass_AThifCatcher_NoRegister();
UPackage* Z_Construct_UPackage__Script_MyProject();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AThifCatcher *************************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_AThifCatcher;
UClass* AThifCatcher::GetPrivateStaticClass()
{
	using TClass = AThifCatcher;
	if (!Z_Registration_Info_UClass_AThifCatcher.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("ThifCatcher"),
			Z_Registration_Info_UClass_AThifCatcher.InnerSingleton,
			StaticRegisterNativesAThifCatcher,
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
	return Z_Registration_Info_UClass_AThifCatcher.InnerSingleton;
}
UClass* Z_Construct_UClass_AThifCatcher_NoRegister()
{
	return AThifCatcher::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AThifCatcher_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "ThifCatcher.h" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpringArm_MetaData[] = {
		{ "Category", "ThifCatcher" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "Category", "ThifCatcher" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAnimation_MetaData[] = {
		{ "Category", "JampAnimation" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentStamina_MetaData[] = {
		{ "Category", "Stamina" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinusStamina_MetaData[] = {
		{ "Category", "Stamina" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlusStamina_MetaData[] = {
		{ "Category", "Stamina" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stamina_MetaData[] = {
		{ "Category", "Stamina" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
		{ "ModuleRelativePath", "Public/ThifCatcher.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class AThifCatcher constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpringArm;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAnimation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentStamina;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinusStamina;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_PlusStamina;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Stamina;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class AThifCatcher constinit property declarations *******************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AThifCatcher>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_AThifCatcher_Statics

// ********** Begin Class AThifCatcher Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AThifCatcher_Statics::NewProp_SpringArm = { "SpringArm", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AThifCatcher, SpringArm), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpringArm_MetaData), NewProp_SpringArm_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AThifCatcher_Statics::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00100000000a0009, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AThifCatcher, Camera), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AThifCatcher_Statics::NewProp_JumpAnimation = { "JumpAnimation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AThifCatcher, JumpAnimation), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAnimation_MetaData), NewProp_JumpAnimation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThifCatcher_Statics::NewProp_CurrentStamina = { "CurrentStamina", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AThifCatcher, CurrentStamina), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentStamina_MetaData), NewProp_CurrentStamina_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThifCatcher_Statics::NewProp_MinusStamina = { "MinusStamina", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AThifCatcher, MinusStamina), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinusStamina_MetaData), NewProp_MinusStamina_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThifCatcher_Statics::NewProp_PlusStamina = { "PlusStamina", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AThifCatcher, PlusStamina), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlusStamina_MetaData), NewProp_PlusStamina_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AThifCatcher_Statics::NewProp_Stamina = { "Stamina", nullptr, (EPropertyFlags)0x0010000000010001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AThifCatcher, Stamina), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stamina_MetaData), NewProp_Stamina_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AThifCatcher_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThifCatcher_Statics::NewProp_SpringArm,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThifCatcher_Statics::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThifCatcher_Statics::NewProp_JumpAnimation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThifCatcher_Statics::NewProp_CurrentStamina,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThifCatcher_Statics::NewProp_MinusStamina,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThifCatcher_Statics::NewProp_PlusStamina,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AThifCatcher_Statics::NewProp_Stamina,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AThifCatcher_Statics::PropPointers) < 2048);
// ********** End Class AThifCatcher Property Definitions ******************************************
UObject* (*const Z_Construct_UClass_AThifCatcher_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AMainCheracter,
	(UObject* (*)())Z_Construct_UPackage__Script_MyProject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AThifCatcher_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AThifCatcher_Statics::ClassParams = {
	&AThifCatcher::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AThifCatcher_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AThifCatcher_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AThifCatcher_Statics::Class_MetaDataParams), Z_Construct_UClass_AThifCatcher_Statics::Class_MetaDataParams)
};
void AThifCatcher::StaticRegisterNativesAThifCatcher()
{
}
UClass* Z_Construct_UClass_AThifCatcher()
{
	if (!Z_Registration_Info_UClass_AThifCatcher.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AThifCatcher.OuterSingleton, Z_Construct_UClass_AThifCatcher_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AThifCatcher.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, AThifCatcher);
AThifCatcher::~AThifCatcher() {}
// ********** End Class AThifCatcher ***************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThifCatcher_h__Script_MyProject_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AThifCatcher, AThifCatcher::StaticClass, TEXT("AThifCatcher"), &Z_Registration_Info_UClass_AThifCatcher, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AThifCatcher), 3748072234U) },
	};
}; // Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThifCatcher_h__Script_MyProject_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThifCatcher_h__Script_MyProject_2555152924{
	TEXT("/Script/MyProject"),
	Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThifCatcher_h__Script_MyProject_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RPGFARM_MAXGODDYK_MyProject_Source_MyProject_Public_ThifCatcher_h__Script_MyProject_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
