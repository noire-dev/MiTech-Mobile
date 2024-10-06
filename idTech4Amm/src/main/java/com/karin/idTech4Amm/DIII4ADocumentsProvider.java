package org.noiredev.sandbox;

import android.annotation.TargetApi;
import android.os.Build;
import android.preference.PreferenceManager;

import org.noiredev.sandbox.misc.HarmDocumentsProvider;
import com.n0n3m4.DIII4A.GameLauncher;
import com.n0n3m4.q3e.Q3EPreference;

// Document provider: user
@TargetApi(Build.VERSION_CODES.KITKAT)
public class DIII4ADocumentsProvider extends HarmDocumentsProvider
{
    @Override
    protected String GetPath()
    {
        return PreferenceManager.getDefaultSharedPreferences(getContext()).getString(Q3EPreference.pref_datapath, GameLauncher.default_gamedata);
    }

}
