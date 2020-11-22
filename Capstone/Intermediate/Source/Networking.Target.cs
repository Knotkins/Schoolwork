using UnrealBuildTool;

public class NetworkingTarget : TargetRules
{
	public NetworkingTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("Networking");
	}
}
