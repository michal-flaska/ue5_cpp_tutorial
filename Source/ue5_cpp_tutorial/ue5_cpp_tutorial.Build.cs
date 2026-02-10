// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ue5_cpp_tutorial : ModuleRules
{
	public ue5_cpp_tutorial(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ue5_cpp_tutorial",
			"ue5_cpp_tutorial/Variant_Horror",
			"ue5_cpp_tutorial/Variant_Horror/UI",
			"ue5_cpp_tutorial/Variant_Shooter",
			"ue5_cpp_tutorial/Variant_Shooter/AI",
			"ue5_cpp_tutorial/Variant_Shooter/UI",
			"ue5_cpp_tutorial/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
