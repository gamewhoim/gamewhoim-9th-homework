// Dahoon_ChatX.Build.cs

using UnrealBuildTool;

public class Dahoon_ChatX : ModuleRules
{
    public Dahoon_ChatX(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
			// Initial Dependencies
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
            // UI
			"UMG", "Slate", "SlateCore",

        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        PublicIncludePaths.AddRange(new string[] { });
    }
}
