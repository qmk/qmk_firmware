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

#include "hidescriptorparser.h"

const char * const ReportDescParserBase::usagePageTitles0[] PROGMEM = {
        pstrUsagePageGenericDesktopControls,
        pstrUsagePageSimulationControls,
        pstrUsagePageVRControls,
        pstrUsagePageSportControls,
        pstrUsagePageGameControls,
        pstrUsagePageGenericDeviceControls,
        pstrUsagePageKeyboardKeypad,
        pstrUsagePageLEDs,
        pstrUsagePageButton,
        pstrUsagePageOrdinal,
        pstrUsagePageTelephone,
        pstrUsagePageConsumer,
        pstrUsagePageDigitizer,
        pstrUsagePagePID,
        pstrUsagePageUnicode
};

const char * const ReportDescParserBase::usagePageTitles1[] PROGMEM = {
        pstrUsagePageBarCodeScanner,
        pstrUsagePageScale,
        pstrUsagePageMSRDevices,
        pstrUsagePagePointOfSale,
        pstrUsagePageCameraControl,
        pstrUsagePageArcade
};
const char * const ReportDescParserBase::genDesktopTitles0[] PROGMEM = {
        pstrUsagePointer,
        pstrUsageMouse,
        pstrUsageJoystick,
        pstrUsageGamePad,
        pstrUsageKeyboard,
        pstrUsageKeypad,
        pstrUsageMultiAxisController,
        pstrUsageTabletPCSystemControls

};
const char * const ReportDescParserBase::genDesktopTitles1[] PROGMEM = {
        pstrUsageX,
        pstrUsageY,
        pstrUsageZ,
        pstrUsageRx,
        pstrUsageRy,
        pstrUsageRz,
        pstrUsageSlider,
        pstrUsageDial,
        pstrUsageWheel,
        pstrUsageHatSwitch,
        pstrUsageCountedBuffer,
        pstrUsageByteCount,
        pstrUsageMotionWakeup,
        pstrUsageStart,
        pstrUsageSelect,
        pstrUsagePageReserved,
        pstrUsageVx,
        pstrUsageVy,
        pstrUsageVz,
        pstrUsageVbrx,
        pstrUsageVbry,
        pstrUsageVbrz,
        pstrUsageVno,
        pstrUsageFeatureNotification,
        pstrUsageResolutionMultiplier
};
const char * const ReportDescParserBase::genDesktopTitles2[] PROGMEM = {
        pstrUsageSystemControl,
        pstrUsageSystemPowerDown,
        pstrUsageSystemSleep,
        pstrUsageSystemWakeup,
        pstrUsageSystemContextMenu,
        pstrUsageSystemMainMenu,
        pstrUsageSystemAppMenu,
        pstrUsageSystemMenuHelp,
        pstrUsageSystemMenuExit,
        pstrUsageSystemMenuSelect,
        pstrUsageSystemMenuRight,
        pstrUsageSystemMenuLeft,
        pstrUsageSystemMenuUp,
        pstrUsageSystemMenuDown,
        pstrUsageSystemColdRestart,
        pstrUsageSystemWarmRestart,
        pstrUsageDPadUp,
        pstrUsageDPadDown,
        pstrUsageDPadRight,
        pstrUsageDPadLeft
};
const char * const ReportDescParserBase::genDesktopTitles3[] PROGMEM = {
        pstrUsageSystemDock,
        pstrUsageSystemUndock,
        pstrUsageSystemSetup,
        pstrUsageSystemBreak,
        pstrUsageSystemDebuggerBreak,
        pstrUsageApplicationBreak,
        pstrUsageApplicationDebuggerBreak,
        pstrUsageSystemSpeakerMute,
        pstrUsageSystemHibernate
};
const char * const ReportDescParserBase::genDesktopTitles4[] PROGMEM = {
        pstrUsageSystemDisplayInvert,
        pstrUsageSystemDisplayInternal,
        pstrUsageSystemDisplayExternal,
        pstrUsageSystemDisplayBoth,
        pstrUsageSystemDisplayDual,
        pstrUsageSystemDisplayToggleIntExt,
        pstrUsageSystemDisplaySwapPriSec,
        pstrUsageSystemDisplayLCDAutoscale
};
const char * const ReportDescParserBase::simuTitles0[] PROGMEM = {
        pstrUsageFlightSimulationDevice,
        pstrUsageAutomobileSimulationDevice,
        pstrUsageTankSimulationDevice,
        pstrUsageSpaceshipSimulationDevice,
        pstrUsageSubmarineSimulationDevice,
        pstrUsageSailingSimulationDevice,
        pstrUsageMotocicleSimulationDevice,
        pstrUsageSportsSimulationDevice,
        pstrUsageAirplaneSimulationDevice,
        pstrUsageHelicopterSimulationDevice,
        pstrUsageMagicCarpetSimulationDevice,
        pstrUsageBicycleSimulationDevice
};
const char * const ReportDescParserBase::simuTitles1[] PROGMEM = {
        pstrUsageFlightControlStick,
        pstrUsageFlightStick,
        pstrUsageCyclicControl,
        pstrUsageCyclicTrim,
        pstrUsageFlightYoke,
        pstrUsageTrackControl
};
const char * const ReportDescParserBase::simuTitles2[] PROGMEM = {
        pstrUsageAileron,
        pstrUsageAileronTrim,
        pstrUsageAntiTorqueControl,
        pstrUsageAutopilotEnable,
        pstrUsageChaffRelease,
        pstrUsageCollectiveControl,
        pstrUsageDiveBrake,
        pstrUsageElectronicCountermeasures,
        pstrUsageElevator,
        pstrUsageElevatorTrim,
        pstrUsageRudder,
        pstrUsageThrottle,
        pstrUsageFlightCommunications,
        pstrUsageFlareRelease,
        pstrUsageLandingGear,
        pstrUsageToeBrake,
        pstrUsageTrigger,
        pstrUsageWeaponsArm,
        pstrUsageWeaponsSelect,
        pstrUsageWingFlaps,
        pstrUsageAccelerator,
        pstrUsageBrake,
        pstrUsageClutch,
        pstrUsageShifter,
        pstrUsageSteering,
        pstrUsageTurretDirection,
        pstrUsageBarrelElevation,
        pstrUsageDivePlane,
        pstrUsageBallast,
        pstrUsageBicycleCrank,
        pstrUsageHandleBars,
        pstrUsageFrontBrake,
        pstrUsageRearBrake
};
const char * const ReportDescParserBase::vrTitles0[] PROGMEM = {
        pstrUsageBelt,
        pstrUsageBodySuit,
        pstrUsageFlexor,
        pstrUsageGlove,
        pstrUsageHeadTracker,
        pstrUsageHeadMountedDisplay,
        pstrUsageHandTracker,
        pstrUsageOculometer,
        pstrUsageVest,
        pstrUsageAnimatronicDevice
};
const char * const ReportDescParserBase::vrTitles1[] PROGMEM = {
        pstrUsageStereoEnable,
        pstrUsageDisplayEnable
};
const char * const ReportDescParserBase::sportsCtrlTitles0[] PROGMEM = {
        pstrUsageBaseballBat,
        pstrUsageGolfClub,
        pstrUsageRowingMachine,
        pstrUsageTreadmill
};
const char * const ReportDescParserBase::sportsCtrlTitles1[] PROGMEM = {
        pstrUsageOar,
        pstrUsageSlope,
        pstrUsageRate,
        pstrUsageStickSpeed,
        pstrUsageStickFaceAngle,
        pstrUsageStickHeelToe,
        pstrUsageStickFollowThough,
        pstrUsageStickTempo,
        pstrUsageStickType,
        pstrUsageStickHeight
};
const char * const ReportDescParserBase::sportsCtrlTitles2[] PROGMEM = {
        pstrUsagePutter,
        pstrUsage1Iron,
        pstrUsage2Iron,
        pstrUsage3Iron,
        pstrUsage4Iron,
        pstrUsage5Iron,
        pstrUsage6Iron,
        pstrUsage7Iron,
        pstrUsage8Iron,
        pstrUsage9Iron,
        pstrUsage10Iron,
        pstrUsage11Iron,
        pstrUsageSandWedge,
        pstrUsageLoftWedge,
        pstrUsagePowerWedge,
        pstrUsage1Wood,
        pstrUsage3Wood,
        pstrUsage5Wood,
        pstrUsage7Wood,
        pstrUsage9Wood
};
const char * const ReportDescParserBase::gameTitles0[] PROGMEM = {
        pstrUsage3DGameController,
        pstrUsagePinballDevice,
        pstrUsageGunDevice
};
const char * const ReportDescParserBase::gameTitles1[] PROGMEM = {
        pstrUsagePointOfView,
        pstrUsageTurnRightLeft,
        pstrUsagePitchForwardBackward,
        pstrUsageRollRightLeft,
        pstrUsageMoveRightLeft,
        pstrUsageMoveForwardBackward,
        pstrUsageMoveUpDown,
        pstrUsageLeanRightLeft,
        pstrUsageLeanForwardBackward,
        pstrUsageHeightOfPOV,
        pstrUsageFlipper,
        pstrUsageSecondaryFlipper,
        pstrUsageBump,
        pstrUsageNewGame,
        pstrUsageShootBall,
        pstrUsagePlayer,
        pstrUsageGunBolt,
        pstrUsageGunClip,
        pstrUsageGunSelector,
        pstrUsageGunSingleShot,
        pstrUsageGunBurst,
        pstrUsageGunAutomatic,
        pstrUsageGunSafety,
        pstrUsageGamepadFireJump,
        pstrUsageGamepadTrigger
};
const char * const ReportDescParserBase::genDevCtrlTitles[] PROGMEM = {
        pstrUsageBatteryStrength,
        pstrUsageWirelessChannel,
        pstrUsageWirelessID,
        pstrUsageDiscoverWirelessControl,
        pstrUsageSecurityCodeCharEntered,
        pstrUsageSecurityCodeCharErased,
        pstrUsageSecurityCodeCleared
};
const char * const ReportDescParserBase::ledTitles[] PROGMEM = {
        pstrUsageNumLock,
        pstrUsageCapsLock,
        pstrUsageScrollLock,
        pstrUsageCompose,
        pstrUsageKana,
        pstrUsagePower,
        pstrUsageShift,
        pstrUsageDoNotDisturb,
        pstrUsageMute,
        pstrUsageToneEnable,
        pstrUsageHighCutFilter,
        pstrUsageLowCutFilter,
        pstrUsageEqualizerEnable,
        pstrUsageSoundFieldOn,
        pstrUsageSurroundOn,
        pstrUsageRepeat,
        pstrUsageStereo,
        pstrUsageSamplingRateDetect,
        pstrUsageSpinning,
        pstrUsageCAV,
        pstrUsageCLV,
        pstrUsageRecordingFormatDetect,
        pstrUsageOffHook,
        pstrUsageRing,
        pstrUsageMessageWaiting,
        pstrUsageDataMode,
        pstrUsageBatteryOperation,
        pstrUsageBatteryOK,
        pstrUsageBatteryLow,
        pstrUsageSpeaker,
        pstrUsageHeadSet,
        pstrUsageHold,
        pstrUsageMicrophone,
        pstrUsageCoverage,
        pstrUsageNightMode,
        pstrUsageSendCalls,
        pstrUsageCallPickup,
        pstrUsageConference,
        pstrUsageStandBy,
        pstrUsageCameraOn,
        pstrUsageCameraOff,
        pstrUsageOnLine,
        pstrUsageOffLine,
        pstrUsageBusy,
        pstrUsageReady,
        pstrUsagePaperOut,
        pstrUsagePaperJam,
        pstrUsageRemote,
        pstrUsageForward,
        pstrUsageReverse,
        pstrUsageStop,
        pstrUsageRewind,
        pstrUsageFastForward,
        pstrUsagePlay,
        pstrUsagePause,
        pstrUsageRecord,
        pstrUsageError,
        pstrUsageSelectedIndicator,
        pstrUsageInUseIndicator,
        pstrUsageMultiModeIndicator,
        pstrUsageIndicatorOn,
        pstrUsageIndicatorFlash,
        pstrUsageIndicatorSlowBlink,
        pstrUsageIndicatorFastBlink,
        pstrUsageIndicatorOff,
        pstrUsageFlashOnTime,
        pstrUsageSlowBlinkOnTime,
        pstrUsageSlowBlinkOffTime,
        pstrUsageFastBlinkOnTime,
        pstrUsageFastBlinkOffTime,
        pstrUsageIndicatorColor,
        pstrUsageIndicatorRed,
        pstrUsageIndicatorGreen,
        pstrUsageIndicatorAmber,
        pstrUsageGenericIndicator,
        pstrUsageSystemSuspend,
        pstrUsageExternalPowerConnected
};
const char * const ReportDescParserBase::telTitles0 [] PROGMEM = {
        pstrUsagePhone,
        pstrUsageAnsweringMachine,
        pstrUsageMessageControls,
        pstrUsageHandset,
        pstrUsageHeadset,
        pstrUsageTelephonyKeyPad,
        pstrUsageProgrammableButton
};
const char * const ReportDescParserBase::telTitles1 [] PROGMEM = {
        pstrUsageHookSwitch,
        pstrUsageFlash,
        pstrUsageFeature,
        pstrUsageHold,
        pstrUsageRedial,
        pstrUsageTransfer,
        pstrUsageDrop,
        pstrUsagePark,
        pstrUsageForwardCalls,
        pstrUsageAlternateFunction,
        pstrUsageLine,
        pstrUsageSpeakerPhone,
        pstrUsageConference,
        pstrUsageRingEnable,
        pstrUsageRingSelect,
        pstrUsagePhoneMute,
        pstrUsageCallerID,
        pstrUsageSend
};
const char * const ReportDescParserBase::telTitles2 [] PROGMEM = {
        pstrUsageSpeedDial,
        pstrUsageStoreNumber,
        pstrUsageRecallNumber,
        pstrUsagePhoneDirectory
};
const char * const ReportDescParserBase::telTitles3 [] PROGMEM = {
        pstrUsageVoiceMail,
        pstrUsageScreenCalls,
        pstrUsageDoNotDisturb,
        pstrUsageMessage,
        pstrUsageAnswerOnOff
};
const char * const ReportDescParserBase::telTitles4 [] PROGMEM = {
        pstrUsageInsideDialTone,
        pstrUsageOutsideDialTone,
        pstrUsageInsideRingTone,
        pstrUsageOutsideRingTone,
        pstrUsagePriorityRingTone,
        pstrUsageInsideRingback,
        pstrUsagePriorityRingback,
        pstrUsageLineBusyTone,
        pstrUsageReorderTone,
        pstrUsageCallWaitingTone,
        pstrUsageConfirmationTone1,
        pstrUsageConfirmationTone2,
        pstrUsageTonesOff,
        pstrUsageOutsideRingback,
        pstrUsageRinger
};
const char * const ReportDescParserBase::telTitles5 [] PROGMEM = {
        pstrUsagePhoneKey0,
        pstrUsagePhoneKey1,
        pstrUsagePhoneKey2,
        pstrUsagePhoneKey3,
        pstrUsagePhoneKey4,
        pstrUsagePhoneKey5,
        pstrUsagePhoneKey6,
        pstrUsagePhoneKey7,
        pstrUsagePhoneKey8,
        pstrUsagePhoneKey9,
        pstrUsagePhoneKeyStar,
        pstrUsagePhoneKeyPound,
        pstrUsagePhoneKeyA,
        pstrUsagePhoneKeyB,
        pstrUsagePhoneKeyC,
        pstrUsagePhoneKeyD
};
const char * const ReportDescParserBase::consTitles0[] PROGMEM = {
        pstrUsageConsumerControl,
        pstrUsageNumericKeyPad,
        pstrUsageProgrammableButton,
        pstrUsageMicrophone,
        pstrUsageHeadphone,
        pstrUsageGraphicEqualizer
};
const char * const ReportDescParserBase::consTitles1[] PROGMEM = {
        pstrUsagePlus10,
        pstrUsagePlus100,
        pstrUsageAMPM
};
const char * const ReportDescParserBase::consTitles2[] PROGMEM = {
        pstrUsagePower,
        pstrUsageReset,
        pstrUsageSleep,
        pstrUsageSleepAfter,
        pstrUsageSleepMode,
        pstrUsageIllumination,
        pstrUsageFunctionButtons

};
const char * const ReportDescParserBase::consTitles3[] PROGMEM = {
        pstrUsageMenu,
        pstrUsageMenuPick,
        pstrUsageMenuUp,
        pstrUsageMenuDown,
        pstrUsageMenuLeft,
        pstrUsageMenuRight,
        pstrUsageMenuEscape,
        pstrUsageMenuValueIncrease,
        pstrUsageMenuValueDecrease
};
const char * const ReportDescParserBase::consTitles4[] PROGMEM = {
        pstrUsageDataOnScreen,
        pstrUsageClosedCaption,
        pstrUsageClosedCaptionSelect,
        pstrUsageVCRTV,
        pstrUsageBroadcastMode,
        pstrUsageSnapshot,
        pstrUsageStill
};
const char * const ReportDescParserBase::consTitles5[] PROGMEM = {
        pstrUsageSelection,
        pstrUsageAssignSelection,
        pstrUsageModeStep,
        pstrUsageRecallLast,
        pstrUsageEnterChannel,
        pstrUsageOrderMovie,
        pstrUsageChannel,
        pstrUsageMediaSelection,
        pstrUsageMediaSelectComputer,
        pstrUsageMediaSelectTV,
        pstrUsageMediaSelectWWW,
        pstrUsageMediaSelectDVD,
        pstrUsageMediaSelectTelephone,
        pstrUsageMediaSelectProgramGuide,
        pstrUsageMediaSelectVideoPhone,
        pstrUsageMediaSelectGames,
        pstrUsageMediaSelectMessages,
        pstrUsageMediaSelectCD,
        pstrUsageMediaSelectVCR,
        pstrUsageMediaSelectTuner,
        pstrUsageQuit,
        pstrUsageHelp,
        pstrUsageMediaSelectTape,
        pstrUsageMediaSelectCable,
        pstrUsageMediaSelectSatellite,
        pstrUsageMediaSelectSecurity,
        pstrUsageMediaSelectHome,
        pstrUsageMediaSelectCall,
        pstrUsageChannelIncrement,
        pstrUsageChannelDecrement,
        pstrUsageMediaSelectSAP,
        pstrUsagePageReserved,
        pstrUsageVCRPlus,
        pstrUsageOnce,
        pstrUsageDaily,
        pstrUsageWeekly,
        pstrUsageMonthly
};
const char * const ReportDescParserBase::consTitles6[] PROGMEM = {
        pstrUsagePlay,
        pstrUsagePause,
        pstrUsageRecord,
        pstrUsageFastForward,
        pstrUsageRewind,
        pstrUsageScanNextTrack,
        pstrUsageScanPreviousTrack,
        pstrUsageStop,
        pstrUsageEject,
        pstrUsageRandomPlay,
        pstrUsageSelectDisk,
        pstrUsageEnterDisk,
        pstrUsageRepeat,
        pstrUsageTracking,
        pstrUsageTrackNormal,
        pstrUsageSlowTracking,
        pstrUsageFrameForward,
        pstrUsageFrameBackwards,
        pstrUsageMark,
        pstrUsageClearMark,
        pstrUsageRepeatFromMark,
        pstrUsageReturnToMark,
        pstrUsageSearchMarkForward,
        pstrUsageSearchMarkBackwards,
        pstrUsageCounterReset,
        pstrUsageShowCounter,
        pstrUsageTrackingIncrement,
        pstrUsageTrackingDecrement,
        pstrUsageStopEject,
        pstrUsagePlayPause,
        pstrUsagePlaySkip
};
const char * const ReportDescParserBase::consTitles7[] PROGMEM = {
        pstrUsageVolume,
        pstrUsageBalance,
        pstrUsageMute,
        pstrUsageBass,
        pstrUsageTreble,
        pstrUsageBassBoost,
        pstrUsageSurroundMode,
        pstrUsageLoudness,
        pstrUsageMPX,
        pstrUsageVolumeIncrement,
        pstrUsageVolumeDecrement
};
const char * const ReportDescParserBase::consTitles8[] PROGMEM = {
        pstrUsageSpeedSelect,
        pstrUsagePlaybackSpeed,
        pstrUsageStandardPlay,
        pstrUsageLongPlay,
        pstrUsageExtendedPlay,
        pstrUsageSlow
};
const char * const ReportDescParserBase::consTitles9[] PROGMEM = {
        pstrUsageFanEnable,
        pstrUsageFanSpeed,
        pstrUsageLightEnable,
        pstrUsageLightIlluminationLevel,
        pstrUsageClimateControlEnable,
        pstrUsageRoomTemperature,
        pstrUsageSecurityEnable,
        pstrUsageFireAlarm,
        pstrUsagePoliceAlarm,
        pstrUsageProximity,
        pstrUsageMotion,
        pstrUsageDuresAlarm,
        pstrUsageHoldupAlarm,
        pstrUsageMedicalAlarm
};
const char * const ReportDescParserBase::consTitlesA[] PROGMEM = {
        pstrUsageBalanceRight,
        pstrUsageBalanceLeft,
        pstrUsageBassIncrement,
        pstrUsageBassDecrement,
        pstrUsageTrebleIncrement,
        pstrUsageTrebleDecrement
};
const char * const ReportDescParserBase::consTitlesB[] PROGMEM = {
        pstrUsageSpeakerSystem,
        pstrUsageChannelLeft,
        pstrUsageChannelRight,
        pstrUsageChannelCenter,
        pstrUsageChannelFront,
        pstrUsageChannelCenterFront,
        pstrUsageChannelSide,
        pstrUsageChannelSurround,
        pstrUsageChannelLowFreqEnhancement,
        pstrUsageChannelTop,
        pstrUsageChannelUnknown
};
const char * const ReportDescParserBase::consTitlesC[] PROGMEM = {
        pstrUsageSubChannel,
        pstrUsageSubChannelIncrement,
        pstrUsageSubChannelDecrement,
        pstrUsageAlternateAudioIncrement,
        pstrUsageAlternateAudioDecrement
};
const char * const ReportDescParserBase::consTitlesD[] PROGMEM = {
        pstrUsageApplicationLaunchButtons,
        pstrUsageALLaunchButtonConfigTool,
        pstrUsageALProgrammableButton,
        pstrUsageALConsumerControlConfig,
        pstrUsageALWordProcessor,
        pstrUsageALTextEditor,
        pstrUsageALSpreadsheet,
        pstrUsageALGraphicsEditor,
        pstrUsageALPresentationApp,
        pstrUsageALDatabaseApp,
        pstrUsageALEmailReader,
        pstrUsageALNewsreader,
        pstrUsageALVoicemail,
        pstrUsageALContactsAddressBook,
        pstrUsageALCalendarSchedule,
        pstrUsageALTaskProjectManager,
        pstrUsageALLogJournalTimecard,
        pstrUsageALCheckbookFinance,
        pstrUsageALCalculator,
        pstrUsageALAVCapturePlayback,
        pstrUsageALLocalMachineBrowser,
        pstrUsageALLANWANBrow,
        pstrUsageALInternetBrowser,
        pstrUsageALRemoteNetISPConnect,
        pstrUsageALNetworkConference,
        pstrUsageALNetworkChat,
        pstrUsageALTelephonyDialer,
        pstrUsageALLogon,
        pstrUsageALLogoff,
        pstrUsageALLogonLogoff,
        pstrUsageALTermLockScrSav,
        pstrUsageALControlPannel,
        pstrUsageALCommandLineProcessorRun,
        pstrUsageALProcessTaskManager,
        pstrUsageALSelectTaskApplication,
        pstrUsageALNextTaskApplication,
        pstrUsageALPreviousTaskApplication,
        pstrUsageALPreemptiveHaltTaskApp,
        pstrUsageALIntegratedHelpCenter,
        pstrUsageALDocuments,
        pstrUsageALThesaurus,
        pstrUsageALDictionary,
        pstrUsageALDesktop,
        pstrUsageALSpellCheck,
        pstrUsageALGrammarCheck,
        pstrUsageALWirelessStatus,
        pstrUsageALKeyboardLayout,
        pstrUsageALVirusProtection,
        pstrUsageALEncryption,
        pstrUsageALScreenSaver,
        pstrUsageALAlarms,
        pstrUsageALClock,
        pstrUsageALFileBrowser,
        pstrUsageALPowerStatus,
        pstrUsageALImageBrowser,
        pstrUsageALAudioBrowser,
        pstrUsageALMovieBrowser,
        pstrUsageALDigitalRightsManager,
        pstrUsageALDigitalWallet,
        pstrUsagePageReserved,
        pstrUsageALInstantMessaging,
        pstrUsageALOEMFeaturesBrowser,
        pstrUsageALOEMHelp,
        pstrUsageALOnlineCommunity,
        pstrUsageALEntertainmentContentBrow,
        pstrUsageALOnlineShoppingBrowser,
        pstrUsageALSmartCardInfoHelp,
        pstrUsageALMarketMonitorFinBrowser,
        pstrUsageALCustomCorpNewsBrowser,
        pstrUsageALOnlineActivityBrowser,
        pstrUsageALResearchSearchBrowser,
        pstrUsageALAudioPlayer
};
const char * const ReportDescParserBase::consTitlesE[] PROGMEM = {
        pstrUsageGenericGUIAppControls,
        pstrUsageACNew,
        pstrUsageACOpen,
        pstrUsageACClose,
        pstrUsageACExit,
        pstrUsageACMaximize,
        pstrUsageACMinimize,
        pstrUsageACSave,
        pstrUsageACPrint,
        pstrUsageACProperties,
        pstrUsageACUndo,
        pstrUsageACCopy,
        pstrUsageACCut,
        pstrUsageACPaste,
        pstrUsageACSelectAll,
        pstrUsageACFind,
        pstrUsageACFindAndReplace,
        pstrUsageACSearch,
        pstrUsageACGoto,
        pstrUsageACHome,
        pstrUsageACBack,
        pstrUsageACForward,
        pstrUsageACStop,
        pstrUsageACRefresh,
        pstrUsageACPreviousLink,
        pstrUsageACNextLink,
        pstrUsageACBookmarks,
        pstrUsageACHistory,
        pstrUsageACSubscriptions,
        pstrUsageACZoomIn,
        pstrUsageACZoomOut,
        pstrUsageACZoom,
        pstrUsageACFullScreenView,
        pstrUsageACNormalView,
        pstrUsageACViewToggle,
        pstrUsageACScrollUp,
        pstrUsageACScrollDown,
        pstrUsageACScroll,
        pstrUsageACPanLeft,
        pstrUsageACPanRight,
        pstrUsageACPan,
        pstrUsageACNewWindow,
        pstrUsageACTileHoriz,
        pstrUsageACTileVert,
        pstrUsageACFormat,
        pstrUsageACEdit,
        pstrUsageACBold,
        pstrUsageACItalics,
        pstrUsageACUnderline,
        pstrUsageACStrikethrough,
        pstrUsageACSubscript,
        pstrUsageACSuperscript,
        pstrUsageACAllCaps,
        pstrUsageACRotate,
        pstrUsageACResize,
        pstrUsageACFlipHorizontal,
        pstrUsageACFlipVertical,
        pstrUsageACMirrorHorizontal,
        pstrUsageACMirrorVertical,
        pstrUsageACFontSelect,
        pstrUsageACFontColor,
        pstrUsageACFontSize,
        pstrUsageACJustifyLeft,
        pstrUsageACJustifyCenterH,
        pstrUsageACJustifyRight,
        pstrUsageACJustifyBlockH,
        pstrUsageACJustifyTop,
        pstrUsageACJustifyCenterV,
        pstrUsageACJustifyBottom,
        pstrUsageACJustifyBlockV,
        pstrUsageACIndentDecrease,
        pstrUsageACIndentIncrease,
        pstrUsageACNumberedList,
        pstrUsageACRestartNumbering,
        pstrUsageACBulletedList,
        pstrUsageACPromote,
        pstrUsageACDemote,
        pstrUsageACYes,
        pstrUsageACNo,
        pstrUsageACCancel,
        pstrUsageACCatalog,
        pstrUsageACBuyChkout,
        pstrUsageACAddToCart,
        pstrUsageACExpand,
        pstrUsageACExpandAll,
        pstrUsageACCollapse,
        pstrUsageACCollapseAll,
        pstrUsageACPrintPreview,
        pstrUsageACPasteSpecial,
        pstrUsageACInsertMode,
        pstrUsageACDelete,
        pstrUsageACLock,
        pstrUsageACUnlock,
        pstrUsageACProtect,
        pstrUsageACUnprotect,
        pstrUsageACAttachComment,
        pstrUsageACDeleteComment,
        pstrUsageACViewComment,
        pstrUsageACSelectWord,
        pstrUsageACSelectSentence,
        pstrUsageACSelectParagraph,
        pstrUsageACSelectColumn,
        pstrUsageACSelectRow,
        pstrUsageACSelectTable,
        pstrUsageACSelectObject,
        pstrUsageACRedoRepeat,
        pstrUsageACSort,
        pstrUsageACSortAscending,
        pstrUsageACSortDescending,
        pstrUsageACFilter,
        pstrUsageACSetClock,
        pstrUsageACViewClock,
        pstrUsageACSelectTimeZone,
        pstrUsageACEditTimeZone,
        pstrUsageACSetAlarm,
        pstrUsageACClearAlarm,
        pstrUsageACSnoozeAlarm,
        pstrUsageACResetAlarm,
        pstrUsageACSyncronize,
        pstrUsageACSendReceive,
        pstrUsageACSendTo,
        pstrUsageACReply,
        pstrUsageACReplyAll,
        pstrUsageACForwardMessage,
        pstrUsageACSend,
        pstrUsageACAttachFile,
        pstrUsageACUpload,
        pstrUsageACDownload,
        pstrUsageACSetBorders,
        pstrUsageACInsertRow,
        pstrUsageACInsertColumn,
        pstrUsageACInsertFile,
        pstrUsageACInsertPicture,
        pstrUsageACInsertObject,
        pstrUsageACInsertSymbol,
        pstrUsageACSaveAndClose,
        pstrUsageACRename,
        pstrUsageACMerge,
        pstrUsageACSplit,
        pstrUsageACDistributeHorizontaly,
        pstrUsageACDistributeVerticaly
};
const char * const ReportDescParserBase::digitTitles0[] PROGMEM = {
        pstrUsageDigitizer,
        pstrUsagePen,
        pstrUsageLightPen,
        pstrUsageTouchScreen,
        pstrUsageTouchPad,
        pstrUsageWhiteBoard,
        pstrUsageCoordinateMeasuringMachine,
        pstrUsage3DDigitizer,
        pstrUsageStereoPlotter,
        pstrUsageArticulatedArm,
        pstrUsageArmature,
        pstrUsageMultiplePointDigitizer,
        pstrUsageFreeSpaceWand
};
const char * const ReportDescParserBase::digitTitles1[] PROGMEM = {
        pstrUsageStylus,
        pstrUsagePuck,
        pstrUsageFinger

};
const char * const ReportDescParserBase::digitTitles2[] PROGMEM = {
        pstrUsageTipPressure,
        pstrUsageBarrelPressure,
        pstrUsageInRange,
        pstrUsageTouch,
        pstrUsageUntouch,
        pstrUsageTap,
        pstrUsageQuality,
        pstrUsageDataValid,
        pstrUsageTransducerIndex,
        pstrUsageTabletFunctionKeys,
        pstrUsageProgramChangeKeys,
        pstrUsageBatteryStrength,
        pstrUsageInvert,
        pstrUsageXTilt,
        pstrUsageYTilt,
        pstrUsageAzimuth,
        pstrUsageAltitude,
        pstrUsageTwist,
        pstrUsageTipSwitch,
        pstrUsageSecondaryTipSwitch,
        pstrUsageBarrelSwitch,
        pstrUsageEraser,
        pstrUsageTabletPick
};
const char * const ReportDescParserBase::aplphanumTitles0[] PROGMEM = {
        pstrUsageAlphanumericDisplay,
        pstrUsageBitmappedDisplay
};
const char * const ReportDescParserBase::aplphanumTitles1[] PROGMEM = {
        pstrUsageDisplayAttributesReport,
        pstrUsageASCIICharacterSet,
        pstrUsageDataReadBack,
        pstrUsageFontReadBack,
        pstrUsageDisplayControlReport,
        pstrUsageClearDisplay,
        pstrUsageDisplayEnable,
        pstrUsageScreenSaverDelay,
        pstrUsageScreenSaverEnable,
        pstrUsageVerticalScroll,
        pstrUsageHorizontalScroll,
        pstrUsageCharacterReport,
        pstrUsageDisplayData,
        pstrUsageDisplayStatus,
        pstrUsageStatusNotReady,
        pstrUsageStatusReady,
        pstrUsageErrorNotALoadableCharacter,
        pstrUsageErrorFotDataCanNotBeRead,
        pstrUsageCursorPositionReport,
        pstrUsageRow,
        pstrUsageColumn,
        pstrUsageRows,
        pstrUsageColumns,
        pstrUsageCursorPixelPosition,
        pstrUsageCursorMode,
        pstrUsageCursorEnable,
        pstrUsageCursorBlink,
        pstrUsageFontReport,
        pstrUsageFontData,
        pstrUsageCharacterWidth,
        pstrUsageCharacterHeight,
        pstrUsageCharacterSpacingHorizontal,
        pstrUsageCharacterSpacingVertical,
        pstrUsageUnicodeCharset,
        pstrUsageFont7Segment,
        pstrUsage7SegmentDirectMap,
        pstrUsageFont14Segment,
        pstrUsage14SegmentDirectMap,
        pstrUsageDisplayBrightness,
        pstrUsageDisplayContrast,
        pstrUsageCharacterAttribute,
        pstrUsageAttributeReadback,
        pstrUsageAttributeData,
        pstrUsageCharAttributeEnhance,
        pstrUsageCharAttributeUnderline,
        pstrUsageCharAttributeBlink
};
const char * const ReportDescParserBase::aplphanumTitles2[] PROGMEM = {
        pstrUsageBitmapSizeX,
        pstrUsageBitmapSizeY,
        pstrUsagePageReserved,
        pstrUsageBitDepthFormat,
        pstrUsageDisplayOrientation,
        pstrUsagePaletteReport,
        pstrUsagePaletteDataSize,
        pstrUsagePaletteDataOffset,
        pstrUsagePaletteData,
        pstrUsageBlitReport,
        pstrUsageBlitRectangleX1,
        pstrUsageBlitRectangleY1,
        pstrUsageBlitRectangleX2,
        pstrUsageBlitRectangleY2,
        pstrUsageBlitData,
        pstrUsageSoftButton,
        pstrUsageSoftButtonID,
        pstrUsageSoftButtonSide,
        pstrUsageSoftButtonOffset1,
        pstrUsageSoftButtonOffset2,
        pstrUsageSoftButtonReport
};
const char * const ReportDescParserBase::medInstrTitles0[] PROGMEM = {
        pstrUsageVCRAcquisition,
        pstrUsageFreezeThaw,
        pstrUsageClipStore,
        pstrUsageUpdate,
        pstrUsageNext,
        pstrUsageSave,
        pstrUsagePrint,
        pstrUsageMicrophoneEnable
};
const char * const ReportDescParserBase::medInstrTitles1[] PROGMEM = {
        pstrUsageCine,
        pstrUsageTransmitPower,
        pstrUsageVolume,
        pstrUsageFocus,
        pstrUsageDepth
};
const char * const ReportDescParserBase::medInstrTitles2[] PROGMEM = {
        pstrUsageSoftStepPrimary,
        pstrUsageSoftStepSecondary
};
const char * const ReportDescParserBase::medInstrTitles3[] PROGMEM = {
        pstrUsageZoomSelect,
        pstrUsageZoomAdjust,
        pstrUsageSpectralDopplerModeSelect,
        pstrUsageSpectralDopplerModeAdjust,
        pstrUsageColorDopplerModeSelect,
        pstrUsageColorDopplerModeAdjust,
        pstrUsageMotionModeSelect,
        pstrUsageMotionModeAdjust,
        pstrUsage2DModeSelect,
        pstrUsage2DModeAdjust
};
const char * const ReportDescParserBase::medInstrTitles4[] PROGMEM = {
        pstrUsageSoftControlSelect,
        pstrUsageSoftControlAdjust
};

