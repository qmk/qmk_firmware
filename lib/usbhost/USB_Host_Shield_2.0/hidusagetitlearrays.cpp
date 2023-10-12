/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */
#if !defined(__HIDUSAGETITLEARRAYS_H__)
#define __HIDUSAGETITLEARRAYS_H__

#include "hidusagestr.h"

// This is here why?

//const char *usagePageTitles0[]	PROGMEM =
//{
//	pstrUsagePageGenericDesktopControls	,
//	pstrUsagePageSimulationControls		,
//	pstrUsagePageVRControls				,
//	pstrUsagePageSportControls			,
//	pstrUsagePageGameControls			,
//	pstrUsagePageGenericDeviceControls	,
//	pstrUsagePageKeyboardKeypad			,
//	pstrUsagePageLEDs					,
//	pstrUsagePageButton					,
//	pstrUsagePageOrdinal				,
//	pstrUsagePageTelephone				,
//	pstrUsagePageConsumer				,
//	pstrUsagePageDigitizer				,
//	pstrUsagePagePID					,
//	pstrUsagePageUnicode
//};
//
//const char *usagePageTitles1[]	PROGMEM =
//{
//	pstrUsagePageBarCodeScanner			,
//	pstrUsagePageScale					,
//	pstrUsagePageMSRDevices				,
//	pstrUsagePagePointOfSale			,
//	pstrUsagePageCameraControl			,
//	pstrUsagePageArcade
//};
//const char *genDesktopTitles0[] PROGMEM =
//{
//	pstrUsagePointer					,
//	pstrUsageMouse						,
//	pstrUsageJoystick					,
//	pstrUsageGamePad					,
//	pstrUsageKeyboard					,
//	pstrUsageKeypad						,
//	pstrUsageMultiAxisController		,
//	pstrUsageTabletPCSystemControls
//
//};
//const char *genDesktopTitles1[] PROGMEM =
//{
//	pstrUsageX							,
//	pstrUsageY							,
//	pstrUsageZ							,
//	pstrUsageRx							,
//	pstrUsageRy							,
//	pstrUsageRz							,
//	pstrUsageSlider						,
//	pstrUsageDial						,
//	pstrUsageWheel						,
//	pstrUsageHatSwitch					,
//	pstrUsageCountedBuffer				,
//	pstrUsageByteCount					,
//	pstrUsageMotionWakeup				,
//	pstrUsageStart						,
//	pstrUsageSelect						,
//	pstrUsagePageReserved				,
//	pstrUsageVx							,
//	pstrUsageVy							,
//	pstrUsageVz							,
//	pstrUsageVbrx						,
//	pstrUsageVbry						,
//	pstrUsageVbrz						,
//	pstrUsageVno						,
//	pstrUsageFeatureNotification		,
//	pstrUsageResolutionMultiplier
//};
//const char *genDesktopTitles2[] PROGMEM =
//{
//	pstrUsageSystemControl		,
//	pstrUsageSystemPowerDown	,
//	pstrUsageSystemSleep		,
//	pstrUsageSystemWakeup		,
//	pstrUsageSystemContextMenu	,
//	pstrUsageSystemMainMenu		,
//	pstrUsageSystemAppMenu		,
//	pstrUsageSystemMenuHelp		,
//	pstrUsageSystemMenuExit		,
//	pstrUsageSystemMenuSelect	,
//	pstrUsageSystemMenuRight	,
//	pstrUsageSystemMenuLeft		,
//	pstrUsageSystemMenuUp		,
//	pstrUsageSystemMenuDown		,
//	pstrUsageSystemColdRestart	,
//	pstrUsageSystemWarmRestart	,
//	pstrUsageDPadUp				,
//	pstrUsageDPadDown			,
//	pstrUsageDPadRight			,
//	pstrUsageDPadLeft
//};
//const char *genDesktopTitles3[] PROGMEM =
//{
//	pstrUsageSystemDock				,
//	pstrUsageSystemUndock			,
//	pstrUsageSystemSetup			,
//	pstrUsageSystemBreak			,
//	pstrUsageSystemDebuggerBreak	,
//	pstrUsageApplicationBreak		,
//	pstrUsageApplicationDebuggerBreak,
//	pstrUsageSystemSpeakerMute		,
//	pstrUsageSystemHibernate
//};
//const char *genDesktopTitles4[] PROGMEM =
//{
//	pstrUsageSystemDisplayInvert		,
//	pstrUsageSystemDisplayInternal		,
//	pstrUsageSystemDisplayExternal		,
//	pstrUsageSystemDisplayBoth			,
//	pstrUsageSystemDisplayDual			,
//	pstrUsageSystemDisplayToggleIntExt	,
//	pstrUsageSystemDisplaySwapPriSec	,
//	pstrUsageSystemDisplayLCDAutoscale
//};
//const char *simuTitles0[] PROGMEM =
//{
//	pstrUsageFlightSimulationDevice		,
//	pstrUsageAutomobileSimulationDevice	,
//	pstrUsageTankSimulationDevice		,
//	pstrUsageSpaceshipSimulationDevice	,
//	pstrUsageSubmarineSimulationDevice	,
//	pstrUsageSailingSimulationDevice	,
//	pstrUsageMotocicleSimulationDevice	,
//	pstrUsageSportsSimulationDevice		,
//	pstrUsageAirplaneSimulationDevice	,
//	pstrUsageHelicopterSimulationDevice	,
//	pstrUsageMagicCarpetSimulationDevice,
//	pstrUsageBicycleSimulationDevice
//};
//const char *simuTitles1[] PROGMEM =
//{
//	pstrUsageFlightControlStick			,
//	pstrUsageFlightStick				,
//	pstrUsageCyclicControl				,
//	pstrUsageCyclicTrim					,
//	pstrUsageFlightYoke					,
//	pstrUsageTrackControl
//};
//const char *simuTitles2[] PROGMEM =
//{
//	pstrUsageAileron					,
//	pstrUsageAileronTrim				,
//	pstrUsageAntiTorqueControl			,
//	pstrUsageAutopilotEnable			,
//	pstrUsageChaffRelease				,
//	pstrUsageCollectiveControl			,
//	pstrUsageDiveBrake					,
//	pstrUsageElectronicCountermeasures	,
//	pstrUsageElevator					,
//	pstrUsageElevatorTrim				,
//	pstrUsageRudder						,
//	pstrUsageThrottle					,
//	pstrUsageFlightCommunications		,
//	pstrUsageFlareRelease				,
//	pstrUsageLandingGear				,
//	pstrUsageToeBrake					,
//	pstrUsageTrigger					,
//	pstrUsageWeaponsArm					,
//	pstrUsageWeaponsSelect				,
//	pstrUsageWingFlaps					,
//	pstrUsageAccelerator				,
//	pstrUsageBrake						,
//	pstrUsageClutch						,
//	pstrUsageShifter					,
//	pstrUsageSteering					,
//	pstrUsageTurretDirection			,
//	pstrUsageBarrelElevation			,
//	pstrUsageDivePlane					,
//	pstrUsageBallast					,
//	pstrUsageBicycleCrank				,
//	pstrUsageHandleBars					,
//	pstrUsageFrontBrake					,
//	pstrUsageRearBrake
//};
//const char *vrTitles0[]	PROGMEM =
//{
//	pstrUsageBelt				,
//	pstrUsageBodySuit			,
//	pstrUsageFlexor				,
//	pstrUsageGlove				,
//	pstrUsageHeadTracker		,
//	pstrUsageHeadMountedDisplay	,
//	pstrUsageHandTracker		,
//	pstrUsageOculometer			,
//	pstrUsageVest				,
//	pstrUsageAnimatronicDevice
//};
//const char *vrTitles1[]	PROGMEM =
//{
//	pstrUsageStereoEnable	,
//	pstrUsageDisplayEnable
//};
//const char *sportsCtrlTitles0[]	PROGMEM =
//{
//	pstrUsageBaseballBat				,
//	pstrUsageGolfClub					,
//	pstrUsageRowingMachine				,
//	pstrUsageTreadmill
//};
//const char *sportsCtrlTitles1[]	PROGMEM =
//{
//	pstrUsageOar						,
//	pstrUsageSlope						,
//	pstrUsageRate						,
//	pstrUsageStickSpeed					,
//	pstrUsageStickFaceAngle				,
//	pstrUsageStickHeelToe				,
//	pstrUsageStickFollowThough			,
//	pstrUsageStickTempo					,
//	pstrUsageStickType					,
//	pstrUsageStickHeight
//};
//const char *sportsCtrlTitles2[]	PROGMEM =
//{
//	pstrUsagePutter						,
//	pstrUsage1Iron						,
//	pstrUsage2Iron						,
//	pstrUsage3Iron						,
//	pstrUsage4Iron						,
//	pstrUsage5Iron						,
//	pstrUsage6Iron						,
//	pstrUsage7Iron						,
//	pstrUsage8Iron						,
//	pstrUsage9Iron						,
//	pstrUsage10Iron						,
//	pstrUsage11Iron						,
//	pstrUsageSandWedge					,
//	pstrUsageLoftWedge					,
//	pstrUsagePowerWedge					,
//	pstrUsage1Wood						,
//	pstrUsage3Wood						,
//	pstrUsage5Wood						,
//	pstrUsage7Wood						,
//	pstrUsage9Wood
//};
//const char *gameTitles0[] PROGMEM =
//{
//	pstrUsage3DGameController		,
//	pstrUsagePinballDevice			,
//	pstrUsageGunDevice
//};
//const char *gameTitles1[] PROGMEM =
//{
//	pstrUsagePointOfView			,
//	pstrUsageTurnRightLeft			,
//	pstrUsagePitchForwardBackward	,
//	pstrUsageRollRightLeft			,
//	pstrUsageMoveRightLeft			,
//	pstrUsageMoveForwardBackward	,
//	pstrUsageMoveUpDown				,
//	pstrUsageLeanRightLeft			,
//	pstrUsageLeanForwardBackward	,
//	pstrUsageHeightOfPOV			,
//	pstrUsageFlipper				,
//	pstrUsageSecondaryFlipper		,
//	pstrUsageBump					,
//	pstrUsageNewGame				,
//	pstrUsageShootBall				,
//	pstrUsagePlayer					,
//	pstrUsageGunBolt				,
//	pstrUsageGunClip				,
//	pstrUsageGunSelector			,
//	pstrUsageGunSingleShot			,
//	pstrUsageGunBurst				,
//	pstrUsageGunAutomatic			,
//	pstrUsageGunSafety				,
//	pstrUsageGamepadFireJump		,
//	pstrUsageGamepadTrigger
//};
//const char *genDevCtrlTitles[] PROGMEM =
//{
//	pstrUsageBatteryStrength,
//	pstrUsageWirelessChannel,
//	pstrUsageWirelessID,
//	pstrUsageDiscoverWirelessControl,
//	pstrUsageSecurityCodeCharEntered,
//	pstrUsageSecurityCodeCharErased,
//	pstrUsageSecurityCodeCleared
//};
//const char *ledTitles[] PROGMEM =
//{
//	pstrUsageNumLock						,
//	pstrUsageCapsLock					,
//	pstrUsageScrollLock					,
//	pstrUsageCompose					,
//	pstrUsageKana						,
//	pstrUsagePower						,
//	pstrUsageShift						,
//	pstrUsageDoNotDisturb				,
//	pstrUsageMute						,
//	pstrUsageToneEnable					,
//	pstrUsageHighCutFilter				,
//	pstrUsageLowCutFilter				,
//	pstrUsageEqualizerEnable			,
//	pstrUsageSoundFieldOn				,
//	pstrUsageSurroundOn					,
//	pstrUsageRepeat						,
//	pstrUsageStereo						,
//	pstrUsageSamplingRateDetect			,
//	pstrUsageSpinning					,
//	pstrUsageCAV						,
//	pstrUsageCLV						,
//	pstrUsageRecordingFormatDetect		,
//	pstrUsageOffHook					,
//	pstrUsageRing						,
//	pstrUsageMessageWaiting				,
//	pstrUsageDataMode					,
//	pstrUsageBatteryOperation			,
//	pstrUsageBatteryOK					,
//	pstrUsageBatteryLow					,
//	pstrUsageSpeaker					,
//	pstrUsageHeadSet					,
//	pstrUsageHold						,
//	pstrUsageMicrophone					,
//	pstrUsageCoverage					,
//	pstrUsageNightMode					,
//	pstrUsageSendCalls					,
//	pstrUsageCallPickup					,
//	pstrUsageConference					,
//	pstrUsageStandBy					,
//	pstrUsageCameraOn					,
//	pstrUsageCameraOff					,
//	pstrUsageOnLine						,
//	pstrUsageOffLine					,
//	pstrUsageBusy						,
//	pstrUsageReady						,
//	pstrUsagePaperOut					,
//	pstrUsagePaperJam					,
//	pstrUsageRemote						,
//	pstrUsageForward					,
//	pstrUsageReverse					,
//	pstrUsageStop						,
//	pstrUsageRewind						,
//	pstrUsageFastForward				,
//	pstrUsagePlay						,
//	pstrUsagePause						,
//	pstrUsageRecord						,
//	pstrUsageError						,
//	pstrUsageSelectedIndicator			,
//	pstrUsageInUseIndicator				,
//	pstrUsageMultiModeIndicator			,
//	pstrUsageIndicatorOn				,
//	pstrUsageIndicatorFlash				,
//	pstrUsageIndicatorSlowBlink			,
//	pstrUsageIndicatorFastBlink			,
//	pstrUsageIndicatorOff				,
//	pstrUsageFlashOnTime				,
//	pstrUsageSlowBlinkOnTime			,
//	pstrUsageSlowBlinkOffTime			,
//	pstrUsageFastBlinkOnTime			,
//	pstrUsageFastBlinkOffTime			,
//	pstrUsageIndicatorColor				,
//	pstrUsageIndicatorRed				,
//	pstrUsageIndicatorGreen				,
//	pstrUsageIndicatorAmber				,
//	pstrUsageGenericIndicator			,
//	pstrUsageSystemSuspend				,
//	pstrUsageExternalPowerConnected
//};
//const char *telTitles0			[] PROGMEM =
//{
//	pstrUsagePhone				,
//	pstrUsageAnsweringMachine	,
//	pstrUsageMessageControls	,
//	pstrUsageHandset			,
//	pstrUsageHeadset			,
//	pstrUsageTelephonyKeyPad	,
//	pstrUsageProgrammableButton
//};
//const char *telTitles1			[] PROGMEM =
//{
//	pstrUsageHookSwitch					,
//	pstrUsageFlash						,
//	pstrUsageFeature					,
//	pstrUsageHold						,
//	pstrUsageRedial						,
//	pstrUsageTransfer					,
//	pstrUsageDrop						,
//	pstrUsagePark						,
//	pstrUsageForwardCalls				,
//	pstrUsageAlternateFunction			,
//	pstrUsageLine						,
//	pstrUsageSpeakerPhone				,
//	pstrUsageConference				,
//	pstrUsageRingEnable				,
//	pstrUsageRingSelect				,
//	pstrUsagePhoneMute				,
//	pstrUsageCallerID				,
//	pstrUsageSend
//};
//const char *telTitles2			[] PROGMEM =
//{
//	pstrUsageSpeedDial		,
//	pstrUsageStoreNumber	,
//	pstrUsageRecallNumber	,
//	pstrUsagePhoneDirectory
//};
//const char *telTitles3			[] PROGMEM =
//{
//	pstrUsageVoiceMail		,
//	pstrUsageScreenCalls	,
//	pstrUsageDoNotDisturb	,
//	pstrUsageMessage		,
//	pstrUsageAnswerOnOff
//};
//const char *telTitles4			[] PROGMEM =
//{
//	pstrUsageInsideDialTone			,
//	pstrUsageOutsideDialTone		,
//	pstrUsageInsideRingTone			,
//	pstrUsageOutsideRingTone		,
//	pstrUsagePriorityRingTone		,
//	pstrUsageInsideRingback			,
//	pstrUsagePriorityRingback		,
//	pstrUsageLineBusyTone			,
//	pstrUsageReorderTone			,
//	pstrUsageCallWaitingTone		,
//	pstrUsageConfirmationTone1		,
//	pstrUsageConfirmationTone2		,
//	pstrUsageTonesOff				,
//	pstrUsageOutsideRingback		,
//	pstrUsageRinger
//};
//const char *telTitles5			[] PROGMEM =
//{
//	pstrUsagePhoneKey0		,
//	pstrUsagePhoneKey1		,
//	pstrUsagePhoneKey2		,
//	pstrUsagePhoneKey3		,
//	pstrUsagePhoneKey4		,
//	pstrUsagePhoneKey5		,
//	pstrUsagePhoneKey6		,
//	pstrUsagePhoneKey7		,
//	pstrUsagePhoneKey8		,
//	pstrUsagePhoneKey9		,
//	pstrUsagePhoneKeyStar	,
//	pstrUsagePhoneKeyPound	,
//	pstrUsagePhoneKeyA		,
//	pstrUsagePhoneKeyB		,
//	pstrUsagePhoneKeyC		,
//	pstrUsagePhoneKeyD
//};
//const char *consTitles0[]	PROGMEM	=
//{
//	pstrUsageConsumerControl,
//	pstrUsageNumericKeyPad,
//	pstrUsageProgrammableButton,
//	pstrUsageMicrophone,
//	pstrUsageHeadphone,
//	pstrUsageGraphicEqualizer
//};
//const char *consTitles1[]	PROGMEM	=
//{
//	pstrUsagePlus10	,
//	pstrUsagePlus100,
//	pstrUsageAMPM
//};
//const char *consTitles2[]	PROGMEM	=
//{
//	pstrUsagePower			,
//	pstrUsageReset			,
//	pstrUsageSleep			,
//	pstrUsageSleepAfter		,
//	pstrUsageSleepMode		,
//	pstrUsageIllumination	,
//	pstrUsageFunctionButtons
//
//};
//const char *consTitles3[]	PROGMEM	=
//{
//	pstrUsageMenu			,
//	pstrUsageMenuPick		,
//	pstrUsageMenuUp			,
//	pstrUsageMenuDown		,
//	pstrUsageMenuLeft		,
//	pstrUsageMenuRight		,
//	pstrUsageMenuEscape		,
//	pstrUsageMenuValueIncrease,
//	pstrUsageMenuValueDecrease
//};
//const char *consTitles4[]	PROGMEM	=
//{
//	pstrUsageDataOnScreen		,
//	pstrUsageClosedCaption		,
//	pstrUsageClosedCaptionSelect,
//	pstrUsageVCRTV				,
//	pstrUsageBroadcastMode		,
//	pstrUsageSnapshot			,
//	pstrUsageStill
//};
//const char *consTitles5[]	PROGMEM	=
//{
//	pstrUsageSelection					,
//	pstrUsageAssignSelection			,
//	pstrUsageModeStep					,
//	pstrUsageRecallLast					,
//	pstrUsageEnterChannel				,
//	pstrUsageOrderMovie					,
//	pstrUsageChannel					,
//	pstrUsageMediaSelection				,
//	pstrUsageMediaSelectComputer		,
//	pstrUsageMediaSelectTV				,
//	pstrUsageMediaSelectWWW				,
//	pstrUsageMediaSelectDVD				,
//	pstrUsageMediaSelectTelephone		,
//	pstrUsageMediaSelectProgramGuide	,
//	pstrUsageMediaSelectVideoPhone		,
//	pstrUsageMediaSelectGames			,
//	pstrUsageMediaSelectMessages		,
//	pstrUsageMediaSelectCD				,
//	pstrUsageMediaSelectVCR				,
//	pstrUsageMediaSelectTuner			,
//	pstrUsageQuit						,
//	pstrUsageHelp						,
//	pstrUsageMediaSelectTape			,
//	pstrUsageMediaSelectCable			,
//	pstrUsageMediaSelectSatellite		,
//	pstrUsageMediaSelectSecurity		,
//	pstrUsageMediaSelectHome			,
//	pstrUsageMediaSelectCall			,
//	pstrUsageChannelIncrement			,
//	pstrUsageChannelDecrement			,
//	pstrUsageMediaSelectSAP				,
//	pstrUsagePageReserved				,
//	pstrUsageVCRPlus					,
//	pstrUsageOnce						,
//	pstrUsageDaily						,
//	pstrUsageWeekly						,
//	pstrUsageMonthly
//};
//const char *consTitles6[]	PROGMEM	=
//{
//	pstrUsagePlay					,
//	pstrUsagePause					,
//	pstrUsageRecord					,
//	pstrUsageFastForward			,
//	pstrUsageRewind					,
//	pstrUsageScanNextTrack			,
//	pstrUsageScanPreviousTrack		,
//	pstrUsageStop					,
//	pstrUsageEject					,
//	pstrUsageRandomPlay				,
//	pstrUsageSelectDisk				,
//	pstrUsageEnterDisk				,
//	pstrUsageRepeat					,
//	pstrUsageTracking					,
//	pstrUsageTrackNormal				,
//	pstrUsageSlowTracking				,
//	pstrUsageFrameForward				,
//	pstrUsageFrameBackwards				,
//	pstrUsageMark						,
//	pstrUsageClearMark					,
//	pstrUsageRepeatFromMark				,
//	pstrUsageReturnToMark				,
//	pstrUsageSearchMarkForward			,
//	pstrUsageSearchMarkBackwards		,
//	pstrUsageCounterReset				,
//	pstrUsageShowCounter				,
//	pstrUsageTrackingIncrement			,
//	pstrUsageTrackingDecrement			,
//	pstrUsageStopEject					,
//	pstrUsagePlayPause					,
//	pstrUsagePlaySkip
//};
//const char *consTitles7[]	PROGMEM	=
//{
//	pstrUsageVolume						,
//	pstrUsageBalance					,
//	pstrUsageMute						,
//	pstrUsageBass						,
//	pstrUsageTreble						,
//	pstrUsageBassBoost					,
//	pstrUsageSurroundMode				,
//	pstrUsageLoudness					,
//	pstrUsageMPX						,
//	pstrUsageVolumeIncrement			,
//	pstrUsageVolumeDecrement
//};
//const char *consTitles8[]	PROGMEM	=
//{
//	pstrUsageSpeedSelect				,
//	pstrUsagePlaybackSpeed				,
//	pstrUsageStandardPlay				,
//	pstrUsageLongPlay					,
//	pstrUsageExtendedPlay				,
//	pstrUsageSlow
//};
//const char *consTitles9[]	PROGMEM	=
//{
//	pstrUsageFanEnable					,
//	pstrUsageFanSpeed					,
//	pstrUsageLightEnable				,
//	pstrUsageLightIlluminationLevel		,
//	pstrUsageClimateControlEnable		,
//	pstrUsageRoomTemperature			,
//	pstrUsageSecurityEnable				,
//	pstrUsageFireAlarm					,
//	pstrUsagePoliceAlarm				,
//	pstrUsageProximity					,
//	pstrUsageMotion						,
//	pstrUsageDuresAlarm					,
//	pstrUsageHoldupAlarm					,
//	pstrUsageMedicalAlarm
//};
//const char *consTitlesA[]	PROGMEM	=
//{
//	pstrUsageBalanceRight				,
//	pstrUsageBalanceLeft				,
//	pstrUsageBassIncrement				,
//	pstrUsageBassDecrement				,
//	pstrUsageTrebleIncrement			,
//	pstrUsageTrebleDecrement
//};
//const char *consTitlesB[]	PROGMEM	=
//{
//	pstrUsageSpeakerSystem				,
//	pstrUsageChannelLeft				,
//	pstrUsageChannelRight				,
//	pstrUsageChannelCenter				,
//	pstrUsageChannelFront				,
//	pstrUsageChannelCenterFront			,
//	pstrUsageChannelSide				,
//	pstrUsageChannelSurround			,
//	pstrUsageChannelLowFreqEnhancement	,
//	pstrUsageChannelTop					,
//	pstrUsageChannelUnknown
//};
//const char *consTitlesC[]	PROGMEM	=
//{
//	pstrUsageSubChannel					,
//	pstrUsageSubChannelIncrement		,
//	pstrUsageSubChannelDecrement		,
//	pstrUsageAlternateAudioIncrement	,
//	pstrUsageAlternateAudioDecrement
//};
//const char *consTitlesD[]	PROGMEM	=
//{
//	pstrUsageApplicationLaunchButtons	,
//	pstrUsageALLaunchButtonConfigTool	,
//	pstrUsageALProgrammableButton		,
//	pstrUsageALConsumerControlConfig	,
//	pstrUsageALWordProcessor			,
//	pstrUsageALTextEditor				,
//	pstrUsageALSpreadsheet				,
//	pstrUsageALGraphicsEditor			,
//	pstrUsageALPresentationApp			,
//	pstrUsageALDatabaseApp				,
//	pstrUsageALEmailReader				,
//	pstrUsageALNewsreader				,
//	pstrUsageALVoicemail				,
//	pstrUsageALContactsAddressBook		,
//	pstrUsageALCalendarSchedule			,
//	pstrUsageALTaskProjectManager		,
//	pstrUsageALLogJournalTimecard		,
//	pstrUsageALCheckbookFinance			,
//	pstrUsageALCalculator				,
//	pstrUsageALAVCapturePlayback		,
//	pstrUsageALLocalMachineBrowser		,
//	pstrUsageALLANWANBrow				,
//	pstrUsageALInternetBrowser			,
//	pstrUsageALRemoteNetISPConnect		,
//	pstrUsageALNetworkConference		,
//	pstrUsageALNetworkChat				,
//	pstrUsageALTelephonyDialer			,
//	pstrUsageALLogon					,
//	pstrUsageALLogoff					,
//	pstrUsageALLogonLogoff				,
//	pstrUsageALTermLockScrSav			,
//	pstrUsageALControlPannel			,
//	pstrUsageALCommandLineProcessorRun	,
//	pstrUsageALProcessTaskManager		,
//	pstrUsageALSelectTaskApplication	,
//	pstrUsageALNextTaskApplication		,
//	pstrUsageALPreviousTaskApplication	,
//	pstrUsageALPreemptiveHaltTaskApp	,
//	pstrUsageALIntegratedHelpCenter		,
//	pstrUsageALDocuments				,
//	pstrUsageALThesaurus				,
//	pstrUsageALDictionary				,
//	pstrUsageALDesktop					,
//	pstrUsageALSpellCheck				,
//	pstrUsageALGrammarCheck				,
//	pstrUsageALWirelessStatus			,
//	pstrUsageALKeyboardLayout			,
//	pstrUsageALVirusProtection			,
//	pstrUsageALEncryption				,
//	pstrUsageALScreenSaver				,
//	pstrUsageALAlarms					,
//	pstrUsageALClock					,
//	pstrUsageALFileBrowser				,
//	pstrUsageALPowerStatus				,
//	pstrUsageALImageBrowser				,
//	pstrUsageALAudioBrowser				,
//	pstrUsageALMovieBrowser				,
//	pstrUsageALDigitalRightsManager		,
//	pstrUsageALDigitalWallet			,
//	pstrUsagePageReserved				,
//	pstrUsageALInstantMessaging			,
//	pstrUsageALOEMFeaturesBrowser		,
//	pstrUsageALOEMHelp					,
//	pstrUsageALOnlineCommunity			,
//	pstrUsageALEntertainmentContentBrow	,
//	pstrUsageALOnlineShoppingBrowser	,
//	pstrUsageALSmartCardInfoHelp		,
//	pstrUsageALMarketMonitorFinBrowser	,
//	pstrUsageALCustomCorpNewsBrowser		,
//	pstrUsageALOnlineActivityBrowser		,
//	pstrUsageALResearchSearchBrowser		,
//	pstrUsageALAudioPlayer
//};
//const char *consTitlesE[]	PROGMEM	=
//{
//	pstrUsageGenericGUIAppControls		,
//	pstrUsageACNew						,
//	pstrUsageACOpen						,
//	pstrUsageACClose					,
//	pstrUsageACExit						,
//	pstrUsageACMaximize					,
//	pstrUsageACMinimize					,
//	pstrUsageACSave						,
//	pstrUsageACPrint					,
//	pstrUsageACProperties				,
//	pstrUsageACUndo						,
//	pstrUsageACCopy						,
//	pstrUsageACCut						,
//	pstrUsageACPaste					,
//	pstrUsageACSelectAll				,
//	pstrUsageACFind						,
//	pstrUsageACFindAndReplace			,
//	pstrUsageACSearch					,
//	pstrUsageACGoto						,
//	pstrUsageACHome						,
//	pstrUsageACBack						,
//	pstrUsageACForward					,
//	pstrUsageACStop						,
//	pstrUsageACRefresh					,
//	pstrUsageACPreviousLink				,
//	pstrUsageACNextLink					,
//	pstrUsageACBookmarks				,
//	pstrUsageACHistory					,
//	pstrUsageACSubscriptions			,
//	pstrUsageACZoomIn					,
//	pstrUsageACZoomOut					,
//	pstrUsageACZoom						,
//	pstrUsageACFullScreenView			,
//	pstrUsageACNormalView				,
//	pstrUsageACViewToggle				,
//	pstrUsageACScrollUp					,
//	pstrUsageACScrollDown				,
//	pstrUsageACScroll					,
//	pstrUsageACPanLeft					,
//	pstrUsageACPanRight					,
//	pstrUsageACPan						,
//	pstrUsageACNewWindow				,
//	pstrUsageACTileHoriz				,
//	pstrUsageACTileVert					,
//	pstrUsageACFormat					,
//	pstrUsageACEdit						,
//	pstrUsageACBold						,
//	pstrUsageACItalics					,
//	pstrUsageACUnderline				,
//	pstrUsageACStrikethrough			,
//	pstrUsageACSubscript				,
//	pstrUsageACSuperscript				,
//	pstrUsageACAllCaps					,
//	pstrUsageACRotate					,
//	pstrUsageACResize					,
//	pstrUsageACFlipHorizontal			,
//	pstrUsageACFlipVertical				,
//	pstrUsageACMirrorHorizontal			,
//	pstrUsageACMirrorVertical			,
//	pstrUsageACFontSelect				,
//	pstrUsageACFontColor				,
//	pstrUsageACFontSize					,
//	pstrUsageACJustifyLeft				,
//	pstrUsageACJustifyCenterH			,
//	pstrUsageACJustifyRight				,
//	pstrUsageACJustifyBlockH			,
//	pstrUsageACJustifyTop				,
//	pstrUsageACJustifyCenterV			,
//	pstrUsageACJustifyBottom			,
//	pstrUsageACJustifyBlockV			,
//	pstrUsageACIndentDecrease			,
//	pstrUsageACIndentIncrease			,
//	pstrUsageACNumberedList				,
//	pstrUsageACRestartNumbering			,
//	pstrUsageACBulletedList				,
//	pstrUsageACPromote					,
//	pstrUsageACDemote					,
//	pstrUsageACYes						,
//	pstrUsageACNo						,
//	pstrUsageACCancel					,
//	pstrUsageACCatalog					,
//	pstrUsageACBuyChkout				,
//	pstrUsageACAddToCart				,
//	pstrUsageACExpand					,
//	pstrUsageACExpandAll				,
//	pstrUsageACCollapse					,
//	pstrUsageACCollapseAll				,
//	pstrUsageACPrintPreview				,
//	pstrUsageACPasteSpecial				,
//	pstrUsageACInsertMode				,
//	pstrUsageACDelete					,
//	pstrUsageACLock						,
//	pstrUsageACUnlock					,
//	pstrUsageACProtect					,
//	pstrUsageACUnprotect				,
//	pstrUsageACAttachComment			,
//	pstrUsageACDeleteComment			,
//	pstrUsageACViewComment				,
//	pstrUsageACSelectWord				,
//	pstrUsageACSelectSentence			,
//	pstrUsageACSelectParagraph			,
//	pstrUsageACSelectColumn				,
//	pstrUsageACSelectRow				,
//	pstrUsageACSelectTable				,
//	pstrUsageACSelectObject				,
//	pstrUsageACRedoRepeat				,
//	pstrUsageACSort						,
//	pstrUsageACSortAscending			,
//	pstrUsageACSortDescending			,
//	pstrUsageACFilter					,
//	pstrUsageACSetClock					,
//	pstrUsageACViewClock				,
//	pstrUsageACSelectTimeZone			,
//	pstrUsageACEditTimeZone				,
//	pstrUsageACSetAlarm					,
//	pstrUsageACClearAlarm				,
//	pstrUsageACSnoozeAlarm				,
//	pstrUsageACResetAlarm				,
//	pstrUsageACSyncronize				,
//	pstrUsageACSendReceive				,
//	pstrUsageACSendTo					,
//	pstrUsageACReply					,
//	pstrUsageACReplyAll					,
//	pstrUsageACForwardMessage			,
//	pstrUsageACSend						,
//	pstrUsageACAttachFile				,
//	pstrUsageACUpload					,
//	pstrUsageACDownload					,
//	pstrUsageACSetBorders				,
//	pstrUsageACInsertRow				,
//	pstrUsageACInsertColumn				,
//	pstrUsageACInsertFile				,
//	pstrUsageACInsertPicture			,
//	pstrUsageACInsertObject				,
//	pstrUsageACInsertSymbol				,
//	pstrUsageACSaveAndClose				,
//	pstrUsageACRename					,
//	pstrUsageACMerge					,
//	pstrUsageACSplit					,
//	pstrUsageACDistributeHorizontaly	,
//	pstrUsageACDistributeVerticaly
//};
//const char *digitTitles0[] PROGMEM =
//{
//	pstrUsageDigitizer					,
//	pstrUsagePen						,
//	pstrUsageLightPen					,
//	pstrUsageTouchScreen				,
//	pstrUsageTouchPad					,
//	pstrUsageWhiteBoard					,
//	pstrUsageCoordinateMeasuringMachine	,
//	pstrUsage3DDigitizer				,
//	pstrUsageStereoPlotter				,
//	pstrUsageArticulatedArm				,
//	pstrUsageArmature					,
//	pstrUsageMultiplePointDigitizer		,
//	pstrUsageFreeSpaceWand
//};
//const char *digitTitles1[] PROGMEM =
//{
//	pstrUsageStylus						,
//	pstrUsagePuck						,
//	pstrUsageFinger
//
//};
//const char *digitTitles2[] PROGMEM =
//{
//	pstrUsageTipPressure			,
//	pstrUsageBarrelPressure			,
//	pstrUsageInRange				,
//	pstrUsageTouch					,
//	pstrUsageUntouch				,
//	pstrUsageTap					,
//	pstrUsageQuality				,
//	pstrUsageDataValid				,
//	pstrUsageTransducerIndex		,
//	pstrUsageTabletFunctionKeys		,
//	pstrUsageProgramChangeKeys		,
//	pstrUsageBatteryStrength		,
//	pstrUsageInvert					,
//	pstrUsageXTilt					,
//	pstrUsageYTilt					,
//	pstrUsageAzimuth				,
//	pstrUsageAltitude				,
//	pstrUsageTwist					,
//	pstrUsageTipSwitch				,
//	pstrUsageSecondaryTipSwitch		,
//	pstrUsageBarrelSwitch			,
//	pstrUsageEraser					,
//	pstrUsageTabletPick
//};
//const char *aplphanumTitles0[]	PROGMEM =
//{
//	pstrUsageAlphanumericDisplay,
//	pstrUsageBitmappedDisplay
//};
//const char *aplphanumTitles1[]	PROGMEM =
//{
//	pstrUsageDisplayAttributesReport	,
//	pstrUsageASCIICharacterSet			,
//	pstrUsageDataReadBack				,
//	pstrUsageFontReadBack				,
//	pstrUsageDisplayControlReport		,
//	pstrUsageClearDisplay				,
//	pstrUsageDisplayEnable				,
//	pstrUsageScreenSaverDelay			,
//	pstrUsageScreenSaverEnable			,
//	pstrUsageVerticalScroll				,
//	pstrUsageHorizontalScroll			,
//	pstrUsageCharacterReport			,
//	pstrUsageDisplayData				,
//	pstrUsageDisplayStatus				,
//	pstrUsageStatusNotReady				,
//	pstrUsageStatusReady				,
//	pstrUsageErrorNotALoadableCharacter	,
//	pstrUsageErrorFotDataCanNotBeRead	,
//	pstrUsageCursorPositionReport		,
//	pstrUsageRow						,
//	pstrUsageColumn						,
//	pstrUsageRows						,
//	pstrUsageColumns					,
//	pstrUsageCursorPixelPosition		,
//	pstrUsageCursorMode					,
//	pstrUsageCursorEnable				,
//	pstrUsageCursorBlink				,
//	pstrUsageFontReport					,
//	pstrUsageFontData					,
//	pstrUsageCharacterWidth				,
//	pstrUsageCharacterHeight			,
//	pstrUsageCharacterSpacingHorizontal	,
//	pstrUsageCharacterSpacingVertical	,
//	pstrUsageUnicodeCharset				,
//	pstrUsageFont7Segment				,
//	pstrUsage7SegmentDirectMap			,
//	pstrUsageFont14Segment				,
//	pstrUsage14SegmentDirectMap			,
//	pstrUsageDisplayBrightness			,
//	pstrUsageDisplayContrast			,
//	pstrUsageCharacterAttribute			,
//	pstrUsageAttributeReadback			,
//	pstrUsageAttributeData				,
//	pstrUsageCharAttributeEnhance		,
//	pstrUsageCharAttributeUnderline		,
//	pstrUsageCharAttributeBlink
//};
//const char *aplphanumTitles2[]	PROGMEM =
//{
//	pstrUsageBitmapSizeX				,
//	pstrUsageBitmapSizeY				,
//	pstrUsagePageReserved				,
//	pstrUsageBitDepthFormat				,
//	pstrUsageDisplayOrientation			,
//	pstrUsagePaletteReport				,
//	pstrUsagePaletteDataSize			,
//	pstrUsagePaletteDataOffset			,
//	pstrUsagePaletteData				,
//	pstrUsageBlitReport					,
//	pstrUsageBlitRectangleX1			,
//	pstrUsageBlitRectangleY1			,
//	pstrUsageBlitRectangleX2			,
//	pstrUsageBlitRectangleY2			,
//	pstrUsageBlitData					,
//	pstrUsageSoftButton					,
//	pstrUsageSoftButtonID				,
//	pstrUsageSoftButtonSide				,
//	pstrUsageSoftButtonOffset1			,
//	pstrUsageSoftButtonOffset2			,
//	pstrUsageSoftButtonReport
//};
//const char *medInstrTitles0[] PROGMEM =
//{
//	pstrUsageVCRAcquisition				,
//	pstrUsageFreezeThaw					,
//	pstrUsageClipStore					,
//	pstrUsageUpdate						,
//	pstrUsageNext						,
//	pstrUsageSave						,
//	pstrUsagePrint						,
//	pstrUsageMicrophoneEnable
//};
//const char *medInstrTitles1[] PROGMEM =
//{
//	pstrUsageCine						,
//	pstrUsageTransmitPower				,
//	pstrUsageVolume						,
//	pstrUsageFocus						,
//	pstrUsageDepth
//};
//const char *medInstrTitles2[] PROGMEM =
//{
//	pstrUsageSoftStepPrimary		,
//	pstrUsageSoftStepSecondary
//};
//const char *medInstrTitles3[] PROGMEM =
//{
//	pstrUsageZoomSelect					,
//	pstrUsageZoomAdjust					,
//	pstrUsageSpectralDopplerModeSelect	,
//	pstrUsageSpectralDopplerModeAdjust	,
//	pstrUsageColorDopplerModeSelect		,
//	pstrUsageColorDopplerModeAdjust		,
//	pstrUsageMotionModeSelect			,
//	pstrUsageMotionModeAdjust			,
//	pstrUsage2DModeSelect				,
//	pstrUsage2DModeAdjust
//};
//const char *medInstrTitles4[] PROGMEM =
//{
//	pstrUsageSoftControlSelect			,
//	pstrUsageSoftControlAdjust
//};

#endif // __HIDUSAGETITLEARRAYS_H__
