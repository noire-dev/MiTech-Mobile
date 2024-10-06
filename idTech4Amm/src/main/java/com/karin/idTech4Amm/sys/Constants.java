package org.noiredev.sandbox.sys;

import org.noiredev.sandbox.BuildConfig;
import org.noiredev.sandbox.lib.DateTimeUtility;
import org.noiredev.sandbox.misc.TextHelper;

import java.util.Arrays;
import java.util.Date;

/**
 * Constants define
 */
public final class Constants
{
    public static final int    CONST_UPDATE_RELEASE = 57;
    public static final String CONST_RELEASE = "2024-09-17";
    public static final String CONST_EMAIL = "beyondk2000@gmail.com";
    public static final String CONST_DEV = "Karin";
    public static final String CONST_CODE = "Harmattan";
    public static final String CONST_APP_NAME = "idTech4A++"; // "DIII4A++";
    public static final String CONST_NAME = "DOOM III/Quake 4/Prey(2006)/DOOM 3 BFG for Android(Harmattan Edition)";
	public static final String CONST_MAIN_PAGE = "https://github.com/glKarin/com.n0n3m4.diii4a";
    public static final String CONST_TIEBA = "https://tieba.baidu.com/p/6825594793";
	public static final String CONST_DEVELOPER = "https://github.com/glKarin";
    public static final String CONST_DEVELOPER_XDA = "https://forum.xda-developers.com/member.php?u=10584229";
    public static final String CONST_PACKAGE = "org.noiredev.sandbox";
    public static final String CONST_FDROID = "https://f-droid.org/packages/org.noiredev.sandbox/";
	public static final String CONST_CHECK_FOR_UPDATE_URL = "https://raw.githubusercontent.com/glKarin/com.n0n3m4.diii4a/master/CHECK_FOR_UPDATE.json";
    public static final String CONST_LICENSE_URL = "https://raw.githubusercontent.com/glKarin/com.n0n3m4.diii4a/master/LICENSE";
	public static String[] CONST_CHANGES()
    {
        return new String[] {
            "Add `ambientLighting` shader, add ambient lighting model with `harm_r_lightingModel` to 4 in DOOM3/Quake4/Prey.",
            "Add `Quake 4: Hardqore` mod of Quake4 support, game data directory named `hardqore`. More view in `" + TextHelper.GenLinkText("https://www.moddb.com/mods/quake-4-hardqore", "Quake 4: Hardqore") + "`.",
            "Add effects color alpha in Quake4.",
            "Add cvar `harm_in_smoothJoystick` to control setup smooth joystick in DOOM3/Quake4/Prey.",
        };
	};

    public static long GetBuildTimestamp()
    {
        return BuildConfig.BUILD_TIMESTAMP;
    }

    public static int GetBuildSDKVersion()
    {
        return BuildConfig.BUILD_SDK_VERSION;
    }

    public static boolean IsDebug()
    {
        return BuildConfig.DEBUG;
    }

    public static String GetBuildTime(String format)
    {
        return DateTimeUtility.Format(GetBuildTimestamp(), format);
    }
    
	private Constants() {}
}
