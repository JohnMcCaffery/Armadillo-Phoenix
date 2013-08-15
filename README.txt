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


changeset:   34166:3f303c53ab1f
branch:      Firestorm_4.4.2
user:        Nicky
date:        Mon Jul 01 21:42:31 2013 +0200
summary:     Backout 're-enabled SSA logging for LL SSA test'