void ReportDescParserBase::Parse(const uint16_t len, const uint8_t *pbuf, const uint16_t &offset) {
        uint16_t cntdn = (uint16_t)len;
        uint8_t *p = (uint8_t*)pbuf;


        totalSize = 0;

        while(cntdn) {
                //USB_HOST_SERIAL.println("");
                //PrintHex<uint16_t>(offset + len - cntdn);
                //USB_HOST_SERIAL.print(":");

                ParseItem(&p, &cntdn);

                //if (ParseItem(&p, &cntdn))
                //        return;
        }
        //USBTRACE2("Total:", totalSize);
}

void ReportDescParserBase::PrintValue(uint8_t *p, uint8_t len) {
        E_Notify(PSTR("("), 0x80);
        for(; len; p++, len--)
                PrintHex<uint8_t > (*p, 0x80);
        E_Notify(PSTR(")"), 0x80);
}

void ReportDescParserBase::PrintByteValue(uint8_t data) {
        E_Notify(PSTR("("), 0x80);
        PrintHex<uint8_t > (data, 0x80);
        E_Notify(PSTR(")"), 0x80);
}

void ReportDescParserBase::PrintItemTitle(uint8_t prefix) {
        switch(prefix & (TYPE_MASK | TAG_MASK)) {
                case (TYPE_GLOBAL | TAG_GLOBAL_PUSH):
                        E_Notify(PSTR("\r\nPush"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_POP):
                        E_Notify(PSTR("\r\nPop"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_USAGEPAGE):
                        E_Notify(PSTR("\r\nUsage Page"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_LOGICALMIN):
                        E_Notify(PSTR("\r\nLogical Min"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_LOGICALMAX):
                        E_Notify(PSTR("\r\nLogical Max"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_PHYSMIN):
                        E_Notify(PSTR("\r\nPhysical Min"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_PHYSMAX):
                        E_Notify(PSTR("\r\nPhysical Max"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_UNITEXP):
                        E_Notify(PSTR("\r\nUnit Exp"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_UNIT):
                        E_Notify(PSTR("\r\nUnit"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTSIZE):
                        E_Notify(PSTR("\r\nReport Size"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTCOUNT):
                        E_Notify(PSTR("\r\nReport Count"), 0x80);
                        break;
                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTID):
                        E_Notify(PSTR("\r\nReport Id"), 0x80);
                        break;
                case (TYPE_LOCAL | TAG_LOCAL_USAGE):
                        E_Notify(PSTR("\r\nUsage"), 0x80);
                        break;
                case (TYPE_LOCAL | TAG_LOCAL_USAGEMIN):
                        E_Notify(PSTR("\r\nUsage Min"), 0x80);
                        break;
                case (TYPE_LOCAL | TAG_LOCAL_USAGEMAX):
                        E_Notify(PSTR("\r\nUsage Max"), 0x80);
                        break;
                case (TYPE_MAIN | TAG_MAIN_COLLECTION):
                        E_Notify(PSTR("\r\nCollection"), 0x80);
                        break;
                case (TYPE_MAIN | TAG_MAIN_ENDCOLLECTION):
                        E_Notify(PSTR("\r\nEnd Collection"), 0x80);
                        break;
                case (TYPE_MAIN | TAG_MAIN_INPUT):
                        E_Notify(PSTR("\r\nInput"), 0x80);
                        break;
                case (TYPE_MAIN | TAG_MAIN_OUTPUT):
                        E_Notify(PSTR("\r\nOutput"), 0x80);
                        break;
                case (TYPE_MAIN | TAG_MAIN_FEATURE):
                        E_Notify(PSTR("\r\nFeature"), 0x80);
                        break;
        } // switch (**pp & (TYPE_MASK | TAG_MASK))
}

uint8_t ReportDescParserBase::ParseItem(uint8_t **pp, uint16_t *pcntdn) {
        //uint8_t ret = enErrorSuccess;
        //reinterpret_cast<>(varBuffer);
        switch(itemParseState) {
                case 0:
                        if(**pp == HID_LONG_ITEM_PREFIX)
                                USBTRACE("\r\nLONG\r\n");
                        else {
                                uint8_t size = ((**pp) & DATA_SIZE_MASK);

                                itemPrefix = (**pp);
                                itemSize = 1 + ((size == DATA_SIZE_4) ? 4 : size);

                                PrintItemTitle(itemPrefix);
                        }
                        (*pp)++;
                        (*pcntdn)--;
                        itemSize--;
                        itemParseState = 1;

                        if(!itemSize)
                                break;

                        if(!pcntdn)
                                return enErrorIncomplete;
                case 1:
                        //USBTRACE2("\r\niSz:",itemSize);

                        theBuffer.valueSize = itemSize;
                        valParser.Initialize(&theBuffer);
                        itemParseState = 2;
                case 2:
                        if(!valParser.Parse(pp, pcntdn))
                                return enErrorIncomplete;
                        itemParseState = 3;
                case 3:
                {
                        uint8_t data = *((uint8_t*)varBuffer);

                        switch(itemPrefix & (TYPE_MASK | TAG_MASK)) {
                                case (TYPE_LOCAL | TAG_LOCAL_USAGE):
                                        if(pfUsage) {
                                                if(theBuffer.valueSize > 1) {
                                                        uint16_t* ui16 = reinterpret_cast<uint16_t *>(varBuffer);
                                                        pfUsage(*ui16);
                                                } else
                                                        pfUsage(data);
                                        }
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTSIZE):
                                        rptSize = data;
                                        PrintByteValue(data);
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTCOUNT):
                                        rptCount = data;
                                        PrintByteValue(data);
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_LOGICALMIN):
                                case (TYPE_GLOBAL | TAG_GLOBAL_LOGICALMAX):
                                case (TYPE_GLOBAL | TAG_GLOBAL_PHYSMIN):
                                case (TYPE_GLOBAL | TAG_GLOBAL_PHYSMAX):
                                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTID):
                                case (TYPE_LOCAL | TAG_LOCAL_USAGEMIN):
                                case (TYPE_LOCAL | TAG_LOCAL_USAGEMAX):
                                case (TYPE_GLOBAL | TAG_GLOBAL_UNITEXP):
                                case (TYPE_GLOBAL | TAG_GLOBAL_UNIT):
                                        PrintValue(varBuffer, theBuffer.valueSize);
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_PUSH):
                                case (TYPE_GLOBAL | TAG_GLOBAL_POP):
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_USAGEPAGE):
                                        SetUsagePage(data);
                                        PrintUsagePage(data);
                                        PrintByteValue(data);
                                        break;
                                case (TYPE_MAIN | TAG_MAIN_COLLECTION):
                                case (TYPE_MAIN | TAG_MAIN_ENDCOLLECTION):
                                        switch(data) {
                                                case 0x00:
                                                        E_Notify(PSTR(" Physical"), 0x80);
                                                        break;
                                                case 0x01:
                                                        E_Notify(PSTR(" Application"), 0x80);
                                                        break;
                                                case 0x02:
                                                        E_Notify(PSTR(" Logical"), 0x80);
                                                        break;
                                                case 0x03:
                                                        E_Notify(PSTR(" Report"), 0x80);
                                                        break;
                                                case 0x04:
                                                        E_Notify(PSTR(" Named Array"), 0x80);
                                                        break;
                                                case 0x05:
                                                        E_Notify(PSTR(" Usage Switch"), 0x80);
                                                        break;
                                                case 0x06:
                                                        E_Notify(PSTR(" Usage Modifier"), 0x80);
                                                        break;
                                                default:
                                                        E_Notify(PSTR(" Vendor Defined("), 0x80);
                                                        PrintHex<uint8_t > (data, 0x80);
                                                        E_Notify(PSTR(")"), 0x80);
                                        }
                                        break;
                                case (TYPE_MAIN | TAG_MAIN_INPUT):
                                case (TYPE_MAIN | TAG_MAIN_OUTPUT):
                                case (TYPE_MAIN | TAG_MAIN_FEATURE):
                                        totalSize += (uint16_t)rptSize * (uint16_t)rptCount;
                                        rptSize = 0;
                                        rptCount = 0;
                                        E_Notify(PSTR("("), 0x80);
                                        PrintBin<uint8_t > (data, 0x80);
                                        E_Notify(PSTR(")"), 0x80);
                                        break;
                        } // switch (**pp & (TYPE_MASK | TAG_MASK))
                }
        } // switch (itemParseState)
        itemParseState = 0;
        return enErrorSuccess;
}

ReportDescParserBase::UsagePageFunc ReportDescParserBase::usagePageFunctions[] /*PROGMEM*/ = {
        &ReportDescParserBase::PrintGenericDesktopPageUsage,
        &ReportDescParserBase::PrintSimulationControlsPageUsage,
        &ReportDescParserBase::PrintVRControlsPageUsage,
        &ReportDescParserBase::PrintSportsControlsPageUsage,
        &ReportDescParserBase::PrintGameControlsPageUsage,
        &ReportDescParserBase::PrintGenericDeviceControlsPageUsage,
        NULL, // Keyboard/Keypad
        &ReportDescParserBase::PrintLEDPageUsage,
        &ReportDescParserBase::PrintButtonPageUsage,
        &ReportDescParserBase::PrintOrdinalPageUsage,
        &ReportDescParserBase::PrintTelephonyPageUsage,
        &ReportDescParserBase::PrintConsumerPageUsage,
        &ReportDescParserBase::PrintDigitizerPageUsage,
        NULL, // Reserved
        NULL, // PID
        NULL // Unicode
};

void ReportDescParserBase::SetUsagePage(uint16_t page) {
        pfUsage = NULL;

        if(VALUE_BETWEEN(page, 0x00, 0x11)) {
                pfUsage = (usagePageFunctions[page - 1]);

        } else {
                switch(page) {
                        case 0x14:
                                pfUsage = &ReportDescParserBase::PrintAlphanumDisplayPageUsage;
                                break;
                        case 0x40:
                                pfUsage = &ReportDescParserBase::PrintMedicalInstrumentPageUsage;
                                break;
                }
        }
}

void ReportDescParserBase::PrintUsagePage(uint16_t page) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(page, 0x00, 0x11, w, E_Notify, usagePageTitles0, 0x80)
        else output_if_between(page, 0x8b, 0x92, w, E_Notify, usagePageTitles1, 0x80)
        else if(VALUE_BETWEEN(page, 0x7f, 0x84))
                E_Notify(pstrUsagePageMonitor, 0x80);
        else if(VALUE_BETWEEN(page, 0x83, 0x8c))
                E_Notify(pstrUsagePagePower, 0x80);
        else if(page > 0xfeff /* && page <= 0xffff */)
                E_Notify(pstrUsagePageVendorDefined, 0x80);
        else
                switch(page) {
                        case 0x14:
                                E_Notify(pstrUsagePageAlphaNumericDisplay, 0x80);
                                break;
                        case 0x40:
                                E_Notify(pstrUsagePageMedicalInstruments, 0x80);
                                break;
                        default:
                                E_Notify(pstrUsagePageUndefined, 0x80);
                }
}

void ReportDescParserBase::PrintButtonPageUsage(uint16_t usage) {
        E_Notify(pstrSpace, 0x80);
        E_Notify(PSTR("Btn"), 0x80);
        PrintHex<uint16_t > (usage, 0x80);
        E_Notify(PSTR("\r\n"), 0x80);
        //USB_HOST_SERIAL.print(usage, HEX);
}

void ReportDescParserBase::PrintOrdinalPageUsage(uint16_t usage) {
        E_Notify(pstrSpace, 0x80);
        E_Notify(PSTR("Inst"), 0x80);
        // Sorry, HEX for now...
        PrintHex<uint16_t > (usage, 0x80);
        E_Notify(PSTR("\r\n"), 0x80);
        //USB_HOST_SERIAL.print(usage, DEC);
}

void ReportDescParserBase::PrintGenericDesktopPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x0a, w, E_Notify, genDesktopTitles0, 0x80)
        else output_if_between(usage, 0x2f, 0x49, w, E_Notify, genDesktopTitles1, 0x80)
        else output_if_between(usage, 0x7f, 0x94, w, E_Notify, genDesktopTitles2, 0x80)
        else output_if_between(usage, 0x9f, 0xa9, w, E_Notify, genDesktopTitles3, 0x80)
        else output_if_between(usage, 0xaf, 0xb8, w, E_Notify, genDesktopTitles4, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintSimulationControlsPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x0d, w, E_Notify, simuTitles0, 0x80)
        else output_if_between(usage, 0x1f, 0x26, w, E_Notify, simuTitles1, 0x80)
        else output_if_between(usage, 0xaf, 0xd1, w, E_Notify, simuTitles2, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintVRControlsPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x0b, w, E_Notify, vrTitles0, 0x80)
        else output_if_between(usage, 0x1f, 0x22, w, E_Notify, vrTitles1, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintSportsControlsPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x05, w, E_Notify, sportsCtrlTitles0, 0x80)
        else output_if_between(usage, 0x2f, 0x3a, w, E_Notify, sportsCtrlTitles1, 0x80)
        else output_if_between(usage, 0x4f, 0x64, w, E_Notify, sportsCtrlTitles2, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintGameControlsPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x04, w, E_Notify, gameTitles0, 0x80)
        else output_if_between(usage, 0x1f, 0x3a, w, E_Notify, gameTitles1, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintGenericDeviceControlsPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x1f, 0x27, w, E_Notify, genDevCtrlTitles, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintLEDPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x4e, w, E_Notify, ledTitles, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintTelephonyPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x08, w, E_Notify, telTitles0, 0x80)
        else output_if_between(usage, 0x1f, 0x32, w, E_Notify, telTitles1, 0x80)
        else output_if_between(usage, 0x4f, 0x54, w, E_Notify, telTitles2, 0x80)
        else output_if_between(usage, 0x6f, 0x75, w, E_Notify, telTitles3, 0x80)
        else output_if_between(usage, 0x8f, 0x9f, w, E_Notify, telTitles4, 0x80)
        else output_if_between(usage, 0xaf, 0xc0, w, E_Notify, telTitles5, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintConsumerPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x07, w, E_Notify, consTitles0, 0x80)
        else output_if_between(usage, 0x1f, 0x23, w, E_Notify, consTitles1, 0x80)
        else output_if_between(usage, 0x2f, 0x37, w, E_Notify, consTitles2, 0x80)
        else output_if_between(usage, 0x3f, 0x49, w, E_Notify, consTitles3, 0x80)
        else output_if_between(usage, 0x5f, 0x67, w, E_Notify, consTitles4, 0x80)
        else output_if_between(usage, 0x7f, 0xa5, w, E_Notify, consTitles5, 0x80)
        else output_if_between(usage, 0xaf, 0xcf, w, E_Notify, consTitles6, 0x80)
        else output_if_between(usage, 0xdf, 0xeb, w, E_Notify, consTitles7, 0x80)
        else output_if_between(usage, 0xef, 0xf6, w, E_Notify, consTitles8, 0x80)
        else output_if_between(usage, 0xff, 0x10e, w, E_Notify, consTitles9, 0x80)
        else output_if_between(usage, 0x14f, 0x156, w, E_Notify, consTitlesA, 0x80)
        else output_if_between(usage, 0x15f, 0x16b, w, E_Notify, consTitlesB, 0x80)
        else output_if_between(usage, 0x16f, 0x175, w, E_Notify, consTitlesC, 0x80)
        else output_if_between(usage, 0x17f, 0x1c8, w, E_Notify, consTitlesD, 0x80)
        else output_if_between(usage, 0x1ff, 0x29d, w, E_Notify, consTitlesE, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintDigitizerPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x0e, w, E_Notify, digitTitles0, 0x80)
        else output_if_between(usage, 0x1f, 0x23, w, E_Notify, digitTitles1, 0x80)
        else output_if_between(usage, 0x2f, 0x47, w, E_Notify, digitTitles2, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintAlphanumDisplayPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        output_if_between(usage, 0x00, 0x03, w, E_Notify, aplphanumTitles0, 0x80)
        else output_if_between(usage, 0x1f, 0x4e, w, E_Notify, aplphanumTitles1, 0x80)
        else output_if_between(usage, 0x7f, 0x96, w, E_Notify, digitTitles2, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

void ReportDescParserBase::PrintMedicalInstrumentPageUsage(uint16_t usage) {
        const char * const * w;
        E_Notify(pstrSpace, 0x80);

        if(usage == 1) E_Notify(pstrUsageMedicalUltrasound, 0x80);
        else if(usage == 0x70)
                E_Notify(pstrUsageDepthGainCompensation, 0x80);
        else output_if_between(usage, 0x1f, 0x28, w, E_Notify, medInstrTitles0, 0x80)
        else output_if_between(usage, 0x3f, 0x45, w, E_Notify, medInstrTitles1, 0x80)
        else output_if_between(usage, 0x5f, 0x62, w, E_Notify, medInstrTitles2, 0x80)
        else output_if_between(usage, 0x7f, 0x8a, w, E_Notify, medInstrTitles3, 0x80)
        else output_if_between(usage, 0x9f, 0xa2, w, E_Notify, medInstrTitles4, 0x80)
        else E_Notify(pstrUsagePageUndefined, 0x80);
}

uint8_t ReportDescParser2::ParseItem(uint8_t **pp, uint16_t *pcntdn) {
        //uint8_t ret = enErrorSuccess;

        switch(itemParseState) {
                case 0:
                        if(**pp == HID_LONG_ITEM_PREFIX)
                                USBTRACE("\r\nLONG\r\n");
                        else {
                                uint8_t size = ((**pp) & DATA_SIZE_MASK);
                                itemPrefix = (**pp);
                                itemSize = 1 + ((size == DATA_SIZE_4) ? 4 : size);
                        }
                        (*pp)++;
                        (*pcntdn)--;
                        itemSize--;
                        itemParseState = 1;

                        if(!itemSize)
                                break;

                        if(!pcntdn)
                                return enErrorIncomplete;
                case 1:
                        theBuffer.valueSize = itemSize;
                        valParser.Initialize(&theBuffer);
                        itemParseState = 2;
                case 2:
                        if(!valParser.Parse(pp, pcntdn))
                                return enErrorIncomplete;
                        itemParseState = 3;
                case 3:
                {
                        uint8_t data = *((uint8_t*)varBuffer);

                        switch(itemPrefix & (TYPE_MASK | TAG_MASK)) {
                                case (TYPE_LOCAL | TAG_LOCAL_USAGE):
                                        if(pfUsage) {
                                                if(theBuffer.valueSize > 1) {
                                                        uint16_t* ui16 = reinterpret_cast<uint16_t *>(varBuffer);
                                                        pfUsage(*ui16);
                                                } else
                                                        pfUsage(data);
                                        }
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTSIZE):
                                        rptSize = data;
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTCOUNT):
                                        rptCount = data;
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_REPORTID):
                                        rptId = data;
                                        break;
                                case (TYPE_LOCAL | TAG_LOCAL_USAGEMIN):
                                        useMin = data;
                                        break;
                                case (TYPE_LOCAL | TAG_LOCAL_USAGEMAX):
                                        useMax = data;
                                        break;
                                case (TYPE_GLOBAL | TAG_GLOBAL_USAGEPAGE):
                                        SetUsagePage(data);
                                        break;
                                case (TYPE_MAIN | TAG_MAIN_OUTPUT):
                                case (TYPE_MAIN | TAG_MAIN_FEATURE):
                                        rptSize = 0;
                                        rptCount = 0;
                                        useMin = 0;
                                        useMax = 0;
                                        break;
                                case (TYPE_MAIN | TAG_MAIN_INPUT):
                                        OnInputItem(data);

                                        totalSize += (uint16_t)rptSize * (uint16_t)rptCount;

                                        rptSize = 0;
                                        rptCount = 0;
                                        useMin = 0;
                                        useMax = 0;
                                        break;
                        } // switch (**pp & (TYPE_MASK | TAG_MASK))
                }
        } // switch (itemParseState)
        itemParseState = 0;
        return enErrorSuccess;
}

