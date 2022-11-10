#pragma once
#include <cstdint>
constexpr uint32_t Spell_record_count = 23544;
constexpr uint32_t Spell_string_block_size = 816621;
struct Spell_record {
    uint32_t ID;
    uint32_t SchoolMask;
    uint32_t Category;
    int32_t castUI;
    uint32_t Dispel;
    uint32_t Mechanic;
    uint32_t Attributes;
    uint32_t AttributesEx;
    uint32_t AttributesEx2;
    uint32_t AttributesEx3;
    uint32_t AttributesEx4;
    uint32_t ShapeshiftMask;
    uint32_t ShapeshiftExclude;
    uint32_t Targets;
    uint32_t TargetCreatureType;
    uint32_t RequiresSpellFocus;
    uint32_t CasterAuraState;
    uint32_t TargetAuraState;
    uint32_t CastingTimeIndex;
    uint32_t RecoveryTime;
    uint32_t CategoryRecoveryTime;
    uint32_t InterruptFlags;
    uint32_t AuraInterruptFlags;
    uint32_t ChannelInterruptFlags;
    uint32_t ProcFlags;
    uint32_t ProcChance;
    uint32_t ProcCharges;
    uint32_t MaximumLevel;
    uint32_t BaseLevel;
    uint32_t SpellLevel;
    uint32_t DurationIndex;
    uint32_t PowerType;
    uint32_t ManaCost;
    uint32_t ManaCostPerLevel;
    uint32_t ManaPerSecond;
    uint32_t ManaPerSecondPerLevel;
    uint32_t RangeIndex;
    uint32_t Speed;
    uint32_t ModalNextSpell;
    uint32_t StackAmount;
    uint32_t Totem1;
    uint32_t Totem2;
    int32_t Reagent1;
    int32_t Reagent2;
    int32_t Reagent3;
    int32_t Reagent4;
    int32_t Reagent5;
    int32_t Reagent6;
    int32_t Reagent7;
    int32_t Reagent8;
    uint32_t ReagentCount1;
    uint32_t ReagentCount2;
    uint32_t ReagentCount3;
    uint32_t ReagentCount4;
    uint32_t ReagentCount5;
    uint32_t ReagentCount6;
    uint32_t ReagentCount7;
    uint32_t ReagentCount8;
    int32_t EquippedItemClass;
    int32_t EquippedItemSubClassMask;
    int32_t EquippedItemInventoryTypeMask;
    uint32_t Effect1;
    uint32_t Effect2;
    uint32_t Effect3;
    int32_t EffectDieSides1;
    int32_t EffectDieSides2;
    int32_t EffectDieSides3;
    int32_t EffectBaseDice1;
    int32_t EffectBaseDice2;
    int32_t EffectBaseDice3;
    int32_t EffectDicePerLevel1;
    int32_t EffectDicePerLevel2;
    int32_t EffectDicePerLevel3;
    int32_t EffectRealPointsPerLevel1;
    int32_t EffectRealPointsPerLevel2;
    int32_t EffectRealPointsPerLevel3;
    int32_t EffectBasePoints1;
    int32_t EffectBasePoints2;
    int32_t EffectBasePoints3;
    uint32_t EffectMechanic1;
    uint32_t EffectMechanic2;
    uint32_t EffectMechanic3;
    uint32_t EffectImplicitTargetA1;
    uint32_t EffectImplicitTargetA2;
    uint32_t EffectImplicitTargetA3;
    uint32_t EffectImplicitTargetB1;
    uint32_t EffectImplicitTargetB2;
    uint32_t EffectImplicitTargetB3;
    uint32_t EffectRadiusIndex1;
    uint32_t EffectRadiusIndex2;
    uint32_t EffectRadiusIndex3;
    uint32_t EffectApplyAuraName1;
    uint32_t EffectApplyAuraName2;
    uint32_t EffectApplyAuraName3;
    uint32_t EffectAmplitude1;
    uint32_t EffectAmplitude2;
    uint32_t EffectAmplitude3;
    float EffectMultipleValue1;
    float EffectMultipleValue2;
    float EffectMultipleValue3;
    uint32_t EffectChainTarget1;
    uint32_t EffectChainTarget2;
    uint32_t EffectChainTarget3;
    uint32_t EffectItemType1;
    uint32_t EffectItemType2;
    uint32_t EffectItemType3;
    int32_t EffectMiscValue1;
    int32_t EffectMiscValue2;
    int32_t EffectMiscValue3;
    uint32_t EffectTriggerSpell1;
    uint32_t EffectTriggerSpell2;
    uint32_t EffectTriggerSpell3;
    float EffectPointsPerComboPoint1;
    float EffectPointsPerComboPoint2;
    float EffectPointsPerComboPoint3;
    uint32_t SpellVisual1;
    uint32_t SpellVisual2;
    uint32_t SpellIconID;
    uint32_t ActiveIconID;
    uint32_t SpellPriority;
    char* SpellName0;
    char* SpellName1;
    char* SpellName2;
    char* SpellName3;
    char* SpellName4;
    char* SpellName5;
    char* SpellName6;
    char* SpellName7;
    uint32_t SpellNameFlag0;
    char* SpellRank0;
    char* SpellRank1;
    char* SpellRank2;
    char* SpellRank3;
    char* SpellRank4;
    char* SpellRank5;
    char* SpellRank6;
    char* SpellRank7;
    uint32_t SpellRankFlags0;
    char* SpellDescription0;
    char* SpellDescription1;
    char* SpellDescription2;
    char* SpellDescription3;
    char* SpellDescription4;
    char* SpellDescription5;
    char* SpellDescription6;
    char* SpellDescription7;
    uint32_t SpellDescriptionFlags0;
    char* SpellToolTip0;
    char* SpellToolTip1;
    char* SpellToolTip2;
    char* SpellToolTip3;
    char* SpellToolTip4;
    char* SpellToolTip5;
    char* SpellToolTip6;
    char* SpellToolTip7;
    uint32_t SpellToolTipFlags0;
    uint32_t ManaCostPercentage;
    uint32_t StartRecoveryCategory;
    uint32_t StartRecoveryTime;
    uint32_t MaximumTargetLevel;
    uint32_t SpellClassSet;
    uint32_t SpellClassMask1;
    uint32_t SpellClassMask2;
    uint32_t MaximumAffectedTargets;
    uint32_t DamageClass;
    uint32_t PreventionType;
    uint32_t StanceBarOrder;
    float EffectDamageMultiplier1;
    float EffectDamageMultiplier2;
    float EffectDamageMultiplier3;
    uint32_t MinimumFactionId;
    uint32_t MinimumReputation;
    uint32_t RequiredAuraVision;
};
