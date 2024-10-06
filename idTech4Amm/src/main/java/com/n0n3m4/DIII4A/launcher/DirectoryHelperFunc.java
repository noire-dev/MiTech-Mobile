package com.n0n3m4.DIII4A.launcher;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import org.noiredev.sandbox.R;
import org.noiredev.sandbox.lib.ContextUtility;
import org.noiredev.sandbox.lib.KCVar;
import org.noiredev.sandbox.lib.KCVarSystem;
import org.noiredev.sandbox.lib.Utility;
import org.noiredev.sandbox.misc.TextHelper;
import org.noiredev.sandbox.sys.Constants;
import org.noiredev.sandbox.sys.Game;
import org.noiredev.sandbox.sys.GameManager;
import org.noiredev.sandbox.ui.ArrayAdapter_base;
import com.n0n3m4.DIII4A.GameLauncher;
import com.n0n3m4.q3e.Q3EGlobals;
import com.n0n3m4.q3e.Q3EInterface;
import com.n0n3m4.q3e.Q3ELang;
import com.n0n3m4.q3e.Q3EPreference;
import com.n0n3m4.q3e.Q3EUtils;
import com.n0n3m4.q3e.karin.KStr;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public final class DirectoryHelperFunc extends GameLauncherFunc
{
    public DirectoryHelperFunc(GameLauncher gameLauncher)
    {
        super(gameLauncher);
    }

    public void Reset()
    {
    }

    public void Start(Bundle data)
    {
        super.Start(data);
        Reset();

        run();
    }

    public void run()
    {
        ContextUtility.OpenMessageDialog(m_gameLauncher, Q3ELang.tr(m_gameLauncher, R.string.current_game_data_path), GetHelperText());
    }

    public CharSequence GetHelperText()
    {
        StringBuilder sb = new StringBuilder();
        final String endl = TextHelper.GetDialogMessageEndl();
        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(m_gameLauncher);
        final String DataDir = preferences.getString(Q3EPreference.pref_datapath, "");
        final boolean Standalone = preferences.getBoolean(Q3EPreference.GAME_STANDALONE_DIRECTORY, false);
        Game[] values = Game.values();
        for (String game : GameManager.Games)
        {
            String gameName = Q3ELang.tr(m_gameLauncher, GameManager.GetGameNameTs(game));
            sb.append("------- ").append(gameName).append(" -------").append(endl);
            int i = 1;
            for (Game value : values)
            {
                if(!value.type.equals(game))
                    continue;

                String subdir = GetSubDir(value.type, Standalone);
                String name = value.GetName(m_gameLauncher);
                sb.append(" ").append(String.format("%2d", i)).append(". ").append(name).append(" -> ").append(endl);
                String path = "";

                if(!game.equals(Q3EGlobals.GAME_QUAKE1))
                {
                    String appHome = Q3EUtils.GetAppInternalSearchPath(m_gameLauncher, null);
                    path = KStr.AppendPath(appHome, subdir, value.game);
                    String pathText = TextHelper.GenLinkText("file://" + path, path);
                    sb.append(" * ").append(pathText).append(endl);
                }

                String path2 = KStr.AppendPath(DataDir, subdir, value.game);
                if(!path2.equals(path))
                {
                    String pathText = TextHelper.GenLinkText("file://" + path2, path2);
                    sb.append(" * ").append(pathText).append(endl);
                }
                i++;
            }

            sb.append(endl);
        }
        return TextHelper.GetDialogMessage(sb.toString());
    }

    private String GetSubDir(String game, boolean standalone)
    {
        final String[] AlwaysStandalone = {
                Q3EGlobals.GAME_TDM,
                Q3EGlobals.GAME_SUBDIR_DOOMBFG,
                Q3EGlobals.GAME_GZDOOM,
        };
        if(standalone || Utility.ArrayContains(AlwaysStandalone, game))
            return Q3EInterface.GetGameStandaloneDirectory(game);
        else
            return null;
    }
}