void ReportDescParser2::OnInputItem(uint8_t itm) {
        uint8_t byte_offset = (totalSize >> 3); // calculate offset to the next unhandled byte i = (int)(totalCount / 8);
        uint32_t tmp = (byte_offset << 3);
        uint8_t bit_offset = totalSize - tmp; // number of bits in the current byte already handled
        uint8_t *p = pBuf + byte_offset; // current byte pointer

        if(bit_offset)
                *p >>= bit_offset;

        uint8_t usage = useMin;

        bool print_usemin_usemax = ((useMin < useMax) && ((itm & 3) == 2) && pfUsage) ? true : false;

        uint8_t bits_of_byte = 8;

        // for each field in field array defined by rptCount
        for(uint8_t field = 0; field < rptCount; field++, usage++) {

                union {
                        uint8_t bResult[4];
                        uint16_t wResult[2];
                        uint32_t dwResult;
                } result;

                result.dwResult = 0;
                uint8_t mask = 0;

                if(print_usemin_usemax)
                        pfUsage(usage);

                // bits_left            - number of bits in the field(array of fields, depending on Report Count) left to process
                // bits_of_byte         - number of bits in current byte left to process
                // bits_to_copy         - number of bits to copy to result buffer

                // for each bit in a field
                for(uint8_t bits_left = rptSize, bits_to_copy = 0; bits_left;
                        bits_left -= bits_to_copy) {
                        bits_to_copy = (bits_left > bits_of_byte) ? bits_of_byte : bits_left;

                        result.dwResult <<= bits_to_copy; // Result buffer is shifted by the number of bits to be copied into it

                        uint8_t val = *p;

                        val >>= (8 - bits_of_byte); // Shift by the number of bits already processed

                        mask = 0;

                        for(uint8_t j = bits_to_copy; j; j--) {
                                mask <<= 1;
                                mask |= 1;
                        }

                        result.bResult[0] = (result.bResult[0] | (val & mask));

                        bits_of_byte -= bits_to_copy;

                        if(bits_of_byte < 1) {
                                bits_of_byte = 8;
                                p++;
                        }
                }
                PrintByteValue(result.dwResult);
        }
        E_Notify(PSTR("\r\n"), 0x80);
}

void UniversalReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
        ReportDescParser2 prs(len, buf);

        uint8_t ret = hid->GetReportDescr(0, &prs);

        if(ret)
                ErrorMessage<uint8_t > (PSTR("GetReportDescr-2"), ret);
}
