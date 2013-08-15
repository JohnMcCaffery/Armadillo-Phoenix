The defaults for the following settings have been changed to help with Chimera.

app_settings/ignoreable_dialogs:
Appended:
    <key>ConfirmQuit</key>
    <map>
      <key>Comment</key>
      <string>Stop firestorm prompting the user before quitting</string>
      <key>Persist</key>
      <integer>1</integer>
      <key>Type</key>
      <string>Boolean</string>
      <key>Value</key>
      <integer>0</integer>
    </map>

app_settings/settings:
DisableCameraConstraints = 1
EnableRemoteControl = 1
EnableSetFollowCamProperties = 0
EnableSetCamera = 1
InterpolateScriptFollowCam = 0
AvatarNameTagMode = 0
ShowNavbarFavoritesPanel = 0
ShowSearchTopBar = 0
ShowMenuBarLocation = 0
CameraOffsetRearView = -1.0, 0.0, 0.0
BackgroundYieldTime = 0
ThrottleMaximumKBPs = 1500.0
//Don't do this for multiple viewers - FullScreen = 1

skins\defaults\toolbars:
Removed all <command> nodes

featuretable.txt Under 'High' settings:
RenderFarClip = 1024
RenderVolumeLODFactory = 4.0
RenderTerrainLODFactor = 4.0
RenderReflectionDetail = 0 0

featuretable.txt and featuretable_xp - all settings
RenderFarClip = 1024

Set Low, and LowFixed to be the same as high settings.


Branches from:
changeset:   31155:d1723a46b247
branch:      Firestorm_4.3.1
tag:         tip
parent:      31153:faa1ef52396b
user:        Nicky
date:        Thu Nov 29 21:59:38 2012 +0100
summary:     Resetting Version to 4.3.1 as it got changed by merge.

