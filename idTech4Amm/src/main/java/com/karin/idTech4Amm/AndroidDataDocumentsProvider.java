package org.noiredev.sandbox;

import android.annotation.TargetApi;
import android.os.Build;

import org.noiredev.sandbox.misc.HarmDocumentsProvider;
import com.n0n3m4.q3e.Q3ELang;
import com.n0n3m4.q3e.Q3EUtils;

// Document provider: /sdcard/Android/data/<package_name>/files
@TargetApi(Build.VERSION_CODES.KITKAT)
public class AndroidDataDocumentsProvider extends HarmDocumentsProvider
{
    @Override
    protected String GetPath()
    {
        return Q3EUtils.GetAppStoragePath(getContext(), null);
    }

    @Override
    protected String GetName()
    {
        return Q3ELang.tr(getContext(), R.string.external_storage);
    }
}
