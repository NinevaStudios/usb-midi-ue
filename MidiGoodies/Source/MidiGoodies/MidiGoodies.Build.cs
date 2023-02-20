// Copyright (c) 2023 Nineva Studios

using System.IO;
using UnrealBuildTool;

#if UE_5_0_OR_LATER
using EpicGames.Core;
#else
using Tools.DotNETCommon;
#endif

public class MidiGoodies : ModuleRules
{
	public MidiGoodies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(new[] { Path.Combine(ModuleDirectory, "Public") });
		PrivateIncludePaths.AddRange(new[] { Path.Combine(ModuleDirectory, "Private") });
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		if (Target.Platform == UnrealTargetPlatform.Android)
		{
			PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android")); // "Private/Android"
			PrivateDependencyModuleNames.Add("Launch");
			var PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "MidiGoodies_Android_UPL.xml"));

		}
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
	}


}
