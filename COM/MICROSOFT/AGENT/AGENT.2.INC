{$DEFINE PEAKTOP:COM/MICROSOFT/AGENT/AGENT.2.INC}
var
  MicrosoftAgent :Variant;
  //============================================================================
  function CreateMicrosoftAgent(const a_CharacterName:string):Variant;
  begin
    DontAutoFree;
    MicrosoftAgent := CreateOleObject('Agent.Control');
    MicrosoftAgent.Connected := true;
    MicrosoftAgent.Characters.Load(a_CharacterName);
    Result := MicrosoftAgent.Characters.Character(a_CharacterName);
  end;
  //============================================================================
